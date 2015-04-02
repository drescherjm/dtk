// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#include "dtkDistributedGraphTopology.h"

#if defined(DTK_HAVE_ZLIB)
#include <dtkCore/dtkIOCompressor>
#endif

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraphTopology implementation
// /////////////////////////////////////////////////////////////////

dtkDistributedGraphTopology::dtkDistributedGraphTopology(void) : dtkDistributedContainer()
{
    m_neighbour_count = NULL;
    m_edge_to_vertex  = NULL;
    m_vertex_to_edge  = NULL;
    m_edge_count = NULL;

    m_comm->barrier();
}

dtkDistributedGraphTopology::dtkDistributedGraphTopology(const qlonglong& vertex_count) : dtkDistributedContainer(vertex_count)
{
    m_neighbour_count = NULL;
    m_edge_to_vertex  = NULL;
    m_vertex_to_edge  = NULL;
    m_edge_count = NULL;
    this->initialize();

    m_comm->barrier();
}

dtkDistributedGraphTopology::~dtkDistributedGraphTopology(void)
{
    m_comm->barrier();

    if (m_neighbour_count)
        delete m_neighbour_count;
    if (m_vertex_to_edge)
        delete m_vertex_to_edge;
    if (m_edge_count)
        delete m_edge_count;
    if (m_edge_to_vertex)
        delete m_edge_to_vertex;
}

void dtkDistributedGraphTopology::resize(qlonglong vertex_count)
{
    m_size = vertex_count;
//    m_edge_to_vertex = new dtkDistributedArray<qlonglong>( edges_count);
    initialize();
}

dtkDistributedMapper *dtkDistributedGraphTopology::edge_mapper(void) const
{
    return m_edge_to_vertex->mapper();
}

void dtkDistributedGraphTopology::initialize(void)
{
    dtkDebug() << "initialize graph with" << vertexCount() << "vertexes, rank =" << this->wid();

    m_mapper->setMapping(vertexCount(), m_comm->size());

    dtkDistributedMapper *mapper = new dtkDistributedMapper;
    mapper->setMapping(vertexCount(), m_comm->size());
    mapper->setMap(vertexCount() + 1, m_comm->size());
    m_vertex_to_edge = new dtkDistributedArray<qlonglong>(vertexCount() + 1, mapper);
    m_vertex_to_edge->fill(0);

    m_neighbour_count = new dtkDistributedArray<qlonglong>(vertexCount() + 1, mapper);
    m_neighbour_count->fill(0);

    m_edge_count = new dtkDistributedArray<qlonglong>(m_comm->size());
    m_edge_count->fill(0);
}

void dtkDistributedGraphTopology::build(void)
{
    this->m_comm->barrier();

    qlonglong edge_count = 0;
    for (qlonglong i = 0; i < m_comm->size(); ++i) {
        edge_count += m_edge_count->at(i);
    }

    dtkDistributedMapper *mapper = new dtkDistributedMapper;
    mapper->initMap(edge_count, m_comm->size());

    qlonglong offset = 0;
    for (qlonglong i = 0; i < m_comm->size(); ++i) {
        mapper->setMap(offset ,i);
        offset += m_edge_count->at(i);
    }

    if (m_edge_to_vertex) {
        delete m_edge_to_vertex;
    }
    m_edge_to_vertex = new dtkDistributedArray<qlonglong>(edge_count, mapper);

    EdgeMap::const_iterator it  = m_map.cbegin();
    EdgeMap::const_iterator end = m_map.cend();

    offset = mapper->firstIndex(this->wid());
    qlonglong index = 0;
    for (; it != end; ++it) {
        m_vertex_to_edge->setAt(it.key(), offset);
        const EdgeList& edge_list = *it;
        offset += edge_list.count();
        EdgeList::const_iterator nit  = edge_list.begin();
        EdgeList::const_iterator nend = edge_list.end();
        for(;nit != nend; ++nit, ++index) {
            m_edge_to_vertex->begin()[index] = *nit;
        }
        m_neighbour_count->setAt(it.key(), edge_list.count());
    }

    this->m_comm->barrier();
    if (this->wid() == this->m_comm->size() - 1) {
        m_vertex_to_edge->setAt(m_vertex_to_edge->size() - 1, offset);
    }

    this->m_comm->barrier();
}

// read graph from file as described in
// http://people.sc.fsu.edu/~jburkardt/data/metis_graph/metis_graph.html
bool dtkDistributedGraphTopology::read(const QString& filename)
{
    QFile file(filename);
    qlonglong edges_count = 0;
    QTime time;
    QIODevice *in;

    if (this->wid() == 0) {
        time.start();

        if(filename.isEmpty() || (!file.exists())) {
            qWarning() << "input file is empty/does not exist" << filename << "Current dir is" << QDir::currentPath();
            return false;
        }

        QIODevice::OpenMode mode = QIODevice::ReadOnly;
        QFileInfo info = QFileInfo(filename);
#if defined(DTK_HAVE_ZLIB)
        if (info.suffix() == "gz") {
            in = new dtkIOCompressor(&file);
        } else {
            in = &file;
            mode |= QIODevice::Text;
        }
#else
        in = &file;
        mode |= QIODevice::Text;
#endif
        if (!in->open(mode))
            return false;

        QStringList header = QString(in->readLine()).split(' ');
        m_size = header.first().toLongLong();
        if (m_size  == 0) {
            qWarning() << "Can't parse size of the graph" << filename;
            return false;
        }
        edges_count = header.at(1).toLongLong();
        if (edges_count  == 0) {
            qWarning() << "Can't parse the number of edges" << filename;
            return false;
        }

    }
    m_comm->broadcast(&m_size, 1, 0);
    m_comm->broadcast(&edges_count, 1, 0);

    this->initialize();
    m_comm->barrier();

    m_edge_to_vertex = new dtkDistributedArray<qlonglong>(2 * edges_count);

    if (this->wid() == 0) {

        QString line;
        QStringList edges;

        QVector<qlonglong> n_vec; n_vec.reserve(2 * m_neighbour_count->mapper()->countMax());
        QVector<qlonglong> v_vec; v_vec.reserve(2 * m_vertex_to_edge->mapper()->countMax());
        QVector<qlonglong> e_vec; e_vec.reserve(2 * m_edge_to_vertex->mapper()->countMax());

        qlonglong e_gid = 0;
        qlonglong v_gid = 0;

        qlonglong e_local_count = 0;

        qlonglong owner = 0;
        qlonglong v_first_gid = m_vertex_to_edge->mapper()->firstIndex(owner);
        qlonglong v_last_gid  = m_vertex_to_edge->mapper()->lastIndex(owner);
        qlonglong e_first_gid = 0;

        while (!in->atEnd()) {
            line = in->readLine().trimmed();
            edges = line.split(' ');
            if (line.isEmpty() || line.at(0) == '#'){
                qDebug() << "skip line" << line;
                continue;
            }
            v_vec << e_gid;
            n_vec << edges.size();
            for (qlonglong i = 0; i < edges.size(); ++i) {
                qlonglong val = edges.at(i).toLongLong();
                if (val < 1 || val > m_size ) {
                    qWarning() << "bad vertice id in graph for edge" << val << v_gid;
                    continue;
                }
                e_vec << val-1;
                ++e_gid;
                ++e_local_count;
            }
            ++v_gid;
            if(in->atEnd()) {
                v_vec << e_gid;
                m_neighbour_count->setAt(v_first_gid, n_vec.data(), n_vec.size());
                m_vertex_to_edge->setAt(v_first_gid, v_vec.data(), v_vec.size());
                m_edge_to_vertex->setAt(e_first_gid, e_vec.data(), e_vec.size());
                m_edge_count->setAt(owner, e_local_count);
                
            } else if(v_gid > v_last_gid) {
                m_neighbour_count->setAt(v_first_gid, n_vec.data(), n_vec.size());
                m_vertex_to_edge->setAt(v_first_gid, v_vec.data(), v_vec.size());
                m_edge_to_vertex->setAt(e_first_gid, e_vec.data(), e_vec.size());
                m_edge_count->setAt(owner, e_local_count);
                
                ++owner;
                e_local_count = 0;
                v_first_gid = v_gid;
                v_last_gid  = m_vertex_to_edge->mapper()->lastIndex(owner);
                e_first_gid = e_gid;
                n_vec.clear();
                n_vec.reserve(2 * m_neighbour_count->mapper()->countMax());
                v_vec.clear();
                v_vec.reserve(2 * m_vertex_to_edge->mapper()->countMax());
                e_vec.clear();
                e_vec.reserve(2 * m_edge_to_vertex->mapper()->countMax());
            }
        }
    }

    m_comm->barrier();

    if (this->wid() == 0) {
        qDebug() << "read done in "<< time.elapsed() << "ms";
        time.restart();
    }
    if (m_comm->size() > 1) {
        dtkDistributedMapper *mapper = new dtkDistributedMapper;
        mapper->initMap(2 * edges_count, m_comm->size());

        qlonglong offset = 0;
        for (qlonglong i = 0; i < m_comm->size(); ++i) {
            mapper->setMap(offset ,i);
            offset += m_edge_count->at(i);
        }
        m_edge_to_vertex->remap(mapper);
        if (this->wid() == 0) {
            qDebug() << "remap done in "<< time.elapsed() << "ms";
        }
    }

    return true;
}

void dtkDistributedGraphTopology::addEdge(qlonglong from, qlonglong to, bool oriented)
{
    qint32 wid = this->wid();
    qint32 from_owner = static_cast<qint32>(m_mapper->owner(from));

    if (wid == from_owner) {
        qlonglong edge_counter = m_edge_count->at(wid);

        EdgeList::iterator it  = m_map[from].begin();
        EdgeList::iterator end = m_map[from].end();

        if (it == end) {
            m_map[from].insert(it, to);
        } else if (to > m_map[from].last()) {
            // tuning: usually, we append at the end, so check this case
            m_map[from].insert(end, to);
        } else {
            for(; it != end; ++it) {
                if (to < (*it))
                    break;
            }
            m_map[from].insert(it, to);
        }

        // m_map[from].append(to);
        ++edge_counter;
        m_edge_count->setAt(wid, edge_counter);
    }

    if (!oriented) {
        addEdge(to, from, true);
    }
}

// 
// dtkDistributedGraphTopology.cpp ends here


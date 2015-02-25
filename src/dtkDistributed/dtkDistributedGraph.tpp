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

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraph implementation
// /////////////////////////////////////////////////////////////////

inline dtkDistributedGraph::dtkDistributedGraph(void) : dtkDistributedContainer()
{
    m_edges      = NULL;
    m_vertices   = NULL;
    m_edge_count = NULL;

}

inline dtkDistributedGraph::dtkDistributedGraph(const qlonglong& vertex_count) : dtkDistributedContainer(vertex_count)
{
    m_edges = NULL;
    this->initialize();
}

inline dtkDistributedGraph::~dtkDistributedGraph(void)
{
    if (m_vertices)
        delete m_vertices;
    if (m_edge_count)
        delete m_edge_count;
    if (m_edges)
        delete m_edges;
}

inline qlonglong dtkDistributedGraph::vertexCount(void) const
{
    return this->size();
}

inline qlonglong dtkDistributedGraph::edgeCount(void) const
{
    return m_edge_count->at(this->wid());
}

inline void dtkDistributedGraph::initialize(void)
{
    qDebug() << "initialize graph with " << vertexCount() << "vertexes" << this->wid();

    m_mapper->setMapping(vertexCount(), m_comm->size());

    dtkDistributedMapper *mapper = new dtkDistributedMapper;
    mapper->setMapping(vertexCount(), m_comm->size());
    mapper->setMap(vertexCount() + 1, m_comm->size());
    m_vertices = new dtkDistributedArray<qlonglong>(vertexCount() + 1, mapper);

    m_edge_count = new dtkDistributedArray<qlonglong>(m_comm->size());
    for (qint32 i = 0; i< m_comm->size(); i++) {
        if (i == this->wid()) {
            m_edge_count->setAt(i,0);
        }
    }
}

inline void dtkDistributedGraph::build(void)
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

    m_edges = new dtkDistributedArray<qlonglong>(edge_count, mapper);

    EdgeMap::const_iterator it  = m_map.cbegin();
    EdgeMap::const_iterator end = m_map.cend();

    offset = mapper->firstIndex(this->wid());
    qlonglong index = 0;
    for (; it != end; ++it) {
        m_vertices->setAt(it.key(), offset);
        offset += (*it).count();
        EdgeList::const_iterator nit  = (*it).begin();
        EdgeList::const_iterator nend = (*it).end();
        for(;nit != nend; ++nit) {
            m_edges->begin()[index] = *nit;
            ++index;
        }
    }

    this->m_comm->barrier();
    if (this->wid() == this->m_comm->size() - 1) {
        m_vertices->setAt(m_vertices->size() - 1, offset);
    }

    this->m_comm->barrier();
}

inline bool dtkDistributedGraph::read2(const QString& filename)
{
    QFile file(filename);
    QTextStream in(&file);
    qlonglong edges_count = 0;
    QTime time;

    if (this->wid() == 0) {
        time.start();

        if(filename.isEmpty() || (!file.exists())) {
            qWarning() << "input file is empty/does not exist" << filename << "Current dir is" << QDir::currentPath();
            return false;
        }
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

        QStringList header = in.readLine().split(' ');
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

    m_edges = new dtkDistributedArray<qlonglong>(2 * edges_count);

    if (this->wid() == 0) {

        QString line;
        QStringList edges;

        QVector<qlonglong> v_vec; v_vec.reserve(2 * m_vertices->mapper()->countMax());
        QVector<qlonglong> e_vec; e_vec.reserve(2 * m_edges->mapper()->countMax());

        qlonglong e_gid = 0;
        qlonglong v_gid = 0;

        qlonglong e_local_count = 0;

        qlonglong owner = 0;
        qlonglong v_first_gid = m_vertices->mapper()->firstIndex(owner);
        qlonglong v_last_gid  = m_vertices->mapper()->lastIndex(owner);
        qlonglong e_first_gid = 0;

        while (!in.atEnd()) {
            line = in.readLine().trimmed();
            edges = line.split(' ');
            if (line.isEmpty() || line.at(0) == '#'){
                qDebug() << "skip line" << line;
                continue;
            }
            v_vec << e_gid;
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
            if(v_gid > v_last_gid || in.atEnd()) {
                if(in.atEnd()) {
                    v_vec << e_gid;
                    m_vertices->setAt(v_first_gid, v_vec.data(), v_vec.size());
                    m_edges->setAt(e_first_gid, e_vec.data(), e_vec.size());
                    m_edge_count->setAt(owner, e_local_count);
                
                } else {
                    m_vertices->setAt(v_first_gid, v_vec.data(), v_vec.size());
                    m_edges->setAt(e_first_gid, e_vec.data(), e_vec.size());
                    m_edge_count->setAt(owner, e_local_count);

                    ++owner;
                    e_local_count = 0;
                    v_first_gid = v_gid;
                    v_last_gid  = m_vertices->mapper()->lastIndex(owner);
                    e_first_gid = e_gid;
                    v_vec.clear();
                    v_vec.reserve(2 * m_vertices->mapper()->countMax());
                    e_vec.clear();
                    e_vec.reserve(2 * m_edges->mapper()->countMax());
                }
            }
        }
    }

    m_comm->barrier();

    qDebug() << "remap";
    dtkDistributedMapper *mapper = new dtkDistributedMapper;
    mapper->initMap(2 * edges_count, m_comm->size());

    qlonglong offset = 0;
    for (qlonglong i = 0; i < m_comm->size(); ++i) {
        mapper->setMap(offset ,i);
        offset += m_edge_count->at(i);
    }
    m_edges->remap(mapper);
    if (this->wid() == 0) {
        qDebug() << "read and remap done in "<< time.elapsed() << "ms";
    }

    return true;
}

// read graph from file as described in
// http://people.sc.fsu.edu/~jburkardt/data/metis_graph/metis_graph.html

inline bool dtkDistributedGraph::read(const QString& filename)
{
    QFile file(filename);
    QTextStream in(&file);
    qlonglong edges_count = 0;
    QTime time;

    if (this->wid() == 0) {
        time.start();

        if(filename.isEmpty() || (!file.exists())) {
            qWarning() << "input file is empty/does not exist" << filename << "Current dir is" << QDir::currentPath();
            m_size = -1;
        } else if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            m_size = -1;
        } else {

            QStringList header = in.readLine().split(' ');
            m_size = header.first().toLongLong();
            if (m_size  == 0) {
                qWarning() << "Can't parse size of the graph" << filename;
                m_size = -1;
            } else {
                edges_count = header.at(1).toLongLong();
                if (edges_count  == 0) {
                    qWarning() << "Can't parse the number of edges" << filename;
                    m_size = -1;
                }
            }
        }
    }
    m_comm->broadcast(&m_size, 1, 0);

    if (m_size < 0)
        return false;

    m_comm->broadcast(&edges_count, 1, 0);

    this->initialize();
    m_comm->barrier();

    m_edges = new dtkDistributedArray<qlonglong>(2 * edges_count);

    if (this->wid() == 0) {

        qlonglong index              = 0;
        qlonglong current_edge_count = 0;
        qlonglong current_owner      = 0;
        qlonglong current_vertice    = 0;
        qlonglong temp_owner;

        QString line;
        QStringList edges;

        qlonglong owner = 0;
        qlonglong next_index = m_edges->mapper()->lastIndex(owner);

        qlonglong max_vert_size = m_vertices->mapper()->countMax();
        qlonglong max_edge_size = m_edges->mapper()->countMax();

        qlonglong *v_array = new qlonglong[max_vert_size];
        qlonglong *e_array = new qlonglong[max_edge_size];

        qlonglong val;
        qlonglong v_pos = 0;
        qlonglong e_pos = 0;
        while (!in.atEnd()) {
            line = in.readLine().trimmed();
            edges = line.split(' ');
            if (line.isEmpty() || line.at(0) == '#'){
                qDebug() << "skip line" << line;
                continue;
            }
            v_array[v_pos] = index;
            for (qlonglong i = 0; i < edges.size(); ++i) {
                val = edges.at(i).toLongLong();
                if (val < 1 || val > m_size ) {
                    qWarning() << "bad vertice id in graph for edge" << val << current_vertice;
                    continue;
                }
                e_array[e_pos] = val-1;
                ++e_pos;
                ++index;
                ++current_edge_count;
                if (index > next_index) {
                    m_edges->setAt(m_edges->mapper()->firstIndex(owner), e_array, e_pos);
                    owner++;
                    e_pos = 0;
                    if (owner <  m_comm->size()) {
                        next_index = m_edges->mapper()->lastIndex(owner);
                    }
                }
            }

            ++current_vertice;
            ++v_pos;

            temp_owner = m_vertices->mapper()->owner(current_vertice, current_owner);
            if (temp_owner != current_owner) {
                m_edge_count->setAt(current_owner, current_edge_count);
                m_vertices->setAt(m_vertices->mapper()->firstIndex(current_owner), v_array, v_pos);
                current_owner = temp_owner;
                current_edge_count = 0;
                v_pos = 0;
            }
        }
        v_array[v_pos] = index; ++v_pos;
        m_vertices->setAt(m_vertices->mapper()->firstIndex(m_vertices->mapper()->owner(current_vertice, current_owner)), v_array, v_pos);
        delete[] v_array;
        delete[] e_array;

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
        m_edges->remap(mapper);
        if (this->wid() == 0) {
            qDebug() << "remap done in "<< time.elapsed() << "ms";
        }
    }
    return true;
}

inline void dtkDistributedGraph::appendEdge(qlonglong from, qlonglong to)
{
    qint32 wid = this->wid();
    qint32 from_owner = static_cast<qint32>(m_mapper->owner(from, wid));
    qint32 to_owner = static_cast<qint32>(m_mapper->owner(to, wid));

    if ((wid != from_owner) && (wid != to_owner))
        return;

    qlonglong edge_counter = m_edge_count->at(this->wid());

    if (wid == from_owner) {
        m_map[from].append(to);
        ++edge_counter;
    }
    if (wid == to_owner) {
        m_map[to].append(from);
        ++edge_counter;
    }
    m_edge_count->setAt(wid, edge_counter);
}

inline qlonglong dtkDistributedGraph::edgeCount(qlonglong vertex_id) const
{
    qlonglong start = m_vertices->at(vertex_id);
    return (m_vertices->at(vertex_id + 1) - start);
}

inline dtkDistributedGraph::Neighbours dtkDistributedGraph::neighbours(const qlonglong& vertex_id) const
{
    qlonglong n_start = m_vertices->at(vertex_id);
    qlonglong size = m_vertices->at(vertex_id + 1) - n_start;

    return Neighbours(*m_edges, n_start, size);
}

inline dtkDistributedGraph::Neighbours dtkDistributedGraph::operator[](qlonglong vertex_id) const
{
    return this->neighbours(vertex_id);
}

dtkDistributedGraph::const_iterator dtkDistributedGraph::cbegin(void) const
{
    return const_iterator(*this, this->m_mapper->firstIndex(this->wid())); 
}

dtkDistributedGraph::const_iterator dtkDistributedGraph::cend(void) const 
{ 
    return const_iterator(*this, this->m_mapper->lastIndex(this->wid()) + 1); 
}

dtkDistributedGraph::const_iterator dtkDistributedGraph::begin(void) const 
{ 
    return const_iterator(*this, this->m_mapper->firstIndex(this->wid())); 
}

dtkDistributedGraph::const_iterator dtkDistributedGraph::end(void) const 
{
    return const_iterator(*this, this->m_mapper->lastIndex(this->wid()) + 1); 
}

//
// dtkDistributedGraph.tpp ends here

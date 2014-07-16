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

inline dtkDistributedGraph::dtkDistributedGraph(dtkDistributedWorker *worker) : dtkDistributedContainer(worker)
{
    m_edges      = NULL;
    m_vertices   = NULL;
    m_edge_count = NULL;

}

inline dtkDistributedGraph::dtkDistributedGraph(const qlonglong& vertex_count, dtkDistributedWorker *worker) : dtkDistributedContainer(vertex_count, worker)
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
    m_vertices = new dtkDistributedArray<qlonglong>(vertexCount() + 1, this->worker(), mapper);

    m_edge_count = new dtkDistributedArray<qlonglong>(m_comm->size(), this->worker());
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

    m_edges = new dtkDistributedArray<qlonglong>(edge_count, this->worker(), mapper);

    EdgeMap::const_iterator it  = m_map.cbegin();
    EdgeMap::const_iterator end = m_map.cend();

    offset = mapper->startIndex(this->wid());
    qlonglong index = 0;
    for (; it != end; ++it) {
        m_vertices->setAt(it.key(), offset);
        offset += (*it).count();
        EdgeList::const_iterator nit  = (*it).begin();
        EdgeList::const_iterator nend = (*it).end();
        for(;nit != nend; ++nit) {
            m_edges->setLocalValue(index, *nit);
            ++index;
        }
    }

    this->m_comm->barrier();
    if (this->wid() == this->m_comm->size() - 1) {
        m_vertices->setAt(m_vertices->size() - 1, offset);
    }

    this->m_comm->barrier();
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

    m_edges = new dtkDistributedArray<qlonglong>(2 * edges_count, this->worker());

    if (this->wid() == 0) {

        qlonglong index              = 0;
        qlonglong current_edge_count = 0;
        qlonglong current_owner      = 0;
        qlonglong current_vertice    = 0;
        qlonglong temp_owner;

        QString line;
        QStringList edges;
        m_vertices->setAt(0, 0);

        while (!in.atEnd()) {
            line = in.readLine().trimmed();
            edges = line.split(' ');
            if (line.isEmpty() || line.at(0) == '#'){
                continue ;
            }
            for (qlonglong i = 0; i < edges.size(); ++i) {
                m_edges->setAt(index, edges.at(i).toLongLong() -1);
                ++index;
                ++current_edge_count;
            }

            ++current_vertice;
            m_vertices->setAt(current_vertice, index);

            temp_owner = m_vertices->mapper()->owner(current_vertice, current_owner);
            if (temp_owner != current_owner) {
                m_edge_count->setAt(current_owner, current_edge_count);
                current_owner = temp_owner;
                current_edge_count = 0;
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

    return Neighbours(m_edges, n_start, size);
}

dtkDistributedGraph::const_iterator dtkDistributedGraph::cbegin(void) const
{
    return const_iterator(this, this->m_mapper->startIndex(this->wid())); 
}

dtkDistributedGraph::const_iterator dtkDistributedGraph::cend(void) const 
{ 
    return const_iterator(this, this->m_mapper->lastIndex(this->wid()) + 1); 
}

dtkDistributedGraph::const_iterator dtkDistributedGraph::begin(void) const 
{ 
    return const_iterator(this, this->m_mapper->startIndex(this->wid())); 
}

dtkDistributedGraph::const_iterator dtkDistributedGraph::end(void) const 
{
    return const_iterator(this, this->m_mapper->lastIndex(this->wid()) + 1); 
}

//
// dtkDistributedGraph.tpp ends here

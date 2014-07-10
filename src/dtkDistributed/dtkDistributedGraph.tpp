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

inline dtkDistributedGraph::dtkDistributedGraph(const qlonglong& vertex_count, dtkDistributedWorker *worker) : dtkDistributedContainer(vertex_count, worker), m_vertex_count(vertex_count), neighbour_cache(0)
{
    if (vertex_count > 0)
        this->initialize();
}

inline dtkDistributedGraph::~dtkDistributedGraph(void)
{
    // if (neighbour_cache)
    //     delete[] neighbour_cache;

    //delete m_edge_count;
    //delete m_edges;
}

inline bool dtkDistributedGraph::empty(void) const 
{ 
    return !m_vertex_count; 
}

inline qlonglong dtkDistributedGraph::vertexCount(void) const
{
    return m_vertex_count;
}

inline qlonglong dtkDistributedGraph::edgeCount(void) const
{
    return m_edge_count->at(this->wid());
}

inline void dtkDistributedGraph::initialize(void)
{
    qDebug() << "initialize graph with " << m_vertex_count << "vertexes";
    m_size = m_vertex_count;
    m_vertices = new dtkDistributedArray<qlonglong>(m_vertex_count + 1, this->worker());
    m_mapper->setMapping(m_vertex_count, m_comm->size());
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

    const_iterator it  = this->cbegin();
    const_iterator end = this->cend();

    offset = mapper->startIndex(this->wid());
    qlonglong index = 0;
    for (; it != end; ++it) {
        m_vertices->setAt(it.key(), offset);
        offset += (*it).count();
        const_edge_iterator nit  = this->beginEdges(it.key());
        const_edge_iterator nend = this->endEdges(it.key());
        for(;nit != nend; ++nit) {
            m_edges->setLocalValue(index, *nit);
            ++index;
        }
    }
    if (this->wid() == this->m_comm->size() - 1)
        m_vertices->setAt(m_vertices->size() - 1, offset);

    this->m_comm->barrier();
}


// read graph from file as described in
// http://people.sc.fsu.edu/~jburkardt/data/metis_graph/metis_graph.html

inline bool dtkDistributedGraph::read(const QString& filename)
{
    QFile file(filename);
    QTextStream in(&file);
    qlonglong edges_count = 0;

    if (this->wid() == 0) {


        if(filename.isEmpty() || (!file.exists())) {
            qWarning() << "input file is empty/does not exist" << filename << "Current dir is" << QDir::currentPath();
            return false;
        }
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

        QStringList header = in.readLine().split(' ');
        m_vertex_count = header.first().toLongLong();
        if (m_vertex_count  == 0) {
            qWarning() << "Can't parse size of the graph" << filename;
            return false;
        }
        edges_count = header.at(1).toLongLong();
        if (edges_count  == 0) {
            qWarning() << "Can't parse the number of edges" << filename;
            return false;
        }

        qWarning() << "will initialize graph with" << m_vertex_count << edges_count;

    }
    m_comm->broadcast(&m_vertex_count, 1, 0);
    m_comm->broadcast(&edges_count, 1, 0);

    this->initialize();
    m_comm->barrier();

    m_edges = new dtkDistributedArray<qlonglong>(2 * edges_count, this->worker());


    if (this->wid() == 0) {

        qlonglong index              = 0;
        qlonglong current_edge_count = 0;
        qlonglong current_owner      = 0;
        qlonglong current_vertice    = 0;

        QString line;
        QStringList edges;

        while (!in.atEnd()) {
            line = in.readLine().trimmed();
            edges = line.split(' ');
            for (qlonglong i = 0; i < edges.size(); ++i) {
                m_edges->setAt(index, edges.at(i).toLongLong() -1);
                ++index;
                ++current_edge_count;
            }
            ++current_vertice;

            if (m_vertices->mapper()->owner(current_vertice) != current_owner) {
                m_edge_count->setAt(current_owner, current_edge_count);
                current_owner = m_vertices->mapper()->owner(current_vertice);
                current_edge_count = 0;
            }
        }
    }

    m_comm->barrier();

    return true;
}

inline void dtkDistributedGraph::appendEdge(qlonglong from, qlonglong to)
{
    qint32 from_owner = static_cast<qint32>(m_mapper->owner(from));
    qint32 to_owner = static_cast<qint32>(m_mapper->owner(to));
    qint32 wid = this->wid();
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
    return m_edges->size();
    // return const_cast<EdgeMap&>(m_map)[vertex_id].count();
}

inline const dtkDistributedGraph::EdgeList& dtkDistributedGraph::edges(qlonglong vertex_id) const
{    
    return const_cast<EdgeMap&>(m_map)[vertex_id];
}

inline dtkDistributedGraph::const_iterator dtkDistributedGraph::cbegin(void) const
{
    return m_map.cbegin();
}

inline dtkDistributedGraph::const_iterator dtkDistributedGraph::cend(void) const
{
    return m_map.cend();
}

inline dtkDistributedGraph::const_iterator dtkDistributedGraph::begin(void) const
{
    return m_map.begin();
}

inline dtkDistributedGraph::const_iterator dtkDistributedGraph::end(void) const
{
    return m_map.end();
}

inline dtkDistributedGraph::iterator dtkDistributedGraph::begin(void)
{
    return (m_vertices->begin());
}

inline dtkDistributedGraph::iterator dtkDistributedGraph::end(void)
{
    return (m_vertices->end());
}

inline dtkDistributedGraph::const_edge_iterator dtkDistributedGraph::cbeginEdges(qlonglong vertex_id) const
{
    return const_cast<EdgeMap&>(m_map)[vertex_id].cbegin();
}

inline dtkDistributedGraph::const_edge_iterator dtkDistributedGraph::cendEdges(qlonglong vertex_id) const
{
    return const_cast<EdgeMap&>(m_map)[vertex_id].cend(); 
}

inline dtkDistributedGraph::const_edge_iterator dtkDistributedGraph::beginEdges(qlonglong vertex_id) const
{
    return const_cast<EdgeMap&>(m_map)[vertex_id].cbegin();
}

inline dtkDistributedGraph::const_edge_iterator dtkDistributedGraph::endEdges(qlonglong vertex_id) const
{
    return const_cast<EdgeMap&>(m_map)[vertex_id].cend(); 
}

inline dtkDistributedGraph::edge_iterator dtkDistributedGraph::beginEdges(qlonglong vertex_id)
{
    return m_map[vertex_id].begin();
}

inline dtkDistributedGraph::edge_iterator dtkDistributedGraph::endEdges(qlonglong vertex_id)
{
    return m_map[vertex_id].end();
}

inline void dtkDistributedGraph::edgeIterators(qlonglong vertex_id, edge_iterator& begin, edge_iterator& end)
{
    qlonglong pos  = m_vertices->at(vertex_id);
    qlonglong size = m_vertices->at(vertex_id + 1) - pos;

    qint32 owner  = static_cast<qint32>(m_mapper->owner(vertex_id));
    pos -= m_edges->mapper()->startIndex(owner);

    if (this->wid() == owner) {
        begin = &((m_edges->begin())[pos]);

    } else {
        //if (neighbour_cache)
            //delete[] neighbour_cache;
        neighbour_cache = new qlonglong[size];
        begin = neighbour_cache;
        for (int i = 0; i < size; ++i) {
            m_comm->get(owner, pos++, &(neighbour_cache[i]), m_edges->dataId());
        }
    }
    end = begin + size;
}


inline dtkDistributedGraph::Neighbours dtkDistributedGraph::neighbours(const qlonglong& vertex_id)
{
    qlonglong n_start = m_vertices->at(vertex_id);
    qlonglong size = m_vertices->at(vertex_id + 1) - n_start;

    return Neighbours(m_edges, n_start, size);    
}

//
// dtkDistributedGraph.tpp ends here

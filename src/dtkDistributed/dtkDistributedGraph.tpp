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

inline dtkDistributedGraph::dtkDistributedGraph(const qlonglong& vertex_count, dtkDistributedWorker *worker) : dtkDistributedContainer(worker), m_vertex_count(vertex_count), m_vertices(vertex_count + 1, worker), neighbour_cache(0)
{
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
    return m_edge_count->atGlobal(this->wid());
}

inline void dtkDistributedGraph::initialize(void)
{
    m_mapper->setMapping(m_vertex_count, m_comm->size());
    m_edge_count = new dtkDistributedArray<qlonglong>(m_comm->size(), this->worker());
}

inline void dtkDistributedGraph::build(void)
{
    qlonglong edge_count = 0;
    for (qlonglong i = 0; i < m_comm->size(); ++i) {
        edge_count += m_edge_count->m_global_handler.at(i);
    }
    
    dtkDistributedMapper *mapper = new dtkDistributedMapper;
    mapper->initMap(edge_count, m_comm->size());

    qlonglong offset = 0;
    for (qlonglong i = 0; i < m_comm->size(); ++i) {
        mapper->setMap(offset ,i);
        offset += m_edge_count->m_global_handler.at(i);
    }

    m_edges = new dtkDistributedArray<qlonglong>(edge_count, this->worker(), mapper);

    const_iterator it  = this->cbegin();
    const_iterator end = this->cend();

    offset = mapper->startIndex(this->wid());
    qlonglong index = 0;
    for (; it != end; ++it) {
        m_vertices.m_global_handler.setAt(it.key(), offset);
        offset += (*it).count();
        const_edge_iterator nit  = this->beginEdges(it.key());
        const_edge_iterator nend = this->endEdges(it.key());
        for(;nit != nend; ++nit) {
            m_edges->m_local_handler.setAt(index, *nit);
            ++index;
        }
    }
    if (this->wid() == this->m_comm->size() - 1)
        m_vertices.m_global_handler.setAt(m_vertices.m_global_handler.count() - 1, offset);
}

inline void dtkDistributedGraph::appendEdge(qlonglong from, qlonglong to)
{
    qlonglong edge_counter = m_edge_count->atGlobal(this->wid());
    qint32 owner = static_cast<qint32>(m_mapper->owner(from));
    if (this->wid() == owner) {
        m_map[from].append(to);
        ++edge_counter;
    }
    owner = static_cast<qint32>(m_mapper->owner(to));
    if (this->wid() == owner) {
        m_map[to].append(from);
        ++edge_counter;
    }
    m_edge_count->setAtGlobal(this->wid(), edge_counter);
}

inline qlonglong dtkDistributedGraph::edgeCount(qlonglong vertex_id) const
{
    return const_cast<EdgeMap&>(m_map)[vertex_id].count();
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
    //return m_map.begin();
    return m_vertices.buffer;
}

inline dtkDistributedGraph::iterator dtkDistributedGraph::end(void)
{
    //return m_map.end();
    return m_vertices.buffer + m_vertices.m_local_handler.count();
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
    qlonglong pos  = m_vertices.m_global_handler.at(vertex_id);
    qlonglong size = m_vertices.m_global_handler.at(vertex_id + 1) - pos;

    qint32 owner  = static_cast<qint32>(m_mapper->owner(vertex_id));
    pos -= m_edges->mapper()->startIndex(owner);

    if (this->wid() == owner) {
        begin = m_edges->buffer + pos;
    
    } else {
        //if (neighbour_cache)
            //delete[] neighbour_cache;
        neighbour_cache = new qlonglong[size];
        begin = neighbour_cache;
        for (int i = 0; i < size; ++i)
            m_comm->get(owner, pos++, &(neighbour_cache[i]), m_edges->bufferId());
    }
    end = begin + size;
}

// 
// dtkDistributedGraph.tpp ends here

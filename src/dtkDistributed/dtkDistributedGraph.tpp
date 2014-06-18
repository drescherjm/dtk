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

inline dtkDistributedGraph::dtkDistributedGraph(const qlonglong& vertex_count, dtkDistributedWorker *worker) : dtkDistributedContainer(worker), m_vertex_count(vertex_count) 
{
    this->initialize();
}

inline dtkDistributedGraph::~dtkDistributedGraph(void)
{

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
    return m_edge_count; 
}

inline void dtkDistributedGraph::initialize(void)
{
    m_mapper->setMapping(m_vertex_count, m_comm->size());
}

inline void dtkDistributedGraph::appendEdge(qlonglong from, qlonglong to) 
{ 
    qint32 owner = static_cast<qint32>(m_mapper->owner(from));
    if (this->wid() == owner) {
        m_map[from].append(to); 
    }
    owner = static_cast<qint32>(m_mapper->owner(to));
    if (this->wid() == owner) {
        m_map[to].append(from);
    }
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
    return m_map.begin(); 
}

inline dtkDistributedGraph::iterator dtkDistributedGraph::end(void)
{
    return m_map.end();
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

// 
// dtkDistributedGraph.tpp ends here

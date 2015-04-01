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

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraphTopologyVertex inline methods
// /////////////////////////////////////////////////////////////////

inline void dtkDistributedGraphTopologyVertex::init(void) 
{ 
    qlonglong l_id = g->m_neighbour_count->mapper()->globalToLocal(m_id, g->wid());
    c_it = g->m_neighbour_count->cbegin();
    c_it += l_id;
    v_it = g->m_vertex_to_edge->cbegin();
    v_it += l_id;
    l_id = g->m_edge_to_vertex->mapper()->globalToLocal(*v_it, g->wid());
    n_it = g->m_edge_to_vertex->cbegin();
    n_it += l_id;
    first_pos = g->m_edge_to_vertex->mapper()->firstIndex(g->wid());
}

inline void dtkDistributedGraphTopologyVertex::advance(void)
{
    Q_ASSERT(c_it < g->m_neighbour_count->end());
    n_it += *c_it;
    ++c_it;
    ++v_it;
}
        
inline void dtkDistributedGraphTopologyVertex::advance(qlonglong j)
{ 
    Q_ASSERT(c_it + j <= g->m_neighbour_count->end());
    for(qlonglong i = 0; i < j; ++i) {
        n_it += *c_it;
        ++c_it;
        ++v_it;
    }            
}

inline void dtkDistributedGraphTopologyVertex::rewind(void)
{
    Q_ASSERT(c_it > g->m_neighbour_count->begin());
    --v_it;
    --c_it;
    n_it -= *c_it;
}
        
inline void dtkDistributedGraphTopologyVertex::rewind(qlonglong j)
{ 
    Q_ASSERT(c_it - j >= g->m_neighbour_count->begin());
    for(qlonglong i = j; i >= 0; --i) {
        --v_it;
        --c_it;
        n_it -= *c_it;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraphTopology inline methods
// /////////////////////////////////////////////////////////////////

inline void dtkDistributedGraphTopology::rlock(void)
{
    m_neighbour_count->rlock();
    m_vertex_to_edge->rlock();
    m_edge_to_vertex->rlock();
}

inline void dtkDistributedGraphTopology::wlock(void)
{
    m_neighbour_count->wlock();
    m_vertex_to_edge->wlock();
    m_edge_to_vertex->wlock();
}

inline void dtkDistributedGraphTopology::unlock(void)
{
    m_neighbour_count->unlock();
    m_vertex_to_edge->unlock();
    m_edge_to_vertex->unlock();
}

inline qlonglong dtkDistributedGraphTopology::vertexCount(void) const
{
    return this->size();
}

inline qlonglong dtkDistributedGraphTopology::edgeCount(void) const
{
    if (!m_edge_count)
        return 0;

    qlonglong size = m_edge_count->size();
    qlonglong count = 0;
    for (qlonglong i = 0; i < size; ++i)
        count += m_edge_count->at(i);

    return count;
}

inline qlonglong dtkDistributedGraphTopology::vertexCount(const qlonglong& wid) const
{
    if (!m_vertex_to_edge)
        return 0;

    return m_vertex_to_edge->mapper()->count(wid);
}

inline qlonglong dtkDistributedGraphTopology::edgeCount(const qlonglong& wid) const
{
    if (!m_edge_count)
        return 0;

    return m_edge_count->at(wid);
}

inline qlonglong dtkDistributedGraphTopology::neighbourCount(qlonglong vertex_id) const
{
    // qlonglong start = m_vertex_to_edge->at(vertex_id);
    // return (m_vertex_to_edge->at(vertex_id + 1) - start);
    return m_neighbour_count->at(vertex_id);
}

inline dtkDistributedGraphTopology::Neighbours dtkDistributedGraphTopology::operator[](qlonglong vertex_id) const
{
    qlonglong n_start = m_vertex_to_edge->at(vertex_id);
    // qlonglong size = m_vertex_to_edge->at(vertex_id + 1) - n_start;
    qlonglong size = m_neighbour_count->at(vertex_id);

    return Neighbours(*m_edge_to_vertex, n_start, size);
}

inline dtkDistributedGraphTopology::iterator dtkDistributedGraphTopology::cbegin(void) const
{
    return iterator(*this, this->m_mapper->firstIndex(this->wid()));
}

inline dtkDistributedGraphTopology::iterator dtkDistributedGraphTopology::cend(void) const 
{ 
    return iterator(*this, this->m_mapper->lastIndex(this->wid()) + 1); 
}

inline dtkDistributedGraphTopology::iterator dtkDistributedGraphTopology::begin(void) const 
{ 
    return iterator(*this, this->m_mapper->firstIndex(this->wid())); 
}

inline dtkDistributedGraphTopology::iterator dtkDistributedGraphTopology::end(void) const 
{
    return iterator(*this, this->m_mapper->lastIndex(this->wid()) + 1); 
}

inline void dtkDistributedGraphTopology::stats(void) const
{
    qDebug() << "m_vertex_to_edge stats:"; m_vertex_to_edge->stats();
    qDebug() << "m_edge_to_vertex stats:"; m_edge_to_vertex->stats();
}

// 
// dtkDistributedGraphTopology.tpp ends here

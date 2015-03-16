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
// dtkDistributedGraphTopology inline methods
// /////////////////////////////////////////////////////////////////

inline void dtkDistributedGraphTopology::rlock(void)
{
    m_vertex_to_edge->rlock();
    m_edge_to_vertex->rlock();
}

inline void dtkDistributedGraphTopology::wlock(void)
{
    m_vertex_to_edge->wlock();
    m_edge_to_vertex->wlock();
}

inline void dtkDistributedGraphTopology::unlock(void)
{
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
    qlonglong start = m_vertex_to_edge->at(vertex_id);
    return (m_vertex_to_edge->at(vertex_id + 1) - start);
}

inline dtkDistributedGraphTopology::Neighbours dtkDistributedGraphTopology::operator[](qlonglong vertex_id) const
{
    qlonglong n_start = m_vertex_to_edge->at(vertex_id);
    qlonglong size = m_vertex_to_edge->at(vertex_id + 1) - n_start;

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

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

#pragma once

#include "dtkDistributedContainer.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraph
// /////////////////////////////////////////////////////////////////

class dtkDistributedGraph : public dtkDistributedContainer
{
public:
     dtkDistributedGraph(const qlonglong& vertex_count, dtkDistributedWorker *worker);
    ~dtkDistributedGraph(void) {}

private:
    void initialize(void);

public:
    bool empty(void) const { return !m_vertex_count; }

    qlonglong vertexCount(void) const { return m_vertex_count; }
    qlonglong   edgeCount(void) const { return m_edge_count; }
    
    void appendEdge(qlonglong from, qlonglong to);

    qlonglong neighbourCount(qlonglong vertex_id) const;

    const QVarLengthArray<qlonglong, 32>& neighbours(qlonglong vertex_id) const;

public:
    typedef QMap<qlonglong, QVarLengthArray<qlonglong, 32> >::const_iterator const_iterator;
    typedef QMap<qlonglong, QVarLengthArray<qlonglong, 32> >::iterator             iterator;

    typedef QVarLengthArray<qlonglong, 32>::const_iterator const_neighbour_iterator;
    typedef QVarLengthArray<qlonglong, 32>::iterator             neighbour_iterator;

    typedef QMap<qlonglong, QVarLengthArray<qlonglong, 32> > Map;

    const_iterator cbegin(void) const { return m_map.cbegin(); }
    const_iterator   cend(void) const { return m_map.cend(); }

    const_neighbour_iterator cbeginNeighbours(qlonglong vertex_id) const { return const_cast<Map&>(m_map)[vertex_id].cbegin(); }
    const_neighbour_iterator   cendNeighbours(qlonglong vertex_id) const { return const_cast<Map&>(m_map)[vertex_id].cend(); }

public:
    qlonglong m_vertex_count;
    qlonglong m_edge_count;

    Map m_map;
};

// /////////////////////////////////////////////////////////////////

inline dtkDistributedGraph::dtkDistributedGraph(const qlonglong& vertex_count, dtkDistributedWorker *worker) : dtkDistributedContainer(worker), m_vertex_count(vertex_count) 
{
    this->initialize();
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

inline qlonglong dtkDistributedGraph::neighbourCount(qlonglong vertex_id) const
{    
    return const_cast<QMap<qlonglong, QVarLengthArray<qlonglong, 32> >& >(m_map)[vertex_id].count();
}

inline const QVarLengthArray<qlonglong, 32>&  dtkDistributedGraph::neighbours(qlonglong vertex_id) const
{    
    return const_cast<QMap<qlonglong, QVarLengthArray<qlonglong, 32> >& >(m_map)[vertex_id];
}



// dtkDistributedGraph.h ends here

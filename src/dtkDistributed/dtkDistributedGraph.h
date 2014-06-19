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
#include "dtkDistributedArray.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraph declaration
// /////////////////////////////////////////////////////////////////

class dtkDistributedGraph : public dtkDistributedContainer
{
public:
    typedef QVarLengthArray<qlonglong, 32> EdgeList;
    typedef QMap<qlonglong, EdgeList>      EdgeMap;

public:
      dtkDistributedGraph(const qlonglong& vertex_count, dtkDistributedWorker *worker);
     ~dtkDistributedGraph(void);

private:
    void initialize(void);

public:
    void build(void);

public:
    bool empty(void) const;

    qlonglong vertexCount(void) const;
    qlonglong   edgeCount(void) const;
    
    void appendEdge(qlonglong from, qlonglong to);

    qlonglong edgeCount(qlonglong vertex_id) const;

    const EdgeList& edges(qlonglong vertex_id) const;

public:
    typedef EdgeMap::const_iterator const_iterator;
    //typedef EdgeMap::iterator             iterator;
    typedef qlonglong* iterator;

    typedef EdgeList::const_iterator const_edge_iterator;
    //typedef EdgeList::iterator             edge_iterator;
    typedef qlonglong* edge_iterator;

    const_iterator cbegin(void) const;
    const_iterator   cend(void) const;

    const_iterator begin(void) const;
    const_iterator   end(void) const;

    iterator begin(void);
    iterator   end(void);

    const_edge_iterator cbeginEdges(qlonglong vertex_id) const;
    const_edge_iterator   cendEdges(qlonglong vertex_id) const;

    const_edge_iterator beginEdges(qlonglong vertex_id) const;
    const_edge_iterator   endEdges(qlonglong vertex_id) const;

    edge_iterator beginEdges(qlonglong vertex_id);
    edge_iterator   endEdges(qlonglong vertex_id);

    void edgeIterators(qlonglong vertex_id, edge_iterator& begin, edge_iterator& end);

public:
    qlonglong *neighbour_cache;

    qlonglong m_vertex_count;

    EdgeMap m_map;

    dtkDistributedArray<qlonglong> *m_edge_count;
    dtkDistributedArray<qlonglong>  m_vertices;
    dtkDistributedArray<qlonglong> *m_edges;
};

// /////////////////////////////////////////////////////////////////

#include "dtkDistributedGraph.tpp"

// dtkDistributedGraph.h ends here

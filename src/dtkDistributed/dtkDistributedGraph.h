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
#include "dtkDistributedArrayNavigator.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraph declaration
// /////////////////////////////////////////////////////////////////

class dtkDistributedGraph : public dtkDistributedContainer
{
public:
    typedef QVarLengthArray<qlonglong, 32> EdgeList;
    typedef QMap<qlonglong, EdgeList>      EdgeMap;

public:
      dtkDistributedGraph(dtkDistributedWorker *worker);
      dtkDistributedGraph(const qlonglong& vertex_count, dtkDistributedWorker *worker);
     ~dtkDistributedGraph(void);

private:
    void initialize(void);

public:
    void build(void);

public:
    bool read(const QString& filename);

public:
    qlonglong vertexCount(void) const;
    qlonglong   edgeCount(void) const;
    
    void appendEdge(qlonglong from, qlonglong to);

    qlonglong edgeCount(qlonglong vertex_id) const;

public:
    typedef dtkDistributedArrayNavigator<qlonglong> Neighbours;

    Neighbours neighbours(const qlonglong& vertex_id) const;

public:
    class const_iterator
    {
        const dtkDistributedGraph *g;
        qlonglong g_id;

    public:
        const_iterator(void) : g(0), g_id(0)  {}
        const_iterator(const dtkDistributedGraph *graph, const qlonglong& gid) : g(graph), g_id(gid) {}

    public:
        qlonglong id(void) { return g_id; }

    public:
        Neighbours operator *  (void) const { return g->neighbours(g_id); }
        Neighbours operator [] (qlonglong j) const { return *(*this + j); }
        bool operator == (const const_iterator &o) const { return g_id == o.g_id; }
        bool operator != (const const_iterator &o) const { return g_id != o.g_id; }
        bool operator <  (const const_iterator &o) const { return g_id  < o.g_id; }
        bool operator >  (const const_iterator &o) const { return g_id  > o.g_id; }
        bool operator <= (const const_iterator &o) const { return g_id <= o.g_id; }
        bool operator >= (const const_iterator &o) const { return g_id >= o.g_id; }
        const_iterator& operator ++ (void) { ++g_id; return *this; }
        const_iterator  operator ++ (int)  { const_iterator it(*this); ++g_id; return it; }
        const_iterator& operator -- (void) { --g_id; return *this; }
        const_iterator  operator -- (int)  { const_iterator it(*this); --g_id; return it; }
        const_iterator& operator += (qlonglong j) { g_id += j; return *this; }
        const_iterator& operator -= (qlonglong j) { g_id -= j; return *this; }
        const_iterator  operator +  (qlonglong j) const { return const_iterator(*this + j); }
        const_iterator  operator -  (qlonglong j) const { return const_iterator(*this - j); }
        qlonglong operator -  (const const_iterator& o) const { return g_id - o.g_id; }
    };
    friend class const_iterator;

public:
    const_iterator cbegin(void) const { return const_iterator(this, this->m_mapper->startIndex(this->wid())); }
    const_iterator   cend(void) const { return const_iterator(this, this->m_mapper->lastIndex(this->wid())); }

    const_iterator begin(void) const { return const_iterator(this, this->m_mapper->startIndex(this->wid())); }
    const_iterator   end(void) const { return const_iterator(this, this->m_mapper->lastIndex(this->wid())); }

public:
    dtkDistributedArray<qlonglong> *m_edge_count;
    EdgeMap m_map;

    dtkDistributedArray<qlonglong> *m_vertices;
    dtkDistributedArray<qlonglong> *m_edges;
};

// /////////////////////////////////////////////////////////////////

#include "dtkDistributedGraph.tpp"

// dtkDistributedGraph.h ends here

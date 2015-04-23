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

#include "dtkDistributedArray.h"
#include "dtkDistributedNavigator.h"
#include "dtkDistributedContainer.h"
#include "dtkDistributedIterator.h"

#include "dtkDistributedExport.h"

#include <QtCore>

class dtkDistributedGraphTopology;

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraphTopologyVertex declaration
// /////////////////////////////////////////////////////////////////

class DTKDISTRIBUTED_EXPORT dtkDistributedGraphTopologyVertex
{    
    const dtkDistributedGraphTopology *g;
    qlonglong m_id;
    dtkDistributedArray<qlonglong>::const_iterator c_it;
    dtkDistributedArray<qlonglong>::const_iterator v_it;
    dtkDistributedArray<qlonglong>::const_iterator n_it;
    qlonglong first_pos;

public:
    dtkDistributedGraphTopologyVertex(const dtkDistributedGraphTopology *graph, qlonglong id) : g(graph), m_id(id) { init(); }
    dtkDistributedGraphTopologyVertex(const dtkDistributedGraphTopologyVertex& o) : g(o.g), m_id(o.m_id) { init(); }

public:
    dtkDistributedGraphTopologyVertex& operator = (const dtkDistributedGraphTopologyVertex& o) { m_id = o.m_id; init(); return *this; }

public:
    qlonglong id(void) const { return m_id; }

public:
    qlonglong neighbourCount(void) const { return *c_it; }
    qlonglong neighbourPos(qlonglong j) const { return *v_it + j; }
    qlonglong neighbourLocalPos(qlonglong j) const { return *v_it + j - first_pos; }

public:
    dtkDistributedArray<qlonglong>::const_iterator begin(void) const { return n_it; }
    dtkDistributedArray<qlonglong>::const_iterator   end(void) const { return n_it + *c_it; }

public:
    bool operator == (const dtkDistributedGraphTopologyVertex& o) const { return (m_id == o.m_id); }
    bool operator != (const dtkDistributedGraphTopologyVertex& o) const { return (m_id != o.m_id); }
    bool operator <  (const dtkDistributedGraphTopologyVertex& o) const { return (m_id <  o.m_id); }
    bool operator <= (const dtkDistributedGraphTopologyVertex& o) const { return (m_id <= o.m_id); }
    bool operator >  (const dtkDistributedGraphTopologyVertex& o) const { return (m_id >  o.m_id); }
    bool operator >= (const dtkDistributedGraphTopologyVertex& o) const { return (m_id >= o.m_id); }
        
public:
    dtkDistributedGraphTopologyVertex& operator ++ (void) { ++m_id; advance(); return *this; }
    dtkDistributedGraphTopologyVertex  operator ++ (int)  { dtkDistributedGraphTopologyVertex o(*this); ++m_id; advance(); return o; }
    dtkDistributedGraphTopologyVertex& operator -- (void) { --m_id; rewind(); return *this; }
    dtkDistributedGraphTopologyVertex  operator -- (int)  { dtkDistributedGraphTopologyVertex o(*this); --m_id; rewind(); return o; }
    dtkDistributedGraphTopologyVertex& operator += (qlonglong j) { m_id += j; advance(j); return *this; }
    dtkDistributedGraphTopologyVertex& operator -= (qlonglong j) { m_id -= j; rewind(j); return *this; }
    dtkDistributedGraphTopologyVertex  operator +  (qlonglong j) const { dtkDistributedGraphTopologyVertex o(*this); o += j; return o; }
    dtkDistributedGraphTopologyVertex  operator -  (qlonglong j) const { dtkDistributedGraphTopologyVertex o(*this); o -= j; return o; }

private:
    void init(void);
    void advance(void);
    void advance(qlonglong j);
    void rewind(void);
    void rewind(qlonglong j);
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraphTopology declaration
// /////////////////////////////////////////////////////////////////

class DTKDISTRIBUTED_EXPORT dtkDistributedGraphTopology : public dtkDistributedContainer
{

public:
    enum GraphFile {
        MetisFormat,
        MatrixMarketFormat
    };

public:
    typedef dtkDistributedNavigator<dtkDistributedArray<qlonglong> > Neighbours;
    typedef dtkDistributedIterator<dtkDistributedGraphTopology> iterator;
    typedef dtkDistributedGraphTopologyVertex vertex;
    friend vertex;

public:
    typedef Neighbours value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef qptrdiff difference_type;
    typedef qlonglong size_type;

public:
    dtkDistributedGraphTopology(void);
    dtkDistributedGraphTopology(const qlonglong& vertex_count);
    dtkDistributedGraphTopology(const qlonglong& vertex_count, dtkDistributedMapper *mapper);
    dtkDistributedGraphTopology(const dtkDistributedGraphTopology& other);

public:
    ~dtkDistributedGraphTopology(void);

public:
    dtkDistributedGraphTopology& operator = (const dtkDistributedGraphTopology& o);

private:
    void initialize(bool has_custom_mapper = false);

public:
    void  rlock(void);
    void  wlock(void);
    void unlock(void);

public:
    void addEdge(qlonglong from, qlonglong to, bool oriented = false);

public:
    void build(void);
    void resize(qlonglong vertexCount);

public:
    qlonglong vertexCount(void) const;
    qlonglong   edgeCount(void) const;

public:
    qlonglong vertexCount(const qlonglong& wid) const;
    qlonglong   edgeCount(const qlonglong& wid) const;

public:
    qlonglong neighbourCount(qlonglong vertex_id) const;

    Neighbours operator[](qlonglong vertex_id) const;

    vertex beginVertex() const { return vertex(this, this->m_mapper->firstIndex(this->wid())); }
    vertex   endVertex() const { return vertex(this, this->m_mapper->lastIndex(this->wid())); }

public:
    dtkDistributedMapper *edge_mapper(void) const;

public:
    iterator cbegin(void) const;
    iterator   cend(void) const;

    iterator begin(void) const;
    iterator   end(void) const;

public:
    void stats(void) const;

public:
    bool read(const QString& filename, GraphFile format = MetisFormat);

    template <class T = double> bool readWithValues(const QString& filename, GraphFile format, dtkDistributedArray<T> *&values );

protected:
    typedef QList<qlonglong> EdgeList;
    typedef QMap<qlonglong, EdgeList> EdgeMap;

    dtkDistributedArray<qlonglong> *m_edge_count;
    EdgeMap m_map;

    dtkDistributedArray<qlonglong> *m_neighbour_count;
    dtkDistributedArray<qlonglong> *m_vertex_to_edge;
    dtkDistributedArray<qlonglong> *m_edge_to_vertex;
};

// /////////////////////////////////////////////////////////////////

#include "dtkDistributedGraphTopology.tpp"

// 
// dtkDistributedGraphTopology.h ends here

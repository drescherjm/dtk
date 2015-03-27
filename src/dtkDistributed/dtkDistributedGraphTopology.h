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

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraphTopology declaration
// /////////////////////////////////////////////////////////////////

class DTKDISTRIBUTED_EXPORT dtkDistributedGraphTopology : public dtkDistributedContainer
{
public:
    typedef dtkDistributedNavigator<dtkDistributedArray<qlonglong> > Neighbours;
    typedef dtkDistributedIterator<dtkDistributedGraphTopology> iterator;

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

public:
    ~dtkDistributedGraphTopology(void);

private:
    void initialize(void);

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
    bool read(const QString& filename);

public:
    qlonglong vertexCount(void) const;
    qlonglong   edgeCount(void) const;

public:
    qlonglong vertexCount(const qlonglong& wid) const;
    qlonglong   edgeCount(const qlonglong& wid) const;

public:
    qlonglong neighbourCount(qlonglong vertex_id) const;

    Neighbours operator[](qlonglong vertex_id) const;

public:
    dtkDistributedMapper *edge_mapper(void) const;

public:
    iterator cbegin(void) const;
    iterator   cend(void) const;

    iterator begin(void) const;
    iterator   end(void) const;

public:
    void stats(void) const;

protected:
    typedef QList<qlonglong> EdgeList;
    typedef QMap<qlonglong, EdgeList> EdgeMap;

    dtkDistributedArray<qlonglong> *m_edge_count;
    EdgeMap m_map;

    dtkDistributedArray<qlonglong> *m_vertex_to_edge;
    dtkDistributedArray<qlonglong> *m_edge_to_vertex;
};

// /////////////////////////////////////////////////////////////////

#include "dtkDistributedGraphTopology.tpp"

// 
// dtkDistributedGraphTopology.h ends here

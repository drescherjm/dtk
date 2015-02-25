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
#include "dtkDistributedArrayNavigator.h"
#include "dtkDistributedContainer.h"
#include "dtkDistributedIterator.h"

#include "dtkDistributedExport.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraph declaration
// /////////////////////////////////////////////////////////////////

class DTKDISTRIBUTED_EXPORT dtkDistributedGraph : public dtkDistributedContainer
{
public:
      dtkDistributedGraph(void);
      dtkDistributedGraph(const qlonglong& vertex_count);
     ~dtkDistributedGraph(void);

private:
    void initialize(void);

public:
    void build(void);

public:
    bool read(const QString& filename);
    bool read2(const QString& filename);

public:
    qlonglong vertexCount(void) const;
    qlonglong   edgeCount(void) const;

    void appendEdge(qlonglong from, qlonglong to);

    qlonglong edgeCount(qlonglong vertex_id) const;

public:
    typedef dtkDistributedNavigator<dtkDistributedArray<qlonglong> > Neighbours;

public:
    typedef Neighbours value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef qptrdiff difference_type;
    typedef qlonglong size_type;

public:
    Neighbours neighbours(const qlonglong& vertex_id) const;

    Neighbours operator[](qlonglong vertex_id) const;

public:
    typedef dtkDistributedIterator<dtkDistributedGraph> const_iterator;

public:
    const_iterator cbegin(void) const;
    const_iterator   cend(void) const;

    const_iterator begin(void) const;
    const_iterator   end(void) const;

public:
    typedef QVarLengthArray<qlonglong, 32> EdgeList;
    typedef QMap<qlonglong, EdgeList>      EdgeMap;

    dtkDistributedArray<qlonglong> *m_edge_count;
    EdgeMap m_map;

    dtkDistributedArray<qlonglong> *m_vertices;
    dtkDistributedArray<qlonglong> *m_edges;
};

// /////////////////////////////////////////////////////////////////

#include "dtkDistributedGraph.tpp"

// dtkDistributedGraph.h ends here

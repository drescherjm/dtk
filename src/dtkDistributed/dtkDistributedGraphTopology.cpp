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

#include "dtkDistributedGraphTopology.h"

#if defined(DTK_HAVE_ZLIB)
#include <dtkCore/dtkIOCompressor>
#endif

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraphTopology implementation
// /////////////////////////////////////////////////////////////////

dtkDistributedGraphTopology::dtkDistributedGraphTopology(void) : dtkDistributedContainer()
{
    m_neighbour_count = NULL;
    m_edge_to_vertex  = NULL;
    m_vertex_to_edge  = NULL;
    m_edge_count = NULL;

    m_comm->barrier();
}

dtkDistributedGraphTopology::dtkDistributedGraphTopology(const qlonglong& vertex_count) : dtkDistributedContainer(vertex_count)
{
    m_neighbour_count = NULL;
    m_edge_to_vertex  = NULL;
    m_vertex_to_edge  = NULL;
    m_edge_count = NULL;

    this->initialize();

    m_comm->barrier();
}

dtkDistributedGraphTopology::dtkDistributedGraphTopology(const qlonglong& vertex_count, dtkDistributedMapper *mapper) : dtkDistributedContainer(vertex_count, mapper)
{
    m_neighbour_count = NULL;
    m_edge_to_vertex  = NULL;
    m_vertex_to_edge  = NULL;
    m_edge_count = NULL;

    this->initialize(true);

    m_comm->barrier();
}

dtkDistributedGraphTopology::dtkDistributedGraphTopology(const dtkDistributedGraphTopology& o) : dtkDistributedContainer(o.m_size)
{
    m_map = o.m_map;

    m_edge_count      = NULL;
    m_neighbour_count = NULL;
    m_vertex_to_edge  = NULL;

    if (o.m_edge_count)
        m_edge_count = new dtkDistributedArray<qlonglong>(*(o.m_edge_count));
    if (o.m_neighbour_count)
        m_neighbour_count = new dtkDistributedArray<qlonglong>(*(o.m_neighbour_count));
    if (o.m_vertex_to_edge)
        m_vertex_to_edge  = new dtkDistributedArray<qlonglong>(*(o.m_vertex_to_edge));

    m_mapper->setMapping(vertexCount(), m_comm->size());
}

dtkDistributedGraphTopology::~dtkDistributedGraphTopology(void)
{
    m_comm->barrier();

    if (m_neighbour_count)
        delete m_neighbour_count;
    if (m_vertex_to_edge)
        delete m_vertex_to_edge;
    if (m_edge_count)
        delete m_edge_count;
    if (m_edge_to_vertex)
        delete m_edge_to_vertex;
}

dtkDistributedGraphTopology& dtkDistributedGraphTopology::operator = (const dtkDistributedGraphTopology& o)
{
    m_map = o.m_map;
    
    if (o.m_edge_count)
        *m_edge_count = *(o.m_edge_count);
    if (o.m_neighbour_count)
        *m_neighbour_count = *(o.m_neighbour_count);
    if (o.m_vertex_to_edge)
        *m_vertex_to_edge  = *(o.m_vertex_to_edge);

    m_mapper->setMapping(vertexCount(), m_comm->size());

    return *this;
}

void dtkDistributedGraphTopology::resize(qlonglong vertex_count)
{
    m_size = vertex_count;
//    m_edge_to_vertex = new dtkDistributedArray<qlonglong>( edges_count);
    initialize();
}

dtkDistributedMapper *dtkDistributedGraphTopology::edge_mapper(void) const
{
    return m_edge_to_vertex->mapper();
}

void dtkDistributedGraphTopology::initialize(bool has_custom_mapper)
{
    dtkDebug() << "initialize graph with" << vertexCount() << "vertexes, rank =" << this->wid();

    if (!has_custom_mapper) {
        m_mapper->setMapping(vertexCount(), m_comm->size());
    }

    dtkDistributedMapper *mapper = new dtkDistributedMapper(*m_mapper);
    mapper->setMap(vertexCount() + 1, m_comm->size());
    m_vertex_to_edge = new dtkDistributedArray<qlonglong>(vertexCount() + 1, mapper);
    m_vertex_to_edge->fill(0);

    m_neighbour_count = new dtkDistributedArray<qlonglong>(vertexCount() + 1, mapper);
    m_neighbour_count->fill(0);

    m_edge_count = new dtkDistributedArray<qlonglong>(m_comm->size());
    m_edge_count->fill(0);
}

void dtkDistributedGraphTopology::build(void)
{
    this->m_comm->barrier();

    qlonglong edge_count = 0;
    for (qlonglong i = 0; i < m_comm->size(); ++i) {
        edge_count += m_edge_count->at(i);
    }

    dtkDistributedMapper *mapper = new dtkDistributedMapper;
    mapper->initMap(edge_count, m_comm->size());

    qlonglong offset = 0;
    for (qlonglong i = 0; i < m_comm->size(); ++i) {
        mapper->setMap(offset ,i);
        offset += m_edge_count->at(i);
    }

    if (m_edge_to_vertex) {
        delete m_edge_to_vertex;
    }
    m_edge_to_vertex = new dtkDistributedArray<qlonglong>(edge_count, mapper);

    EdgeMap::const_iterator it  = m_map.cbegin();
    EdgeMap::const_iterator end = m_map.cend();

    offset = mapper->firstIndex(this->wid());
    qlonglong index = 0;
    for (; it != end; ++it) {
        m_vertex_to_edge->setAt(it.key(), offset);
        const EdgeList& edge_list = *it;
        offset += edge_list.count();
        EdgeList::const_iterator nit  = edge_list.begin();
        EdgeList::const_iterator nend = edge_list.end();
        for(;nit != nend; ++nit, ++index) {
            m_edge_to_vertex->begin()[index] = *nit;
        }
        m_neighbour_count->setAt(it.key(), edge_list.count());
    }

    this->m_comm->barrier();
    if (this->wid() == this->m_comm->size() - 1) {
        m_vertex_to_edge->setAt(m_vertex_to_edge->size() - 1, offset);
    }

    this->m_comm->barrier();
}


void dtkDistributedGraphTopology::addEdge(qlonglong from, qlonglong to, bool oriented)
{
    qint32 wid = this->wid();
    qint32 from_owner = static_cast<qint32>(m_mapper->owner(from));

    if (wid == from_owner) {
        qlonglong edge_counter = m_edge_count->at(wid);

        EdgeList::iterator it  = m_map[from].begin();
        EdgeList::iterator end = m_map[from].end();

        if (it == end) {
            m_map[from].insert(it, to);
        } else if (to > m_map[from].last()) {
            // tuning: usually, we append at the end, so check this case
            m_map[from].insert(end, to);
        } else {
            for(; it != end; ++it) {
                if (to == (*it))
                    return;
                if (to < (*it))
                    break;
            }
            m_map[from].insert(it, to);
        }

        // m_map[from].append(to);
        ++edge_counter;
        m_edge_count->setAt(wid, edge_counter);
    }

    if (!oriented) {
        addEdge(to, from, true);
    }
}

// 
// dtkDistributedGraphTopology.cpp ends here


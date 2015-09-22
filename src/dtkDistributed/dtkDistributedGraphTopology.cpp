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

#include <dtkLog>
#include "dtkDistributedGraphTopology.h"

#if defined(DTK_HAVE_ZLIB)
#include <dtkCore/dtkIOCompressor>
#endif

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraphTopology implementation
// /////////////////////////////////////////////////////////////////

dtkDistributedGraphTopology::dtkDistributedGraphTopology(void) : dtkDistributedContainer()
{
    m_builded=false;
    m_neighbour_count = NULL;
    m_edge_to_vertex  = NULL;
    m_vertex_to_edge  = NULL;
    m_edge_count      = NULL;
    m_remote_edges_count = NULL;
    m_remote_edges       = NULL;

    m_comm->barrier();
}

dtkDistributedGraphTopology::dtkDistributedGraphTopology(const qlonglong& vertex_count) : dtkDistributedContainer(vertex_count)
{
    m_builded=false;
    m_neighbour_count = NULL;
    m_edge_to_vertex  = NULL;
    m_vertex_to_edge  = NULL;
    m_edge_count      = NULL;
    m_remote_edges_count = NULL;
    m_remote_edges       = NULL;

    this->initialize();

    m_comm->barrier();
}

dtkDistributedGraphTopology::dtkDistributedGraphTopology(const qlonglong& vertex_count, dtkDistributedMapper *mapper) : dtkDistributedContainer(vertex_count, mapper)
{
    m_builded=false;
    m_neighbour_count = NULL;
    m_edge_to_vertex  = NULL;
    m_vertex_to_edge  = NULL;
    m_edge_count = NULL;
    m_remote_edges_count = NULL;
    m_remote_edges       = NULL;

    this->initialize(true);

    m_comm->barrier();
}

dtkDistributedGraphTopology::dtkDistributedGraphTopology(const dtkDistributedGraphTopology& o) : dtkDistributedContainer(o.m_size)
{
    m_map = o.m_map;
    m_builded=o.m_builded;
    m_edge_count      = NULL;
    m_neighbour_count = NULL;
    m_vertex_to_edge  = NULL;
    m_remote_edges_count = NULL;
    m_remote_edges       = NULL;

    if (o.m_edge_count)
        m_edge_count = new dtkDistributedArray<qlonglong>(*(o.m_edge_count));
    if (o.m_neighbour_count)
        m_neighbour_count = new dtkDistributedArray<qlonglong>(*(o.m_neighbour_count));
    if (o.m_vertex_to_edge)
        m_vertex_to_edge  = new dtkDistributedArray<qlonglong>(*(o.m_vertex_to_edge));
    if (o.m_remote_edges)
        m_remote_edges  = new dtkDistributedArray<qlonglong>(*(o.m_remote_edges));
    if (o.m_remote_edges_count)
        m_remote_edges_count  = new dtkDistributedArray<qlonglong>(*(o.m_remote_edges_count));

    m_mapper->setMapping(vertexCount(), m_comm->size());
}

dtkDistributedGraphTopology::~dtkDistributedGraphTopology(void)
{
    if (!m_builded && m_edge_count)
        m_edge_count->unlock(this->wid());

    m_comm->barrier();

    if (m_neighbour_count)
        delete m_neighbour_count;
    if (m_vertex_to_edge)
        delete m_vertex_to_edge;
    if (m_edge_count)
        delete m_edge_count;
    if (m_edge_to_vertex)
        delete m_edge_to_vertex;
    if (m_remote_edges)
        delete m_remote_edges;
    if (m_remote_edges_count)
        delete m_remote_edges_count;
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
    if (o.m_remote_edges)
        *m_remote_edges  = *(o.m_remote_edges);
    if (o.m_remote_edges_count)
        *m_remote_edges_count  = *(o.m_remote_edges_count);

    m_mapper->setMapping(vertexCount(), m_comm->size());

    return *this;
}

void dtkDistributedGraphTopology::resize(qlonglong vertex_count)
{
    m_size = vertex_count;
//    m_edge_to_vertex = new dtkDistributedArray<qlonglong>( edges_count);
    initialize();
}

// if the graph is not builded, it will do a segfault
dtkDistributedMapper *dtkDistributedGraphTopology::edge_mapper(void) const
{
    if(!m_builded) {
        dtkError() << "calling edge_mapper while the dtkDistributedgraphTopology is not builded! ";
    }
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
    // If the graph is build with addEdge, m_edge_count is written
    // locally and the locks can be a bottleneck, so set a wlock here.
    // This will be unlocked after the build (or read )
    m_edge_count->wlock(this->wid());

    m_remote_edges_count = new dtkDistributedArray<qlonglong>(m_comm->size());
    m_remote_edges_count->fill(0);

}

void dtkDistributedGraphTopology::build(void)
{
    m_edge_count->unlock(this->wid());
    this->m_comm->barrier();
    m_builded = true;
    qlonglong wid = this->wid();

    // handle remote edges
    qlonglong remote_edge_count = 0;
    for (qlonglong i = 0; i < m_comm->size(); ++i) {
        remote_edge_count += 3 * m_remote_edges_count->at(i);
    }


    qlonglong offset = 0;

    if (remote_edge_count == 0) {
        dtkDebug() << "No remote edges in graph, build";
    } else  {
        dtkDebug() << "Add remotes edges ! " << remote_edge_count/3;
        dtkDistributedMapper *rmapper = new dtkDistributedMapper();
        // We don't know yet the final edge_count (see fake one later), use a size >= comm->size
        rmapper->initMap(remote_edge_count  + m_comm->size() , m_comm->size());
        for (qlonglong i = 0; i < m_comm->size(); ++i) {
            rmapper->setMap(offset , i);
            qlonglong count =  m_remote_edges_count->at(i);
            if (count == 0) {
                // need to add fake entry because empty local array is not supported
                offset += 3 ;
                remote_edge_count+= 3;
             } else {
                offset += 3 * count;
            }
        }
        rmapper->setMap(remote_edge_count , m_comm->size());

        m_remote_edges = new dtkDistributedArray<qlonglong>(remote_edge_count, rmapper);
        m_remote_edges->fill(-1);

        EdgeMap::const_iterator it  = m_map_remote.cbegin();
        EdgeMap::const_iterator end = m_map_remote.cend();

        qlonglong index = rmapper->firstIndex(wid);
        for (; it != end; ++it) {
            const EdgeList& edge_list = *it;
            EdgeList::const_iterator nit  = edge_list.begin();
            EdgeList::const_iterator nend = edge_list.end();
            for(;nit != nend; ++nit) {
                qlonglong owner = m_mapper->owner(it.key());
                m_remote_edges->setAt(index,   owner);
                m_remote_edges->setAt(index+1, it.key());
                m_remote_edges->setAt(index+2, *nit);
                index += 3;
            }
        }
        m_comm->barrier();
        // scan the whole remote_edges DSarray to find our edges added by other procs
        for (qlonglong i = 0 ; i < m_remote_edges->size(); i += 3){
            if  (m_remote_edges->at(i) == wid) {
                this->addEdge(m_remote_edges->at(i+1),m_remote_edges->at(i+2),true);
            }
        }
        m_comm->barrier();
        delete m_remote_edges;
        m_remote_edges = NULL;
    }

    // handle our edges
    qlonglong edge_count = 0;
    for (qlonglong i = 0; i < m_comm->size(); ++i) {
        edge_count += m_edge_count->at(i);
    }

    dtkDistributedMapper *mapper = new dtkDistributedMapper;
    mapper->initMap(edge_count, m_comm->size());

    offset = 0;
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

bool dtkDistributedGraphTopology::builded(void)
{
    return m_builded;
}

void dtkDistributedGraphTopology::addGlobalEdge(qlonglong from, qlonglong to)
{
    qint32 wid = this->wid();
    qint32 from_owner = static_cast<qint32>(m_mapper->owner(from));
    if (wid == from_owner) {
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
        m_edge_count->addAssign(wid, 1);
    } else {
        // we are now the owner, store this in a tmp array
        // global counter of remote edges
        m_remote_edges_count->addAssign(wid, 1);
        EdgeList::iterator it  = m_map_remote[from].begin();
        EdgeList::iterator end = m_map_remote[from].end();
        if (it == end) {
            m_map_remote[from].insert(it, to);
        } else if (to > m_map[from].last()) {
            // tuning: usually, we append at the end, so check this case
            m_map_remote[from].insert(end, to);
        } else {
            for(; it != end; ++it) {
                if (to == (*it))
                    return;
                if (to < (*it))
                    break;
            }
            m_map_remote[from].insert(it,to);
        }
    }
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
    else {
        dtkWarn() << "dtkDistributedGraphTopology try to addEdge(" << from << "," << to << ") with wid=" << wid << " but the owner is " << from_owner  << " . Nothing will be done !!!";
    }
    
    if (!oriented) {
        addEdge(to, from, true);
    }
}

// 
// dtkDistributedGraphTopology.cpp ends here


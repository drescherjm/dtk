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
// Helper function
// /////////////////////////////////////////////////////////////////

void dtkDistributedOrderingListInsertion(QList<qlonglong>& l, qlonglong id);
void dtkDistributedSortListUsingMap(const QList<qlonglong>& l, const QMap<qlonglong, qlonglong>& m, QList<qlonglong>& res);
bool dtkDistributedGraphTopologyPopulateMap(QMap<qlonglong, QList<qlonglong> >& map, qlonglong from, qlonglong to);

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
    m_positions          = NULL;

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
    m_positions          = NULL;

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
    m_positions          = NULL;

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
    m_positions          = NULL;

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
    if (m_positions)
        delete m_positions;
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

        EdgeMap::const_iterator it  = m_map_hybrid.cbegin();
        EdgeMap::const_iterator end = m_map_hybrid.cend();

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

        QMap<qlonglong, qlonglong> map_remote_owner;
        it  = m_map_remote.cbegin();
        end = m_map_remote.cend();
        for (; it != end; ++it) {
            const EdgeList& edge_list = *it;
            EdgeList::const_iterator nit  = edge_list.begin();
            EdgeList::const_iterator nend = edge_list.end();
            for(;nit != nend; ++nit) {
                qlonglong owner = m_mapper->owner(it.key());
                m_remote_edges->setAt(index,   owner);
                m_remote_edges->setAt(index+1, it.key());
                m_remote_edges->setAt(index+2, *nit);
                map_remote_owner.insert(index, it.key());
                index += 3;
            }
        }

        m_comm->barrier();

        // scan the whole remote_edges DSarray to find our edges added by other procs
        for (qlonglong i = 0 ; i < m_remote_edges->size(); i += 3){
            if  (m_remote_edges->at(i) == wid) {
                this->addEdge(m_remote_edges->at(i+1), m_remote_edges->at(i+2), true);
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

void dtkDistributedGraphTopology::addEdge(qlonglong from, qlonglong to, bool oriented)
{
    qint32 wid = this->wid();
    qint32 from_owner = static_cast<qint32>(m_mapper->owner(from));

    if (wid == from_owner) {
        if (dtkDistributedGraphTopologyPopulateMap(m_map, from, to)) {
            m_edge_count->addAssign(wid, 1);
        }
    }
    else {
        dtkWarn() << "dtkDistributedGraphTopology try to addEdge(" << from << "," << to << ") with wid=" << wid << " but the owner is " << from_owner  << " . Nothing will be done !!!";
    }

    if (!oriented) {
        addEdge(to, from, true);
    }
}

void dtkDistributedGraphTopology::addEdgeFEM(qlonglong from, qlonglong to)
{
    qint32 wid = this->wid();
    qint32 from_owner = static_cast<qint32>(m_mapper->owner(from));
    if (wid == from_owner) {
        dtkDistributedGraphTopologyPopulateMap(m_map, from, to);
        m_edge_count->addAssign(wid, 1);
    } else {

        m_remote_edges_count->addAssign(wid, 1);

        qint32 to_owner = static_cast<qint32>(m_mapper->owner(to));

        if (wid == to_owner) {
            dtkDistributedGraphTopologyPopulateMap(m_map_hybrid, from, to);

        } else {
            dtkDistributedGraphTopologyPopulateMap(m_map_remote, from, to);
        }
    }
}

void dtkDistributedGraphTopology::buildFEM(void)
{
    m_edge_count->unlock(this->wid());
    this->m_comm->barrier();
    // ---------------------------
    // First stage: interface vertex counting
    // ---------------------------

    // The first step of this procedure is to identify the vertices
    // that stand on an interface. We use the m_neighbour_count DSarray
    // to distinguish interior vertices from interface vertices.

    // Resets m_neighbour_count DSarray
    m_neighbour_count->fill(0);

    // Now we scan the m_map_hybrid containing the edges with a source
    // vertex that belongs to another partition. Such source vertices
    // stand on an interface. For each corresponding entry into the
    // m_neighbour_count DSarray, we add the number of edges that
    // connect these vertices to interior vertices.
    {
        auto it  = m_map_hybrid.cbegin();
        auto ite = m_map_hybrid.cend();

        for(; it != ite; ++it) {
            m_neighbour_count->addAssign(it.key(), (*it).size());
        }
    }
    this->m_comm->barrier();

    // After the previous scan, each partition can identify among its
    // interior vertices those that have connections with vertices on
    // other partitions. Tecognize new interface vertices provided by
    // other partitions. These vertices were added into the m_map. So,
    // we can now move them into the m_map_hybrid and increment for
    // each of them the number of connected edges into the
    // m_neighbour_count DSarray.

    // For that, we scan the local part of this latter. For each non
    // zero entry, we search for the corresponding vertex into the
    // m_map then, if we find it, we move its edges into the
    // m_map_hybrid and we increment the value of the current entry of
    // the m_neighbour_count DSarray.
    {
        auto it  = m_neighbour_count->begin();
        auto ite = m_neighbour_count->end();
        qlonglong id = 0;
        qlonglong gid;

        for(; it != ite; ++it, ++id) {
            if (*it != 0) {
                gid = m_neighbour_count->mapper()->localToGlobal(id, this->wid());
                EdgeList l = m_map.take(gid);
                if (!l.empty()) {
                    m_map_hybrid.insert(gid, l);
                    *it += l.size();
                }
            }
        }
    }
    m_comm->barrier();

    // ---------------------------
    // Second stage: odd edge counting
    // ---------------------------

    // At this stage, the local m_map_hybrid contains all the
    // interface vertices and their connections to interior
    // ones. However, for given graph topology, it is likely that some
    // edges connect two interface vertices without being themselves
    // on the interface. If such edges exist, they have been added
    // into the m_map_remote that contains all the edges that connect
    // two interface vertices that belong to another partition.

    // Identifying such edges requires to assemble a DSarray
    // containing all the edges from the local m_map_hybrid. Then,
    // each partition scan the edges of its local m_map_remote and
    // search for them into the DSarray whether they have been already
    // treated or not. If not, these edges are moved from the
    // m_map_remote to the m_map_hybrid.

    /* if (wid() == 3) {
        qDebug() << m_map_hybrid << m_map;
        auto it  = m_neighbour_count->begin();
        auto ite = m_neighbour_count->end();
        for(; it != ite; ++it) {
            qDebug() << *it;
        }
    }*/

    // The following step is therefore to assemble into a DSarray all
    // the edges from the local m_map_hybrid. These edges will be
    // stored into the CSR format so we can reuse the intrinsic
    // structures of the graph, namely the m_vertex_to_edge DSarray
    // and the m_edge_to_vertex one.

    // We now build the mapper of the m_edge_to_vertex DSarray. For
    // that, we need to count the local edges that have an interface
    // vertex as source. We also populate the m_vertex_to_edge DSarray
    // that will tell us the positions in the m_edge_to_vertex DSarray
    // of the first neighbours for each interface vertex.

    qlonglong local_itf_edges;
    {
        m_vertex_to_edge->fill(-1);
        qlonglong first_id = m_vertex_to_edge->mapper()->firstIndex(this->wid());
        qlonglong offset = 0;
        for(qlonglong i = 0; i < first_id; ++i) {
            offset += m_neighbour_count->at(i);
        }
        offset += this->wid();

        auto it  = m_neighbour_count->begin();
        auto ite = m_neighbour_count->end();
        auto vit = m_vertex_to_edge->begin();

        local_itf_edges = offset;
        for(; it != ite; ++it, ++vit) {
            if (*it != 0) {
                *vit = local_itf_edges;
                local_itf_edges += *it;
            }
        }

        local_itf_edges -= offset;

        // In order to avoid zero array allocation which can happen
        // when a partition does not own any interface vertex (usually
        // the last partition), we enforce a minimal size of one.
        local_itf_edges += 1;
    }

    // if(wid() == 0) {
    //     for (int i = 0; i < m_vertex_to_edge->size(); ++i) {
    //         qDebug() << "v_to_itf_e" << i << m_vertex_to_edge->at(i) << m_neighbour_count->at(i);
    //     }
    // }

    // Reduction to compute the global number of interface edges.
    qlonglong itf_edges_count = 0;
    m_comm->reduce(&local_itf_edges, &itf_edges_count, 1, dtkDistributedCommunicator::Sum, 0, true);

    // We update the DSarray m_edge_count so that it contains the
    // number of interface edges for each partitions.
    (*m_edge_count->begin()) = local_itf_edges;
    m_comm->barrier();

    // Builds the mapper for m_edge_to_vertex DSarray.
    dtkDistributedMapper *itf_edges_mapper = new dtkDistributedMapper();
    itf_edges_mapper->initMap(itf_edges_count, m_comm->size());

    qlonglong itf_edge_counter = 0;
    for (int i = 0; i < m_comm->size(); ++i) {
        itf_edges_mapper->setMap(itf_edge_counter, i);
        itf_edge_counter += m_edge_count->at(i);
    }
    m_comm->barrier();

    // Now we can populate the m_edge_to_vertex DSarray
    if (m_edge_to_vertex) {
        delete m_edge_to_vertex;
    }
    m_edge_to_vertex = new dtkDistributedArray<qlonglong>(itf_edges_count, itf_edges_mapper);
    m_edge_to_vertex->fill(-1);
    this->m_comm->barrier();

    // We scan the interface vertices of the local m_hybrid_map. For
    // each of them we find using the m_vertex_to_edge DSarray the
    // position into the m_edge_to_vertex DSarray where we can set the
    // value of all its neighbours.
    {
        auto it  = m_map_hybrid.cbegin();
        auto ite = m_map_hybrid.cend();

        for(; it != ite; ++it) {
            qlonglong start_pos = m_vertex_to_edge->at(it.key());
            qlonglong end_pos = start_pos + m_neighbour_count->at(it.key());
            const EdgeList& l = *it;
            for (qlonglong nid : l) {
                for (qlonglong j = start_pos; j < end_pos; ++j) {
                    qlonglong tmp = m_edge_to_vertex->at(j);
                    if (tmp < 0) {
                        m_edge_to_vertex->setAt(j, nid);
                        start_pos = j + 1;
                        break;
                    }
                }
            }
        }
    }
    this->m_comm->barrier();

    // Now, the m_edge_to_vertex DSarray contains all the edges that
    // have an interface vertex as source. We can perfom an
    // intersection with the local m_map_remote to find the remaining
    // edges that connect two interface vertices but that does not
    // stand on an interface.

    /*if(wid() == 0) {
        for (qlonglong i = 0; i < m_vertex_to_edge->size(); ++i) {
            qlonglong start_pos = m_vertex_to_edge->at(i);
            qlonglong end_pos = start_pos + m_neighbour_count->at(i);
            for (qlonglong j = start_pos; j < end_pos; ++j) {
                qDebug() << i << m_edge_to_vertex->at(j);
            }
        }
    }*/

    // Such edges will be moved from m_map_remote to m_map_hybrid and
    // also stored into a dedicated map.
    QMap<qlonglong, QList<qlonglong> > remote_edge_to_add;

    // For each edge of the m_map_remote, we search into the
    // m_edge_to_vertex whether it is found or not. If the edge is not
    // found, it means that it is an edge that connects two interface
    // vertices but that it does not stand on an interface.
    {
        auto it  = m_map_remote.begin();
        auto ite = m_map_remote.end();

        QList<qlonglong> edges_to_move;

        for(; it != ite; ++it) {
            qlonglong start_pos = m_vertex_to_edge->at(it.key());
            qlonglong end_pos = start_pos + m_neighbour_count->at(it.key());
            EdgeList& l = *it;
            edges_to_move.clear();
            for (int i = 0; i < l.size(); ++i) {
                qlonglong nid = l.at(i);
                bool found = false;
                for (qlonglong j = start_pos; j < end_pos; ++j) {
                    if (nid == m_edge_to_vertex->at(j)) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    edges_to_move << i;
                }
            }
            if (!edges_to_move.empty()) {
                EdgeList& rl = remote_edge_to_add[it.key()];
                EdgeList& hl = m_map_hybrid[it.key()];
                for (int i = 0; i < edges_to_move.size(); ++i) {
                    qlonglong e_id = l.at(edges_to_move.at(i));
                    rl << e_id;
                    l.removeAt(edges_to_move.at(i));
                    auto it = hl.begin();
                    for(; it != hl.end(); ++it) {
                        if (e_id < (*it)) {
                            break;
                        }
                    }
                    hl.insert(it, e_id);
                }
                m_neighbour_count->addAssign(it.key(), edges_to_move.size());
            }
        }
    }
    m_comm->barrier();

    // At the end of this stage, the local hybrid map contains all the
    // edges that connect an interior vertex to an interface vertex
    // plus the special edges that connect two interface vertices but
    // that does not belong to an interface.

    // Moreover, for all the vertices that stand on an interface, the
    // m_neighbour_count array contains the right number of edges
    // connected to these vertices.

    // ---------------------------
    // Third stage: graph building
    // ---------------------------

    // Firstly, we save the mapping of the vertex to the interface
    // edges and the local interface edges into pure local arrays. To
    // preserve a local mapping we need to substract to each value the
    // first position in the current partition.

    dtkArray<qlonglong, 0> itf_neightbour_count(m_neighbour_count->data(), m_neighbour_count->mapper()->count(this->wid()));
    dtkArray<qlonglong, 0> vertex_to_itf_edges(m_vertex_to_edge->data(), m_vertex_to_edge->mapper()->count(this->wid()));
    dtkArray<qlonglong, 0> itf_edges_to_vertex(m_edge_to_vertex->data(), m_edge_to_vertex->mapper()->count(this->wid()) - 1);
    {
        qlonglong offset = m_edge_to_vertex->mapper()->firstIndex(this->wid());
        for (qlonglong& i : vertex_to_itf_edges) {
            i -= offset;
        }
    }
    m_comm->barrier();

    // Resets the mapping.
    m_vertex_to_edge->fill(0);

    // We now complete the counting of the neighbours for the intern
    // vertices. This step is purely local.
    m_neighbour_count->wlock(this->wid());
    {
        auto it  = m_map.cbegin();
        auto ite = m_map.cend();
        for (; it != ite; ++it) {
            const EdgeList& l = *it;
            m_neighbour_count->setAt(it.key(), l.size());
        }
    }
    m_neighbour_count->unlock(this->wid());

    // We now build the mapper for the m_edge_to_vertex DSarray. We
    // count the local edges for each partition and assign this value
    // into the m_edge_count DSarray
    m_neighbour_count->rlock(this->wid());
    qlonglong local_edge_count = 0;
    {
        for(qlonglong count : (*m_neighbour_count)) {
            local_edge_count += count;
        }
        (*(m_edge_count->begin())) = local_edge_count;
    }
    m_neighbour_count->unlock(this->wid());

    // Reduction to compute global edge count
    qlonglong edge_count;
    m_comm->reduce(&local_edge_count, &edge_count, 1, dtkDistributedCommunicator::Sum, 0, true);

    // We are now able to populate the mapper.
    dtkDistributedMapper *e_mapper = new dtkDistributedMapper;
    e_mapper->initMap(edge_count, m_comm->size());
    {
        qlonglong offset = 0;
        for (qlonglong i = 0; i < m_comm->size(); ++i) {
            e_mapper->setMap(offset ,i);
            offset += m_edge_count->at(i);
        }
        offset = e_mapper->firstIndex(this->wid());

        // We also populate the m_vertex_to_edge DSarray that will
        // tell us the positions in the m_edge_to_vertex DSarray of
        // the first neighbours for each vertex.

        m_vertex_to_edge->wlock(this->wid());
        m_neighbour_count->rlock(this->wid());

        auto nit  = m_neighbour_count->begin();
        auto nite = m_neighbour_count->end();
        auto it   = m_vertex_to_edge->begin();

        for (; nit != nite; ++nit, ++it) {
            *it = offset;
            offset += *nit;
        }

        m_neighbour_count->unlock(this->wid());
        m_vertex_to_edge->unlock(this->wid());
    }
    m_comm->barrier();

    // We destroy the former DSarray to create a new one with the
    // total number of edges.
    delete m_edge_to_vertex;
    m_edge_to_vertex = new dtkDistributedArray<qlonglong>(edge_count, e_mapper);
    m_edge_to_vertex->fill(-1);

    // Firstly, each partition add the odd edges stored in its
    // remote_edge_to_add map.
    {
        auto it  = remote_edge_to_add.cbegin();
        auto ite = remote_edge_to_add.cend();

        for(; it != ite; ++it) {
            qlonglong start_pos = m_vertex_to_edge->at(it.key());
            qlonglong end_pos = start_pos + m_neighbour_count->at(it.key());
            const EdgeList& l = *it;
            for (qlonglong nid : l) {
                for (qlonglong j = start_pos; j < end_pos; ++j) {
                    qlonglong tmp = m_edge_to_vertex->at(j);
                    if (tmp < 0) {
                        m_edge_to_vertex->setAt(j, nid);
                        start_pos = j + 1;
                        break;
                    }
                }
            }
        }
    }
    this->m_comm->barrier();

    // Populate the m_edge_to_vertex DSarray
    m_vertex_to_edge->rlock(this->wid());
    m_neighbour_count->rlock(this->wid());
    {
        qlonglong e_offset = m_edge_to_vertex->mapper()->firstIndex(this->wid());

        // Firstly, we scan the edges of the interface vertices. For
        // each of them, we store in a list with increasing order
        // the id of their neighbours.
        EdgeList l;
        for (qlonglong i = 0; i < vertex_to_itf_edges.size(); ++i) {
            qlonglong start_pos = vertex_to_itf_edges.at(i);
            if (start_pos < 0) {
                // We squeeze intern vertices.
                continue;
            }
            qlonglong gid = this->mapper()->localToGlobal(i, this->wid());
            l.reserve(m_neighbour_count->at(gid));

            // We start by the edges having two vertices on an
            // interface but that do not belong to an interface.
            auto e_it  = m_edge_to_vertex->begin() + m_vertex_to_edge->at(gid) - e_offset;
            auto e_end =  e_it + m_neighbour_count->at(gid);
            for(; e_it != e_end; ++e_it) {
                if ((*e_it) < 0)
                    break;
                dtkDistributedOrderingListInsertion(l, *e_it);
            }

            // Now we scan the itf_edges_to_vertex array. To get the
            // right number of edges, we need to substract the number
            // of edges scanned in the previous step because
            // itf_neightbour_count array gets the total amount of
            // edges for each vertex.
            qlonglong end_pos = start_pos + itf_neightbour_count.at(i) - l.size();
            for (qlonglong j = start_pos; j < end_pos; ++j) {
                dtkDistributedOrderingListInsertion(l, itf_edges_to_vertex.at(j));
            }

            // Now we can use this list to populate m_vertex_to_edge DSarray.
            e_it  = m_edge_to_vertex->begin() + m_vertex_to_edge->at(gid) - e_offset;
            auto lit = l.cbegin();
            for (; e_it != e_end; ++e_it, ++lit) {
                *e_it = *lit;
            }

            // Clear the list before tackling next vertex.
            l.clear();
        }

        // Secondly, we scan the edges of the intern vertices and we
        // add them directly into the m_edge_to_vertex DSarray at the
        // right position.
        auto it  = m_map.cbegin();
        auto end = m_map.cend();

        for (; it != end; ++it) {
            const EdgeList& edge_list = *it;
            auto nit  = edge_list.begin();
            auto nend = edge_list.end();
            auto e_it  = m_edge_to_vertex->begin() + m_vertex_to_edge->at(it.key()) - e_offset;

            for(;nit != nend; ++nit, ++e_it) {
                *e_it = *nit;
            }
        }
    }

    m_neighbour_count->unlock(this->wid());
    m_vertex_to_edge->unlock(this->wid());

    this->m_comm->barrier();

    // if (this->wid() == 0) {
    //     for (qlonglong i = 0; i < m_vertex_to_edge->size(); ++i) {
    //         qlonglong start_pos = m_vertex_to_edge->at(i);
    //         qlonglong end_pos = start_pos + m_neighbour_count->at(i);
    //         for (qlonglong j = start_pos; j < end_pos; ++j) {
    //             qDebug() << i << m_edge_to_vertex->at(j);
    //         }
    //     }
    // }


    // ------------------------
    {
        qlonglong local_internal_nnz = 0;
        qlonglong local_hybrid_nnz = 0;
        qlonglong local_remote_nnz = 0;
        qlonglong v_count = 0;
        qlonglong e_count = 0;

        dtkArray<qlonglong, 0> local_neighbour_count;

        m_local_vertex_to_edge.reserve(m_map.size() + m_map_hybrid.size() + 1);

        {
            auto it  = m_map.cbegin();
            auto ite = m_map.cend();

            for(; it != ite; ++it) {
                local_internal_nnz += (*it).size();
                m_glob_to_loc.insert(it.key(), v_count++);
                m_loc_to_glob << it.key();
                local_neighbour_count << (*it).size();
                m_local_vertex_to_edge << e_count;
                e_count += (*it).size();
            }
        }
        {
            auto it  = m_map_hybrid.cbegin();
            auto ite = m_map_hybrid.cend();

            for(; it != ite; ++it) {
                local_hybrid_nnz += (*it).size();
                m_glob_to_loc.insert(it.key(), v_count++);
                m_loc_to_glob << it.key();
                local_neighbour_count << (*it).size();
                m_local_vertex_to_edge << e_count;
                e_count += (*it).size();
            }
        }
        m_local_vertex_to_edge << e_count;

        {
            auto it  = m_map_remote.cbegin();
            auto ite = m_map_remote.cend();

            for(; it != ite; ++it) {
                local_remote_nnz += (*it).size();
                if(!m_glob_to_loc.contains(it.key())) {
                    m_glob_to_loc.insert(it.key(), v_count++);
                    m_loc_to_glob << it.key();
                    local_neighbour_count << (*it).size();
                    e_count += (*it).size();
                } else {
                    local_neighbour_count[m_glob_to_loc[it.key()]] += (*it).size();
                    e_count += (*it).size();
                }
            }
        }

        qlonglong local_nnz = local_internal_nnz + local_hybrid_nnz + local_remote_nnz;
        m_local_edge_to_vertex.resize(local_nnz);

        dtkDistributedArray<qlonglong> local_edge_count(m_comm->size());
        auto loc_it = local_edge_count.begin();
        *loc_it = local_nnz;

        qlonglong total_local_nnz = 0;
        m_comm->reduce(&local_nnz, &total_local_nnz, 1, dtkDistributedCommunicator::Sum, 0, true);

        m_fe_mapper = new dtkDistributedMapper;
        m_fe_mapper->initMap(total_local_nnz, m_comm->size());

        qlonglong offset = 0;
        for (qlonglong i = 0; i < m_comm->size(); ++i) {
            m_fe_mapper->setMap(offset, i);
            offset += local_edge_count.at(i);
        }

        auto local_it = m_local_edge_to_vertex.begin();
        {
            auto it  = m_map.cbegin();
            auto ite = m_map.cend();

            QList<qlonglong> vertex_sorted_according_local_id;
            for(; it != ite; ++it) {
                dtkDistributedSortListUsingMap(*it, m_glob_to_loc, vertex_sorted_according_local_id);
                for (qlonglong id : vertex_sorted_according_local_id) {
                    // if (m_comm->wid() == 3) {
                    //     qDebug() << "intern fill" << it.key() << id << m_glob_to_loc[it.key()] << m_glob_to_loc[id];
                    // }
                    //(*local_it) = m_glob_to_loc[id];
                    (*local_it) = id;
                    ++local_it;
                }
            }
        }

        {
            auto it  = m_map_hybrid.cbegin();
            auto ite = m_map_hybrid.cend();

            QList<qlonglong> vertex_sorted_according_local_id;
            for(; it != ite; ++it) {
                dtkDistributedSortListUsingMap(*it, m_glob_to_loc, vertex_sorted_according_local_id);
                for (qlonglong id : vertex_sorted_according_local_id) {
                    // if (m_comm->wid() == 3) {
                    //     qDebug() << "hybrid fill" << it.key() << id << m_glob_to_loc[it.key()] << m_glob_to_loc[id];
                    // }
                    //(*local_it) = m_glob_to_loc[id];
                    (*local_it) = id;
                    ++local_it;
                }

            }
        }

        {
            auto it  = m_map_remote.cbegin();
            auto ite = m_map_remote.cend();

            QList<qlonglong> vertex_sorted_according_local_id;
            for(; it != ite; ++it) {
                dtkDistributedSortListUsingMap(*it, m_glob_to_loc, vertex_sorted_according_local_id);
                for (qlonglong id : vertex_sorted_according_local_id) {
                    // if (m_comm->wid() == 3) {
                    //     qDebug() << "remote fill" << it.key() << id << m_glob_to_loc[it.key()] << m_glob_to_loc[id];

                    // }
                    //(*local_it) = m_glob_to_loc[id];
                    (*local_it) = id;
                    ++local_it;
                }
            }
        }

        // ----------------

        qlonglong local_pos = m_fe_mapper->firstIndex(this->wid());

        if(m_positions)
            delete m_positions;
        m_positions = new dtkDistributedArray<qlonglong>(m_edge_to_vertex->size(), m_edge_to_vertex->mapper());
        m_positions->fill(-1);

        m_positions->wlock();
        for (qlonglong i = 0; i < m_local_vertex_to_edge.size() - 1; ++i) {
            qlonglong gi = m_loc_to_glob[i];
            qlonglong nnz = m_local_vertex_to_edge[i+1] - m_local_vertex_to_edge[i];
            qlonglong local_start = m_local_vertex_to_edge[i];

            qlonglong first_n_pos = m_vertex_to_edge->at(gi);
            qlonglong n_count = m_neighbour_count->at(gi);

            for (qlonglong j = 0; j < nnz; ++j) {
                qlonglong gj = m_local_edge_to_vertex[j + local_start];
                for (qlonglong k = 0; k < n_count; ++k) {
                    qlonglong global_pos = k + first_n_pos;
                    // if (m_comm->wid() == 3 && gi == 7)
                    //     qDebug() << global_pos << local_pos << gi << gj;

                    if (gj == m_edge_to_vertex->at(global_pos)) {
                         // if (m_comm->wid() == 3 && gi == 7)
                         //     qDebug() << global_pos << local_pos << gi << gj;
                        m_positions->setAt(global_pos, local_pos);
                        ++local_pos;
                        break;
                    }
                }
            }
        }
        m_positions->unlock();
    }

    // ------------------------

    this->m_comm->barrier();
}

// /////////////////////////////////////////////////////////////////
// Helper function
// /////////////////////////////////////////////////////////////////

void dtkDistributedOrderingListInsertion(QList<qlonglong>& l, qlonglong id)
{
    auto it  = l.begin();
    auto end = l.end();

    for(; it != end; ++it) {
        if (id == (*it)) {
            qDebug() << Q_FUNC_INFO << "Index already added in the list: id =" << id;
            return;
        } else if(id < *(it)) {
            break;
        }
    }
    l.insert(it, id);
}

void dtkDistributedSortListUsingMap(const QList<qlonglong>& l, const QMap<qlonglong, qlonglong>& m, QList<qlonglong>& res)
{
    res.clear();
    res.reserve(l.size());
    qlonglong lid;
    for(const qlonglong& id : l) {
        lid = m[id];

        auto it  = res.begin();
        auto end = res.end();

        for(; it != end; ++it) {
            if(lid < m[*(it)]) {
                break;
            }
        }
        res.insert(it, id);
    }
}

bool dtkDistributedGraphTopologyPopulateMap(QMap<qlonglong, QList<qlonglong> >& map, qlonglong from, qlonglong to)
{
    auto it  = map[from].begin();
    auto end = map[from].end();

    if (it == end) {
        map[from].insert(it, to);
    } else if (to > map[from].last()) {
        // tuning: usually, we append at the end, so check this case
        map[from].insert(end, to);
    } else {
        for(; it != end; ++it) {
            if (to == (*it))
                return false;
            if (to < (*it))
                break;
        }
        map[from].insert(it, to);
    }

    return true;
}

//
// dtkDistributedGraphTopology.cpp ends here

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

dtkDistributedGraphTopology::dtkDistributedGraphTopology(void) : dtkDistributedContainer(), m_is_assembled(false), m_edge_count(NULL), m_neighbour_count(NULL), m_vertex_to_edge(NULL), m_edge_to_vertex(NULL)
{
    m_dd.mapper = NULL;
    m_dd.positions = NULL;

    m_comm->barrier();
}

dtkDistributedGraphTopology::dtkDistributedGraphTopology(const qlonglong& vertex_count) : dtkDistributedContainer(vertex_count), m_is_assembled(false), m_edge_count(NULL), m_neighbour_count(NULL), m_vertex_to_edge(NULL), m_edge_to_vertex(NULL)
{
    m_dd.mapper = NULL;
    m_dd.positions = NULL;

    this->initialize();

    m_comm->barrier();
}

dtkDistributedGraphTopology::dtkDistributedGraphTopology(const qlonglong& vertex_count, dtkDistributedMapper *mapper) : dtkDistributedContainer(vertex_count, mapper), m_is_assembled(false), m_edge_count(NULL), m_neighbour_count(NULL), m_vertex_to_edge(NULL), m_edge_to_vertex(NULL)
{
    m_dd.mapper = NULL;
    m_dd.positions = NULL;

    this->initialize();

    m_comm->barrier();
}

dtkDistributedGraphTopology::dtkDistributedGraphTopology(const dtkDistributedGraphTopology& o) : dtkDistributedContainer(o.m_size), m_is_assembled(o.m_is_assembled), m_edge_count(NULL), m_neighbour_count(NULL), m_vertex_to_edge(NULL), m_edge_to_vertex(NULL)
{
    m_dd.mapper = NULL;
    m_dd.positions = NULL;

    m_comm->barrier();
    dtkWarn() << Q_FUNC_INFO << "Copy ctor not implemented. It is not clear it is necessary.";
}

dtkDistributedGraphTopology::~dtkDistributedGraphTopology(void)
{
    // if (!m_is_assembled && m_edge_count)
    //     m_edge_count->unlock(this->wid());

    this->clear();
}

dtkDistributedGraphTopology& dtkDistributedGraphTopology::operator = (const dtkDistributedGraphTopology&)
{
    dtkWarn() << Q_FUNC_INFO << "Copy assignment not implemented. It is not clear it is necessary.";
    return *this;
}

void dtkDistributedGraphTopology::clear(void)
{
    m_comm->barrier();

    m_size = 0LL;

    m_is_assembled = false;

    m_mapper->clear();

    if (m_neighbour_count) {
        delete m_neighbour_count;
    }

    if (m_edge_count)
        delete m_edge_count;

    if (m_vertex_to_edge)
        delete m_vertex_to_edge;
    if (m_edge_to_vertex)
        delete m_edge_to_vertex;


    if (m_dd.mapper && !m_dd.mapper->deref())
        delete m_dd.mapper;
    if (m_dd.positions)
        delete m_dd.positions;

    m_edge_count      = NULL;
    m_neighbour_count = NULL;
    m_vertex_to_edge  = NULL;
    m_edge_to_vertex  = NULL;

    m_dd.mapper    = NULL;
    m_dd.positions = NULL;

    m_comm->barrier();
}

void dtkDistributedGraphTopology::resize(qlonglong vertex_count)
{
    if (m_size == vertex_count)
        return;

    this->clear();
    m_size = vertex_count;
    m_mapper->setMapping(vertexCount(), m_comm->size());
    this->initialize();
}

void dtkDistributedGraphTopology::initialize(void)
{
    dtkDebug() << "initialize graph with" << vertexCount() << "vertexes, rank =" << this->wid();

    dtkDistributedMapper *mapper = new dtkDistributedMapper(*m_mapper);
    mapper->setMap(vertexCount() + 1, m_comm->size());
    m_vertex_to_edge = new dtkDistributedArray<qlonglong>(vertexCount() + 1, mapper);
    m_vertex_to_edge->fill(0);

    m_neighbour_count = new dtkDistributedArray<qlonglong>(vertexCount() + 1, mapper);
    m_neighbour_count->fill(0);

    m_edge_count = new dtkDistributedArray<qlonglong>(m_comm->size());
    m_edge_count->fill(0);
}

void dtkDistributedGraphTopology::addEdge(qlonglong from, qlonglong to)
{
    qint32 wid = this->wid();
    qint32 from_owner = static_cast<qint32>(m_mapper->owner(from));

    if (wid == from_owner) {
        dtkDistributedGraphTopologyPopulateMap(m_dd.map, from, to);
        *(m_edge_count->begin()) += 1;

    } else {

        qint32 to_owner = static_cast<qint32>(m_mapper->owner(to));

        if (wid == to_owner) {
            dtkDistributedGraphTopologyPopulateMap(m_dd.map_hybrid, from, to);

        } else {
            dtkDistributedGraphTopologyPopulateMap(m_dd.map_remote, from, to);
        }
    }
}

void dtkDistributedGraphTopology::buildDomainDecompositionMaps(void)
{
    if (!m_is_assembled)
        return;

    qlonglong wid = this->wid();

    m_dd.map.clear();
    m_dd.map_hybrid.clear();
    m_dd.map_remote.clear();

    // List of boundary nodes owned by a lower id partition.
    QList<qlonglong> be_nodes;

    qlonglong first_id = this->mapper()->firstIndex(wid);
    qlonglong  last_id = this->mapper()->lastIndex(wid);
    qlonglong v_count = this->mapper()->count(wid);
    qlonglong loc_size = this->mapper()->count(wid);
    qlonglong v_id = first_id;

    auto vit  = m_vertex_to_edge->begin();
    auto vend = vit + v_count;

    auto n_count = m_neighbour_count->begin();
    auto nit = m_edge_to_vertex->begin();

    // Lookup over interior nodes to detect:
    // - whether the current intern node is on a boundary
    // - boundary nodes owned by a lower partition
    // - populate pure intern edges into m_dd.map
    // - populate hybrid edges into m_dd.map_hybrid
    for (; vit != vend; ++vit, ++n_count, ++v_id) {
        auto nbeg = nit;
        auto nend = (nit + *n_count);
        bool current_node_is_on_boundary = false;

        // Lookup over interior nodes to detect whether the current
        // intern node is on a boundary
        for (; nit != nend; ++nit) {
            if (*nit > last_id) {
                current_node_is_on_boundary = true;
                break;
            }
        }
        nit = nbeg;

        // When the current node is on a boundary, all outcoming edges
        // are hybrid. Moreover, when target node is on a partition
        // with a lower id, the incoming edge is also hybrid.
        if (current_node_is_on_boundary) {
            for (; nit != nend; ++nit) {
                if (*nit < first_id) {
                    dtkDistributedGraphTopologyPopulateMap(m_dd.map_hybrid, v_id, *nit);
                    dtkDistributedGraphTopologyPopulateMap(m_dd.map_hybrid, *nit, v_id);
                    dtkDistributedOrderingListInsertion(be_nodes, *nit);
                } else if (*nit <= last_id) {
                    dtkDistributedGraphTopologyPopulateMap(m_dd.map_hybrid, v_id, *nit);
                }
            }
        // When the current node is interior, outcoming edges are
        // interior. When the target node is on a partition with a
        // lower id, the incoming edge is hybrid.
        } else {
            for (; nit != nend; ++nit) {
                if (*nit < first_id) {
                    dtkDistributedGraphTopologyPopulateMap(m_dd.map, v_id, *nit);
                    dtkDistributedGraphTopologyPopulateMap(m_dd.map_hybrid, *nit, v_id);
                    dtkDistributedOrderingListInsertion(be_nodes, *nit);
                } else if (*nit <= last_id) {
                    dtkDistributedGraphTopologyPopulateMap(m_dd.map, v_id, *nit);
                }
            }
        }
    }

    // At this stage, it is possible to know which vertex each
    // partition shares with another one and which interface vertices
    // each partition is responsible for. This information is gather
    // into m_dd.map_itf. (Same piece of code in assemble method!!!)
    {
        m_dd.local_intern_size = m_dd.map.size();
        m_dd.local_itf_size = m_dd.map_hybrid.size();

        auto it = m_dd.map_hybrid.cbegin();
        auto end = m_dd.map_hybrid.cend();

        for(; it != end; ++it) {

            qlonglong gid = it.key();
            qlonglong owner_gid = this->mapper()->owner(gid);
            if(wid == owner_gid) {
                dtkDistributedOrderingListInsertion(m_dd.map_itf[owner_gid], gid);
            }

            qlonglong j = m_vertex_to_edge->at(gid);
            qlonglong jend = j + m_neighbour_count->at(gid);
            for(; j < jend; ++j) {
                qlonglong jid = m_edge_to_vertex->at(j);
                qlonglong owner_jid = this->mapper()->owner(jid);
                if (wid != owner_jid && owner_gid <= owner_jid) {
                    dtkDistributedOrderingListInsertion(m_dd.map_itf[owner_jid], gid);
                }
            }
        }
    }

    // Now we populate the m_dd.map_remote that contains all the edges
    // connecting boundary nodes of lower id partitions.
    this->rlock();
    for (qlonglong ve_id : be_nodes) {
        qlonglong n_start = m_vertex_to_edge->at(ve_id);
        qlonglong n_end = n_start + m_neighbour_count->at(ve_id);
        for (qlonglong ne_id = n_start; ne_id < n_end; ++ne_id) {
            qlonglong vn_id = m_edge_to_vertex->at(ne_id);
            if (be_nodes.contains(vn_id)) {
                dtkDistributedGraphTopologyPopulateMap(m_dd.map_remote, ve_id, vn_id);
            }
        }
    }
    this->unlock();

    //qDebug() << wid << mapper()->firstIndex(wid) << mapper()->lastIndex(wid) << m_dd.map;// << m_dd.map_hybrid << m_dd.map_remote;

    this->m_comm->barrier();
}


void dtkDistributedGraphTopology::buildDomainDecompositionData(void)
{
    if (!m_is_assembled)
        return;

    qlonglong local_internal_nnz = 0;
    qlonglong local_hybrid_nnz = 0;
    qlonglong local_remote_nnz = 0;
    qlonglong v_count = 0;
    qlonglong e_count = 0;

    dtkArray<qlonglong, 0> local_neighbour_count;

    // Build the local CSR structures that organize data according to
    // domain decomposition paradigm.

    // First, we clean map_remote to extract vertices that are not
    // shared with other partitions. It means that vertices taht do
    // not appear into map_hybrid are removed from the map_remote.
    {
        auto it  = m_dd.map_remote.begin();
        auto ite = m_dd.map_remote.end();
        dtkArray<qlonglong> vert_to_remove; vert_to_remove.reserve(m_dd.map_remote.size());

        for (; it != ite; ++it) {
            if (!m_dd.map_hybrid.contains(it.key())) {
                vert_to_remove << it.key();
            } else {
                QList<qlonglong>& l = *it;
                auto lit = l.begin();
                auto lend = l.end();
                for (; lit != lend; ++lit) {
                    auto pos = lit;
                    if (!m_dd.map_hybrid.contains(*lit)) {
                        lit = l.erase(pos);
                        --lit;
                    }
                }
                qlonglong id = l.indexOf(it.key());
                if (id > -1) {
                    l.removeAt(id);
                }
            }
        }

        for (qlonglong vid : vert_to_remove) {
            m_dd.map_remote.remove(vid);
        }

    }

    // Fills the local_vertex_to_edge array that maps each vertex to
    // its first local edge. The vertices are sorted as follows:
    // - first, the pure interior ones
    // - second, the boundary vertices owned by the current partition
    // - third, the boundary vertices owned by lower id partitions

    m_dd.local_vertex_to_edge.reserve(m_dd.map.size() + m_dd.map_hybrid.size() + m_dd.map_remote.size());

    // At the same time, we make the mapping that enable to find local
    // id to global id and conversely.
    {
        auto it  = m_dd.map.cbegin();
        auto ite = m_dd.map.cend();

        for(; it != ite; ++it) {
            local_internal_nnz += (*it).size();
            m_dd.glob_to_loc.insert(it.key(), v_count++);
            m_dd.loc_to_glob << it.key();
            local_neighbour_count << (*it).size();
            m_dd.local_vertex_to_edge << e_count;
            e_count += (*it).size();
        }
    }
    {
        auto it  = m_dd.map_hybrid.cbegin();
        auto ite = m_dd.map_hybrid.cend();

        for(; it != ite; ++it) {
            local_hybrid_nnz += (*it).size();
            m_dd.glob_to_loc.insert(it.key(), v_count++);
            m_dd.loc_to_glob << it.key();
            local_neighbour_count << (*it).size();
            m_dd.local_vertex_to_edge << e_count;
            e_count += (*it).size();
        }
    }
    m_dd.local_vertex_to_edge << e_count;

    // The remote edges are not handled by the current partition so
    // they are registered at the end of the local_edge_to_vertex
    // array and they are not referenced by the local_vertex_to_edge
    // array.
    {
        auto it  = m_dd.map_remote.cbegin();
        auto ite = m_dd.map_remote.cend();

        for(; it != ite; ++it) {
            local_remote_nnz += (*it).size();
            if(!m_dd.glob_to_loc.contains(it.key())) {
                m_dd.glob_to_loc.insert(it.key(), v_count++);
                m_dd.loc_to_glob << it.key();
                local_neighbour_count << (*it).size();
                e_count += (*it).size();
                m_dd.local_vertex_to_edge << m_dd.local_vertex_to_edge.last();
            } else {
                local_neighbour_count[m_dd.glob_to_loc[it.key()]] += (*it).size();
                e_count += (*it).size();
            }
        }
    }

    // Now we can build the mapper that describe how the edges are
    // distributed according to domain decomposition paradigm.
    qlonglong local_nnz = local_internal_nnz + local_hybrid_nnz + local_remote_nnz;
    m_dd.local_edge_to_vertex.resize(local_nnz);

    qlonglong local_edge_count[m_comm->size()];
    m_comm->gather(&local_nnz, local_edge_count, 1, 0, true);

    qlonglong total_local_nnz = 0;
    for(qlonglong i=0; i<m_comm->size(); ++i)
        total_local_nnz += local_edge_count[i];

    m_dd.mapper = new dtkDistributedMapper;
    m_dd.mapper->ref();
    m_dd.mapper->initMap(total_local_nnz, m_comm->size());

    qlonglong offset = 0;
    for (qlonglong i = 0; i < m_comm->size(); ++i) {
        m_dd.mapper->setMap(offset, i);
        offset += local_edge_count[i];
    }

    // We now fill the local CSR edge_to_vertex array. The global ids
    // are sorted according to their local ids. This operation is
    // purely local.
    auto local_it = m_dd.local_edge_to_vertex.begin();
    QList<qlonglong> vertex_sorted_according_local_id;
    {
        auto it  = m_dd.map.cbegin();
        auto ite = m_dd.map.cend();

        for(; it != ite; ++it) {
            dtkDistributedSortListUsingMap(*it, m_dd.glob_to_loc, vertex_sorted_according_local_id);
            for (qlonglong id : vertex_sorted_according_local_id) {
                (*local_it) = id;
                ++local_it;
            }
        }
    }

    {
        auto it  = m_dd.map_hybrid.cbegin();
        auto ite = m_dd.map_hybrid.cend();

        for(; it != ite; ++it) {
            dtkDistributedSortListUsingMap(*it, m_dd.glob_to_loc, vertex_sorted_according_local_id);
            for (qlonglong id : vertex_sorted_according_local_id) {
                (*local_it) = id;
                ++local_it;
            }

        }
    }

    {
        auto it  = m_dd.map_remote.cbegin();
        auto ite = m_dd.map_remote.cend();

        for(; it != ite; ++it) {
            dtkDistributedSortListUsingMap(*it, m_dd.glob_to_loc, vertex_sorted_according_local_id);
            for (qlonglong id : vertex_sorted_according_local_id) {
                (*local_it) = id;
                ++local_it;
            }
        }
    }
    // if (wid() == 3) {
    //     qDebug() << m_dd.local_edge_to_vertex;
    // }


    // Now we fill the m_dd.position DSarray that tells for each edge
    // in the graph structure where it can be found in the domain
    // decomposition organization.

    qlonglong local_pos = m_dd.mapper->firstIndex(this->wid());

    if (m_dd.positions)
        delete m_dd.positions;

    m_dd.positions = new dtkDistributedArray<qlonglong>(m_edge_to_vertex->size(), m_edge_to_vertex->mapper());
    m_dd.positions->fill(-1);


    // We scan the local vertices of the DD structure.
    this->rlock();
    for (qlonglong i = 0; i < m_dd.local_vertex_to_edge.size() - 1; ++i) {

        qlonglong gi = m_dd.loc_to_glob[i];
        qlonglong nnz = m_dd.local_vertex_to_edge[i+1] - m_dd.local_vertex_to_edge[i];
        qlonglong local_start = m_dd.local_vertex_to_edge[i];

        qlonglong first_n_pos = m_vertex_to_edge->at(gi);
        qlonglong n_count = m_neighbour_count->at(gi);

        // For each local edge we search for its pos into the graph at
        // the same place we set its local pos into the m_dd.positions
        // DS array.
        for (qlonglong j = 0; j < nnz; ++j) {
            qlonglong gj = m_dd.local_edge_to_vertex[j + local_start];
            for (qlonglong k = 0; k < n_count; ++k) {
                qlonglong global_pos = k + first_n_pos;

                if (gj == m_edge_to_vertex->at(global_pos)) {
                    m_dd.positions->setAt(global_pos, local_pos);
                    ++local_pos;
                    break;
                }
            }
        }
    }
    this->unlock();

    // We only keep the remote map for referencing remote edges.
    m_dd.map.clear();
    m_dd.map_hybrid.clear();

    this->m_comm->barrier();
}

void dtkDistributedGraphTopology::assembleDomainDecompositionFeatures(void)
{
    this->buildDomainDecompositionMaps();
    this->buildDomainDecompositionData();
}

void dtkDistributedGraphTopology::assemble(void)
{
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
        auto it  = m_dd.map_hybrid.cbegin();
        auto ite = m_dd.map_hybrid.cend();

        for(; it != ite; ++it) {
            m_neighbour_count->addAssign(it.key(), (*it).size());
        }
    }
    this->m_comm->barrier();

    // After the previous scan, each partition can identify among its
    // interior vertices those that have connections with vertices on
    // other partitions. Recognize new interface vertices provided by
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
                EdgeList l = m_dd.map.take(gid);
                if (!l.empty()) {
                    m_dd.map_hybrid.insert(gid, l);
                    *it += l.size();
                }
            }
        }
    }
    m_comm->barrier();
    m_neighbour_count->clearCache();

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

    // if (wid() == 3) {
    //     qDebug() << m_dd.map_hybrid << m_dd.map;
    //     auto it  = m_neighbour_count->begin();
    //     auto ite = m_neighbour_count->end();
    //     for(; it != ite; ++it) {
    //         qDebug() << *it;
    //     }
    // }

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
        qlonglong last_id =  m_vertex_to_edge->mapper()->lastIndex(this->wid());
        qlonglong offset = 0;

        //calculation of offset
        //1 each proc sum it's local offset
        qlonglong local_offset=0;
        m_neighbour_count->rlock(this->wid());
        for(qlonglong i=first_id; i<=last_id; ++i)
        {
            local_offset += m_neighbour_count->at(i);
        }
        m_neighbour_count->unlock();
        m_comm->barrier();

        //2 we do a all gather to avoid reading data of other processes 
        qlonglong offset_per_proc[m_comm->size()] ;
        m_comm->gather(&local_offset, offset_per_proc, 1, 0, true); 

        //3 do a reduction
        for(qlonglong i=0; i<this->wid(); ++i)
        {
            offset += offset_per_proc[i];
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
    m_comm->barrier();
    m_vertex_to_edge->clearCache();

    // if(wid() == 0) {
    //     //m_vertex_to_edge->clearCache();m_neighbour_count->clearCache();
    //     for (int i = 0; i < m_vertex_to_edge->size() - 1; ++i) {
    //         qDebug() << "v_to_itf_e" << i << m_vertex_to_edge->at(i);// << m_neighbour_count->at(i);
    //     }
    // }

    // Reduction to compute the global number of interface edges.
    qlonglong itf_edges_count = 0;
    m_comm->reduce(&local_itf_edges, &itf_edges_count, 1, dtkDistributedCommunicator::Sum, 0, true);

    // We update the DSarray m_edge_count so that it contains the
    // number of interface edges for each partitions.
    (*m_edge_count->begin()) = local_itf_edges;
    m_comm->barrier();
    m_edge_count->clearCache();

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

    // We scan the interface vertices of the local m_hybrid_map. For
    // each of them we find using the m_vertex_to_edge DSarray the
    // position into the m_edge_to_vertex DSarray where we can set the
    // value of all its neighbours.
    {
        auto it  = m_dd.map_hybrid.cbegin();
        auto ite = m_dd.map_hybrid.cend();

        qlonglong minusOne = -1;

        for(; it != ite; ++it) {
            qlonglong start_pos = m_vertex_to_edge->at(it.key());
            qlonglong end_pos = start_pos + m_neighbour_count->at(it.key());
            const EdgeList& l = *it;
            for (qlonglong nid : l) {
                for (qlonglong j = start_pos; j < end_pos; ++j) {
                    if (m_edge_to_vertex->compareAndSwap(j, nid, minusOne)) {
                        break;
                    }
                }
            }
        }
    }
    this->m_comm->barrier();

    // At this stage, it is possible to know which vertex each
    // partition shares with another one and which interface vertices
    // each partition is responsible for. This infcormation is gather
    // into m_dd.map_itf.
    {
        m_dd.local_intern_size = m_dd.map.size();
        m_dd.local_itf_size = m_dd.map_hybrid.size();

        auto it = m_dd.map_hybrid.cbegin();
        auto end = m_dd.map_hybrid.cend();

        for(; it != end; ++it) {

            qlonglong gid = it.key();
            qlonglong owner_gid = this->mapper()->owner(gid);
            if(wid() == owner_gid) {
                dtkDistributedOrderingListInsertion(m_dd.map_itf[owner_gid], gid);
            }

            qlonglong j = m_vertex_to_edge->at(gid);
            qlonglong jend = j + m_neighbour_count->at(gid);
            for(; j < jend; ++j) {
                qlonglong jid = m_edge_to_vertex->at(j);
                qlonglong owner_jid = this->mapper()->owner(jid);
                if (wid() != owner_jid && owner_gid <= owner_jid) {
                    dtkDistributedOrderingListInsertion(m_dd.map_itf[owner_jid], gid);
                }
            }
        }
    }
    // Furthermore, we can now compute the total number of vertices on
    // all the interfaces.
    qlonglong local_itf_owned = m_dd.map_itf[wid()].size();
    m_comm->reduce(&local_itf_owned, &m_dd.global_itf_size, 1, dtkDistributedCommunicator::Sum, 0, true);

    // Now, the m_edge_to_vertex DSarray contains all the edges that
    // have an interface vertex as source. We can perfom an
    // intersection with the local m_map_remote to find the remaining
    // edges that connect two interface vertices but that does not
    // stand on an interface.

    // if(wid() == 1) {
    //     for (qlonglong i = 0; i < m_vertex_to_edge->size(); ++i) {
    //         qlonglong start_pos = m_vertex_to_edge->at(i);
    //         qlonglong nc = m_neighbour_count->at(i);
    //         qlonglong end_pos = start_pos + m_neighbour_count->at(i);
    //          for (qlonglong j = start_pos; j < end_pos; ++j) {
    //             qDebug() << i << m_edge_to_vertex->at(j);
    //         }
    //     }
    // }
    // this->m_comm->barrier();

    // Such edges will be moved from m_map_remote to m_map_hybrid and
    // also stored into a dedicated map.
    QMap<qlonglong, QList<qlonglong> > remote_edge_to_add;

    // For each edge of the m_dd.map_remote, we search into the
    // m_edge_to_vertex whether it is found or not. If the edge is not
    // found, it means that it is an edge that connects two interface
    // vertices but that it does not stand on an interface.
    {
        auto it  = m_dd.map_remote.begin();
        auto ite = m_dd.map_remote.end();

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
                EdgeList& hl = m_dd.map_hybrid[it.key()];
                for (int i = 0; i < edges_to_move.size(); ++i) {
                    qlonglong e_id = l.at(edges_to_move.at(i));
                    rl << e_id;
                    auto it = hl.begin();
                    for(; it != hl.end(); ++it) {
                        if (e_id < (*it)) {
                            break;
                        }
                    }
                    hl.insert(it, e_id);
                }
                l.clear();
                m_neighbour_count->addAssign(it.key(), edges_to_move.size());
            }
        }
    }
    m_comm->barrier();
    m_neighbour_count->clearCache();

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

    //qDebug() << Q_FUNC_INFO << this->wid() << itf_edges_to_vertex;
    // m_comm->barrier();

    // Resets the mapping.
    m_vertex_to_edge->fill(0);

    // We now complete the counting of the neighbours for the intern
    // vertices. This step is purely local.
    m_neighbour_count->wlock(this->wid());
    {
        auto it  = m_dd.map.cbegin();
        auto ite = m_dd.map.cend();
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
    m_neighbour_count->clearCache();
    m_edge_count->clearCache();

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
    m_vertex_to_edge->clearCache();

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

        qlonglong minusOne = -1;

        for(; it != ite; ++it) {
            qlonglong start_pos = m_vertex_to_edge->at(it.key());
            qlonglong end_pos = start_pos + m_neighbour_count->at(it.key());
            const EdgeList& l = *it;
            for (qlonglong nid : l) {
                for (qlonglong j = start_pos; j < end_pos; ++j) {
                    if (m_edge_to_vertex->compareAndSwap(j, nid, minusOne)) {
                        break;
                    }
                }
            }
        }
    }
    this->m_comm->barrier();
    m_edge_to_vertex->clearCache();

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
            auto e_it  = m_edge_to_vertex->begin() + (m_vertex_to_edge->at(gid) - e_offset);
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
                //if (itf_edges_to_vertex.at(j) < 0)
                    //qDebug() << Q_FUNC_INFO << this->wid() << gid << itf_edges_to_vertex.at(j);
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
        this->m_comm->barrier();
        m_edge_to_vertex->clearCache();

        // Secondly, we scan the edges of the intern vertices and we
        // add them directly into the m_edge_to_vertex DSarray at the
        // right position.
        auto it  = m_dd.map.cbegin();
        auto end = m_dd.map.cend();

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

    // if (this->wid() == 0) {
    //     for (qlonglong i = 0; i < m_vertex_to_edge->size(); ++i) {
    //         qlonglong start_pos = m_vertex_to_edge->at(i);
    //         qlonglong end_pos = start_pos + m_neighbour_count->at(i);
    //         for (qlonglong j = start_pos; j < end_pos; ++j) {
    //             qDebug() << i << m_edge_to_vertex->at(j);
    //         }
    //     }
    // }

    m_is_assembled = true;

    m_comm->barrier();
    m_edge_to_vertex->clearCache();

    // ------------------------
    this->buildDomainDecompositionData();
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
            //qDebug() << Q_FUNC_INFO << "Index already added in the list: id =" << id << l;
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
    for(const qlonglong& id : l) {
        const qlonglong& lid = m[id];

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
    QList<qlonglong> *list = &map[from];
    auto it  = list->begin();
    auto end = list->end();

    if (it == end) {
        list->insert(it, to);
    } else if (to > list->last()) {
        // tuning: usually, we append at the end, so check this case
        list->insert(end, to);
    } else {
        for(; it != end; ++it) {
            if (to == (*it))
                return false;
            if (to < (*it))
                break;
        }
        list->insert(it, to);
    }

    return true;
}

//
// dtkDistributedGraphTopology.cpp ends here

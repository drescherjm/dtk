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

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraph implementation
// /////////////////////////////////////////////////////////////////

inline dtkDistributedGraph::dtkDistributedGraph(dtkDistributedWorker *worker) : dtkDistributedContainer(worker)
{
}

inline dtkDistributedGraph::dtkDistributedGraph(const qlonglong& vertex_count, dtkDistributedWorker *worker) : dtkDistributedContainer(vertex_count, worker)
{
    this->initialize();
}

inline dtkDistributedGraph::~dtkDistributedGraph(void)
{
}

inline qlonglong dtkDistributedGraph::vertexCount(void) const
{
    return this->size();
}

inline qlonglong dtkDistributedGraph::edgeCount(void) const
{
    return m_edge_count->at(this->wid());
}

inline void dtkDistributedGraph::initialize(void)
{
    qDebug() << "initialize graph with " << vertexCount() << "vertexes";

    m_vertices = new dtkDistributedArray<qlonglong>(vertexCount() + 1, this->worker());

    m_edge_count = new dtkDistributedArray<qlonglong>(m_comm->size(), this->worker());
    for (qint32 i = 0; i< m_comm->size(); i++) {
        if (i == this->wid()) {
            m_edge_count->setAt(i,0);
        }
    }

    m_mapper->setMapping(vertexCount(), m_comm->size());
}

inline void dtkDistributedGraph::build(void)
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

    m_edges = new dtkDistributedArray<qlonglong>(edge_count, this->worker(), mapper);

    EdgeMap::const_iterator it  = m_map.cbegin();
    EdgeMap::const_iterator end = m_map.cend();

    offset = mapper->startIndex(this->wid());
    qlonglong index = 0;
    for (; it != end; ++it) {
        m_vertices->setAt(it.key(), offset);
        offset += (*it).count();
        EdgeList::const_iterator nit  = (*it).begin();
        EdgeList::const_iterator nend = (*it).end();
        for(;nit != nend; ++nit) {
            m_edges->setLocalValue(index, *nit);
            ++index;
        }
    }

    this->m_comm->barrier();
    if (this->wid() == this->m_comm->size() - 1) {
        m_vertices->setAt(m_vertices->size() - 1, offset);
    }

    this->m_comm->barrier();
}

inline bool dtkDistributedGraph::read(const QString& filename)
{
    QFile file(filename);

    if(filename.isEmpty() || (!file.exists())) {
        qWarning() << "input file is empty/does not exist" << filename << "Current dir is" << QDir::currentPath();
        return false;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    QStringList header = in.readLine().split(' ');
    this->m_size = header.first().toLongLong();
    if (vertexCount()  == 0) {
        qWarning() << "Can't parse size of the graph" << filename;
        return false;
    }
    qlonglong edges_count = header.at(1).toLongLong();
    if (edges_count  == 0) {
        qWarning() << "Can't parse the number of edges" << filename;
        return false;
    }

    qWarning() << "will initialize graph with" << vertexCount() << edges_count;
    this->initialize();
    m_comm->barrier();

    // if (this->wid() == 0) {

        qlonglong from = 0;
        qlonglong to   = 0;

        QString line;
        QStringList edges;

        while (!in.atEnd()) {
            line = in.readLine().trimmed();
            edges = line.split(' ');
            for (qlonglong i = 0; i < edges.size(); i++) {
                to = edges.at(i).toLongLong();
                // qDebug() << " edge" << from << to;
                if (to > 0)
                    appendEdge(from, to - 1);
                else
                    qWarning() << "bad edge value at line" << from << "value:"<< edges.at(i) <<"line:" << line;
            }
            from ++;
        }
    // }
    build();

    return true;
}

inline void dtkDistributedGraph::appendEdge(qlonglong from, qlonglong to)
{
    qlonglong edge_counter = m_edge_count->at(this->wid());
    qint32 from_owner = static_cast<qint32>(m_mapper->owner(from));
    qint32 to_owner = static_cast<qint32>(m_mapper->owner(to));
    qint32 wid = this->wid();
    if ((wid != from_owner) && (wid != to_owner))
        return;

    if (wid == from_owner) {
        m_map[from].append(to);
        ++edge_counter;
    }
    if (wid == to_owner) {
        m_map[to].append(from);
        ++edge_counter;
    }
    m_edge_count->setAt(wid, edge_counter);
}

inline qlonglong dtkDistributedGraph::edgeCount(qlonglong vertex_id) const
{
    qlonglong start = m_vertices->at(vertex_id);
    return (m_vertices->at(vertex_id + 1) - start);
}

inline dtkDistributedGraph::Neighbours dtkDistributedGraph::neighbours(const qlonglong& vertex_id) const
{
    qlonglong n_start = m_vertices->at(vertex_id);
    qlonglong size = m_vertices->at(vertex_id + 1) - n_start;

    return Neighbours(m_edges, n_start, size);
}

//
// dtkDistributedGraph.tpp ends here

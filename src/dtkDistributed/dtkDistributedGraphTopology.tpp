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

#include <QtCore>

#if defined(DTK_HAVE_ZLIB)
#include <dtkCore/dtkIOCompressor>
#endif

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraphTopologyVertex inline methods
// /////////////////////////////////////////////////////////////////

inline void dtkDistributedGraphTopologyVertex::init(void)
{
    qlonglong l_id = g->m_neighbour_count->mapper()->globalToLocal(m_id, g->wid());

    c_beg = g->m_neighbour_count->cbegin();
    c_it = c_beg;
    c_it += l_id;
    v_it = g->m_vertex_to_edge->cbegin();
    v_it += l_id;

    if (v_it !=  g->m_vertex_to_edge->cend()) {
        l_id = g->m_edge_to_vertex->mapper()->globalToLocal(*v_it, g->wid());
        n_it = g->m_edge_to_vertex->cbegin();
        n_it += l_id;
    } else {
        n_it = g->m_edge_to_vertex->cend();
    }
    first_pos = g->m_edge_to_vertex->mapper()->firstIndex(g->wid());
}

inline void dtkDistributedGraphTopologyVertex::advance(void)
{
    Q_ASSERT(c_it < g->m_neighbour_count->end());
    n_it += *c_it;
    ++c_it;
    ++v_it;
}

inline void dtkDistributedGraphTopologyVertex::advance(qlonglong j)
{
    Q_ASSERT(c_it + j <= g->m_neighbour_count->end());
    for(qlonglong i = 0; i < j; ++i) {
        n_it += *c_it;
        ++c_it;
        ++v_it;
    }
}

inline void dtkDistributedGraphTopologyVertex::rewind(void)
{
    if (c_it != c_beg) {
        --v_it;
        --c_it;
        n_it -= *c_it;
    } else {
        --v_it;
        --c_it;
    }
}

inline void dtkDistributedGraphTopologyVertex::rewind(qlonglong j)
{
    Q_ASSERT(c_it - j >= g->m_neighbour_count->begin());
    for(qlonglong i = j; i >= 0; --i) {
        this->rewind();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkDistributedGraphTopology inline methods
// /////////////////////////////////////////////////////////////////

inline void dtkDistributedGraphTopology::rlock(void)
{
    m_neighbour_count->rlock();
    m_vertex_to_edge->rlock();
    m_edge_to_vertex->rlock();
}

inline void dtkDistributedGraphTopology::wlock(void)
{
    m_neighbour_count->wlock();
    m_vertex_to_edge->wlock();
    m_edge_to_vertex->wlock();
}

inline void dtkDistributedGraphTopology::unlock(void)
{
    m_neighbour_count->unlock();
    m_vertex_to_edge->unlock();
    m_edge_to_vertex->unlock();
}

inline bool dtkDistributedGraphTopology::isAssembled(void) const
{
    return m_is_assembled;
}

inline qlonglong dtkDistributedGraphTopology::vertexCount(void) const
{
    return this->size();
}

inline qlonglong dtkDistributedGraphTopology::edgeCount(void) const
{
    if (!m_is_assembled) {
        return 0LL;
    }
    return m_edge_to_vertex->size();
}

inline qlonglong dtkDistributedGraphTopology::vertexCount(const qlonglong& wid) const
{
    if (!m_is_assembled) {
        return 0LL;
    }
    return m_vertex_to_edge->mapper()->count(wid);
}

inline qlonglong dtkDistributedGraphTopology::edgeCount(const qlonglong& wid) const
{
    if (!m_is_assembled) {
        return 0LL;
    }

    return m_edge_count->at(wid);
}

inline qlonglong dtkDistributedGraphTopology::neighbourCount(qlonglong vertex_id) const
{
    Q_ASSERT_X(m_is_assembled && vertex_id < m_size, "neighbourCount", "graph is not assembled or 'vertex_id' is not valid.");

    return m_neighbour_count->at(vertex_id);
}

inline dtkDistributedGraphTopology::Neighbours dtkDistributedGraphTopology::operator[](qlonglong vertex_id) const
{
    Q_ASSERT_X(m_is_assembled && vertex_id < m_size, "operator[]", "graph is not assembled or 'vertex_id' is not valid.");

    qlonglong n_start = m_vertex_to_edge->at(vertex_id);
    qlonglong size = m_neighbour_count->at(vertex_id);

    return Neighbours(*m_edge_to_vertex, n_start, size);
}

inline qlonglong dtkDistributedGraphTopology::firstNeighbourPos(qlonglong vertex_id) const
{
    Q_ASSERT_X(m_is_assembled && vertex_id < m_size, "firstNeighbourPos", "graph is not assembled or 'vertex_id' is not valid.");

    return m_vertex_to_edge->at(vertex_id);
}

inline qlonglong dtkDistributedGraphTopology::firstNeighbourId(qlonglong vertex_id) const
{
    Q_ASSERT_X(m_is_assembled && vertex_id < m_size, "firstNeighbourId", "graph is not assembled or 'vertex_id' is not valid.");

    return m_edge_to_vertex->at(m_vertex_to_edge->at(vertex_id));
}

inline dtkDistributedGraphTopology::iterator dtkDistributedGraphTopology::cbegin(void) const
{
    return iterator(*this, this->m_mapper->firstIndex(this->wid()));
}

inline dtkDistributedGraphTopology::iterator dtkDistributedGraphTopology::cend(void) const
{
    return iterator(*this, this->m_mapper->lastIndex(this->wid()) + 1);
}

inline dtkDistributedGraphTopology::iterator dtkDistributedGraphTopology::begin(void) const
{
    return iterator(*this, this->m_mapper->firstIndex(this->wid()));
}

inline dtkDistributedGraphTopology::iterator dtkDistributedGraphTopology::end(void) const
{
    return iterator(*this, this->m_mapper->lastIndex(this->wid()) + 1);
}

inline void dtkDistributedGraphTopology::stats(void) const
{
    qDebug() << m_comm->rank() << "m_vertex_to_edge stats:"; m_vertex_to_edge->stats();
    qDebug() << m_comm->rank() << "m_edge_to_vertex stats:"; m_edge_to_vertex->stats();
}

inline dtkDistributedMapper *dtkDistributedGraphTopology::edgeMapper(void) const
{
    Q_ASSERT_X(m_is_assembled, "edgeMapper", "graph is not yet assembled.");

    return m_edge_to_vertex->mapper();
}

inline bool dtkDistributedGraphTopology::read(const QString& filename, GraphFile format)
{
    dtkDistributedArray<qlonglong> *empty = NULL;
    return readWithValues(filename, format, empty );
}

// read graph from file as described in
// http://people.sc.fsu.edu/~jburkardt/data/metis_graph/metis_graph.html
template <class T> bool dtkDistributedGraphTopology::readWithValues(const QString& filename, GraphFile format, dtkDistributedArray<T> *& values )
{
    this->clear();

    qlonglong vertex_count = 0;

    QFile file(filename);
    qlonglong edges_count = 0;
    QTime time;
    QIODevice *in;
    bool is_double = true;

    if (this->wid() == 0) {
        time.start();

        if(filename.isEmpty() || (!file.exists())) {
            qWarning() << "input file is empty/does not exist" << filename << "Current dir is" << QDir::currentPath();
            return false;
        }

        QIODevice::OpenMode mode = QIODevice::ReadOnly;
        QFileInfo info = QFileInfo(filename);
#if defined(DTK_HAVE_ZLIB)
        if (info.suffix() == "gz") {
            in = new dtkIOCompressor(&file);
        } else {
            in = &file;
            mode |= QIODevice::Text;
        }
#else
        in = &file;
        mode |= QIODevice::Text;
#endif

        // to avoid troubles with floats separators ('.' and not ',')
        QLocale::setDefault(QLocale::c());
#if defined (Q_OS_UNIX) && !defined(Q_OS_MAC)
        setlocale(LC_NUMERIC, "C");
#endif

        if (!in->open(mode))
            return false;

        QStringList header;
        QString datatype;
        QString format_str;
        QRegExp re = QRegExp("\\s+");
        QString line;
        QStringList data;

        switch (format) {
        case  MetisFormat:
        case  MetisDirectedFormat:
            dtkTrace() << "reading metis file header";
            header = QString(in->readLine()).split(re);
            //m_size = header.first().toLongLong();
            vertex_count = header.first().toLongLong();
            //if (m_size  == 0) {
            if (vertex_count  == 0) {
                qWarning() << "Can't parse size of the graph" << filename;
                return false;
            }
            edges_count = header.at(1).toLongLong();
            if (edges_count  == 0) {
                qWarning() << "Can't parse the number of edges" << filename;
                return false;
            }
            if (format == MetisFormat)
                edges_count *= 2;
            break;
        case MatrixMarketFormat:
            dtkTrace() << "reading matrix market file header";
            header = QString(in->readLine()).split(' ');
            // %%MatrixMarket matrix coordinate real general
            if (header.at(1) != "matrix" && header.at(2) != "coordinate")  {
                in->close();
                qWarning() << "not a matrix coordinate format, can't read" << filename;
                return false;
            }
            datatype = header.at(3);
            format_str = header.at(4).trimmed();

            if (datatype  == "integer") {
                is_double = false;
            } else if ((datatype == "complex") || (datatype  == "pattern")) {
                qWarning() << datatype << "Format not supported, can't read matrix" << filename;
                return false;
            }

            if (format_str != "general") {
                qWarning()<< format_str << "Only general format supported, can't read matrix from file" << filename;
                return false;
            }

            //while (m_size == 0) {
            while (vertex_count == 0) {
                line = in->readLine().trimmed();

                if (line.startsWith("%"))
                    continue;
                data = line.split(re);
                //m_size   = data[0].toLongLong();
                vertex_count   = data[0].toLongLong();
                //if (m_size != data[1].toLongLong()) {
                if (vertex_count != data[1].toLongLong()) {
                    dtkError() << "non symetric matrix not supported";
                    return false;
                }
                edges_count = data[2].toLongLong();
            }
            break;
        default:
            dtkError() << "format unknown";
        }
    }

    m_comm->broadcast(&vertex_count, 1, 0);
    m_comm->broadcast(&edges_count, 1, 0);
    dtkTrace() << "Matrix size"<< vertex_count << "edges count" << edges_count << m_comm->wid();

    // Resizing and initialization
    this->resize(vertex_count);
    
    m_comm->barrier();

    m_edge_to_vertex = new dtkDistributedArray<qlonglong>(edges_count);
    m_vertex_to_edge->setAt(m_vertex_to_edge->size() - 1, edges_count);

    if (values) {
        dtkTrace() << "init values vector";
        delete values;
        values = new dtkDistributedArray<T>(edges_count, this->edgeMapper());
    }

    if (this->wid() == 0) {

        qlonglong i,end;
        T value;

        std::string linestd;
        std::string linestd2;
        std::string::size_type sz;

        QString line;
        QStringList edges;

        QVector<qlonglong> n_vec; n_vec.reserve(2 * m_neighbour_count->mapper()->countMax());
        QVector<qlonglong> v_vec; v_vec.reserve(2 * m_vertex_to_edge->mapper()->countMax());
        QVector<qlonglong> e_vec; e_vec.reserve(2 * m_edge_to_vertex->mapper()->countMax());
        QVector<T>         e_val; e_val.reserve(2 * m_edge_to_vertex->mapper()->countMax());

        QVector<qlonglong> e_line_vec;
        QVector<T>         e_line_val;

        qlonglong e_gid = 0;
        qlonglong v_gid = 0;

        qlonglong e_local_count = 0;
        qlonglong edges_size = 0;
        qlonglong val = 0;
        qlonglong owner = 0;
        qlonglong v_first_gid = m_vertex_to_edge->mapper()->firstIndex(owner);
        qlonglong v_last_gid  = m_vertex_to_edge->mapper()->lastIndex(owner);

        qlonglong v_last_line  = 0;

        qlonglong e_first_gid = 0;

        switch (format) {

        case  MatrixMarketFormat:
            dtkTrace() << "read matrix data";
            v_vec << 0;
            while (!in->atEnd()) {
                //linestd = in->readLine().toStdString(); // Works only with Qt5.4
                const QByteArray array = in->readLine();
                linestd = std::string(array.constData(), array.length());
                try {
                    v_gid = std::stoi (linestd, &sz) -1;
                    linestd2 = linestd.substr(sz);
                    val = std::stoi (linestd2, &sz) -1;
                    if (values) {
                        value = (is_double) ? std::stod (linestd2.substr(sz)) : std::stoi (linestd2.substr(sz));
                    }
                    ++e_local_count;
                    ++edges_size;
                    ++e_gid;

                    if(v_gid == v_last_line) {

                       i = 0;
                       end = e_line_vec.size();

                        // sorted insert in e_vec
                        if (i == end) {
                            e_line_vec.prepend(val);
                            if (values) {
                                e_line_val.prepend(value);
                            }
                        } else if (val > e_line_vec.last()) {
                            // tuning: usually, we append at the end, so check this case
                            e_line_vec.append(val);
                            if (values) {
                                e_line_val.append(value);
                            }
                        } else {
                            for(i=0 ; i < end; ++i) {
                                if (val < e_line_vec[i])
                                    break;
                            }
                            e_line_vec.insert(i, val);
                            if (values) {
                                e_line_val.insert(i, value);
                            }
                        }

                        if(in->atEnd()) {
                            e_vec << e_line_vec;
                            e_val << e_line_val;
                            e_line_val.clear();
                            e_line_vec.clear();
                            n_vec << edges_size;

                            m_neighbour_count->setAt(v_first_gid, n_vec.data(), n_vec.size());
                            m_vertex_to_edge->setAt(v_first_gid, v_vec.data(), v_vec.size());
                            m_edge_to_vertex->setAt(e_first_gid, e_vec.data(), e_vec.size());
                            if (values) {
                                values->setAt(e_first_gid, e_val.data(), e_val.size());
                            }
                            m_edge_count->setAt(owner, e_local_count);
                            // qDebug() << owner << v_first_gid << v_last_gid ;
                            // qDebug() << "n_vec" << n_vec  ;
                            // qDebug() << "v_vec" << v_vec  ;
                            // qDebug() << "e_vec" << e_vec  ;
                            // qDebug() << "e_val" << e_val  ;

                        }

                    } else if (v_gid < v_last_line) {
                        qCritical() << "i values should be sorted !, aborting reading of "<< filename <<v_gid << v_last_line;
                        return false;
                    } else { // new vertex

                        //  first, handle  the previous vertex:
                        n_vec << edges_size-1;
                        e_vec << e_line_vec;
                        if (values) {
                            e_val << e_line_val;
                        }

                        // then, handle the first edge of this new vertex:
                        edges_size = 1;
                        e_line_vec.clear();
                        if (values) {
                            e_line_val.clear();
                        }
                        e_line_vec.prepend(val);
                        if (values) {
                            e_line_val.prepend(value);
                        }

                        if(v_gid > v_last_gid) {

                            m_neighbour_count->setAt(v_first_gid, n_vec.data(), n_vec.size());
                            m_vertex_to_edge->setAt(v_first_gid, v_vec.data(), v_vec.size());
                            m_edge_to_vertex->setAt(e_first_gid, e_vec.data(), e_vec.size());
                            m_edge_count->setAt(owner, e_local_count-1);
                            if (values) {
                                values->setAt(e_first_gid, e_val.data(), e_val.size());
                            }

                            // qDebug() << owner << v_first_gid << v_last_gid  ;
                            // qDebug() << "n_vec" << n_vec  ;
                            // qDebug() << "v_vec" << v_vec  ;
                            // qDebug() << "e_vec" << e_vec  ;
                            // qDebug() << "e_val" << e_val  ;

                            ++owner;
                            e_local_count = 1;
                            v_first_gid = v_gid;
                            v_last_gid  = m_vertex_to_edge->mapper()->lastIndex(owner);
                            e_first_gid = e_gid -1;

                            n_vec.clear();
                            n_vec.reserve(2 * m_neighbour_count->mapper()->countMax());
                            v_vec.clear();
                            v_vec.reserve(2 * m_vertex_to_edge->mapper()->countMax());
                            e_vec.clear();
                            e_vec.reserve(2 * m_edge_to_vertex->mapper()->countMax());
                            e_val.clear();
                            e_val.reserve(2 * m_edge_to_vertex->mapper()->countMax());
                            v_vec << e_gid-1;
                        } else {
                            v_vec << e_gid-1;
                        }
                        if(in->atEnd()) {

                            e_vec << e_line_vec;
                            e_val << e_line_val;
                            n_vec << 1;
                            m_neighbour_count->setAt(v_first_gid, n_vec.data(), n_vec.size());
                            m_vertex_to_edge->setAt(v_first_gid, v_vec.data(), v_vec.size());
                            m_edge_to_vertex->setAt(e_first_gid, e_vec.data(), e_vec.size());
                            m_edge_count->setAt(owner, e_local_count);
                            // qDebug() << owner  << v_first_gid << v_last_gid  ;
                            // qDebug() << "n_vec" << n_vec  ;
                            // qDebug() << "v_vec" << v_vec  ;
                            // qDebug() << "e_vec" << e_vec  ;
                            // qDebug() << "e_val" << e_val  ;
                            if (values) {
                                values->setAt(e_first_gid, e_val.data(), e_val.size());
                            }

                        }


                    }
                    v_last_line = v_gid;
                } catch (...) {
                    // qDebug()<< "skip line";
                }
            }
            break;
        case  MetisFormat:
        case  MetisDirectedFormat:
            while (!in->atEnd()) {
                line = in->readLine().trimmed();
                edges = line.split(' ');
                if (line.isEmpty() || line.at(0) == '#'){
                    continue;
                }
                v_vec << e_gid;
                n_vec << edges.size();
                for (qlonglong i = 0; i < edges.size(); ++i) {
                    val = edges.at(i).toLongLong();
                    if (val < 1 || val > m_size ) {
                        qWarning() << "bad vertice id in graph for edge" << val << v_gid;
                        continue;
                    }
                    e_vec << val-1;
                    ++e_gid;
                    ++e_local_count;
                }
                ++v_gid;
                if(in->atEnd()) {
                    v_vec << e_gid;
                    m_neighbour_count->setAt(v_first_gid, n_vec.data(), n_vec.size());
                    m_vertex_to_edge->setAt(v_first_gid, v_vec.data(), v_vec.size());
                    m_edge_to_vertex->setAt(e_first_gid, e_vec.data(), e_vec.size());
                    m_edge_count->setAt(owner, e_local_count);

                } else if(v_gid > v_last_gid) {
                    m_neighbour_count->setAt(v_first_gid, n_vec.data(), n_vec.size());
                    m_vertex_to_edge->setAt(v_first_gid, v_vec.data(), v_vec.size());
                    m_edge_to_vertex->setAt(e_first_gid, e_vec.data(), e_vec.size());
                    m_edge_count->setAt(owner, e_local_count);

                    ++owner;
                    e_local_count = 0;
                    v_first_gid = v_gid;
                    v_last_gid  = m_vertex_to_edge->mapper()->lastIndex(owner);
                    e_first_gid = e_gid;
                    n_vec.clear();
                    n_vec.reserve(2 * m_neighbour_count->mapper()->countMax());
                    v_vec.clear();
                    v_vec.reserve(2 * m_vertex_to_edge->mapper()->countMax());
                    e_vec.clear();
                    e_vec.reserve(2 * m_edge_to_vertex->mapper()->countMax());
                }
            }
            break;
        }
        in->close();
    }
    m_comm->barrier();

    if (this->wid() == 0) {
        qDebug() << "read done in "<< time.elapsed() << "ms";
        time.restart();
    }
    if (m_comm->size() > 1) {
        dtkDistributedMapper *mapper = new dtkDistributedMapper;
        mapper->initMap(edges_count, m_comm->size());

        qlonglong offset = 0;
        for (qlonglong i = 0; i < m_comm->size(); ++i) {
            mapper->setMap(offset ,i);
            offset += m_edge_count->at(i);
        }
        m_edge_to_vertex->remap(mapper);
        if (values) {
            values->remap(mapper);
        }
        if (this->wid() == 0) {
            qDebug() << "remap done in "<< time.elapsed() << "ms";
        }
    }

    m_is_assembled = true;
    m_comm->barrier();

    this->assembleDomainDecompositionFeatures();

    return true;
}

//
// dtkDistributedGraphTopology.tpp ends here

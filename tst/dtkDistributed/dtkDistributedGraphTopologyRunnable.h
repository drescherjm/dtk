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

#include <dtkDistributed>

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// Class to factorize reference graph
// ///////////////////////////////////////////////////////////////////

class neighboursForTest
{
    QMap<qlonglong, QVector<qlonglong> > m_neighbours;
    qlonglong m_count;

public:
    QVector<QMap<qlonglong, QVector<qlonglong> > > m_DD_neighbours;

public:
    neighboursForTest(void);

public:
    qlonglong size(void) const { return m_neighbours.count(); }
    qlonglong edgeCount(void) const { return m_count; }

public:
    qlonglong count(qlonglong v_id) const { return m_neighbours[v_id].count(); }

public:
    QVector<qlonglong> operator[] (qlonglong v_id) const { return m_neighbours[v_id]; }

public:
    void addEdgeToGraph(dtkDistributedGraphTopology& topo);
};

inline neighboursForTest::neighboursForTest(void) : m_count(0)
{
    m_neighbours[0 ] << 1 << 3 << 8 ;
    m_neighbours[1 ] << 0 << 2 << 3 << 4 ;
    m_neighbours[2 ] << 1 << 3 << 4 << 5 << 6 ;
    m_neighbours[3 ] << 0 << 1 << 2 << 6 << 7 << 8 ;
    m_neighbours[4 ] << 1 << 2 << 5 << 9 ;
    m_neighbours[5 ] << 2 << 4 << 6 << 9 << 10;
    m_neighbours[6 ] << 2 << 3 << 5 << 7 << 10 << 14;
    m_neighbours[7 ] << 3 << 6 << 8 << 14 << 20 << 21 << 22;
    m_neighbours[8 ] << 0 << 3 << 7 << 22;
    m_neighbours[9 ] << 4 << 5 << 10 << 11;
    m_neighbours[10] << 5 << 6 << 9 << 11 << 13 << 14;
    m_neighbours[11] << 9 << 10 << 12 << 13;
    m_neighbours[12] << 11 << 13 << 15;
    m_neighbours[13] << 10 << 11 << 12 << 14 << 15 << 17;
    m_neighbours[14] << 6 << 7 << 10 << 13 << 17 << 18 << 20;
    m_neighbours[15] << 12 << 13 << 16 << 17;
    m_neighbours[16] << 15 << 17 << 19;
    m_neighbours[17] << 13 << 14 << 15 << 16 << 18 << 19;
    m_neighbours[18] << 14 << 17 << 19 << 20;
    m_neighbours[19] << 16 << 17 << 18 << 20 << 21;
    m_neighbours[20] << 7 << 14 << 18 << 19 << 21;
    m_neighbours[21] << 7 << 19 << 20 << 22;
    m_neighbours[22] << 7 << 8 << 21;

    for(int i = 0; i < m_neighbours.count(); ++i)
        m_count += m_neighbours[i].count();

    m_DD_neighbours.resize(4);

    m_DD_neighbours[0][0 ] << 1 ;
    m_DD_neighbours[0][0 ] << 3 ;
    m_DD_neighbours[0][0 ] << 8 ;
    m_DD_neighbours[0][1 ] << 0 ;
    m_DD_neighbours[0][1 ] << 2 ;
    m_DD_neighbours[0][1 ] << 3 ;
    m_DD_neighbours[0][1 ] << 4 ;
    m_DD_neighbours[0][2 ] << 1 ;
    m_DD_neighbours[0][2 ] << 3 ;
    m_DD_neighbours[0][2 ] << 4 ;
    m_DD_neighbours[0][2 ] << 5 ;
    m_DD_neighbours[0][2 ] << 6 ;
    m_DD_neighbours[0][3 ] << 0 ;
    m_DD_neighbours[0][3 ] << 1 ;
    m_DD_neighbours[0][3 ] << 2 ;
    m_DD_neighbours[0][3 ] << 6 ;
    m_DD_neighbours[0][3 ] << 7 ;
    m_DD_neighbours[0][3 ] << 8 ;
    m_DD_neighbours[0][4 ] << 1 ;
    m_DD_neighbours[0][4 ] << 2 ;
    m_DD_neighbours[0][4 ] << 5 ;
    m_DD_neighbours[1][4 ] << 5 ;
    m_DD_neighbours[1][4 ] << 9 ;
    m_DD_neighbours[0][5 ] << 2 ;
    m_DD_neighbours[0][5 ] << 4 ;
    m_DD_neighbours[1][5 ] << 4 ;
    m_DD_neighbours[0][5 ] << 6 ;
    m_DD_neighbours[1][5 ] << 6 ;
    m_DD_neighbours[1][5 ] << 9 ;
    m_DD_neighbours[1][5 ] << 10;
    m_DD_neighbours[0][6 ] << 2 ;
    m_DD_neighbours[0][6 ] << 3 ;
    m_DD_neighbours[0][6 ] << 5 ;
    m_DD_neighbours[1][6 ] << 5 ;
    m_DD_neighbours[0][6 ] << 7 ;
    m_DD_neighbours[3][6 ] << 7 ;
    m_DD_neighbours[1][6 ] << 10;
    m_DD_neighbours[1][6 ] << 14;
    m_DD_neighbours[3][6 ] << 14;
    m_DD_neighbours[0][7 ] << 3 ;
    m_DD_neighbours[0][7 ] << 6 ;
    m_DD_neighbours[3][7 ] << 6 ;
    m_DD_neighbours[0][7 ] << 8 ;
    m_DD_neighbours[3][7 ] << 8 ;
    m_DD_neighbours[3][7 ] << 14;
    m_DD_neighbours[3][7 ] << 20;
    m_DD_neighbours[3][7 ] << 21;
    m_DD_neighbours[3][7 ] << 22;
    m_DD_neighbours[0][8 ] << 0 ;
    m_DD_neighbours[0][8 ] << 3 ;
    m_DD_neighbours[0][8 ] << 7 ;
    m_DD_neighbours[3][8 ] << 7 ;
    m_DD_neighbours[3][8 ] << 22;

    m_DD_neighbours[1][9 ] << 4 ;
    m_DD_neighbours[1][9 ] << 5 ;
    m_DD_neighbours[1][9 ] << 10;
    m_DD_neighbours[1][9 ] << 11;
    m_DD_neighbours[1][10] << 5 ;
    m_DD_neighbours[1][10] << 6 ;
    m_DD_neighbours[1][10] << 9 ;
    m_DD_neighbours[1][10] << 11;
    m_DD_neighbours[1][10] << 13;
    m_DD_neighbours[1][10] << 14;
    m_DD_neighbours[1][11] << 9 ;
    m_DD_neighbours[1][11] << 10;
    m_DD_neighbours[1][11] << 12;
    m_DD_neighbours[1][11] << 13;
    m_DD_neighbours[1][12] << 11;
    m_DD_neighbours[1][12] << 13;
    m_DD_neighbours[2][12] << 13;
    m_DD_neighbours[2][12] << 15;
    m_DD_neighbours[1][13] << 10;
    m_DD_neighbours[1][13] << 11;
    m_DD_neighbours[1][13] << 12;
    m_DD_neighbours[2][13] << 12;
    m_DD_neighbours[1][13] << 14;
    m_DD_neighbours[2][13] << 14;
    m_DD_neighbours[2][13] << 15;
    m_DD_neighbours[2][13] << 17;
    m_DD_neighbours[1][14] << 6 ;
    m_DD_neighbours[3][14] << 6 ;
    m_DD_neighbours[3][14] << 7 ;
    m_DD_neighbours[1][14] << 10;
    m_DD_neighbours[1][14] << 13;
    m_DD_neighbours[2][14] << 13;
    m_DD_neighbours[2][14] << 17;
    m_DD_neighbours[2][14] << 18;
    m_DD_neighbours[3][14] << 18;
    m_DD_neighbours[3][14] << 20;

    m_DD_neighbours[2][15] << 12;
    m_DD_neighbours[2][15] << 13;
    m_DD_neighbours[2][15] << 16;
    m_DD_neighbours[2][15] << 17;
    m_DD_neighbours[2][16] << 15;
    m_DD_neighbours[2][16] << 17;
    m_DD_neighbours[2][16] << 19;
    m_DD_neighbours[2][17] << 13;
    m_DD_neighbours[2][17] << 14;
    m_DD_neighbours[2][17] << 15;
    m_DD_neighbours[2][17] << 16;
    m_DD_neighbours[2][17] << 18;
    m_DD_neighbours[2][17] << 19;
    m_DD_neighbours[2][18] << 14;
    m_DD_neighbours[3][18] << 14;
    m_DD_neighbours[2][18] << 17;
    m_DD_neighbours[2][18] << 19;
    m_DD_neighbours[3][18] << 19;
    m_DD_neighbours[3][18] << 20;
    m_DD_neighbours[2][19] << 16;
    m_DD_neighbours[2][19] << 17;
    m_DD_neighbours[2][19] << 18;
    m_DD_neighbours[3][19] << 18;
    m_DD_neighbours[3][19] << 20;
    m_DD_neighbours[3][19] << 21;

    m_DD_neighbours[3][20] << 7 ;
    m_DD_neighbours[3][20] << 14;
    m_DD_neighbours[3][20] << 18;
    m_DD_neighbours[3][20] << 19;
    m_DD_neighbours[3][20] << 21;
    m_DD_neighbours[3][21] << 7 ;
    m_DD_neighbours[3][21] << 19;
    m_DD_neighbours[3][21] << 20;
    m_DD_neighbours[3][21] << 22;
    m_DD_neighbours[3][22] << 7 ;
    m_DD_neighbours[3][22] << 8 ;
    m_DD_neighbours[3][22] << 21;
}

inline void neighboursForTest::addEdgeToGraph(dtkDistributedGraphTopology& topo)
{
    dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
    if (comm->size() != 4 ) {
        qWarning() << "bad communicator size, should be equal to 4"  ;
        return;
    }
    /* qlonglong start = 0; */
    /* qlonglong end   = 9; */
    /* if (comm->wid() == 1 ) { */
    /*     start = 9; */
    /*     end   = 15; */
    /* } else if (comm->wid() == 2 ) { */
    /*     start = 15; */
    /*     end   = 20; */
    /* } else if (comm->wid() == 3 ) { */
    /*     start = 20; */
    /*     end   = 23; */
    /* } */

    const QMap<qlonglong, QVector<qlonglong> >& local_fe_neighbours = m_DD_neighbours[comm->wid()];

    auto it  = local_fe_neighbours.cbegin();
    auto ite = local_fe_neighbours.cend();
    for(; it != ite; ++it) {
        qlonglong i = it.key();
        const QVector<qlonglong>& n = *it;
        for (int j = 0; j < n.count(); ++j) {
            topo.addEdge(i, n[j]);
        }
    }
}

// ///////////////////////////////////////////////////////////////////
// Tests
// ///////////////////////////////////////////////////////////////////

class testGraphTopologyCreateDestroy: public QRunnable
{
public:
    void run(void)
    {
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong wid = comm->wid();

        dtkDistributedGraphTopology *topo = new dtkDistributedGraphTopology;
        QVERIFY(!topo->isAssembled());
        QVERIFY(topo->empty());
        QVERIFY(topo->empty());
        QCOMPARE(topo->size(), 0LL);
        QCOMPARE(topo->vertexCount(), 0LL);
        QCOMPARE(topo->edgeCount(), 0LL);
        QCOMPARE(topo->vertexCount(wid), 0LL);
        QCOMPARE(topo->edgeCount(wid), 0LL);
        delete topo;

        qlonglong N = 101;
        topo = new dtkDistributedGraphTopology(N);
        QVERIFY(!topo->empty());
        QVERIFY(!topo->isAssembled());
        QCOMPARE(topo->size(), N);
        QCOMPARE(topo->vertexCount(), N);
        QCOMPARE(topo->edgeCount(), 0LL);
        QCOMPARE(topo->vertexCount(wid), 0LL);
        QCOMPARE(topo->edgeCount(wid), 0LL);
        delete topo;
    }
};

class testGraphTopologyClearResize: public QRunnable
{
public:
    void run(void)
    {
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong wid = comm->wid();
        qlonglong N = 101;

        dtkDistributedGraphTopology *topo = new dtkDistributedGraphTopology(N);
        topo->clear();

        QVERIFY(topo->empty());
        QVERIFY(!topo->isAssembled());
        QCOMPARE(topo->size(), 0LL);
        QCOMPARE(topo->vertexCount(), 0LL);
        QCOMPARE(topo->edgeCount(), 0LL);
        QCOMPARE(topo->vertexCount(wid), 0LL);
        QCOMPARE(topo->edgeCount(wid), 0LL);

        topo->resize(N);

        QVERIFY(!topo->empty());
        QVERIFY(!topo->isAssembled());
        QCOMPARE(topo->size(), N);
        QCOMPARE(topo->vertexCount(), N);
        QCOMPARE(topo->edgeCount(), 0LL);
        QCOMPARE(topo->vertexCount(wid), 0LL);
        QCOMPARE(topo->edgeCount(wid), 0LL);

        delete topo;
    }
};

class testGraphTopologyAssemble: public QRunnable
{
public:
    void run(void)
    {
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong wid = comm->wid();
        qlonglong N = 23;

        dtkDistributedMapper *m = new dtkDistributedMapper;
        QCOMPARE(comm->size(), 4);
        m->initMap(N, comm->size());
        m->setMap( 0, 0);
        m->setMap( 9, 1);
        m->setMap(15, 2);
        m->setMap(20, 3);

        dtkDistributedGraphTopology topo(N, m);

        neighboursForTest neighbours;
        neighbours.addEdgeToGraph(topo);

        topo.assemble();

        if (wid == 0) {
            for(qlonglong i = 0; i < topo.size(); ++i) {
                QCOMPARE(topo.neighbourCount(i), neighbours.count(i));
            }
            qlonglong count = 0;
            for(qlonglong i = 0; i < topo.size(); ++i) {
                dtkDistributedGraphTopology::Neighbours n = topo[i];
                QCOMPARE(n.size(), neighbours.count(i));
                QCOMPARE(n.startIndex(), count);
                count += n.size();
            }
        }
    }
};

class testGraphTopologyNeighbours: public QRunnable
{
public:
    void run(void)
    {
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong wid = comm->wid();
        qlonglong N = 23;

        dtkDistributedMapper *m = new dtkDistributedMapper;
        m->initMap(N, comm->size());
        m->setMap( 0, 0);
        m->setMap( 9, 1);
        m->setMap(15, 2);
        m->setMap(20, 3);

        dtkDistributedGraphTopology topo(N, m);

        neighboursForTest neighbours;
        neighbours.addEdgeToGraph(topo);

        topo.assemble();

        if (wid == 0) {
            for(qlonglong i = 0; i < topo.size(); ++i) {
                QCOMPARE(topo.neighbourCount(i), neighbours.count(i));
            }
            qlonglong count = 0;
            for(qlonglong i = 0; i < topo.size(); ++i) {
                dtkDistributedGraphTopology::Neighbours n = topo[i];
                QCOMPARE(n.size(), neighbours.count(i));
                QCOMPARE(n.startIndex(), count);
                count += n.size();
            }
        }
    }
};

class testGraphTopologyIterator: public QRunnable
{
public:
    void run(void)
    {
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong N = 23;

        dtkDistributedMapper *m = new dtkDistributedMapper;
        m->initMap(N, comm->size());
        m->setMap( 0, 0);
        m->setMap( 9, 1);
        m->setMap(15, 2);
        m->setMap(20, 3);

        dtkDistributedGraphTopology topo(N, m);

        neighboursForTest neighbours;
        neighbours.addEdgeToGraph(topo);

        topo.assemble();

        dtkDistributedGraphTopology::iterator it  = topo.begin();
        dtkDistributedGraphTopology::iterator end = topo.end();

        for (; it != end; ++it) {
            QCOMPARE((*it).size(), neighbours.count(it.id()));

            dtkDistributedGraphTopology::Neighbours::iterator nit  = (*it).begin();
            dtkDistributedGraphTopology::Neighbours::iterator nend = (*it).end();

            for(int i = 0; nit != nend; ++nit, ++i) {
                QCOMPARE(*nit, neighbours[it.id()][i]);
            }
        }
    }
};

class testGraphTopologyRead: public QRunnable
{
public:
    void run(void)
    {
        dtkDistributedGraphTopology topo;
        qDebug() << topo.mapper()->deref() << topo.mapper()->ref();
        QVERIFY(topo.read("../customGraph.graph"));

        neighboursForTest neighbours;

        dtkDistributedGraphTopology::iterator it  = topo.begin();
        dtkDistributedGraphTopology::iterator end = topo.end();

        for (; it != end; ++it) {
            QCOMPARE((*it).size(), neighbours.count(it.id()));

            dtkDistributedGraphTopology::Neighbours::iterator nit  = (*it).begin();
            dtkDistributedGraphTopology::Neighbours::iterator nend = (*it).end();

            for(int i = 0; nit != nend; ++nit, ++i) {
                QCOMPARE(*nit, neighbours[it.id()][i]);
            }
        }
    }
};

class testGraphTopologyLock: public QRunnable
{
public:
    void run(void)
    {
        dtkDistributedGraphTopology topo;
        QVERIFY(topo.read("../customGraph.graph"));

        neighboursForTest neighbours;

        dtkDistributedGraphTopology::iterator it  = topo.begin();
        dtkDistributedGraphTopology::iterator end = topo.end();

        topo.rlock();

        for (; it != end; ++it) {
            QCOMPARE((*it).size(), neighbours.count(it.id()));

            dtkDistributedGraphTopology::Neighbours::iterator nit  = (*it).begin();
            dtkDistributedGraphTopology::Neighbours::iterator nend = (*it).end();

            for(int i = 0; nit != nend; ++nit, ++i) {
                QCOMPARE(*nit, neighbours[it.id()][i]);
            }
        }

        topo.unlock();
    }
};

class testGraphTopologyVertex: public QRunnable
{
public:
    void run(void)
    {
        dtkDistributedGraphTopology topo;
        QVERIFY(topo.read("../customGraph.graph"));

        neighboursForTest neighbours;

        dtkDistributedGraphTopology::vertex v_it  = topo.beginVertex();
        //dtkDistributedGraphTopology::vertex v_end = topo.endVertex();
        
        //qDebug() << topo[18].size() << topo.neighbourCount(18);

        // for (; v_it != v_end; ++v_it) {
        //     //qDebug() << topo.wid() << v_it.id() << v_it.neighbourCount();
        //     QCOMPARE(v_it.neighbourCount(), neighbours.count(v_it.id()));

        //     dtkDistributedArray<qlonglong>::const_iterator nit  = v_it.begin();
        //     dtkDistributedArray<qlonglong>::const_iterator nend = v_it.end();

        //     for(int i = 0; nit != nend; ++nit, ++i) {
        //         QCOMPARE(*nit, neighbours[v_it.id()][i]);
        //     }
        // }
    }
};

//
// dtkDistributedArrayRunnable.h ends here

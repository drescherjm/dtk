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
    QMap<qlonglong, QVector<qlonglong> > m_neighbours2;
    qlonglong m_count;

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
    void addEdgeToGraph(dtkDistributedGraphTopology& topo) const;
    void addEdgeToGraphRemote(dtkDistributedGraphTopology& topo) const;
};

class neighboursRemoteForTest
{
    QMap<qlonglong, QVector<qlonglong> > m_neighbours;
    qlonglong m_count;

public:
    neighboursRemoteForTest(void);

public:
    qlonglong size(void) const { return m_neighbours.count(); }
    qlonglong edgeCount(void) const { return m_count; }
    
public:
    qlonglong count(qlonglong v_id) const { return m_neighbours[v_id].count(); }

public:
    QVector<qlonglong> operator[] (qlonglong v_id) const { return m_neighbours[v_id]; }

public:
    void addEdgeToGraphRemote(dtkDistributedGraphTopology& topo) ;
};

inline neighboursForTest::neighboursForTest(void) : m_count(0)
{    
    m_neighbours[0 ] << 1 ; m_neighbours[1 ] << 0 ; 
    m_neighbours[0 ] << 12; m_neighbours[12] << 0 ;
    m_neighbours[0 ] << 13; m_neighbours[13] << 0 ;
    m_neighbours[1 ] << 2 ; m_neighbours[2 ] << 1 ;
    m_neighbours[1 ] << 12; m_neighbours[12] << 1 ;
    m_neighbours[2 ] << 3 ; m_neighbours[3 ] << 2 ;
    m_neighbours[2 ] << 10; m_neighbours[10] << 2 ;
    m_neighbours[2 ] << 11; m_neighbours[11] << 2 ;
    m_neighbours[2 ] << 12; m_neighbours[12] << 2 ;
    m_neighbours[3 ] << 4 ; m_neighbours[4 ] << 3 ;
    m_neighbours[3 ] << 10; m_neighbours[10] << 3 ;
    m_neighbours[4 ] << 5 ; m_neighbours[5 ] << 4 ;
    m_neighbours[4 ] << 8 ; m_neighbours[8 ] << 4 ;
    m_neighbours[4 ] << 9 ; m_neighbours[9 ] << 4 ;
    m_neighbours[4 ] << 10; m_neighbours[10] << 4 ;
    m_neighbours[5 ] << 6 ; m_neighbours[6 ] << 5 ;
    m_neighbours[5 ] << 8 ; m_neighbours[8 ] << 5 ;
    m_neighbours[6 ] << 7 ; m_neighbours[7 ] << 6 ;
    m_neighbours[6 ] << 8 ; m_neighbours[8 ] << 6 ;
    m_neighbours[7 ] << 8 ; m_neighbours[8 ] << 7 ;
    m_neighbours[7 ] << 20; m_neighbours[20] << 7 ;
    m_neighbours[8 ] << 9 ; m_neighbours[9 ] << 8 ;
    m_neighbours[8 ] << 19; m_neighbours[19] << 8 ;
    m_neighbours[8 ] << 20; m_neighbours[20] << 8 ;
    m_neighbours[9 ] << 10; m_neighbours[10] << 9 ;
    m_neighbours[9 ] << 18; m_neighbours[18] << 9 ;
    m_neighbours[9 ] << 19; m_neighbours[19] << 9 ;
    m_neighbours[10] << 11; m_neighbours[11] << 10;
    m_neighbours[10] << 17; m_neighbours[17] << 10;
    m_neighbours[10] << 18; m_neighbours[18] << 10;
    m_neighbours[11] << 12; m_neighbours[12] << 11;
    m_neighbours[11] << 16; m_neighbours[16] << 11;
    m_neighbours[11] << 17; m_neighbours[17] << 11;
    m_neighbours[12] << 13; m_neighbours[13] << 12;
    m_neighbours[12] << 15; m_neighbours[15] << 12;
    m_neighbours[12] << 16; m_neighbours[16] << 12;
    m_neighbours[13] << 14; m_neighbours[14] << 13;
    m_neighbours[13] << 15; m_neighbours[15] << 13;
    m_neighbours[14] << 15; m_neighbours[15] << 14;
    m_neighbours[14] << 26; m_neighbours[26] << 14;
    m_neighbours[14] << 27; m_neighbours[27] << 14;
    m_neighbours[15] << 16; m_neighbours[16] << 15;
    m_neighbours[15] << 25; m_neighbours[25] << 15;
    m_neighbours[15] << 26; m_neighbours[26] << 15;
    m_neighbours[15] << 28; m_neighbours[28] << 15;
    m_neighbours[16] << 17; m_neighbours[17] << 16;
    m_neighbours[16] << 23; m_neighbours[23] << 16;
    m_neighbours[16] << 24; m_neighbours[24] << 16;
    m_neighbours[16] << 25; m_neighbours[25] << 16;
    m_neighbours[17] << 18; m_neighbours[18] << 17;
    m_neighbours[17] << 22; m_neighbours[22] << 17;
    m_neighbours[17] << 23; m_neighbours[23] << 17;
    m_neighbours[18] << 19; m_neighbours[19] << 18;
    m_neighbours[18] << 21; m_neighbours[21] << 18;
    m_neighbours[18] << 22; m_neighbours[22] << 18;
    m_neighbours[19] << 20; m_neighbours[20] << 19;
    m_neighbours[19] << 21; m_neighbours[21] << 19;
    m_neighbours[20] << 21; m_neighbours[21] << 20;
    m_neighbours[20] << 30; m_neighbours[30] << 20;
    m_neighbours[21] << 22; m_neighbours[22] << 21;
    m_neighbours[21] << 30; m_neighbours[30] << 21;
    m_neighbours[22] << 23; m_neighbours[23] << 22;
    m_neighbours[22] << 24; m_neighbours[24] << 22;
    m_neighbours[22] << 29; m_neighbours[29] << 22;
    m_neighbours[22] << 30; m_neighbours[30] << 22;
    m_neighbours[23] << 24; m_neighbours[24] << 23;
    m_neighbours[24] << 25; m_neighbours[25] << 24;
    m_neighbours[24] << 28; m_neighbours[28] << 24;
    m_neighbours[24] << 29; m_neighbours[29] << 24;
    m_neighbours[25] << 28; m_neighbours[28] << 25;
    m_neighbours[26] << 27; m_neighbours[27] << 26;
    m_neighbours[26] << 28; m_neighbours[28] << 26;
    m_neighbours[27] << 28; m_neighbours[28] << 27;
    m_neighbours[28] << 29; m_neighbours[29] << 28;
    m_neighbours[29] << 30; m_neighbours[30] << 29;

    for(int i = 0; i < m_neighbours.count(); ++i) 
        m_count += m_neighbours[i].count();
}

inline neighboursRemoteForTest::neighboursRemoteForTest(void) : m_count(0)
{

    m_neighbours[0 ] << 1 ;
    m_neighbours[0 ] << 3 ;
    m_neighbours[0 ] << 8 ;
    m_neighbours[1 ] << 0 ;
    m_neighbours[1 ] << 2 ;
    m_neighbours[1 ] << 3 ;
    m_neighbours[1 ] << 4 ;
    m_neighbours[2 ] << 1 ;
    m_neighbours[2 ] << 3 ;
    m_neighbours[2 ] << 4 ;
    m_neighbours[2 ] << 5 ;
    m_neighbours[2 ] << 6 ;
    m_neighbours[3 ] << 0 ;
    m_neighbours[3 ] << 1 ;
    m_neighbours[3 ] << 2 ;
    m_neighbours[3 ] << 6 ;
    m_neighbours[3 ] << 7 ;
    m_neighbours[3 ] << 8 ;
    m_neighbours[4 ] << 1 ;
    m_neighbours[4 ] << 2 ;
    m_neighbours[4 ] << 5 ;
    m_neighbours[4 ] << 9 ;
    m_neighbours[5 ] << 2 ;
    m_neighbours[5 ] << 4 ;
    m_neighbours[5 ] << 6 ;
    m_neighbours[5 ] << 9 ;
    m_neighbours[5 ] << 10;
    m_neighbours[6 ] << 2 ;
    m_neighbours[6 ] << 3 ;
    m_neighbours[6 ] << 5 ;
    m_neighbours[6 ] << 7 ;
    m_neighbours[6 ] << 10;
    m_neighbours[6 ] << 14;
    m_neighbours[7 ] << 3 ;
    m_neighbours[7 ] << 6 ;
    m_neighbours[7 ] << 8 ;
    /* m_neighbours[7 ] << 14; */
    m_neighbours[7 ] << 20;
    m_neighbours[7 ] << 21;
    m_neighbours[7 ] << 22;
    m_neighbours[8 ] << 0 ;
    m_neighbours[8 ] << 3 ;
    m_neighbours[8 ] << 7 ;
    m_neighbours[8 ] << 22;
    m_neighbours[9 ] << 4 ;
    m_neighbours[9 ] << 5 ;
    m_neighbours[9 ] << 10;
    m_neighbours[9 ] << 11;
    m_neighbours[10] << 5 ;
    m_neighbours[10] << 6 ;
    m_neighbours[10] << 9 ;
    m_neighbours[10] << 11;
    m_neighbours[10] << 13;
    m_neighbours[10] << 14;
    m_neighbours[11] << 9 ;
    m_neighbours[11] << 10;
    m_neighbours[11] << 12;
    m_neighbours[11] << 13;
    m_neighbours[12] << 11;
    m_neighbours[12] << 13;
    m_neighbours[12] << 15;
    m_neighbours[13] << 10;
    m_neighbours[13] << 11;
    m_neighbours[13] << 12;
    m_neighbours[13] << 14;
    m_neighbours[13] << 15;
    m_neighbours[13] << 17;
    m_neighbours[14] << 6 ;
    /* m_neighbours[14] << 7 ; */
    m_neighbours[14] << 10;
    m_neighbours[14] << 13;
    m_neighbours[14] << 17;
    m_neighbours[14] << 18;
    m_neighbours[14] << 20;
    m_neighbours[15] << 12;
    m_neighbours[15] << 13;
    m_neighbours[15] << 16;
    m_neighbours[15] << 17;
    m_neighbours[16] << 15;
    m_neighbours[16] << 17;
    m_neighbours[16] << 19;
    m_neighbours[17] << 13;
    m_neighbours[17] << 14;
    m_neighbours[17] << 15;
    m_neighbours[17] << 16;
    m_neighbours[17] << 18;
    m_neighbours[17] << 19;
    m_neighbours[18] << 14;
    m_neighbours[18] << 17;
    m_neighbours[18] << 19;
    m_neighbours[18] << 20;
    m_neighbours[19] << 16;
    m_neighbours[19] << 17;
    m_neighbours[19] << 18;
    m_neighbours[19] << 20;
    m_neighbours[19] << 21;
    m_neighbours[20] << 7 ;
    m_neighbours[20] << 14;
    m_neighbours[20] << 18;
    m_neighbours[20] << 19;
    m_neighbours[20] << 21;
    m_neighbours[21] << 7 ;
    m_neighbours[21] << 19;
    m_neighbours[21] << 20;
    m_neighbours[21] << 22;
    m_neighbours[22] << 7 ;
    m_neighbours[22] << 8 ;
    m_neighbours[22] << 21;

    for(int i = 0; i < m_neighbours.count(); ++i)
        m_count += m_neighbours[i].count();

}

inline void neighboursRemoteForTest::addEdgeToGraphRemote(dtkDistributedGraphTopology& topo)
{
    dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
    if (comm->size() != 4 ) {
        qWarning() << "bad communicator size, should be equal to 4"  ;
        return;
    }
    qlonglong start = 0;
    qlonglong end   = 9;
    if (comm->wid() == 1 ) {
        start = 9;
        end   = 15;
    } else if (comm->wid() == 2 ) {
        start = 15;
        end   = 20;
    } else if (comm->wid() == 3 ) {
        start = 20;
        end   = 23;
        topo.addGlobalEdge(7, 14);
        topo.addGlobalEdge(14, 7);
    }

    for (qlonglong i = start; i < end; ++i) {
        const QVector<qlonglong>& n = m_neighbours[i];
        for (int j = 0; j < n.count(); ++j) {
            topo.addGlobalEdge(i, n[j]);
        }
    }
     m_neighbours[7] << 14;
     m_neighbours[14] << 7;
     m_count += 2;

}


inline void neighboursForTest::addEdgeToGraph(dtkDistributedGraphTopology& topo) const
{
    for (qlonglong i = 0; i < m_neighbours.count(); ++i) {
        const QVector<qlonglong>& n = m_neighbours[i];
        for (int j = 0; j < n.count(); ++j) {
            if (i < n[j])
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
        qlonglong N = 0;

        dtkDistributedGraphTopology *topo = new dtkDistributedGraphTopology;
        QVERIFY(topo->empty());
        QCOMPARE(topo->size(), N);
        QCOMPARE(topo->vertexCount(), N);
        QCOMPARE(topo->edgeCount(), N);
        QCOMPARE(topo->vertexCount(wid), N);
        QCOMPARE(topo->edgeCount(wid), N);
        delete topo;

        N = 101;
        topo = new dtkDistributedGraphTopology(N);
        QVERIFY(!topo->empty());
        QCOMPARE(topo->size(), N);
        QCOMPARE(topo->vertexCount(), N);
        QCOMPARE(topo->edgeCount(), (qlonglong)(0));
        QVERIFY(topo->vertexCount(wid) != (qlonglong)(0));
        QCOMPARE(topo->edgeCount(wid), (qlonglong)(0));
        delete topo;
    }
};

class testGraphTopologyAddEdge: public QRunnable
{
public:
    void run(void)
    {
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong wid = comm->wid();
        qlonglong N = 31;

        dtkDistributedGraphTopology topo(N);

        neighboursForTest neighbours;
        neighbours.addEdgeToGraph(topo);

        comm->barrier();

        QCOMPARE(topo.edgeCount(), neighbours.edgeCount());
        QVERIFY(topo.edgeCount(wid) != (qlonglong)(0));
    }
};

class testGraphTopologyAddEdgeRemote: public QRunnable
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

        neighboursRemoteForTest neighbours;
        neighbours.addEdgeToGraphRemote(topo);

        topo.build();

        if (dtkDistributed::app()->communicator()->wid() == 0) {
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

class testGraphTopologyBuild: public QRunnable
{
public:
    void run(void)
    {
        qlonglong N = 31;
        dtkDistributedGraphTopology topo(N);

        neighboursForTest neighbours;
        neighbours.addEdgeToGraph(topo);

        topo.build();

    }
};

class testGraphTopologyNeighbours: public QRunnable
{
public:
    void run(void)
    {
        qlonglong N = 31;
        dtkDistributedGraphTopology topo(N);

        neighboursForTest neighbours;
        neighbours.addEdgeToGraph(topo);

        topo.build();

        if (dtkDistributed::app()->communicator()->wid() == 0) {
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
        qlonglong N = 31;
        dtkDistributedGraphTopology topo(N);

        neighboursForTest neighbours;
        neighbours.addEdgeToGraph(topo);
        
        topo.build();

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
        dtkDistributedGraphTopology::vertex v_end = topo.endVertex();

        for (; v_it != v_end; ++v_it) {
            QCOMPARE(v_it.neighbourCount(), neighbours.count(v_it.id()));

            dtkDistributedArray<qlonglong>::const_iterator nit  = v_it.begin();
            dtkDistributedArray<qlonglong>::const_iterator nend = v_it.end();
    
            for(int i = 0; nit != nend; ++nit, ++i) {
                QCOMPARE(*nit, neighbours[v_it.id()][i]);
            }
        }
    }
};

//
// dtkDistributedArrayRunnable.h ends here

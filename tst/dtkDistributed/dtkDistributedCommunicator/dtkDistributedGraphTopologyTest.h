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

#include <dtkTest>

class dtkDistributedGraphTopologyTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testCreateDestroy(void);
    void testAddEdge(void);
    void testAddEdgeRemote(void);
    void testAddEdgeFEM(void);
    void testBuild(void);
    void testNeighbours(void);
    void testIterator(void);
    void testRead(void);
    void testLock(void);
    void testVertex(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);

};

//
// dtkDistributedGraphTopologyTest.h ends here

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

class dtkDistributedBufferManagerTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testCreateDestroy(void);
    void testAllocateDeallocate(void);
    void testLocks(void);
    void testAdd(void);
    void testSub(void);
    void testMul(void);
    void testDiv(void);
    void testPut(void);
    void testGet(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);

};

//
// dtkDistributedBufferManagerTest.h ends here

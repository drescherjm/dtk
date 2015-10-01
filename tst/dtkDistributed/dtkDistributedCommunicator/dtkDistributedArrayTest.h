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

class dtkDistributedArrayTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testCreateDestroy(void);
    void testAtFirstLast(void);
    void testFill(void);
    void testSwap(void);
    void testOperatorGet(void);
    void testSetAt(void);
    void testIterator(void);
    void testRemap(void);
    void testCopyIntoArray(void);
    void testToNavigator(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);

};

// 
// dtkDistributedArrayTest.h ends here

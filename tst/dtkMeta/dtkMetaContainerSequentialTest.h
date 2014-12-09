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

// ///////////////////////////////////////////////////////////////////

class dtkMetaContainerSequentialTestCase : public QObject
{
    Q_OBJECT

public:
             dtkMetaContainerSequentialTestCase(void);
    virtual ~dtkMetaContainerSequentialTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testConversion(void);
    void testBasics(void);
    void testQList(void);
    void testQVector(void);
    void testQVarLengthArray(void);
    void testStdList(void);
    void testStdVector(void);

private slots:
    void testBenchVec(void);
    void testBenchMetaItemAt(void);
    void testBenchMetaVariantAt(void);
    void testBenchMetaConstIterators(void);
    void testBenchMetaIterators(void);
    void testBenchMetaIteratorsDirect(void);
    void testBenchMetaOperatorConst(void);
    void testBenchMetaOperator(void);
    void testBenchMetaRangeLoopConst(void);
    void testBenchMetaRangeLoop(void);

private slots:
    void testBenchVecSetAt(void);
    void testBenchMetaSetAt(void);
    void testBenchMetaSetAtIterator(void);
    void testBenchMetaSetAtOperator(void);
    void testBenchMetaSetAtRange(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};

//
// dtkMetaContainerSequentialTest.h ends here

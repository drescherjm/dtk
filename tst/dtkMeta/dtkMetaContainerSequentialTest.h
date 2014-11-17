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
    void testQList(void);
    void testQVector(void);
    void testQVarLengthArray(void);
    void testStdList(void);
    void testStdVector(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};

//
// dtkMetaContainerSequentialTest.h ends here

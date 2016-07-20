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

class dtkComposerTransmitterTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testAtomicType(void);
    void testComplexType(void);
    void testLinks(void);
    void testProxyLoop(void);
    void testProxyVariant(void);
    void testSwapPointer(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};

//
// dtkComposerTransmitterTest.h ends here

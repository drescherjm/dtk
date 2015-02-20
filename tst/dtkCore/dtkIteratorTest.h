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

class dtkIteratorTestCasePrivate;

class dtkIteratorTestCase : public QObject
{
    Q_OBJECT

public:
             dtkIteratorTestCase(void);
    virtual ~dtkIteratorTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testCreate(void);
    void testCopyCreate(void);
    void testCopy(void);
    void testDereference(void);
    void testBracket(void);
    void testForward(void);
    void testPreForward(void);
    void testPreBackward(void);
    void testBackward(void);
    void testAffectAdd(void);
    void testAffectSubstract(void);
    void testAdd(void);
    void testSubstract(void);
    void testEquality(void);
    void testInequality(void);
    void testInferior(void);
    void testInferiorEqual(void);
    void testSuperior(void);
    void testSuperiorEqual(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);

private:
    dtkIteratorTestCasePrivate *d;
};

//
// dtkIteratorTest.h ends here

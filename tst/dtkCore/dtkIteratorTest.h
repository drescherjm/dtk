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

private slots:
    void cleanupTestCase(void);
    void cleanup(void);

private:
    dtkIteratorTestCasePrivate *d;
};

// 
// dtkIteratorTest.h ends here

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

class dtkHashTestCase : public QObject
{
    Q_OBJECT

public:
     dtkHashTestCase(void);
    ~dtkHashTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testPair(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};

//
// dtkHashTest.h ends here

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

class dtkHelperFunctionTestCase : public QObject
{
    Q_OBJECT

public:
     dtkHelperFunctionTestCase(void);
    ~dtkHelperFunctionTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testCheckVersion(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};

//
// dtkHelperFunctionTest.h ends here

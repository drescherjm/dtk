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

class dtkLoggerHandlersTestCase : public QObject
{
    Q_OBJECT

public:
    dtkLoggerHandlersTestCase(void);
    virtual ~dtkLoggerHandlersTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testLoggerHandlers(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};

//
// dtkLoggerHandlersTest.h ends here

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

#include "dtkLoggerHandlersTest.h"

#include <dtkLog>

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

dtkLoggerHandlersTestCase::dtkLoggerHandlersTestCase(void)
{

}

dtkLoggerHandlersTestCase::~dtkLoggerHandlersTestCase(void)
{

}

void dtkLoggerHandlersTestCase::initTestCase(void)
{
    dtkInstallLoggerHandler(dtkLog::File);
}

void dtkLoggerHandlersTestCase::init(void)
{

}

void dtkLoggerHandlersTestCase::testLoggerHandlers(void)
{

}

void dtkLoggerHandlersTestCase::cleanup(void)
{

}

void dtkLoggerHandlersTestCase::cleanupTestCase(void)
{
    dtkUninstallLoggerHandler();
}

DTKTEST_MAIN_NOGUI(dtkLoggerHandlersTest, dtkLoggerHandlersTestCase)

//
// dtkLoggerHandlersTest.cpp ends here

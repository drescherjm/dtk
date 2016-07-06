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

#include "dtkHelperFunctionTest.h"

#include <dtkCore/dtkCore.h>

#include <QtCore>

#include <iostream>
#include <unordered_map>

// ///////////////////////////////////////////////////////////////////
// dtkHelperFunctionTestCase
// ///////////////////////////////////////////////////////////////////

dtkHelperFunctionTestCase::dtkHelperFunctionTestCase(void)
{
}

dtkHelperFunctionTestCase::~dtkHelperFunctionTestCase(void)
{
}

void dtkHelperFunctionTestCase::initTestCase(void)
{
}

void dtkHelperFunctionTestCase::init(void)
{

}

void dtkHelperFunctionTestCase::testCheckVersion(void)
{
    QCOMPARE(checkVersion("3.1.1","3.1.1"),  true);

    QCOMPARE(checkVersion("4.1.1","3.1.1"),  false);
    QCOMPARE(checkVersion("3.1.1","4.1.1"),  false);

    QCOMPARE(checkVersion("3.1.1","3.1.0"),  true);
    QCOMPARE(checkVersion("3.1.1","3.1.3"),  false);

    QCOMPARE(checkVersion("3.1.0","3.2.0"),  false);
    QCOMPARE(checkVersion("3.3.0","3.2.0"),  true);

    QCOMPARE(checkVersion("3.2.1", "3.2"),  true);

    QCOMPARE(checkVersion("3.2.1","3.3"),  false);
    QCOMPARE(checkVersion("3.2.1","3.1"),  true);

    QCOMPARE(checkVersion("3.2.1","2.3"),  false);

    QCOMPARE(checkVersion("3.2.1","2"),  false);
    QCOMPARE(checkVersion("3.2.1","4"),  false);
}

void dtkHelperFunctionTestCase::cleanup(void)
{
}

void dtkHelperFunctionTestCase::cleanupTestCase(void)
{
}

DTKTEST_MAIN_NOGUI(dtkHelperFunctionTest, dtkHelperFunctionTestCase)

//
// dtkHelperFunctionTest.cpp ends here

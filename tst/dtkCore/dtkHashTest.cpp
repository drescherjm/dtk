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

#include "dtkHashTest.h"

#include <dtkCore/dtkHash.h>

#include <QtCore>

#include <iostream>
#include <unordered_map>

// ///////////////////////////////////////////////////////////////////
// dtkHashTestCase
// ///////////////////////////////////////////////////////////////////

dtkHashTestCase::dtkHashTestCase(void)
{
}

dtkHashTestCase::~dtkHashTestCase(void)
{
}

void dtkHashTestCase::initTestCase(void)
{
}

void dtkHashTestCase::init(void)
{

}

void dtkHashTestCase::testPair(void)
{
    std::unordered_map<std::pair<qlonglong, qlonglong>, qlonglong, dtkHash> map_of_pair;

    std::pair<qlonglong, qlonglong> p0 = std::make_pair(12, 19);
    std::pair<qlonglong, qlonglong> p1 = std::make_pair(19, 12);

    map_of_pair[p0] =  27;
    map_of_pair[p1] = -27;

    QCOMPARE(map_of_pair[p0],  27LL);
    QCOMPARE(map_of_pair[p1], -27LL);
}

void dtkHashTestCase::cleanup(void)
{
}

void dtkHashTestCase::cleanupTestCase(void)
{
}

DTKTEST_MAIN_NOGUI(dtkHashTest, dtkHashTestCase)

//
// dtkHashTest.cpp ends here

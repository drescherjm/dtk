/* dtkCompareDoubleTest.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun 20 13:12:23 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Nov 21 17:25:44 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 126
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCompareDoubleTest.h"

#include <dtkMath/dtkMath.h>

#include <float.h>

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

bool TestAlmostEqual(double A, double B, int64_t maxUlps = 8 * 1024 * 1024);

// /////////////////////////////////////////////////////////////////
// dtkCompareDoubleTestObjectPrivate
// /////////////////////////////////////////////////////////////////

class dtkCompareDoubleTestObjectPrivate
{
public:
    double zero1;
    double zero2;

    double negativeZero;

    double nan1;
    double nan2;
    double nan3;
    double nan4;

    double inf0;

    double smallestDenormal;
};

// /////////////////////////////////////////////////////////////////
// dtkCompareDoubleTestObject
// /////////////////////////////////////////////////////////////////

dtkCompareDoubleTestObject::dtkCompareDoubleTestObject(void) : d(new dtkCompareDoubleTestObjectPrivate)
{
    d->zero1 = 0;
    d->zero2 = 0;

    d->inf0 = 1 / d->zero1;

    *(long long int*)(&(d->negativeZero)) = 0x8000000000000000LL;

    d->nan1 = sqrt(-1.0);
    d->nan2 = d->zero1 / d->zero2;
    d->nan3 = d->inf0 - d->inf0;
    d->nan4 = d->nan3;

    (*(long long int*)(&(d->nan4))) += 1;

    d->smallestDenormal = 0;

    (*(long long int*)(&(d->smallestDenormal))) += 1;
}

dtkCompareDoubleTestObject::~dtkCompareDoubleTestObject(void)
{

}

void dtkCompareDoubleTestObject::initTestCase(void)
{

}

void dtkCompareDoubleTestObject::init(void)
{

}

void dtkCompareDoubleTestObject::cleanup(void)
{

}

void dtkCompareDoubleTestObject::cleanupTestCase(void)
{

}

void dtkCompareDoubleTestObject::testAlmostEqual1(void)
{
    QVERIFY(TestAlmostEqual(d->zero1, d->negativeZero) == true);
    QVERIFY(TestAlmostEqual(2.0, 1.999999999999999) == true);
    QVERIFY(TestAlmostEqual(2.0, 1.9999999999999995) == true);
    QVERIFY(TestAlmostEqual(1.9999999999999995, 2.0) == true);
    QVERIFY(TestAlmostEqual(2.0, 1.9999999999999995) == true);
}

void dtkCompareDoubleTestObject::testAlmostEqual2(void)
{
    QVERIFY(TestAlmostEqual(d->inf0, -d->inf0, 16 * 1024 * 1024) == false);
    QVERIFY(TestAlmostEqual(DBL_MAX, d->inf0) == false);
    QVERIFY(TestAlmostEqual(d->nan2, d->nan2) == false);
    QVERIFY(TestAlmostEqual(d->nan2, d->nan3) == false);
    QVERIFY(TestAlmostEqual(d->smallestDenormal, -d->smallestDenormal) ==  false);
}

DTKTEST_NOGUI_MAIN(dtkCompareDoubleTest, dtkCompareDoubleTestObject)

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

bool TestAlmostEqual(double A, double B, int64_t maxUlps)
{
    return dtkAlmostEqualUlps(A, B, maxUlps);
}

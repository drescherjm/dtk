/* dtkCompareDoubleTest.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun 20 13:12:23 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Nov 20 17:43:05 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 115
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

bool TestCompare2sComplement(double A, double B, int64_t maxUlps = 8 * 1024 *1024);
bool TestCompareFinal(double A, double B, int64_t maxUlps = 8 * 1024 * 1024);
bool TestCompareAll(double A, double B, int64_t maxUlps = 8 * 1024 * 1024);

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

void dtkCompareDoubleTestObject::testCompareAll(void)
{
    QVERIFY(TestCompareAll(d->zero1, d->negativeZero) == true);
    QVERIFY(TestCompareAll(2.0, 1.999999999999999) == true);
    QVERIFY(TestCompareAll(2.0, 1.9999999999999995) == true);
    QVERIFY(TestCompareAll(1.9999999999999995, 2.0) == true);
    QVERIFY(TestCompareAll(2.0, 1.9999999999999995) == true);
}

void dtkCompareDoubleTestObject::testCompare2sComplement(void)
{
    QVERIFY(TestCompare2sComplement(d->inf0, -d->inf0, 16 * 1024 * 1024) == false);
    QVERIFY(TestCompare2sComplement(DBL_MAX, d->inf0) == true);
    QVERIFY(TestCompare2sComplement(d->nan2, d->nan2) == true);
    QVERIFY(TestCompare2sComplement(d->nan2, d->nan3) == true);
    QVERIFY(TestCompare2sComplement(d->smallestDenormal, -d->smallestDenormal) == true);
 }

void dtkCompareDoubleTestObject::testCompareFinal(void)
{
    QVERIFY(TestCompareFinal(d->inf0, -d->inf0, 16 * 1024 * 1024) == false);
    QVERIFY(TestCompareFinal(DBL_MAX, d->inf0) == false);
    QVERIFY(TestCompareFinal(d->nan2, d->nan2) == false);
    QVERIFY(TestCompareFinal(d->nan2, d->nan3) == false);
    QVERIFY(TestCompareFinal(d->smallestDenormal, -d->smallestDenormal) ==  false);
}

DTKTEST_NOGUI_MAIN(dtkCompareDoubleTest, dtkCompareDoubleTestObject)

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

bool TestCompare2sComplement(double A, double B, int64_t maxUlps)
{
    return dtkAlmostEqual2sComplement(A, B, maxUlps);
}

bool TestCompareFinal(double A, double B, int64_t maxUlps)
{
    return dtkAlmostEqualUlps(A, B, maxUlps);
}

bool TestCompareAll(double A, double B, int64_t maxUlps)
{
    return (TestCompare2sComplement(A, B, maxUlps) || TestCompareFinal(A, B, maxUlps));
}

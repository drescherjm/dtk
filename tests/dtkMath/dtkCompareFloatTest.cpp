/* dtkTestFloat.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Aug 18 19:42:04 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Sat Jun 30 01:31:02 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkCompareFloatTest.h"

#include <dtkMath/dtkMath.h>

#include <float.h>

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

bool TestCompare2sComplement(float A, float B, int32_t maxUlps = 10);
bool TestCompareFinal(float A, float B, int32_t maxUlps = 10);
bool TestCompareAll(float A, float B, int32_t maxUlps = 10);

// /////////////////////////////////////////////////////////////////
// dtkCompareFloatTestObjectPrivate
// /////////////////////////////////////////////////////////////////

class dtkCompareFloatTestObjectPrivate
{
public:
    float zero1;
    float zero2;

    float negativeZero;

    float nan1;
    float nan2;
    float nan3;
    float nan4;

    float inf0;

    float smallestDenormal;
};

// /////////////////////////////////////////////////////////////////
// dtkCompareFloatTestObject
// /////////////////////////////////////////////////////////////////

dtkCompareFloatTestObject::dtkCompareFloatTestObject(void) : d(new dtkCompareFloatTestObjectPrivate)
{
    d->zero1 = 0;
    d->zero2 = 0;

    d->inf0 = 1 / d->zero1;

    *(long long int*)(&(d->negativeZero)) = 0x80000000;

    d->nan1 = sqrt(-1.0f);
    d->nan2 = d->zero1 / d->zero2;
    d->nan3 = d->inf0 - d->inf0;
    d->nan4 = d->nan3;

    (*(int*)(&(d->nan4))) += 1;

    d->smallestDenormal = 0;

    (*(int*)(&(d->smallestDenormal))) += 1;
}


dtkCompareFloatTestObject::~dtkCompareFloatTestObject(void)
{
}

void dtkCompareFloatTestObject::initTestCase()
{
}

void dtkCompareFloatTestObject::init()
{
}

void dtkCompareFloatTestObject::cleanup()
{
}

void dtkCompareFloatTestObject::cleanupTestCase()
{
}

void dtkCompareFloatTestObject::testCompareAll(void)
{
    QVERIFY(TestCompareAll(d->zero1, d->negativeZero) == true);
    QVERIFY(TestCompareAll(2.0, 1.99999999) == true);
    QVERIFY(TestCompareAll(2.0, 1.99999995) == true);
    QVERIFY(TestCompareAll(1.99999995, 2.0) == true);
    QVERIFY(TestCompareAll(2.0, 1.99999995) == true);
}

void dtkCompareFloatTestObject::testCompare2sComplement(void)
{
    QVERIFY(TestCompare2sComplement(d->inf0, -d->inf0, 16 * 1024 * 1024) == false);
    QVERIFY(TestCompare2sComplement(FLT_MAX, d->inf0) == true);
    QVERIFY(TestCompare2sComplement(d->nan2, d->nan2) == true);
    QVERIFY(TestCompare2sComplement(d->nan2, d->nan3) == true);
    QVERIFY(TestCompare2sComplement(d->smallestDenormal, -d->smallestDenormal) == true);
}

void dtkCompareFloatTestObject::testCompareFinal(void)
{
    QVERIFY(TestCompareFinal(d->inf0, -d->inf0, 16 * 1024 * 1024) == false);
    QVERIFY(TestCompareFinal(FLT_MAX, d->inf0) == false);
    QVERIFY(TestCompareFinal(d->nan2, d->nan2) == false);
    QVERIFY(TestCompareFinal(d->nan2, d->nan3) == false);
    QVERIFY(TestCompareFinal(d->smallestDenormal, -d->smallestDenormal) ==  false);
}

DTKTEST_NOGUI_MAIN(dtkCompareFloatTest, dtkCompareFloatTestObject)

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

bool TestCompare2sComplement(float A, float B, int32_t maxUlps)
{
    return dtkAlmostEqual2sComplement(A, B, maxUlps);
}

bool TestCompareFinal(float A, float B, int32_t maxUlps)
{
    return dtkAlmostEqualUlps(A, B, maxUlps);
}

bool TestCompareAll(float A, float B, int32_t maxUlps)
{
    return (TestCompare2sComplement(A, B, maxUlps) || TestCompareFinal(A, B, maxUlps));
}


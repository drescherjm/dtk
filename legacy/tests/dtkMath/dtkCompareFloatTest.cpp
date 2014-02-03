/* dtkTestFloat.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Aug 18 19:42:04 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Nov 21 17:26:22 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 15
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

bool TestAlmostEqual(float A, float B, int32_t maxUlps = 10);

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

void dtkCompareFloatTestObject::testAlmostEqual1(void)
{
    QVERIFY(TestAlmostEqual(d->zero1, d->negativeZero) == true);
    QVERIFY(TestAlmostEqual(2.0, 1.99999999) == true);
    QVERIFY(TestAlmostEqual(2.0, 1.99999995) == true);
    QVERIFY(TestAlmostEqual(1.99999995, 2.0) == true);
    QVERIFY(TestAlmostEqual(2.0, 1.99999995) == true);
}

void dtkCompareFloatTestObject::testAlmostEqual2(void)
{
    QVERIFY(TestAlmostEqual(d->inf0, -d->inf0, 16 * 1024 * 1024) == false);
    QVERIFY(TestAlmostEqual(FLT_MAX, d->inf0) == false);
    QVERIFY(TestAlmostEqual(d->nan2, d->nan2) == false);
    QVERIFY(TestAlmostEqual(d->nan2, d->nan3) == false);
    QVERIFY(TestAlmostEqual(d->smallestDenormal, -d->smallestDenormal) ==  false);
}

DTKTEST_NOGUI_MAIN(dtkCompareFloatTest, dtkCompareFloatTestObject)

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

bool TestAlmostEqual(float A, float B, int32_t maxUlps)
{
    return dtkAlmostEqualUlps(A, B, maxUlps);
}

/* dtkCompareDoubleTest.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun 20 13:12:23 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun 20 13:24:13 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 53
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCompareDoubleTest.h"

#include <dtkMath/dtkMath.h>

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
    QVERIFY(dtkAlmostEqual2sComplement(d->zero1, d->negativeZero, (long long int)10) == true);
}

DTKTEST_NOGUI_MAIN(dtkCompareDoubleTest,dtkCompareDoubleTestObject)

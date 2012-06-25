/* dtkTestSingleton.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Aug 18 19:42:04 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 16:52:09 2012 (+0200)
 *           By: Babette Lekouta
 *     Update #: 2
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkCompareSingletonTest.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkSingleton.h>
#include <dtkCore/dtkSingletonDeclare.h>

class dtkCompareSingletonTestObjectPrivate : public QObject
{
    DTK_DECLARE_SINGLETON(dtkCompareSingletonTestObjectPrivate);

public:
    static int count(void);

private:
     dtkCompareSingletonTestObjectPrivate(void);
    ~dtkCompareSingletonTestObjectPrivate(void);

private:
    static int s_count;
};

int dtkCompareSingletonTestObjectPrivate::s_count = 0;

DTK_IMPLEMENT_SINGLETON(dtkCompareSingletonTestObjectPrivate);

dtkCompareSingletonTestObjectPrivate::dtkCompareSingletonTestObjectPrivate(void)
{
    s_count++;
}

dtkCompareSingletonTestObjectPrivate::~dtkCompareSingletonTestObjectPrivate(void)
{
    s_count--;
}

int dtkCompareSingletonTestObjectPrivate::count(void)
{
    return s_count;
}

// /////////////////////////////////////////////////////////////////
// dtkCompareSingletonTestObject
// /////////////////////////////////////////////////////////////////

dtkCompareSingletonTestObject::dtkCompareSingletonTestObject(void)
{

}

dtkCompareSingletonTestObject::~dtkCompareSingletonTestObject(void)
{   

}

void dtkCompareSingletonTestObject::initTestCase(void)
{

}

void dtkCompareSingletonTestObject::init(void)
{

}

void dtkCompareSingletonTestObject::cleanup(void)
{

}

void dtkCompareSingletonTestObject::cleanupTestCase(void)
{

}

void dtkCompareSingletonTestObject::testSingleton(void)
{
    QVERIFY(dtkCompareSingletonTestObjectPrivate::count() == 0);

    this->d = dtkCompareSingletonTestObjectPrivate::instance();

    QVERIFY(dtkCompareSingletonTestObjectPrivate::count() == 1);

    dtkCompareSingletonTestObjectPrivate *s = dtkCompareSingletonTestObjectPrivate::instance();

    QVERIFY(s);

    QVERIFY(dtkCompareSingletonTestObjectPrivate::count() == 1);
}

DTKTEST_NOGUI_MAIN(dtkCompareSingletonTest, dtkCompareSingletonTestObject)

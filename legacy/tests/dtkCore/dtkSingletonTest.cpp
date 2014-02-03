/* dtkTestSingleton.cpp ---
 *
 * Author: Babette Lekouta
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

#include "dtkSingletonTest.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkSingleton.h>
#include <dtkCore/dtkSingletonDeclare.h>

class dtkSingletonTestObjectPrivate : public QObject
{
    DTK_DECLARE_SINGLETON(dtkSingletonTestObjectPrivate);

public:
    static int count(void);

private:
     dtkSingletonTestObjectPrivate(void);
    ~dtkSingletonTestObjectPrivate(void);

private:
    static int s_count;
};

int dtkSingletonTestObjectPrivate::s_count = 0;

DTK_IMPLEMENT_SINGLETON(dtkSingletonTestObjectPrivate);

dtkSingletonTestObjectPrivate::dtkSingletonTestObjectPrivate(void)
{
    s_count++;
}

dtkSingletonTestObjectPrivate::~dtkSingletonTestObjectPrivate(void)
{
    s_count--;
}

int dtkSingletonTestObjectPrivate::count(void)
{
    return s_count;
}

// /////////////////////////////////////////////////////////////////
// dtkSingletonTestObject
// /////////////////////////////////////////////////////////////////

dtkSingletonTestObject::dtkSingletonTestObject(void)
{

}

dtkSingletonTestObject::~dtkSingletonTestObject(void)
{

}

void dtkSingletonTestObject::initTestCase(void)
{

}

void dtkSingletonTestObject::init(void)
{

}

void dtkSingletonTestObject::cleanup(void)
{

}

void dtkSingletonTestObject::cleanupTestCase(void)
{

}

void dtkSingletonTestObject::testSingleton(void)
{
    QVERIFY(dtkSingletonTestObjectPrivate::count() == 0);

    this->d = dtkSingletonTestObjectPrivate::instance();

    QVERIFY(dtkSingletonTestObjectPrivate::count() == 1);

    dtkSingletonTestObjectPrivate *s = dtkSingletonTestObjectPrivate::instance();

    QVERIFY(s);

    QVERIFY(dtkSingletonTestObjectPrivate::count() == 1);
}

DTKTEST_NOGUI_MAIN(dtkSingletonTest, dtkSingletonTestObject)

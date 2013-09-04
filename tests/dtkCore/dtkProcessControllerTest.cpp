/* dtkProcessControllerTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Thu Aug 29 14:50:23 2013 (+0200)
 * Version: 
 * Last-Updated: mer. sept.  4 11:37:16 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 110
 */

/* Change Log:
 * 
 */

#include "dtkProcessControllerTest.h"

#include <dtkCore/dtkAbstractProcess>
#include <dtkCore/dtkAbstractProcessController>
#include <dtkCore/dtkAbstractProcessFactory>

#include <dtkCore/dtkGlobal.h>

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

class dummyProcess : public dtkAbstractProcess
{
public:
    int update(void);

public:
    int count;
};

int dummyProcess::update(void)
{
    count = 0;

    forever {
        count++;
        SLEEP(1000);
    }
}

// ///////////////////////////////////////////////////////////////////
// dtkProcessControllerTestPrivate
// ///////////////////////////////////////////////////////////////////

class dtkProcessControllerTestObjectPrivate
{
public:
    dtkAbstractProcessController *controller;
};

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

dtkProcessControllerTestObject::dtkProcessControllerTestObject(void)
{
    d = new dtkProcessControllerTestObjectPrivate;
}

dtkProcessControllerTestObject::~dtkProcessControllerTestObject(void)
{
    delete d;
}

void dtkProcessControllerTestObject::initTestCase(void)
{
    d->controller = new dtkAbstractProcessController;
}

void dtkProcessControllerTestObject::init(void)
{

}

void dtkProcessControllerTestObject::testStart(void)
{
    d->controller->setProcess(new dummyProcess);
    d->controller->start();
}

void dtkProcessControllerTestObject::testProcess(void)
{
    using namespace QTest;

    qWait(2000); QCOMPARE(dynamic_cast<dummyProcess *>(d->controller->process())->count, 3);
    qWait(2000); QCOMPARE(dynamic_cast<dummyProcess *>(d->controller->process())->count, 5);
    qWait(2000); QCOMPARE(dynamic_cast<dummyProcess *>(d->controller->process())->count, 7);
    qWait(2000); QCOMPARE(dynamic_cast<dummyProcess *>(d->controller->process())->count, 9);
    qWait(2000); QCOMPARE(dynamic_cast<dummyProcess *>(d->controller->process())->count, 11);
    qWait(2000); QCOMPARE(dynamic_cast<dummyProcess *>(d->controller->process())->count, 13);
}

void dtkProcessControllerTestObject::testStop(void)
{
    using namespace QTest;

    qWait(5000);

    QVERIFY(dynamic_cast<dummyProcess *>(d->controller->process())->count > 13);

    d->controller->stop();
}

void dtkProcessControllerTestObject::cleanup(void)
{

}

void dtkProcessControllerTestObject::cleanupTestCase(void)
{
    delete d->controller->process();
    delete d->controller;
}

DTKTEST_NOGUI_MAIN(dtkProcessControllerTest, dtkProcessControllerTestObject)

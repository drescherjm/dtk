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

#include "dtkDistributedArrayTest.h"
#include "../dtkDistributedArrayRunnable.h"

#include <dtkDistributed>
#include <dtkDistributed/dtkDistributedPolicy>

void dtkDistributedArrayTestCase::initTestCase(void)
{
    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    dtkDistributed::communicator::initialize(settings.value("plugins").toString());
    settings.endGroup();

    dtkDistributed::policy()->setType("qthread");

    for (int i = 0; i < 4; ++i) {
        dtkDistributed::policy()->addHost("localhost");
    }

    dtkDistributed::spawn();
}

void dtkDistributedArrayTestCase::init(void)
{

}

void dtkDistributedArrayTestCase::testCreateDestroy(void)
{
    QRunnable *test = new testArrayCreateDestroy();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedArrayTestCase::testAtFirstLast(void)
{
    QRunnable *test = new testArrayAtFirstLast();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedArrayTestCase::testFill(void)
{
    QRunnable *test = new testArrayFill();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedArrayTestCase::testSwap(void)
{
    QRunnable *test = new testArraySwap();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedArrayTestCase::testOperatorGet(void)
{
    QRunnable *test = new testArrayOperatorGet();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedArrayTestCase::testSetAt(void)
{
    QRunnable *test = new testArraySetAt();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedArrayTestCase::testIterator(void)
{
    QRunnable *test = new testArrayIterator();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedArrayTestCase::testRemap(void)
{
    QRunnable *test = new testArrayRemap();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedArrayTestCase::testCopyIntoArray(void)
{
    QRunnable *test = new testArrayCopyIntoArray();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedArrayTestCase::testToNavigator(void)
{
    QRunnable *test = new testArrayToNavigator();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedArrayTestCase::cleanupTestCase(void)
{
    dtkDistributed::unspawn();
    dtkDistributed::communicator::pluginManager().uninitialize();
}

void dtkDistributedArrayTestCase::cleanup(void)
{

}

DTKDISTRIBUTEDTEST_MAIN_NOGUI(dtkDistributedArrayTest, dtkDistributedArrayTestCase)

//
// dtkDistributedArrayTest.cpp ends here

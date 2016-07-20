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

#include "dtkDistributedBufferManagerTest.h"
#include "../dtkDistributedBufferManagerRunnable.h"

#include <dtkDistributed>
#include <dtkDistributed/dtkDistributedPolicy>

void dtkDistributedBufferManagerTestCase::initTestCase(void)
{
    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    dtkDistributed::communicator::initialize(settings.value("plugins").toString());
    settings.endGroup();

    dtkDistributed::policy()->setType("qthread");

    for (int i = 0; i < 2; ++i) {
        dtkDistributed::policy()->addHost("localhost");
    }

    dtkDistributed::spawn();
}

void dtkDistributedBufferManagerTestCase::init(void)
{

}

void dtkDistributedBufferManagerTestCase::testCreateDestroy(void)
{
    testBufferManagerCreateDestroy *test = new testBufferManagerCreateDestroy();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedBufferManagerTestCase::testAllocateDeallocate(void)
{
    testBufferManagerAllocateDeallocate *test = new testBufferManagerAllocateDeallocate();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedBufferManagerTestCase::testLocks(void)
{
    testBufferManagerLocks *test = new testBufferManagerLocks();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedBufferManagerTestCase::testAdd(void)
{
    testBufferManagerAdd *test = new testBufferManagerAdd();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedBufferManagerTestCase::testSub(void)
{
    testBufferManagerSub *test = new testBufferManagerSub();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedBufferManagerTestCase::testMul(void)
{
    testBufferManagerMul *test = new testBufferManagerMul();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedBufferManagerTestCase::testDiv(void)
{
    testBufferManagerDiv *test = new testBufferManagerDiv();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedBufferManagerTestCase::testPut(void)
{
    testBufferManagerPut *test = new testBufferManagerPut();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedBufferManagerTestCase::testGet(void)
{
    testBufferManagerGet *test = new testBufferManagerGet();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedBufferManagerTestCase::cleanupTestCase(void)
{
    dtkDistributed::unspawn();
    dtkDistributed::communicator::pluginManager().uninitialize();
}

void dtkDistributedBufferManagerTestCase::cleanup(void)
{

}

DTKDISTRIBUTEDTEST_MAIN_NOGUI(dtkDistributedBufferManagerTest, dtkDistributedBufferManagerTestCase)

//
// dtkDistributedBufferManagerTest.cpp ends here

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

#include "dtkDistributedGraphTopologyTest.h"
#include "../dtkDistributedGraphTopologyRunnable.h"

#include <dtkDistributed>
#include <dtkDistributed/dtkDistributedPolicy>

void dtkDistributedGraphTopologyTestCase::initTestCase(void)
{
    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    dtkDistributed::communicator::initialize(settings.value("plugins").toString());
    settings.endGroup();

    dtkDistributed::policy()->setType("mpi");

    for (int i = 0; i < 3; ++i) {
        dtkDistributed::policy()->addHost("localhost");
    }

    dtkDistributed::spawn();
}

void dtkDistributedGraphTopologyTestCase::init(void)
{

}

void dtkDistributedGraphTopologyTestCase::testCreateDestroy(void)
{
    QRunnable *test = new testGraphTopologyCreateDestroy();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedGraphTopologyTestCase::testClearResize(void)
{
    QRunnable *test = new testGraphTopologyClearResize();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedGraphTopologyTestCase::testAssemble(void)
{
    QRunnable *test = new testGraphTopologyAssemble();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedGraphTopologyTestCase::testNeighbours(void)
{
    QRunnable *test = new testGraphTopologyNeighbours();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedGraphTopologyTestCase::testIterator(void)
{
    QRunnable *test = new testGraphTopologyIterator();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedGraphTopologyTestCase::testRead(void)
{
    QRunnable *test = new testGraphTopologyRead();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedGraphTopologyTestCase::testLock(void)
{
    QRunnable *test = new testGraphTopologyLock();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedGraphTopologyTestCase::testVertex(void)
{
    QRunnable *test = new testGraphTopologyVertex();
    dtkDistributed::exec(test);
    delete test;
}

void dtkDistributedGraphTopologyTestCase::cleanupTestCase(void)
{
    dtkDistributed::unspawn();
    dtkDistributed::communicator::pluginManager().uninitialize();
}

void dtkDistributedGraphTopologyTestCase::cleanup(void)
{

}

DTKDISTRIBUTEDTEST_MAIN_NOGUI(dtkDistributedGraphTopologyTest, dtkDistributedGraphTopologyTestCase)

//
// dtkDistributedGraphTopologyTest.cpp ends here

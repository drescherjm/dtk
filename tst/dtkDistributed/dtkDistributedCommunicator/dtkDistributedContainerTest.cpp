/* dtkDistributedContainerTest.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Mon Feb  4 15:37:54 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedContainerTest.h"
#include "../dtkDistributedContainerRunnable.h"

#include <dtkDistributed>
#include <dtkDistributed/dtkDistributedCoreApplication.h>


void dtkDistributedContainerTestCase::initTestCase(void)
{
    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    dtkDistributed::communicator::initialize(settings.value("plugins").toString());
    settings.endGroup();
}

void dtkDistributedContainerTestCase::init(void)
{

}

void dtkDistributedContainerTestCase::testAll(void)
{
    communicator_container_test::runAll("qthread");
}

void dtkDistributedContainerTestCase::cleanupTestCase(void)
{
    dtkDistributed::communicator::pluginManager().uninitialize();
}

void dtkDistributedContainerTestCase::cleanup(void)
{

}

DTKDISTRIBUTEDTEST_MAIN_NOGUI(dtkDistributedContainerTest, dtkDistributedContainerTestCase)

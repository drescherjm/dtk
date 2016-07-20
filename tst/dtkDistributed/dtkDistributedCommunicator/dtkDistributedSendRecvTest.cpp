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

#include "dtkDistributedSendRecvTest.h"
#include "../dtkDistributedCommRunnable.h"

#include <dtkDistributed>
#include <dtkDistributed/dtkDistributedArray>
#include <dtkDistributed/dtkDistributedPolicy>


void dtkDistributedSendRecvTestCase::initTestCase(void)
{
    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    dtkDistributed::communicator::initialize(settings.value("plugins").toString());
    settings.endGroup();
    dtkLogger::instance().attachConsole();
    dtkLogger::instance().setLevel("trace");
}

void dtkDistributedSendRecvTestCase::init(void)
{

}

void dtkDistributedSendRecvTestCase::testAll(void)
{
    communicator_send_test::runAll("qthread");
}

void dtkDistributedSendRecvTestCase::cleanupTestCase(void)
{
    dtkDistributed::communicator::pluginManager().uninitialize();
}

void dtkDistributedSendRecvTestCase::cleanup(void)
{

}

DTKDISTRIBUTEDTEST_MAIN_NOGUI(dtkDistributedSendRecvTest, dtkDistributedSendRecvTestCase)

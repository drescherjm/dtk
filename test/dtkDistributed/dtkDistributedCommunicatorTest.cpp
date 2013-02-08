/* dtkDistributedCommunicatorTest.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb  4 14:11:27 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Feb  8 16:43:10 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 49
 */

/* Change Log:
 * 
 */

#include "dtkDistributedCommunicatorTest.h"

#include <dtkDistributed>

void dtkDistributedCommunicatorTestCase::initTestCase(void)
{

}

void dtkDistributedCommunicatorTestCase::init(void)
{

}

void dtkDistributedCommunicatorTestCase::testPluginManager(void)
{
    QVERIFY(dtkDistributedCommunicatorPluginManager::instance());
}

void dtkDistributedCommunicatorTestCase::testPluginFactory(void)
{
    QVERIFY(dtkDistributedCommunicatorPluginFactory::instance());
}

void dtkDistributedCommunicatorTestCase::cleanupTestCase(void)
{

}

void dtkDistributedCommunicatorTestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkDistributedCommunicatorTest, dtkDistributedCommunicatorTestCase)

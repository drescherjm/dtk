/* dtkDistributedCommunicatorTest.cpp ---
 *
 * Author: Julien Wintz
 * Created: Mon Feb  4 14:11:27 2013 (+0100)
 */

/* Change Log:
 *
 */

#include "dtkDistributedCommunicatorTest.h"

#include <dtkDistributed>

void dtkDistributedCommunicatorTestCase::initTestCase(void)
{
    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    qDebug() << "plugins path:" << settings.value("plugins").toString();
    dtkDistributed::communicator::pluginManager().setVerboseLoading(true);
    dtkLogger::instance().attachConsole();
    dtkLogger::instance().setLevel("trace");
    dtkDistributed::communicator::initialize(settings.value("plugins").toString());
    dtkLogger::instance().setLevel("info");
    settings.endGroup();
}

void dtkDistributedCommunicatorTestCase::init(void)
{

}

void dtkDistributedCommunicatorTestCase::testPluginManager(void)
{
    qDebug() << dtkDistributed::communicator::pluginManager().plugins();
}

void dtkDistributedCommunicatorTestCase::testPluginFactory(void)
{
    qDebug() << dtkDistributed::communicator::pluginFactory().keys();
}

void dtkDistributedCommunicatorTestCase::testPlugin(void)
{
    dtkDistributedCommunicator *communicator = dtkDistributed::communicator::pluginFactory().create("qthread");
    communicator->initialize();
    qDebug() << communicator->metaObject()->className();
    qDebug() << communicator->wid();
    qDebug() << communicator->size();
    communicator->uninitialize();
    delete communicator;
}

void dtkDistributedCommunicatorTestCase::cleanupTestCase(void)
{
    dtkDistributed::communicator::pluginManager().uninitialize();
}

void dtkDistributedCommunicatorTestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkDistributedCommunicatorTest, dtkDistributedCommunicatorTestCase)

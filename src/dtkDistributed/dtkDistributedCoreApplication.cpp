/* dtkDistributedCoreApplication.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/01/27 11:47:52
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */



#include "dtkDistributedCoreApplication.h"

#include <dtkDistributed/dtkDistributed.h>
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedSettings.h>
#include <dtkDistributed/dtkDistributedPolicy.h>
#include <dtkDistributed/dtkDistributedWorkerManager.h>

#include <dtkLog>

#include <QtCore>

class dtkDistributedCoreApplicationPrivate
{

public:
    dtkDistributedWorkerManager manager;
    dtkDistributedPolicy policy;
};

dtkDistributedCoreApplication::dtkDistributedCoreApplication(int &argc, char **argv) : dtkCoreApplication(argc,argv)
{
    d = new dtkDistributedCoreApplicationPrivate;
}

dtkDistributedCoreApplication::~dtkDistributedCoreApplication(void)
{
    d->manager.unspawn();
    delete d;
    d = NULL;
}

void dtkDistributedCoreApplication::exec(dtkDistributedWork *work)
{
     d->manager.exec(work);
}

dtkDistributedPolicy *dtkDistributedCoreApplication::policy(void)
{
     return &(d->policy);
}

dtkDistributedWorker *dtkDistributedCoreApplication::worker(void)
{

    return d->policy.communicator()->worker();
}

bool dtkDistributedCoreApplication::isMaster(void)
{
    return (d->policy.communicator()->rank() == 0);
}

void dtkDistributedCoreApplication::initialize(void)
{
    QCommandLineParser *parser = this->dtkCoreApplication::parser();

    QString policyType = "qthread";
    QCommandLineOption policyOption("policy", "dtkDistributed policy (default is qthread)", "qthread|mpi|mpi3", policyType);
    parser->addOption(policyOption);

    QCommandLineOption npOption("np","number of processes","int","1");
    parser->addOption(npOption);
    QCommandLineOption ntOption("nt","number of threads (for hybrid plugins)","int", "1");
    parser->addOption(ntOption);

    dtkCoreApplication::initialize();

        // plugins
    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    qDebug() << "initialize plugin manager "<< settings.value("plugins").toString();
    dtkDistributed::communicator::pluginManager().initialize(settings.value("plugins").toString());
    settings.endGroup();

    qDebug() << dtkDistributed::communicator::pluginManager().plugins();
    qDebug() << "available plugins:" << dtkDistributed::communicator::pluginFactory().keys();

     if (parser->isSet(policyOption)) {
         policyType = parser->value(policyOption);
     }
    d->policy.setType(policyType);

    d->manager.setPolicy(&(d->policy));
    d->manager.spawn();

}

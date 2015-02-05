/* dtkDistributedApplication.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/02/04 12:31:06
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkDistributed.h"
#include "dtkDistributedAbstractApplication.h"
#include "dtkDistributedCommunicator"
#include "dtkDistributedCoreApplication.h"
#include "dtkDistributedSettings.h"
#include "dtkDistributedWorkerManager.h"
#include "dtkDistributedPolicy.h"

#include <dtkLog>

#include <QtCore>

class dtkDistributedAbstractApplicationPrivate
{

public:
    dtkDistributedWorkerManager manager;
    dtkDistributedPolicy policy;

};

dtkDistributedAbstractApplication::dtkDistributedAbstractApplication(void)
{

    d = new dtkDistributedAbstractApplicationPrivate;

}

dtkDistributedAbstractApplication::~dtkDistributedAbstractApplication(void)
{

    d->manager.unspawn();

    delete d;
    d = NULL;
}

void dtkDistributedAbstractApplication::initialize(void)
{
    QCommandLineParser *parser = dtkDistributedAbstractApplication::parser();

    QString policyType = "qthread";
    QCommandLineOption policyOption("policy", "dtkDistributed policy (default is qthread)", "qthread|mpi|mpi3", policyType);
    parser->addOption(policyOption);

    QCommandLineOption npOption("np","number of processes","int","1");
    parser->addOption(npOption);
    QCommandLineOption ntOption("nt","number of threads (for hybrid plugins)","int", "1");
    parser->addOption(ntOption);

    dtkAbstractApplication::initialize();

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


void dtkDistributedAbstractApplication::exec(QRunnable *task)
{
    d->manager.exec(task);
}

dtkDistributedPolicy *dtkDistributedAbstractApplication::policy(void)
{
     return &(d->policy);
}

dtkDistributedCommunicator *dtkDistributedAbstractApplication::communicator(void)
{

    return d->policy.communicator();
}

bool dtkDistributedAbstractApplication::isMaster(void)
{
    return (d->policy.communicator()->rank() == 0);
}

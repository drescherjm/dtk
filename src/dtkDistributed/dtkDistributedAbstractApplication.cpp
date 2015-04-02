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
#include "dtkDistributedPolicy.h"

#include <dtkLog>

#include <QtCore>

class dtkDistributedAbstractApplicationPrivate
{

public:
    dtkDistributedPolicy policy;
    bool spawned;
};



/*!
  \class dtkDistributedAbstractApplication
  \inmodule dtkDistributed
  \brief dtkDistributedAbstractApplication ...

*/

dtkDistributedAbstractApplication::dtkDistributedAbstractApplication(void)
{

    d = new dtkDistributedAbstractApplicationPrivate;
    d->spawned = false;

}

dtkDistributedAbstractApplication::~dtkDistributedAbstractApplication(void)
{
    if (d->spawned)
        this->unspawn();

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
    dtkDebug() << "initialize plugin manager "<< settings.value("plugins").toString();

    QCommandLineOption verboseOption("verbose", QCoreApplication::translate("main", "verbose plugin initialization"));
    if (parser->isSet(verboseOption)) {
        dtkDistributed::communicator::pluginManager().setVerboseLoading(true);
    }
    dtkDistributed::communicator::pluginManager().initialize(settings.value("plugins").toString());
    settings.endGroup();

    dtkDebug() << "available plugins:" << dtkDistributed::communicator::pluginFactory().keys();

    if (parser->isSet(policyOption)) {
        policyType = parser->value(policyOption);
    }
    d->policy.setType(policyType);
}


void dtkDistributedAbstractApplication::exec(QRunnable *task)
{
    d->policy.communicator()->exec(task);
}

void dtkDistributedAbstractApplication::spawn(void)
{
    QStringList hosts = d->policy.hosts();
    d->spawned = true;
    d->policy.communicator()->spawn(hosts, d->policy.nthreads());
}

void dtkDistributedAbstractApplication::unspawn(void)
{
    d->policy.communicator()->unspawn();
    d->spawned = false;
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

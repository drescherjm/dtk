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
#include "dtkDistributedApplication.h"
#include "dtkDistributedCommunicator"
#include "dtkDistributedSettings.h"
#include "dtkDistributedPolicy.h"

#include <dtkLog>

class dtkDistributedApplicationPrivate
{

public:
    dtkDistributedPolicy policy;
    bool spawned;
    QString wrapper;
};



/*!
  \class dtkDistributedApplication
  \inmodule dtkDistributed
  \brief dtkDistributedApplication ...

*/

dtkDistributedApplication::dtkDistributedApplication(int &argc, char **argv): dtkApplication(argc, argv)
{

    d = new dtkDistributedApplicationPrivate;
    d->spawned = false;

}

dtkDistributedApplication::~dtkDistributedApplication(void)
{
    if (d->spawned)
        this->unspawn();

    delete d;
    d = NULL;
}

void dtkDistributedApplication::initialize(void)
{
    QCommandLineParser *parser = dtkDistributedApplication::parser();

    QString policyType = "qthread";
    QCommandLineOption policyOption("policy", "dtkDistributed policy (default is qthread)", "qthread|mpi|mpi3", policyType);
    parser->addOption(policyOption);

    QCommandLineOption npOption("np","number of processes","int","1");
    parser->addOption(npOption);
    QCommandLineOption ntOption("nt","number of threads (for hybrid plugins)","int", "1");
    parser->addOption(ntOption);
    QCommandLineOption wrapperOption("wrapper","use wrapper command when spawning processes","command", "");
    parser->addOption(wrapperOption);
    QCommandLineOption hostsOption("hosts","hosts (multiple hosts can be specified)","hostname", "localhost");
    parser->addOption(hostsOption);

    dtkApplication::initialize();

    // plugins
    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    dtkDebug() << "initialize plugin manager "<< settings.value("plugins").toString();

    QCommandLineOption verboseOption("verbose", QCoreApplication::translate("main", "verbose plugin initialization"));
    if (parser->isSet(verboseOption)) {
        dtkDistributed::communicator::pluginManager().setVerboseLoading(true);
    }
    dtkDistributed::communicator::initialize(settings.value("plugins").toString());
    settings.endGroup();

    dtkDebug() << "available plugins:" << dtkDistributed::communicator::pluginFactory().keys();

    if (parser->isSet(policyOption)) {
        policyType = parser->value(policyOption);
    }
    if (parser->isSet(hostsOption)) {
        foreach(QString s, parser->values(hostsOption)) {
            d->policy.addHost(s);
        }
    } else {
        d->policy.setHostsFromEnvironment();
    }

    if (parser->isSet(wrapperOption)) {
        d->wrapper = parser->value(wrapperOption);
    }
    qlonglong np = 0;
    if (parser->isSet(npOption)) {
            np = parser->value(npOption).toLongLong();
            dtkTrace() << "got np value from command line:"<< np ;
            d->policy.setNWorkers(np);
    }
    d->policy.setType(policyType);
}


void dtkDistributedApplication::exec(QRunnable *task)
{
    d->policy.communicator()->exec(task);
}

void dtkDistributedApplication::spawn(void)
{
    QStringList hosts = d->policy.hosts();
    d->spawned = true;
    d->policy.communicator()->spawn(hosts, d->wrapper);
}

void dtkDistributedApplication::unspawn(void)
{
    d->policy.communicator()->unspawn();
    d->spawned = false;
}

dtkDistributedPolicy *dtkDistributedApplication::policy(void)
{
     return &(d->policy);
}

dtkDistributedCommunicator *dtkDistributedApplication::communicator(void)
{

    return d->policy.communicator();
}

bool dtkDistributedApplication::isMaster(void)
{
    return (d->policy.communicator()->rank() == 0);
}

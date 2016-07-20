/* dtkDistributedApplicationPrivate.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/04/25 13:15:31
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkDistributedApplicationPrivate.h>

#include <dtkDistributedCommunicator.h>
#include <dtkDistributedSettings.h>
#include <dtkDistributed.h>

dtkDistributedApplicationPrivate::dtkDistributedApplicationPrivate(void): dtkApplicationPrivate()
{
    spawned = false;
    nospawn = false;
}

dtkDistributedApplicationPrivate::~dtkDistributedApplicationPrivate(void)
{
    if (spawned)
        unspawn();
}


void dtkDistributedApplicationPrivate::spawn(QMap<QString, QString> options)
{
    if (!smp.isEmpty()) {
        options.insert("smp", smp);
    }

    if (nospawn) {
        QStringList nospawn;
        nospawn << "nospawn";
        policy.communicator()->spawn(nospawn, wrapper, options);
    } else {
        QStringList hosts = policy.hosts();
        spawned = true;
        policy.communicator()->spawn(hosts, wrapper, options);
    }
}

void dtkDistributedApplicationPrivate::unspawn(void)
{
    policy.communicator()->unspawn();
    spawned = false;
}

void dtkDistributedApplicationPrivate::initialize(void)
{
    QString policyType = "qthread";
    QCommandLineOption policyOption("policy", "dtkDistributed policy (default is qthread)", "qthread|mpi|mpi3", policyType);
    parser->addOption(policyOption);

    QCommandLineOption npOption("np", "number of processes", "int", "1");
    parser->addOption(npOption);
    QCommandLineOption nsOption("no-spawn", "disable spawning");
    parser->addOption(nsOption);
    QCommandLineOption ntOption("nt", "number of threads (for hybrid plugins)", "int", "1");
    parser->addOption(ntOption);
    QCommandLineOption wrapperOption("wrapper", "use wrapper command when spawning processes", "command", "");
    parser->addOption(wrapperOption);
    QCommandLineOption smpOption("smp", "smp option (disabled by default)", "single|funneled|serialized|multiple", "");
    parser->addOption(smpOption);
    QCommandLineOption hostsOption("hosts", "hosts (multiple hosts can be specified)", "hostname", "localhost");
    parser->addOption(hostsOption);


    QCommandLineOption DSsettingsOption("distributed-settings", "dtkDistributed settings file", "filename");
    parser->addOption(DSsettingsOption);

    dtkApplicationPrivate::initialize();

    QSettings *settings;

    if (parser->isSet(DSsettingsOption)) {
        settings = new QSettings(parser->value(DSsettingsOption), QSettings::IniFormat);
    } else {
        settings =  new dtkDistributedSettings;
    }

    if (parser->isSet(nsOption)) {
        nospawn = true;
    }

    // plugins
    settings->beginGroup("communicator");
    dtkDebug() << "initialize plugin manager " << settings->value("plugins").toString();

    QCommandLineOption verboseOption("verbose", QCoreApplication::translate("main", "verbose plugin initialization"));

    if (parser->isSet(verboseOption)) {
        dtkDistributed::communicator::pluginManager().setVerboseLoading(true);
    }

    dtkDistributed::communicator::initialize(settings->value("plugins").toString());
    settings->endGroup();

    delete settings;

    dtkDebug() << "available plugins:" << dtkDistributed::communicator::pluginFactory().keys();

    if (parser->isSet(policyOption)) {
        policyType = parser->value(policyOption);
    }

    if (parser->isSet(hostsOption)) {
        foreach (QString s, parser->values(hostsOption)) {
            policy.addHost(s);
        }
    } else {
        policy.setHostsFromEnvironment();
    }

    if (parser->isSet(wrapperOption)) {
        wrapper = parser->value(wrapperOption);
    }

    qlonglong np = 0;

    if (parser->isSet(npOption)) {
        np = parser->value(npOption).toLongLong();
        dtkTrace() << "got np value from command line:" << np ;
        policy.setNWorkers(np);
    }

    if (parser->isSet(smpOption)) {
        smp = parser->value(smpOption);
    }

    policy.setType(policyType);
}





/* @(#)dtkDistributedPolicy.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/18 15:18:41
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkCore.h>

#include "dtkDistributedApplication.h"
#include "dtkDistributedPolicy.h"

#include <dtkDistributed>
#include <dtkLog>

class dtkDistributedPolicyPrivate
{
public:
    QStringList hosts;

public:
    qlonglong np;
    QString type;

public:
    dtkDistributedCommunicator *comm;
};

/*!
  \class dtkDistributedPolicy
  \inmodule dtkDistributed
  \brief dtkDistributedPolicy is used to setup the communicator  (plugin, hostnames, number of processes)


  The policy can be set directly (using dtkDistributedPolicy::addHosts) or can be discover from the environments.
  OAR and Torque resources can be discover automatically; you can also use the DTK_NUM_PROCS variable.

*/

dtkDistributedPolicy::dtkDistributedPolicy(void) : QObject(), d(new dtkDistributedPolicyPrivate)
{
    d->comm = NULL;
    d->np       = 0;
    d->type = "qthread";
}

dtkDistributedPolicy::~dtkDistributedPolicy(void)
{
    delete d;

    d = NULL;
}

dtkDistributedPolicy::dtkDistributedPolicy(const dtkDistributedPolicy& other)
{
}

dtkDistributedPolicy& dtkDistributedPolicy::operator = (const dtkDistributedPolicy& other)
{
    return (*this);
}

void dtkDistributedPolicy::addHost(QString host)
{
    if (d->np == 0 || d->np > d->hosts.count()) {
        d->hosts.append(host);
    } else {
        dtkTrace() << "np reached, don't add host " << host;
    }
}

dtkDistributedCommunicator *dtkDistributedPolicy::communicator(void)
{
    return d->comm;
}

void dtkDistributedPolicy::setType(const QString& type)
{
    dtkDebug() << "create" << type << "communicator";
    d->type = type;
    d->comm = dtkDistributed::communicator::pluginFactory().create(type);
    if (!d->comm)
        qWarning() << "NULL communicator !!" << type;
}

QStringList dtkDistributedPolicy::types(void)
{
    return dtkDistributed::communicator::pluginFactory().keys();
}

QStringList dtkDistributedPolicy::hosts(void)
{
    if (d->hosts.count() == 0) {
        //Try to get hostsfile from env
        QStringList schedulers;
        schedulers << "PBS_NODEFILE";
        schedulers << "OAR_NODEFILE";
        if (d->np == 0) {
            QByteArray numprocs = qgetenv("DTK_NUM_PROCS");
            if (!numprocs.isEmpty()) {
                d->np = numprocs.toInt();
                dtkDebug() << "got num procs from env" << d->np;
            }
        }
        foreach (QString envname, schedulers) {
            QString nodefile =  QString::fromUtf8(qgetenv(qPrintable(envname)));
            if (!nodefile.isEmpty()) {
               dtkDebug() << "Extracting hosts from file" << nodefile;
                QFile file(nodefile);
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    dtkWarn() << "Error while opening"<< nodefile;
                    return d->hosts;
                }
                QTextStream in(&file);
                qlonglong np = 0;
                while (!in.atEnd()) {
                    this->addHost(in.readLine());
                    np ++;
                }
                if (d->np > 0) {
                    // will add extra hosts if d->np is > number of hosts in file
                    this->setNWorkers(d->np);
                }
                return d->hosts;
            }
        }
        dtkDebug() << "No hostfile found, try DTK envs";
        if (d->np == 0) {
            QByteArray numprocs = qgetenv("DTK_NUM_PROCS");
            if (!numprocs.isEmpty()) {
                d->np = numprocs.toInt();
                dtkDebug() << "got num procs from env" << d->np;
            } else {
                d->np = 1;
            }
        }
        for (int i = 0; i <  d->np; i++) {
            d->hosts <<  "localhost";
        }
        dtkDebug() << "policy updated, hosts:" << d->hosts.count() ;
    }
    return d->hosts;
}

void dtkDistributedPolicy::setNWorkers(qlonglong np)
{
    d->np = np;
    if (d->hosts.count() > 0) {
        if (d->np > d->hosts.count()) {
            qlonglong i = 0;
            while (d->hosts.count() < d->np) {
                d->hosts << d->hosts.at(i);
                ++i;
            }
        } else {
            while (d->np < d->hosts.count())
                d->hosts.removeLast();
        }
    }
}


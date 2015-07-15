/* dtkDistributedPolicy.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/18 15:18:41
 */

#include <dtkCore/dtkCore.h>

#include "dtkDistributedApplication.h"
#include "dtkDistributedPolicy.h"

#include <dtkDistributed>
#include <dtkLog>

// helper functions ////////////////////////

QStringList hostsFromScheduler(void)
{
    QStringList hosts;
    QStringList schedulers;
    schedulers << "PBS_NODEFILE";
    schedulers << "OAR_NODEFILE";

    foreach (QString envname, schedulers) {
        QString nodefile =  QString::fromUtf8(qgetenv(qPrintable(envname)));
        if (!nodefile.isEmpty()) {
            dtkDebug() << "Extracting hosts from file" << nodefile;
            QFile file(nodefile);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                dtkWarn() << "Error while opening"<< nodefile;
                return hosts;
            }
            QTextStream in(&file);
            while (!in.atEnd()) {
                hosts << in.readLine();
            }
        }
    }
    return hosts;
}

// dtkDistributedPolicyPrivate class ////////////////////////

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

  Some communicator plugins will be able to spawn processes on non
  local host, the default one (qthread) is only able to spawn
  processes on the local machine (using shared memory for
  communications)
*/

dtkDistributedPolicy::dtkDistributedPolicy(void) : QObject(), d(new dtkDistributedPolicyPrivate)
{
    d->comm = NULL;
    d->np   = 0;
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

/*! \fn void dtkDistributedPolicy::addHost(const QString& host)

  Add \a host: to the current hosts list.

*/

void dtkDistributedPolicy::addHost(const QString& host)
{
    d->hosts.append(host);
}

/*! \fn dtkDistributedCommunicator *dtkDistributedPolicy::communicator(void) const

  Return the current communicator pointer.

*/

dtkDistributedCommunicator *dtkDistributedPolicy::communicator(void) const
{
    return d->comm;
}

/*! \fn void dtkDistributedPolicy::setType(const QString& type)

  Set communicator implementation \a type. Default is "qthread". "mpi" or "mpi3" plugins can also be available.
*/
void dtkDistributedPolicy::setType(const QString& type)
{
    dtkDebug() << "create" << type << "communicator";
    d->type = type;
    d->comm = dtkDistributed::communicator::pluginFactory().create(type);
    if (!d->comm)
        qWarning() << "NULL communicator !!" << type;
}

QStringList dtkDistributedPolicy::types(void) const
{
    return dtkDistributed::communicator::pluginFactory().keys();
}


/*! \fn void dtkDistributedPolicy::setHostsFromEnvironment(void) {

  Try to detect the hosts file from a scheduler environment variables. Torque and OAR are currently supported.
*/
void dtkDistributedPolicy::setHostsFromEnvironment(void) {

    QStringList hosts = hostsFromScheduler();

    if (hosts.count() == 0) {
        dtkWarn() << "No hosts defined or found from scheduler, will use localhost";
        this->addHost("localhost");
    } else {
        d->hosts = hosts;
    }

    if (d->np == 0) {
        QByteArray numprocs = qgetenv("DTK_NUM_PROCS");
        if (!numprocs.isEmpty()) {
            d->np = numprocs.toInt();
            dtkInfo() << "got num procs from env" << d->np;
            this->setNWorkers(d->np);
        } else {
            d->np = hosts.size();
        }
    }
}


/*! \fn QStringList dtkDistributedPolicy::hosts(void) const

  Return the hosts list where the communicator will be spawned. If the
  number of workers is greater than the hosts size, more than one
  process can be started on a host.
*/
QStringList dtkDistributedPolicy::hosts(void) const
{
    return d->hosts;
}

/*! \fn void dtkDistributedPolicy::setNWorkers (qlonglong np)

  Set the total number of processes that will be spawned on hosts to \a np
  \sa hosts()
*/

void dtkDistributedPolicy::setNWorkers(qlonglong np)
{
    d->np = np;
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


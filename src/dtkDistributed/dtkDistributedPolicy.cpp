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

#include "dtkDistributedPolicy.h"

#include <dtkDistributed>

class dtkDistributedPolicyPrivate
{
public:
    QStringList hosts;

public:
    qlonglong nthreads;
    QString type;

public:
    dtkDistributedCommunicator *comm;
};

dtkDistributedPolicy::dtkDistributedPolicy(void) : QObject(), d(new dtkDistributedPolicyPrivate)
{
    d->comm = NULL;
    d->nthreads = 1;
    d->type = "qthread";
}

dtkDistributedPolicy::~dtkDistributedPolicy(void)
{
    if (d->comm) {
        delete d->comm;
    }

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
    qDebug() << "add host " << host;

    d->hosts.append(host);
}

dtkDistributedCommunicator *dtkDistributedPolicy::communicator(void)
{
    return d->comm;
}

void dtkDistributedPolicy::setType(const QString& type)
{
    qDebug() << "create" << type << "communicator";
    d->type = type;
    d->comm = dtkDistributed::communicator::pluginFactory().create(type);
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
        foreach (QString envname, schedulers) {
            QString nodefile =  QString::fromUtf8(qgetenv(qPrintable(envname)));
            if (!nodefile.isEmpty()) {
                qDebug() << "Extracting hosts from file" << nodefile;
                QFile file(nodefile);
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    qWarning() << "Error while opening"<< nodefile;
                    return d->hosts;
                }
                QTextStream in(&file);
                while (!in.atEnd()) {
                    d->hosts <<  in.readLine();
                }
                if (d->type == "hybrid") {
                    d->nthreads = d->hosts.count();
                    d->hosts.removeDuplicates();
                    d->nthreads /= d->hosts.count();
                }
                return d->hosts;
            }
        }
        qDebug() << "No hostfile found, try qapp args";
        if (dtkCoreApplicationArgumentsContain(qApp,"-np")) {
             int np = dtkCoreApplicationArgumentsValue(qApp,"-np").toInt();
             for (int i = 0; i <  np; i++) {
                d->hosts <<  "localhost";
             }
        } else {
            d->hosts <<  "localhost";
            d->nthreads = 1;
        }
        if (dtkCoreApplicationArgumentsContain(qApp,"-nt")) { // number of threads
                if (d->type == "mpi") {
                    int nt = dtkCoreApplicationArgumentsValue(qApp,"-nt").toInt();
                    int total = d->hosts.count() * nt;
                    for (int i = d->hosts.count(); i <  total; i++) {
                        d->hosts <<  "localhost";
                    }
                } else {
                    d->nthreads = dtkCoreApplicationArgumentsValue(qApp,"-nt").toInt();
                }
        }
        qDebug() << "policy updated, hosts:" << d->hosts.count() << "threads:" <<  d->nthreads;
    }
    return d->hosts;
}

void dtkDistributedPolicy::setNThreads(qlonglong nthreads)
{
    d->nthreads = nthreads;
}

qlonglong dtkDistributedPolicy::nthreads(void)
{
    return d->nthreads;
}


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

#include "dtkDistributedPolicy.h"

#include <dtkDistributed>

class dtkDistributedPolicyPrivate
{
public:
    QStringList hosts;

public:
    dtkDistributedCommunicator *comm;
};

dtkDistributedPolicy::dtkDistributedPolicy(void) : QObject(), d(new dtkDistributedPolicyPrivate)
{
    d->comm = NULL;
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
    qDebug() << "add host " << host;

    d->hosts.append(host);
}

dtkDistributedCommunicator *dtkDistributedPolicy::communicator(void)
{
    return d->comm;
}

void dtkDistributedPolicy::setType(dtkDistributedPolicy::Type type)
{
    switch (type) {
    case dtkDistributedPolicy::MP :
        qDebug() << "create mpi communicator";
        d->comm = dtkDistributed::communicator::pluginFactory().create("mpi");
        break;
    case dtkDistributedPolicy::MT :
        qDebug() << "create qthread communicator";
        d->comm = dtkDistributed::communicator::pluginFactory().create("qthread");
        break;
    default:
        qDebug() << "unkwown policy ";
    }
}

QStringList dtkDistributedPolicy::hosts(void)
{
    return d->hosts;
}

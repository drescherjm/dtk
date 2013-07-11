/* @(#)dtkDistributedWorkerManager.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/14 13:20:59
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedWorkerManager.h"

#include "dtkDistributedCommunicator.h"
#include "dtkDistributedPolicy.h"
#include "dtkDistributedWorker.h"

class dtkDistributedWorkerManagerPrivate
{

public:
    dtkDistributedCommunicator *comm;
    dtkDistributedPolicy *policy;
    dtkDistributedWorker worker;

public:
    bool spawned;

};

dtkDistributedWorkerManager::dtkDistributedWorkerManager(void) : QObject(), d(new dtkDistributedWorkerManagerPrivate)
{
    d->comm    = NULL;
    d->policy  = NULL;
    d->spawned = false;
}

dtkDistributedWorkerManager::~dtkDistributedWorkerManager(void)
{
    delete d;

    d = NULL;
}

dtkDistributedWorkerManager::dtkDistributedWorkerManager(const dtkDistributedWorkerManager& other)
{
}

dtkDistributedWorkerManager& dtkDistributedWorkerManager::operator = (const dtkDistributedWorkerManager& other)
{
    return (*this);
}

void dtkDistributedWorkerManager::setCommunicator(dtkDistributedCommunicator *comm)
{
    d->comm = comm;
}

void dtkDistributedWorkerManager::setPolicy(dtkDistributedPolicy *policy)
{
    d->policy = policy;
    d->comm = policy->communicator();
}

void dtkDistributedWorkerManager::spawn(void)
{
    if (d->spawned)
        return;

    d->worker.setCommunicator(d->comm);

    QStringList hosts = d->policy->hosts();
    d->comm->spawn(hosts, d->policy->nthreads() * hosts.count() , d->worker);
    d->spawned = true;
}

void dtkDistributedWorkerManager::exec(dtkDistributedWork *work)
{
    d->comm->exec( work );
}

void dtkDistributedWorkerManager::unspawn(void)
{
    d->comm->unspawn();
    d->spawned = false;
}

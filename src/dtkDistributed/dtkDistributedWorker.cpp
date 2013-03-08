/* @(#)dtkDistributedWorker.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/15 13:57:56
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkDistributedWorker.h"

#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedArray.h>
#include <dtkDistributed/dtkDistributedWork.h>

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkDistributedWorkerPrivate
// /////////////////////////////////////////////////////////////////

class dtkDistributedWorkerPrivate
{
public:
    qlonglong wid;
    qlonglong wct;
    qlonglong container_count;

public:
    QHash<dtkDistributedContainer*, qlonglong> containers;

public:
    dtkDistributedCommunicator *comm;
    dtkDistributedWork *work;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedWorker
// /////////////////////////////////////////////////////////////////


dtkDistributedWorker::dtkDistributedWorker(void) : QRunnable(), d(new dtkDistributedWorkerPrivate)
{
    d->comm = NULL;
    d->work = NULL;
    d->wid  =   -1;
    d->wct  =    0;
    d->container_count  = 0;

    this->setAutoDelete(false);
}

dtkDistributedWorker::~dtkDistributedWorker(void)
{
    if (d->work)
        delete d->work;

    delete d;

    d = NULL;
}

dtkDistributedWorker::dtkDistributedWorker(const dtkDistributedWorker& other): QRunnable(), d(new dtkDistributedWorkerPrivate)
{
    d->wid  = other.d->wid;
    d->wct  = other.d->wct;
    d->comm = other.d->comm;
    d->work = NULL;
    this->setAutoDelete(false);
    d->container_count = 0; // do not share containers count
}

dtkDistributedWorker& dtkDistributedWorker::operator = (const dtkDistributedWorker& other)
{
    d->wid  = other.d->wid;
    d->wct  = other.d->wct;
    d->comm = other.d->comm;
    d->container_count = 0; // do not share containers count
    return (*this);
}

void dtkDistributedWorker::setMode(const dtkDistributed::Mode& mode)
{	
    QHashIterator<dtkDistributedContainer*, qlonglong> it(d->containers);

    while( it.hasNext()) {
        it.next();
        it.key()->setMode(mode);
    }
}

void dtkDistributedWorker::setWid(qlonglong wid)
{
    d->wid = wid;
}

void dtkDistributedWorker::setWct(qlonglong wct)
{
    d->wct = wct;
}

bool dtkDistributedWorker::master(void)
{
    return (d->wid == 0);
}

qlonglong dtkDistributedWorker::wid(void)
{
    return d->wid;
}

qlonglong dtkDistributedWorker::wct(void)
{
    return d->wct;
}

qlonglong dtkDistributedWorker::record(dtkDistributedContainer *container)
{
    d->containers.insert(container, d->container_count);

    return d->container_count++;
}

void dtkDistributedWorker::unrecord(dtkDistributedContainer *container)
{
    d->containers.remove(container);
}

qlonglong dtkDistributedWorker::containerId(dtkDistributedContainer *container)
{
    return d->containers.value(container);
}

void dtkDistributedWorker::setWork(dtkDistributedWork *work)
{
    if (!work)
        return;

    d->work = work->clone();
    d->work->setWorker(this);
}

void dtkDistributedWorker::setCommunicator(dtkDistributedCommunicator *comm)
{
    d->comm = comm;
}

dtkDistributedCommunicator *dtkDistributedWorker::communicator(void)
{
    return d->comm;
}

void dtkDistributedWorker::run(void)
{
    qDebug() << "thread " << d->wid << "barrier";
    d->comm->barrier();
    qDebug() << "thread " << d->wid << "barrier released, run";
    d->work->run();
    qDebug() << "thread " << d->wid << "run finished, barrier";
    d->comm->barrier();
}

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
    d->wid  = -1;
    d->wct  = 0;
}

dtkDistributedWorker::~dtkDistributedWorker(void)
{
    delete d;

    d = NULL;
}

dtkDistributedWorker::dtkDistributedWorker(const dtkDistributedWorker& other): QRunnable(), d(new dtkDistributedWorkerPrivate)
{
    d->wid  = other.d->wid;
    d->wct  = other.d->wct;
    d->comm = other.d->comm;
    d->work = other.d->work->clone();
    d->work->setWorker(this);
}

dtkDistributedWorker& dtkDistributedWorker::operator = (const dtkDistributedWorker& other)
{
    return *this;

}

void dtkDistributedWorker::setWid(qlonglong wid)
{
    d->wid = wid;
}

void dtkDistributedWorker::setWct(qlonglong wct)
{
    d->wct = wct;
}

qlonglong dtkDistributedWorker::wid(void)
{
    return d->wid;
}

qlonglong dtkDistributedWorker::wct(void)
{
    return d->wct;
}

void dtkDistributedWorker::setWork(dtkDistributedWork *work)
{
    d->work = work;
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

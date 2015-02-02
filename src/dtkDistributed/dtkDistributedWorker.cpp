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

    this->setAutoDelete(false);
}

dtkDistributedWorker::~dtkDistributedWorker(void)
{
    // if (d->work)
    //     delete d->work;

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
}

dtkDistributedWorker& dtkDistributedWorker::operator = (const dtkDistributedWorker& other)
{
    d->wid  = other.d->wid;
    d->wct  = other.d->wct;
    d->comm = other.d->comm;
    return (*this);
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

void dtkDistributedWorker::setWork(dtkDistributedWork *work)
{
    if (!work)
        return;

    d->work = work;
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
    d->comm->barrier();
    d->work->run();
    d->comm->barrier();
}

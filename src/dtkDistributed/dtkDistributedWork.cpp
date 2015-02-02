/* @(#)dtkDistributedWork.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/15 14:10:44
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkDistributedWork.h"
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCoreApplication.h>
#include <dtkDistributed/dtkDistributedWorker.h>

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkDistributedWorkPrivate
// /////////////////////////////////////////////////////////////////

class dtkDistributedWorkPrivate
{
public:
    dtkDistributedWorker *worker;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedWork
// /////////////////////////////////////////////////////////////////


dtkDistributedWork::dtkDistributedWork(void) : QObject(), d(new dtkDistributedWorkPrivate)
{
    d->worker = NULL;
}

dtkDistributedWork::~dtkDistributedWork(void)
{
    delete d;

    d = NULL;
}

dtkDistributedWork::dtkDistributedWork(const dtkDistributedWork& other) : QObject(), d(new dtkDistributedWorkPrivate)
{
    d->worker = other.d->worker;

}

dtkDistributedWork& dtkDistributedWork::operator = (const dtkDistributedWork& other)
{
    return *this;

}

dtkDistributedCommunicator *dtkDistributedWork::communicator(void)
{
    return  dtkDistributed::app()->communicator() ;
}

void dtkDistributedWork::barrier(void)
{
    dtkDistributed::app()->communicator()->barrier() ;
}

qlonglong dtkDistributedWork::wct(void)
{
    return  dtkDistributed::app()->communicator()->size() ;
}

qlonglong dtkDistributedWork::wid(void)
{
    return  dtkDistributed::app()->communicator()->wid() ;
}

bool dtkDistributedWork::isMaster(void)
{
    return (wid() == 0) ;
}

void dtkDistributedWork::run(void)
{
    qDebug() << "should be implemented in sub classes";
}



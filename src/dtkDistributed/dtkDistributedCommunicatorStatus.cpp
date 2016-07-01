/* @(#)dtkDistributedCommunicatorStatus.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/04/30 09:25:26
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedCommunicatorStatus.h"

class dtkDistributedCommunicatorStatusPrivate
{

public:
    int       tag;
    qlonglong  count;
    qint32 source;
    int     error;

};

dtkDistributedCommunicatorStatus::dtkDistributedCommunicatorStatus(void) : d(new dtkDistributedCommunicatorStatusPrivate)
{
    d->tag    = 0;
    d->count  = -1;
    d->source = -1;
    d->error  = 0;

}

dtkDistributedCommunicatorStatus::~dtkDistributedCommunicatorStatus(void)
{
    delete d;

    d = NULL;
}

qlonglong dtkDistributedCommunicatorStatus::count(void) const
{
    return d->count;
}

qint32 dtkDistributedCommunicatorStatus::source(void) const
{
    return d->source;
}

int dtkDistributedCommunicatorStatus::error(void) const
{
    return d->error;
}

int dtkDistributedCommunicatorStatus::tag(void) const
{
    return d->tag;
}

void dtkDistributedCommunicatorStatus::setTag(int tag)
{
    d->tag = tag;
}

void dtkDistributedCommunicatorStatus::setCount(qlonglong count)
{
    d->count = count;
}

void dtkDistributedCommunicatorStatus::setSource(qint32 source)
{
    d->source = source;
}

void dtkDistributedCommunicatorStatus::setError(qint32 error)
{
    d->error = error;
}


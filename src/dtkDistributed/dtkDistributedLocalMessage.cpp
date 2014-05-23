/* @(#)dtkDistributedLocalMessage.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/21 15:48:20
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedLocalMessage.h"

class dtkDistributedLocalMessagePrivate
{
public:
    QWaitCondition wait;
    QMutex        mutex;

public:
    qint32 tag;
    qint32 source;
    bool   wait_for_data;

public:
    QVariant data;
};


dtkDistributedLocalMessage::dtkDistributedLocalMessage(): d(new dtkDistributedLocalMessagePrivate)
{
    d->tag = 0;
    d->source = -1;
    d->wait_for_data = false;
}

dtkDistributedLocalMessage::dtkDistributedLocalMessage(QVariant &v, qint32 source, qint32 tag): d(new dtkDistributedLocalMessagePrivate)
{
    d->tag    = tag;
    d->source = source;
    d->data   = v;
    d->wait_for_data = false;
}

dtkDistributedLocalMessage::~dtkDistributedLocalMessage(void)
{
    delete d;
    d = NULL;
}

void dtkDistributedLocalMessage::lock(void)
{
    d->mutex.lock();
}

void dtkDistributedLocalMessage::unlock(void)
{
    d->mutex.unlock();
}

void dtkDistributedLocalMessage::wait(void)
{
    d->wait.wait(&(d->mutex));
}

bool dtkDistributedLocalMessage::wait_for_data(void)
{
    return d->wait_for_data;
}

void dtkDistributedLocalMessage::wake(void)
{
    d->wait.wakeOne();
}

QVariant &dtkDistributedLocalMessage::data(void)
{
    return d->data;
}

qint32 dtkDistributedLocalMessage::tag(void)
{
    return d->tag;
}

qint32 dtkDistributedLocalMessage::source(void)
{
    return d->source;
}

void dtkDistributedLocalMessage::setWaitData(bool wait)
{
    d->wait_for_data = wait;
}

void dtkDistributedLocalMessage::setData(QVariant data)
{
    d->data = data;
}

void dtkDistributedLocalMessage::setTag(qint32 tag)
{
    d->tag = tag;
}

void dtkDistributedLocalMessage::setSource(qint32 source)
{
    d->source = source;
}

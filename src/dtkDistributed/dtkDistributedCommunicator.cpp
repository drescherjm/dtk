/* @(#)dtkDistributedCommunicator.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/07 13:59:41
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedCommunicator.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedCommunicatorPrivate
// /////////////////////////////////////////////////////////////////

class dtkDistributedCommunicatorPrivate
{
public:
    QMap<qlonglong, void *> buffer_map;

public:
    qlonglong id;

public:
    bool initialized;
};


// /////////////////////////////////////////////////////////////////
// dtkDistributedCommunicator
// /////////////////////////////////////////////////////////////////


dtkDistributedCommunicator::dtkDistributedCommunicator(void) : QObject(), d(new dtkDistributedCommunicatorPrivate)
{
    d->id = 0;
    d->initialized = false;
}

dtkDistributedCommunicator::~dtkDistributedCommunicator(void)
{
    delete d;

    d = NULL;
}

dtkDistributedCommunicator::dtkDistributedCommunicator(const dtkDistributedCommunicator& other)
{

}

dtkDistributedCommunicator& dtkDistributedCommunicator::operator = (const dtkDistributedCommunicator& other)
{
    return *this;

}

void dtkDistributedCommunicator::initialize(void)
{
    d->initialized = true;
}

bool dtkDistributedCommunicator::initialized(void)
{
    return d->initialized;
}

void dtkDistributedCommunicator::uninitialize(void)
{
    d->initialized = false;
}

int dtkDistributedCommunicator::pid(void)
{
   return 0;
}

int dtkDistributedCommunicator::size(void)
{
   return 1;
}

void *dtkDistributedCommunicator::allocate(qlonglong count, qlonglong size, qlonglong& buffer_id)
{
    void *buffer = malloc(size*count);
    d->buffer_map.insert(d->id, buffer);
    buffer_id = (d->id)++;
    return buffer;
}

void dtkDistributedCommunicator::get(qint32 from, qlonglong position, void *array, qlonglong buffer_id)
{

    if (d->buffer_map.contains(buffer_id)) {
        qlonglong *buffer = (qlonglong *)(d->buffer_map[buffer_id]);
        memcpy ( array, buffer + position, sizeof(qlonglong) );
    } else {
        qDebug() <<  "unknown buffer" << buffer_id;
    }
}

QByteArray dtkDistributedCommunicator::get(qint32 from, qlonglong position, qlonglong size, qlonglong buffer_id)
{
    return QByteArray();
}

void dtkDistributedCommunicator::put(qint32 dest, qlonglong position, void *data, qlonglong buffer_id)
{
    if (d->buffer_map.contains(buffer_id)) {
        qlonglong *buffer = (qlonglong *)(d->buffer_map[buffer_id]);
        memcpy ( buffer + position, data, sizeof(qlonglong) );

    } else {
        qDebug() <<  "unknown buffer" << buffer_id;
    }
}


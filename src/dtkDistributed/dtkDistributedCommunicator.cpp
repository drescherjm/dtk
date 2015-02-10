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
#include "dtkDistributedRequest.h"

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

/*!
  \class dtkDistributedCommunicator
  \inmodule dtkDistributed
  \brief ...
 */

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

bool dtkDistributedCommunicator::active(void)
{
    return false;
}

void dtkDistributedCommunicator::setPolicy(QString type)
{
}

/*! \fn dtkDistributedCommunicator::spawn (QStringList hostnames, qlonglong np)

  Spawn a communicator on all hostnames, starting np threads on each
  process.

*/

void dtkDistributedCommunicator::spawn(QStringList hostnames, qlonglong np)
{
    qDebug() << Q_FUNC_INFO;
}

void dtkDistributedCommunicator::unspawn(void)
{
}

void dtkDistributedCommunicator::exec(QRunnable *work)
{
//   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::barrier(void)
{
//   DTK_DEFAULT_IMPLEMENTATION;
}

qint32 dtkDistributedCommunicator::wid(void)
{
   return 0;
}

void dtkDistributedCommunicator::setWid(qint32 id)
{
}

qint32 dtkDistributedCommunicator::size(void)
{
   return 1;
}

void *dtkDistributedCommunicator::allocate(qlonglong count, qlonglong size, qlonglong wid, qlonglong& buffer_id)
{
    void *buffer = malloc(size*count);
    d->buffer_map.insert(d->id, buffer);
    buffer_id = (d->id)++;
    return buffer;
}

void dtkDistributedCommunicator::deallocate(qlonglong wid, const qlonglong& buffer_id)
{
    void *buffer = d->buffer_map.take(buffer_id);
    free (buffer);
}

void dtkDistributedCommunicator::send(char *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, Char, target, tag);
}

void dtkDistributedCommunicator::send(bool *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, Bool, target, tag);
}

void dtkDistributedCommunicator::send(int *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, Int, target, tag);
}

void dtkDistributedCommunicator::send(long *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, Long, target, tag);
}

void dtkDistributedCommunicator::send(qlonglong *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, Int64, target, tag);
}

void dtkDistributedCommunicator::send(float *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, Float, target, tag);
}

void dtkDistributedCommunicator::send(double *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, Double, target, tag);
}

void dtkDistributedCommunicator::send(const QVariant &v, qint32 target, qint32 tag)
{
    QByteArray bytes;
    QDataStream stream(&bytes,QIODevice::WriteOnly);
    stream << v;
    this->send(bytes, target, tag);
}

void dtkDistributedCommunicator::send(const QString& s, qint32 target, qint32 tag)
{
    QByteArray bytes = s.toUtf8();
    this->send(bytes, target, tag);
};

void dtkDistributedCommunicator::receive(char *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, Char, source, tag);
}

void dtkDistributedCommunicator::receive(bool *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, Bool, source, tag);
}

void dtkDistributedCommunicator::receive(int *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, Int, source, tag);
}

void dtkDistributedCommunicator::receive(long *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, Long, source, tag);
}

void dtkDistributedCommunicator::receive(qlonglong *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, Int64, source, tag);
}

void dtkDistributedCommunicator::receive(float *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, Float, source, tag);
}

void dtkDistributedCommunicator::receive(double *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, Double, source, tag);
}

void dtkDistributedCommunicator::receive(QVariant &v, qint32 target, qint32 tag)
{
    QByteArray bytes;
    this->receive(bytes, target, tag);
    QDataStream stream(&bytes,QIODevice::ReadOnly);
    stream >> v;
}

void dtkDistributedCommunicator::receive(QString &s, qint32 target, qint32 tag)
{
    QByteArray bytes;
    this->receive(bytes, target, tag);
    s = QString(bytes);
}

dtkDistributedRequest dtkDistributedCommunicator::ireceive(bool *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, Bool, source, tag);
}

dtkDistributedRequest dtkDistributedCommunicator::ireceive(char *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, Char, source, tag);
}

dtkDistributedRequest dtkDistributedCommunicator::ireceive(int *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, Int, source, tag);
}

dtkDistributedRequest dtkDistributedCommunicator::ireceive(long *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, Long, source, tag);
}

dtkDistributedRequest dtkDistributedCommunicator::ireceive(qint64 *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, Int64, source, tag);
}

dtkDistributedRequest dtkDistributedCommunicator::ireceive(float *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, Float, source, tag);
}

dtkDistributedRequest dtkDistributedCommunicator::ireceive(double *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, Double, source, tag);
}

void dtkDistributedCommunicator::reduce(void   *send, void   *recv, qint64 size, DataType dataType, OperationType operationType, qint32 target, bool all)
{
    qCritical() << "Default operator for reduce, not implemented";
}

void dtkDistributedCommunicator::reduce(bool *send, bool *recv, qint64 size, OperationType operationType, qint32 target, bool all)
{
    return this->reduce(send, recv, size, Bool, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(char *send, char *recv, qint64 size, OperationType operationType, qint32 target, bool all)
{
    return this->reduce(send, recv, size, Char, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(int *send, int *recv, qint64 size, OperationType operationType, qint32 target, bool all)
{
    return this->reduce(send, recv, size, Int, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(qlonglong *send, qlonglong *recv, qint64 size, OperationType operationType, qint32 target, bool all)
{
    return this->reduce(send, recv, size, Int64, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(float *send, float *recv, qint64 size, OperationType operationType, qint32 target, bool all)
{
    return this->reduce(send, recv, size, Float, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(double *send, double *recv, qint64 size, OperationType operationType, qint32 target, bool all)
{
    return this->reduce(send, recv, size, Double, operationType, target, all);
}

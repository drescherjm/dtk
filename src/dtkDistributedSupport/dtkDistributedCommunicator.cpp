/* dtkDistributedCommunicator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 13:38:59 2010 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedCommunicator.h"

#include <dtkCoreSupport/dtkGlobal.h>

class dtkDistributedCommunicatorPrivate
{
public:
    QMap<qlonglong, dtkDistributedMessage *> msg_map;

};

dtkDistributedCommunicator::dtkDistributedCommunicator(void) : QObject(), d(new dtkDistributedCommunicatorPrivate)
{

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
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

dtkDistributedCommunicator *dtkDistributedCommunicator::spawn(QString cmd, qlonglong np)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
   return new dtkDistributedCommunicator;
}

bool dtkDistributedCommunicator::initialized(void)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";

    return false;
}

void dtkDistributedCommunicator::uninitialize(void)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

int dtkDistributedCommunicator::rank(void)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
   return -1;
}

int dtkDistributedCommunicator::size(void)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
   return 0;
}

void dtkDistributedCommunicator::send(void   *data, qint64 size, DataType dataType, qint16 target, int tag)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}


void dtkDistributedCommunicator::send(dtkAbstractData *data,     qint16 target, int tag)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::send(const QString& s,   qint16 target, int tag)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::send(QByteArray& array,  qint16 target, int tag)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::receive(void *data, qint64 size, DataType dataType, qint16 source, int tag)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::receive(dtkAbstractData *&data, qint16 source, int tag)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::receive(QString &s, qint16 source, int tag)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::receive(QByteArray &v, qint16 source, int tag)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::receive(void   *data, qint64 size, DataType dataType, qint16 source, int tag, dtkDistributedCommunicatorStatus& status)
{
    DTK_UNUSED(data);
    DTK_UNUSED(size);
    DTK_UNUSED(dataType);
    DTK_UNUSED(source);
    DTK_UNUSED(tag);
    DTK_UNUSED(status);

    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::receive(QByteArray &v, qint16 source, int tag, dtkDistributedCommunicatorStatus &status)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::barrier(void)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::broadcast(void   *data, qint64 size, DataType dataType, qint16 source)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::gather(void   *send, void   *recv, qint64 size, DataType dataType, qint16 target, bool all)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::scatter(void   *send, void   *recv, qint64 size, DataType dataType, qint16 source)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::reduce(void   *send, void   *recv, qint64 size, DataType dataType, OperationType operationType, qint16 target, bool all)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::send(bool *data, qint64 size, qint16 target, int tag)
{
    return this->send(data, size, dtkDistributedCommunicatorBool, target, tag);
}

void dtkDistributedCommunicator::send(char *data, qint64 size, qint16 target, int tag)
{
    return this->send(data, size, dtkDistributedCommunicatorChar, target, tag);
}

void dtkDistributedCommunicator::send(int *data, qint64 size, qint16 target, int tag)
{
    return this->send(data, size, dtkDistributedCommunicatorInt, target, tag);
}

void dtkDistributedCommunicator::send(long *data, qint64 size, qint16 target, int tag)
{
    return this->send(data, size, dtkDistributedCommunicatorLong, target, tag);
}

void dtkDistributedCommunicator::send(qint64 *data, qint64 size, qint16 target, int tag)
{
    return this->send(data, size, dtkDistributedCommunicatorInt64, target, tag);
}

void dtkDistributedCommunicator::send(float *data, qint64 size, qint16 target, int tag)
{
    return this->send(data, size, dtkDistributedCommunicatorFloat, target, tag);
}

void dtkDistributedCommunicator::send(double *data, qint64 size, qint16 target, int tag)
{
    return this->send(data, size, dtkDistributedCommunicatorDouble, target, tag);
}

void dtkDistributedCommunicator::isend(void *data, qint64 size, DataType dataType, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::isend(bool *data, qint64 size, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->isend(data, size, dtkDistributedCommunicatorBool, target, tag, req);
}

void dtkDistributedCommunicator::isend(char *data, qint64 size, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->isend(data, size, dtkDistributedCommunicatorChar, target, tag, req);
}

void dtkDistributedCommunicator::isend(int *data, qint64 size, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->isend(data, size, dtkDistributedCommunicatorInt, target, tag, req);
}

void dtkDistributedCommunicator::isend(long *data, qint64 size, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->isend(data, size, dtkDistributedCommunicatorLong, target, tag, req);
}

void dtkDistributedCommunicator::isend(qint64 *data, qint64 size, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->isend(data, size, dtkDistributedCommunicatorInt64, target, tag, req);
}

void dtkDistributedCommunicator::isend(float *data, qint64 size, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->isend(data, size, dtkDistributedCommunicatorFloat, target, tag, req);
}

void dtkDistributedCommunicator::isend(double *data, qint64 size, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->isend(data, size, dtkDistributedCommunicatorDouble, target, tag, req);
}

void dtkDistributedCommunicator::isend(dtkAbstractData *data,     qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::isend(const QString& s,   qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::isend(QByteArray& array,  qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::receive(bool *data, qint64 size, qint16 source, int tag)
{
    return this->receive(data, size, dtkDistributedCommunicatorBool, source, tag);
}

void dtkDistributedCommunicator::receive(char *data, qint64 size, qint16 source, int tag)
{
    return this->receive(data, size, dtkDistributedCommunicatorChar, source, tag);
}

void dtkDistributedCommunicator::receive(int *data, qint64 size, qint16 source, int tag)
{
    return this->receive(data, size, dtkDistributedCommunicatorInt, source, tag);
}

void dtkDistributedCommunicator::receive(long *data, qint64 size, qint16 source, int tag)
{
    return this->receive(data, size, dtkDistributedCommunicatorLong, source, tag);
}

void dtkDistributedCommunicator::receive(qint64 *data, qint64 size, qint16 source, int tag)
{
    return this->receive(data, size, dtkDistributedCommunicatorInt64, source, tag);
}

void dtkDistributedCommunicator::receive(float *data, qint64 size, qint16 source, int tag)
{
    return this->receive(data, size, dtkDistributedCommunicatorFloat, source, tag);
}

void dtkDistributedCommunicator::receive(double *data, qint64 size, qint16 source, int tag)
{
    return this->receive(data, size, dtkDistributedCommunicatorDouble, source, tag);
}

void dtkDistributedCommunicator::ireceive(void *data, qint64 size, DataType dataType, qint16 source, int tag, dtkDistributedCommunicatorRequest *req)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::ireceive(bool *data, qint64 size, qint16 source, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->ireceive(data, size, dtkDistributedCommunicatorBool, source, tag, req);
}

void dtkDistributedCommunicator::ireceive(char *data, qint64 size, qint16 source, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->ireceive(data, size, dtkDistributedCommunicatorChar, source, tag, req);
}

void dtkDistributedCommunicator::ireceive(int *data, qint64 size, qint16 source, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->ireceive(data, size, dtkDistributedCommunicatorInt, source, tag, req);
}

void dtkDistributedCommunicator::ireceive(long *data, qint64 size, qint16 source, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->ireceive(data, size, dtkDistributedCommunicatorLong, source, tag, req);
}

void dtkDistributedCommunicator::ireceive(qint64 *data, qint64 size, qint16 source, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->ireceive(data, size, dtkDistributedCommunicatorInt64, source, tag, req);
}

void dtkDistributedCommunicator::ireceive(float *data, qint64 size, qint16 source, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->ireceive(data, size, dtkDistributedCommunicatorFloat, source, tag, req);
}

void dtkDistributedCommunicator::ireceive(double *data, qint64 size, qint16 source, int tag, dtkDistributedCommunicatorRequest *req)
{
    this->ireceive(data, size, dtkDistributedCommunicatorDouble, source, tag, req);
}


void dtkDistributedCommunicator::ireceive(dtkAbstractData *&data, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::ireceive(QString& s, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::ireceive(QByteArray& array, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::broadcast(bool *data, qint64 size, qint16 source)
{
    return this->broadcast(data, size, dtkDistributedCommunicatorBool, source);
}

void dtkDistributedCommunicator::broadcast(char *data, qint64 size, qint16 source)
{
    return this->broadcast(data, size, dtkDistributedCommunicatorChar, source);
}

void dtkDistributedCommunicator::broadcast(int *data, qint64 size, qint16 source)
{
    return this->broadcast(data, size, dtkDistributedCommunicatorInt, source);
}

void dtkDistributedCommunicator::broadcast(long *data, qint64 size, qint16 source)
{
    return this->broadcast(data, size, dtkDistributedCommunicatorLong, source);
}

void dtkDistributedCommunicator::broadcast(qint64 *data, qint64 size, qint16 source)
{
    return this->broadcast(data, size, dtkDistributedCommunicatorInt64, source);
}

void dtkDistributedCommunicator::broadcast(float *data, qint64 size, qint16 source)
{
    return this->broadcast(data, size, dtkDistributedCommunicatorFloat, source);
}

void dtkDistributedCommunicator::broadcast(double *data, qint64 size, qint16 source)
{
    return this->broadcast(data, size, dtkDistributedCommunicatorDouble, source);
}


void dtkDistributedCommunicator::broadcast(QString &s,   qint16 source)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::broadcast(QByteArray &v,qint16 source)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::broadcast(dtkAbstractData *&data, qint16 source)
{
    qCritical() << Q_FUNC_INFO << "NOT IMPLEMENTED";
}

void dtkDistributedCommunicator::gather(bool *send, bool *recv, qint64 size, qint16 target, bool all)
{
    return this->gather(send, recv, size, dtkDistributedCommunicatorBool, target, all);
}

void dtkDistributedCommunicator::gather(char *send, char *recv, qint64 size, qint16 target, bool all)
{
    return this->gather(send, recv, size, dtkDistributedCommunicatorChar, target, all);
}

void dtkDistributedCommunicator::gather(int *send, int *recv, qint64 size, qint16 target, bool all)
{
    return this->gather(send, recv, size, dtkDistributedCommunicatorInt, target, all);
}

void dtkDistributedCommunicator::gather(float *send, float *recv, qint64 size, qint16 target, bool all)
{
    return this->gather(send, recv, size, dtkDistributedCommunicatorFloat, target, all);
}

void dtkDistributedCommunicator::gather(double *send, double *recv, qint64 size, qint16 target, bool all)
{
    return this->gather(send, recv, size, dtkDistributedCommunicatorDouble, target, all);
}

void dtkDistributedCommunicator::scatter(bool *send, bool *recv, qint64 size, qint16 source)
{
    return this->scatter(send, recv, size, dtkDistributedCommunicatorBool, source);
}

void dtkDistributedCommunicator::scatter(char *send, char *recv, qint64 size, qint16 source)
{
    return this->scatter(send, recv, size, dtkDistributedCommunicatorChar, source);
}

void dtkDistributedCommunicator::scatter(int *send, int *recv, qint64 size, qint16 source)
{
    return this->scatter(send, recv, size, dtkDistributedCommunicatorInt, source);
}

void dtkDistributedCommunicator::scatter(float *send, float *recv, qint64 size, qint16 source)
{
    return this->scatter(send, recv, size, dtkDistributedCommunicatorFloat, source);
}

void dtkDistributedCommunicator::scatter(double *send, double *recv, qint64 size, qint16 source)
{
    return this->scatter(send, recv, size, dtkDistributedCommunicatorDouble, source);
}

void dtkDistributedCommunicator::reduce(bool *send, bool *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkDistributedCommunicatorBool, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(char *send, char *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkDistributedCommunicatorChar, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(int *send, int *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkDistributedCommunicatorInt, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(qlonglong *send, qlonglong *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkDistributedCommunicatorInt, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(float *send, float *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkDistributedCommunicatorFloat, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(double *send, double *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkDistributedCommunicatorDouble, operationType, target, all);
}

QMap<qlonglong, dtkDistributedMessage *> *dtkDistributedCommunicator::msgBuffer(void)
{
    return &(d->msg_map);
}



/*
 * Class dtkComposerCommunicatorRequest
 */


dtkDistributedCommunicatorRequest::dtkDistributedCommunicatorRequest(void)
{

}

dtkDistributedCommunicatorRequest::~dtkDistributedCommunicatorRequest(void)
{

}

void dtkDistributedCommunicatorRequest::wait(void)
{
}

/*
 * Class dtkComposerCommunicatorStatus
 */

class dtkDistributedCommunicatorStatusPrivate
{

public:
    int       tag;
    qint64  count;
    qint16 source;
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

dtkDistributedCommunicatorStatus::dtkDistributedCommunicatorStatus(const dtkDistributedCommunicatorStatus& other)
{
    d->tag    = other.tag();
    d->count  = other.count();
    d->source = other.source();
    d->error  = other.error();
}

dtkDistributedCommunicatorStatus& dtkDistributedCommunicatorStatus::operator = (const dtkDistributedCommunicatorStatus& other)
{
    return *this;
}


qint64 dtkDistributedCommunicatorStatus::count(void) const
{
    return d->count;
}

qint16 dtkDistributedCommunicatorStatus::source(void) const
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

void dtkDistributedCommunicatorStatus::setCount(qint64 count)
{
    d->count = count;
}

void dtkDistributedCommunicatorStatus::setSource(qint16 source)
{
    d->source = source;
}

void dtkDistributedCommunicatorStatus::setError(int error)
{
    d->error = error;
}



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

#include <dtkCore/dtkGlobal.h>

class dtkDistributedCommunicatorPrivate
{
public:
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
   DTK_DEFAULT_IMPLEMENTATION;
}

bool dtkDistributedCommunicator::initialized(void)
{
   DTK_DEFAULT_IMPLEMENTATION;

   return false;
}

void dtkDistributedCommunicator::uninitialize(void)
{
   DTK_DEFAULT_IMPLEMENTATION;
}

int dtkDistributedCommunicator::rank(void)
{
   DTK_DEFAULT_IMPLEMENTATION;
   return -1;
}

int dtkDistributedCommunicator::size(void)
{
   DTK_DEFAULT_IMPLEMENTATION;
   return 0;
}

void dtkDistributedCommunicator::send(void   *data, qint64 size, DataType dataType, qint16 target, int tag)
{
   DTK_DEFAULT_IMPLEMENTATION;
}


void dtkDistributedCommunicator::send(dtkAbstractData *data,     qint16 target, int tag)
{
   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::send(const QString& s,   qint16 target, int tag)
{
   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::send(QByteArray& array,  qint16 target, int tag)
{
   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::receive(void   *data, qint64 size, DataType dataType, qint16 source, int tag)
{
   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::receive(dtkAbstractData *&data, qint16 source, int tag)
{
   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::receive(QString &s, qint16 source, int tag)
{
   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::receive(QByteArray &v, qint16 source, int tag)
{
   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::barrier(void)
{
   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::broadcast(void   *data, qint64 size, DataType dataType, qint16 source)
{
   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::gather(void   *send, void   *recv, qint64 size, DataType dataType, qint16 target, bool all)
{
   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::scatter(void   *send, void   *recv, qint64 size, DataType dataType, qint16 source)
{
   DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicator::reduce(void   *send, void   *recv, qint64 size, DataType dataType, OperationType operationType, qint16 target, bool all)
{
   DTK_DEFAULT_IMPLEMENTATION;
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

void dtkDistributedCommunicator::reduce(float *send, float *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkDistributedCommunicatorFloat, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(double *send, double *recv, qint64 size, OperationType operationType, qint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkDistributedCommunicatorDouble, operationType, target, all);
}

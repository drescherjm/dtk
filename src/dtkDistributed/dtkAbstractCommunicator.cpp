/* dtkAbstractCommunicator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 13:38:59 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:11:15 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 71
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAbstractCommunicator.h"

#include <dtkCore/dtkGlobal.h>

class dtkAbstractCommunicatorPrivate
{
public:
};

dtkAbstractCommunicator::dtkAbstractCommunicator(void) : QObject(), d(new dtkAbstractCommunicatorPrivate)
{

}

dtkAbstractCommunicator::~dtkAbstractCommunicator(void)
{
    delete d;

    d = NULL;
}

int dtkAbstractCommunicator::send(const void *data, quint16 size, DataType dataType, quint16 target, MessageType messageType)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(size);
    DTK_UNUSED(dataType);
    DTK_UNUSED(target);
    DTK_UNUSED(messageType);
}

int dtkAbstractCommunicator::send(const bool *data, quint16 size, quint16 target, MessageType messageType)
{
    return this->send(data, size, dtkAbstractCommunicatorBool, target, messageType);
}

int dtkAbstractCommunicator::send(const char *data, quint16 size, quint16 target, MessageType messageType)
{
    return this->send(data, size, dtkAbstractCommunicatorChar, target, messageType);
}

int dtkAbstractCommunicator::send(const int *data, quint16 size, quint16 target, MessageType messageType)
{
    return this->send(data, size, dtkAbstractCommunicatorInt, target, messageType);
}

int dtkAbstractCommunicator::send(const float *data, quint16 size, quint16 target, MessageType messageType)
{
    return this->send(data, size, dtkAbstractCommunicatorFloat, target, messageType);
}

int dtkAbstractCommunicator::send(const double *data, quint16 size, quint16 target, MessageType messageType)
{
    return this->send(data, size, dtkAbstractCommunicatorDouble, target, messageType);
}

int dtkAbstractCommunicator::receive(const void *data, quint16 size, DataType dataType, quint16 target, MessageType messageType)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(size);
    DTK_UNUSED(dataType);
    DTK_UNUSED(target);
    DTK_UNUSED(messageType);
}

int dtkAbstractCommunicator::receive(const bool *data, quint16 size, quint16 target, MessageType messageType)
{
    return this->receive(data, size, dtkAbstractCommunicatorBool, target, messageType);
}

int dtkAbstractCommunicator::receive(const char *data, quint16 size, quint16 target, MessageType messageType)
{
    return this->receive(data, size, dtkAbstractCommunicatorChar, target, messageType);
}

int dtkAbstractCommunicator::receive(const int *data, quint16 size, quint16 target, MessageType messageType)
{
    return this->receive(data, size, dtkAbstractCommunicatorInt, target, messageType);
}

int dtkAbstractCommunicator::receive(const float *data, quint16 size, quint16 target, MessageType messageType)
{
    return this->receive(data, size, dtkAbstractCommunicatorFloat, target, messageType);
}

int dtkAbstractCommunicator::receive(const double *data, quint16 size, quint16 target, MessageType messageType)
{
    return this->receive(data, size, dtkAbstractCommunicatorDouble, target, messageType);
}

int dtkAbstractCommunicator::barrier(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

int dtkAbstractCommunicator::broadcast(const void *data, quint16 size, DataType dataType, quint16 source)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(size);
    DTK_UNUSED(dataType);
    DTK_UNUSED(source);
}

int dtkAbstractCommunicator::broadcast(const bool *data, quint16 size, quint16 source)
{
    return this->broadcast(data, size, dtkAbstractCommunicatorBool, source);
}

int dtkAbstractCommunicator::broadcast(const char *data, quint16 size, quint16 source)
{
    return this->broadcast(data, size, dtkAbstractCommunicatorChar, source);
}

int dtkAbstractCommunicator::broadcast(const int *data, quint16 size, quint16 source)
{
    return this->broadcast(data, size, dtkAbstractCommunicatorInt, source);
}

int dtkAbstractCommunicator::broadcast(const float *data, quint16 size, quint16 source)
{
    return this->broadcast(data, size, dtkAbstractCommunicatorFloat, source);
}

int dtkAbstractCommunicator::broadcast(const double *data, quint16 size, quint16 source)
{
    return this->broadcast(data, size, dtkAbstractCommunicatorDouble, source);
}

int dtkAbstractCommunicator::gather(const void *send, const void *recv, quint16 size, DataType dataType, quint16 target, bool all)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(send);
    DTK_UNUSED(recv);
    DTK_UNUSED(size);
    DTK_UNUSED(dataType);
    DTK_UNUSED(target);
    DTK_UNUSED(all);
}

int dtkAbstractCommunicator::gather(const bool *send, const bool *recv, quint16 size, quint16 target, bool all)
{
    return this->gather(send, recv, size, dtkAbstractCommunicatorBool, target, all);
}

int dtkAbstractCommunicator::gather(const char *send, const char *recv, quint16 size, quint16 target, bool all)
{
    return this->gather(send, recv, size, dtkAbstractCommunicatorChar, target, all);
}

int dtkAbstractCommunicator::gather(const int *send, const int *recv, quint16 size, quint16 target, bool all)
{
    return this->gather(send, recv, size, dtkAbstractCommunicatorInt, target, all);
}

int dtkAbstractCommunicator::gather(const float  *send, const float *recv, quint16 size, quint16 target, bool all)
{
    return this->gather(send, recv, size, dtkAbstractCommunicatorFloat, target, all);
}

int dtkAbstractCommunicator::gather(const double *send, const double *recv, quint16 size, quint16 target, bool all)
{
    return this->gather(send, recv, size, dtkAbstractCommunicatorDouble, target, all);
}

int dtkAbstractCommunicator::scatter(const void *send, const void *recv, quint16 size, DataType dataType, quint16 source)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(send);
    DTK_UNUSED(recv);
    DTK_UNUSED(size);
    DTK_UNUSED(dataType);
    DTK_UNUSED(source);
}

int dtkAbstractCommunicator::scatter(const bool *send, const bool *recv, quint16 size, quint16 source)
{
    return this->scatter(send, recv, size, dtkAbstractCommunicatorBool, source);
}

int dtkAbstractCommunicator::scatter(const char *send, const char *recv, quint16 size, quint16 source)
{
    return this->scatter(send, recv, size, dtkAbstractCommunicatorChar, source);
}

int dtkAbstractCommunicator::scatter(const int *send, const int *recv, quint16 size, quint16 source)
{
    return this->scatter(send, recv, size, dtkAbstractCommunicatorInt, source);
}

int dtkAbstractCommunicator::scatter(const float *send, const float *recv, quint16 size, quint16 source)
{
    return this->scatter(send, recv, size, dtkAbstractCommunicatorFloat, source);
}

int dtkAbstractCommunicator::scatter(const double *send, const double *recv, quint16 size, quint16 source)
{
    return this->scatter(send, recv, size, dtkAbstractCommunicatorDouble, source);
}

int dtkAbstractCommunicator::reduce(const void *send, const void *recv, quint16 size, DataType dataType, OperationType operationType, quint16 target, bool all)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(send);
    DTK_UNUSED(recv);
    DTK_UNUSED(size);
    DTK_UNUSED(dataType);
    DTK_UNUSED(operationType);
    DTK_UNUSED(target);
    DTK_UNUSED(all);
}

int dtkAbstractCommunicator::reduce(const bool *send, const bool *recv, quint16 size, OperationType operationType, quint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkAbstractCommunicatorBool, operationType, target, all);
}

int dtkAbstractCommunicator::reduce(const char *send, const char *recv, quint16 size, OperationType operationType, quint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkAbstractCommunicatorChar, operationType, target, all);
}

int dtkAbstractCommunicator::reduce(const int *send, const int *recv, quint16 size, OperationType operationType, quint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkAbstractCommunicatorInt, operationType, target, all);
}

int dtkAbstractCommunicator::reduce(const float *send, const float *recv, quint16 size, OperationType operationType, quint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkAbstractCommunicatorFloat, operationType, target, all);
}

int dtkAbstractCommunicator::reduce(const double *send, const double *recv, quint16 size, OperationType operationType, quint16 target, bool all)
{
    return this->reduce(send, recv, size, dtkAbstractCommunicatorDouble, operationType, target, all);
}

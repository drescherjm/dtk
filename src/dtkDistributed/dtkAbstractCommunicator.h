/* dtkAbstractCommunicator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 09:18:40 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:09:59 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTCOMMUNICATOR_H
#define DTKABSTRACTCOMMUNICATOR_H

#include <QtCore>

#include "dtkDistributedExport.h"

class dtkAbstractCommunicatorPrivate;

class DTKDISTRIBUTED_EXPORT dtkAbstractCommunicator : public QObject
{
    Q_OBJECT

public:
     dtkAbstractCommunicator(void);
    ~dtkAbstractCommunicator(void);

    enum MessageType {
        dtkAbstractCommunicatorBroadcast,
        dtkAbstractCommunicatorGather,
        dtkAbstractCommunicatorScatter,
        dtkAbstractCommunicatorReduce,
        dtkAbstractCommunicatorBarrier
    };

    enum DataType {
        dtkAbstractCommunicatorBool,
        dtkAbstractCommunicatorChar,
        dtkAbstractCommunicatorInt,
        dtkAbstractCommunicatorFloat,
        dtkAbstractCommunicatorDouble
    };

    enum OperationType {
        dtkAbstractCommunicatorMin,
        dtkAbstractCommunicatorMax,
        dtkAbstractCommunicatoyesrSum,
        dtkAbstractCommunicatorProduct,
        dtkAbstractCommunicatorBitwiseAnd,
        dtkAbstractCommunicatorBitwiseOr,
        dtkAbstractCommunicatorBitwiseXor,
        dtkAbstractCommunicatorLogicalAnd,
        dtkAbstractCommunicatorLogicalOr,
        dtkAbstractCommunicatorLogicalXor
    };

    virtual int      send(const void   *data, quint16 size, DataType dataType, quint16 target, MessageType messageType);
    virtual int      send(const bool   *data, quint16 size, quint16 target, MessageType messageType);
    virtual int      send(const char   *data, quint16 size, quint16 target, MessageType messageType);
    virtual int      send(const int    *data, quint16 size, quint16 target, MessageType messageType);
    virtual int      send(const float  *data, quint16 size, quint16 target, MessageType messageType);
    virtual int      send(const double *data, quint16 size, quint16 target, MessageType messageType);

    virtual int   receive(const void   *data, quint16 size, DataType dataType, quint16 target, MessageType messageType);
    virtual int   receive(const bool   *data, quint16 size, quint16 target, MessageType messageType);
    virtual int   receive(const char   *data, quint16 size, quint16 target, MessageType messageType);
    virtual int   receive(const int    *data, quint16 size, quint16 target, MessageType messageType);
    virtual int   receive(const float  *data, quint16 size, quint16 target, MessageType messageType);
    virtual int   receive(const double *data, quint16 size, quint16 target, MessageType messageType);

    virtual int   barrier(void);

    virtual int broadcast(const void   *data, quint16 size, DataType dataType, quint16 source);
    virtual int broadcast(const bool   *data, quint16 size, quint16 source);
    virtual int broadcast(const char   *data, quint16 size, quint16 source);
    virtual int broadcast(const int    *data, quint16 size, quint16 source);
    virtual int broadcast(const float  *data, quint16 size, quint16 source);
    virtual int broadcast(const double *data, quint16 size, quint16 source);

    virtual int    gather(const void   *send, const void   *recv, quint16 size, DataType dataType, quint16 target, bool all = false);
    virtual int    gather(const bool   *send, const bool   *recv, quint16 size, quint16 target, bool all = false);
    virtual int    gather(const char   *send, const char   *recv, quint16 size, quint16 target, bool all = false);
    virtual int    gather(const int    *send, const int    *recv, quint16 size, quint16 target, bool all = false);
    virtual int    gather(const float  *send, const float  *recv, quint16 size, quint16 target, bool all = false);
    virtual int    gather(const double *send, const double *recv, quint16 size, quint16 target, bool all = false);

    virtual int   scatter(const void   *send, const void   *recv, quint16 size, DataType dataType, quint16 source);
    virtual int   scatter(const bool   *send, const bool   *recv, quint16 size, quint16 source);
    virtual int   scatter(const char   *send, const char   *recv, quint16 size, quint16 source);
    virtual int   scatter(const int    *send, const int    *recv, quint16 size, quint16 source);
    virtual int   scatter(const float  *send, const float  *recv, quint16 size, quint16 source);
    virtual int   scatter(const double *send, const double *recv, quint16 size, quint16 source);

    virtual int    reduce(const void   *send, const void   *recv, quint16 size, DataType dataType, OperationType operationType, quint16 target, bool all = false);
    virtual int    reduce(const bool   *send, const bool   *recv, quint16 size, OperationType operationType, quint16 target, bool all = false);
    virtual int    reduce(const char   *send, const char   *recv, quint16 size, OperationType operationType, quint16 target, bool all = false);
    virtual int    reduce(const int    *send, const int    *recv, quint16 size, OperationType operationType, quint16 target, bool all = false);
    virtual int    reduce(const float  *send, const float  *recv, quint16 size, OperationType operationType, quint16 target, bool all = false);
    virtual int    reduce(const double *send, const double *recv, quint16 size, OperationType operationType, quint16 target, bool all = false);

private:
    dtkAbstractCommunicatorPrivate *d;
};

#endif

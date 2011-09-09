/* dtkDistributedCommunicator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 09:18:40 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Sep  9 13:04:03 2011 (+0200)
 *           By: jwintz
 *     Update #: 72
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCOMMUNICATOR_H
#define DTKDISTRIBUTEDCOMMUNICATOR_H

#include <QtCore>

#include "dtkDistributedExport.h"

class dtkDistributedCommunicatorPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedCommunicator : public QObject
{
    Q_OBJECT

public:
     dtkDistributedCommunicator(void);
    ~dtkDistributedCommunicator(void);

    enum DataType {
        dtkDistributedCommunicatorBool,
        dtkDistributedCommunicatorChar,
        dtkDistributedCommunicatorInt,
        dtkDistributedCommunicatorLong,
        dtkDistributedCommunicatorFloat,
        dtkDistributedCommunicatorDouble
    };

    enum OperationType {
        dtkDistributedCommunicatorMin,
        dtkDistributedCommunicatorMax,
        dtkDistributedCommunicatorSum,
        dtkDistributedCommunicatorProduct,
        dtkDistributedCommunicatorBitwiseAnd,
        dtkDistributedCommunicatorBitwiseOr,
        dtkDistributedCommunicatorBitwiseXor,
        dtkDistributedCommunicatorLogicalAnd,
        dtkDistributedCommunicatorLogicalOr,
        dtkDistributedCommunicatorLogicalXor
    };

    enum MessageType {
        dtkDistributedCommunicatorBarrier = 1
    };

    enum MessageTag {
        dtkDistributedCommunicatorSend    = 2001,
        dtkDistributedCommunicatorReceive = 2002
    };

    virtual void   initialize(void) = 0;
    virtual void uninitialize(void) = 0;

    virtual int rank(void) = 0;
    virtual int size(void) = 0;

    virtual void      send(void   *data, quint16 size, DataType dataType, quint16 target, int tag) = 0;
    virtual void      send(bool   *data, quint16 size, quint16 target, int tag);
    virtual void      send(char   *data, quint16 size, quint16 target, int tag);
    virtual void      send(int    *data, quint16 size, quint16 target, int tag);
    virtual void      send(long   *data, quint16 size, quint16 target, int tag);
    virtual void      send(float  *data, quint16 size, quint16 target, int tag);
    virtual void      send(double *data, quint16 size, quint16 target, int tag);

    virtual void   receive(void   *data, quint16 size, DataType dataType, quint16 source, int tag) = 0;
    virtual void   receive(bool   *data, quint16 size, quint16 source, int tag);
    virtual void   receive(char   *data, quint16 size, quint16 source, int tag);
    virtual void   receive(int    *data, quint16 size, quint16 source, int tag);
    virtual void   receive(long   *data, quint16 size, quint16 source, int tag);
    virtual void   receive(float  *data, quint16 size, quint16 source, int tag);
    virtual void   receive(double *data, quint16 size, quint16 source, int tag);

    virtual void   barrier(void) = 0;

    virtual void broadcast(void   *data, quint16 size, DataType dataType, quint16 source) = 0;
    virtual void broadcast(bool   *data, quint16 size, quint16 source);
    virtual void broadcast(char   *data, quint16 size, quint16 source);
    virtual void broadcast(int    *data, quint16 size, quint16 source);
    virtual void broadcast(float  *data, quint16 size, quint16 source);
    virtual void broadcast(double *data, quint16 size, quint16 source);

    virtual void    gather(void   *send, void   *recv, quint16 size, DataType dataType, quint16 target, bool all = false) = 0;
    virtual void    gather(bool   *send, bool   *recv, quint16 size, quint16 target, bool all = false);
    virtual void    gather(char   *send, char   *recv, quint16 size, quint16 target, bool all = false);
    virtual void    gather(int    *send, int    *recv, quint16 size, quint16 target, bool all = false);
    virtual void    gather(float  *send, float  *recv, quint16 size, quint16 target, bool all = false);
    virtual void    gather(double *send, double *recv, quint16 size, quint16 target, bool all = false);
                                         
    virtual void   scatter(void   *send, void   *recv, quint16 size, DataType dataType, quint16 source) = 0;
    virtual void   scatter(bool   *send, bool   *recv, quint16 size, quint16 source);
    virtual void   scatter(char   *send, char   *recv, quint16 size, quint16 source);
    virtual void   scatter(int    *send, int    *recv, quint16 size, quint16 source);
    virtual void   scatter(float  *send, float  *recv, quint16 size, quint16 source);
    virtual void   scatter(double *send, double *recv, quint16 size, quint16 source);
                                         
    virtual void    reduce(void   *send, void   *recv, quint16 size, DataType dataType, OperationType operationType, quint16 target, bool all = false) = 0;
    virtual void    reduce(bool   *send, bool   *recv, quint16 size, OperationType operationType, quint16 target, bool all = false);
    virtual void    reduce(char   *send, char   *recv, quint16 size, OperationType operationType, quint16 target, bool all = false);
    virtual void    reduce(int    *send, int    *recv, quint16 size, OperationType operationType, quint16 target, bool all = false);
    virtual void    reduce(float  *send, float  *recv, quint16 size, OperationType operationType, quint16 target, bool all = false);
    virtual void    reduce(double *send, double *recv, quint16 size, OperationType operationType, quint16 target, bool all = false);

private:
    dtkDistributedCommunicatorPrivate *d;
};

#endif

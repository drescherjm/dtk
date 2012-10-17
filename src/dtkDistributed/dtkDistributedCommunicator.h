/* dtkDistributedCommunicator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 09:18:40 2010 (+0100)
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
#include <dtkCore/dtkAbstractData.h>

class dtkDistributedCommunicatorPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedCommunicator : public QObject
{
    Q_OBJECT

public:
             dtkDistributedCommunicator(void);
    virtual ~dtkDistributedCommunicator(void);

public:
    dtkDistributedCommunicator(const dtkDistributedCommunicator& other);
    dtkDistributedCommunicator& operator = (const dtkDistributedCommunicator& other);

public:
    enum DataType {
        dtkDistributedCommunicatorBool,
        dtkDistributedCommunicatorChar,
        dtkDistributedCommunicatorInt,
        dtkDistributedCommunicatorLong,
        dtkDistributedCommunicatorInt64,
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

    virtual void   initialize(void);
    virtual bool  initialized(void);
    virtual void uninitialize(void);

    virtual int rank(void);
    virtual int size(void);

    virtual void      send(void   *data, qint64 size, DataType dataType, qint16 target, int tag);
    virtual void      send(bool   *data, qint64 size, qint16 target, int tag);
    virtual void      send(char   *data, qint64 size, qint16 target, int tag);
    virtual void      send(int    *data, qint64 size, qint16 target, int tag);
    virtual void      send(long   *data, qint64 size, qint16 target, int tag);
    virtual void      send(qint64 *data, qint64 size, qint16 target, int tag);
    virtual void      send(float  *data, qint64 size, qint16 target, int tag);
    virtual void      send(double *data, qint64 size, qint16 target, int tag);
    virtual void      send(dtkAbstractData *data,     qint16 target, int tag);
    virtual void      send(const QString& s,   qint16 target, int tag);
    virtual void      send(QByteArray& array,  qint16 target, int tag);

    virtual void   receive(void   *data, qint64 size, DataType dataType, qint16 source, int tag);
    virtual void   receive(void   *data, qint64 size, DataType dataType, qint16 source, int tag, int& from) {
        DTK_UNUSED(data);
        DTK_UNUSED(size);
        DTK_UNUSED(dataType);
        DTK_UNUSED(source);
        DTK_UNUSED(tag);
        DTK_UNUSED(from);

        DTK_DEFAULT_IMPLEMENTATION;
    }
    virtual void   receive(bool   *data, qint64 size, qint16 source, int tag);
    virtual void   receive(char   *data, qint64 size, qint16 source, int tag);
    virtual void   receive(int    *data, qint64 size, qint16 source, int tag);
    virtual void   receive(long   *data, qint64 size, qint16 source, int tag);
    virtual void   receive(qint64 *data, qint64 size, qint16 source, int tag);
    virtual void   receive(float  *data, qint64 size, qint16 source, int tag);
    virtual void   receive(double *data, qint64 size, qint16 source, int tag);
    virtual void   receive(dtkAbstractData *&data, qint16 source, int tag);
    virtual void   receive(QString &s,   qint16 source, int tag);
    virtual void   receive(QByteArray &v,  qint16 source, int tag);

    virtual void   barrier(void);

    virtual void broadcast(void   *data, qint64 size, DataType dataType, qint16 source);
    virtual void broadcast(bool   *data, qint64 size, qint16 source);
    virtual void broadcast(char   *data, qint64 size, qint16 source);
    virtual void broadcast(int    *data, qint64 size, qint16 source);
    virtual void broadcast(long   *data, qint64 size, qint16 source);
    virtual void broadcast(qint64 *data, qint64 size, qint16 source);
    virtual void broadcast(float  *data, qint64 size, qint16 source);
    virtual void broadcast(double *data, qint64 size, qint16 source);

    virtual void    gather(void   *send, void   *recv, qint64 size, DataType dataType, qint16 target, bool all = false);
    virtual void    gather(bool   *send, bool   *recv, qint64 size, qint16 target, bool all = false);
    virtual void    gather(char   *send, char   *recv, qint64 size, qint16 target, bool all = false);
    virtual void    gather(int    *send, int    *recv, qint64 size, qint16 target, bool all = false);
    virtual void    gather(float  *send, float  *recv, qint64 size, qint16 target, bool all = false);
    virtual void    gather(double *send, double *recv, qint64 size, qint16 target, bool all = false);

    virtual void   scatter(void   *send, void   *recv, qint64 size, DataType dataType, qint16 source);
    virtual void   scatter(bool   *send, bool   *recv, qint64 size, qint16 source);
    virtual void   scatter(char   *send, char   *recv, qint64 size, qint16 source);
    virtual void   scatter(int    *send, int    *recv, qint64 size, qint16 source);
    virtual void   scatter(float  *send, float  *recv, qint64 size, qint16 source);
    virtual void   scatter(double *send, double *recv, qint64 size, qint16 source);

    virtual void    reduce(void   *send, void   *recv, qint64 size, DataType dataType, OperationType operationType, qint16 target, bool all = false);
    virtual void    reduce(bool   *send, bool   *recv, qint64 size, OperationType operationType, qint16 target, bool all = false);
    virtual void    reduce(char   *send, char   *recv, qint64 size, OperationType operationType, qint16 target, bool all = false);
    virtual void    reduce(int    *send, int    *recv, qint64 size, OperationType operationType, qint16 target, bool all = false);
    virtual void    reduce(float  *send, float  *recv, qint64 size, OperationType operationType, qint16 target, bool all = false);
    virtual void    reduce(double *send, double *recv, qint64 size, OperationType operationType, qint16 target, bool all = false);

private:
    dtkDistributedCommunicatorPrivate *d;
};

Q_DECLARE_METATYPE(dtkDistributedCommunicator);
Q_DECLARE_METATYPE(dtkDistributedCommunicator *);

#endif

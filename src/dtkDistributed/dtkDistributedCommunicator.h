// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:


#pragma once

#include "dtkDistributedExport.h"
#include "dtkDistributedPolicy.h"

#include <dtkCore/dtkCorePlugin.h>

class dtkDistributedWork;
class dtkDistributedWorker;
class dtkDistributedCommunicatorPrivate;
class dtkDistributedCommunicatorStatus;

class DTKDISTRIBUTED_EXPORT dtkDistributedCommunicator : public QObject
{
    Q_OBJECT

public:
             dtkDistributedCommunicator(void);
    virtual ~dtkDistributedCommunicator(void);

public:
    static const qint32 ANY_TAG    = -1;
    static const qint32 BCAST_TAG  = -7;
    static const qint32 ANY_SOURCE = -1;

    enum DataType {
        Bool,
        Char,
        Int,
        Long,
        Int64,
        Float,
        Double
    };

    enum OperationType {
        None,
        Min,
        Max,
        Sum,
        Product,
        BitwiseAnd,
        BitwiseOr,
        BitwiseXor,
        LogicalAnd,
        LogicalOr,
        LogicalXor
    };

public:
    dtkDistributedCommunicator(const dtkDistributedCommunicator& other);
    dtkDistributedCommunicator& operator = (const dtkDistributedCommunicator& other);

public:
    virtual void  initialize(void);
    virtual bool  initialized(void);
    virtual void uninitialize(void);
    virtual bool       active(void);

public:
    virtual void setPolicy(QString type);

public:
    virtual void *allocate(qlonglong count, qlonglong size, qlonglong wid, qlonglong& buffer_id);

    virtual void deallocate(qlonglong wid, const qlonglong& buffer_id);
    virtual void rlock(qlonglong wid, const qlonglong& buffer_id)  = 0;
    virtual void wlock(qlonglong wid, const qlonglong& buffer_id)  = 0;
    virtual void unlock(qlonglong wid, const qlonglong& buffer_id) = 0;

public:
    virtual void get(qint32 from, qlonglong position, void *array, qlonglong buffer_id, qlonglong nelements = 1) = 0;
    virtual void put(qint32 dest, qlonglong position, void  *data, qlonglong buffer_id, qlonglong nelements = 1) = 0;

public:
    virtual void send(void   *data, qint64 size, DataType dataType, qint32 target, qint32 tag) = 0;
    virtual void send(bool   *data, qint64 size, qint32 target, int tag);
    virtual void send(int    *data, qint64 size, qint32 target, int tag);
    virtual void send(long   *data, qint64 size, qint32 target, int tag);
    virtual void send(qint64 *data, qint64 size, qint32 target, int tag);
    virtual void send(float  *data, qint64 size, qint32 target, int tag);
    virtual void send(double *data, qint64 size, qint32 target, int tag);
    virtual void send(char *data, qint64 size, qint32 target, qint32 tag);
    virtual void send(QByteArray& array, qint32 target, qint32 tag) = 0;
    virtual void send(const QVariant& v, qint32 target, qint32 tag);
    virtual void send(const QString& s, qint32 target, qint32 tag);

public:
    virtual void broadcast(qlonglong *data, qint64 size, qint32 source) = 0;
    virtual void broadcast(double    *data, qint64 size, qint32 source) = 0;
    virtual void broadcast(QByteArray& array, qint32 source) = 0;
    virtual void broadcast(QVariant& v, qint32 source) = 0;

public:
    virtual void receive(void   *data, qint64 size, DataType dataType, qint32 source, qint32 tag) = 0;
    virtual void receive(bool   *data, qint64 size, qint32 source, int tag);
    virtual void receive(int    *data, qint64 size, qint32 source, int tag);
    virtual void receive(long   *data, qint64 size, qint32 source, int tag);
    virtual void receive(qint64 *data, qint64 size, qint32 source, int tag);
    virtual void receive(float  *data, qint64 size, qint32 source, int tag);
    virtual void receive(double *data, qint64 size, qint32 source, int tag);
    virtual void receive(char   *data, qint64 size, qint32 source, qint32 tag);
    virtual void receive(QByteArray &v,qint32 source, qint32 tag) = 0 ;
    virtual void receive(QByteArray &v,qint32 source, qint32 tag, dtkDistributedCommunicatorStatus& status) = 0;
    virtual void receive(QVariant &v,  qint32 source, qint32 tag) ;
    virtual void receive(QString &s,   qint32 source, qint32 tag) ;
    /* virtual void receive(QVariant &v,  qint32 source, qint32 tag, dtkDistributedCommunicatorStatus& status) = 0; */

public:
    virtual void reduce(void   *send, void   *recv, qint64 size, DataType dataType, OperationType operationType, qint32 target, bool all = false);
    virtual void reduce(bool   *send, bool   *recv, qint64 size, OperationType operationType, qint32 target, bool all = false);
    virtual void reduce(char   *send, char   *recv, qint64 size, OperationType operationType, qint32 target, bool all = false);
    virtual void reduce(int    *send, int    *recv, qint64 size, OperationType operationType, qint32 target, bool all = false);
    virtual void reduce(qlonglong *send, qlonglong *recv, qint64 size, OperationType operationType, qint32 target, bool all = false);
    virtual void reduce(float  *send, float  *recv, qint64 size, OperationType operationType, qint32 target, bool all = false);
    virtual void reduce(double *send, double *recv, qint64 size, OperationType operationType, qint32 target, bool all = false);

public:
    virtual void spawn(QStringList hostnames, qlonglong np, dtkDistributedWorker& worker);
    virtual void  exec(dtkDistributedWork *work);

public:
    virtual void unspawn(void);
    virtual void barrier(void);

public:
    virtual qint32  wid(void);
    inline  qint32 rank(void) {return wid();};
    virtual qint32 size(void);

public:
    virtual void setWid(qint32 id);

public:
    dtkDistributedCommunicatorPrivate *d;
};

DTK_DECLARE_OBJECT(dtkDistributedCommunicator*)
DTK_DECLARE_PLUGIN(dtkDistributedCommunicator, DTKDISTRIBUTED_EXPORT)
DTK_DECLARE_PLUGIN_FACTORY(dtkDistributedCommunicator, DTKDISTRIBUTED_EXPORT)
DTK_DECLARE_PLUGIN_MANAGER(dtkDistributedCommunicator, DTKDISTRIBUTED_EXPORT)

//
// dtkDistributedCommunicator.h ends here

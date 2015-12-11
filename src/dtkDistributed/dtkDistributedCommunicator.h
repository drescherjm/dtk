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
class dtkDistributedCommunicatorPrivate;
class dtkDistributedCommunicatorStatus;
class dtkDistributedBufferManager;
class dtkDistributedRequest;


class DTKDISTRIBUTED_EXPORT dtkDistributedCommunicator : public QObject
{
    Q_OBJECT

public:
             dtkDistributedCommunicator(void);
    virtual ~dtkDistributedCommunicator(void);

public:
    // use the same value as defined in mpi.h from openmpi
    static const qint32 ANY_TAG    = -1;
    static const qint32 BCAST_TAG  = -7;
    static const qint32 ANY_SOURCE = -1;
    static const qint16 ROOT       = -4;
    static const qint16 PROC_NULL  = -2;

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

    enum MessageTag {
        TagSend    = 2001,
        TagReceive = 2002,
        TagReduce = 2003
    };

public:
    virtual void  initialize(void)  = 0;
    virtual bool  initialized(void) = 0;
    virtual void uninitialize(void) = 0;
    virtual bool       active(void) = 0;

public:
    virtual dtkDistributedBufferManager *createBufferManager(void) { return 0; } ;
    virtual void destroyBufferManager(dtkDistributedBufferManager *&) {;}

public:
    virtual void send(void   *data, qint64 size, QMetaType::Type dataType, qint32 target, qint32 tag) = 0;
    void send(bool   *data, qint64 size, qint32 target, int tag);
    void send(int    *data, qint64 size, qint32 target, int tag);
    void send(long   *data, qint64 size, qint32 target, int tag);
    void send(qint64 *data, qint64 size, qint32 target, int tag);
    void send(float  *data, qint64 size, qint32 target, int tag);
    void send(double *data, qint64 size, qint32 target, int tag);
    void send(char *data, qint64 size, qint32 target, qint32 tag);
    virtual void send(QByteArray& array, qint32 target, qint32 tag) = 0;
    virtual void send(const QVariant& v, qint32 target, qint32 tag);

public:
    template <typename T> void send(T data, qint32 target, qint32 tag);
    template <typename T> void receive(T &data, qint32 source, qint32 tag);

    template <typename T, typename U> void run(T* t, U (T::*functionPointer)());

public:
    virtual void broadcast(void *data, qint64 size, QMetaType::Type dataType, qint32 source) = 0;
    void broadcast(bool      *data, qint64 size, qint32 source);
    void broadcast(int       *data, qint64 size, qint32 source);
    void broadcast(long      *data, qint64 size, qint32 source);
    void broadcast(qlonglong *data, qint64 size, qint32 source);
    void broadcast(float     *data, qint64 size, qint32 source);
    void broadcast(double    *data, qint64 size, qint32 source);
    void broadcast(char      *data, qint64 size, qint32 source);
    virtual void broadcast(QByteArray& array, qint32 source) = 0;
    virtual void broadcast(QVariant& v, qint32 source) = 0;

public:
    virtual void receive(void   *data, qint64 size, QMetaType::Type dataType, qint32 source, qint32 tag) = 0;
    void receive(bool   *data, qint64 size, qint32 source, int tag);
    void receive(int    *data, qint64 size, qint32 source, int tag);
    void receive(long   *data, qint64 size, qint32 source, int tag);
    void receive(qint64 *data, qint64 size, qint32 source, int tag);
    void receive(float  *data, qint64 size, qint32 source, int tag);
    void receive(double *data, qint64 size, qint32 source, int tag);
    void receive(char   *data, qint64 size, qint32 source, qint32 tag);
    virtual void receive(QByteArray &v,qint32 source, qint32 tag) = 0 ;
    virtual void receive(QByteArray &v,qint32 source, qint32 tag, dtkDistributedCommunicatorStatus& status) = 0;
    virtual void receive(QVariant &v,  qint32 source, qint32 tag, dtkDistributedCommunicatorStatus& status);
    virtual void receive(QVariant &v,  qint32 source, qint32 tag) ;

    virtual dtkDistributedRequest *ireceive(void   *data, qint64 size, QMetaType::Type dataType, qint32 source, int tag) = 0;
    dtkDistributedRequest *ireceive(bool   *data, qint64 size, qint32 source, int tag);
    dtkDistributedRequest *ireceive(char   *data, qint64 size, qint32 source, int tag);
    dtkDistributedRequest *ireceive(int    *data, qint64 size, qint32 source, int tag);
    dtkDistributedRequest *ireceive(long   *data, qint64 size, qint32 source, int tag);
    dtkDistributedRequest *ireceive(qint64 *data, qint64 size, qint32 source, int tag);
    dtkDistributedRequest *ireceive(float  *data, qint64 size, qint32 source, int tag);
    dtkDistributedRequest *ireceive(double *data, qint64 size, qint32 source, int tag);

    virtual void wait(dtkDistributedRequest *req) = 0;

public:
    virtual void reduce(void   *send, void   *recv, qint64 size, QMetaType::Type dataType, OperationType operationType, qint32 target, bool all = false) = 0;
    virtual void reduce(bool   *send, bool   *recv, qint64 size, OperationType operationType, qint32 target, bool all = false);
    virtual void reduce(char   *send, char   *recv, qint64 size, OperationType operationType, qint32 target, bool all = false);
    virtual void reduce(int    *send, int    *recv, qint64 size, OperationType operationType, qint32 target, bool all = false);
    virtual void reduce(qlonglong *send, qlonglong *recv, qint64 size, OperationType operationType, qint32 target, bool all = false);
    virtual void reduce(float  *send, float  *recv, qint64 size, OperationType operationType, qint32 target, bool all = false);
    virtual void reduce(double *send, double *recv, qint64 size, OperationType operationType, qint32 target, bool all = false);

public:
    virtual void gather(void   *send, void   *recv, qint64 size, QMetaType::Type dataType, qint32 target, bool all = false) = 0;
    virtual void gather(bool   *send, bool   *recv, qint64 size, qint32 target, bool all = false);
    virtual void gather(char   *send, char   *recv, qint64 size, qint32 target, bool all = false);
    virtual void gather(int    *send, int    *recv, qint64 size, qint32 target, bool all = false);
    virtual void gather(qlonglong *send, qlonglong *recv, qint64 size, qint32 target, bool all = false);
    virtual void gather(float  *send, float  *recv, qint64 size, qint32 target, bool all = false);
    virtual void gather(double *send, double *recv, qint64 size, qint32 target, bool all = false);

public:
    virtual void spawn(QStringList hostnames, QString wrapper = "", QMap<QString,QString> options = QMap<QString,QString>() ) = 0;
    virtual void  exec(QRunnable *work) = 0;

public:
    virtual void unspawn(void) = 0;
    virtual void barrier(void) = 0;

public:
    virtual qint32  wid(void) = 0;
    inline  qint32 rank(void) {return wid();};
    virtual qint32 size(void) = 0;
    virtual void*  data(void) { return NULL;}; 
public:
    virtual void setWid(qint32 id) ;

};

DTK_DECLARE_OBJECT(dtkDistributedCommunicator*)
DTK_DECLARE_PLUGIN(dtkDistributedCommunicator, DTKDISTRIBUTED_EXPORT)
DTK_DECLARE_PLUGIN_FACTORY(dtkDistributedCommunicator, DTKDISTRIBUTED_EXPORT)
DTK_DECLARE_PLUGIN_MANAGER(dtkDistributedCommunicator, DTKDISTRIBUTED_EXPORT)

//for numComposer
Q_DECLARE_METATYPE(dtkDistributedCommunicator **);

template <typename T> void dtkDistributedCommunicator::send(T data, qint32 target, qint32 tag)
{
    QVariant v;
    v = QVariant::fromValue<T>(data);
    send(v, target,tag);
}

template <typename T> void dtkDistributedCommunicator::receive(T &data, qint32 source, qint32 tag)
{
    QVariant v;
    receive(v,source,tag);
    data = v.value<T>();
}

template <typename T, typename U> class runFunction: public QRunnable
{
public:
    U (T::*func)();
    T *object;

public:
    void run(void) {
        (object->*func)();
    }
};

template <typename T, typename U> void dtkDistributedCommunicator::run(T* t, U (T::*functionPointer)())
{
    runFunction<T,U> runner;
    runner.func = functionPointer;
    runner.object = t;
    this->exec(&runner);
}


//
// dtkDistributedCommunicator.h ends here

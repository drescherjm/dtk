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

#include "dtkDistributedCommunicator.h"

class qthDistributedCommunicatorPrivate;
class dtkDistributedBufferManager;
class dtkDistributedRequest;

class qthDistributedCommunicator : public dtkDistributedCommunicator
{
    Q_OBJECT

public:
     qthDistributedCommunicator(void);
    ~qthDistributedCommunicator(void);

public:
    void   initialize(void);
    bool  initialized(void);
    void uninitialize(void);
    bool       active(void);

public:
    void   spawn(QStringList hostnames, qlonglong np);
    void    exec(QRunnable *work);

public:
    void barrier(void);
    void unspawn(void);

public:
    dtkDistributedBufferManager *createBufferManager(void);
    void destroyBufferManager(dtkDistributedBufferManager *& buffer_manager);

public:
    void broadcast(void *data, qint64 size, QMetaType::Type dataType, qint32 source);
    void broadcast(QByteArray &array, qint32 source );
    void broadcast(QVariant &v, qint32 source );


public:
    void send(void *data, qint64 size, QMetaType::Type dataType, qint32 target, qint32 tag);
    void send(QByteArray& array, qint32 target, qint32 tag);

public:
    void receive(void *data, qint64 size, QMetaType::Type dataType, qint32 source, qint32 tag);
    void receive(QByteArray &v,  qint32 source, qint32 tag);
    void receive(QByteArray &v,  qint32 source, qint32 tag, dtkDistributedCommunicatorStatus& status);
    using dtkDistributedCommunicator::receive;

public:
    void reduce(void *send, void *recv, qint64 size, QMetaType::Type dataType, OperationType operationType, qint32 root, bool all);

public:
    dtkDistributedRequest *ireceive(void *data, qint64 size, QMetaType::Type dataType, qint32 source, qint32 tag);
    void wait(dtkDistributedRequest *req);

public:
    qint32  wid(void);
    qint32 size(void);

public:
    void setWid(qint32 id);

public:
    qthDistributedCommunicatorPrivate *d;

};


static dtkDistributedCommunicator *qthDistributedCommunicatorCreator(void)
{
    return new qthDistributedCommunicator();
}

// 
// qthDistributedCommunicator.h ends here

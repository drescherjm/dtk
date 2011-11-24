/* dtkDistributedCommunicatorTcp.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:50:54 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 18:34:32 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 48
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCOMMUNICATORTCP_H
#define DTKDISTRIBUTEDCOMMUNICATORTCP_H

#include "dtkDistributedCommunicator.h"
#include "dtkDistributedSocket.h"
#include <QAbstractSocket>
#include <dtkCore/dtkAbstractDataSerializer.h>

class dtkDistributedCommunicatorTcpPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedCommunicatorTcp : public dtkDistributedCommunicator
{
    Q_OBJECT

public:
     dtkDistributedCommunicatorTcp(void);
    ~dtkDistributedCommunicatorTcp(void);

    void   initialize(void);
    void uninitialize(void);

    int rank(void);
    int size(void);

    void   barrier(void);
    void      send(void *data,             qint64 size, DataType dataType, quint16 target, int tag);
    void   receive(void *data,             qint64 size, DataType dataType, quint16 source, int tag);
    void broadcast(void *data,             qint64 size, DataType dataType, quint16 source);
    void    gather(void *send, void *recv, qint64 size, DataType dataType, quint16 target, bool all = false);
    void   scatter(void *send, void *recv, qint64 size, DataType dataType, quint16 source);
    void    reduce(void *send, void *recv, qint64 size, DataType dataType, OperationType operationType, quint16 target, bool all = false);


    void                 connectToHost(const QString &host , qint16 port);
    void            disconnectFromHost();
    dtkDistributedSocket *socket();

    void send(dtkAbstractData &data, dtkAbstractDataSerializer *serializer, QString type, quint16 target, int tag);

    void flush();

private:
    dtkDistributedCommunicatorTcpPrivate *d;
};

#endif

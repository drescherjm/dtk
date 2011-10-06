/* dtkDistributedCommunicatorTcp.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:51:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: mer. oct.  5 14:45:39 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 107
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedCommunicatorTcp.h"
#include "dtkDistributedSocket.h"

#include <dtkCore/dtkLog.h>

#include <QtCore>
#include <QtNetwork>

class dtkDistributedCommunicatorTcpPrivate
{
public:
    dtkDistributedSocket *server;
    dtkDistributedSocket *socket;

    QList<dtkDistributedSocket *> sockets;
};

dtkDistributedCommunicatorTcp::dtkDistributedCommunicatorTcp(void) : dtkDistributedCommunicator(), d(new dtkDistributedCommunicatorTcpPrivate)
{
    d->server = NULL;
    d->socket = NULL;
}

dtkDistributedCommunicatorTcp::~dtkDistributedCommunicatorTcp(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedCommunicatorTcp::connectToHost(const QString &host , qint16 port)
{
    if (!d->socket) {
        d->socket = new dtkDistributedSocket();
        d->socket->connectToHost(host,port);
    }
}

void dtkDistributedCommunicatorTcp::disconnectFromHost()
{
    if (d->socket)
        d->socket->disconnectFromHost();
}

dtkDistributedSocket *dtkDistributedCommunicatorTcp::socket(void)
{
    return d->socket;
}


// QAbstractSocket::SocketState dtkDistributedCommunicatorTcp::state(void)
// {
//     return d->socket->state();
// }

// bool  dtkDistributedCommunicatorTcp::waitForConnected(void)
// {
//     return d->socket->waitForConnected();
// }

void dtkDistributedCommunicatorTcp::initialize(void)
{

}

void dtkDistributedCommunicatorTcp::uninitialize(void)
{

}

int dtkDistributedCommunicatorTcp::rank(void)
{
    if(d->server)
        return 0;
    else
        return -1;
}

int dtkDistributedCommunicatorTcp::size(void)
{
    if(d->server)
        return d->sockets.count() + 1;
    else
        return -1;
}

void dtkDistributedCommunicatorTcp::barrier(void)
{
    char junk;

    if(d->server) {
        this->send(&junk, 1,
                   dtkDistributedCommunicator::dtkDistributedCommunicatorChar, 0,
                   dtkDistributedCommunicator::dtkDistributedCommunicatorBarrier);
        this->receive(&junk, 1,
                   dtkDistributedCommunicator::dtkDistributedCommunicatorChar, 0,
                   dtkDistributedCommunicator::dtkDistributedCommunicatorBarrier);
    } else {
        this->receive(&junk, 1,
                   dtkDistributedCommunicator::dtkDistributedCommunicatorChar, 0,
                   dtkDistributedCommunicator::dtkDistributedCommunicatorBarrier);
        this->send(&junk, 1,
                   dtkDistributedCommunicator::dtkDistributedCommunicatorChar, 0,
                   dtkDistributedCommunicator::dtkDistributedCommunicatorBarrier);
    }
}


void dtkDistributedCommunicatorTcp::send(void *data, quint16 size, DataType dataType, quint16 target, int tag)
{
    // TODO: handle target and tag, and check return value of write
    d->socket->write((char *)data,size);

}

void dtkDistributedCommunicatorTcp::receive(void *data, quint16 size, DataType dataType, quint16 source, int tag)
{

}

void dtkDistributedCommunicatorTcp::broadcast(void *data, quint16 size, DataType dataType, quint16 source)
{

}

void dtkDistributedCommunicatorTcp::gather(void *send, void *recv, quint16 size, DataType dataType, quint16 target, bool all)
{
    dtkWarning() << "Collective operations are not supported on sockets";
}

void dtkDistributedCommunicatorTcp::scatter(void *send, void *recv, quint16 size, DataType dataType, quint16 source)
{
    dtkWarning() << "Collective operations are not supported on sockets";
}

void dtkDistributedCommunicatorTcp::reduce(void *send, void *recv, quint16 size, DataType dataType, OperationType operationType, quint16 target, bool all)
{
    dtkWarning() << "Collective operations are not supported on sockets";
}

/* dtkDistributedCommunicatorTcp.cpp ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:51:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: ven. déc.  9 15:39:55 2011 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 185
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

void dtkDistributedCommunicatorTcp::initialize(void)
{

}

void dtkDistributedCommunicatorTcp::uninitialize(void)
{
    if (d->socket)
        d->socket->close();
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

void dtkDistributedCommunicatorTcp::flush(void)
{
    while (this->socket()->bytesToWrite() > 0) {
        this->socket()->flush();
    }
}

void dtkDistributedCommunicatorTcp::send(dtkAbstractData *data, qint16 target, int tag)
{
    QByteArray *array;
    QString type = data->identifier();

    array = data->serialize();
    if (!array->isNull()) {
        d->socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::DATA,QString::number(tag),target, array->size(), type));
        d->socket->write(*array);
    } else {
        dtkWarning() << "serialization failed";
    }
}

void dtkDistributedCommunicatorTcp::receive(dtkAbstractData *data, qint16 source, int tag)
{

    d->socket->blockSignals(true);

    if (!d->socket->waitForReadyRead(300000))
        qDebug() << "WARN: data not ready in receive for rank " << source;
    else {
        dtkDistributedMessage *msg = d->socket->parseRequest();
        if (msg->size() > 0) {
            QByteArray array = msg->content();
            if (!data->deserialize(array))
                dtkWarning() << "warning: deserialization failed";
        } else
            dtkWarning() << "warning: no content in receive";
    }
    d->socket->blockSignals(false);
}


void dtkDistributedCommunicatorTcp::send(void *data, qint64 size, DataType dataType, qint16 target, int tag)
{
    // TODO: handle target and tag, and check return value of write
    d->socket->write((char *)data,size);

}

void dtkDistributedCommunicatorTcp::receive(void *data, qint64 size, DataType dataType, qint16 source, int tag)
{

}

void dtkDistributedCommunicatorTcp::broadcast(void *data, qint64 size, DataType dataType, qint16 source)
{

}

void dtkDistributedCommunicatorTcp::gather(void *send, void *recv, qint64 size, DataType dataType, qint16 target, bool all)
{
    dtkWarning() << "Collective operations are not supported on sockets";
}

void dtkDistributedCommunicatorTcp::scatter(void *send, void *recv, qint64 size, DataType dataType, qint16 source)
{
    dtkWarning() << "Collective operations are not supported on sockets";
}

void dtkDistributedCommunicatorTcp::reduce(void *send, void *recv, qint64 size, DataType dataType, OperationType operationType, qint16 target, bool all)
{
    dtkWarning() << "Collective operations are not supported on sockets";
}

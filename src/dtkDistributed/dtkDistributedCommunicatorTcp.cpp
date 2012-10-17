/* dtkDistributedCommunicatorTcp.cpp ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:51:02 2010 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedCommunicatorTcp.h"
#include "dtkDistributedSocket.h"

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkLog/dtkLog.h>

#include <QtCore>
#include <QtNetwork>

class dtkDistributedCommunicatorTcpPrivate
{
public:
    dtkDistributedSocket *server;
    dtkDistributedSocket *socket;

    QList<dtkDistributedSocket *> sockets;

public:
    bool initialized;
};

dtkDistributedCommunicatorTcp::dtkDistributedCommunicatorTcp(void) : dtkDistributedCommunicator(), d(new dtkDistributedCommunicatorTcpPrivate)
{
    d->server = NULL;
    d->socket = NULL;
    d->initialized = false;
}

dtkDistributedCommunicatorTcp::~dtkDistributedCommunicatorTcp(void)
{
    delete d->server;
    delete d->socket;
    delete d;

    d = NULL;
}

dtkDistributedCommunicatorTcp::dtkDistributedCommunicatorTcp(const dtkDistributedCommunicatorTcp& other)
{

}

dtkDistributedCommunicatorTcp& dtkDistributedCommunicatorTcp::operator = (const dtkDistributedCommunicatorTcp& other)
{
    return *this;
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
    d->initialized = true;
}

bool dtkDistributedCommunicatorTcp::initialized(void)
{
    return d->initialized;
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
    QByteArray *array = data->serialize();
    if (array) {
        dtkDistributedMessage *msg = new dtkDistributedMessage(dtkDistributedMessage::DATA, "unknown", target, array->size(), data->identifier(), *array);
        d->socket->sendRequest(msg);
        d->socket->waitForBytesWritten();

        delete msg;
    } else {
        dtkError() << "Empty array serialized, can't send anything";
    }

}


void dtkDistributedCommunicatorTcp::receive(dtkAbstractData *&data, qint16 source, int tag)
{
    DTK_UNUSED(tag);

    d->socket->blockSignals(true);

    if (!d->socket->waitForReadyRead(300000))
        dtkWarn() << "Data not ready in receive for rank " << source;
    else {
        dtkDistributedMessage *msg = d->socket->parseRequest();
        if (msg->size() > 0) {
            QByteArray array = msg->content();
            if(!data) {
                data = dtkAbstractDataFactory::instance()->create(msg->type());
            }
            if (!data->deserialize(array)) {
                dtkError() << "Deserialization failed";
            }
        } else {
            dtkWarn() << "warning: no content in receive";
        }
    }
    d->socket->blockSignals(false);
}

void dtkDistributedCommunicatorTcp::send(const QString &s, qint16 target, int tag)
{
    d->socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::DATA,QString::number(tag),target, s.count(), "text"));
    d->socket->write(s.toUtf8());
}

void dtkDistributedCommunicatorTcp::send(QByteArray &a, qint16 target, int tag)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicatorTcp::receive(QString &data, qint16 source, int tag)
{
    DTK_UNUSED(tag);

    d->socket->blockSignals(true);

    if (!d->socket->waitForReadyRead(300000))
        dtkWarn() << "Data not ready in receive for rank " << source;
    else {
        dtkDistributedMessage *msg = d->socket->parseRequest();
        if (msg->size() > 0) {
            QByteArray array = msg->content();
            data = QString(array);
        } else {
            dtkWarn() << "warning: no content in receive";
        }
    }
    d->socket->blockSignals(false);
}

void dtkDistributedCommunicatorTcp::receive(QByteArray &array, qint16 source, int tag)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkDistributedCommunicatorTcp::send(void *data, qint64 size, DataType dataType, qint16 target, int tag)
{
    DTK_UNUSED(dataType);
    DTK_UNUSED(tag);
    DTK_UNUSED(target);
    // TODO: handle target and tag, and check return value of write
    d->socket->write((char *)data,size);

}

void dtkDistributedCommunicatorTcp::receive(void *data, qint64 size, DataType dataType, qint16 source, int tag)
{
    DTK_UNUSED(data);
    DTK_UNUSED(size);
    DTK_UNUSED(dataType);
    DTK_UNUSED(tag);
    DTK_UNUSED(source);
}

void dtkDistributedCommunicatorTcp::broadcast(void *data, qint64 size, DataType dataType, qint16 source)
{
    DTK_UNUSED(data);
    DTK_UNUSED(size);
    DTK_UNUSED(dataType);
    DTK_UNUSED(source);

    dtkWarn() << "Collective operations are not supported on sockets";
}

void dtkDistributedCommunicatorTcp::gather(void *send, void *recv, qint64 size, DataType dataType, qint16 target, bool all)
{
    DTK_UNUSED(send);
    DTK_UNUSED(recv);
    DTK_UNUSED(size);
    DTK_UNUSED(dataType);
    DTK_UNUSED(target);
    DTK_UNUSED(all);

    dtkWarn() << "Collective operations are not supported on sockets";
}

void dtkDistributedCommunicatorTcp::scatter(void *send, void *recv, qint64 size, DataType dataType, qint16 source)
{
    DTK_UNUSED(send);
    DTK_UNUSED(recv);
    DTK_UNUSED(size);
    DTK_UNUSED(dataType);
    DTK_UNUSED(source);

    dtkWarn() << "Collective operations are not supported on sockets";
}

void dtkDistributedCommunicatorTcp::reduce(void *send, void *recv, qint64 size, DataType dataType, OperationType operationType, qint16 target, bool all)
{
    DTK_UNUSED(send);
    DTK_UNUSED(recv);
    DTK_UNUSED(size);
    DTK_UNUSED(dataType);
    DTK_UNUSED(operationType);
    DTK_UNUSED(target);
    DTK_UNUSED(all);

    dtkWarn() << "Collective operations are not supported on sockets";
}

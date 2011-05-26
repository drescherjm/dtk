/* dtkDistributedServer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 11:30:49 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 41
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedServer.h"
#include "dtkDistributedService.h"

class dtkDistributedServerPrivate
{
public:
};

dtkDistributedServer::dtkDistributedServer(quint16 port, QObject *parent) : QTcpServer(parent), d(new dtkDistributedServerPrivate)
{
    this->listen(QHostAddress::Any, port);
}

dtkDistributedServer::~dtkDistributedServer(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedServer::incomingConnection(int descriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discard()));
    socket->setSocketDescriptor(descriptor);

    dtkDistributedServiceBase::instance()->logMessage("New connection");
}

void dtkDistributedServer::read(void)
{
    QTcpSocket *socket = (QTcpSocket *)sender();

    if(socket->canReadLine()) {   
        dtkDistributedServiceBase::instance()->logMessage(QString("Read: %1").arg(QString(socket->readLine())));
    }
}

void dtkDistributedServer::discard(void)
{
    QTcpSocket *socket = (QTcpSocket *)sender();
    socket->deleteLater();

    dtkDistributedServiceBase::instance()->logMessage("Connection closed");
}

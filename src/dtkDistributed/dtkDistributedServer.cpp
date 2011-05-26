/* dtkDistributedServer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 15:04:10 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 91
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedServer.h"
#include "dtkDistributedService.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkDistributedServerDaemon
// /////////////////////////////////////////////////////////////////

class dtkDistributedServerDaemonPrivate
{
public:
};

dtkDistributedServerDaemon::dtkDistributedServerDaemon(quint16 port, QObject *parent) : QTcpServer(parent), d(new dtkDistributedServerDaemonPrivate)
{
    this->listen(QHostAddress::Any, port);
}

dtkDistributedServerDaemon::~dtkDistributedServerDaemon(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedServerDaemon::incomingConnection(int descriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discard()));
    socket->setSocketDescriptor(descriptor);

    dtkDistributedServiceBase::instance()->logMessage("New connection");
}

void dtkDistributedServerDaemon::read(void)
{
    QTcpSocket *socket = (QTcpSocket *)sender();

    if(socket->canReadLine()) {
        dtkDistributedServiceBase::instance()->logMessage(QString("Read: %1").arg(QString(socket->readLine())));
    }
}

void dtkDistributedServerDaemon::discard(void)
{
    QTcpSocket *socket = (QTcpSocket *)sender();
    socket->deleteLater();

    dtkDistributedServiceBase::instance()->logMessage("Connection closed");
}

// /////////////////////////////////////////////////////////////////
// dtkDistributedServer
// /////////////////////////////////////////////////////////////////

class dtkDistributedServerPrivate
{
public:
    dtkDistributedServerDaemon *daemon;

public:
    quint16 port;
};

#include <iostream>

dtkDistributedServer::dtkDistributedServer(int argc, char **argv) : dtkDistributedService<QCoreApplication>(argc, argv, "dtkDistributedServer"), d(new dtkDistributedServerPrivate)
{
    if(dtkApplicationArgumentsContain(argc, argv, "-p"))
        d->port = dtkApplicationArgumentsValue(argc, argv, "-p").toInt();
    else if(dtkApplicationArgumentsContain(argc, argv, "--port"))
        d->port = dtkApplicationArgumentsValue(argc, argv, "--port").toInt();
    else
        d->port = 9999;

    std::cout << d->port << std::endl;

    this->setServiceDescription("dtkDistributedServer");
}

void dtkDistributedServer::start(void)
{
    QCoreApplication *app = this->application();

    d->daemon = new dtkDistributedServerDaemon(d->port, app);

    if (!d->daemon->isListening()) {
        logMessage(QString("Failed to bind port %1").arg(d->daemon->serverPort()), dtkDistributedServiceBase::Error);
        app->quit();
    }
}

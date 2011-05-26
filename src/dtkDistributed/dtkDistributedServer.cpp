/* dtkDistributedServer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 11:44:06 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 64
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

dtkDistributedServer::dtkDistributedServer(int argc, char **argv) : dtkDistributedService<QCoreApplication>(argc, argv, "dtkDistributedServer")
{
    this->setServiceDescription("dtkDistributedServer");
}

void dtkDistributedServer::start(void)
{
    QCoreApplication *app = this->application();

    quint16 port;

    if(dtkApplicationArgumentsContain(app, "-p"))
        port = dtkApplicationArgumentsValue(app, "-p").toInt();
    else if(dtkApplicationArgumentsContain(app, "--port"))
        port = dtkApplicationArgumentsValue(app, "--port").toInt();
    else
        port = 9999;
    
    daemon = new dtkDistributedServerDaemon(port, app);

    if (!daemon->isListening()) {
        logMessage(QString("Failed to bind port %1").arg(daemon->serverPort()), dtkDistributedServiceBase::Error);
        app->quit();
    }
}

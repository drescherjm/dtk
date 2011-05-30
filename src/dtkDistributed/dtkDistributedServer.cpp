/* dtkDistributedServer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 14:05:58 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 154
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
    qDebug() << DTK_PRETTY_FUNCTION << "-- Connection --";
    qDebug() << DTK_PRETTY_FUNCTION << descriptor;
    qDebug() << DTK_PRETTY_FUNCTION << "-- Connection --";

    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discard()));
    socket->setSocketDescriptor(descriptor);

    dtkDistributedServiceBase::instance()->logMessage("New connection");
}

void dtkDistributedServerDaemon::read(void)
{
    QTcpSocket *socket = (QTcpSocket *)sender();

    QString contents = socket->readAll();
    
    qDebug() << DTK_PRETTY_FUNCTION << "-- Begin read --";
    qDebug() << DTK_PRETTY_FUNCTION << contents;
    qDebug() << DTK_PRETTY_FUNCTION << "--   End read --";
    
    dtkDistributedServiceBase::instance()->logMessage(QString("Read: %1").arg(QString(socket->readLine())));
    
    if(contents == "** status **") {
        
        socket->write("magic ninietsch was here");
    }
}

void dtkDistributedServerDaemon::discard(void)
{
    qDebug() << DTK_PRETTY_FUNCTION << "-- Disconnection --";

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
};

dtkDistributedServer::dtkDistributedServer(int argc, char **argv) : dtkDistributedService<QCoreApplication>(argc, argv, "dtkDistributedServer"), d(new dtkDistributedServerPrivate)
{
    this->setServiceDescription("dtkDistributedServer");
}

dtkDistributedServer::~dtkDistributedServer(void)
{

}

void dtkDistributedServer::start(void)
{
    QCoreApplication *app = this->application();

    quint16 port;

    if(dtkApplicationArgumentsContain(app, "-p"))
        port = dtkApplicationArgumentsValue(app, "-p").toInt();
    else
        port = 9999;

    d->daemon = new dtkDistributedServerDaemon(port, app);

    if (!d->daemon->isListening()) {
        logMessage(QString("Failed to bind port %1").arg(d->daemon->serverPort()), dtkDistributedServiceBase::Error);
        app->quit();
    }
}

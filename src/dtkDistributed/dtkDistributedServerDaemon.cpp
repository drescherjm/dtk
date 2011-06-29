/* dtkDistributedServerDaemon.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. juin 29 17:51:22 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 46
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedServerDaemon.h"
#include "dtkDistributedServerManager.h"
#include "dtkDistributedServerManagerOar.h"
#include "dtkDistributedServerManagerTorque.h"
#include "dtkDistributedService.h"

#include <dtkCore/dtkGlobal.h>

class dtkDistributedServerDaemonPrivate
{
public:
    dtkDistributedServerManager *manager;
};

dtkDistributedServerDaemon::dtkDistributedServerDaemon(quint16 port, QObject *parent) : QTcpServer(parent), d(new dtkDistributedServerDaemonPrivate)
{
    d->manager = NULL;

    this->listen(QHostAddress::Any, port);
}

dtkDistributedServerDaemon::~dtkDistributedServerDaemon(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedServerDaemon::setManager(dtkDistributedServerManager::Type type)
{
    switch(type) {
    case dtkDistributedServerManager::Oar:
        d->manager = new dtkDistributedServerManagerOar;
        break;
    case dtkDistributedServerManager::Torque:
        d->manager = new dtkDistributedServerManagerTorque;
        break;
    default:
        break;
    }
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
        QString r = d->manager->status();
        qDebug() << r;

        socket->write(QString("!! status !!").toAscii());
        socket->write(r.toAscii());
        socket->write(QString("!! endstatus !!").toAscii());
    } else if(contents.contains("** submit **")) {
        QString jobid = d->manager->submit(contents);
        qDebug() << jobid;
        socket->write(QString("!! submit !!").toAscii());
        socket->write(jobid.toAscii());
        socket->write(QString("!! endsubmit !!").toAscii());
    }
}

void dtkDistributedServerDaemon::discard(void)
{
    qDebug() << DTK_PRETTY_FUNCTION << "-- Disconnection --";

    QTcpSocket *socket = (QTcpSocket *)sender();
    socket->deleteLater();

    dtkDistributedServiceBase::instance()->logMessage("Connection closed");
}

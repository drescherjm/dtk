/* dtkDistributedServerDaemon.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. avril 24 18:29:50 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 729
 */

/* Commentary: 
 * 
 * debug logging: use dtkLog() << "message" or qDebug() << "message"
 *   run logging: use dtkDistributedServiceBase::instance()->logMessage("message");
 */

/* Change log:
 * 
 */

#include "dtkDistributedServerDaemon.h"
#include "dtkDistributedServerManager.h"
#include "dtkDistributedServerManagerOar.h"
#include "dtkDistributedServerManagerSsh.h"
#include "dtkDistributedServerManagerTorque.h"
#include "dtkDistributedService.h"
#include "dtkDistributedSocket.h"

#include <dtkCore/dtkGlobal.h>

#include <dtkLog/dtkLog.h>

class dtkDistributedServerDaemonPrivate
{
public:
    dtkDistributedServerManager *manager;

    QMap<int, dtkDistributedSocket*> sockets;
};

dtkDistributedServerDaemon::dtkDistributedServerDaemon(quint16 port, QObject *parent) : QTcpServer(parent), d(new dtkDistributedServerDaemonPrivate)
{
    d->manager = NULL;

    if (!this->listen(QHostAddress::Any, port)) {
        dtkError() << "Can't listen on port"  << port << ", aborting";
        exit(1);
    } else {
        dtkDebug() << "OK, server is waiting for incoming connection on port"  << port ;
    }

    dtkDistributedServiceBase::instance()->logMessage("Server daemon listening on port " + QString::number(port));
}

dtkDistributedServerDaemon::~dtkDistributedServerDaemon(void)
{
    delete d;

    d = NULL;
}

dtkDistributedServerManager * dtkDistributedServerDaemon::manager(void)
{
    return d->manager;
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
    case dtkDistributedServerManager::Ssh:
        d->manager = new dtkDistributedServerManagerSsh;
        break;
    default:
        break;
    }
}

void dtkDistributedServerDaemon::incomingConnection(int descriptor)
{
    dtkDebug() << DTK_PRETTY_FUNCTION << "-- Connection -- " << descriptor ;

    dtkDistributedSocket *socket = new dtkDistributedSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discard()));
    socket->setSocketDescriptor(descriptor);

    dtkDistributedServiceBase::instance()->logMessage("New connection");
}

//! Wait for incomming connection
/*! Warning, in its current state, this method may never return if no
 *  connection is established.
 * 
 * \param rank, the identifier of the slave on the cluster side.
 */
void dtkDistributedServerDaemon::waitForConnection(int rank)
{
    while(!d->sockets.keys().contains(rank))
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
}

QByteArray dtkDistributedServerDaemon::waitForData(int rank)
{
    dtkDistributedSocket *socket = d->sockets.value(rank, NULL);

    if(!socket) {
        dtkWarn() << "No socket found for rank " << rank;
        return QByteArray();
    }

    socket->blockSignals(true);

    dtkDistributedMessage *data = NULL;

    if (socket->waitForReadyRead(30000))
        data = socket->parseRequest();
    else
        dtkWarn() << "Data not ready for rank " << rank;

    socket->blockSignals(false);

    if (data) {
        return data->content();
    } else {
        dtkWarn() << "Message not allocated - return void QByteArray";
        return QByteArray();
    }
}

void dtkDistributedServerDaemon::read(void)
{
    dtkDistributedSocket *socket = (dtkDistributedSocket *)sender();
    dtkDistributedMessage *msg = socket->parseRequest();

    QByteArray r;
    QString jobid;

    dtkDebug() << DTK_PRETTY_FUNCTION << "read message of type" << msg->method();

    switch (msg->method()) {
    case dtkDistributedMessage::STATUS:
        r = d->manager->status();
        socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::OKSTATUS,"",dtkDistributedMessage::SERVER_RANK,r.size(),"json",r));
        // GET status is from the controller, store the socket in sockets using rank=-1
        if (!d->sockets.contains(dtkDistributedMessage::CONTROLLER_RANK))
            d->sockets.insert(dtkDistributedMessage::CONTROLLER_RANK, socket);
        break;

    case dtkDistributedMessage::NEWJOB:
        jobid = d->manager->submit(msg->content());
        dtkDebug() << DTK_PRETTY_FUNCTION << jobid;
        socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::OKJOB, jobid));
        break;

    case dtkDistributedMessage::ENDJOB:
        dtkDebug() << DTK_PRETTY_FUNCTION << "Job ended " << msg->jobid();
        //TODO: check if exists
        d->sockets[dtkDistributedMessage::CONTROLLER_RANK]->sendRequest(msg);
        break;

    case dtkDistributedMessage::SETRANK:

        dtkDebug() << DTK_PRETTY_FUNCTION << "connected remote is of rank " << msg->rank();
        d->sockets.insert(msg->rank(), socket);
        // rank 0 is alive, warn the controller
        if (msg->rank() == 0 && d->sockets.contains(dtkDistributedMessage::CONTROLLER_RANK))
            (d->sockets[dtkDistributedMessage::CONTROLLER_RANK])->sendRequest(msg);

        break;

    case dtkDistributedMessage::DELJOB:
        jobid = msg->jobid();
        if (d->manager->deljob(jobid).startsWith("OK"))
            socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::OKDEL, jobid) );
        else
            socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::ERRORDEL, jobid) );
        break;

    case dtkDistributedMessage::DATA:
        msg->addHeader("x-forwarded-for", QString::number(d->sockets.key(socket)));
        dtkDebug() << DTK_PRETTY_FUNCTION << "forwarding data of type" << msg->type() << "and size" << msg->content().size();
        (d->sockets[msg->rank()])->sendRequest(msg);
        break;

    default:
        dtkWarn() << DTK_PRETTY_FUNCTION << "Unknown data";
    };

    delete msg;
    if (socket->bytesAvailable() > 0)
        this->read();
}

void dtkDistributedServerDaemon::discard(void)
{
    dtkDebug() << DTK_PRETTY_FUNCTION << "-- Disconnection --";

    dtkDistributedSocket *socket = (dtkDistributedSocket *)sender();
    socket->deleteLater();

    dtkDistributedServiceBase::instance()->logMessage("Connection closed");
}

/* dtkDistributedServerDaemon.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. sept. 22 10:25:14 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 519
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
#include "dtkDistributedServerManagerTorque.h"
#include "dtkDistributedService.h"
#include "dtkDistributedSocket.h"

#include <dtkCore/dtkGlobal.h>

#define DTK_DEBUG_SERVER_DAEMON 0

class dtkDistributedServerDaemonPrivate
{
public:
    dtkDistributedServerManager *manager;

    QMap<int, dtkDistributedSocket*> sockets;
};

dtkDistributedServerDaemon::dtkDistributedServerDaemon(quint16 port, QObject *parent) : QTcpServer(parent), d(new dtkDistributedServerDaemonPrivate)
{
    d->manager = NULL;

    this->listen(QHostAddress::Any, port);

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
    default:
        break;
    }
}

void dtkDistributedServerDaemon::incomingConnection(int descriptor)
{
#if defined(DTK_DEBUG_SERVER_DAEMON)
    qDebug() << DTK_PRETTY_FUNCTION << "-- Connection -- " << descriptor ;
#endif

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
        qDebug() << "WARN: no socket found for rank " << rank;
        return QByteArray();
    }

    socket->blockSignals(true);

    QVariantMap data;

    if (d->sockets[rank]->waitForReadyRead(30000))
        data = d->sockets[rank]->parseRequest();

    socket->blockSignals(false);

    return data["content"].toByteArray() ;
}

void dtkDistributedServerDaemon::read(void)
{
    dtkDistributedSocket *socket = (dtkDistributedSocket *)sender();


    QVariantMap request = socket->parseRequest();
    QString method= request["method"].toString();
    QString path= request["path"].toString();

    if( method == "GET" && path   == "/status") {

        QByteArray r = d->manager->status();
        socket->sendRequest("OK","/status",r.size(),"json",r);
        // GET status is from the controller, store the socket in sockets using rank=-1
        if (!d->sockets.contains(-1))
            d->sockets.insert(-1, socket);

    } else if( method == "PUT" && path == "/job" ) {

        QString jobid = d->manager->submit(request["content"].toByteArray());
#if defined(DTK_DEBUG_SERVER_DAEMON)
        qDebug() << DTK_PRETTY_FUNCTION << jobid;
#endif
        socket->sendRequest("OK","/job/"+jobid);

    } else if( method == "ENDED" && path.startsWith("/job")) {

        QString jobid = path.split("/").at(2);
#if defined(DTK_DEBUG_SERVER_DAEMON)
        qDebug() << DTK_PRETTY_FUNCTION << "Job ended " << jobid;
#endif
        //TODO: check if exists
        dtkDistributedSocket *controller =  d->sockets[-1];
        controller->sendRequest(method,path);

    } else if( method == "PUT" && path.startsWith("/rank")) {

        int rank = path.split("/").at(2).toInt();

#if defined(DTK_DEBUG_SERVER_DAEMON)
        qDebug() << DTK_PRETTY_FUNCTION << "connected remote is of rank " << rank;
#endif
        d->sockets.insert(rank, socket);

    } else if( method == "DELETE" && path.startsWith("/job")) {

        QString jobid = path.split("/").at(2);
        socket->sendRequest(d->manager->deljob(jobid),"/job/"+jobid);

    } else if( method == "POST" && path.startsWith("/data")) {
        QString jobid = path.split("/").at(2);
        int torank = path.split("/").at(3).toInt();
        int size = request["size"].toInt();
        QString type = request["type"].toString();
        int fromrank = d->sockets.key(socket);

        dtkDistributedSocket *dest =  d->sockets[torank];
        QHash<QString,QString> headers;
        headers["x-forwarded-for"] = QString::number(fromrank);
        dest->sendRequest(method,"/data/"+jobid, size, type, request["content"].toByteArray(),headers);
    } else {
        qDebug() << DTK_PRETTY_FUNCTION << "WARNING: Unknown data";
    }
    if (socket->bytesAvailable() > 0)
        this->read();
}

void dtkDistributedServerDaemon::discard(void)
{
#if defined(DTK_DEBUG_SERVER_DAEMON)
    qDebug() << DTK_PRETTY_FUNCTION << "-- Disconnection --";
#endif

    dtkDistributedSocket *socket = (dtkDistributedSocket *)sender();
    socket->deleteLater();

    dtkDistributedServiceBase::instance()->logMessage("Connection closed");
}

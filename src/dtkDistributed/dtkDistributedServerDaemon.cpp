/* dtkDistributedServerDaemon.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:18:53 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 844
 */

/* Commentary: 
 * 
 * debug logging: use dtkLog() << "message" or qDebug() << "message"
 *   run logging: use dtkDistributedServiceBase::instance()->logMessage("message");
 */

/* Change log:
 * 
 */

#include "dtkDistributedMessage.h"
#include "dtkDistributedServerDaemon.h"
#include "dtkDistributedResourceManager.h"
#include "dtkDistributedResourceManagerOar.h"
#include "dtkDistributedResourceManagerLocal.h"
#include "dtkDistributedResourceManagerTorque.h"

#include <dtkLog/dtkLogger.h>

#include <QTcpSocket>

class dtkDistributedServerDaemonPrivate
{
public:
    dtkDistributedResourceManager *manager;

public:
    QMap< QPair<int,QString>, QTcpSocket *> sockets;
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

    // dtkDistributedServiceBase::instance()->logMessage("Server daemon listening on port " + QString::number(port));
}

dtkDistributedServerDaemon::~dtkDistributedServerDaemon(void)
{
    delete d;

    d = NULL;
}

dtkDistributedResourceManager * dtkDistributedServerDaemon::manager(void)
{
    return d->manager;
}

void dtkDistributedServerDaemon::setManager(QString name)
{
    dtkDebug()<< "create resource manager" << name;
    if (name == "torque") {
        d->manager = new dtkDistributedResourceManagerTorque;
    } else if (name =="oar") {
        d->manager = new dtkDistributedResourceManagerOar;
    } else if (name =="local") {
        d->manager = new dtkDistributedResourceManagerLocal;
    } else {
        dtkCritical() << "unknown resource manager type" << name;
    }
}

void dtkDistributedServerDaemon::incomingConnection(qintptr descriptor)
{
    dtkDebug() << "-- Connection -- " << descriptor ;

    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discard()));
    socket->setSocketDescriptor(descriptor);

    // dtkDistributedServiceBase::instance()->logMessage("New connection");
}

//! Wait for incomming connection
/*! Warning, in its current state, this method may never return if no
 *  connection is established.
 * 
 * \param rank, the identifier of the slave on the cluster side.
 */
void dtkDistributedServerDaemon::waitForConnection(int rank, QString jobid)
{
    dtkDebug()<< "wait for connection" << rank << jobid;
    while(!d->sockets.keys().contains(qMakePair(rank, jobid)))
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
}

QByteArray dtkDistributedServerDaemon::waitForData(int rank, QString jobid)
{
    dtkDebug()<< "wait for data" << rank << jobid;
    QTcpSocket *socket = d->sockets.value(qMakePair(rank, jobid), NULL);

    if(!socket) {
        dtkWarn() << "No socket found for rank " << rank;
        return QByteArray();
    }

    socket->blockSignals(true);

    dtkDistributedMessage data;

    if (socket->waitForReadyRead(30000))
        data.parse(socket);
    else
        dtkWarn() << "Data not ready for rank " << rank;

    socket->blockSignals(false);

    if (! data.content().isEmpty()) {
        return data.content();
    } else {
        dtkWarn() << "Message not allocated - return void QByteArray";
        return QByteArray();
    }
}

void dtkDistributedServerDaemon::read(void)
{
    QTcpSocket *socket = (QTcpSocket *)sender();
    QScopedPointer<dtkDistributedMessage> msg(new dtkDistributedMessage);
    QScopedPointer<dtkDistributedMessage> resp(new dtkDistributedMessage);

    dtkDebug() << "Data received ,parse";

    msg.data()->parse(socket);

    QByteArray r;
    QString jobid;
    int      controller_rank = dtkDistributedMessage::CONTROLLER_RANK;
    QString controller_jobid = QString("");
    QPair<int, QString> controller = qMakePair(controller_rank, controller_jobid);
    QPair<int, QString> pair;

    dtkDebug() << "read message of type" << msg->method();

    switch (msg->method()) {
    case dtkDistributedMessage::STATUS:
        r = d->manager->status();
        resp.reset(new dtkDistributedMessage(dtkDistributedMessage::OKSTATUS,"",dtkDistributedMessage::SERVER_RANK,r.size(),"application/json",r));
        resp->send(socket);
        // GET status is from the controller, store the socket in sockets using rank=-1
        d->sockets.insert(controller, socket);
        break;

    case dtkDistributedMessage::STOP:
        qApp->quit();
        break;

    case dtkDistributedMessage::NEWJOB:
        jobid = d->manager->submit(msg->content());
        dtkDebug() << jobid;
        if (jobid == "ERROR") {
            msg.reset(new dtkDistributedMessage(dtkDistributedMessage::ERRORJOB, jobid));
        } else {
            msg.reset(new dtkDistributedMessage(dtkDistributedMessage::OKJOB, jobid));
        }
        msg->send(socket);
        break;

    case dtkDistributedMessage::ENDJOB:
        dtkDebug() << "Job ended " << msg->jobid();
        //TODO: check if exists
        msg->send(d->sockets[controller]);
        break;

    case dtkDistributedMessage::SETRANK:

        dtkDebug() << "connected remote is of rank " << msg->rank() << msg->jobid();
        d->sockets.insert(qMakePair(msg->rank(),msg->jobid()), socket);
        // rank 0 is alive, warn the controller
        if (msg->rank() == dtkDistributedMessage::SLAVE_RANK && d->sockets.contains(controller)) {
            msg->send(d->sockets[controller]);
        }
        break;

    case dtkDistributedMessage::DELJOB:
        jobid = msg->jobid();
        if (d->manager->deljob(jobid).startsWith("OK")) {
            msg.reset(new dtkDistributedMessage(dtkDistributedMessage::OKDEL, jobid));
            msg->send(socket);
        } else {
            msg.reset(new dtkDistributedMessage(dtkDistributedMessage::ERRORDEL, jobid));
            msg->send(socket);
        }
        break;

    case dtkDistributedMessage::DATA:
        pair = d->sockets.key(socket);
        msg->addHeader("x-forwarded-for", QString::number(pair.first));
        dtkDebug() << "forwarding data of type" << msg->type() << "and size" << msg->content().size() << "from" << pair.first << "to" << msg->rank();
        pair = qMakePair(msg->rank(),msg->jobid());
        if (d->sockets.contains(pair )) {
            msg->send(d->sockets[pair]);
        } else {
            dtkWarn() << "unknown socket for rank, store message" <<  msg->rank() << msg->jobid();
        }

        break;

    default:
        dtkWarn() << "Unknown data";
    };

    if (socket->bytesAvailable() > 0)
        this->read();
}

void dtkDistributedServerDaemon::discard(void)
{
    dtkDebug() << "-- Disconnection --";

    QTcpSocket *socket = (QTcpSocket *)sender();
    socket->deleteLater();

    // dtkDistributedServiceBase::instance()->logMessage("Connection closed");
}


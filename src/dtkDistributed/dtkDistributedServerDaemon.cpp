/* dtkDistributedServerDaemon.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep 19 11:15:43 2011 (+0200)
 *           By: jwintz
 *     Update #: 334
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

#include <dtkCore/dtkGlobal.h>

#define DTK_DEBUG_SERVER_DAEMON 0

class dtkDistributedServerDaemonPrivate
{
public:
    dtkDistributedServerManager *manager;

    QMap<int, QTcpSocket*> sockets;
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

    QTcpSocket *socket = new QTcpSocket(this);
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
    QTcpSocket *socket = d->sockets.value(rank, NULL);

    if(!socket) {
        qDebug() << "WARN: no socket found for rank " << rank;
        return QByteArray();
    }

    socket->blockSignals(true);

    QByteArray data;

    if (d->sockets[rank]->waitForReadyRead(30000))
        data = d->sockets[rank]->readLine(1024);

    socket->blockSignals(false);

    return data;
}

void dtkDistributedServerDaemon::read(void)
{
    QTcpSocket *socket = (QTcpSocket *)sender();

    static const int MAX_LINE_LENGTH = 1024;

    QString contents = socket->readLine(MAX_LINE_LENGTH);

#if defined(DTK_DEBUG_SERVER_DAEMON)
    qDebug() << DTK_PRETTY_FUNCTION << "-- Begin read --";
    qDebug() << DTK_PRETTY_FUNCTION << contents;
    qDebug() << DTK_PRETTY_FUNCTION << "--   End read --";
#endif

    if(contents == "GET /status\n") {

        QString r = d->manager->status();
        socket->write(QString("STATUS:\n").toAscii());
        QByteArray R = r.toAscii();
        socket->write(QString::number(R.size()).toAscii()+"\n");
        socket->write(R);

    } else if(contents == "PUT /job\n") {

        QByteArray buffer;
        QString size = socket->readLine(MAX_LINE_LENGTH);
        qint64 toread= size.toInt();
#if defined(DTK_DEBUG_SERVER_DAEMON)
        qDebug() << DTK_PRETTY_FUNCTION << "Size to read:" << toread;
#endif
        while (buffer.size() < toread  ) {
#if defined(DTK_DEBUG_SERVER_DAEMON)
            qDebug() << "read buffer loop " << buffer.size();
#endif
            buffer.append(socket->read(toread));
        }

        QString jobid = d->manager->submit(buffer);
#if defined(DTK_DEBUG_SERVER_DAEMON)
        qDebug() << DTK_PRETTY_FUNCTION << jobid;
#endif
        socket->write(QString("NEWJOB:\n").toAscii());
        socket->write(jobid.toAscii()+"\n");

    } else if(contents == "ENDJOB\n") {

        QString jobid = socket->readLine(MAX_LINE_LENGTH);
#if defined(DTK_DEBUG_SERVER_DAEMON)
        qDebug() << DTK_PRETTY_FUNCTION << "Job ended " << jobid;
#endif
    } else if(contents.contains("rank:")) {

        int rank = contents.split(":").last().trimmed().toInt();
#if defined(DTK_DEBUG_SERVER_DAEMON)
        qDebug() << DTK_PRETTY_FUNCTION << "connected remote is of rank " << rank;
#endif
        d->sockets.insert(rank, socket);

    } else if(contents.contains("DELETE /job/")) {

        QString jobid = contents.split("/").last().trimmed();
        QString resp  = "DEL "+d->manager->deljob(jobid) +"\n";
        socket->write(resp.toAscii());

    } else if(contents.contains("STARTED")) {

        qDebug() << DTK_PRETTY_FUNCTION << "job started";

    } else if(contents.contains("ENDED")) {
        qDebug() << DTK_PRETTY_FUNCTION << "job ended";

    } else {
        qDebug() << DTK_PRETTY_FUNCTION << "WARNING: Unknown data";
    }
}

void dtkDistributedServerDaemon::discard(void)
{
#if defined(DTK_DEBUG_SERVER_DAEMON)
    qDebug() << DTK_PRETTY_FUNCTION << "-- Disconnection --";
#endif

    QTcpSocket *socket = (QTcpSocket *)sender();
    socket->deleteLater();

    dtkDistributedServiceBase::instance()->logMessage("Connection closed");
}

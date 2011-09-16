/* dtkDistributedServerDaemon.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: ven. sept. 16 16:41:51 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 232
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
    QMap<int, QTcpSocket*> sockets;
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

dtkDistributedServerManager * dtkDistributedServerDaemon::manager(void) {
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
    qDebug() << DTK_PRETTY_FUNCTION << "-- Connection -- " << descriptor ;

    QTcpSocket *socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discard()));
    socket->setSocketDescriptor(descriptor);
    dtkDistributedServiceBase::instance()->logMessage("New connection");
}

QByteArray dtkDistributedServerDaemon::wait(int rank)
{
    if (d->sockets.contains(rank)) {
        qDebug() << "blocking signals; we want data from slave rank " << rank;
        this->blockSignals(true);
        QByteArray data;
        if (d->sockets[rank]->waitForReadyRead(30000))
             data = d->sockets[rank]->readLine(1024); //FIXME: readdata ?
        this->blockSignals(false);
        return data;
    } else {
        qDebug() << "WARN: no socket found for rank " << rank;
        return NULL;
    }
}

void dtkDistributedServerDaemon::read(void)
{
    QTcpSocket *socket = (QTcpSocket *)sender();

    static const int MAX_LINE_LENGTH = 1024;

    QString contents = socket->readLine(MAX_LINE_LENGTH);

    qDebug() << DTK_PRETTY_FUNCTION << "-- Begin read --";
    qDebug() << DTK_PRETTY_FUNCTION << contents;
    qDebug() << DTK_PRETTY_FUNCTION << "--   End read --";

//    dtkDistributedServiceBase::instance()->logMessage(QString("Read: %1").arg(QString(socket->readLine())));



    if(contents == "GET /status\n") {
        QString r = d->manager->status();
        qDebug() << r;

        socket->write(QString("STATUS:\n").toAscii());
        QByteArray R = r.toAscii();
        socket->write(QString::number(R.size()).toAscii()+"\n");
        socket->write(R);
    } else if(contents == "PUT /job\n") {
        QByteArray buffer;
        QString size = socket->readLine(MAX_LINE_LENGTH);
        qint64 toread= size.toInt();
        qDebug() << "Size to read: " << toread;
        while (buffer.size() < toread  ) {
            qDebug() << "read buffer loop " << buffer.size();
//            socket->waitForReadyRead(-1); // doesn't work ?!
            buffer.append(socket->read(toread));
        }
        QString jobid = d->manager->submit(buffer);
        qDebug() << jobid;
        socket->write(QString("NEWJOB:\n").toAscii());
        socket->write(jobid.toAscii()+"\n");
    } else if(contents == "ENDJOB\n") {
        QString jobid = socket->readLine(MAX_LINE_LENGTH);
        qDebug() << DTK_PRETTY_FUNCTION << "Job ended " << jobid;
    } else if(contents.contains("rank:")) {
        int rank = contents.split(":").last().trimmed().toInt();
        qDebug() << DTK_PRETTY_FUNCTION << "connected remote is of rank " << rank;
        d->sockets.insert(rank, socket);
    } else if(contents.contains("DELETE /job/")) {
        QString jobid = contents.split("/").last().trimmed();
        QString resp  = "DEL "+d->manager->deljob(jobid) +"\n";
        socket->write(resp.toAscii());
    } else {
        qDebug() << DTK_PRETTY_FUNCTION << "WARNING: Unknown data";
    }
}

void dtkDistributedServerDaemon::discard(void)
{
    qDebug() << DTK_PRETTY_FUNCTION << "-- Disconnection --";

    QTcpSocket *socket = (QTcpSocket *)sender();
    socket->deleteLater();

    dtkDistributedServiceBase::instance()->logMessage("Connection closed");
}

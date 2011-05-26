/* dtkDistributedController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 16:05:29 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 47
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedController.h"

#include <QtNetwork>

class dtkDistributedControllerPrivate
{
public:
    QList<QTcpSocket *> sockets;
};

dtkDistributedController::dtkDistributedController(void) : d(new dtkDistributedControllerPrivate)
{

}

dtkDistributedController::~dtkDistributedController(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedController::connect(const QUrl& server)
{
    qDebug() << "Connecting to" << server;

    QProcess ssh;
    ssh.setProcessChannelMode(QProcess::MergedChannels);
    ssh.start("ssh", QStringList() << server.toString() << "dtkDistributedServer");

    if (!ssh.waitForStarted()) {
        qCritical() << "Unable to launch ssh command";
        return;
    }

    if (!ssh.waitForFinished()) {
        qCritical() << "Unable to complete ssh command";
        return;
    }

    QString result = ssh.readAll();

    qDebug() << "Connected to" << server << ":" << result;
}

void dtkDistributedController::disconnect(const QUrl& server)
{
    qDebug() << "Disconnecting from" << server;

    QProcess ssh;
    ssh.start("ssh", QStringList() << server.toString() << "dtkDistributedServer" << "-t");

    if (!ssh.waitForStarted()) {
        qCritical() << "Unable to launch ssh command";
        return;
    }

    if (!ssh.waitForFinished()) {
        qCritical() << "Unable to complete ssh command";
        return;
    }
}

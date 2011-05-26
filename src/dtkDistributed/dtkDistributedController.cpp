/* dtkDistributedController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 09:19:18 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
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

    QProcess ssh; ssh.start("ssh", QStringList() << server.toString());

    if (!ssh.waitForStarted()) {
        qCritical() << "Unable to launch ssh command";
        return;
    }

    // if (!ssh.waitForFinished()) {
    //     qCritical() << "Unable to complete ssh command";
    //     return;
    // }

    QString result = ssh.readAll();

    qDebug() << "Connected to" << server << ":" << result;
}

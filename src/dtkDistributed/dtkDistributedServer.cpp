/* dtkDistributedServer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep 19 10:38:54 2011 (+0200)
 *           By: jwintz
 *     Update #: 213
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedServer.h"
#include "dtkDistributedServerDaemon.h"
#include "dtkDistributedServerManager.h"
#include "dtkDistributedService.h"

#include <dtkCore/dtkGlobal.h>

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

dtkDistributedServerManager *dtkDistributedServer::manager(void)
{
    return d->daemon->manager();
}

void dtkDistributedServer::waitForConnection(int rank)
{
    d->daemon->waitForConnection(rank);
}

QByteArray dtkDistributedServer::waitForData(int rank)
{
    return d->daemon->waitForData(rank);
}

/*! launch server using service
 *  invoked by exec()
 */
void dtkDistributedServer::start(void)
{
    QCoreApplication *app = this->application();

    quint16 port;

    if(dtkApplicationArgumentsContain(app, "-p"))
        port = dtkApplicationArgumentsValue(app, "-p").toInt();
    else
        port = 9999;

    d->daemon = new dtkDistributedServerDaemon(port, app);

    if(dtkApplicationArgumentsContain(app, "--oar"))
        d->daemon->setManager(dtkDistributedServerManager::Oar);

    if(dtkApplicationArgumentsContain(app, "--torque"))
        d->daemon->setManager(dtkDistributedServerManager::Torque);

    if (!d->daemon->isListening()) {
        logMessage(QString("Failed to bind port %1").arg(d->daemon->serverPort()), dtkDistributedServiceBase::Error);
        app->quit();
    }
}

/*! launch server bypassing service
 *
 */
void dtkDistributedServer::run(void)
{
    quint16 port;

    if(dtkApplicationArgumentsContain(qApp, "-p"))
        port = dtkApplicationArgumentsValue(qApp, "-p").toInt();
    else
        port = 9999;

    d->daemon = new dtkDistributedServerDaemon(port, qApp);

    if(dtkApplicationArgumentsContain(qApp, "--oar"))
        d->daemon->setManager(dtkDistributedServerManager::Oar);

    if(dtkApplicationArgumentsContain(qApp, "--torque"))
        d->daemon->setManager(dtkDistributedServerManager::Torque);

    if (!d->daemon->isListening()) {
        logMessage(QString("Failed to bind port %1").arg(d->daemon->serverPort()), dtkDistributedServiceBase::Error);
    }
}

/* dtkDistributedServer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. oct. 16 10:09:53 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 232
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

#include <dtkCoreSupport/dtkGlobal.h>

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

void dtkDistributedServer::waitForConnection(int rank, QString jobid)
{
    d->daemon->waitForConnection(rank, jobid);
}

QByteArray dtkDistributedServer::waitForData(int rank, QString jobid)
{
    return d->daemon->waitForData(rank, jobid);
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
    else if(dtkApplicationArgumentsContain(app, "--torque"))
        d->daemon->setManager(dtkDistributedServerManager::Torque);
    else if(dtkApplicationArgumentsContain(app, "--ssh"))
        d->daemon->setManager(dtkDistributedServerManager::Ssh);
    else {
        logMessage(QString("No manager set !"));
        app->quit();
    }

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
    else if(dtkApplicationArgumentsContain(qApp, "--torque"))
        d->daemon->setManager(dtkDistributedServerManager::Torque);
    else if(dtkApplicationArgumentsContain(qApp, "--ssh"))
        d->daemon->setManager(dtkDistributedServerManager::Ssh);
    else {
        qDebug()<< "No manager set!";
        return;
    }

    if (!d->daemon->isListening()) {
        logMessage(QString("Failed to bind port %1").arg(d->daemon->serverPort()), dtkDistributedServiceBase::Error);
    }
}

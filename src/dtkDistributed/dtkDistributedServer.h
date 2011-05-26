/* dtkDistributedServer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 11:38:08 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 34
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVER_H
#define DTKDISTRIBUTEDSERVER_H

#include "dtkDistributedExport.h"
#include "dtkDistributedService.h"

#include <QtCore>
#include <QtNetwork>

// /////////////////////////////////////////////////////////////////
// dtkDistributedServerDaemon
// /////////////////////////////////////////////////////////////////

class dtkDistributedServerDaemonPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedServerDaemon : public QTcpServer
{
    Q_OBJECT

public:
     dtkDistributedServerDaemon(quint16 port, QObject *parent = 0);
    ~dtkDistributedServerDaemon(void);

protected:
    void incomingConnection(int descriptor);

private slots:
    void read(void);
    void discard(void);

private:
    dtkDistributedServerDaemonPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedServer
// /////////////////////////////////////////////////////////////////

class DTKDISTRIBUTED_EXPORT dtkDistributedServer : dtkDistributedService<QCoreApplication>
{
public:
    dtkDistributedServer(int argc, char **argv);

protected:
    void start(void);

private:
    dtkDistributedServerDaemon *daemon;
};

#endif

/* dtkDistributedServerDaemon.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 11:27:42 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. oct. 16 10:10:23 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 32
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVERDAEMON_H
#define DTKDISTRIBUTEDSERVERDAEMON_H

#include "dtkDistributedSupportExport.h"
#include "dtkDistributedServerManager.h"

#include <QtCore>
#include <QtNetwork>

class dtkDistributedServerDaemonPrivate;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributedServerDaemon : public QTcpServer
{
    Q_OBJECT

public:
     dtkDistributedServerDaemon(quint16 port, QObject *parent = 0);
    ~dtkDistributedServerDaemon(void);

    void setManager(dtkDistributedServerManager::Type type);

    dtkDistributedServerManager *manager(void);

    void waitForConnection(int rank, QString jobid);
    QByteArray waitForData(int rank, QString jobid);

protected:
    void incomingConnection(int descriptor);

private slots:
    virtual void read(void);
    void discard(void);

private:
    dtkDistributedServerDaemonPrivate *d;
};

#endif

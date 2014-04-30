/* dtkDistributedServerDaemon.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 11:27:42 2011 (+0200)
 */


#pragma once

#include "dtkDistributedResourceManager.h"

#include <QtCore>
#include <QtNetwork>

class dtkDistributedServerDaemonPrivate;

class dtkDistributedServerDaemon : public QTcpServer
{
    Q_OBJECT

public:
     dtkDistributedServerDaemon(quint16 port, QObject *parent = 0);
    ~dtkDistributedServerDaemon(void);

    void setManager(QString type);

    dtkDistributedResourceManager *manager(void);

    void waitForConnection(int rank, QString jobid);
    QByteArray waitForData(int rank, QString jobid);

protected:
    void incomingConnection(qintptr descriptor);

private slots:
    virtual void read(void);
    void discard(void);

private:
    dtkDistributedServerDaemonPrivate *d;
};


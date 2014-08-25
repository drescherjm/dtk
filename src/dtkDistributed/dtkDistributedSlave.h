/* dtkDistributedSlave.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkDistributedExport.h"

#include <QtCore>
#include <QtNetwork>

class dtkDistributedSlavePrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedSlave : public QObject
{
    Q_OBJECT

public:
     dtkDistributedSlave(void);
     dtkDistributedSlave(QTcpSocket *socket);
    ~dtkDistributedSlave(void);

public:
    static QString jobId(void);

public:
    bool    isConnected(void);
    bool isDisconnected(void);

signals:
    void    connected(const QUrl& server);
    void disconnected(const QUrl& server);

public slots:
    void    connect(const QUrl& server);
    void disconnect(const QUrl& server);

public:
    QTcpSocket *socket();

protected slots:
    void error(QAbstractSocket::SocketError error);

private:
    dtkDistributedSlavePrivate *d;
};

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

#include <QtCore>
#include <QtNetwork>

class dtkDistributedSlavePrivate;

class dtkDistributedSlave : public QObject
{
    Q_OBJECT

public:
     dtkDistributedSlave(void);
     dtkDistributedSlave(QTcpSocket *socket);
    ~dtkDistributedSlave(void);

    QString jobId(void);

public:
    virtual int run(void);

public:
    bool    isConnected(void);
    bool isDisconnected(void);

    bool flush(void);
    void close(void);

signals:
    void    connected(const QUrl& server);
    void disconnected(const QUrl& server);

    void started(void);
    void   ended(void);

public slots:
    void    connect(const QUrl& server);
    void disconnect(const QUrl& server);

protected:
    virtual int exec(void) = 0;

public:
    QTcpSocket *socket();

protected slots:
    void      read(void);
    void onStarted(void);
    void   onEnded(void);

protected slots:
    void error(QAbstractSocket::SocketError error);

private:
    dtkDistributedSlavePrivate *d;
};


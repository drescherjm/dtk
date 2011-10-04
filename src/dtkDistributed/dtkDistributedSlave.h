/* dtkDistributedSlave.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 22 10:10:34 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 61
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSLAVE_H
#define DTKDISTRIBUTEDSLAVE_H

#include "dtkDistributedExport.h"
#include "dtkDistributedSocket.h"

#include <QtCore>
#include <QtNetwork>

class dtkDistributedSlavePrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedSlave : public QObject
{
    Q_OBJECT

public:
     dtkDistributedSlave(void);
    ~dtkDistributedSlave(void);

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

    qint64 sendRequest(QString method, QString path, int size = 0, QString type = "json", const QByteArray& content = QByteArray(), const dtkDistributedSocket::dtkDistributedSocketHeaders& headers = dtkDistributedSocket::dtkDistributedSocketHeaders());

protected slots:
    void onStarted(void);
    void   onEnded(void);

protected slots:
    void read(void);
    void write(const QByteArray& array);
    void error(QAbstractSocket::SocketError error);

private:
    dtkDistributedSlavePrivate *d;
};

#endif

/* dtkDistributedController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. oct. 31 17:07:34 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 115
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLER_H
#define DTKDISTRIBUTEDCONTROLLER_H

#include "dtkDistributedExport.h"
#include "dtkDistributedMessage.h"
#include "dtkDistributedSocket.h"

#include <dtkCore/dtkAbstractData.h>

#include <QtCore>
#include <QtNetwork>

class dtkDistributedControllerPrivate;
class dtkDistributedJob;
class dtkDistributedNode;

class DTKDISTRIBUTED_EXPORT dtkDistributedController : public QObject
{
    Q_OBJECT

public:
     dtkDistributedController(void);
    ~dtkDistributedController(void);

public:
    static dtkDistributedController *instance(void);

public:
    bool    isConnected(const QUrl& server);
    bool isDisconnected(const QUrl& server);

signals:
    void    connected(const QUrl& server);
    void disconnected(const QUrl& server);

    void updated(void);
    void updated(const QUrl& server);

    void dataPosted(const QByteArray& data);
    void jobStarted(QString jobid);
    void jobQueued(QString jobid);

    void status(const QUrl& server);

public:
    static quint16 defaultPort(void);

public:
    dtkDistributedSocket *socket(const QString& jobid);

public slots:
    bool    connect(const QUrl& server);
    void disconnect(const QUrl& server);
    bool     deploy(const QUrl& server);
    void       stop(const QUrl& server);
    void    refresh(const QUrl& server);
    void    killjob(const QUrl& server, QString jobid);
    void       send(dtkDistributedMessage *msg);
    void       send(dtkAbstractData *data, QString jobid, qint16 destrank);

public slots:
    bool     submit(const QUrl& server, QByteArray& resources);

public:
    QList<dtkDistributedNode *> nodes(void);
    QList<dtkDistributedNode *> nodes(const QString& cluster);

    QList<dtkDistributedJob *> jobs(void);
    QList<dtkDistributedJob *> jobs(const QString& cluster);

public:
    bool is_running(const QString& jobid);

protected slots:
    void read(void);
    void error(QAbstractSocket::SocketError error);
    void cleanup(void);

protected slots:
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    static dtkDistributedController *s_instance;

private:
    dtkDistributedControllerPrivate *d;
};

#endif

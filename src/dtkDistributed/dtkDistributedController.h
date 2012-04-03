/* dtkDistributedController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 10:26:58 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 68
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

#include <dtkCore/dtkAbstractData.h>

#include <QtCore>
#include <QtNetwork>

class dtkDistributedControllerPrivate;
class dtkDistributedNode;

class DTKDISTRIBUTED_EXPORT dtkDistributedController : public QObject
{
    Q_OBJECT

public:
     dtkDistributedController(void);
    ~dtkDistributedController(void);

    bool    isConnected(const QUrl& server);
    bool isDisconnected(const QUrl& server);

signals:
    void    connected(const QUrl& server);
    void disconnected(const QUrl& server);

    void updated(void);
    void updated(const QUrl& server);

    void dataPosted(const QByteArray& data);
    void jobStarted(QString jobid);

public slots:
    void    connect(const QUrl& server);
    void     deploy(const QUrl& server);
    void disconnect(const QUrl& server);
    void     submit(const QUrl& server, QByteArray& resources);
    void       send(dtkDistributedMessage *msg);
    void       send(dtkAbstractData *data, QString jobid, qint16 destrank);

public:
    QList<dtkDistributedNode *> nodes(void);
    QList<dtkDistributedNode *> nodes(const QString& cluster);

protected slots:
    void read(void);
    void error(QAbstractSocket::SocketError error);
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus );
    void cleanup(void);

private:
    dtkDistributedControllerPrivate *d;
};

#endif

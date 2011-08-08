/* dtkDistributedController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul  1 15:17:03 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 36
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

public slots:
    void    connect(const QUrl& server);
    void disconnect(const QUrl& server);

public:
    QList<dtkDistributedNode *> nodes(void);
    QList<dtkDistributedNode *> nodes(const QString& cluster);

protected slots:
    void read(void);
    void error(QAbstractSocket::SocketError error);

private:
    dtkDistributedControllerPrivate *d;
};

#endif

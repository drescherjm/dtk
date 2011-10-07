/* dtkDistributedSocket.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. oct.  6 18:25:50 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #:
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKDISTRIBUTEDSOCKET_H
#define DTKDISTRIBUTEDSOCKET_H

#include <QObject>
#include <QtCore>
#include <QTcpSocket>
#include "dtkDistributedExport.h"

class dtkDistributedSocketPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedSocket : public QTcpSocket
{
    Q_OBJECT

public:
    typedef QHash<QString, QString> dtkDistributedSocketHeaders;

public:
             dtkDistributedSocket( QObject *parent = 0);
    virtual ~dtkDistributedSocket(void);

    qint64       sendRequest(QString method, QString path, qint64 size = 0, QString type = "json", const QByteArray& content = QByteArray(),  const dtkDistributedSocketHeaders& headers = dtkDistributedSocketHeaders());

    QVariantMap parseRequest(void);

private:

    dtkDistributedSocketPrivate *d;

};

#endif

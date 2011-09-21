/* dtkDistributedSocket.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. sept. 20 21:57:26 2011 (+0200)
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


class DTKDISTRIBUTED_EXPORT dtkDistributedSocket : public QTcpSocket
{
    Q_OBJECT

public:
    dtkDistributedSocket( QObject *parent = 0);
    virtual ~dtkDistributedSocket(void);

    qint64 sendRequest(QString method, QString path, int size = 0, QString type = "json", const QByteArray  &content = NULL,  const QHash<QString,QString>  & headers = QHash<QString,QString>() );
    QVariantMap parseRequest(void);

};

#endif

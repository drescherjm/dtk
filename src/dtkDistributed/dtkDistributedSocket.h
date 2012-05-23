/* dtkDistributedSocket.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 21 23:50:26 2012 (+0200)
 *           By: Julien Wintz
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

#include "dtkDistributedExport.h"
#include "dtkDistributedMessage.h"

#include <QtCore>
#include <QtNetwork>

class dtkAbstractData;

class dtkDistributedSocketPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedSocket : public QTcpSocket
{
    Q_OBJECT

public:
             dtkDistributedSocket( QObject *parent = 0);
    virtual ~dtkDistributedSocket(void);

public:
    qint64 sendRequest(dtkDistributedMessage *msg);

public:
    void send(dtkAbstractData *data, QString jobid, qint16 target);
    void send(QVariant data, QString jobid, qint16 target);

public:
    dtkDistributedMessage *parseRequest(void);

private:
    dtkDistributedSocketPrivate *d;
};

#endif

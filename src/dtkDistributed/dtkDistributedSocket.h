/* dtkDistributedSocket.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: ven. avril 13 13:31:07 2012 (+0200)
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
#include "dtkDistributedMessage.h"

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
    dtkDistributedMessage *parseRequest(void);

public:
    bool waitForData(int max_wait = 300000);

private:
    dtkDistributedSocketPrivate *d;
};

#endif

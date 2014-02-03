/* dtkDistributedSocket.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: ven. mars 22 16:34:51 2013 (+0100)
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

#include "dtkDistributedSupportExport.h"
#include "dtkDistributedMessage.h"

#include <QtCore>
#include <QtNetwork>

class dtkAbstractData;

class dtkDistributedSocketPrivate;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributedSocket : public QTcpSocket
{
    Q_OBJECT

public:
             dtkDistributedSocket( QObject *parent = 0);
    virtual ~dtkDistributedSocket(void);

public:
    qint64 sendRequest(dtkDistributedMessage *msg);

public:
    void fflush(void);

public:
    dtkDistributedMessage *parseRequest(void);

private:
    dtkDistributedSocketPrivate *d;
};

#endif

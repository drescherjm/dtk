/* dtkDistributedSocket.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: Wed Jun  1 11:28:54 2011 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. oct.  4 16:05:11 2012 (+0200)
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
    dtkDistributedMessage *parseRequest(void);

private:
    dtkDistributedSocketPrivate *d;
};

#endif

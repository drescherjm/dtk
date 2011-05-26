/* dtkDistributedServer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 11:29:33 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVER_H
#define DTKDISTRIBUTEDSERVER_H

#include "dtkDistributedExport.h"

#include <QtCore>
#include <QtNetwork>

class dtkDistributedServerPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedServer : public QTcpServer
{
    Q_OBJECT

public:
     dtkDistributedServer(quint16 port, QObject *parent = 0);
    ~dtkDistributedServer(void);

protected:
    void incomingConnection(int descriptor);

private slots:
    void read(void);
    void discard(void);

private:
    dtkDistributedServerPrivate *d;
};

#endif

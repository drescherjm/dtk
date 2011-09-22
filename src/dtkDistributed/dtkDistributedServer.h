/* dtkDistributedServer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep 19 10:38:36 2011 (+0200)
 *           By: jwintz
 *     Update #: 73
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
#include "dtkDistributedService.h"

#include <QtCore>

class dtkDistributedServerPrivate;
class dtkDistributedServerManager;

class DTKDISTRIBUTED_EXPORT dtkDistributedServer : public dtkDistributedService<QCoreApplication>
{
public:
     dtkDistributedServer(int argc, char **argv);
    ~dtkDistributedServer(void);

    dtkDistributedServerManager *manager(void);

          void waitForConnection(int rank);
    QByteArray waitForData(int rank);

public slots:
    void run(void);

protected:
    void start(void);

private:
    dtkDistributedServerPrivate *d;
};

#endif

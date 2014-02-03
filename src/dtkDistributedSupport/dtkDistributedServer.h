/* dtkDistributedServer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. oct. 16 10:09:23 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 74
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVER_H
#define DTKDISTRIBUTEDSERVER_H

#include "dtkDistributedSupportExport.h"
#include "dtkDistributedService.h"

#include <QtCore>

class dtkDistributedServerPrivate;
class dtkDistributedServerManager;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributedServer : public dtkDistributedService<QCoreApplication>
{
public:
     dtkDistributedServer(int argc, char **argv);
    ~dtkDistributedServer(void);

    dtkDistributedServerManager *manager(void);

    void waitForConnection(int rank, QString jobid);
    QByteArray waitForData(int rank, QString jobid);

public slots:
    void run(void);

protected:
    void start(void);

private:
    dtkDistributedServerPrivate *d;
};

#endif

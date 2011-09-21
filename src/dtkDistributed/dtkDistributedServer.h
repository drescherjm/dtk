/* dtkDistributedServer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. sept. 15 10:50:01 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 59
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

    dtkDistributedServerManager * manager(void);

    public slots:
    void run(void);

protected:
    void start(void);

private:
    dtkDistributedServerPrivate *d;
};

#endif

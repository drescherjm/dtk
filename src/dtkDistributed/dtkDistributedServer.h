/* dtkDistributedServer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun  1 11:28:37 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 45
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

class DTKDISTRIBUTED_EXPORT dtkDistributedServer : public dtkDistributedService<QCoreApplication>
{
public:
     dtkDistributedServer(int argc, char **argv);
    ~dtkDistributedServer(void);

protected:
    void start(void);

private:
    dtkDistributedServerPrivate *d;
};

#endif

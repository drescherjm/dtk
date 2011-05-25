/* dtkDistributedServer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 25 14:19:45 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 9
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

#include <QtCore/QObject>

class dtkDistributedServerPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedServer : public QObject
{
    Q_OBJECT

public:
     dtkDistributedServer(void);
    ~dtkDistributedServer(void);

private:
    dtkDistributedServerPrivate *d;
};

#endif

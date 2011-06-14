/* dtkDistributedClient.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 25 14:18:39 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCLIENT_H
#define DTKDISTRIBUTEDCLIENT_H

#include "dtkDistributedExport.h"

#include <QtCore/QObject>

class dtkDistributedClientPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedClient : public QObject
{
    Q_OBJECT

public:
     dtkDistributedClient(void);
    ~dtkDistributedClient(void);

private:
    dtkDistributedClientPrivate *d;
};

#endif

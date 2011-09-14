/* dtkDistributedSlave.h --- 
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

#ifndef DTKDISTRIBUTEDSLAVE_H
#define DTKDISTRIBUTEDSLAVE_H

#include "dtkDistributedExport.h"

#include <QtCore/QObject>

class dtkDistributedSlavePrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedSlave : public QObject
{
    Q_OBJECT

public:
     dtkDistributedSlave(void);
    ~dtkDistributedSlave(void);

private:
    dtkDistributedSlavePrivate *d;
};

#endif

/* dtkDistributedCore.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:24:27 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 22 10:13:49 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCORE_H
#define DTKDISTRIBUTEDCORE_H

#include <QObject>

#include "dtkDistributedExport.h"

class dtkDistributedCpu;
class dtkDistributedGpu;
class dtkDistributedCorePrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedCore : public QObject
{
    Q_OBJECT

public:
     dtkDistributedCore(dtkDistributedCpu *parent);
     dtkDistributedCore(dtkDistributedGpu *parent);
    ~dtkDistributedCore(void);

private:
    dtkDistributedCorePrivate *d;
};

#endif

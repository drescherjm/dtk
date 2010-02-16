/* dtkDistributedGpu.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:32:38 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 16 16:28:47 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDGPU_H
#define DTKDISTRIBUTEDGPU_H

#include <QtCore>

#include "dtkDistributedExport.h"

class dtkDistributedNode;
class dtkDistributedCore;
class dtkDistributedGpuPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedGpu : public QObject
{
    Q_OBJECT

public:
     dtkDistributedGpu(dtkDistributedNode *parent);
    ~dtkDistributedGpu(void);

private:
    dtkDistributedGpuPrivate *d;
};

#endif

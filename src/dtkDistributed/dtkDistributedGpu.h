/* dtkDistributedGpu.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:32:38 2010 (+0100)
 * Version: $Id$
 * Last-Updated: mar. juin 28 17:40:50 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 23
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
class dtkDistributedGpuPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedGpu : public QObject
{
    Q_OBJECT

public:
     dtkDistributedGpu(dtkDistributedNode *parent);
    ~dtkDistributedGpu(void);

public:
    enum Architecture {
           Nvidia = 0x1,
              AMD = 0x2
    };

    Architecture architecture(void);

    void setArchitecture(Architecture arch);

    enum Model {
           T10    = 0x1,
           C2050  = 0x2,
           C2070  = 0x4
    };

    Model model(void);

    void setModel(Model model);


private:
    dtkDistributedGpuPrivate *d;
};

#endif

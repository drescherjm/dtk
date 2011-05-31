/* dtkDistributedGpu.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:32:38 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 31 20:51:49 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
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

public:
    enum Architecture {
           x86 = 0x1,
        x86_64 = 0x2
    };

    Architecture architecture(void);

    void setArchitecture(Architecture arch);

    enum Model {
           Xeon = 0x1,
        Opteron = 0x2
    };

    Model model(void);

    void setModel(Model model);

    enum Cardinality {
        Single = 0x1,
          Dual = 0x2,
          Quad = 0x4,
          Octo = 0x8
    };

    Cardinality cardinality(void);
    
    void setCardinality(Cardinality cardinality);

public:
    QList<dtkDistributedCore *> cores(void);

    void operator << (dtkDistributedCore *core);

private:
    dtkDistributedGpuPrivate *d;
};

#endif

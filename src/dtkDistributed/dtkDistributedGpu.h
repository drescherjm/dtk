/* dtkDistributedGpu.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:32:38 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 22 10:11:17 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 8
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

    enum Architecture {
        x86,
        x86_64,
    };

    Architecture architecture(void);

    void setArchitecture(Architecture arch);

    enum Model {
        Xeon,
        Opteron
    };

    Model model(void);

    void setModel(Model model);

    QList<dtkDistributedCore *> cores(void);

    void operator << (dtkDistributedCore *core);

private:
    dtkDistributedGpuPrivate *d;
};

#endif

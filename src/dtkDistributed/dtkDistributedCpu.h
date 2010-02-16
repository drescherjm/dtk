/* dtkDistributedCpu.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:23:49 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 16 17:13:01 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCPU_H
#define DTKDISTRIBUTEDCPU_H

#include <QObject>

#include "dtkDistributedExport.h"

class dtkDistributedNode;
class dtkDistributedCore;
class dtkDistributedCpuPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedCpu : public QObject
{
    Q_OBJECT

public:
     dtkDistributedCpu(dtkDistributedNode *parent);
    ~dtkDistributedCpu(void);

    enum Architecture {
        dtkDistributedCpuX86,
        dtkDistributedCpuX86_64,
    };

    Architecture architecture(void);

    enum Model {
        dtkDistributedCpuXeon,
        dtkDistributedCpuOpteron
    };

    Model model(void);

    QList<dtkDistributedCore *> cores(void);

private:
    dtkDistributedCpuPrivate *d;
};

#endif

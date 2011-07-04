/* dtkDistributedCpu.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:23:49 2010 (+0100)
 * Version: $Id$
 * Last-Updated: mar. juin 28 17:33:12 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 33
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

    int cardinality(void);

    void setCardinality(int cardinality);

public:
    QList<dtkDistributedCore *> cores(void);

    void operator << (dtkDistributedCore *core);

private:
    dtkDistributedCpuPrivate *d;
};

#endif

/* dtkDistributedCpu.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:23:49 2010 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QObject>

class dtkDistributedNode;
class dtkDistributedCore;
class dtkDistributedCpuPrivate;

class dtkDistributedCpu : public QObject
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

    Q_DECLARE_FLAGS(Architectures, Architecture)

    enum Model {
           Xeon = 0x1,
        Opteron = 0x2
    };

    Q_DECLARE_FLAGS(Models, Model)

    Architecture architecture(void);
    Model model(void);
    int cardinality(void);

    void setArchitecture(Architecture arch);
    void setModel(Model model);
    void setCardinality(int cardinality);

public:
    QList<dtkDistributedCore *> cores(void);

public:
    void operator << (dtkDistributedCore *core);

private:
    dtkDistributedCpuPrivate *d;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(dtkDistributedCpu::Architectures)
Q_DECLARE_OPERATORS_FOR_FLAGS(dtkDistributedCpu::Models)


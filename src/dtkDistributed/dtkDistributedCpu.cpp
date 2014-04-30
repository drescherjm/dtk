/* dtkDistributedCpu.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedCore.h"
#include "dtkDistributedCpu.h"

class dtkDistributedCpuPrivate
{
public:
    dtkDistributedNode *parent;

    dtkDistributedCpu::Architecture architecture;
    dtkDistributedCpu::Model model;

    int cardinality;

    QList<dtkDistributedCore *> cores;
};

dtkDistributedCpu::dtkDistributedCpu(dtkDistributedNode *parent) : QObject(), d(new dtkDistributedCpuPrivate)
{
    d->parent = parent;
}

dtkDistributedCpu::~dtkDistributedCpu(void)
{
    qDeleteAll(d->cores);

    delete d;

    d = NULL;
}

dtkDistributedCpu::Architecture dtkDistributedCpu::architecture(void)
{
    return d->architecture;
}

void dtkDistributedCpu::setArchitecture(Architecture arch)
{
    d->architecture = arch;
}

dtkDistributedCpu::Model dtkDistributedCpu::model(void)
{
    return d->model;
}

void dtkDistributedCpu::setModel(Model model)
{
    d->model = model;
}

int dtkDistributedCpu::cardinality(void)
{
    return d->cardinality;
}

void dtkDistributedCpu::setCardinality(int cardinality)
{
    d->cardinality = cardinality;
}

QList<dtkDistributedCore *> dtkDistributedCpu::cores(void)
{
    return d->cores;
}

void dtkDistributedCpu::operator << (dtkDistributedCore *core)
{
    d->cores << core;
}

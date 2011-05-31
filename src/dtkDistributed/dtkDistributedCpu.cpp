/* dtkDistributedCpu.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:18:36 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 31 20:00:43 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedCpu.h"

class dtkDistributedCpuPrivate
{
public:
    dtkDistributedNode *parent;

    dtkDistributedCpu::Architecture architecture;
    dtkDistributedCpu::Model model;
    dtkDistributedCpu::Cardinality cardinality;

    QList<dtkDistributedCore *> cores;
};

dtkDistributedCpu::dtkDistributedCpu(dtkDistributedNode *parent) : QObject(), d(new dtkDistributedCpuPrivate)
{
    d->parent = parent;
}

dtkDistributedCpu::~dtkDistributedCpu(void)
{
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

dtkDistributedCpu::Cardinality dtkDistributedCpu::cardinality(void)
{
    return d->cardinality;
}

void dtkDistributedCpu::setCardinality(Cardinality cardinality)
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

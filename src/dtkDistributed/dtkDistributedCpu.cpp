/* dtkDistributedCpu.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:18:36 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 16 16:23:01 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
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

    QList<dtkDistributedCore *> cores;
};

dtkDistributedCpu::dtkDistributedCpu(dtkDistributedNode *parent) : QObject(), d(new dtkDistributedCpuPrivate)
{

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

dtkDistributedCpu::Model dtkDistributedCpu::model(void)
{
    return d->model;
}

QList<dtkDistributedCore *> dtkDistributedCpu::cores(void)
{
    return d->cores;
}

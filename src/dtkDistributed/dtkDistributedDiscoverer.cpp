/* dtkDistributedDiscoverer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:44:52 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 17 09:52:48 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedNode.h"
#include "dtkDistributedCore.h"
#include "dtkDistributedCpu.h"
#include "dtkDistributedGpu.h"
#include "dtkDistributedDiscoverer.h"

#include <dtkCore/dtkGlobal.h>

class dtkDistributedDiscovererPrivate
{
public:
    QList<dtkDistributedNode *> nodes;
};

dtkDistributedDiscoverer::dtkDistributedDiscoverer(void) : QObject(), d(new dtkDistributedDiscovererPrivate)
{

}

dtkDistributedDiscoverer::~dtkDistributedDiscoverer(void)
{
    delete d;

    d = NULL;
}

QList<dtkDistributedNode *> dtkDistributedDiscoverer::nodes(void)
{
    return d->nodes;
}

QList<dtkDistributedCpu *> dtkDistributedDiscoverer::cpus(void)
{
    QList<dtkDistributedCpu *> cpus;

    foreach(dtkDistributedNode *node, d->nodes)
        cpus << node->cpus();

    return cpus;
}

QList<dtkDistributedGpu *> dtkDistributedDiscoverer::gpus(void)
{
    QList<dtkDistributedGpu *> gpus;

    foreach(dtkDistributedNode *node, d->nodes)
        gpus << node->gpus();

    return gpus;
}

QList<dtkDistributedCore *> dtkDistributedDiscoverer::cores(void)
{
    QList<dtkDistributedCore *> cores;

    foreach(dtkDistributedCpu *cpu, this->cpus())
        cores << cpu->cores();

    return cores;
}

bool dtkDistributedDiscoverer::available(dtkDistributedNode *node, int duration)
{
    DTK_UNUSED(node);
    DTK_UNUSED(duration);

    return false;
}

bool dtkDistributedDiscoverer::available(dtkDistributedCpu *cpu, int duration)
{
    DTK_UNUSED(cpu);
    DTK_UNUSED(duration);

    return false;
}

bool dtkDistributedDiscoverer::available(dtkDistributedGpu *gpu, int duration)
{
    DTK_UNUSED(gpu);
    DTK_UNUSED(duration);

    return false;
}

bool dtkDistributedDiscoverer::available(dtkDistributedCore *core, int duration)
{
    DTK_UNUSED(core);
    DTK_UNUSED(duration);

    return false;
}

/* dtkDistributedServerManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:02:52 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 31 23:47:52 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedCore.h"
#include "dtkDistributedCpu.h"
#include "dtkDistributedGpu.h"
#include "dtkDistributedNode.h"
#include "dtkDistributedServerManager.h"
#include "dtkDistributedServerManager_p.h"

#include <dtkCore/dtkGlobal.h>

dtkDistributedServerManager::dtkDistributedServerManager(void) : d(new dtkDistributedServerManagerPrivate)
{

}

dtkDistributedServerManager::~dtkDistributedServerManager(void)
{
    delete d;

    d = NULL;
}

QList<dtkDistributedNode *> dtkDistributedServerManager::nodes(void)
{
    return d->nodes;
}

QList<dtkDistributedCpu *> dtkDistributedServerManager::cpus(void)
{
    QList<dtkDistributedCpu *> cpus;

    foreach(dtkDistributedNode *node, d->nodes)
        cpus << node->cpus();

    return cpus;
}

QList<dtkDistributedGpu *> dtkDistributedServerManager::gpus(void)
{
    QList<dtkDistributedGpu *> gpus;

    foreach(dtkDistributedNode *node, d->nodes)
        gpus << node->gpus();

    return gpus;
}

QList<dtkDistributedCore *> dtkDistributedServerManager::cores(void)
{
    QList<dtkDistributedCore *> cores;

    foreach(dtkDistributedCpu *cpu, this->cpus())
        cores << cpu->cores();

    return cores;
}

bool dtkDistributedServerManager::available(dtkDistributedNode *node, int duration)
{
    DTK_UNUSED(node);
    DTK_UNUSED(duration);

    return false;
}

bool dtkDistributedServerManager::available(dtkDistributedCpu *cpu, int duration)
{
    DTK_UNUSED(cpu);
    DTK_UNUSED(duration);

    return false;
}

bool dtkDistributedServerManager::available(dtkDistributedGpu *gpu, int duration)
{
    DTK_UNUSED(gpu);
    DTK_UNUSED(duration);

    return false;
}

bool dtkDistributedServerManager::available(dtkDistributedCore *core, int duration)
{
    DTK_UNUSED(core);
    DTK_UNUSED(duration);

    return false;
}

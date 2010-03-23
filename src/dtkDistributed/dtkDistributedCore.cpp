/* dtkDistributedCore.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:26:17 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 22 10:14:41 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedCore.h"
#include "dtkDistributedCpu.h"

class dtkDistributedCorePrivate
{
public:
    dtkDistributedCpu *cpu;
    dtkDistributedGpu *gpu;
};

dtkDistributedCore::dtkDistributedCore(dtkDistributedCpu *parent) : QObject(), d(new dtkDistributedCorePrivate)
{
    d->cpu = parent;
    d->gpu = NULL;
}

dtkDistributedCore::dtkDistributedCore(dtkDistributedGpu *parent) : QObject(), d(new dtkDistributedCorePrivate)
{
    d->cpu = NULL;
    d->gpu = parent;
}

dtkDistributedCore::~dtkDistributedCore(void)
{
    delete d;

    d = NULL;
}

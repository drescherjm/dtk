/* dtkDistributedCore.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:26:17 2010 (+0100)
 * Version: $Id$
 * Last-Updated: mer. août 10 11:04:38 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 44
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedCore.h"
#include "dtkDistributedCpu.h"
#include "dtkDistributedJob.h"

class dtkDistributedCorePrivate
{
public:
    dtkDistributedCpu *cpu;

    dtkDistributedJob *job;

};

dtkDistributedCore::dtkDistributedCore(dtkDistributedCpu *parent) : QObject(), d(new dtkDistributedCorePrivate)
{
    d->cpu = parent;
}

dtkDistributedCore::~dtkDistributedCore(void)
{
    delete d;

    d = NULL;
}


dtkDistributedJob* dtkDistributedCore::job(void)
{
    return d->job;
}

void dtkDistributedCore::setJob(dtkDistributedJob *job)
{
    d->job = job;
}

void dtkDistributedCore::delJob(void)
{
    d->job = NULL;
}


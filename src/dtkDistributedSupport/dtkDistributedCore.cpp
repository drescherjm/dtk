/* dtkDistributedCore.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:26:17 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr  5 10:38:22 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 69
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
    qint64 id;
};

dtkDistributedCore::dtkDistributedCore(dtkDistributedCpu *parent, qint64 id) : QObject(), d(new dtkDistributedCorePrivate)
{
    d->cpu = parent;
    d->job = NULL;
    d->id = id;
}

dtkDistributedCore::~dtkDistributedCore(void)
{
    delete d;

    d = NULL;
}

dtkDistributedJob *dtkDistributedCore::job(void)
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

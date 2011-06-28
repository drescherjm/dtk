/* dtkDistributedCore.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:26:17 2010 (+0100)
 * Version: $Id$
 * Last-Updated: mar. juin 28 17:40:04 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 10
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

/* dtkDistributedGpu.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:23:42 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 16 16:24:12 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedGpu.h"

class dtkDistributedGpuPrivate
{
public:
};

dtkDistributedGpu::dtkDistributedGpu(dtkDistributedNode *parent) : QObject(), d(new dtkDistributedGpuPrivate)
{

}

dtkDistributedGpu::~dtkDistributedGpu(void)
{
    delete d;

    d = NULL;
}

/* dtkDistributedCore.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:26:17 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 16 17:13:25 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
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
    dtkDistributedCpu *parent;
};

dtkDistributedCore::dtkDistributedCore(dtkDistributedCpu *parent) : QObject(), d(new dtkDistributedCorePrivate)
{

}

dtkDistributedCore::~dtkDistributedCore(void)
{
    delete d;

    d = NULL;
}

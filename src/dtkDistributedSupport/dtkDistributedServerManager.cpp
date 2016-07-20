/* dtkDistributedServerManager.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:02:52 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 28 14:31:51 2011 (+0200)
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
#include "dtkDistributedGpu.h"
#include "dtkDistributedNode.h"
#include "dtkDistributedServerManager.h"
#include "dtkDistributedServerManager_p.h"

#include <dtkCoreSupport/dtkGlobal.h>

dtkDistributedServerManager::dtkDistributedServerManager(void) : d(new dtkDistributedServerManagerPrivate)
{

}

dtkDistributedServerManager::~dtkDistributedServerManager(void)
{
    delete d;

    d = NULL;
}

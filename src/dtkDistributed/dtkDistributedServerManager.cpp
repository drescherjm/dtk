/* dtkDistributedServerManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:02:52 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 31 23:03:51 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedServerManager.h"

class dtkDistributedServerManagerPrivate
{
public:
};

dtkDistributedServerManager::dtkDistributedServerManager(void) : d(new dtkDistributedServerManagerPrivate)
{

}

dtkDistributedServerManager::~dtkDistributedServerManager(void)
{
    delete d;

    d = NULL;
}

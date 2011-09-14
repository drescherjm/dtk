/* dtkDistributedTutorial4Slave.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Sep 14 13:26:49 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep 14 13:27:56 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedTutorial4Slave.h"

class dtkDistributedTutorial4SlavePrivate
{
public:

};

dtkDistributedTutorial4Slave::dtkDistributedTutorial4Slave(void) : dtkDistributedSlave(), d(new dtkDistributedTutorial4SlavePrivate)
{

}

dtkDistributedTutorial4Slave::~dtkDistributedTutorial4Slave(void)
{
    delete d;

    d = NULL;
}

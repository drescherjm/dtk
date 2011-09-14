/* dtkDistributedTutorial4Slave.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Sep 14 13:25:20 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep 14 13:50:56 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDTUTORIAL4SLAVE_H
#define DTKDISTRIBUTEDTUTORIAL4SLAVE_H

#include <dtkDistributed/dtkDistributedSlave.h>

class dtkDistributedTutorial4SlavePrivate;

class dtkDistributedTutorial4Slave : public dtkDistributedSlave
{
public:
     dtkDistributedTutorial4Slave(void);
    ~dtkDistributedTutorial4Slave(void);

public:
    void exec(void);

private:
    dtkDistributedTutorial4SlavePrivate *d;
};

#endif

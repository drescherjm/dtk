/* dtkDistributedTutorial6Slave.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Sep 14 13:25:20 2011 (+0200)
 * Version: $Id$
 * Last-Updated: lun. déc.  5 10:58:48 2011 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDTUTORIAL6SLAVE_H
#define DTKDISTRIBUTEDTUTORIAL6SLAVE_H

#include <dtkDistributed/dtkDistributedSlave.h>

class dtkDistributedTutorial6SlavePrivate;

class dtkDistributedTutorial6Slave : public dtkDistributedSlave
{
public:
     dtkDistributedTutorial6Slave(void);
    ~dtkDistributedTutorial6Slave(void);

    void setCount(int count);

public:
    int exec(void);

private:
    dtkDistributedTutorial6SlavePrivate *d;
};

#endif

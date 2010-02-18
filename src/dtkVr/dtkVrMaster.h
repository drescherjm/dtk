/* dtkVrMaster.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 10 21:06:22 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 11:16:57 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRMASTER_H
#define DTKVRMASTER_H

#include "dtkVrProcess.h"

class dtkVrMasterPrivate;

class dtkVrMaster : public dtkVrProcess
{
public:
     dtkVrMaster(dtkDistributedCommunicator *communicator);
    ~dtkVrMaster(void);

    virtual void   initialize(void);
    virtual void uninitialize(void);

protected:
    void process(void);

private:
    dtkVrMasterPrivate *d;
};

#endif

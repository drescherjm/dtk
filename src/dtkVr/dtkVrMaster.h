/* dtkVrMaster.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 10 21:06:22 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon May  9 14:46:33 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 34
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
#include "dtkVrTrackerVrpn.h"

class dtkVrMasterPrivate;

class dtkVrMaster : public dtkVrProcess
{
    Q_OBJECT

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

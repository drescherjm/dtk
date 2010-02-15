/* dtkVrMaster.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 10 21:06:22 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Feb 13 20:51:25 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
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
     dtkVrMaster(void);
    ~dtkVrMaster(void);

    virtual void   initialize(void);
    virtual void uninitialize(void);

protected:
    void process(void);

private:
    dtkVrMasterPrivate *d;
};

#endif

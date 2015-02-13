/* dtkDistributedAbstractApplication.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/02/04 12:28:51
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkDistributedExport.h"

#include <dtkCore/dtkAbstractApplication.h>

class dtkDistributedCommunicator;
class dtkDistributedPolicy;
class dtkDistributedAbstractApplicationPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedAbstractApplication: public dtkAbstractApplication
{
public:
             dtkDistributedAbstractApplication(void);
    virtual ~dtkDistributedAbstractApplication(void);

public:
    virtual void initialize(void);
    virtual void exec(QRunnable *task);
    virtual void spawn(void);
    virtual void unspawn(void);

public:
    bool isMaster(void);
    dtkDistributedCommunicator *communicator(void);
    dtkDistributedPolicy *policy(void);

private:
    dtkDistributedAbstractApplicationPrivate *d;

};



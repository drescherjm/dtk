/* @(#)dtkDistributedCoreApplication.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/01/27 10:33:58
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkDistributedExport.h"

#include <dtkCore/dtkCoreApplication.h>


class dtkDistributedPolicy;
class dtkDistributedCommunicator;
class dtkDistributedCoreApplicationPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedCoreApplication: public dtkCoreApplication
{
public:
             dtkDistributedCoreApplication(int &argc, char **argv);
    virtual ~dtkDistributedCoreApplication(void);

public:
    virtual void initialize(void);
    virtual void exec(QRunnable *work);

public:
    bool isMaster(void);
    dtkDistributedCommunicator *communicator(void);
    dtkDistributedPolicy *policy(void);

private:
    dtkDistributedCoreApplicationPrivate *d;
};


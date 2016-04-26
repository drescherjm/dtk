/* dtkDistributedApplication.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/02/04 12:31:06
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkDistributed.h"
#include "dtkDistributedApplication.h"
#include "dtkDistributedApplicationPrivate.h"
#include "dtkDistributedCommunicator"
#include "dtkDistributedSettings.h"
#include "dtkDistributedPolicy.h"

#include <dtkLog>



/*!
  \class dtkDistributedApplication
  \inmodule dtkDistributed
  \brief dtkDistributedApplication ...

*/

dtkDistributedApplication::dtkDistributedApplication(int &argc, char **argv): dtkCoreApplication(argc, argv)
{

    d = new dtkDistributedApplicationPrivate;
}

dtkDistributedApplication::~dtkDistributedApplication(void)
{
    delete d;
    d = NULL;
}

void dtkDistributedApplication::initialize(void)
{
    d->initialize();
}

void dtkDistributedApplication::exec(QRunnable *task)
{
    d->policy.communicator()->exec(task);
}

void dtkDistributedApplication::spawn(QMap<QString,QString> options)
{
    d->spawn();
}

void dtkDistributedApplication::unspawn(void)
{
    d->unspawn();
}

dtkDistributedPolicy *dtkDistributedApplication::policy(void)
{
     return &(d->policy);
}

dtkDistributedCommunicator *dtkDistributedApplication::communicator(void)
{

    return d->policy.communicator();
}

bool dtkDistributedApplication::isMaster(void)
{
    return (d->policy.communicator()->rank() == 0);
}

/* always returns true: just to be compatible with dtkDistributedGuiApplication */
bool dtkDistributedApplication::noGui(void)
{
    return true;
}

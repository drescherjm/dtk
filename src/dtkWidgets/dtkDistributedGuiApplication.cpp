/* @(#)dtkDistributedGuiApplication.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/04/25 13:06:26
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedGuiApplication.h"

#include <dtkDistributed/dtkDistributedApplicationPrivate.h>
#include <dtkDistributed/dtkDistributedCommunicator.h>

#include <dtkWidgets/dtkApplication.h>

#include <dtkLog>

/*!
  \class dtkDistributedApplication
  \inmodule dtkDistributed
  \brief dtkDistributedApplication ...

*/

dtkDistributedGuiApplication::dtkDistributedGuiApplication(int &argc, char **argv): QApplication(argc, argv)
{

    d = new dtkDistributedApplicationPrivate;
    d->spawned = false;
    d->nospawn = false;

}

dtkDistributedGuiApplication::~dtkDistributedGuiApplication(void)
{
    delete d;
    d = NULL;
}

void dtkDistributedGuiApplication::initialize(void)
{
    d->initialize();
}

QCommandLineParser *dtkDistributedGuiApplication::parser(void)
{
    return d->parser;
}

bool dtkDistributedGuiApplication::noGui(void)
{
    return !(qApp && qobject_cast<QGuiApplication *>(qApp) && (QGuiApplication::platformName() != "minimal")) ;
}

void dtkDistributedGuiApplication::exec(QRunnable *task)
{
    d->policy.communicator()->exec(task);
}

void dtkDistributedGuiApplication::spawn(QMap<QString,QString> options)
{
    d->spawn();
}

void dtkDistributedGuiApplication::unspawn(void)
{
    d->unspawn();
}

dtkDistributedPolicy *dtkDistributedGuiApplication::policy(void)
{
     return &(d->policy);
}

dtkDistributedCommunicator *dtkDistributedGuiApplication::communicator(void)
{

    return d->policy.communicator();
}

bool dtkDistributedGuiApplication::isMaster(void)
{
    return (d->policy.communicator()->rank() == 0);
}


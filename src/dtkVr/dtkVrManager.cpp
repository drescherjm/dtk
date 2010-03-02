/* dtkVrManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 10:09:51 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  2 15:13:49 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 81
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrManager.h"
#include "dtkVrMaster.h"
#include "dtkVrSlave.h"

#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkLog.h>

#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorMpi.h>

class dtkVrManagerPrivate
{
public:
    bool stereo;

    QUrl device;
    QUrl tracker;

    dtkDistributedCommunicatorMpi *communicator;
};

dtkVrManager *dtkVrManager::instance(void)
{
    if(!s_instance)
        s_instance = new dtkVrManager;

    return s_instance;
}

void dtkVrManager::initialize(void)
{
    d->communicator->initialize();
}

void dtkVrManager::uninitialize(void)
{
    d->communicator->uninitialize();
}

void dtkVrManager::setTracker(const QUrl& url)
{
    d->tracker = url;
}

void dtkVrManager::setDevice(const QUrl& url)
{
    d->device = url;
}

void dtkVrManager::setStereo(bool on)
{
    d->stereo = on;
}

dtkVrProcess *dtkVrManager::create(QString type)
{
    dtkAbstractView *view = dtkAbstractViewFactory::instance()->create(type);

    if(!view)
        dtkWarning() << "no" << type << "specialization is available";

    dtkVrProcess *process = NULL;

    if(d->communicator->rank()) {
        process = new dtkVrSlave(d->communicator);
        dynamic_cast <dtkVrSlave *>(process)->setView(view);
        dynamic_cast <dtkVrSlave *>(process)->setStereo(d->stereo);
    } else {
        process = new dtkVrMaster(d->communicator);
        if(d->tracker.isValid())
            dynamic_cast <dtkVrMaster *>(process)->setTracker(d->tracker);
        if(d->device.isValid())
            dynamic_cast <dtkVrMaster *>(process)->setDevice(d->device);
    }

    return process;
}

dtkVrManager::dtkVrManager(void) : QObject(), d(new dtkVrManagerPrivate)
{
    d->communicator = new dtkDistributedCommunicatorMpi;
}

dtkVrManager::~dtkVrManager(void)
{
    delete d;

    d = NULL;
}

dtkVrManager *dtkVrManager::s_instance = NULL;

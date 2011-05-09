/* dtkVrMaster.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 10:03:10 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu May  5 09:15:52 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 212
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrMaster.h"
#include "dtkVrDeviceVrpn.h"
#include "dtkVrTrackerVrpn.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkVec3.h>
#include <dtkCore/dtkQuat.h>

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkVrMasterPrivate
// /////////////////////////////////////////////////////////////////

class dtkVrMasterPrivate
{
public:
    QUrl trackerUrl;
    QUrl deviceUrl;

    dtkVrTrackerVrpn *tracker;
    dtkVrDeviceVrpn *device;

    static void positionHandler1(float x, float y, float z);
    static void positionHandler2(float x, float y, float z);

    static void orientationHandler1(float q0, float q1, float q2, float q3);
    static void orientationHandler2(float q0, float q1, float q2, float q3);

    static dtkVrMasterPrivate *self;

    dtkVrMaster *q;
};

void dtkVrMasterPrivate::positionHandler1(float x, float y, float z)
{
    // self->q->user()->setPosition(dtkVec3(x, y, z));
}

void dtkVrMasterPrivate::positionHandler2(float x, float y, float z)
{
    // self->q->wand()->setCurrentPosition(dtkVec3(x, y, z));
}

void dtkVrMasterPrivate::orientationHandler1(float q0, float q1, float q2, float q3)
{
    // self->q->user()->setOrientation(dtkQuat(q0, q1, q2, q3));
}

void dtkVrMasterPrivate::orientationHandler2(float q0, float q1, float q2, float q3)
{
    // self->q->wand()->setCurrentOrientation(dtkQuat(q0, q1, q2, q3));
}

dtkVrMasterPrivate *dtkVrMasterPrivate::self = NULL;

// /////////////////////////////////////////////////////////////////
// dtkVrMaster
// /////////////////////////////////////////////////////////////////

dtkVrMaster::dtkVrMaster(dtkDistributedCommunicator *communicator) : dtkVrProcess(communicator), d(new dtkVrMasterPrivate)
{
    d->q = this;
    d->self = d;
 
    d->tracker = NULL;
    d->device = NULL;
}


dtkVrMaster::~dtkVrMaster(void)
{
    delete d;
    
    d = NULL;
}

void dtkVrMaster::initialize(void)
{
    if (d->tracker)
        d->tracker->startConnection(d->trackerUrl);

    if (d->device)
        d->device->startConnection(d->deviceUrl);
}

void dtkVrMaster::uninitialize(void)
{
    if (d->tracker)
        d->tracker->stopConnection();

    if (d->device)
        d->device->stopConnection();
}

void dtkVrMaster::setTracker(const QUrl& url)
{
    d->tracker = new dtkVrTrackerVrpn;
    d->tracker->registerPositionHandler1(dtkVrMasterPrivate::positionHandler1);
    d->tracker->registerPositionHandler2(dtkVrMasterPrivate::positionHandler2);
    d->tracker->registerOrientationHandler1(dtkVrMasterPrivate::orientationHandler1);
    d->tracker->registerOrientationHandler2(dtkVrMasterPrivate::orientationHandler2);
    
    connect(d->tracker, SIGNAL(buttonPressed(int)), this, SLOT(onButtonPressed(int)));
    connect(d->tracker, SIGNAL(buttonReleased(int)), this, SLOT(onButtonReleased(int)));

    d->trackerUrl = url;
}

void dtkVrMaster::setDevice(const QUrl& url)
{
    d->device = new dtkVrDeviceVrpn;
    d->device->registerPositionHandler(dtkVrMasterPrivate::positionHandler2);
    d->device->registerOrientationHandler(dtkVrMasterPrivate::orientationHandler2);
    
    connect(d->device, SIGNAL(buttonPressed(int)), this, SLOT(onButtonPressed(int)));
    connect(d->device, SIGNAL(buttonReleased(int)), this, SLOT(onButtonReleased(int)));

    d->deviceUrl = url;
}

void dtkVrMaster::onButtonPressed(int button)
{
    if(d->tracker) switch(button) {
    case dtkVrTrackerVrpn::dtkVrTrackerVrpnButton0:
        // this->wand()->setAction(dtkVrWand::dtkVrWandPicking);
        // this->wand()->setReferencePosition(this->wand()->currentPosition());
        // this->wand()->setReferenceOrientation(this->wand()->currentOrientation());
        break;
    };
}

void dtkVrMaster::onButtonReleased(int button)
{
    if(d->tracker) switch(button) {
    case dtkVrTrackerVrpn::dtkVrTrackerVrpnButton0:
        // this->wand()->setAction(dtkVrWand::dtkVrWandNone);
        break;
    case dtkVrTrackerVrpn::dtkVrTrackerVrpnButton3:
        // this->wand()->setMode(dtkVrWand::dtkVrWandInteraction);
        break;
    case dtkVrTrackerVrpn::dtkVrTrackerVrpnButton4:
        // this->wand()->setMode(dtkVrWand::dtkVrWandNavigation);
        break;
    default: break;
    }

    if(d->device) switch(button) {
    case dtkVrDeviceVrpn::dtkVrDeviceVrpnButton1:
        // this->wand()->setMode(dtkVrWand::dtkVrWandInteraction);
        break;
    case dtkVrDeviceVrpn::dtkVrDeviceVrpnButton0:
        // this->wand()->setMode(dtkVrWand::dtkVrWandNavigation);
        break;
    default: break;
    }
}

void dtkVrMaster::process(void)
{
    qApp->processEvents(QEventLoop::AllEvents, 10);
}

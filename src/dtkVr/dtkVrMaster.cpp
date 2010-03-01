/* dtkVrMaster.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 10:03:10 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 24 19:21:10 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 143
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrMaster.h"
#include "dtkVrTrackerVrpn.h"
#include "dtkVrUser.h"
#include "dtkVrWand.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkVec3.h>
#include <dtkCore/dtkQuat.h>

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkVrMasterPrivate
// /////////////////////////////////////////////////////////////////

class dtkVrMasterPrivate
{
public:
    dtkVrTrackerVrpn *tracker;

    static void positionHandler1(float x, float y, float z);
    static void positionHandler2(float x, float y, float z);

    static void orientationHandler1(float q0, float q1, float q2, float q3);
    static void orientationHandler2(float q0, float q1, float q2, float q3);

    static dtkVrMasterPrivate *self;

    dtkVrMaster *q;
};

void dtkVrMasterPrivate::positionHandler1(float x, float y, float z)
{
    self->q->user()->setPosition(dtkVec3(x, y, z));
}

void dtkVrMasterPrivate::positionHandler2(float x, float y, float z)
{
    self->q->wand()->setCurrentPosition(dtkVec3(x, y, z));
}

void dtkVrMasterPrivate::orientationHandler1(float q0, float q1, float q2, float q3)
{
    self->q->user()->setOrientation(dtkQuat(q0, q1, q2, q3));
}

void dtkVrMasterPrivate::orientationHandler2(float q0, float q1, float q2, float q3)
{
    self->q->wand()->setCurrentOrientation(dtkQuat(q0, q1, q2, q3));
}

dtkVrMasterPrivate *dtkVrMasterPrivate::self = NULL;

// /////////////////////////////////////////////////////////////////
// dtkVrMaster
// /////////////////////////////////////////////////////////////////

dtkVrMaster::dtkVrMaster(dtkDistributedCommunicator *communicator) : dtkVrProcess(communicator), d(new dtkVrMasterPrivate)
{
    d->q = this;
    d->self = d;
 
    d->tracker = new dtkVrTrackerVrpn;
    d->tracker->registerPositionHandler1(dtkVrMasterPrivate::positionHandler1);
    d->tracker->registerPositionHandler2(dtkVrMasterPrivate::positionHandler2);
    d->tracker->registerOrientationHandler1(dtkVrMasterPrivate::orientationHandler1);
    d->tracker->registerOrientationHandler2(dtkVrMasterPrivate::orientationHandler2);

    connect(d->tracker, SIGNAL(buttonPressed(int)), this, SLOT(onButtonPressed(int)));
    connect(d->tracker, SIGNAL(buttonReleased(int)), this, SLOT(onButtonReleased(int)));
}

dtkVrMaster::~dtkVrMaster(void)
{
    delete d;
    
    d = NULL;
}

void dtkVrMaster::initialize(void)
{
    QUrl url;

    for(int i = 0; i < qApp->arguments().count(); i++)
        if(qApp->arguments().at(i) == "--tracker")
            url = QUrl(qApp->arguments().at(i+1));

    if(url.isValid())
        d->tracker->startConnection(url);
}

void dtkVrMaster::uninitialize(void)
{
    d->tracker->stopConnection();
}

void dtkVrMaster::onButtonPressed(int button)
{
    switch(button) {
    case dtkVrTrackerVrpn::dtkVrTrackerVrpnButton0:
        this->wand()->setAction(dtkVrWand::dtkVrWandPicking);
        this->wand()->setReferencePosition(this->wand()->currentPosition());
        this->wand()->setReferenceOrientation(this->wand()->currentOrientation());
        break;
    };    
}

void dtkVrMaster::onButtonReleased(int button)
{
    switch(button) {
    case dtkVrTrackerVrpn::dtkVrTrackerVrpnButton0:
        this->wand()->setAction(dtkVrWand::dtkVrWandNone);
        break;
    case dtkVrTrackerVrpn::dtkVrTrackerVrpnButton4:
        this->wand()->setMode(dtkVrWand::dtkVrWandInteraction);
        break;
    case dtkVrTrackerVrpn::dtkVrTrackerVrpnButton3:
        this->wand()->setMode(dtkVrWand::dtkVrWandNavigation);
        break;
    default: break;
    }
}

void dtkVrMaster::process(void)
{

}

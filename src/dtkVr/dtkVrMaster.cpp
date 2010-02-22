/* dtkVrMaster.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 10:03:10 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 22 09:44:04 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 83
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
    self->q->wand()->setPosition(dtkVec3(x, y, z));
}

void dtkVrMasterPrivate::orientationHandler1(float q0, float q1, float q2, float q3)
{
    self->q->user()->setOrientation(dtkQuat(q0, q1, q2, q3));
}

void dtkVrMasterPrivate::orientationHandler2(float q0, float q1, float q2, float q3)
{
    self->q->wand()->setOrientation(dtkQuat(q0, q1, q2, q3));
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

void dtkVrMaster::process(void)
{

}

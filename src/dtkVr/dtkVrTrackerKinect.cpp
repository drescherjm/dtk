/* dtkVrTrackerKinect.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 25 16:59:15 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 25 17:35:11 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrTrackerKinect.h"
#include "dtkVrTrackerKinect_p.h"

dtkVrTrackerKinect::dtkVrTrackerKinect(void) : dtkVrTracker(), d(new dtkVrTrackerKinectPrivate)
{

}

dtkVrTrackerKinect::~dtkVrTrackerKinect(void)
{
    delete d;
    
    d = NULL;
}

void dtkVrTrackerKinect::initialize(void)
{
    d->initialize();
}

void dtkVrTrackerKinect::uninitialize(void)
{
    d->uninitialize();
}

dtkVector3D<double> dtkVrTrackerKinect::headPosition(void)
{
    return d->position();
}

dtkVector3D<double> dtkVrTrackerKinect::handPosition(void)
{
    return d->hand();
}

dtkQuaternion<double> dtkVrTrackerKinect::headOrientation(void)
{
    return d->orientation();
}

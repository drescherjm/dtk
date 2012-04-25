/* dtkVrTracker.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 20:32:08 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr 25 16:57:30 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrTracker.h"

#include <dtkCore/dtkGlobal.h>

class dtkVrTrackerPrivate
{
public:
};

dtkVrTracker::dtkVrTracker(void) : QObject(), d(new dtkVrTrackerPrivate)
{

}

dtkVrTracker::~dtkVrTracker(void)
{
    delete d;

    d = NULL;
}

void dtkVrTracker::initialize(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkVrTracker::initialize(const QUrl& server)
{
    DTK_DEFAULT_IMPLEMENTATION;

    Q_UNUSED(server);
}

void dtkVrTracker::uninitialize(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

dtkVector3D<double> dtkVrTracker::headPosition(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return dtkVector3D<double>();
}

dtkVector3D<double> dtkVrTracker::handPosition(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return dtkVector3D<double>();
}

dtkQuaternion<double> dtkVrTracker::headOrientation(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return dtkQuaternion<double>();
}

/* dtkVrWand.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 21 18:28:53 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 24 19:30:11 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 45
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrWand.h"

#include <dtkCore/dtkVec3.h>
#include <dtkCore/dtkQuat.h>

class dtkVrWandPrivate
{
public:
    int action;
    int mode;

    dtkVec3 referencePosition;
    dtkQuat referenceOrientation;
    dtkVec3 currentPosition;
    dtkQuat currentOrientation;
};

dtkVrWand::dtkVrWand(void) : QObject(), d(new dtkVrWandPrivate)
{
    d->action = dtkVrWandNone;
    d->mode = dtkVrWandNavigation;
}

dtkVrWand::~dtkVrWand(void)
{
    delete d;

    d = NULL;
}

int& dtkVrWand::action(void)
{
    return d->action;
}

int& dtkVrWand::mode(void)
{
    return d->mode;
}

void dtkVrWand::setAction(Action action)
{
    d->action = action;
}

void dtkVrWand::setMode(Mode mode)
{
    d->mode = mode;
}

dtkVec3& dtkVrWand::referencePosition(void)
{
    return d->referencePosition;
}

dtkQuat& dtkVrWand::referenceOrientation(void)
{
    return d->referenceOrientation;
}

dtkVec3& dtkVrWand::currentPosition(void)
{
    return d->currentPosition;
}

dtkQuat& dtkVrWand::currentOrientation(void)
{
    return d->currentOrientation;
}

void dtkVrWand::setReferencePosition(const dtkVec3& position)
{
    d->referencePosition = position;
}

void dtkVrWand::setReferenceOrientation(const dtkQuat& orientation)
{
    d->referenceOrientation = orientation;
}

void dtkVrWand::setCurrentPosition(const dtkVec3& position)
{
    d->currentPosition = position;
}

void dtkVrWand::setCurrentOrientation(const dtkQuat& orientation)
{
    d->currentOrientation = orientation;
}

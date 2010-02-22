/* dtkVrWand.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 21 18:28:53 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 22 09:44:35 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 15
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
    dtkVec3 position;
    dtkQuat orientation;
};

dtkVrWand::dtkVrWand(void) : QObject(), d(new dtkVrWandPrivate)
{

}

dtkVrWand::~dtkVrWand(void)
{
    delete d;

    d = NULL;
}

dtkVec3& dtkVrWand::position(void)
{
    return d->position;
}

dtkQuat& dtkVrWand::orientation(void)
{
    return d->orientation;
}

void dtkVrWand::setPosition(const dtkVec3& position)
{
    d->position = position;
}

void dtkVrWand::setOrientation(const dtkQuat& orientation)
{
    d->orientation = orientation;
}

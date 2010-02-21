/* dtkVrUser.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 21 18:28:53 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb 21 18:34:49 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrUser.h"

#include <dtkCore/dtkVec3.h>
#include <dtkCore/dtkQuat.h>

class dtkVrUserPrivate
{
public:
    dtkVec3 position;
    dtkQuat orientation;
};

dtkVrUser::dtkVrUser(void) : QObject(), d(new dtkVrUserPrivate)
{

}

dtkVrUser::~dtkVrUser(void)
{
    delete d;

    d = NULL;
}

dtkVec3 dtkVrUser::position(void) const
{
    return d->position;
}

dtkQuat dtkVrUser::orientation(void) const
{
    return d->orientation;
}

void dtkVrUser::setPosition(const dtkVec3& position)
{
    d->position = position;
}

void dtkVrUser::setOrientation(const dtkQuat& orientation)
{
    d->orientation = orientation;
}

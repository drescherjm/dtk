/* dtkVrUser.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 21 18:28:53 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 22 09:47:39 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
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

dtkVec3& dtkVrUser::position(void)
{
    return d->position;
}

dtkQuat& dtkVrUser::orientation(void)
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

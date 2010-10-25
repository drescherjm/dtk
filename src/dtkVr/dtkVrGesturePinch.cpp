/* dtkVrGesturePinch.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Oct 23 17:39:12 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Sat Oct 23 17:44:52 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrGesturePinch.h"

class dtkVrGesturePinchPrivate
{
public:
    Qt::GestureState state;
};

dtkVrGesturePinch::dtkVrGesturePinch(QObject *parent) : QPinchGesture(parent), d(new dtkVrGesturePinchPrivate)
{
    
}

dtkVrGesturePinch::~dtkVrGesturePinch(void)
{
    delete d;

    d = NULL;
}

Qt::GestureState dtkVrGesturePinch::state(void) const
{
    return d->state;
}

void dtkVrGesturePinch::setState(Qt::GestureState state)
{
    d->state = state;
}

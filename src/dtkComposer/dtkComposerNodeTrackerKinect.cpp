/* dtkComposerNodeTrackerKinect.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 26 10:27:53 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 10:36:44 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeTrackerKinect.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath/dtkVector3D.h>
#include <dtkMath/dtkQuaternion.h>

class dtkComposerNodeTrackerKinectPrivate
{
public:
    // dtkComposerTransmitterEmitter<dtkVector3D<double> > *head_position;
    // dtkComposerTransmitterEmitter<dtkQuaternion<double> > *head_orientation;
};

dtkComposerNodeTrackerKinect::dtkComposerNodeTrackerKinect(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeTrackerKinectPrivate)
{
    // d->head_position = new dtkComposerTransmitterEmitter<dtkVector3D<double> >(this);
    // d->head_orientation = new dtkComposerTransmitterEmitter<dtkQuaternion<double> >(this);

    // this->appendEmitter(d->head_position);
    // this->appendEmitter(d->head_orientation);
}

dtkComposerNodeTrackerKinect::~dtkComposerNodeTrackerKinect(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeTrackerKinect::run(void)
{
    
}

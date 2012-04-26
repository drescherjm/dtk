/* dtkComposerNodeTrackerKinect.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 26 10:27:53 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 11:05:41 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 35
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

#include <dtkVr/dtkVrTrackerKinect.h>

class dtkComposerNodeTrackerKinectPrivate
{
public:
    // dtkComposerTransmitterEmitter<dtkVector3D<double> > *head_position;
    // dtkComposerTransmitterEmitter<dtkQuaternion<double> > *head_orientation;

public:
    dtkVrTrackerKinect *tracker;
};

dtkComposerNodeTrackerKinect::dtkComposerNodeTrackerKinect(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeTrackerKinectPrivate)
{
    // d->head_position = new dtkComposerTransmitterEmitter<dtkVector3D<double> >(this);
    // d->head_orientation = new dtkComposerTransmitterEmitter<dtkQuaternion<double> >(this);

    // this->appendEmitter(d->head_position);
    // this->appendEmitter(d->head_orientation);

    d->tracker = NULL;
}

dtkComposerNodeTrackerKinect::~dtkComposerNodeTrackerKinect(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeTrackerKinect::run(void)
{
    if(!d->tracker) {
        d->tracker = new dtkVrTrackerKinect;
        d->tracker->initialize();
    }
}

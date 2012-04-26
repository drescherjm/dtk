/* dtkComposerNodeTrackerKinect.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 26 10:27:53 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 15:23:13 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 51
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeTrackerKinect.h"
#include "dtkComposerNodeVector3D.h"
#include "dtkComposerNodeQuaternion.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath/dtkVector3D.h>
#include <dtkMath/dtkQuaternion.h>

#include <dtkVr/dtkVrTrackerKinect.h>

class dtkComposerNodeTrackerKinectPrivate
{
public:
    dtkComposerTransmitterEmitter<dtkVector3DReal> head_position;
    dtkComposerTransmitterEmitter<dtkQuaternionReal> head_orientation;

public:
    dtkVrTrackerKinect *tracker;
};

dtkComposerNodeTrackerKinect::dtkComposerNodeTrackerKinect(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeTrackerKinectPrivate)
{
    this->appendEmitter(&(d->head_position));
    this->appendEmitter(&(d->head_orientation));

    d->tracker = NULL;
}

dtkComposerNodeTrackerKinect::~dtkComposerNodeTrackerKinect(void)
{
    d->tracker->uninitialize();

    delete d->tracker;
    delete d;

    d = NULL;
}

void dtkComposerNodeTrackerKinect::run(void)
{
    if(!d->tracker) {
        d->tracker = new dtkVrTrackerKinect;
        d->tracker->initialize();
    }

    d->head_position.setData(d->tracker->headPosition());
    d->head_orientation.setData(d->tracker->headOrientation());
}

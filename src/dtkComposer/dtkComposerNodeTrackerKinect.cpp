/* dtkComposerNodeTrackerKinect.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 26 10:27:53 2012 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. mars 21 11:21:21 2013 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 67
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
    dtkVector3DReal position;
    dtkQuaternionReal orientation;

public:
    dtkVrTrackerKinect *tracker;
};

dtkComposerNodeTrackerKinect::dtkComposerNodeTrackerKinect(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeTrackerKinectPrivate)
{
    this->appendEmitter(&(d->head_position));
    this->appendEmitter(&(d->head_orientation));

    d->head_position.setData(&d->position);
    d->head_orientation.setData(&d->orientation);

    d->tracker = NULL;
}

dtkComposerNodeTrackerKinect::~dtkComposerNodeTrackerKinect(void)
{
    if (d->tracker) {
        d->tracker->uninitialize();
        delete d->tracker;
    }
    d->tracker = NULL;

    delete d;

    d = NULL;
}

void dtkComposerNodeTrackerKinect::run(void)
{
    if(!d->tracker) {
        d->tracker = new dtkVrTrackerKinect;
        d->tracker->initialize();
    }

    d->position = d->tracker->headPosition();
    d->orientation = d->tracker->headOrientation();
}

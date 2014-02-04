/* dtkComposerNodeTrackerVrpn.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 26 16:51:45 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Nov 22 10:18:39 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeTrackerVrpn.h"
#include "dtkComposerNodeVector3D.h"
#include "dtkComposerNodeQuaternion.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMathSupport/dtkVector3D.h>
#include <dtkMathSupport/dtkQuaternion.h>

#include <dtkVr/dtkVrTrackerVrpn.h>

class dtkComposerNodeTrackerVrpnPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> url;

    dtkComposerTransmitterEmitter<dtkVector3DReal> head_position;
    dtkComposerTransmitterEmitter<dtkQuaternionReal> head_orientation;

public:
    dtkVector3DReal *position;
    dtkQuaternionReal *orientation;

public:
    dtkVrTrackerVrpn *tracker;
};

dtkComposerNodeTrackerVrpn::dtkComposerNodeTrackerVrpn(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeTrackerVrpnPrivate)
{
    this->appendReceiver(&(d->url));
    this->appendEmitter(&(d->head_position));
    this->appendEmitter(&(d->head_orientation));

    d->position = new dtkVector3DReal;
    d->orientation = new dtkQuaternionReal;

    d->tracker = NULL;
}

dtkComposerNodeTrackerVrpn::~dtkComposerNodeTrackerVrpn(void)
{
    if (d->tracker) {
        d->tracker->uninitialize();
        delete d->tracker;
    }

    d->tracker = NULL;

    delete d->position;
    delete d->orientation;
    delete d;

    d = NULL;
}

void dtkComposerNodeTrackerVrpn::run(void)
{
    if(!d->tracker && !d->url.isEmpty()) {
        d->tracker = new dtkVrTrackerVrpn;
        d->tracker->setUrl(QUrl(*d->url.data()));
        d->tracker->initialize();
    }

    if(!d->tracker)
        return;

    *(d->position) = d->tracker->headPosition();
    *(d->orientation) = d->tracker->headOrientation();

    d->head_position.setData(d->position);
    d->head_orientation.setData(d->orientation);
}

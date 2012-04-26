/* dtkComposerNodeTrackerVrpn.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 26 16:51:45 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 17:58:33 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 12
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

#include <dtkMath/dtkVector3D.h>
#include <dtkMath/dtkQuaternion.h>

#include <dtkVr/dtkVrTrackerVrpn.h>

class dtkComposerNodeTrackerVrpnPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> url;

    dtkComposerTransmitterEmitter<dtkVector3DReal> head_position;
    dtkComposerTransmitterEmitter<dtkQuaternionReal> head_orientation;

public:
    dtkVrTrackerVrpn *tracker;
};

dtkComposerNodeTrackerVrpn::dtkComposerNodeTrackerVrpn(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeTrackerVrpnPrivate)
{
    this->appendReceiver(&(d->url));
    this->appendEmitter(&(d->head_position));
    this->appendEmitter(&(d->head_orientation));

    d->tracker = NULL;
}

dtkComposerNodeTrackerVrpn::~dtkComposerNodeTrackerVrpn(void)
{
    d->tracker->uninitialize();

    delete d->tracker;
    delete d;

    d = NULL;
}

void dtkComposerNodeTrackerVrpn::run(void)
{
    if(!d->tracker && !d->url.isEmpty()) {
        d->tracker = new dtkVrTrackerVrpn;
        d->tracker->setUrl(QUrl(d->url.data()));
        d->tracker->initialize();
    }

    if(!d->tracker)
        return;

    d->head_position.setData(d->tracker->headPosition());
    d->head_orientation.setData(d->tracker->headOrientation());
}

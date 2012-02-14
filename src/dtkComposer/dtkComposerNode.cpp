/* dtkComposerNode.cpp --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 14:25:11 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 14 16:49:35 2012 (+0100)
 *           By: David Rey
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePrivate
{
public:
    QList<dtkComposerTransmitter *> emitters;
    QList<dtkComposerTransmitter *> receivers;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNode implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNode::dtkComposerNode(void) : d(new dtkComposerNodePrivate)
{

}

dtkComposerNode::~dtkComposerNode(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNode::appendEmitter(dtkComposerTransmitter *emitter)
{
    if (!d->emitters.contains(emitter))
        d->emitters << emitter;
}

void dtkComposerNode::removeEmitter(dtkComposerTransmitter *emitter)
{
    if (d->emitters.contains(emitter))
        d->emitters.removeOne(emitter);
}

void dtkComposerNode::appendReceiver(dtkComposerTransmitter *receiver)
{ 
    if (!d->receivers.contains(receiver))
        d->receivers << receiver;
}

void dtkComposerNode::removeReceiver(dtkComposerTransmitter *receiver)
{
    if (d->receivers.contains(receiver))
        d->receivers.removeOne(receiver);
}

QList<dtkComposerTransmitter *> dtkComposerNode::emitters(void)
{
    return d->emitters;
}

QList<dtkComposerTransmitter *> dtkComposerNode::receivers(void)
{
    return d->receivers;
}

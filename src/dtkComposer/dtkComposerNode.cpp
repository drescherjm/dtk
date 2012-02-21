/* dtkComposerNode.cpp --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 14:25:11 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 21 15:17:30 2012 (+0100)
 *           By: tkloczko
 *     Update #: 47
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

public:
    QString title_hint;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNode implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNode::dtkComposerNode(void) : d(new dtkComposerNodePrivate)
{
    d->title_hint = "Node";
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
    d->emitters.removeOne(emitter);
}

dtkComposerTransmitter *dtkComposerNode::removeEmitter(int index)
{
    return d->emitters.takeAt(index);
}

void dtkComposerNode::appendReceiver(dtkComposerTransmitter *receiver)
{ 
    if (!d->receivers.contains(receiver))
        d->receivers << receiver;
}

void dtkComposerNode::removeReceiver(dtkComposerTransmitter *receiver)
{
    d->receivers.removeOne(receiver);
}

dtkComposerTransmitter *dtkComposerNode::removeReceiver(int index)
{
    return d->receivers.takeAt(index);
}

QList<dtkComposerTransmitter *> dtkComposerNode::emitters(void)
{
    return d->emitters;
}

QList<dtkComposerTransmitter *> dtkComposerNode::receivers(void)
{
    return d->receivers;
}

QString dtkComposerNode::titleHint(void)
{
    return d->title_hint;
}

QString dtkComposerNode::labelHint(int port)
{
    return "port";
}

void dtkComposerNode::setTitleHint(const QString& hint)
{
    d->title_hint = hint;
}

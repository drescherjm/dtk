/* dtkComposerNode.cpp --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 14:25:11 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 16 18:57:49 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 45
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

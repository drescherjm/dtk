/* dtkComposerNode.cpp --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 14:25:11 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jun 27 16:12:12 2012 (+0200)
 *           By: tkloczko
 *     Update #: 73
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerTransmitter.h"

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
    QString title;

public:
    QHash<int, QString>  input_label_hint;
    QHash<int, QString> output_label_hint;
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
    if (!d->emitters.contains(emitter)) {
        d->emitters << emitter;
        emitter->setParentNode(this);
    }
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
    if (!d->receivers.contains(receiver)) {
        d->receivers << receiver;
        receiver->setParentNode(this);
    }
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

QString dtkComposerNode::title(void) const
{
    return d->title;
}

QString dtkComposerNode::titleHint(void)
{
    return d->title_hint;
}

QString dtkComposerNode::inputLabelHint(int port)
{
    if(d->input_label_hint.contains(port))
        return d->input_label_hint[port];

    return "port";
}

QString dtkComposerNode::outputLabelHint(int port)
{
    if(d->output_label_hint.contains(port))
        return d->output_label_hint[port];

    return "port";
}

void dtkComposerNode::setTitle(const QString& title)
{
    d->title = title;
}

void dtkComposerNode::setTitleHint(const QString& hint)
{
    d->title_hint = hint;
}

void dtkComposerNode::setInputLabelHint(const QString& hint, int port)
{
    d->input_label_hint[port] = hint;
}

void dtkComposerNode::setOutputLabelHint(const QString& hint, int port)
{
    d->output_label_hint[port] = hint;
}

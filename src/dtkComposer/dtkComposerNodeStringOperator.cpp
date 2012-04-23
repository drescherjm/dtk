/* @(#)dtkComposerNodeStringOperator.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/23 09:24:08
 * Version: $Id$
 * Last-Updated: lun. avril 23 11:28:43 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 6
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerNodeStringOperator.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkLog/dtkLog.h>


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterVariant *receiver;

public:
    dtkComposerTransmitterVariant *emitter;
};

dtkComposerNodeStringOperatorUnary::dtkComposerNodeStringOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorUnaryPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::String;

    d->receiver = new dtkComposerTransmitterVariant(this);
    d->receiver->setTypes(variant_list);
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerTransmitterVariant(this);
    d->emitter->setTypes(variant_list);
    this->appendEmitter(d->emitter);
}

dtkComposerNodeStringOperatorUnary::~dtkComposerNodeStringOperatorUnary(void)
{
    delete d->receiver;
    delete d->emitter;
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterVariant *receiver_lhs;
    dtkComposerTransmitterVariant *receiver_rhs;

public:
    dtkComposerTransmitterVariant *emitter;
};

dtkComposerNodeStringOperatorBinary::dtkComposerNodeStringOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorBinaryPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::String;

    d->receiver_lhs = new dtkComposerTransmitterVariant(this);
    d->receiver_lhs->setTypes(variant_list);
    this->appendReceiver(d->receiver_lhs);

    d->receiver_rhs = new dtkComposerTransmitterVariant(this);
    d->receiver_rhs->setTypes(variant_list);
    this->appendReceiver(d->receiver_rhs);

    d->emitter = new dtkComposerTransmitterVariant(this);
    d->emitter->setTypes(variant_list);
    this->appendEmitter(d->emitter);
}

dtkComposerNodeStringOperatorBinary::~dtkComposerNodeStringOperatorBinary(void)
{
    delete d->receiver_lhs;
    delete d->receiver_rhs;
    delete d->emitter;
    delete d;

    d = NULL;
}


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinary - Append
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeStringOperatorBinaryAppend::run(void)
{
    QString a = d->receiver_lhs->data().toString();
    QString b = d->receiver_rhs->data().toString();
    d->emitter->setData(a + b);
}



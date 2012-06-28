/* @(#)dtkComposerNodeStringOperator.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/23 09:24:08
 * Version: $Id$
 * Last-Updated: Tue Jun 26 17:31:25 2012 (+0200)
 *           By: tkloczko
 *     Update #: 19
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
    dtkComposerTransmitterVariant receiver;

public:
    dtkComposerTransmitterEmitter<QString> emitter;
};

dtkComposerNodeStringOperatorUnary::dtkComposerNodeStringOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorUnaryPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::String;

    d->receiver.setTypes(variant_list);
    this->appendReceiver(&(d->receiver));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeStringOperatorUnary::~dtkComposerNodeStringOperatorUnary(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterVariant receiver_lhs;
    dtkComposerTransmitterVariant receiver_rhs;

public:
    dtkComposerTransmitterEmitter<QString> emitter;
};

dtkComposerNodeStringOperatorBinary::dtkComposerNodeStringOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorBinaryPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::String;

    d->receiver_lhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeStringOperatorBinary::~dtkComposerNodeStringOperatorBinary(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinaryLogic
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorBinaryLogicPrivate
{
public:
    dtkComposerTransmitterVariant receiver_lhs;
    dtkComposerTransmitterVariant receiver_rhs;

public:
    dtkComposerTransmitterEmitter<bool> emitter;
};

dtkComposerNodeStringOperatorBinaryLogic::dtkComposerNodeStringOperatorBinaryLogic(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorBinaryLogicPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::String;

    d->receiver_lhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeStringOperatorBinaryLogic::~dtkComposerNodeStringOperatorBinaryLogic(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinary - Append
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeStringOperatorBinaryAppend::run(void)
{
    QString a = d->receiver_lhs.data().toString();
    QString b = d->receiver_rhs.data().toString();
    d->emitter.setData(a + b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinaryLogic - Equality
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeStringOperatorBinaryLogicEquality::run(void)
{
    QString a = d->receiver_lhs.data().toString();
    QString b = d->receiver_rhs.data().toString();
    d->emitter.setData((a == b));
}



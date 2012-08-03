/* @(#)dtkComposerNodeStringOperator.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/23 09:24:08
 * Version: $Id$
 * Last-Updated: Sat Aug  4 00:36:10 2012 (+0200)
 *           By: tkloczko
 *     Update #: 37
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerMetatype.h"

#include "dtkComposerNodeStringOperator.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterUtils.h"
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

public:
    QString value;
};

dtkComposerNodeStringOperatorUnary::dtkComposerNodeStringOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorUnaryPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Bool << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double << QVariant::String << QVariant::ByteArray;

    d->receiver.setTypes(variant_list);
    this->appendReceiver(&(d->receiver));

    d->emitter.setData(&d->value);
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

public:
    QString value;
};

dtkComposerNodeStringOperatorBinary::dtkComposerNodeStringOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorBinaryPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Bool << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double << QVariant::String << QVariant::ByteArray;

    d->receiver_lhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->emitter.setData(&d->value);
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

public:
    bool value;
};

dtkComposerNodeStringOperatorBinaryLogic::dtkComposerNodeStringOperatorBinaryLogic(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorBinaryLogicPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Bool << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double << QVariant::String << QVariant::ByteArray;

    d->receiver_lhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->emitter.setData(&d->value);
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
    QString a = *dtkComposerTransmitterData<QString>(d->receiver_lhs);
    QString b = *dtkComposerTransmitterData<QString>(d->receiver_rhs);

    d->value = (a + b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinaryLogic - Equality
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeStringOperatorBinaryLogicEquality::run(void)
{
    QString a = *dtkComposerTransmitterData<QString>(d->receiver_lhs);
    QString b = *dtkComposerTransmitterData<QString>(d->receiver_rhs);

    d->value = (a == b);
}



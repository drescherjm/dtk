/* @(#)dtkComposerNodeStringOperator.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/23 09:24:08
 * Version: $Id$
 * Last-Updated: Tue Aug  7 17:04:36 2012 (+0200)
 *           By: tkloczko
 *     Update #: 46
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
    dtkComposerTransmitterReceiver<QString> receiver;

public:
    dtkComposerTransmitterEmitter<QString> emitter;

public:
    QString value;
};

dtkComposerNodeStringOperatorUnary::dtkComposerNodeStringOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorUnaryPrivate)
{
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
    dtkComposerTransmitterReceiver<QString> receiver_lhs;
    dtkComposerTransmitterReceiver<QString> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<QString> emitter;

public:
    QString value;
};

dtkComposerNodeStringOperatorBinary::dtkComposerNodeStringOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorBinaryPrivate)
{
    this->appendReceiver(&(d->receiver_lhs));
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
    dtkComposerTransmitterReceiver<QString> receiver_lhs;
    dtkComposerTransmitterReceiver<QString> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<bool> emitter;

public:
    bool value;
};

dtkComposerNodeStringOperatorBinaryLogic::dtkComposerNodeStringOperatorBinaryLogic(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorBinaryLogicPrivate)
{
    this->appendReceiver(&(d->receiver_lhs));
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
    d->value = *(d->receiver_lhs.data()) + *(d->receiver_rhs.data());
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinaryLogic - Equality
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeStringOperatorBinaryLogicEquality::run(void)
{
    d->value = (*(d->receiver_lhs.data()) == *(d->receiver_rhs.data()));
}



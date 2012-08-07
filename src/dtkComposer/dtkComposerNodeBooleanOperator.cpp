/* dtkComposerNodeBooleanOperator.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:52:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Aug  7 17:08:15 2012 (+0200)
 *           By: tkloczko
 *     Update #: 149
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerMetatype.h"

#include "dtkComposerNodeBooleanOperator.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterUtils.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<bool> receiver;

public:    
    dtkComposerTransmitterEmitter<bool> emitter;

public:
    bool value;
};

dtkComposerNodeBooleanOperatorUnary::dtkComposerNodeBooleanOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanOperatorUnaryPrivate)
{
    this->appendReceiver(&(d->receiver));

    d->value = false;
    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeBooleanOperatorUnary::~dtkComposerNodeBooleanOperatorUnary(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterReceiver<bool> receiver_lhs;
    dtkComposerTransmitterReceiver<bool> receiver_rhs;

public:    
    dtkComposerTransmitterEmitter<bool> emitter;

public:
    bool value;
};

dtkComposerNodeBooleanOperatorBinary::dtkComposerNodeBooleanOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanOperatorBinaryPrivate)
{
    this->appendReceiver(&(d->receiver_lhs));
    this->appendReceiver(&(d->receiver_rhs));

    d->value = false;
    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeBooleanOperatorBinary::~dtkComposerNodeBooleanOperatorBinary(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// Unary boolean operator - NOT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorUnaryNot::run(void)
{
    d->value = !(*d->receiver.data());
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - AND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryAnd::run(void)
{
    bool a = *d->receiver_lhs.data();
    bool b = *d->receiver_rhs.data();

    d->value = (a && b);
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - OR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryOr::run(void)
{
    bool a = *d->receiver_lhs.data();
    bool b = *d->receiver_rhs.data();

    d->value = (a || b);
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - XOR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryXor::run(void)
{
    bool a = *d->receiver_lhs.data();
    bool b = *d->receiver_rhs.data();

    d->value = ((a && !b) || (!a && b));
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - NAND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryNand::run(void)
{
    bool a = *d->receiver_lhs.data();
    bool b = *d->receiver_rhs.data();

    d->value = !(a && b);
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - NOR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryNor::run(void)
{
    bool a = *d->receiver_lhs.data();
    bool b = *d->receiver_rhs.data();

    d->value = !(a || b);
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - XNOR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryXnor::run(void)
{
    bool a = *d->receiver_lhs.data();
    bool b = *d->receiver_rhs.data();

    d->value = ((a && b) || (!a && !b));
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - IMP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryImp::run(void)
{
    bool a = *d->receiver_lhs.data();
    bool b = *d->receiver_rhs.data();

    d->value = (!a || b);
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - NIMP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryNimp::run(void)
{
    bool a = *d->receiver_lhs.data();
    bool b = *d->receiver_rhs.data();

    d->value = (a && !b);
}

/* dtkComposerNodeBooleanOperator.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:52:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 29 10:17:44 2012 (+0100)
 *           By: tkloczko
 *     Update #: 110
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeBooleanOperator.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<bool> *receiver;

public:    
    dtkComposerTransmitterEmitter<bool> *emitter;
};

dtkComposerNodeBooleanOperatorUnary::dtkComposerNodeBooleanOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanOperatorUnaryPrivate)
{
    d->receiver = new dtkComposerTransmitterReceiver<bool>;
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerTransmitterEmitter<bool>;
    this->appendEmitter(d->emitter);
}

dtkComposerNodeBooleanOperatorUnary::~dtkComposerNodeBooleanOperatorUnary(void)
{
    delete d->receiver;
    delete d->emitter;
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterReceiver<bool> *receiver_lhs;
    dtkComposerTransmitterReceiver<bool> *receiver_rhs;

public:    
    dtkComposerTransmitterEmitter<bool> *emitter;
};

dtkComposerNodeBooleanOperatorBinary::dtkComposerNodeBooleanOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanOperatorBinaryPrivate)
{
    d->receiver_lhs = new dtkComposerTransmitterReceiver<bool>;
    this->appendReceiver(d->receiver_lhs);

    d->receiver_rhs = new dtkComposerTransmitterReceiver<bool>;
    this->appendReceiver(d->receiver_rhs);

    d->emitter = new dtkComposerTransmitterEmitter<bool>;
    this->appendEmitter(d->emitter);
}

dtkComposerNodeBooleanOperatorBinary::~dtkComposerNodeBooleanOperatorBinary(void)
{
    delete d->receiver_lhs;
    delete d->receiver_rhs;
    delete d->emitter;
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// Unary boolean operator - NOT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorUnaryNot::run(void)
{
    bool a = d->receiver->data();

    d->emitter->setData(!a);
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - AND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryAnd::run(void)
{
    bool a = d->receiver_lhs->data();
    bool b = d->receiver_rhs->data();

    d->emitter->setData(a && b);
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - OR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryOr::run(void)
{
    bool a = d->receiver_lhs->data();
    bool b = d->receiver_rhs->data();

    d->emitter->setData(a || b);
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - XOR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryXor::run(void)
{
    bool a = d->receiver_lhs->data();
    bool b = d->receiver_rhs->data();

    d->emitter->setData((a && !b) || (!a && b));
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - NAND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryNand::run(void)
{
    bool a = d->receiver_lhs->data();
    bool b = d->receiver_rhs->data();

    d->emitter->setData(!(a && b));
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - NOR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryNor::run(void)
{
    bool a = d->receiver_lhs->data();
    bool b = d->receiver_rhs->data();

    d->emitter->setData(!(a || b));
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - XNOR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryXnor::run(void)
{
    bool a = d->receiver_lhs->data();
    bool b = d->receiver_rhs->data();

    d->emitter->setData((a && b) || (!a && !b));
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - IMP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryImp::run(void)
{
    bool a = d->receiver_lhs->data();
    bool b = d->receiver_rhs->data();

    d->emitter->setData((!a || b));
}

// /////////////////////////////////////////////////////////////////
// Binary boolean operator - NIMP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeBooleanOperatorBinaryNimp::run(void)
{
    bool a = d->receiver_lhs->data();
    bool b = d->receiver_rhs->data();

    d->emitter->setData((a && !b));
}

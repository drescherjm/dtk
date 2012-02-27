/* dtkComposerNodeBooleanOperator.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:52:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 15:37:25 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 74
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeBooleanOperator.h"
#include "dtkComposerEmitter.h"
#include "dtkComposerReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorUnaryPrivate
{
public:
    dtkComposerReceiver<bool> *receiver;

public:    
    dtkComposerEmitter<bool> *emitter;
};

dtkComposerNodeBooleanOperatorUnary::dtkComposerNodeBooleanOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanOperatorUnaryPrivate)
{
    d->receiver = new dtkComposerReceiver<bool>;
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerEmitter<bool>;
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
    dtkComposerReceiver<bool> *receiver_lhs;
    dtkComposerReceiver<bool> *receiver_rhs;

public:    
    dtkComposerEmitter<bool> *emitter;
};

dtkComposerNodeBooleanOperatorBinary::dtkComposerNodeBooleanOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanOperatorBinaryPrivate)
{
    d->receiver_lhs = new dtkComposerReceiver<bool>;
    this->appendReceiver(d->receiver_lhs);

    d->receiver_rhs = new dtkComposerReceiver<bool>;
    this->appendReceiver(d->receiver_rhs);

    d->emitter = new dtkComposerEmitter<bool>;
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
// 
// /////////////////////////////////////////////////////////////////

// bool dtkComposerNodeBooleanOperatorPrivate::evaluate(void)
// {
//     bool a = receiver_lhs->data();
//     bool b = receiver_rhs->data();

//     bool value = false;

//     switch(operation) {
//     case And:
//         value = a && b;
//         break;
//     case Or:
//         value = a || b;
//         break;
//     case Xor:
//         value = (a && !b) || (!a && b);
//         break;
//     case Nand:
//         value = !(a && b);
//         break;
//     case Nor:
//         value = !(a || b);
//         break;
//     case Xnor:
//         value = ((a && b) || (!a && !b));
//         break;
//     case Imp:
//         value = (!a || b);
//         break;
//     case Nimp:
//         value = (a && !b);
//         break;
//     default:
//         break;
//     }

//     return value;
// }

// void dtkComposerNodeBooleanOperator::run(void)
// {
//     d->emitter->setData(d->evaluate());
// }

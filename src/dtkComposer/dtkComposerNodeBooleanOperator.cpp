/* dtkComposerNodeBooleanOperator.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:52:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 10:08:11 2012 (+0100)
 *           By: tkloczko
 *     Update #: 15
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
// dtkComposerNodeBooleanOperatorPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorPrivate
{
public:    
    enum Operation {
        And,
        Or,
        Xor,
        Nand,
        Nor,
        Xnor,
        Imp,
        Nimp        
    };

public:
    bool evaluate(void);

public:
    dtkComposerReceiver<bool> *receiver_lhs;
    dtkComposerReceiver<bool> *receiver_rhs;

public:    
    dtkComposerEmitter<bool> *emitter;

public:
    Operation operation;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperatorPrivate implementation
// /////////////////////////////////////////////////////////////////

bool dtkComposerNodeBooleanOperatorPrivate::evaluate(void)
{
    bool a = receiver_lhs->data();
    bool b = receiver_rhs->data();

    bool value = false;

    switch(operation) {
    case And:
        value = a && b;
        break;
    case Or:
        value = a || b;
        break;
    case Xor:
        value = (a && !b) || (!a && b);
        break;
    case Nand:
        value = !(a && b);
        break;
    case Nor:
        value = !(a || b);
        break;
    case Xnor:
        value = ((a && b) || (!a && !b));
        break;
    case Imp:
        value = (!a || b);
        break;
    case Nimp:
        value = (a && !b);
        break;
    default:
        break;
    }

    return value;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperator implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeBooleanOperator::dtkComposerNodeBooleanOperator(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanOperatorPrivate)
{
    d->receiver_lhs = new dtkComposerReceiver<bool>;
    this->appendReceiver(d->receiver_lhs);

    d->receiver_rhs = new dtkComposerReceiver<bool>;
    this->appendReceiver(d->receiver_rhs);

    d->emitter = new dtkComposerEmitter<bool>;
    this->appendEmitter(d->emitter);

    d->operation = dtkComposerNodeBooleanOperatorPrivate::And;
}

dtkComposerNodeBooleanOperator::~dtkComposerNodeBooleanOperator(void)
{
    delete d->receiver_lhs;
    delete d->receiver_rhs;
    delete d->emitter;
    delete d;
    
    d = NULL;
}

void dtkComposerNodeBooleanOperator::run(void)
{
    d->emitter->setData(d->evaluate());
}




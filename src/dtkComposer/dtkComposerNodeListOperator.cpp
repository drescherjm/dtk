/* dtkComposerNodeListOperator.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:52:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 29 10:14:20 2012 (+0100)
 *           By: tkloczko
 *     Update #: 117
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeListOperator.h"

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeListOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeListOperatorUnaryPrivate
{
// public:
//     dtkComposerReceiver<??> *receiver;

// public:    
//     dtkComposerEmitter<??> *emitter;
};

dtkComposerNodeListOperatorUnary::dtkComposerNodeListOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeListOperatorUnaryPrivate)
{
    // d->receiver = new dtkComposerReceiver<??>;
    // this->appendReceiver(d->receiver);

    // d->emitter = new dtkComposerEmitter<??>;
    // this->appendEmitter(d->emitter);
}

dtkComposerNodeListOperatorUnary::~dtkComposerNodeListOperatorUnary(void)
{
    // delete d->receiver;
    // delete d->emitter;
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeListOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeListOperatorBinaryPrivate
{
// public:
//     dtkComposerReceiver<??> *receiver_lhs;
//     dtkComposerReceiver<??> *receiver_rhs;

// public:    
//     dtkComposerEmitter<??> *emitter;
};

dtkComposerNodeListOperatorBinary::dtkComposerNodeListOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeListOperatorBinaryPrivate)
{
    // d->receiver_lhs = new dtkComposerReceiver<??>;
    // this->appendReceiver(d->receiver_lhs);

    // d->receiver_rhs = new dtkComposerReceiver<??>;
    // this->appendReceiver(d->receiver_rhs);

    // d->emitter = new dtkComposerEmitter<??>;
    // this->appendEmitter(d->emitter);
}

dtkComposerNodeListOperatorBinary::~dtkComposerNodeListOperatorBinary(void)
{
    // delete d->receiver_lhs;
    // delete d->receiver_rhs;
    // delete d->emitter;
    delete d;
    
    d = NULL;
}

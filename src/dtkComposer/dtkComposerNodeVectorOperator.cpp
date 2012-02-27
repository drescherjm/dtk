/* dtkComposerNodeVectorOperator.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:52:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 17:18:06 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 117
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeVectorOperator.h"

#include "dtkComposerEmitter.h"
#include "dtkComposerReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorOperatorUnaryPrivate
{
// public:
//     dtkComposerReceiver<??> *receiver;

// public:    
//     dtkComposerEmitter<??> *emitter;
};

dtkComposerNodeVectorOperatorUnary::dtkComposerNodeVectorOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorOperatorUnaryPrivate)
{
    // d->receiver = new dtkComposerReceiver<??>;
    // this->appendReceiver(d->receiver);

    // d->emitter = new dtkComposerEmitter<??>;
    // this->appendEmitter(d->emitter);
}

dtkComposerNodeVectorOperatorUnary::~dtkComposerNodeVectorOperatorUnary(void)
{
    // delete d->receiver;
    // delete d->emitter;
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorOperatorBinaryPrivate
{
// public:
//     dtkComposerReceiver<??> *receiver_lhs;
//     dtkComposerReceiver<??> *receiver_rhs;

// public:    
//     dtkComposerEmitter<??> *emitter;
};

dtkComposerNodeVectorOperatorBinary::dtkComposerNodeVectorOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorOperatorBinaryPrivate)
{
    // d->receiver_lhs = new dtkComposerReceiver<??>;
    // this->appendReceiver(d->receiver_lhs);

    // d->receiver_rhs = new dtkComposerReceiver<??>;
    // this->appendReceiver(d->receiver_rhs);

    // d->emitter = new dtkComposerEmitter<??>;
    // this->appendEmitter(d->emitter);
}

dtkComposerNodeVectorOperatorBinary::~dtkComposerNodeVectorOperatorBinary(void)
{
    // delete d->receiver_lhs;
    // delete d->receiver_rhs;
    // delete d->emitter;
    delete d;
    
    d = NULL;
}

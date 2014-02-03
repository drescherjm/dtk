/* dtkComposerNodeVectorOperator.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:52:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 29 10:17:18 2012 (+0100)
 *           By: tkloczko
 *     Update #: 118
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeVectorOperator.h"

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

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
//     dtkComposerTransmitterReceiver<??> *receiver_lhs;
//     dtkComposerTransmitterReceiver<??> *receiver_rhs;

// public:    
//     dtkComposerTransmitterEmitter<??> *emitter;
};

dtkComposerNodeVectorOperatorBinary::dtkComposerNodeVectorOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorOperatorBinaryPrivate)
{
    // d->receiver_lhs = new dtkComposerTransmitterReceiver<??>;
    // this->appendReceiver(d->receiver_lhs);

    // d->receiver_rhs = new dtkComposerTransmitterReceiver<??>;
    // this->appendReceiver(d->receiver_rhs);

    // d->emitter = new dtkComposerTransmitterEmitter<??>;
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

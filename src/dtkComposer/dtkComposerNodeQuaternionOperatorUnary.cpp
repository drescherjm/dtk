/* dtkComposerNodeQuaternionOperatorUnary.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 14:22:58 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 27 17:56:52 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeQuaternion.h"
#include "dtkComposerNodeQuaternionOperatorUnary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnary 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeQuaternionOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkQuaternionReal> receiver_quat;

public:
    dtkComposerTransmitterEmitter<dtkQuaternionReal> emitter_quat;
};

dtkComposerNodeQuaternionOperatorUnary::dtkComposerNodeQuaternionOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeQuaternionOperatorUnaryPrivate)
{
    this->appendReceiver(&d->receiver_quat);
    this->appendEmitter(&d->emitter_quat);
}

dtkComposerNodeQuaternionOperatorUnary::~dtkComposerNodeQuaternionOperatorUnary(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeQuaternionOperatorUnaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkQuaternionReal> receiver_quat;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_val;
};

dtkComposerNodeQuaternionOperatorUnaryScalar::dtkComposerNodeQuaternionOperatorUnaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeQuaternionOperatorUnaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_quat);
    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeQuaternionOperatorUnaryScalar::~dtkComposerNodeQuaternionOperatorUnaryScalar(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnary - UNITARY
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorUnaryUnitary::run(void)
{
    d->emitter_quat.setData(d->receiver_quat.data().unit());
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnaryScalar - NORM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorUnaryScalarNorm::run(void)
{
    d->emitter_val.setData(d->receiver_quat.data().norm());
}

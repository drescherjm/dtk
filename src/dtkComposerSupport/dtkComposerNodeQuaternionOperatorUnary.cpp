/* dtkComposerNodeQuaternionOperatorUnary.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 14:22:58 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 13 16:32:35 2012 (+0200)
 *           By: tkloczko
 *     Update #: 10
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

public:
    qreal value;
};

dtkComposerNodeQuaternionOperatorUnaryScalar::dtkComposerNodeQuaternionOperatorUnaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeQuaternionOperatorUnaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_quat);

    d->value = 0.;
    d->emitter_val.setData(&d->value);
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
    if (d->receiver_quat.isEmpty()) {
        
        dtkWarn() << "Input not specified. Nothing is done";

    }  else {

        dtkQuaternionReal *quat = d->receiver_quat.data();
        quat->makeUnit();

        d->emitter_quat.setData(quat);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnaryScalar - NORM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorUnaryScalarNorm::run(void)
{
    if (d->receiver_quat.isEmpty()) {

        dtkWarn() << "Input not specified. Nothing is done";

    }  else {
        
        d->value = d->receiver_quat.data()->norm();

    }
}

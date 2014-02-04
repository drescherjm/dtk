/* dtkComposerNodeVectorRealOperatorUnary.cpp ---
 *
 * Author: slekout
 * Copyright (C) 2011 - Babette lekouta, Inria.
 * Created: Thu Apr 26 15:58:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated:
 *           By:
 *     Update #:
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerNodeVectorRealOperatorUnary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMathSupport/dtkVector>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vec;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal> emitter_vec;
};

dtkComposerNodeVectorRealOperatorUnary::dtkComposerNodeVectorRealOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorUnaryPrivate)
{
    this->appendReceiver(&d->receiver_vec);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVectorRealOperatorUnary::~dtkComposerNodeVectorRealOperatorUnary(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorUnaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vec;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_val;

public:
    qreal value;
};

dtkComposerNodeVectorRealOperatorUnaryScalar::dtkComposerNodeVectorRealOperatorUnaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorUnaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_vec);  

    d->value = 0.;
    d->emitter_val.setData(&d->value);
    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeVectorRealOperatorUnaryScalar::~dtkComposerNodeVectorRealOperatorUnaryScalar(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnary - UNITARY
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorUnaryUnitary::run(void)
{
    if (d->receiver_vec.isEmpty()){
        dtkWarn() << "Input not specified. Nothing is done";
        d->emitter_vec.clearData();

    } else {
        dtkVectorReal *vector = d->receiver_vec.data();
        vector->makeUnit();
        d->emitter_vec.setData(vector);
    }
}
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorUnaryScalar - NORM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorUnaryScalarNorm::run(void)
{
    if (d->receiver_vec.isEmpty()){
        dtkWarn() << "Input not specified. Nothing is done";
        d->value = -1.;

    } else {
        d->value = d->receiver_vec.data()->norm();
    }

}

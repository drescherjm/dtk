/* dtkComposerNodeVectorIntegerOperatorUnary.cpp ---
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


#include "dtkComposerNodeVectorIntegerOperatorUnary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMathSupport/dtkVector>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorInteger> receiver_vec;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger> emitter_vec;
};

dtkComposerNodeVectorIntegerOperatorUnary::dtkComposerNodeVectorIntegerOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerOperatorUnaryPrivate)
{
    this->appendReceiver(&d->receiver_vec);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVectorIntegerOperatorUnary::~dtkComposerNodeVectorIntegerOperatorUnary(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorUnaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorUnaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorInteger> receiver_vec;

public:
    dtkComposerTransmitterEmitter<qlonglong> emitter_val;

public:
    qlonglong value;
};

dtkComposerNodeVectorIntegerOperatorUnaryScalar::dtkComposerNodeVectorIntegerOperatorUnaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerOperatorUnaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_vec);

    d->value = 0.;
    d->emitter_val.setData(&d->value);
    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeVectorIntegerOperatorUnaryScalar::~dtkComposerNodeVectorIntegerOperatorUnaryScalar(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorUnary - UNITARY
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorUnaryUnitary::run(void)
{
    if (d->receiver_vec.isEmpty()) {
        dtkWarn() << "Input not specified. Nothing is done";
        d->emitter_vec.clearData();

    } else {
        dtkVectorInteger *vector = d->receiver_vec.data();
        vector->makeUnit();
        d->emitter_vec.setData(vector);
    }
}
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorUnaryScalar - NORM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorUnaryScalarNorm::run(void)
{
    if (d->receiver_vec.isEmpty()) {
        dtkWarn() << "Input not specified. Nothing is done";
        d->value = -1.;

    } else {
        d->value = d->receiver_vec.data()->norm();
    }

}

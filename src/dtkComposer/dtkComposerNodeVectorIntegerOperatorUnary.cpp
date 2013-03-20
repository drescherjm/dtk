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

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorInteger*> receiver_vec;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger*> emitter_vec;
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
    dtkComposerTransmitterReceiver<dtkVectorInteger*> receiver_vec;

public:
    dtkComposerTransmitterEmitter<qlonglong> emitter_val;
};

dtkComposerNodeVectorIntegerOperatorUnaryScalar::dtkComposerNodeVectorIntegerOperatorUnaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerOperatorUnaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_vec);  

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
    if (!d->receiver_vec.isEmpty()){
        dtkVectorInteger *vector = d->receiver_vec.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorUnaryUnitary::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vec.clearData();
            return;
        }

        vector->makeUnit();
        d->emitter_vec.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorUnaryUnitary::" << Q_FUNC_INFO << "Input not specified. Nothing is done";
        d->emitter_vec.clearData();
    }
}
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorUnaryScalar - NORM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorUnaryScalarNorm::run(void)
{
    if (!d->receiver_vec.isEmpty()){
        const dtkVectorInteger *vector = d->receiver_vec.constData();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorUnaryScalarNorm::" << Q_FUNC_INFO << "Input vector not set. -1 is returned";
            d->emitter_val.setData(-1);
            return;
        }        

        d->emitter_val.setData(vector->norm());

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorUnaryScalarNorm::" << Q_FUNC_INFO << "Input not specified. Nothing is done";
        d->emitter_val.setData(-1);
    }
}

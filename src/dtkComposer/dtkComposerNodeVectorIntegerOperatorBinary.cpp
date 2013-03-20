/* dtkComposerNodeVectorIntegerOperatorBinary.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - Babette Lekouta, Inria.
 * Created: Thu Apr 26 16:15:40 2012 (+0200)
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

#include "dtkComposerNodeVectorIntegerOperatorBinary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorInteger*> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVectorInteger*> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger*> emitter_vec;

public:
    dtkVectorInteger *vector;
};

dtkComposerNodeVectorIntegerOperatorBinary::dtkComposerNodeVectorIntegerOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerOperatorBinaryPrivate)
{
    d->vector = NULL;

    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVectorIntegerOperatorBinary::~dtkComposerNodeVectorIntegerOperatorBinary(void)
{
    if (d->vector)
        delete d->vector;
    d->vector = NULL;

    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorBinaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorInteger*> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVectorInteger*> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<qlonglong> emitter_val;

public:
    qlonglong value;
};

dtkComposerNodeVectorIntegerOperatorBinaryScalar::dtkComposerNodeVectorIntegerOperatorBinaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerOperatorBinaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);

    d->value = 0.;
    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeVectorIntegerOperatorBinaryScalar::~dtkComposerNodeVectorIntegerOperatorBinaryScalar(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorHomothetic
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorHomotheticPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorInteger*> receiver_vec;
    dtkComposerTransmitterReceiver<qlonglong>         receiver_val;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger*> emitter_vec;
};

dtkComposerNodeVectorIntegerOperatorHomothetic::dtkComposerNodeVectorIntegerOperatorHomothetic(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerOperatorHomotheticPrivate)
{
    this->appendReceiver(&d->receiver_vec);
    this->appendReceiver(&d->receiver_val);

    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVectorIntegerOperatorHomothetic::~dtkComposerNodeVectorIntegerOperatorHomothetic(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinary - SUM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorBinarySum::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorBinarySum::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

        if (d->vector)
            d->vector->deallocate();

    } else {

        if (!d->vector) {
            d->vector = new dtkVectorInteger();
        }

        dtkVectorInteger *v_lhs = d->receiver_lhs.constData();
        dtkVectorInteger *v_rhs = d->receiver_rhs.constData();

        if (!v_lhs || !v_rhs) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorBinarySum::" << Q_FUNC_INFO << "Input vectors not set. Nothing is done";
            d->emitter_vec.clearData();
            d->vector->deallocate();
            return;
        }

        if (v_lhs->size() != v_rhs->size()) {
            dtkWarn() << "dtkComposerNodeVectorIntegerOperatorBinarySum::" << Q_FUNC_INFO << "Input vectors do not have the same size. Nothing is done";
            d->vector->deallocate();
            d->emitter_vec.clearData();
            return;
        } 

        *(d->vector) = (*v_lhs + *v_rhs);
        d->emitter_vec.setData(d->vector);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinary - SUBSTRACT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorBinarySubstract::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorBinarySubstract::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

        if (d->vector)
            d->vector->deallocate();

    } else {

        if (!d->vector) {
            d->vector = new dtkVectorInteger();
        }

        dtkVectorInteger *v_lhs = d->receiver_lhs.constData();
        dtkVectorInteger *v_rhs = d->receiver_rhs.constData();

        if (!v_lhs || !v_rhs) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorBinarySubstract::" << Q_FUNC_INFO << "Input vectors not set. Nothing is done";
            d->emitter_vec.clearData();
            d->vector->deallocate();
            return;
        }

        if (v_lhs->size() != v_rhs->size()) {
            dtkWarn() << "dtkComposerNodeVectorIntegerOperatorBinarySubstract::" << Q_FUNC_INFO << "Input vectors do not have the same size. Nothing is done";
            d->vector->deallocate();
            d->emitter_vec.clearData();
            return;
        } 

        *(d->vector) = (*v_lhs - *v_rhs);
        d->emitter_vec.setData(d->vector);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinaryScalar - DOT PRODUCT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorBinaryScalarDotProd::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorBinaryScalarDotProd::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_val.clearData();

    } else {

        dtkVectorInteger *v_lhs = d->receiver_lhs.constData();
        dtkVectorInteger *v_rhs = d->receiver_rhs.constData();

        if (!v_lhs || !v_rhs) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorBinaryScalarDotProd::" << Q_FUNC_INFO << "Input vectors not set. Nothing is done";
            d->emitter_val.clearData();
            return;
        }

        if (v_lhs->size() != v_rhs->size()) {
            dtkWarn() << "dtkComposerNodeVectorIntegerOperatorBinaryScalarDotProd::" << Q_FUNC_INFO << "Input vectors do not have the same size. Nothing is done";
            return;
        } 

        d->emitter_val.setData( (*v_lhs) * (*v_rhs) );
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorHomothetic - MULTIPLICATION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorHomotheticMult::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()) { 
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorHomotheticMult::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

    } else {
        
        dtkVectorInteger *vector = d->receiver_vec.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorHomotheticMult::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vec.clearData();
            return;
        }

        *vector *= d->receiver_val.data();
        d->emitter_vec.setData(vector);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorHomothetic - DIVISION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorHomotheticDivision::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()) {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorHomotheticDivision::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

    } else {
        qlonglong value = d->receiver_val.data();

        if (value != 0 ) {
            
            dtkVectorInteger *vector = d->receiver_vec.data();
            
            if (!vector) {
                dtkError() << "dtkComposerNodeVectorIntegerOperatorHomotheticDivision::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
                d->emitter_vec.clearData();
                return;
            }

            *vector /= value;

            d->emitter_vec.setData(vector);

        } else {
            dtkWarn() << "dtkComposerNodeVectorIntegerOperatorHomotheticDivision::" << Q_FUNC_INFO << "You divide by zero. Nothing is done" ;
            d->emitter_vec.clearData();

        }
    }
}

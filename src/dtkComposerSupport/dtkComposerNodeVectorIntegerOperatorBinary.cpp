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

#include <dtkMathSupport/dtkVector>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorInteger> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVectorInteger> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger> emitter_vec;

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
    dtkComposerTransmitterReceiver<dtkVectorInteger> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVectorInteger> receiver_rhs;

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
    d->emitter_val.setData(&d->value);
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
    dtkComposerTransmitterReceiver<dtkVectorInteger> receiver_vec;
    dtkComposerTransmitterVariant                 receiver_val;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger>  emitter_vec;
};

dtkComposerNodeVectorIntegerOperatorHomothetic::dtkComposerNodeVectorIntegerOperatorHomothetic(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerOperatorHomotheticPrivate)
{
    this->appendReceiver(&d->receiver_vec);

    QList<int> variant_list;

    variant_list << QMetaType::LongLong << QMetaType::Double;
    d->receiver_val.setDataTypes(variant_list);
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
        dtkWarn() << "Inputs not specified. Nothing is done";

        if (d->vector)
            d->vector->deallocate();

    } else {

        if (!d->vector) {
            d->vector = new dtkVectorInteger();
            d->emitter_vec.setData(d->vector);
        }

        dtkVectorInteger *v_lhs = d->receiver_lhs.data();
        dtkVectorInteger *v_rhs = d->receiver_rhs.data();

        if (v_lhs->size() != v_rhs->size()) {
            dtkWarn()<< "Input vectors do not have the same size. Nothing is done";
            d->vector->deallocate();
        } else {
            *(d->vector) = (*v_lhs + *v_rhs);
        }
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinary - SUBSTRACT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorBinarySubstract::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

        if (d->vector)
            d->vector->deallocate();

    } else {

        if (!d->vector) {
            d->vector = new dtkVectorInteger();
            d->emitter_vec.setData(d->vector);
        }

        dtkVectorInteger *v_lhs = d->receiver_lhs.data();
        dtkVectorInteger *v_rhs = d->receiver_rhs.data();

        if (v_lhs->size() != v_rhs->size()) {
            dtkWarn()<< "Input vectors do not have the same size. Nothing is done";
            d->vector->deallocate();
        } else {
            *(d->vector) = ((*v_lhs) - (*v_rhs));
        }
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinaryScalar - DOT PRODUCT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorBinaryScalarDotProd::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

        d->value = 0.;

    } else {

        d->value = (*(d->receiver_lhs.data())) * (*(d->receiver_rhs.data()));

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorHomothetic - MULTIPLICATION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorHomotheticMult::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()){ 
        dtkWarn() << "Inputs not specified. Nothing is done";

        d->emitter_vec.clearData();

    } else {
        
        dtkVectorInteger *vector = d->receiver_vec.data();
        qlonglong value = *d->receiver_val.data<qlonglong>();

        *vector *= value;

        d->emitter_vec.setData(vector);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorHomothetic - DIVISION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorHomotheticDivision::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

        d->emitter_vec.clearData();

    } else {
        qlonglong value = *d->receiver_val.data<qlonglong>();

        if (value != 0 ) {
            
            dtkVectorInteger *vector = d->receiver_vec.data();

            *vector /= value;

            d->emitter_vec.setData(vector);

        } else {
            dtkWarn() << "You divide by zero. Nothing is done" ;
            d->emitter_vec.clearData();

        }
    }
}

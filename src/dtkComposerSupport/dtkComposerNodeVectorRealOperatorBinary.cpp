/* dtkComposerNodeVectorRealOperatorBinary.cpp ---
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

#include "dtkComposerNodeVectorRealOperatorBinary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkMathSupport/dtkVector>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal> emitter_vec;

public:
    dtkVectorReal *vector;
};

dtkComposerNodeVectorRealOperatorBinary::dtkComposerNodeVectorRealOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorBinaryPrivate)
{
    d->vector = NULL;

    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVectorRealOperatorBinary::~dtkComposerNodeVectorRealOperatorBinary(void)
{
    if (d->vector)
        delete d->vector;

    d->vector = NULL;

    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorBinaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_val;

public:
    qreal value;
};

dtkComposerNodeVectorRealOperatorBinaryScalar::dtkComposerNodeVectorRealOperatorBinaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorBinaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);

    d->value = 0.;
    d->emitter_val.setData(&d->value);
    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeVectorRealOperatorBinaryScalar::~dtkComposerNodeVectorRealOperatorBinaryScalar(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorHomothetic
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorHomotheticPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vec;
    dtkComposerTransmitterVariant                 receiver_val;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal>  emitter_vec;
};

dtkComposerNodeVectorRealOperatorHomothetic::dtkComposerNodeVectorRealOperatorHomothetic(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorHomotheticPrivate)
{
    this->appendReceiver(&d->receiver_vec);

    QList<int> variant_list;

    variant_list << QMetaType::LongLong << QMetaType::Double;
    d->receiver_val.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_val);

    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVectorRealOperatorHomothetic::~dtkComposerNodeVectorRealOperatorHomothetic(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinary - SUM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorBinarySum::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

        if (d->vector)
            d->vector->deallocate();

    } else {

        dtkVectorReal *v_lhs = d->receiver_lhs.data();
        dtkVectorReal *v_rhs = d->receiver_rhs.data();

        if (!v_lhs || !v_rhs) {
            dtkWarn() << "NULL Input vectors. Nothing is done";
            return;
        }

        if (!d->vector) {
            d->vector = new dtkVectorReal();
            d->emitter_vec.setData(d->vector);
        }

        if (v_lhs->size() != v_rhs->size()) {
            dtkWarn() << "Input vectors do not have the same size. Nothing is done";
            d->vector->deallocate();
        } else {
            *(d->vector) = (*v_lhs + *v_rhs);
        }
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinary - SUBSTRACT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorBinarySubstract::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

        if (d->vector)
            d->vector->deallocate();

    } else {

        if (!d->vector) {
            d->vector = new dtkVectorReal();
            d->emitter_vec.setData(d->vector);
        }

        dtkVectorReal *v_lhs = d->receiver_lhs.data();
        dtkVectorReal *v_rhs = d->receiver_rhs.data();

        if (v_lhs->size() != v_rhs->size()) {
            dtkWarn() << "Input vectors do not have the same size. Nothing is done";
            d->vector->deallocate();
        } else {
            *(d->vector) = ((*v_lhs) - (*v_rhs));
        }
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinaryScalar - DOT PRODUCT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorBinaryScalarDotProd::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

        d->value = 0.;

    } else {

        d->value = (*(d->receiver_lhs.data())) * (*(d->receiver_rhs.data()));

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorHomothetic - MULTIPLICATION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorHomotheticMult::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

        d->emitter_vec.clearData();

    } else {

        dtkVectorReal *vector = d->receiver_vec.data();
        qreal value = *d->receiver_val.data<qreal>();

        *vector *= value;

        d->emitter_vec.setData(vector);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorHomothetic - DIVISION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorHomotheticDivision::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

        d->emitter_vec.clearData();

    } else {
        qreal value = *d->receiver_val.data<qreal>();

        if (value != 0 ) {

            dtkVectorReal *vector = d->receiver_vec.data();

            *vector /= value;

            d->emitter_vec.setData(vector);

        } else {
            dtkWarn() << "You divide by zero. Nothing is done" ;
            d->emitter_vec.clearData();

        }
    }
}

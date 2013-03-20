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

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal*> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVectorReal*> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal*> emitter_vec;

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
    dtkComposerTransmitterReceiver<dtkVectorReal*> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVectorReal*> receiver_rhs;

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
    dtkComposerTransmitterReceiver<dtkVectorReal*> receiver_vec;
    dtkComposerTransmitterVariant                  receiver_val;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal*> emitter_vec;
};

dtkComposerNodeVectorRealOperatorHomothetic::dtkComposerNodeVectorRealOperatorHomothetic(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorHomotheticPrivate)
{
    this->appendReceiver(&d->receiver_vec);

    QVector<const dtkComposerType*> variant_list;

    variant_list << dtkComposerTypeInfo<qlonglong>::type() << dtkComposerTypeInfo<double>::type();
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
        dtkWarn() << "dtkComposerNodeVectorRealOperatorBinarySum::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

        if (d->vector)
            d->vector->deallocate();

    } else {

        if (!d->vector) {
            d->vector = new dtkVectorReal();
        }

        dtkVectorReal *v_lhs = d->receiver_lhs.constData();
        dtkVectorReal *v_rhs = d->receiver_rhs.constData();

        if (!v_lhs || !v_rhs) {
            dtkError() << "dtkComposerNodeVectorRealOperatorBinarySum::" << Q_FUNC_INFO << "Input vectors not set. Nothing is done";
            d->emitter_vec.clearData();
            d->vector->deallocate();
            return;
        }

        if (v_lhs->size() != v_rhs->size()) {
            dtkWarn()<< "dtkComposerNodeVectorRealOperatorBinarySum::" << Q_FUNC_INFO << "Input vectors do not have the same size. Nothing is done";
            d->emitter_vec.clearData();
            d->vector->deallocate();
            return;
        }

        *(d->vector) = (*v_lhs + *v_rhs);
        d->emitter_vec.setData(d->vector);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinary - SUBSTRACT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorBinarySubstract::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "dtkComposerNodeVectorRealOperatorBinarySubstract::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

        if (d->vector)
            d->vector->deallocate();

    } else {

        if (!d->vector) {
            d->vector = new dtkVectorReal();
        }

        dtkVectorReal *v_lhs = d->receiver_lhs.constData();
        dtkVectorReal *v_rhs = d->receiver_rhs.constData();

        if (!v_lhs || !v_rhs) {
            dtkError() << "dtkComposerNodeVectorRealOperatorBinarySubstract::" << Q_FUNC_INFO << "Input vectors not set. Nothing is done";
            d->emitter_vec.clearData();
            d->vector->deallocate();
            return;
        }

        if (v_lhs->size() != v_rhs->size()) {
            dtkWarn() << "dtkComposerNodeVectorRealOperatorBinarySubstract::" << Q_FUNC_INFO << "Input vectors do not have the same size. Nothing is done";
            d->emitter_vec.clearData();
            d->vector->deallocate();
            return;
        }
         
        *(d->vector) = (*v_lhs) - (*v_rhs);
        d->emitter_vec.setData(d->vector);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinaryScalar - DOT PRODUCT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorBinaryScalarDotProd::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "dtkComposerNodeVectorRealOperatorBinaryScalarDotProd::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_val.clearData();

    } else {

        const dtkVectorReal *v_lhs = d->receiver_lhs.constData();
        const dtkVectorReal *v_rhs = d->receiver_rhs.constData();

        if (!v_lhs || !v_rhs) {
            dtkError() << "dtkComposerNodeVectorRealOperatorBinaryScalarDotProd::" << Q_FUNC_INFO << "Input vectors not set. Nothing is done";
            d->emitter_val.clearData();
            return;
        }

        if (v_lhs->size() != v_rhs->size()) {
            dtkWarn() << "dtkComposerNodeVectorRealOperatorBinaryScalarDotProd::" << Q_FUNC_INFO << "Input vectors do not have the same size. Nothing is done";
            d->emitter_val.clearData();
            return;
        }

        d->emitter_val.setData( ((*v_lhs) * (*v_rhs)) );
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorHomothetic - MULTIPLICATION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorHomotheticMult::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()) { 
        dtkWarn() << "dtkComposerNodeVectorRealOperatorHomotheticMult::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

    } else {
        
        dtkVectorReal *vector = d->receiver_vec.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorRealOperatorHomotheticMult::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vec.clearData();
            return;
        }

        *vector *= d->receiver_val.data<qreal>();
        d->emitter_vec.setData(vector);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorHomothetic - DIVISION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorHomotheticDivision::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()) { 
        dtkWarn() << "dtkComposerNodeVector3DOperatorHomotheticDivision::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

    } else {
        qreal value = d->receiver_val.data<qreal>();

        if (value != 0 ) {
            
            dtkVectorReal *vector = d->receiver_vec.data();

            if (!vector) {
                dtkError() << "dtkComposerNodeVectorRealOperatorHomotheticDivision::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
                d->emitter_vec.clearData();
                return;
            }

            *vector /= value;
            d->emitter_vec.setData(vector);

        } else {
            dtkWarn() << "dtkComposerNodeVectorRealOperatorHomotheticDivision::" << Q_FUNC_INFO << "You divide by zero. Nothing is done" ;
            d->emitter_vec.clearData();

        }
    }
}

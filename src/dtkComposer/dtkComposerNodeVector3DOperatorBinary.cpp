/* dtkComposerNodeVector3DOperatorBinary.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 16:15:40 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2013 Tue Jan  8 09:46:07 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 109
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeVector3D.h"
#include "dtkComposerNodeVector3DOperatorBinary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<dtkVector3DReal*> emitter_vec;

public:
    dtkVector3DReal *vector;
};

dtkComposerNodeVector3DOperatorBinary::dtkComposerNodeVector3DOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorBinaryPrivate)
{
    d->vector = NULL;

    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVector3DOperatorBinary::~dtkComposerNodeVector3DOperatorBinary(void)
{
    if (d->vector)
        delete d->vector;

    d->vector = NULL;

    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorBinaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorBinaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_val;
};

dtkComposerNodeVector3DOperatorBinaryScalar::dtkComposerNodeVector3DOperatorBinaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorBinaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);

    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeVector3DOperatorBinaryScalar::~dtkComposerNodeVector3DOperatorBinaryScalar(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorHomothetic
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorHomotheticPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_vec;
    dtkComposerTransmitterVariant                   receiver_val;

public:
    dtkComposerTransmitterEmitter<dtkVector3DReal*>  emitter_vec;
};

dtkComposerNodeVector3DOperatorHomothetic::dtkComposerNodeVector3DOperatorHomothetic(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorHomotheticPrivate)
{
    this->appendReceiver(&d->receiver_vec);

    QVector<const dtkComposerType*> variant_list;

    variant_list << dtkComposerTypeInfo<qlonglong>::type() << dtkComposerTypeInfo<double>::type();
    d->receiver_val.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_val);

    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVector3DOperatorHomothetic::~dtkComposerNodeVector3DOperatorHomothetic(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorBinary - SUM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorBinarySum::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "dtkComposerNodeVector3DOperatorBinarySum::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

    } else {

        if (!d->vector) {
            d->vector = new dtkVector3DReal(0., 0., 0.);
        }

        const dtkVector3DReal *v_lhs = d->receiver_lhs.constData();
        const dtkVector3DReal *v_rhs = d->receiver_rhs.constData();

        if (!v_lhs || !v_rhs) {
            dtkError() << "dtkComposerNodeVector3DOperatorBinarySum::" << Q_FUNC_INFO << "Input vectors not set. Nothing is done";
            d->emitter_vec.clearData();
            return;
        }

        *(d->vector) = (*v_lhs + *v_rhs);
        d->emitter_vec.setData(d->vector);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorBinary - SUBSTRACT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorBinarySubstract::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "dtkComposerNodeVector3DOperatorBinarySubstract::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

    } else {

        if (!d->vector) {
            d->vector = new dtkVector3DReal(0., 0., 0.);
        }

        const dtkVector3DReal *v_lhs = d->receiver_lhs.constData();
        const dtkVector3DReal *v_rhs = d->receiver_rhs.constData();

        if (!v_lhs || !v_rhs) {
            dtkError() << "dtkComposerNodeVector3DOperatorBinarySubstract::" << Q_FUNC_INFO << "Input vectors not set. Nothing is done";
            d->emitter_vec.clearData();
            return;
        }

        *(d->vector) = (*v_lhs - *v_rhs);
        d->emitter_vec.setData(d->vector);

    }
}
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorBinary - CROSS PROD
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorBinaryCrossProd::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "dtkComposerNodeVector3DOperatorBinaryCrossProd::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

    } else {

        if (!d->vector) {
            d->vector = new dtkVector3DReal(0., 0., 0.);
        }

        const dtkVector3DReal *v_lhs = d->receiver_lhs.constData();
        const dtkVector3DReal *v_rhs = d->receiver_rhs.constData();

        if (!v_lhs || !v_rhs) {
            dtkError() << "dtkComposerNodeVector3DOperatorBinaryCrossProd::" << Q_FUNC_INFO << "Input vectors not set. Nothing is done";
            d->emitter_vec.clearData();
            return;
        }

        *(d->vector) = (*v_lhs % *v_rhs);  
        d->emitter_vec.setData(d->vector);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorBinaryScalar - DOT PROD
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorBinaryScalarDotProd::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "dtkComposerNodeVector3DOperatorBinaryScalarDotProd::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_val.clearData();

    } else {

        const dtkVector3DReal *v_lhs = d->receiver_lhs.constData();
        const dtkVector3DReal *v_rhs = d->receiver_rhs.constData();

        if (!v_lhs || !v_rhs) {
            dtkError() << "dtkComposerNodeVector3DOperatorBinaryScalarDotProd::" << Q_FUNC_INFO << "Input vectors not set. Nothing is done";
            d->emitter_val.clearData();
            return;
        }

        d->emitter_val.setData( ((*v_lhs) * (*v_rhs)) );
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorHomothetic - MULTIPLICATION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorHomotheticMult::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()) { 
        dtkWarn() << "dtkComposerNodeVector3DOperatorHomotheticMult::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

    } else {
        
        dtkVector3DReal *vector = d->receiver_vec.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVector3DOperatorHomotheticMult::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vec.clearData();
            return;
        }

        *vector *= d->receiver_val.data<qreal>();
        d->emitter_vec.setData(vector);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorHomothetic - DIVISION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorHomotheticDivision::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()) { 
        dtkWarn() << "dtkComposerNodeVector3DOperatorHomotheticDivision::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

    } else {
        qreal value = d->receiver_val.data<qreal>();

        if (value != 0 ) {
            
            dtkVector3DReal *vector = d->receiver_vec.data();

            if (!vector) {
                dtkError() << "dtkComposerNodeVector3DOperatorHomotheticDivision::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
                d->emitter_vec.clearData();
                return;
            }

            *vector /= value;
            d->emitter_vec.setData(vector);

        } else {
            dtkWarn() << "dtkComposerNodeVector3DOperatorHomotheticDivision::" << Q_FUNC_INFO << "You divide by zero. Nothing is done" ;
            d->emitter_vec.clearData();
        }
    }
}

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
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal> emitter_vec;
};

dtkComposerNodeVectorRealOperatorBinary::dtkComposerNodeVectorRealOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorBinaryPrivate)
{
    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVectorRealOperatorBinary::~dtkComposerNodeVectorRealOperatorBinary(void)
{
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
};

dtkComposerNodeVectorRealOperatorBinaryScalar::dtkComposerNodeVectorRealOperatorBinaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorBinaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);
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

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;
    d->receiver_val.setTypes(variant_list);
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
        d->emitter_vec.setData(dtkVectorReal());

    } else {
        dtkVectorReal& vector1(d->receiver_lhs.data());
        dtkVectorReal& vector2(d->receiver_rhs.data());

        if ( vector1.getRows() == vector2.getRows())
            d->emitter_vec.setData(vector1 + vector2 );

        else {
            dtkWarn()<< "Vectors do not have the same size";
            d->emitter_vec.setData(dtkVectorReal());
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
        d->emitter_vec.setData(dtkVectorReal());

    } else {



        dtkVectorReal& vector1(d->receiver_lhs.data());
        dtkVectorReal& vector2(d->receiver_rhs.data());

        if ( vector1.getRows() == vector2.getRows())
            d->emitter_vec.setData(vector1 - vector2 );


        else {
            dtkWarn()<< "Vectors do not have the same size";
            d->emitter_vec.setData(dtkVectorReal());
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
        d->emitter_val.setData(qreal());

    } else {
        dtkVectorReal& vector1(d->receiver_lhs.data());
        dtkVectorReal& vector2(d->receiver_rhs.data());

        if ( vector1.getRows() == vector2.getRows())
            d->emitter_val.setData(vector1 * vector2 );

        else {
            dtkWarn()<< "Vectors do not have the same size";
            d->emitter_val.setData(qreal());
        }

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorHomothetic - MULTIPLICATION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorHomotheticMult::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()){

        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vec.setData(dtkVectorReal());

    } else {
        dtkVectorReal& vector(d->receiver_vec.data());
        qreal value = qvariant_cast<qreal>(d->receiver_val.data());

        d->emitter_vec.setData(vector * value);

    }

}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorHomothetic - DIVISION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorHomotheticDivision::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()) {

        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vec.setData(dtkVectorReal());

    } else {
        dtkVectorReal& vector(d->receiver_vec.data());
        qreal value = qvariant_cast<qreal>(d->receiver_val.data());

        if (value!=0)
            d->emitter_vec.setData(vector * value);

    }

}

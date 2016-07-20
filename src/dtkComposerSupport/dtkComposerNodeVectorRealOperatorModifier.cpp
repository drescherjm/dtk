/* dtkComposerNodeVectorRealOperatorModifier.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2012 Wed Oct 10 18:13:50 (+0200)
 *           By: Thibaud Kloczko, Inria.
 *     Update #: 82
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerNodeVectorRealOperatorModifier.h"

#include <dtkMathSupport/dtkVector>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodearrayScalarOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorModifierPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector;
    dtkComposerTransmitterVariant receiver_value;
    dtkComposerTransmitterVariant receiver_index;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal>  emitter_vector;
};

dtkComposerNodeVectorRealOperatorModifier::dtkComposerNodeVectorRealOperatorModifier(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorModifierPrivate)
{
    this->appendReceiver(&d->receiver_vector);

    QList<int> variant_list;

    variant_list << QMetaType::LongLong;
    d->receiver_index.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_index);

    variant_list << QMetaType::Double;
    d->receiver_value.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_vector);
}

dtkComposerNodeVectorRealOperatorModifier::~dtkComposerNodeVectorRealOperatorModifier(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodeVectorRealOperatorModifierAll
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorModifierAllPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector;
    dtkComposerTransmitterVariant                 receiver_value;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal> emitter_vector;
};


dtkComposerNodeVectorRealOperatorModifierAll::dtkComposerNodeVectorRealOperatorModifierAll(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorModifierAllPrivate)
{
    this->appendReceiver(&d->receiver_vector);

    QList<int> variant_list;

    variant_list << QMetaType::LongLong << QMetaType::Double;
    d->receiver_value.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_vector);
}

dtkComposerNodeVectorRealOperatorModifierAll::~dtkComposerNodeVectorRealOperatorModifierAll(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodeVectorRealOperatorModifierPart
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorModifierPartPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector;
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_subvector;
    dtkComposerTransmitterReceiver<qlonglong>     receiver_index;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal> emitter_vector;
};


dtkComposerNodeVectorRealOperatorModifierPart::dtkComposerNodeVectorRealOperatorModifierPart(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorModifierPartPrivate)
{
    this->appendReceiver(&d->receiver_vector);
    this->appendReceiver(&d->receiver_subvector);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_vector);
}

dtkComposerNodeVectorRealOperatorModifierPart::~dtkComposerNodeVectorRealOperatorModifierPart(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier - SET
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierSet::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorReal *vector = d->receiver_vector.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (!vector) {
            dtkError() << "Vector is not defined.";
            return;
        }

        if (index >= vector->size()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            (*vector)[index] = value;

        }

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier - Sum
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierSum::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorReal *vector = d->receiver_vector.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (!vector) {
            dtkError() << "Vector is not defined.";
            return;
        }

        if (index >= vector->size()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            (*vector)[index] += value;

        }

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierSubstract::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorReal *vector = d->receiver_vector.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (!vector) {
            dtkError() << "Vector is not defined.";
            return;
        }

        if (index >= vector->size()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            (*vector)[index] -= value;

        }

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierMult::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorReal *vector = d->receiver_vector.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (!vector) {
            dtkError() << "Vector is not defined.";
            return;
        }

        if (index >= vector->size()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            (*vector)[index] *= value;

        }

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Divide
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierDivide::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorReal *vector = d->receiver_vector.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (!vector) {
            dtkError() << "Vector is not defined.";
            return;
        }

        if (index >= vector->size()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            if (value == 0)
                dtkWarn() << "Value is zero. Same array is returned." ;

            else
                (*vector)[index] /= value;

        }

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierAll - Add
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierAllAdd::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorReal *vector = d->receiver_vector.data();
        qreal value = *d->receiver_value.data<qreal>();

        if (!vector) {
            dtkError() << "Vector is not defined.";
            return;
        }

        for (qlonglong i = 0 ; i < vector->size(); ++i)
            (*vector)[i] += value ;

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierAll - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierAllSubstract::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorReal *vector = d->receiver_vector.data();
        qreal value = *d->receiver_value.data<qreal>();

        if (!vector) {
            dtkError() << "Vector is not defined.";
            d->emitter_vector.clearData();
            return;
        }

        for (qlonglong i = 0 ; i < vector->size(); ++i)
            (*vector)[i] -= value ;

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierAll - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierAllMult::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorReal *vector = d->receiver_vector.data();
        qreal value = *d->receiver_value.data<qreal>();

        if (!vector) {
            dtkError() << "Vector is not defined.";
            d->emitter_vector.clearData();
            return;
        }

        for (qlonglong i = 0 ; i < vector->size(); ++i)
            (*vector)[i] *= value ;

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierAll - Divide
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierAllDivide::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorReal *vector = d->receiver_vector.data();
        qreal value = *d->receiver_value.data<qreal>();

        if (!vector) {
            dtkError() << "Vector is not defined.";
            d->emitter_vector.clearData();
            return;
        }

        if (value == 0) {
            dtkWarn() << "Value is zero. Same array is returned." ;

        } else {

            for (qlonglong i = 0 ; i < vector->size(); ++i)
                (*vector)[i] /= value ;

        }

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierPart - Sum
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierPartSum::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_subvector.isEmpty()) {

        dtkVectorReal *vector = d->receiver_vector.data();
        dtkVectorReal *subvector = d->receiver_subvector.data();

        if (!vector) {
            dtkError() << DTK_PRETTY_FUNCTION << "Vector is not defined.";
            d->emitter_vector.clearData();
            return;
        }

        if (!subvector) {
            dtkError() << DTK_PRETTY_FUNCTION << "Subvector is not defined.";
            d->emitter_vector.clearData();
            return;
        }

        qlonglong index = 0;

        if (!d->receiver_index.isEmpty())
            index = *d->receiver_index.data();

        for (qlonglong i = 0; i < subvector->size(); ++i, ++index)
            (*vector)[index] += (*subvector)[i] ;

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifierPart - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierPartSubstract::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_subvector.isEmpty()) {

        dtkVectorReal *vector = d->receiver_vector.data();
        dtkVectorReal *subvector = d->receiver_subvector.data();

        if (!vector) {
            dtkError() << DTK_PRETTY_FUNCTION << "Vector is not defined.";
            d->emitter_vector.clearData();
            return;
        }

        if (!subvector) {
            dtkError() << DTK_PRETTY_FUNCTION << "Subvector is not defined.";
            d->emitter_vector.clearData();
            return;
        }

        qlonglong index = 0;

        if (!d->receiver_index.isEmpty())
            index = *d->receiver_index.data();

        for (qlonglong i = 0; i < subvector->size(); ++i, ++index)
            (*vector)[index] -= (*subvector)[i] ;

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

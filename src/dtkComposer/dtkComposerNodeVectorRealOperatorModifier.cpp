/* dtkComposerNodeVectorRealOperatorModifier.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 20 14:47:14 2012 (+0200)
 *           By: tkloczko
 *     Update #: 55
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

#include <dtkMath>

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
    dtkComposerTransmitterVariant               receiver_value;

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
// dtkComposerNodeVectorRealOperatorModifier - SET
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierSet::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorReal *vector = d->receiver_vector.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

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

        for (int i = 0 ; i< vector->size(); ++i)
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

        for (int i = 0 ; i< vector->size(); ++i)
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

        for (int i = 0 ; i< vector->size(); ++i)
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

        if (value == 0) {
            dtkWarn() << "Value is zero. Same array is returned." ;

        } else {
            
            for (int i = 0 ; i< vector->size(); ++i)
                (*vector)[i] *= value ;

        }

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

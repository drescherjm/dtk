/* dtkComposerNodeArrayScalarOperatorModifier.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Sep  7 15:36:38 2012 (+0200)
 *           By: tkloczko
 *     Update #: 93
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerNodeArrayScalarOperatorModifier.h"

#include <dtkContainer/dtkContainerVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodearrayScalarOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarOperatorModifierPrivate
{
public:
    dtkComposerTransmitterReceiverVector<qreal> receiver_array;
    dtkComposerTransmitterVariant receiver_index;
    dtkComposerTransmitterVariant receiver_value;

public:
    dtkComposerTransmitterEmitterVector<qreal> emitter_array;

public:
    dtkContainerVectorReal *array;
};

dtkComposerNodeArrayScalarOperatorModifier::dtkComposerNodeArrayScalarOperatorModifier(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarOperatorModifierPrivate)
{
    d->array = NULL;

    this->appendReceiver(&d->receiver_array);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::LongLong;
    d->receiver_index.setTypes(variant_list);
    this->appendReceiver(&d->receiver_index);

    variant_list << QVariant::Double;
    d->receiver_value.setTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_array);
}

dtkComposerNodeArrayScalarOperatorModifier::~dtkComposerNodeArrayScalarOperatorModifier(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodeArrayScalarOperatorModifierAll
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarOperatorModifierAllPrivate
{
public:
    dtkComposerTransmitterReceiverVector<qreal> receiver_array;
    dtkComposerTransmitterVariant receiver_value;

public:
    dtkComposerTransmitterEmitterVector<qreal> emitter_array;

public:
    dtkContainerVectorReal *array;
};


dtkComposerNodeArrayScalarOperatorModifierAll::dtkComposerNodeArrayScalarOperatorModifierAll(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarOperatorModifierAllPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;
    d->receiver_value.setTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_array);
}

dtkComposerNodeArrayScalarOperatorModifierAll::~dtkComposerNodeArrayScalarOperatorModifierAll(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - INSERT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorInsert::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        d->array = d->receiver_array.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (index >= d->array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            d->array->insert(index, value);

        }

        d->emitter_array.setData(d->array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Set
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorSet::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        d->array = d->receiver_array.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (index >= d->array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            d->array->replace(index, value);

        }

        d->emitter_array.setData(d->array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - APPEND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorAppend::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        d->array = d->receiver_array.data();

        qreal value = *d->receiver_value.data<qreal>();

        d->array->append(value);
        d->emitter_array.setData(d->array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - PREPEND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorPrepend::run(void)
{ 
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        d->array = d->receiver_array.data();

        qreal value = *d->receiver_value.data<qreal>();

        d->array->prepend(value);
        d->emitter_array.setData(d->array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll - Add
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorModifierAllAdd::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        d->array = d->receiver_array.data();

        qreal value = *d->receiver_value.data<qreal>();

        for(qlonglong i = 0 ; i < d->array->count(); ++i)
            (*d->array)[i] += value ;

        d->emitter_array.setData(d->array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorModifierAllSubstract::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        d->array = d->receiver_array.data();

        qreal value = *d->receiver_value.data<qreal>();

        for(qlonglong i = 0 ; i < d->array->count(); ++i)
            (*d->array)[i] -= value ;

        d->emitter_array.setData(d->array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorModifierAllMult::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        d->array = d->receiver_array.data();

        qreal value = *d->receiver_value.data<qreal>();

        for(qlonglong i = 0 ; i < d->array->count(); ++i)
            (*d->array)[i] *= value ;

        d->emitter_array.setData(d->array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll - Divide
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorModifierAllDivide::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        d->array = d->receiver_array.data();

        qreal value = *d->receiver_value.data<qreal>();

        if (value == 0) {
            dtkWarn() << "Value is zero. Same array is returned." ;

        } else {
            for(qlonglong i = 0 ; i < d->array->count(); ++i)
                (*d->array)[i] /= value ;

        }

        d->emitter_array.setData(d->array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - SUM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorSum::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        d->array = d->receiver_array.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (index >= d->array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            (*d->array)[index] += value;

        }

        d->emitter_array.setData(d->array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorSubstract::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        d->array = d->receiver_array.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (index >= d->array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            (*d->array)[index] -= value;

        }

        d->emitter_array.setData(d->array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorMult::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        d->array = d->receiver_array.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (index >= d->array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            (*d->array)[index] *= value;

        }

        d->emitter_array.setData(d->array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Divide
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorDivide::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        d->array = d->receiver_array.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (index >= d->array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            if (value == 0)
                dtkWarn() << "Value is zero. Same array is returned." ;

            else
                (*d->array)[index] /= value;

        }

        d->emitter_array.setData(d->array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

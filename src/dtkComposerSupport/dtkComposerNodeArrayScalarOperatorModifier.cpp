/* dtkComposerNodeArrayScalarOperatorModifier.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 17:09:33 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 117
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

#include <dtkContainerSupport/dtkContainerVector.h>

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
};

dtkComposerNodeArrayScalarOperatorModifier::dtkComposerNodeArrayScalarOperatorModifier(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarOperatorModifierPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<int> variant_list;

    variant_list << QMetaType::LongLong;
    d->receiver_index.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_index);

    variant_list << QMetaType::Double;
    d->receiver_value.setDataTypes(variant_list);
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
};


dtkComposerNodeArrayScalarOperatorModifierAll::dtkComposerNodeArrayScalarOperatorModifierAll(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarOperatorModifierAllPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<int> variant_list;

    variant_list << QMetaType::LongLong << QMetaType::Double;
    d->receiver_value.setDataTypes(variant_list);
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

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }

        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (index >= array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            array->insert(index, value);

        }

        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Set
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorSet::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }

        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (index >= array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            array->replace(index, value);

        }

        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - APPEND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorAppend::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }

        qreal value = *d->receiver_value.data<qreal>();

        array->append(value);
        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - PREPEND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorPrepend::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }

        qreal value = *d->receiver_value.data<qreal>();

        array->prepend(value);
        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll - Add
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorModifierAllAdd::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }

        qreal value = *d->receiver_value.data<qreal>();

        for (qlonglong i = 0 ; i < array->count(); ++i)
            (*array)[i] += value ;

        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorModifierAllSubstract::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }

        qreal value = *d->receiver_value.data<qreal>();

        for (qlonglong i = 0 ; i < array->count(); ++i)
            (*array)[i] -= value ;

        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorModifierAllMult::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }

        qreal value = *d->receiver_value.data<qreal>();

        for (qlonglong i = 0 ; i < array->count(); ++i)
            (*array)[i] *= value ;

        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll - Divide
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorModifierAllDivide::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }

        qreal value = *d->receiver_value.data<qreal>();

        if (value == 0) {
            dtkWarn() << "Value is zero. Same array is returned." ;

        } else {
            for (qlonglong i = 0 ; i < array->count(); ++i)
                (*array)[i] /= value ;

        }

        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - SUM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorSum::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }

        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (index >= array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            (*array)[index] += value;

        }

        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorSubstract::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }

        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (index >= array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            (*array)[index] -= value;

        }

        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorMult::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }

        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (index >= array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            (*array)[index] *= value;

        }

        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Divide
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorDivide::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal *array = d->receiver_array.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }

        qlonglong index = *d->receiver_index.data<qlonglong>();
        qreal value = *d->receiver_value.data<qreal>();

        if (index >= array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            if (value == 0)
                dtkWarn() << "Value is zero. Same array is returned." ;

            else
                (*array)[index] /= value;

        }

        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

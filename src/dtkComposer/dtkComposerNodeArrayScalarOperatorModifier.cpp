/* dtkComposerNodeArrayScalarOperatorModifier.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 26 16:02:34 2012 (+0200)
 *           By: tkloczko
 *     Update #: 52
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

#include <dtkCore/dtkContainerVector.h>

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

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong;
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
//  dtkComposerNodeArrayScalarOperatorModifierPend
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

        dtkContainerVectorReal& array(d->receiver_array.data());
        dtkxarch_int index = qvariant_cast<dtkxarch_int>(d->receiver_index.data());
        qreal value = qvariant_cast<qreal>(d->receiver_value.data());

        if (index < array.count()) {
            array.insert(index,value);
            d->emitter_array.setData(array);

        } else {
            dtkWarn() << "index > size of the vector. Nothing is done" ;
            dtkContainerVectorReal vec;
            d->emitter_array.setData(vec);
        }

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkContainerVectorReal vec;
        d->emitter_array.setData(vec);
    }
}


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - REPLACE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorReplace::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal& array(d->receiver_array.data());
        dtkxarch_int index = qvariant_cast<dtkxarch_int>(d->receiver_index.data());
        qreal value = qvariant_cast<qreal>(d->receiver_value.data());

        if (index < array.count()) {
            array.replace(index, value);
            d->emitter_array.setData(array);

        } else {
            dtkWarn() << "index > size of the vector. Nothing is done" ;
            dtkContainerVectorReal vec;
            d->emitter_array.setData(vec);
        }

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkContainerVectorReal vec;
        d->emitter_array.setData(vec);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - APPEND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorAppend::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal& array(d->receiver_array.data());
        qreal value = qvariant_cast<qreal>(d->receiver_value.data());

        array.append(value);
        d->emitter_array.setData( array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkContainerVectorReal vec;
        d->emitter_array.setData(vec);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - PREPEND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorPrepend::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal& array(d->receiver_array.data());
        qreal value = qvariant_cast<qreal>(d->receiver_value.data());

        array.prepend(value) ;
        d->emitter_array.setData( array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkContainerVectorReal vec;
        d->emitter_array.setData(vec);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll - Add
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorModifierAllAdd::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty()) {

        dtkContainerVectorReal& array(d->receiver_array.data());
        qreal value = qvariant_cast<qreal>(d->receiver_value.data());

        for (dtkxarch_int i = 0 ; i < array.count(); ++i)
            array[i] += value ;

        d->emitter_array.setData(array);

    } else {

        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkContainerVectorReal vec;
        d->emitter_array.setData(vec);

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorModifierAllSubstract::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal& array(d->receiver_array.data());
        qreal value = qvariant_cast<qreal>(d->receiver_value.data());

        for (dtkxarch_int i = 0 ; i< array.count(); ++i)
            array[i] -= value ;

        d->emitter_array.setData( array);

    } else {

        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkContainerVectorReal vec;
        d->emitter_array.setData(vec);

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorModifierAllMult::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal& array(d->receiver_array.data());
        qreal value = qvariant_cast<qreal>(d->receiver_value.data());

        for (dtkxarch_int i = 0 ; i< array.count(); ++i)
            array[i] *= value ;

        d->emitter_array.setData( array);

    } else {

        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkContainerVectorReal vec;
        d->emitter_array.setData(vec);

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperatorModifierAll - Divide
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorModifierAllDivide::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal& array(d->receiver_array.data());
        qreal value = qvariant_cast<qreal>(d->receiver_value.data());

        if (value == 0) {

            dtkWarn() << "Value is zero. Same array is returned." ;
            d->emitter_array.setData(array);

        } else {

            for (dtkxarch_int i = 0 ; i< array.count(); ++i)
                array[i] /= value ;

            d->emitter_array.setData(array);

        }

    } else {

        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkContainerVectorReal vec;
        d->emitter_array.setData(vec);

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - SUM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorSum::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal& array(d->receiver_array.data());
        dtkxarch_int index = qvariant_cast<dtkxarch_int>(d->receiver_index.data());
        qreal value = qvariant_cast<qreal>(d->receiver_value.data());

        if (index < array.count()) {
            array[index] += value ;
            d->emitter_array.setData(array);

        } else {
            dtkWarn() << "index > size of the vector. Nothing is done" ;
            dtkContainerVectorReal vec;
            d->emitter_array.setData(vec);
        }

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkContainerVectorReal vec;
        d->emitter_array.setData(vec);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorSubstract::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal& array(d->receiver_array.data());
        dtkxarch_int index = qvariant_cast<dtkxarch_int>(d->receiver_index.data());
        qreal value = qvariant_cast<qreal>(d->receiver_value.data());

        if (index < array.count()) {
            array[index] -=  value ;
            d->emitter_array.setData(array);

        } else {
            dtkWarn() << "index > size of the vector. Nothing is done" ;
            dtkContainerVectorReal vec;
            d->emitter_array.setData(vec);
        }

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkContainerVectorReal vec;
        d->emitter_array.setData(vec);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorMult::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal& array(d->receiver_array.data());
        dtkxarch_int index = qvariant_cast<dtkxarch_int>(d->receiver_index.data());
        qreal value = qvariant_cast<qreal>(d->receiver_value.data());

        if (index < array.count()) {
            array[index] *= value ;
            d->emitter_array.setData(array);

        } else {
            dtkWarn() << "index > size of the vector. Nothing is done" ;
            dtkContainerVectorReal vec;
            d->emitter_array.setData(vec);
        }

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkContainerVectorReal vec;
        d->emitter_array.setData(vec);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Divide
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorDivide::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkContainerVectorReal& array(d->receiver_array.data());
        dtkxarch_int index = qvariant_cast<dtkxarch_int>(d->receiver_index.data());
        qreal value = qvariant_cast<qreal>(d->receiver_value.data());

        if (index < array.count()) {
            if (value == 0)
                dtkWarn() << "Value is zero. Nothing is done" ;
            else
                array[index]/= value ;

            d->emitter_array.setData(array);

        } else {
            dtkWarn() << "index > size of the vector. Nothing is done" ;
            dtkContainerVectorReal vec;
            d->emitter_array.setData(vec);
        }

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkContainerVectorReal vec;
        d->emitter_array.setData(vec);
    }

}

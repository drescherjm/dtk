/* dtkComposerNodeVectorIntegerOperatorModifier.cpp ---
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
#include "dtkComposerNodeVectorIntegerOperatorModifier.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodearrayScalarOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorModifierPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorInteger> receiver_vector;
    dtkComposerTransmitterVariant receiver_value;
    dtkComposerTransmitterVariant receiver_index;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger>  emitter_vector;
};

dtkComposerNodeVectorIntegerOperatorModifier::dtkComposerNodeVectorIntegerOperatorModifier(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerOperatorModifierPrivate)
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

dtkComposerNodeVectorIntegerOperatorModifier::~dtkComposerNodeVectorIntegerOperatorModifier(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodeVectorIntegerOperatorModifierAll
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorModifierAllPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorInteger> receiver_vector;
    dtkComposerTransmitterVariant                 receiver_value;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger> emitter_vector;
};


dtkComposerNodeVectorIntegerOperatorModifierAll::dtkComposerNodeVectorIntegerOperatorModifierAll(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerOperatorModifierAllPrivate)
{
    this->appendReceiver(&d->receiver_vector);

    QList<int> variant_list;

    variant_list << QMetaType::LongLong << QMetaType::Double;
    d->receiver_value.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_vector);
}

dtkComposerNodeVectorIntegerOperatorModifierAll::~dtkComposerNodeVectorIntegerOperatorModifierAll(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodeVectorIntegerOperatorModifierPart
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorModifierPartPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorInteger> receiver_vector;
    dtkComposerTransmitterReceiver<dtkVectorInteger> receiver_subvector;
    dtkComposerTransmitterReceiver<qlonglong>     receiver_index;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger> emitter_vector;
};


dtkComposerNodeVectorIntegerOperatorModifierPart::dtkComposerNodeVectorIntegerOperatorModifierPart(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerOperatorModifierPartPrivate)
{
    this->appendReceiver(&d->receiver_vector);
    this->appendReceiver(&d->receiver_subvector);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_vector);
}

dtkComposerNodeVectorIntegerOperatorModifierPart::~dtkComposerNodeVectorIntegerOperatorModifierPart(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifier - SET
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorModifierSet::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qlonglong value = *d->receiver_value.data<qlonglong>();

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
// dtkComposerNodeVectorIntegerOperatorModifier - Sum
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorModifierSum::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qlonglong value = *d->receiver_value.data<qlonglong>();

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

void dtkComposerNodeVectorIntegerOperatorModifierSubstract::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qlonglong value = *d->receiver_value.data<qlonglong>();

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

void dtkComposerNodeVectorIntegerOperatorModifierMult::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qlonglong value = *d->receiver_value.data<qlonglong>();

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

void dtkComposerNodeVectorIntegerOperatorModifierDivide::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        qlonglong index = *d->receiver_index.data<qlonglong>();
        qlonglong value = *d->receiver_value.data<qlonglong>();

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
// dtkComposerNodeVectorIntegerOperatorModifierAll - Add
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorModifierAllAdd::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        qlonglong value = *d->receiver_value.data<qlonglong>();

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
// dtkComposerNodeVectorIntegerOperatorModifierAll - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorModifierAllSubstract::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        qlonglong value = *d->receiver_value.data<qlonglong>();

        if (!vector) {
            dtkError() << "Vector is not defined.";
            d->emitter_vector.clearData();
            return;
        }

        for (qlonglong i = 0 ; i< vector->size(); ++i)
            (*vector)[i] -= value ;

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorModifierAll - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorModifierAllMult::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        qlonglong value = *d->receiver_value.data<qlonglong>();

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
// dtkComposerNodeVectorIntegerOperatorModifierAll - Divide
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorModifierAllDivide::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_value.isEmpty() ) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        qlonglong value = *d->receiver_value.data<qlonglong>();

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
// dtkComposerNodeVectorIntegerOperatorModifierPart - Sum
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorModifierPartSum::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_subvector.isEmpty()) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        dtkVectorInteger *subvector = d->receiver_subvector.data();

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
// dtkComposerNodeVectorIntegerOperatorModifierPart - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorIntegerOperatorModifierPartSubstract::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_subvector.isEmpty()) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        dtkVectorInteger *subvector = d->receiver_subvector.data();

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

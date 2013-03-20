/* dtkComposerNodeVectorIntegerOperatorModifier.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2013 Wed Jan  9 09:52:59 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 99
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
    dtkComposerTransmitterReceiver<dtkVectorInteger*> receiver_vector;
    dtkComposerTransmitterReceiver<qlonglong>         receiver_value;
    dtkComposerTransmitterReceiver<qlonglong>         receiver_index;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger*> emitter_vector;
};

dtkComposerNodeVectorIntegerOperatorModifier::dtkComposerNodeVectorIntegerOperatorModifier(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerOperatorModifierPrivate)
{
    this->appendReceiver(&d->receiver_vector);
    this->appendReceiver(&d->receiver_index);
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
    dtkComposerTransmitterReceiver<dtkVectorInteger*> receiver_vector;
    dtkComposerTransmitterReceiver<qlonglong>         receiver_value;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger*> emitter_vector;
};


dtkComposerNodeVectorIntegerOperatorModifierAll::dtkComposerNodeVectorIntegerOperatorModifierAll(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerOperatorModifierAllPrivate)
{
    this->appendReceiver(&d->receiver_vector);
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
    dtkComposerTransmitterReceiver<dtkVectorInteger*> receiver_vector;
    dtkComposerTransmitterReceiver<dtkVectorInteger*> receiver_subvector;
    dtkComposerTransmitterReceiver<qlonglong>         receiver_index;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger*> emitter_vector;
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
        qlonglong index = d->receiver_index.data();
        qlonglong value = d->receiver_value.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierSet::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vector.clearData();
            return;
        }

        if (index >= vector->size()) {
            dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierSet::" << Q_FUNC_INFO << "index > size of the vector. Same array is returned.";

        } else {
            (*vector)[index] = value;

        }
        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierSet::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
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
        qlonglong index = d->receiver_index.data();
        qlonglong value = d->receiver_value.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierSum::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vector.clearData();
            return;
        }

        if (index >= vector->size()) {
            dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierSum::" << Q_FUNC_INFO << "index > size of the vector. Same array is returned.";

        } else {
            (*vector)[index] += value;

        }
        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierSum::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
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
        qlonglong index = d->receiver_index.data();
        qlonglong value = d->receiver_value.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierSubstract::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vector.clearData();
            return;
        }

        if (index >= vector->size()) {
            dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierSubstract::" << Q_FUNC_INFO << "index > size of the vector. Same array is returned.";

        } else {
            (*vector)[index] -= value;

        }
        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierSubstract::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
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
        qlonglong index = d->receiver_index.data();
        qlonglong value = d->receiver_value.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierMult::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vector.clearData();
            return;
        }

        if (index >= vector->size()) {
            dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierMult::" << Q_FUNC_INFO << "index > size of the vector. Same array is returned.";

        } else {
            (*vector)[index] *= value;

        }
        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierMult::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
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
        qlonglong index = d->receiver_index.data();
        qlonglong value = d->receiver_value.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierMult::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vector.clearData();
            return;
        }

        if (index >= vector->size()) {
            dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierMult::" << Q_FUNC_INFO << "index > size of the vector. Same array is returned.";

        } else {
            if (value == 0)
                dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierMult::" << Q_FUNC_INFO << "Value is zero. Same array is returned." ;

            else
                (*vector)[index] /= value;

        }
        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierMult::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
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
        qlonglong value = d->receiver_value.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierAllAdd::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vector.clearData();
            return;
        }

        for (qlonglong i = 0 ; i < vector->size(); ++i)
            (*vector)[i] += value ;

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierAllAdd::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
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
        qlonglong value = d->receiver_value.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierAllSubstract::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vector.clearData();
            return;
        }

        for (qlonglong i = 0 ; i< vector->size(); ++i)
            (*vector)[i] -= value ;

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierAllSubstract::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
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
        qlonglong value = d->receiver_value.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierAllMult::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vector.clearData();
            return;
        }

        for (qlonglong i = 0 ; i < vector->size(); ++i)
            (*vector)[i] *= value ;

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierAllMult::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
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
        qlonglong value = d->receiver_value.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierAllDivide::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
            d->emitter_vector.clearData();
            return;
        }

        if (value == 0) {
            dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierAllDivide::" << Q_FUNC_INFO << "Value is zero. Same array is returned." ;

        } else {
            
            for (qlonglong i = 0 ; i < vector->size(); ++i)
                (*vector)[i] /= value ;

        }

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierAllDivide::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
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
        dtkVectorInteger *subvector = d->receiver_subvector.constData();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierPartSum::" << Q_FUNC_INFO << "Vector is not defined.";
            d->emitter_vector.clearData();
            return;
        }

        if (!subvector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierPartSum::" << Q_FUNC_INFO << "Subvector is not defined.";
            d->emitter_vector.clearData();
            return;
        }

        qlonglong index = 0;

        if (!d->receiver_index.isEmpty())
            index = d->receiver_index.data();
            
        for (qlonglong i = 0; i < subvector->size(); ++i, ++index)
            (*vector)[index] += (*subvector)[i] ;

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierPartSum::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
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
        dtkVectorInteger *subvector = d->receiver_subvector.constData();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierPartSubstract::" << Q_FUNC_INFO << "Vector is not defined.";
            d->emitter_vector.clearData();
            return;
        }

        if (!subvector) {
            dtkError() << "dtkComposerNodeVectorIntegerOperatorModifierPartSubstract::" << Q_FUNC_INFO << "Subvector is not defined.";
            d->emitter_vector.clearData();
            return;
        }

        qlonglong index = 0;

        if (!d->receiver_index.isEmpty())
            index = d->receiver_index.data();
            
        for (qlonglong i = 0; i < subvector->size(); ++i, ++index)
            (*vector)[index] -= (*subvector)[i] ;

        d->emitter_vector.setData(vector);

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerOperatorModifierPartSubstract::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vector.clearData();
    }
}

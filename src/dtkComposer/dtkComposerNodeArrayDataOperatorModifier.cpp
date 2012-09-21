/* dtkComposerNodeArrayDataOperatorModifier.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jul  5 09:37:40 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Sep 21 16:27:01 2012 (+0200)
 *           By: tkloczko
 *     Update #: 51
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitterVariant.h"
#include "dtkComposerNodeArrayDataOperatorModifier.h"

#include <dtkContainer/dtkAbstractContainerWrapper.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodeArrayDataOperatorModifier
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayDataOperatorModifierPrivate
{
public:
    dtkComposerTransmitterVariant receiver_array;
    dtkComposerTransmitterVariant receiver_index;
    dtkComposerTransmitterVariant receiver_item;

public:
    dtkComposerTransmitterVariant emitter_array;
};

dtkComposerNodeArrayDataOperatorModifier::dtkComposerNodeArrayDataOperatorModifier(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayDataOperatorModifierPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<int> variant_list;

    variant_list << QMetaType::LongLong;
    d->receiver_index.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_index);

    this->appendReceiver(&d->receiver_item);

    this->appendEmitter(&d->emitter_array);
}

dtkComposerNodeArrayDataOperatorModifier::~dtkComposerNodeArrayDataOperatorModifier(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodeArrayDataOperatorModifierAll
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayDataOperatorModifierAllPrivate
{
public:
    dtkComposerTransmitterVariant receiver_array;
    dtkComposerTransmitterVariant receiver_item;

public:
    dtkComposerTransmitterVariant emitter_array;
};

dtkComposerNodeArrayDataOperatorModifierAll::dtkComposerNodeArrayDataOperatorModifierAll(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayDataOperatorModifierAllPrivate)
{
    this->appendReceiver(&d->receiver_array);
    this->appendReceiver(&d->receiver_item);

    this->appendEmitter(&d->emitter_array);
}

dtkComposerNodeArrayDataOperatorModifierAll::~dtkComposerNodeArrayDataOperatorModifierAll(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperator - INSERT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayDataOperatorInsert::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_item.isEmpty() ) {

        dtkAbstractContainerWrapper *array = d->receiver_array.container();
        qlonglong index = *d->receiver_index.data<qlonglong>();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }
    
        if (array->isReset()) {
            dtkWarn() << "Input array is not valid. Nothing is done.";
            d->emitter_array.clearData();
            return;
        }

        if (index >= array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            array->insert(d->receiver_item.variant(), index);

        }
        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperator - Set
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayDataOperatorSet::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_item.isEmpty() ) {

        dtkAbstractContainerWrapper *array = d->receiver_array.container();
        qlonglong index = *d->receiver_index.data<qlonglong>();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }
    
        if (array->isReset()) {
            dtkWarn() << "Input array is not valid. Nothing is done.";
            d->emitter_array.clearData();
            return;
        }

        if (index >= array->count()) {
            dtkWarn() << "index > size of the vector. Same array is returned.";

        } else {
            array->replace(d->receiver_item.variant(), index);

        }
        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperator - APPEND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayDataOperatorAppend::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_item.isEmpty() ) {

        dtkAbstractContainerWrapper *array = d->receiver_array.container();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }
    
        if (array->isReset()) {
            dtkWarn() << "Input array is not valid. Nothing is done.";
            d->emitter_array.clearData();
            return;
        }

        array->append(d->receiver_item.variant());
        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperator - PREPEND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayDataOperatorPrepend::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_item.isEmpty() ) {

        dtkAbstractContainerWrapper *array = d->receiver_array.container();

        if (!array) {
            dtkError() << "Input array is not defined.";
            d->emitter_array.clearData();
            return;
        }
    
        if (array->isReset()) {
            dtkWarn() << "Input array is not valid. Nothing is done.";
            d->emitter_array.clearData();
            return;
        }

        array->prepend(d->receiver_item.variant());
        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_array.clearData();
    }
}

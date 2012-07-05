/* dtkComposerNodeArrayDataOperatorModifier.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jul  5 09:37:40 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jul  5 10:19:05 2012 (+0200)
 *           By: tkloczko
 *     Update #: 35
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

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong;
    d->receiver_index.setTypes(variant_list);
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

        dtkAbstractContainerWrapper array = d->receiver_array.container();
        qlonglong index = qvariant_cast<qlonglong>(d->receiver_index.data());
    
        if (array.isReset()) {
            dtkWarn() << "Input array is not valid. Nothing is done.";
            return;
        }

        if (index < array.count()) {
            array.insert(d->receiver_item.data(), index);
            d->emitter_array.setData(array);

        } else {
            dtkWarn() << "index > size of the vector. Nothing is done" ;
            dtkAbstractContainerWrapper array;
            d->emitter_array.setData(array);
        }

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkAbstractContainerWrapper array;
        d->emitter_array.setData(array);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperator - REPLACE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayDataOperatorReplace::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_item.isEmpty() ) {

        dtkAbstractContainerWrapper array = d->receiver_array.container();
        qlonglong index = qvariant_cast<qlonglong>(d->receiver_index.data());
    
        if (array.isReset()) {
            dtkWarn() << "Input array is not valid. Nothing is done.";
            return;
        }

        if (index < array.count()) {
            array.replace(d->receiver_item.data(), index);
            d->emitter_array.setData(array);

        } else {
            dtkWarn() << "index > size of the vector. Nothing is done" ;
            dtkAbstractContainerWrapper array;
            d->emitter_array.setData(array);
        }

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkAbstractContainerWrapper array;
        d->emitter_array.setData(array);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperator - APPEND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayDataOperatorAppend::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_item.isEmpty() ) {

        dtkAbstractContainerWrapper array = d->receiver_array.container();
    
        if (array.isReset()) {
            dtkWarn() << "Input array is not valid. Nothing is done.";
            return;
        }

        array.append(d->receiver_item.data());
        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkAbstractContainerWrapper array;
        d->emitter_array.setData(array);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataOperator - PREPEND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayDataOperatorPrepend::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_item.isEmpty() ) {

        dtkAbstractContainerWrapper array = d->receiver_array.container();
    
        if (array.isReset()) {
            dtkWarn() << "Input array is not valid. Nothing is done.";
            return;
        }

        array.prepend(d->receiver_item.data());
        d->emitter_array.setData(array);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        dtkAbstractContainerWrapper array;
        d->emitter_array.setData(array);
    }
}

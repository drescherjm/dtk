/* dtkComposerNodeArrayDataExtractor.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Jul  4 12:07:20 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2012 Wed Nov  7 17:40:35 (+0100)
 *           By: Thibaud Kloczko, Inria.
 *     Update #: 63
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeArrayDataExtractor.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkContainer/dtkAbstractContainerWrapper.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataExtractorPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayDataExtractorPrivate
{
public:
    dtkComposerTransmitterVariant               receiver_array;
    dtkComposerTransmitterReceiver<qlonglong>   receiver_index;

public:
    dtkComposerTransmitterVariant emitter_item;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataExtractor implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayDataExtractor::dtkComposerNodeArrayDataExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayDataExtractorPrivate)
{
    this->appendReceiver(&d->receiver_array);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_item);
}

dtkComposerNodeArrayDataExtractor::~dtkComposerNodeArrayDataExtractor(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeArrayDataExtractor::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "array";
        break;
    case 1:
        return "index";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeArrayDataExtractor::outputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "item";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeArrayDataExtractor::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_index.isEmpty()) {

        dtkAbstractContainerWrapper *array = d->receiver_array.container();
        qlonglong index = *d->receiver_index.data();

        if (!array) {
            dtkError() << "Input array is not defined.";
            return;
        }

        if (index >= array->count()) {
            dtkWarn() << "index " << index << " > size of the input array " << array->count() << ". Invalid QVariant is returned.";
            d->emitter_item.setData(QVariant());

        } else {
            d->emitter_item.setData(array->at(index));

        }

    } else {
        dtkWarn() << "Inputs not specified. Invalid QVariant is returned.";
        d->emitter_item.setData(QVariant());
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataExtractorSubArrayPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayDataExtractorSubArrayPrivate
{
public:
    dtkComposerTransmitterVariant receiver_array;
    dtkComposerTransmitterVariant receiver_indices;

public:
    dtkComposerTransmitterVariant emitter_subarray;

public:
    dtkAbstractContainerWrapper *subarray;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataExtractorSubArray implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayDataExtractorSubArray::dtkComposerNodeArrayDataExtractorSubArray(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayDataExtractorSubArrayPrivate)
{
    d->subarray = NULL;

    this->appendReceiver(&d->receiver_array);

    QList<int> variant_list;
    variant_list << QMetaType::Int << QMetaType::UInt << QMetaType::LongLong << QMetaType::ULongLong;
    d->receiver_indices.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_indices);

    this->appendEmitter(&d->emitter_subarray);
}

dtkComposerNodeArrayDataExtractorSubArray::~dtkComposerNodeArrayDataExtractorSubArray(void)
{
    if (d->subarray)
        delete d->subarray;
    d->subarray = NULL;

    delete d;

    d = NULL;
}

QString dtkComposerNodeArrayDataExtractorSubArray::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "array";
        break;
    case 1:
        return "index array";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeArrayDataExtractorSubArray::outputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "subarray";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeArrayDataExtractorSubArray::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_indices.isEmpty()) {

        dtkAbstractContainerWrapper *array   = d->receiver_array.container();
        dtkAbstractContainerWrapper *indices = d->receiver_indices.container();

        if (!array || !indices) {
            dtkError() << "Inputs are not defined.";
            d->emitter_subarray.clearData();
            return;
        }

        if (!d->subarray)
            d->subarray = array->voidClone();
        else
            d->subarray->clear();

        qlonglong index;
        for(qlonglong i = 0; i < indices->count(); ++i) {
            index = indices->at(i).value<qlonglong>();
            if (index >= array->count()) {
                dtkWarn() << "index " << i << " of indices array is greater than the size of the array. Zero is inserted.";
                d->subarray->append(QVariant());
            } else {
                d->subarray->append(array->at(index));
            }
        }
        d->emitter_subarray.setData(d->subarray);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_subarray.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataExtractorArrayPartPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayDataExtractorArrayPartPrivate
{
public:
    dtkComposerTransmitterVariant             receiver_array;
    dtkComposerTransmitterReceiver<qlonglong> receiver_from;
    dtkComposerTransmitterReceiver<qlonglong> receiver_length;

public:
    dtkComposerTransmitterVariant emitter_subarray;

public:
    dtkAbstractContainerWrapper *subarray;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataExtractorArrayPart implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayDataExtractorArrayPart::dtkComposerNodeArrayDataExtractorArrayPart(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayDataExtractorArrayPartPrivate)
{
    d->subarray = NULL;

    this->appendReceiver(&d->receiver_array);
    this->appendReceiver(&d->receiver_from);
    this->appendReceiver(&d->receiver_length);

    this->appendEmitter(&d->emitter_subarray);
}

dtkComposerNodeArrayDataExtractorArrayPart::~dtkComposerNodeArrayDataExtractorArrayPart(void)
{
    if (d->subarray)
        delete d->subarray;
    d->subarray = NULL;

    delete d;

    d = NULL;
}

QString dtkComposerNodeArrayDataExtractorArrayPart::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "array";
        break;
    case 1:
        return "from";
        break;
    case 2:
        return "length";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeArrayDataExtractorArrayPart::outputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "subarray";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeArrayDataExtractorArrayPart::run(void)
{
    if (!d->receiver_array.isEmpty() && !d->receiver_from.isEmpty()) {

        dtkAbstractContainerWrapper *array = d->receiver_array.container();

        if (!array) {
            dtkError() << "Inputs are not defined.";
            d->emitter_subarray.clearData();
            return;
        }

        if (array->isReset()) {
            dtkWarn() << "Input array is not valid. Nothing is done.";
            d->emitter_subarray.clearData();
            return;
        }

        qlonglong from = *d->receiver_from.data();
        if (from >= array->count()) {
            dtkWarn() << "Starting value from is greater than array size:" << from << ">=" << array->count();
            d->emitter_subarray.clearData();
            return;
        }

        qlonglong length = 0;
        if (!d->receiver_length.isEmpty())
            length = *d->receiver_length.data();
        
        if (length < 0) {
            dtkWarn() << "Length value is negative:" << length << "<" << 0;
            d->emitter_subarray.clearData();
            return;
        }

        qlonglong to = qMin((from + length), array->count());

        if (!d->subarray)
            d->subarray = array->voidClone();
        else
            d->subarray->clear();

        for (qlonglong i = from; i < to; ++i) {
            d->subarray->append(array->at(i));
        }
        d->emitter_subarray.setData(d->subarray);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_subarray.clearData();
    }
}

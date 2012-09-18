/* dtkComposerNodeArrayDataExtractor.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Jul  4 12:07:20 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jul  5 09:55:01 2012 (+0200)
 *           By: tkloczko
 *     Update #: 26
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeArrayDataExtractor.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkContainer/dtkAbstractContainerWrapper.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataExtractorPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayDataExtractorPrivate
{
public:
    dtkComposerTransmitterVariant receiver_array;
    dtkComposerTransmitterVariant receiver_index;

public:
    dtkComposerTransmitterVariant emitter_item;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataExtractor implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayDataExtractor::dtkComposerNodeArrayDataExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayDataExtractorPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;
    d->receiver_index.setTypes(variant_list);
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
    if (d->receiver_array.isEmpty())
        return;

    if (d->receiver_index.isEmpty())
        return;

    const dtkAbstractContainerWrapper& array(d->receiver_array.container());
    qlonglong index = qvariant_cast<qlonglong>(d->receiver_index.data());

    if (array.isReset()) {
        dtkWarn() << "Input array is not valid. Nothing is done.";
        return;
    }

    if (index < array.count())
        d->emitter_item.setData(array.at(index));

    else
        dtkWarn() << "index is larger than size of the array:" << index << ">=" << array.count();
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
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataExtractorSubArray implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayDataExtractorSubArray::dtkComposerNodeArrayDataExtractorSubArray(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayDataExtractorSubArrayPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double ;
    d->receiver_indices.setTypes(variant_list);
    this->appendReceiver(&d->receiver_indices);

    this->appendEmitter(&d->emitter_subarray);
}

dtkComposerNodeArrayDataExtractorSubArray::~dtkComposerNodeArrayDataExtractorSubArray(void)
{
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
    if (d->receiver_array.isEmpty())
        return;

    if (d->receiver_indices.isEmpty())
        return;

    const dtkAbstractContainerWrapper& array(d->receiver_array.container());
    const dtkAbstractContainerWrapper& indices(d->receiver_indices.container());

    if (array.isReset()) {
        dtkWarn() << "Input array is not valid. Nothing is done.";
        return;
    }

    dtkAbstractContainerWrapper *subarray = array.voidClone();

    for(qlonglong i = 0; i < indices.count(); ++i) {
        subarray->append(array.at(qvariant_cast<qlonglong>(indices.at(i))));
    }

    d->emitter_subarray.setData(*subarray);
    delete subarray;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataExtractorArrayPartPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayDataExtractorArrayPartPrivate
{
public:
    dtkComposerTransmitterVariant receiver_array;
    dtkComposerTransmitterVariant receiver_from;
    dtkComposerTransmitterVariant receiver_length;

public:
    dtkComposerTransmitterVariant emitter_subarray;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataExtractorArrayPart implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayDataExtractorArrayPart::dtkComposerNodeArrayDataExtractorArrayPart(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayDataExtractorArrayPartPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong;

    d->receiver_from.setTypes(variant_list);
    this->appendReceiver(&d->receiver_from);
    d->receiver_length.setTypes(variant_list);
    this->appendReceiver(&d->receiver_length);

    this->appendEmitter(&d->emitter_subarray);
}

dtkComposerNodeArrayDataExtractorArrayPart::~dtkComposerNodeArrayDataExtractorArrayPart(void)
{
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
    if (d->receiver_array.isEmpty())
        return;

    if (d->receiver_from.isEmpty())
        return;

    const dtkAbstractContainerWrapper& array(d->receiver_array.container());

    if (array.isReset()) {
        dtkWarn() << "Input array is not valid. Nothing is done.";
        return;
    }

    qlonglong from = qvariant_cast<qlonglong>(d->receiver_from.data());
    if (from >= array.count()) {
        dtkWarn() << "Starting value from is greater than array size:" << from << ">=" << array.count();
        return;
    }

    qlonglong length;
    if (!d->receiver_length.isEmpty())
        length = qvariant_cast<qlonglong>(d->receiver_length.data());

    if (length < 0) {
        dtkWarn() << "Length value is negative:" << length << "<" << 0;
        return;
    }

    qlonglong to = qMin((from + length), array.count());

    dtkAbstractContainerWrapper *subarray = array.voidClone();

    for (qlonglong i = from; i < to; ++i) {
        subarray->append(array.at(i));
    }

    d->emitter_subarray.setData(*subarray);
    delete subarray;
}

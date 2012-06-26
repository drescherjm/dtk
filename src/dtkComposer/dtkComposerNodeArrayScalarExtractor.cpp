/* dtkComposerNodeArrayScalarExtractor.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 26 16:32:03 2012 (+0200)
 *           By: tkloczko
 *     Update #: 144
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeArrayScalarExtractor.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkContainer/dtkContainerVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractorPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarExtractorPrivate
{
public:
    dtkComposerTransmitterReceiverVector<qreal> receiver_array;
    dtkComposerTransmitterVariant               receiver_index;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractor implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayScalarExtractor::dtkComposerNodeArrayScalarExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarExtractorPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;
    d->receiver_index.setTypes(variant_list);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeArrayScalarExtractor::~dtkComposerNodeArrayScalarExtractor(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeArrayScalarExtractor::inputLabelHint(int port)
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

QString dtkComposerNodeArrayScalarExtractor::outputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "value";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeArrayScalarExtractor::run(void)
{
    if (d->receiver_array.isEmpty())
        return;

    if (d->receiver_index.isEmpty())
        return;

    dtkContainerVectorReal& array(d->receiver_array.data());
    dtkxarch_int index = qvariant_cast<dtkxarch_int>(d->receiver_index.data());

    if (index < array.count())
        d->emitter_value.setData(array.at(index));

    else
        dtkWarn() << "index is larger than size of the array:" << index << ">=" << array.count();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractorSubArrayPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarExtractorSubArrayPrivate
{
public:
    dtkComposerTransmitterReceiverVector<qreal> receiver_array;
    dtkComposerTransmitterVariantContainer      receiver_indices;

public:
    dtkComposerTransmitterEmitterVector<qreal> emitter_subarray;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractorSubArray implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayScalarExtractorSubArray::dtkComposerNodeArrayScalarExtractorSubArray(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarExtractorSubArrayPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double ;
    d->receiver_indices.setTypes(variant_list);
    this->appendReceiver(&d->receiver_indices);

    this->appendEmitter(&d->emitter_subarray);
}

dtkComposerNodeArrayScalarExtractorSubArray::~dtkComposerNodeArrayScalarExtractorSubArray(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeArrayScalarExtractorSubArray::inputLabelHint(int port)
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

QString dtkComposerNodeArrayScalarExtractorSubArray::outputLabelHint(int port)
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

void dtkComposerNodeArrayScalarExtractorSubArray::run(void)
{
    if (d->receiver_array.isEmpty())
        return;

    if (d->receiver_indices.isEmpty())
        return;

    dtkContainerVectorReal&        array = d->receiver_array.data();
    dtkAbstractContainerWrapper& indices = d->receiver_indices.container();

    dtkContainerVectorReal subarray;
    subarray.reserve(indices.count());

    for(dtkxarch_int i = 0; i < indices.count(); ++i) {
        subarray.append(array.at(qvariant_cast<dtkxarch_int>(indices.at(i))));
    }

    d->emitter_subarray.setData(subarray);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractorArrayPartPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarExtractorArrayPartPrivate
{
public:
    dtkComposerTransmitterReceiverVector<qreal> receiver_array;
    dtkComposerTransmitterVariant               receiver_from;
    dtkComposerTransmitterVariant               receiver_length;

public:
    dtkComposerTransmitterEmitterVector<qreal> emitter_subarray;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractorArrayPart implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayScalarExtractorArrayPart::dtkComposerNodeArrayScalarExtractorArrayPart(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarExtractorArrayPartPrivate)
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

dtkComposerNodeArrayScalarExtractorArrayPart::~dtkComposerNodeArrayScalarExtractorArrayPart(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeArrayScalarExtractorArrayPart::inputLabelHint(int port)
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

QString dtkComposerNodeArrayScalarExtractorArrayPart::outputLabelHint(int port)
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

void dtkComposerNodeArrayScalarExtractorArrayPart::run(void)
{
    if (d->receiver_array.isEmpty())
        return;

    if (d->receiver_from.isEmpty())
        return;

    dtkContainerVectorReal& array = d->receiver_array.data();

    dtkxarch_int from = qvariant_cast<dtkxarch_int>(d->receiver_from.data());
    if (from >= array.count()) {
        dtkWarn() << "Starting value from is greater than array size:" << from << ">=" << array.count();
        return;
    }

    dtkxarch_int length;
    if (!d->receiver_length.isEmpty())
        length = qvariant_cast<dtkxarch_int>(d->receiver_length.data());

    if (length < 0) {
        dtkWarn() << "Length value is negative:" << length << "<" << 0;
        return;
    }

    dtkxarch_int to = qMin((from + length), array.count());
    
    dtkContainerVectorReal *subarray = array.subContainer(from, to);
    d->emitter_subarray.setData(*subarray);
    delete subarray;
}

/* dtkComposerNodeArrayScalarExtractor.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 26 10:05:00 2012 (+0200)
 *           By: tkloczko
 *     Update #: 96
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
//
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarExtractorPrivate
{
public:
    dtkComposerTransmitterReceiverVector<qreal> receiver_array;
    dtkComposerTransmitterVariant receiver_index;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_value;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayScalarExtractor::dtkComposerNodeArrayScalarExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarExtractorPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double ;
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
    if(d->receiver_array.isEmpty())
        return;

    if(d->receiver_index.isEmpty())
        return;

    dtkContainerVectorReal& array(d->receiver_array.data());
    qlonglong index = qvariant_cast<qreal>(d->receiver_index.data());

    if (index < array.count())
        d->emitter_value.setData(array.at(index));

    else
        dtkWarn() << "index is larger than size of the array:" << index << ">=" << array.count();
}

// /////////////////////////////////////////////////////////////////
//
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
//
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
    if(d->receiver_array.isEmpty())
        return;

    if(d->receiver_indices.isEmpty())
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

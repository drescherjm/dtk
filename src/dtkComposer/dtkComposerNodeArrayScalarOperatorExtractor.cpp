/* dtkComposerNodeArrayScalarOperatorExtractor.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun 15 09:51:39 2012 (+0200)
 *           By: sblekout
 *     Update #: 66
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeArrayScalarOperatorExtractor.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkContainer/dtkContainerVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarOperatorExtractorPrivate
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

dtkComposerNodeArrayScalarOperatorExtractor::dtkComposerNodeArrayScalarOperatorExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarOperatorExtractorPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double ;
    d->receiver_index.setTypes(variant_list);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeArrayScalarOperatorExtractor::~dtkComposerNodeArrayScalarOperatorExtractor(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeArrayScalarOperatorExtractor::inputLabelHint(int port)
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

QString dtkComposerNodeArrayScalarOperatorExtractor::outputLabelHint(int port)
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

void dtkComposerNodeArrayScalarOperatorExtractor::run(void)
{
    if(d->receiver_array.isEmpty())
        return;

    if(d->receiver_index.isEmpty())
        return;

    dtkContainerVectorReal& array(d->receiver_array.data());
    qlonglong index = qvariant_cast<qreal>(d->receiver_index.data());

    d->emitter_value.setData(array.at(index));
}

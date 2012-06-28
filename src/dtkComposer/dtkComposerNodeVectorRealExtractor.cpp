/* dtkComposerNodeVectorRealExtractor.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 26 16:10:51 2012 (+0200)
 *           By: tkloczko
 *     Update #: 70
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeVectorRealExtractor.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealExtractorPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector;
    dtkComposerTransmitterVariant receiver_index;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_value;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

dtkComposerNodeVectorRealExtractor::dtkComposerNodeVectorRealExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealExtractorPrivate)
{
    this->appendReceiver(&d->receiver_vector);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double ;
    d->receiver_index.setTypes(variant_list);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeVectorRealExtractor::~dtkComposerNodeVectorRealExtractor(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeVectorRealExtractor::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "vector";
        break;
    case 1:
        return "index";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeVectorRealExtractor::outputLabelHint(int port)
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

void dtkComposerNodeVectorRealExtractor::run(void)
{
    if(d->receiver_vector.isEmpty())
        return;

    if(d->receiver_index.isEmpty())
        return;

    dtkVectorReal& vector(d->receiver_vector.data());
    qlonglong index = qvariant_cast<qlonglong>(d->receiver_index.data());

    if (index < vector.getRows())
        d->emitter_value.setData(vector[index]);
    else
        dtkWarn() << "index is larger than size of the vector:" << index << ">=" << vector.getRows();
        
}

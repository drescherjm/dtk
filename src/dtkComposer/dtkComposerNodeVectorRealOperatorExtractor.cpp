/* dtkComposerNodeVectorRealOperatorExtractor.cpp ---
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

#include "dtkComposerNodeVectorRealOperatorExtractor.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorExtractorPrivate
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

dtkComposerNodeVectorRealOperatorExtractor::dtkComposerNodeVectorRealOperatorExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorExtractorPrivate)
{
    this->appendReceiver(&d->receiver_vector);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double ;
    d->receiver_index.setTypes(variant_list);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeVectorRealOperatorExtractor::~dtkComposerNodeVectorRealOperatorExtractor(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeVectorRealOperatorExtractor::inputLabelHint(int port)
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

QString dtkComposerNodeVectorRealOperatorExtractor::outputLabelHint(int port)
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

void dtkComposerNodeVectorRealOperatorExtractor::run(void)
{
    if(d->receiver_vector.isEmpty())
        return;

    if(d->receiver_index.isEmpty())
        return;

    dtkVectorReal& vector(d->receiver_vector.data());
    qlonglong index = qvariant_cast<qreal>(d->receiver_index.data());

    d->emitter_value.setData(vector[index]);
}

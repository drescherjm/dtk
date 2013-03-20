/* dtkComposerNodeVectorReal.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette Lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2013 Wed Jan  9 09:55:03 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 100
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeVectorReal.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal*> receiver_vector;
    dtkComposerTransmitterVariant                  receiver_size;
    dtkComposerTransmitterVariant                  receiver_value;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal*> emitter_vector;
    dtkComposerTransmitterEmitter<qlonglong>      emitter_size;

public:
    dtkVectorReal *vector;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorReal implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeVectorReal::dtkComposerNodeVectorReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealPrivate)
{
    d->vector = NULL;

    this->appendReceiver(&d->receiver_vector);

    QVector<const dtkComposerType*> variant_list;

    variant_list << dtkComposerTypeInfo<qlonglong>::type();
    d->receiver_size.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_size);

    variant_list << dtkComposerTypeInfo<double>::type();
    d->receiver_value.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_vector);

    this->appendEmitter(&d->emitter_size);
}

dtkComposerNodeVectorReal::~dtkComposerNodeVectorReal(void)
{
    if (d->vector)
        delete d->vector;
    d->vector = NULL;

    delete d;

    d = NULL;
}

QString dtkComposerNodeVectorReal::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "vector";
        break;
    case 1:
        return "size";
        break;
    case 2:
        return "value";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeVectorReal::outputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "vector";
        break;
    case 1:
        return "size";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeVectorReal::run(void)
{
    if (!d->receiver_vector.isEmpty()) {

        dtkVectorReal *vector = d->receiver_vector.constData();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorReal::" << Q_FUNC_INFO << "Input vector is not defined.";
            d->emitter_size.clearData();
            d->emitter_vector.clearData();
            return;
        }

        d->emitter_size.setData(vector->size());
        d->emitter_vector.setData(vector);

    } else {

        if (!d->vector)
            d->vector = new dtkVectorReal();

        qlonglong size = 0;
        if (!d->receiver_size.isEmpty())
            size = d->receiver_size.data<qlonglong>();

        if (size == 0) {
            d->vector->allocate(0);
            dtkWarn() << "dtkComposerNodeVectorReal::" << Q_FUNC_INFO << "The size of the vector is zero.";

        } else {        
            if (size != d->vector->size())
                d->vector->allocate(size);

            qreal value = 0.;
            if (!d->receiver_value.isEmpty())
                value = d->receiver_value.data<qreal>();

            d->vector->fill(value);
        }

        d->emitter_size.setData(size);
        d->emitter_vector.setData(d->vector);
    }
}

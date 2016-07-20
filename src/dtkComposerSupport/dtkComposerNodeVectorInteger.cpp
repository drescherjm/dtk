/* dtkComposerNodeVectorInteger.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette Lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 20 13:57:46 2012 (+0200)
 *           By: tkloczko
 *     Update #: 73
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeVectorInteger.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMathSupport/dtkVector>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorInteger>  receiver_vector;
    dtkComposerTransmitterVariant receiver_size;
    dtkComposerTransmitterVariant receiver_value;

public:
    dtkComposerTransmitterEmitter<dtkVectorInteger>   emitter_vector;
    dtkComposerTransmitterEmitter<qlonglong>       emitter_size;

public:
    dtkVectorInteger *vector;
    qlonglong size;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorInteger implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeVectorInteger::dtkComposerNodeVectorInteger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerPrivate)
{
    d->vector = NULL;
    d->size = 0;

    this->appendReceiver(&d->receiver_vector);

    QList<int> variant_list;

    variant_list << QMetaType::LongLong;
    d->receiver_size.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_size);

    variant_list << QMetaType::Double;
    d->receiver_value.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_vector);

    d->emitter_size.setData(&d->size);
    this->appendEmitter(&d->emitter_size);
}

dtkComposerNodeVectorInteger::~dtkComposerNodeVectorInteger(void)
{
    if (d->vector)
        delete d->vector;

    d->vector = NULL;

    delete d;

    d = NULL;
}

QString dtkComposerNodeVectorInteger::inputLabelHint(int port)
{
    switch (port) {
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

QString dtkComposerNodeVectorInteger::outputLabelHint(int port)
{
    switch (port) {
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

void dtkComposerNodeVectorInteger::run(void)
{
    if (!d->receiver_vector.isEmpty()) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        d->size = vector->size();

        d->emitter_vector.setData(vector);

    } else {

        if (!d->vector)
            d->vector = new dtkVectorInteger();

        if (!d->receiver_size.isEmpty())
            d->size = *d->receiver_size.data<qlonglong>();
        else
            d->size = 0;

        if (d->size == 0) {

            d->vector->allocate(0);

            dtkWarn() << "The size of the matrix is zero.";

        } else {

            if (d->size != d->vector->size())
                d->vector->allocate(d->size);

            qlonglong value = 0.;

            if (!d->receiver_value.isEmpty())
                value = *d->receiver_value.data<qlonglong>();

            d->vector->fill(value);
        }

        d->emitter_vector.setData(d->vector);
    }
}

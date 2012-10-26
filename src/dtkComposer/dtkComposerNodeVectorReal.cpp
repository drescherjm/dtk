/* dtkComposerNodeVectorReal.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette Lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Ven oct 26 21:38:07 2012 (+0200)
 *           By: Régis Duvigneau
 *     Update #: 82
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
    dtkComposerTransmitterReceiver<dtkVectorReal>  receiver_vector;
    dtkComposerTransmitterVariant receiver_size;
    dtkComposerTransmitterVariant receiver_value;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal>   emitter_vector;
    dtkComposerTransmitterEmitter<qlonglong>       emitter_size;

public:
    dtkVectorReal *vector;
    qlonglong size;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorReal implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeVectorReal::dtkComposerNodeVectorReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealPrivate)
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

        d->vector = d->receiver_vector.data();
        d->size = d->vector->size();

        if (!d->receiver_value.isEmpty()){
            qreal value = *d->receiver_value.data<qreal>();   
            d->vector->fill(value);
        }

        d->emitter_vector.setData(d->vector);

    } else {

        if (!d->vector)
            d->vector = new dtkVectorReal();

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

            qreal value = 0.;

            if (!d->receiver_value.isEmpty())
                value = *d->receiver_value.data<qreal>();

            d->vector->fill(value);
        }

        d->emitter_vector.setData(d->vector);
    }
}

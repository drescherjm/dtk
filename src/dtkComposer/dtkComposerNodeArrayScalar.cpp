/* dtkComposerNodeArrayScalar.cpp --- 
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Sep 18 13:15:36 2012 (+0200)
 *           By: tkloczko
 *     Update #: 107
 */

/* Commentary: 
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeArrayScalar.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkContainer/dtkContainerVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarPrivate
{
public:
    dtkComposerTransmitterReceiverVector<qreal> receiver_array;
    dtkComposerTransmitterVariant receiver_size;
    dtkComposerTransmitterVariant receiver_value;


public:
    dtkComposerTransmitterEmitterVector<qreal> emitter_array;
    dtkComposerTransmitterEmitter<qlonglong>   emitter_size;

public:
    dtkContainerVectorReal *array;
    qlonglong size;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalar implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayScalar::dtkComposerNodeArrayScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarPrivate)
{
    d->array = NULL;
    d->size = 0;

    this->appendReceiver(&d->receiver_array);

    QList<int> variant_list;

    variant_list << QMetaType::Int << QMetaType::UInt << QMetaType::LongLong << QMetaType::ULongLong;
    d->receiver_size.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_size);

    variant_list << QMetaType::Double;
    d->receiver_value.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    d->emitter_array.setData(d->array);
    this->appendEmitter(&d->emitter_array);

    d->emitter_size.setData(&d->size);
    this->appendEmitter(&d->emitter_size);
}

dtkComposerNodeArrayScalar::~dtkComposerNodeArrayScalar(void)
{
    delete d;
    
    d = NULL;
}

QString dtkComposerNodeArrayScalar::inputLabelHint(int port) 
{
    switch(port) {
    case 0:
        return "array";
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

QString dtkComposerNodeArrayScalar::outputLabelHint(int port)
{    
    switch(port) {
    case 0:
        return "array";
        break;
    case 1:
        return "size";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeArrayScalar::run(void)
{
    if (!d->receiver_array.isEmpty()) {

        d->array = d->receiver_array.data();
        d->size = d->array->count();

    } else {

        if (d->array)
            d->array->clear();
        else
            d->array = new dtkContainerVectorReal();  
        
        if (!d->receiver_size.isEmpty())
            d->size = *d->receiver_size.data<qlonglong>();

        if (d->size == 0) {
            dtkWarn() << "The size of the array is zero." ;

        } else {          

            d->array->reserve(d->size);
        
            qreal value;

            if (!d->receiver_value.isEmpty())
                value = *d->receiver_value.data<qreal>();

        for(int i = 0 ; i < d->size; i++)
            *(d->array) << value;

        }
    }

    d->emitter_array.setData(d->array);
}

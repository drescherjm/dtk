/* dtkComposerNodeArrayScalar.cpp --- 
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2012 Wed Dec 12 16:44:15 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 151
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
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalar implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayScalar::dtkComposerNodeArrayScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarPrivate)
{
    d->array = NULL;

    this->appendReceiver(&d->receiver_array);

    QVector<const dtkComposerType*> variant_list;

    variant_list << dtkComposerTypeInfo<int>::type() << dtkComposerTypeInfo<uint>::type() << dtkComposerTypeInfo<qlonglong>::type() << dtkComposerTypeInfo<qulonglong>::type();
    d->receiver_size.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_size);

    variant_list << dtkComposerTypeInfo<double>::type();
    d->receiver_value.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_array);
    this->appendEmitter(&d->emitter_size);
}

dtkComposerNodeArrayScalar::~dtkComposerNodeArrayScalar(void)
{
    if (d->array)
        delete d->array;
    d->array = NULL;

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
        qlonglong size = d->array->count();

        if (!d->receiver_value.isEmpty()){
            qreal value = d->receiver_value.data<qreal>();
            for(qlonglong i = 0 ; i < size; ++i)
                d->array->replace(i, value);
        }

        d->emitter_array.setData(d->array);        

    } else {

        if (!d->array)
            d->array = new dtkContainerVectorReal();  
        
        qlonglong size = -1;
        if (!d->receiver_size.isEmpty())
            size = d->receiver_size.data<qlonglong>();

        if (size == 0) {

            d->array->clear();
            
            dtkWarn() << "The size of the array is zero.";

        } else {

            d->array->resize(size);

            qreal value = 0.;

            if (!d->receiver_value.isEmpty())
                value = d->receiver_value.data<qreal>();

            for(qlonglong i = 0 ; i < size; ++i)
                d->array->replace(i, value);

        }
        d->emitter_size.setData(size);
        d->emitter_array.setData(d->array);
    }
}

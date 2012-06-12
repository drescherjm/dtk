/* dtkComposerNodeArrayScalar.cpp --- 
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jun 11 16:28:53 2012 (+0200)
 *           By: tkloczko
 *     Update #: 65
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
// 
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
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayScalar::dtkComposerNodeArrayScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong;
    d->receiver_size.setTypes(variant_list);
    this->appendReceiver(&d->receiver_size);

    variant_list << QVariant::Double;
    d->receiver_value.setTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_array);
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

        dtkContainerVectorReal array(d->receiver_array.data());

        //this->releaseReceivers();

        d->emitter_array.setData(array);
        d->emitter_size.setData(array.count());

    } else {

        qlonglong size = 0;
        qreal value = 0;
        dtkContainerVector<qreal> array;

        if (!d->receiver_size.isEmpty())
            size = qvariant_cast<qlonglong>(d->receiver_size.data());

        if (size == 0) {
            dtkWarn() << "The size of the array is zero." ;
            //this->releaseReceivers();

        } else {

            array.reserve(size);

            if (!d->receiver_value.isEmpty())
                value = qvariant_cast<qreal>(d->receiver_value.data());

            //this->releaseReceivers();

            for(int i = 0 ; i < size; i++)
                array << value;
        }

        d->emitter_array.setData(array);
        d->emitter_size.setData(size);

    }
}

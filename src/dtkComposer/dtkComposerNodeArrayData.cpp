/* dtkComposerNodeArrayData.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Jul  4 11:47:12 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jul  5 10:26:42 2012 (+0200)
 *           By: tkloczko
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeArrayData.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkContainer/dtkAbstractContainerWrapper.h>
#include <dtkContainer/dtkContainerVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayDataPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayDataPrivate
{
public:
    dtkComposerTransmitterVariant receiver_array;
    dtkComposerTransmitterVariant receiver_size;
    dtkComposerTransmitterVariant receiver_value;


public:
    dtkComposerTransmitterVariant            emitter_array;
    dtkComposerTransmitterEmitter<qlonglong> emitter_size;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayData implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayData::dtkComposerNodeArrayData(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayDataPrivate)
{
    this->appendReceiver(&d->receiver_array);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong;
    d->receiver_size.setTypes(variant_list);
    this->appendReceiver(&d->receiver_size);

    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_array);
    this->appendEmitter(&d->emitter_size);
}

dtkComposerNodeArrayData::~dtkComposerNodeArrayData(void)
{
    delete d;
    
    d = NULL;
}

QString dtkComposerNodeArrayData::inputLabelHint(int port) 
{
    switch(port) {
    case 0:
        return "array";
        break;
    case 1:
        return "size";
        break;
    case 2:
        return "item";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeArrayData::outputLabelHint(int port)
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

void dtkComposerNodeArrayData::run(void)
{
    if (!d->receiver_array.isEmpty()) {

        const dtkAbstractContainerWrapper& array = d->receiver_array.container();

        if (array.isReset()) {
            dtkWarn() << "Input array is not valid. Nothing is done.";
            return;
        }        

        d->emitter_array.setData(array);
        d->emitter_size.setData(array.count());

    } else {

        qlonglong size = 0;
        dtkContainerVector<QVariant> array;

        if (!d->receiver_size.isEmpty())
            size = qvariant_cast<qlonglong>(d->receiver_size.data());

        if (size == 0) {
            dtkWarn() << "The size of the array is zero." ;

        } else {

            array.reserve(size);

            dtkInfo() << "A dtkContainerVector of QVariant has been created.";

            if (!d->receiver_value.isEmpty()) {
                for(qlonglong i = 0 ; i < size; ++i) {
                    array << d->receiver_value.data();
                }
            }
        }

        d->emitter_array.setData(dtkContainerVectorWrapper<QVariant>(array));
        d->emitter_size.setData(size);

    }
}

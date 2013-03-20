/* dtkComposerNodeArrayData.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Jul  4 11:47:12 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2012 Wed Dec 12 15:24:34 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 68
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeArrayData.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
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
    dtkComposerTransmitterVariant             receiver_array;
    dtkComposerTransmitterReceiver<qlonglong> receiver_size;
    dtkComposerTransmitterVariant             receiver_value;


public:
    dtkComposerTransmitterVariant            emitter_array;
    dtkComposerTransmitterEmitter<qlonglong> emitter_size;

public:
    dtkAbstractContainerWrapper *container;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayData implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayData::dtkComposerNodeArrayData(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayDataPrivate)
{
    d->container = NULL;

    this->appendReceiver(&d->receiver_array);
    this->appendReceiver(&d->receiver_size);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_array);
    this->appendEmitter(&d->emitter_size);
}

dtkComposerNodeArrayData::~dtkComposerNodeArrayData(void)
{
    if (d->container)
        delete d->container;
    d->container = NULL;

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

        dtkAbstractContainerWrapper* array = d->receiver_array.container();

        if (!array || array->isReset()) {
            d->emitter_array.clearData();
            dtkWarn() << "Input array is not valid. Nothing is done.";
            return;
        }

        d->emitter_size.setData(array->count());
        d->emitter_array.setData(array);

    } else {

        if (!d->container) {
            dtkContainerVector<QVariant> *array = new dtkContainerVector<QVariant>();
            d->container = new dtkContainerVectorWrapper<QVariant>(array);
        }  
        
        qlonglong size = -1;
        if (!d->receiver_size.isEmpty())
            size = d->receiver_size.data();

        if (size == 0) {
            d->container->clear();            
            dtkWarn() << "The size of the array is zero.";

        } else {
            dtkInfo() << "A dtkContainerVector of QVariant has been created.";

            d->container->clear();
            d->container->resize(size);
            if (!d->receiver_value.isEmpty()) {
                for(qlonglong i = 0 ; i < size; ++i) {
                    d->container->replace(d->receiver_value.variant(), i);
                }
            }

        }

        d->emitter_size.setData(size);
        d->emitter_array.setData(d->container);
    }
}

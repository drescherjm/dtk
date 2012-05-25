/* dtkComposerNodeArrayScalar.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 24 12:15:54 2012 (+0200)
 *           By: tkloczko
 *     Update #: 41
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

#include <dtkCore/dtkContainerVector.h>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<qreal>     receiver_array;
    dtkComposerTransmitterReceiver<qlonglong> receiver_size;
    dtkComposerTransmitterReceiver<qreal>     receiver_value;

public:
    dtkComposerTransmitterEmitter<qreal>     emitter_array;
    dtkComposerTransmitterEmitter<qlonglong> emitter_size;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkComposerNodeArrayScalar::dtkComposerNodeArrayScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarPrivate)
{
    this->appendReceiver(&d->receiver_array);
    this->appendReceiver(&d->receiver_size);
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

        dtkContainerVectorReal array(d->receiver_array.vector());

        d->emitter_array.setVector(array);
        d->emitter_size.setData(array.count());

    } else {

        qlonglong size = 0;
        qreal value = 0;        

        if (!d->receiver_size.isEmpty()) {            
            size = d->receiver_size.data();
            if (!d->receiver_value.isEmpty())
                value = d->receiver_value.data();
        }

        QVector<qreal> array(size, value);

        //d->emitter_array.setVector(dtkContainerVectorReal(array));
        d->emitter_size.setData(size);
    }
}

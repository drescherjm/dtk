/* dtkComposerNodeMetaScalarArrayAppend.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Jul 13 16:06:48 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Oct 17 11:55:41 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 34
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeMetaScalarArrayAppend.h"

#include <dtkComposer/dtkComposerTransmitterEmitter.h>
#include <dtkComposer/dtkComposerTransmitterReceiver.h>

#include <dtkContainer/dtkAbstractContainerWrapper.h>
#include <dtkContainer/dtkContainerVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArrayAppendPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaScalarArrayAppendPrivate
{
public:
    dtkComposerTransmitterReceiverVector<dtkContainerVector<qreal> > receiver_arrays;
    dtkComposerTransmitterReceiverVector<qreal> receiver_array;

    dtkComposerTransmitterEmitterVector<dtkContainerVector<qreal> > emitter_arrays;

    dtkContainerVector<dtkContainerVector<qreal> > *arrays;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArrayAppend implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaScalarArrayAppend::dtkComposerNodeMetaScalarArrayAppend(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaScalarArrayAppendPrivate)
{
    this->appendReceiver(&d->receiver_arrays);
    this->appendReceiver(&d->receiver_array);

    this->appendEmitter(&d->emitter_arrays);
}

dtkComposerNodeMetaScalarArrayAppend::~dtkComposerNodeMetaScalarArrayAppend(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeMetaScalarArrayAppend::run(void)
{

    if (d->receiver_arrays.isEmpty())
        return;

    if (d->receiver_array.isEmpty())
        return;

    d->arrays = d->receiver_arrays.data();

    d->arrays->append((*(d->receiver_array.data())));

    d->emitter_arrays.setData(d->arrays);
}

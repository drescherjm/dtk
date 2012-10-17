// dtkComposerNodeMetaScalarArrayReplace.cpp --- 
// 
// Author: Régis Duvigneau
// Copyright (C) 2008 - Regis Duvigneau, Inria.
// Created: Thu Jul 19 10:28:54 2012 (+0200)
// Version: $Id$
// Last-Updated: Wed Oct 17 12:02:27 2012 (+0200)
//           By: Julien Wintz
//     Update #: 19
// 

// Commentary: 
// 
// 

// Change log:
// 
// 

#include "dtkComposerNodeMetaScalarArrayReplace.h"

#include <dtkComposer/dtkComposerTransmitterEmitter.h>
#include <dtkComposer/dtkComposerTransmitterReceiver.h>

#include <dtkContainer/dtkAbstractContainerWrapper.h>
#include <dtkContainer/dtkContainerVector.h>

#include <dtkMath/dtkVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArrayReplacePrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaScalarArrayReplacePrivate
{
public:
    dtkComposerTransmitterReceiverVector< dtkContainerVector<qreal> > receiver_arrays;
    dtkComposerTransmitterReceiver< dtkVector<qreal> > receiver_vector;
    dtkComposerTransmitterReceiver<dtkxarch_int> receiver_index;

    dtkComposerTransmitterEmitterVector< dtkContainerVector<qreal> > emitter_arrays;

    dtkContainerVector<dtkContainerVector<qreal> > arrays;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArrayReplace implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaScalarArrayReplace::dtkComposerNodeMetaScalarArrayReplace(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaScalarArrayReplacePrivate)
{
    this->appendReceiver(&d->receiver_arrays);
    this->appendReceiver(&d->receiver_vector);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_arrays);
}

dtkComposerNodeMetaScalarArrayReplace::~dtkComposerNodeMetaScalarArrayReplace(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeMetaScalarArrayReplace::run(void)
{
    if (d->receiver_arrays.isEmpty())
        return;

    if (d->receiver_vector.isEmpty())
        return;

    if (d->receiver_index.isEmpty())
        return;

    d->arrays = dtkContainerVector<dtkContainerVector<qreal> >((*(d->receiver_arrays.data())));

    dtkxarch_int size = d->arrays.count();
    dtkxarch_int index = (*(d->receiver_index.data()));

    for (int i=0; i<size; i++)
        (d->arrays[i])[index] = (*(d->receiver_vector.data()))[i];
    
    d->emitter_arrays.setData(&(d->arrays));
}

// dtkComposerNodeMetaScalarArrayExtractor.cpp --- 
// 
// Author: Régis Duvigneau
// Copyright (C) 2008 - Regis Duvigneau, Inria.
// Created: Thu Jul 19 11:27:24 2012 (+0200)
// Version: $Id$
// Last-Updated: Wed Oct 17 11:57:51 2012 (+0200)
//           By: Julien Wintz
//     Update #: 18
// 

// Commentary: 
// 
// 

// Change log:
// 
// 

#include "dtkComposerNodeMetaScalarArrayExtractor.h"

#include <dtkComposer/dtkComposerTransmitterEmitter.h>
#include <dtkComposer/dtkComposerTransmitterReceiver.h>

#include <dtkContainer/dtkAbstractContainerWrapper.h>
#include <dtkContainer/dtkContainerVector.h>

#include <dtkMath/dtkVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArrayExtractorPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaScalarArrayExtractorPrivate
{
public:
    dtkComposerTransmitterReceiverVector< dtkContainerVector<qreal> > receiver_arrays;
    dtkComposerTransmitterReceiver<dtkxarch_int> receiver_index;

    dtkComposerTransmitterEmitterVector<qreal> emitter_array;

    dtkContainerVector<qreal> array;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArrayExtractor implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaScalarArrayExtractor::dtkComposerNodeMetaScalarArrayExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaScalarArrayExtractorPrivate)
{
    this->appendReceiver(&d->receiver_arrays);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_array);
}

dtkComposerNodeMetaScalarArrayExtractor::~dtkComposerNodeMetaScalarArrayExtractor(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeMetaScalarArrayExtractor::run(void)
{
    if (d->receiver_arrays.isEmpty())
        return;

    if (d->receiver_index.isEmpty())
        return;

    long long index = (long long)(d->receiver_index.data());

    d->array = (*(d->receiver_arrays.data()))[index];

    d->emitter_array.setData(&(d->array));
}

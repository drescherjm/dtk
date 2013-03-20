// dtkComposerNodeMetaScalarArrayExtractor.cpp --- 
// 
// Author: Régis Duvigneau
// Copyright (C) 2008 - Regis Duvigneau, Inria.
// Created: Thu Jul 19 11:27:24 2012 (+0200)
// Version: $Id$
// Last-Updated: 2012 Wed Dec 12 16:57:27 (+0100)
//           By: Thibaud Kloczko
//     Update #: 24
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
    dtkComposerTransmitterReceiverVector< dtkContainerVector<qreal> *> receiver_arrays;
    dtkComposerTransmitterReceiver<qlonglong> receiver_index;

    dtkComposerTransmitterEmitterVector<qreal> emitter_array;

    dtkContainerVector<qreal> *array;
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

    qlonglong index = d->receiver_index.data();

    d->array = (*(d->receiver_arrays.data()))[index];

    d->emitter_array.setData(d->array);
}

// dtkComposerNodeMetaScalarArrayExtractor.cpp --- 
// 
// Author: Régis Duvigneau
// Copyright (C) 2008 - Regis Duvigneau, Inria.
// Created: Thu Jul 19 11:27:24 2012 (+0200)
// Version: $Id$
// Last-Updated: mar. févr.  4 17:40:38 2014 (+0100)
//           By: Nicolas Niclausse
//     Update #: 25
// 

// Commentary: 
// 
// 

// Change log:
// 
// 

#include "dtkComposerNodeMetaScalarArrayExtractor.h"

#include <dtkComposerTransmitterEmitter.h>
#include <dtkComposerTransmitterReceiver.h>

#include <dtkContainerSupport/dtkAbstractContainerWrapper.h>
#include <dtkContainerSupport/dtkContainerVector.h>

#include <dtkMathSupport/dtkVector.h>

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

    qlonglong index = *d->receiver_index.data();

    d->array = (*(d->receiver_arrays.data()))[index];

    d->emitter_array.setData(d->array);
}

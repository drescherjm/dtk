// dtkComposerNodeMetaVector3DArrayAppend.cpp --- 
// 
// Author: Jeremie Labroquere
// Copyright (C) 2011 - Jeremie Labroquere, Inria.
// Created: Mon Aug  6 15:26:10 2012 (+0200)
// Version: $Id$
// Last-Updated: Wed Oct 17 12:23:51 2012 (+0200)
//           By: Julien Wintz
//     Update #: 11
// 

// Commentary: 
// 
// 

// Change log:
// 
// 

#include "dtkComposerNodeMetaVector3DArrayAppend.h"

#include <dtkComposer/dtkComposerTransmitterEmitter.h>
#include <dtkComposer/dtkComposerTransmitterReceiver.h>

#include <dtkContainer/dtkAbstractContainerWrapper.h>
#include <dtkContainer/dtkContainerVector.h>

// #include <dtkMath/dtkVector.h>
#include <dtkMath/dtkVector3D.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaVector3DArrayAppendPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaVector3DArrayAppendPrivate
{
public:
    dtkComposerTransmitterReceiverVector<dtkContainerVector<dtkVector3DReal> > receiver_arrays;
    dtkComposerTransmitterReceiverVector<dtkVector3DReal> receiver_array;

    dtkComposerTransmitterEmitterVector<dtkContainerVector<dtkVector3DReal> > emitter_arrays;

    dtkContainerVector<dtkContainerVector<dtkVector3DReal> > *arrays;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaVector3DArrayAppend implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaVector3DArrayAppend::dtkComposerNodeMetaVector3DArrayAppend(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaVector3DArrayAppendPrivate)
{
    this->appendReceiver(&d->receiver_arrays);
    this->appendReceiver(&d->receiver_array);

    this->appendEmitter(&d->emitter_arrays);
}

dtkComposerNodeMetaVector3DArrayAppend::~dtkComposerNodeMetaVector3DArrayAppend(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeMetaVector3DArrayAppend::run(void)
{

    if (d->receiver_arrays.isEmpty())
        return;

    if (d->receiver_array.isEmpty())
        return;

    d->arrays = d->receiver_arrays.data();

    d->arrays->append((*(d->receiver_array.data())));

    d->emitter_arrays.setData(d->arrays);
}

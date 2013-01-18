// dtkComposerNodeMetaVectorArray.cpp --- 
// 
// Author: Jeremie Labroquere
// Copyright (C) 2011 - Jeremie Labroquere, Inria.
// Created: Mon Aug  6 14:29:10 2012 (+0200)
// Version: $Id$
// Last-Updated: Wed Oct 17 11:37:25 2012 (+0200)
//           By: Julien Wintz
//     Update #: 6
// 

// Commentary: 
// 
// 

// Change log:
// 
// 

#include "dtkComposerNodeMetaVector3DArray.h"

#include <dtkComposer/dtkComposerTransmitterEmitter.h>

#include <dtkContainer/dtkAbstractContainerWrapper.h>
#include <dtkContainer/dtkContainerVector.h>

#include <dtkMath/dtkVector3D.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaVector3DArrayPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaVector3DArrayPrivate
{
public:
    dtkComposerTransmitterEmitterVector< dtkContainerVector<dtkVector3DReal*> *> emitter_arrays;

    dtkContainerVector< dtkContainerVector<dtkVector3DReal*> *> arrays;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaVector3DArray implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaVector3DArray::dtkComposerNodeMetaVector3DArray(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaVector3DArrayPrivate)
{
    d->emitter_arrays.setData(&d->arrays);

    this->appendEmitter(&d->emitter_arrays);
}

dtkComposerNodeMetaVector3DArray::~dtkComposerNodeMetaVector3DArray(void)
{
    delete d;
    
    d = NULL;
}

QString dtkComposerNodeMetaVector3DArray::outputLabelHint(int port)
{    
    switch(port) {
    case 0:
        return "arrays";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeMetaVector3DArray::run(void)
{
    d->arrays.clear();
}

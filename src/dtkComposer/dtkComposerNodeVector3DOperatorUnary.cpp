/* dtkComposerNodeVector3DOperatorUnary.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 15:58:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 27 17:57:57 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeVector3D.h"
#include "dtkComposerNodeVector3DOperatorUnary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorUnary 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_vec;

public:
    dtkComposerTransmitterEmitter<dtkVector3DReal> emitter_vec;
};

dtkComposerNodeVector3DOperatorUnary::dtkComposerNodeVector3DOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorUnaryPrivate)
{
    this->appendReceiver(&d->receiver_vec);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVector3DOperatorUnary::~dtkComposerNodeVector3DOperatorUnary(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorUnaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorUnaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_vec;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_val;
};

dtkComposerNodeVector3DOperatorUnaryScalar::dtkComposerNodeVector3DOperatorUnaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorUnaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_vec);
    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeVector3DOperatorUnaryScalar::~dtkComposerNodeVector3DOperatorUnaryScalar(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorUnary - UNITARY
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorUnaryUnitary::run(void)
{
    if (d->receiver_vec.isEmpty()) {
        dtkWarn() << "Input not specified. Nothing is done";
        this->releaseReceivers();
        d->emitter_vec.setData(dtkVector3DReal());

    }  else {
        this->releaseReceivers();
        d->emitter_vec.setData(d->receiver_vec.data().unit());
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorUnaryScalar - NORM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorUnaryScalarNorm::run(void)
{

    if (d->receiver_vec.isEmpty()) {
        dtkWarn() << "Input not specified. Nothing is done";
        this->releaseReceivers();
        d->emitter_val.setData(qreal());

    }  else {
        this->releaseReceivers();
        d->emitter_val.setData(d->receiver_vec.data().norm());
    }
}


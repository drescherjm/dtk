/* dtkComposerNodeVector3DOperatorTernary.cpp --- 
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 16:58:34 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 27 14:49:34 2012 (+0200)
 *           By: tkloczko
 *     Update #: 10
 */

/* Commentary: 
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeVector3D.h"
#include "dtkComposerNodeVector3DOperatorTernary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkLog/dtkLog>

#include <dtkMath/dtkMath.tpp>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorTernary 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorTernaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_0;
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_1;
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_2;

public:
    dtkComposerTransmitterEmitter<dtkVector3DReal> emitter_vec;
};

dtkComposerNodeVector3DOperatorTernary::dtkComposerNodeVector3DOperatorTernary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorTernaryPrivate)
{
    this->appendReceiver(&d->receiver_0);
    this->appendReceiver(&d->receiver_1);
    this->appendReceiver(&d->receiver_2);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVector3DOperatorTernary::~dtkComposerNodeVector3DOperatorTernary(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorTernaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorTernaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_0;
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_1;
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_2;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_val;
};

dtkComposerNodeVector3DOperatorTernaryScalar::dtkComposerNodeVector3DOperatorTernaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorTernaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_0);
    this->appendReceiver(&d->receiver_1);
    this->appendReceiver(&d->receiver_2);
    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeVector3DOperatorTernaryScalar::~dtkComposerNodeVector3DOperatorTernaryScalar(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorTernary - Vector Triple Prod
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorTernaryTripleProd::run(void)
{
    if (d->receiver_0.isEmpty() || d->receiver_1.isEmpty() || d->receiver_2.isEmpty()){
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vec.setData(dtkVector3DReal());


    } else {
        dtkVector3DReal& vector1 = d->receiver_0.data();
        dtkVector3DReal& vector2 = d->receiver_1.data();
        dtkVector3DReal& vector3 = d->receiver_2.data();

        d->emitter_vec.setData(vector1 % (vector2 % vector3));
    }
}
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorTernaryScalar - Mixed Prod
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorTernaryScalarMixedProd::run(void)
{
    if (d->receiver_0.isEmpty() || d->receiver_1.isEmpty() || d->receiver_2.isEmpty()){
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_val.setData(qreal());

    }   else {
        dtkVector3DReal& vector1 = d->receiver_0.data();
        dtkVector3DReal& vector2 = d->receiver_1.data();
        dtkVector3DReal& vector3 = d->receiver_2.data();

        d->emitter_val.setData(dtkMixedProduct(vector1, vector2, vector3));
    }
}

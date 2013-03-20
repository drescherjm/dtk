/* dtkComposerNodeVector3DOperatorTernary.cpp --- 
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 16:58:34 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2013 Mon Jan  7 12:17:09 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 26
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
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_0;
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_1;
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_2;

public:
    dtkComposerTransmitterEmitter<dtkVector3DReal*> emitter_vec;

public:
    dtkVector3DReal *vector;
};

dtkComposerNodeVector3DOperatorTernary::dtkComposerNodeVector3DOperatorTernary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorTernaryPrivate)
{
    d->vector = NULL;

    this->appendReceiver(&d->receiver_0);
    this->appendReceiver(&d->receiver_1);
    this->appendReceiver(&d->receiver_2);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVector3DOperatorTernary::~dtkComposerNodeVector3DOperatorTernary(void)
{
    if (d->vector)
        delete d->vector;

    d->vector = NULL;

    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorTernaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorTernaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_0;
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_1;
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_2;

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
        dtkWarn() << "dtkComposerNodeVector3DOperatorTernaryTripleProd::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_vec.clearData();

    } else {
        const dtkVector3DReal *vector1 = d->receiver_0.constData();
        const dtkVector3DReal *vector2 = d->receiver_1.constData();
        const dtkVector3DReal *vector3 = d->receiver_2.constData();

        if (!vector1 || !vector2 || !vector3) {
            dtkError() << "dtkComposerNodeVector3DOperatorTernaryTripleProd::" << Q_FUNC_INFO << "Input vectors not set. Nothing is done";
            d->emitter_vec.clearData();
            return;
        }

        if (!d->vector) {
            d->vector = new dtkVector3DReal(0., 0., 0.);
        }

        *d->vector = (*vector1) % ((*vector2) % (*vector3));
        d->emitter_vec.setData(d->vector);
    }
}
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorTernaryScalar - Mixed Prod
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorTernaryScalarMixedProd::run(void)
{
    if (d->receiver_0.isEmpty() || d->receiver_1.isEmpty() || d->receiver_2.isEmpty()){
        dtkWarn() << "dtkComposerNodeVector3DOperatorTernaryScalarMixedProd::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_val.clearData();
        
    }   else {
        dtkVector3DReal *vector1 = d->receiver_0.data();
        dtkVector3DReal *vector2 = d->receiver_1.data();
        dtkVector3DReal *vector3 = d->receiver_2.data();

        if (!vector1 || !vector2 || !vector3) {
            dtkError() << "dtkComposerNodeVector3DOperatorTernaryScalarMixedProd::" << Q_FUNC_INFO << "Input vectors not set. Nothing is done";
            d->emitter_val.clearData();
            return;
        }

        d->emitter_val.setData( dtkMixedProduct(*vector1, *vector2, *vector3) );
    }
}

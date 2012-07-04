/* dtkComposerNodeVector3DOperatorBinary.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 16:15:40 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 28 17:18:23 2012 (+0200)
 *           By: tkloczko
 *     Update #: 43
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeVector3D.h"
#include "dtkComposerNodeVector3DOperatorBinary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<dtkVector3DReal> emitter_vec;
};

dtkComposerNodeVector3DOperatorBinary::dtkComposerNodeVector3DOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorBinaryPrivate)
{
    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVector3DOperatorBinary::~dtkComposerNodeVector3DOperatorBinary(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorBinaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorBinaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_val;
};

dtkComposerNodeVector3DOperatorBinaryScalar::dtkComposerNodeVector3DOperatorBinaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorBinaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);
    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeVector3DOperatorBinaryScalar::~dtkComposerNodeVector3DOperatorBinaryScalar(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorHomothetic
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DOperatorHomotheticPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_vec;
    dtkComposerTransmitterVariant                   receiver_val;

public:
    dtkComposerTransmitterEmitter<dtkVector3DReal>  emitter_vec;
};

dtkComposerNodeVector3DOperatorHomothetic::dtkComposerNodeVector3DOperatorHomothetic(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DOperatorHomotheticPrivate)
{
    this->appendReceiver(&d->receiver_vec);
    this->appendReceiver(&d->receiver_val);
    this->appendEmitter(&d->emitter_vec);
}

dtkComposerNodeVector3DOperatorHomothetic::~dtkComposerNodeVector3DOperatorHomothetic(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorBinary - SUM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorBinarySum::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vec.setData(dtkVector3DReal());

    } else {
        d->emitter_vec.setData(d->receiver_lhs.data() + d->receiver_rhs.data());

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorBinary - SUBSTRACT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorBinarySubstract::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vec.setData(dtkVector3DReal());

    } else {
        d->emitter_vec.setData(d->receiver_lhs.data() - d->receiver_rhs.data());

    }
}
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorBinary - CROSS PROD
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorBinaryCrossProd::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vec.setData(dtkVector3DReal());

    } else {
        d->emitter_vec.setData(d->receiver_lhs.data() % d->receiver_rhs.data());

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorBinaryScalar - DOT PROD
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorBinaryScalarDotProd::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_val.setData(qreal());

    } else {
        d->emitter_val.setData(d->receiver_lhs.data() * d->receiver_rhs.data());

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorHomothetic - MULTIPLICATION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorHomotheticMult::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()){
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vec.setData(dtkVector3DReal());


    } else {
        d->emitter_vec.setData(d->receiver_vec.data() * qvariant_cast<qreal>(d->receiver_val.data()));

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVector3DOperatorHomothetic - DIVISION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVector3DOperatorHomotheticDivision::run(void)
{
    if (d->receiver_vec.isEmpty() || d->receiver_val.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vec.setData(dtkVector3DReal());


    } else {
        qreal value = qvariant_cast<qreal>(d->receiver_val.data());

        if (value != 0 ) {
            d->emitter_vec.setData(d->receiver_vec.data() / value);

        } else {
            dtkWarn() << "You divide by zero. Nothing is done" ;
            d->emitter_vec.setData(d->receiver_vec.data());

        }
    }
}

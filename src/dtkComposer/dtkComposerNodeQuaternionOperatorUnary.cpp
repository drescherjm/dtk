/* dtkComposerNodeQuaternionOperatorUnary.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 14:22:58 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2013 Tue Jan  8 09:33:34 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeQuaternion.h"
#include "dtkComposerNodeQuaternionOperatorUnary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnary 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeQuaternionOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkQuaternionReal*> receiver_quat;

public:
    dtkComposerTransmitterEmitter<dtkQuaternionReal*> emitter_quat;
};

dtkComposerNodeQuaternionOperatorUnary::dtkComposerNodeQuaternionOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeQuaternionOperatorUnaryPrivate)
{
    this->appendReceiver(&d->receiver_quat);
    this->appendEmitter(&d->emitter_quat);
}

dtkComposerNodeQuaternionOperatorUnary::~dtkComposerNodeQuaternionOperatorUnary(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeQuaternionOperatorUnaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkQuaternionReal*> receiver_quat;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_val;

public:
    qreal value;
};

dtkComposerNodeQuaternionOperatorUnaryScalar::dtkComposerNodeQuaternionOperatorUnaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeQuaternionOperatorUnaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_quat);

    d->value = 0.;
    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeQuaternionOperatorUnaryScalar::~dtkComposerNodeQuaternionOperatorUnaryScalar(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnary - UNITARY
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorUnaryUnitary::run(void)
{
    if (!d->receiver_quat.isEmpty()) {

        dtkQuaternionReal *quat = d->receiver_quat.data();

        if (!quat) {
            dtkError() << "dtkComposerNodeQuaternionOperatorUnaryUnitary::" << Q_FUNC_INFO << "Input quaternion not set. Nothing is done";
            d->emitter_quat.clearData();
            return;
        }

        quat->makeUnit();

        d->emitter_quat.setData(quat);        

    }  else {
        dtkWarn() << "dtkComposerNodeQuaternionOperatorUnaryUnitary::" << Q_FUNC_INFO << "Input not specified. Nothing is done";
        d->emitter_quat.clearData();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorUnaryScalar - NORM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorUnaryScalarNorm::run(void)
{
    if (!d->receiver_quat.isEmpty()) {

        dtkQuaternionReal *quat = d->receiver_quat.constData();

        if (!quat) {
            dtkError() << "dtkComposerNodeQuaternionOperatorUnaryScalarNorm::" << Q_FUNC_INFO << "Input quaternion not set. Nothing is done";
            d->emitter_val.clearData();
            return;
        }

        d->emitter_val.setData(quat->norm());

    }  else {
        dtkWarn() << "dtkComposerNodeQuaternionOperatorUnaryScalarNorm::" << Q_FUNC_INFO << "Input not specified. Nothing is done";
        d->emitter_val.clearData();
    }
}

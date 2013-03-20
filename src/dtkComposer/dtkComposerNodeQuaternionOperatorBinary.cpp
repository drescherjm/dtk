/* dtkComposerNodeQuaternionOperatorBinary.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 14:36:04 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2013 Tue Jan  8 09:46:04 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 41
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeQuaternion.h"
#include "dtkComposerNodeQuaternionOperatorBinary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeQuaternionOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkQuaternionReal*> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkQuaternionReal*> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<dtkQuaternionReal*> emitter_quat;

public:
    dtkQuaternionReal *quat;
};

dtkComposerNodeQuaternionOperatorBinary::dtkComposerNodeQuaternionOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeQuaternionOperatorBinaryPrivate)
{
    d->quat = NULL;

    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);
    this->appendEmitter(&d->emitter_quat);
}

dtkComposerNodeQuaternionOperatorBinary::~dtkComposerNodeQuaternionOperatorBinary(void)
{
    if (d->quat)
        delete d->quat;

    d->quat = NULL;

    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorHomothetic
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeQuaternionOperatorHomotheticPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkQuaternionReal*> receiver_quat;
    dtkComposerTransmitterReceiver<qreal>              receiver_val;

public:
    dtkComposerTransmitterEmitter<dtkQuaternionReal*> emitter_quat;
};

dtkComposerNodeQuaternionOperatorHomothetic::dtkComposerNodeQuaternionOperatorHomothetic(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeQuaternionOperatorHomotheticPrivate)
{
    this->appendReceiver(&d->receiver_quat);
    this->appendReceiver(&d->receiver_val);
    this->appendEmitter(&d->emitter_quat);
}

dtkComposerNodeQuaternionOperatorHomothetic::~dtkComposerNodeQuaternionOperatorHomothetic(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary - SUM 
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorBinarySum::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "dtkComposerNodeQuaternionOperatorBinarySum::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_quat.clearData();

    } else {
        
        if (!d->quat) {
            d->quat = new dtkQuaternionReal(0., 0., 0., 0.);
        }

        const dtkQuaternionReal *q_lhs = d->receiver_lhs.constData();
        const dtkQuaternionReal *q_rhs = d->receiver_rhs.constData();

        if (!q_lhs || !q_rhs) {
            dtkError() << "dtkComposerNodeQuaternionOperatorBinarySum::" << Q_FUNC_INFO << "Input quaternions not set. Nothing is done";
            d->emitter_quat.clearData();
            return;
        }

        *(d->quat) = (*q_lhs + *q_rhs);
        d->emitter_quat.setData(d->quat);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary - SUBSTRACT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorBinarySubstract::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "dtkComposerNodeQuaternionOperatorBinarySubstract::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_quat.clearData();

    } else {
        
        if (!d->quat) {
            d->quat = new dtkQuaternionReal(0., 0., 0., 0.);
        }

        const dtkQuaternionReal *q_lhs = d->receiver_lhs.constData();
        const dtkQuaternionReal *q_rhs = d->receiver_rhs.constData();

        if (!q_lhs || !q_rhs) {
            dtkError() << "dtkComposerNodeQuaternionOperatorBinarySubstract::" << Q_FUNC_INFO << "Input quaternions not set. Nothing is done";
            d->emitter_quat.clearData();
            return;
        }

        *(d->quat) = (*q_lhs - *q_rhs);
        d->emitter_quat.setData(d->quat);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary - HAMILTON MULT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorBinaryMult::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "dtkComposerNodeQuaternionOperatorBinaryMult::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_quat.clearData();

    } else {
        
        if (!d->quat) {
            d->quat = new dtkQuaternionReal(0., 0., 0., 0.);
        }

        const dtkQuaternionReal *q_lhs = d->receiver_lhs.constData();
        const dtkQuaternionReal *q_rhs = d->receiver_rhs.constData();

        if (!q_lhs || !q_rhs) {
            dtkError() << "dtkComposerNodeQuaternionOperatorBinaryMult::" << Q_FUNC_INFO << "Input quaternions not set. Nothing is done";
            d->emitter_quat.clearData();
            return;
        }

        *(d->quat) = (*q_lhs * *q_rhs);
        d->emitter_quat.setData(d->quat);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorHomothetic - MULTIPLICATION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorHomotheticMult::run(void)
{
    if (d->receiver_quat.isEmpty() || d->receiver_val.isEmpty()){
        dtkWarn() << "dtkComposerNodeQuaternionOperatorHomotheticMult::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_quat.clearData();

    } else {

        dtkQuaternionReal *quat = d->receiver_quat.data();

        if (!quat) {
            dtkError() << "dtkComposerNodeQuaternionOperatorHomotheticMult::" << Q_FUNC_INFO << "Input quaternion not set. Nothing is done";
            d->emitter_quat.clearData();
            return;
        }

        *quat *= d->receiver_val.data();
        d->emitter_quat.setData(quat);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorHomothetic - DIVISION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorHomotheticDivision::run(void)
{
    if (d->receiver_quat.isEmpty() || d->receiver_val.isEmpty()){
        dtkWarn() << "dtkComposerNodeQuaternionOperatorHomotheticDivision::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_quat.clearData();

    } else {
        qreal value = d->receiver_val.data();

        if (value != 0 ) {

            dtkQuaternionReal *quat = d->receiver_quat.data();
            
            if (!quat) {
                dtkError() << "dtkComposerNodeQuaternionOperatorHomotheticDivision::" << Q_FUNC_INFO << "Input quaternion not set. Nothing is done";
                d->emitter_quat.clearData();
                return;
            }

            *quat /= value;
            d->emitter_quat.setData(quat);

        } else {
            dtkWarn() << "dtkComposerNodeQuaternionOperatorHomotheticDivision::" << Q_FUNC_INFO << "You divide by zero. Nothing is done" ;
            d->emitter_quat.clearData();
        }
    }
}

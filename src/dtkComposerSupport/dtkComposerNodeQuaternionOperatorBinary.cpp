/* dtkComposerNodeQuaternionOperatorBinary.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 14:36:04 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 17:47:56 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 30
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

#include <dtkMathSupport/dtkQuaternion.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeQuaternionOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkQuaternionReal> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkQuaternionReal> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<dtkQuaternionReal> emitter_quat;

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
    dtkComposerTransmitterReceiver<dtkQuaternionReal> receiver_quat;
    dtkComposerTransmitterReceiver<qreal>             receiver_val;

public:
    dtkComposerTransmitterEmitter<dtkQuaternionReal> emitter_quat;
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
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

    } else {

        if (!d->quat) {
            d->quat = new dtkQuaternionReal(0., 0., 0., 0.);
            d->emitter_quat.setData(d->quat);
        }

        *(d->quat) = (*(d->receiver_lhs.data())) + (*(d->receiver_rhs.data()));
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary - SUBSTRACT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorBinarySubstract::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

    } else {

        if (!d->quat) {
            d->quat = new dtkQuaternionReal(0., 0., 0., 0.);
            d->emitter_quat.setData(d->quat);
        }

        *(d->quat) = (*(d->receiver_lhs.data())) - (*(d->receiver_rhs.data()));
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary - HAMILTON MULT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorBinaryMult::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

    } else {

        if (!d->quat) {
            d->quat = new dtkQuaternionReal(0., 0., 0., 0.);
            d->emitter_quat.setData(d->quat);
        }

        *(d->quat) = (*(d->receiver_lhs.data())) * (*(d->receiver_rhs.data()));
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorHomothetic - MULTIPLICATION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorHomotheticMult::run(void)
{
    if (d->receiver_quat.isEmpty() || d->receiver_val.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

    } else {

        dtkQuaternionReal *quat = d->receiver_quat.data();
        qreal value = *d->receiver_val.data();

        *quat *= value;

        d->emitter_quat.setData(quat);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorHomothetic - DIVISION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorHomotheticDivision::run(void)
{
    if (d->receiver_quat.isEmpty() || d->receiver_val.isEmpty()) {
        dtkWarn() << "Inputs not specified. Nothing is done";

    } else {
        qreal value = *d->receiver_val.data();

        if (value != 0 ) {
            dtkQuaternionReal *quat = d->receiver_quat.data();

            *quat /= value;

            d->emitter_quat.setData(quat);

        } else {
            dtkWarn() << "You divide by zero. Nothing is done" ;

        }
    }
}

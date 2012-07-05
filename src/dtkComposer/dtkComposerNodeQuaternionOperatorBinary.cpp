/* dtkComposerNodeQuaternionOperatorBinary.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 14:36:04 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 28 17:22:28 2012 (+0200)
 *           By: tkloczko
 *     Update #: 14
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
    dtkComposerTransmitterReceiver<dtkQuaternionReal> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkQuaternionReal> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<dtkQuaternionReal> emitter_quat;
};

dtkComposerNodeQuaternionOperatorBinary::dtkComposerNodeQuaternionOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeQuaternionOperatorBinaryPrivate)
{
    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);
    this->appendEmitter(&d->emitter_quat);
}

dtkComposerNodeQuaternionOperatorBinary::~dtkComposerNodeQuaternionOperatorBinary(void)
{
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
    dtkComposerTransmitterVariant                   receiver_val;

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
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_quat.setData(dtkQuaternionReal());

    } else {
        d->emitter_quat.setData(d->receiver_lhs.data() + d->receiver_rhs.data());

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary - SUBSTRACT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorBinarySubstract::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_quat.setData(dtkQuaternionReal());

    } else {
        d->emitter_quat.setData(d->receiver_lhs.data() - d->receiver_rhs.data());

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorBinary - HAMILTON MULT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorBinaryMult::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()){
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_quat.setData(dtkQuaternionReal());

    } else {
        d->emitter_quat.setData(d->receiver_lhs.data() * d->receiver_rhs.data());

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorHomothetic - MULTIPLICATION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorHomotheticMult::run(void)
{
    if (d->receiver_quat.isEmpty() || d->receiver_val.isEmpty()){
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_quat.setData(dtkQuaternionReal());

    } else {
        d->emitter_quat.setData(d->receiver_quat.data() * d->receiver_val.data().toReal());

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeQuaternionOperatorHomothetic - DIVISION
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeQuaternionOperatorHomotheticDivision::run(void)
{
    if (d->receiver_quat.isEmpty() || d->receiver_val.isEmpty()){
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_quat.setData(dtkQuaternionReal());

    } else {

        qreal value = d->receiver_val.data().toReal();

        if ( value != 0) {
            d->emitter_quat.setData(d->receiver_quat.data() / value);

        } else {
            dtkWarn() << "You divide by zero. Nothing is done" ;
            d->emitter_quat.setData(d->receiver_quat.data());

        }
    }
}

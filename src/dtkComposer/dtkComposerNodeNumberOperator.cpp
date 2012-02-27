/* dtkComposerNodeNumberOperator.cpp --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Mon Feb 27 14:28:20 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 16:14:46 2012 (+0100)
 *           By: David Rey
 *     Update #: 46
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerEmitter.h"
#include "dtkComposerReceiver.h"

#include <math.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorUnaryPrivate
{
public:
    dtkComposerReceiver<qreal> *receiver;

public:    
    dtkComposerEmitter<qreal> *emitter;
};

dtkComposerNodeNumberOperatorUnary::dtkComposerNodeNumberOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberOperatorUnaryPrivate)
{
    d->receiver = new dtkComposerReceiver<qreal>;
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerEmitter<qreal>;
    this->appendEmitter(d->emitter);
}

dtkComposerNodeNumberOperatorUnary::~dtkComposerNodeNumberOperatorUnary(void)
{
    delete d->receiver;
    delete d->emitter;
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorBinaryPrivate
{
public:
    dtkComposerReceiver<qreal> *receiver_lhs;
    dtkComposerReceiver<qreal> *receiver_rhs;

public:    
    dtkComposerEmitter<qreal> *emitter;
};

dtkComposerNodeNumberOperatorBinary::dtkComposerNodeNumberOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberOperatorBinaryPrivate)
{
    d->receiver_lhs = new dtkComposerReceiver<qreal>;
    this->appendReceiver(d->receiver_lhs);

    d->receiver_rhs = new dtkComposerReceiver<qreal>;
    this->appendReceiver(d->receiver_rhs);

    d->emitter = new dtkComposerEmitter<qreal>;
    this->appendEmitter(d->emitter);
}

dtkComposerNodeNumberOperatorBinary::~dtkComposerNodeNumberOperatorBinary(void)
{
    delete d->receiver_lhs;
    delete d->receiver_rhs;
    delete d->emitter;
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberComparatorPrivate
{
public:
    dtkComposerReceiver<qreal> *receiver_lhs;
    dtkComposerReceiver<qreal> *receiver_rhs;

public:    
    dtkComposerEmitter<qreal> *emitter;
};

dtkComposerNodeNumberComparator::dtkComposerNodeNumberComparator(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberComparatorPrivate)
{
    d->receiver_lhs = new dtkComposerReceiver<qreal>;
    this->appendReceiver(d->receiver_lhs);

    d->receiver_rhs = new dtkComposerReceiver<qreal>;
    this->appendReceiver(d->receiver_rhs);

    d->emitter = new dtkComposerEmitter<qreal>;
    this->appendEmitter(d->emitter);
}

dtkComposerNodeNumberComparator::~dtkComposerNodeNumberComparator(void)
{
    delete d->receiver_lhs;
    delete d->receiver_rhs;
    delete d->emitter;
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INCR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryIncr::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(a+1);    
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DECR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryDecr::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(a-1);    
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SQRT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySqrt::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(sqrt(a));    
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SQUARE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySquare::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(a*a);    
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryLn::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(log(a));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LOG10
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryLog10::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(log10(a));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - EXP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryExp::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(exp(a));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - COS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryCos::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(cos(a));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySin::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(sin(a));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - TAN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryTan::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(tan(a));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ACOS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAcos::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(acos(a));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ASIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAsin::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(asin(a));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ATAN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAtan::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(atan(a));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DEG2RAD
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryDeg2Rad::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(M_PI * a / 180.0);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - RAD2DEG
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRad2Deg::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(180.0 * a / M_PI);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INV
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryInv::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(1.0 / a);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - RAD2DEG
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryOpp::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(-a);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - CEIL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryCeil::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(ceil(a));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - FLOOR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryFloor::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(floor(a));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ROUND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRound::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(round(a));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ABS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAbs::run(void)
{
    qreal a = d->receiver->data();
    d->emitter->setData(abs(a));
}

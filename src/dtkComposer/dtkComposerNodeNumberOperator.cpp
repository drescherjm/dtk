/* dtkComposerNodeNumberOperator.cpp --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Mon Feb 27 14:28:20 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 15 12:43:25 2012 (+0100)
 *           By: tkloczko
 *     Update #: 142
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkMath/dtkMath.h>

#include <math.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<qreal> *receiver;

public:    
    dtkComposerTransmitterEmitter<qreal> *emitter;
};

dtkComposerNodeNumberOperatorUnary::dtkComposerNodeNumberOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberOperatorUnaryPrivate)
{
    d->receiver = new dtkComposerTransmitterReceiver<qreal>;
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerTransmitterEmitter<qreal>;
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
    dtkComposerTransmitterVariant *receiver_lhs;
    dtkComposerTransmitterVariant *receiver_rhs;

public:    
    dtkComposerTransmitterVariant *emitter;
};

dtkComposerNodeNumberOperatorBinary::dtkComposerNodeNumberOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberOperatorBinaryPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;

    d->receiver_lhs = new dtkComposerTransmitterVariant(variant_list, this);
    this->appendReceiver(d->receiver_lhs);

    d->receiver_rhs = new dtkComposerTransmitterVariant(variant_list, this);
    this->appendReceiver(d->receiver_rhs);

    d->emitter = new dtkComposerTransmitterVariant(variant_list, this);
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
    dtkComposerTransmitterReceiver<qreal> *receiver_lhs;
    dtkComposerTransmitterReceiver<qreal> *receiver_rhs;

public:    
    dtkComposerTransmitterEmitter<bool> *emitter;
};

dtkComposerNodeNumberComparator::dtkComposerNodeNumberComparator(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberComparatorPrivate)
{
    d->receiver_lhs = new dtkComposerTransmitterReceiver<qreal>;
    this->appendReceiver(d->receiver_lhs);

    d->receiver_rhs = new dtkComposerTransmitterReceiver<qreal>;
    this->appendReceiver(d->receiver_rhs);

    d->emitter = new dtkComposerTransmitterEmitter<bool>;
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
// dtkComposerNodeLeaf - ALMOSTEQ
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberAlmosteqPrivate
{
public:
    dtkComposerTransmitterReceiver<qreal> *receiver_lhs;
    dtkComposerTransmitterReceiver<qreal> *receiver_rhs;
    dtkComposerTransmitterReceiver<qreal> *receiver_eps;

public:    
    dtkComposerTransmitterEmitter<bool> *emitter;
};

dtkComposerNodeNumberAlmosteq::dtkComposerNodeNumberAlmosteq(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberAlmosteqPrivate)
{
    d->receiver_lhs = new dtkComposerTransmitterReceiver<qreal>;
    this->appendReceiver(d->receiver_lhs);

    d->receiver_rhs = new dtkComposerTransmitterReceiver<qreal>;
    this->appendReceiver(d->receiver_rhs);

    d->receiver_eps = new dtkComposerTransmitterReceiver<qreal>;
    this->appendReceiver(d->receiver_eps);

    d->emitter = new dtkComposerTransmitterEmitter<bool>;
    this->appendEmitter(d->emitter);
}

dtkComposerNodeNumberAlmosteq::~dtkComposerNodeNumberAlmosteq(void)
{
    delete d->receiver_lhs;
    delete d->receiver_rhs;
    delete d->receiver_eps;
    delete d->emitter;
    delete d;
    
    d = NULL;
}

void dtkComposerNodeNumberAlmosteq::run(void)
{
    qreal a = d->receiver_lhs->data();
    qreal b = d->receiver_rhs->data();
    qreal eps = d->receiver_eps->data();

    d->emitter->setData(dtkAlmostEqualUlpsSimple(a,b,eps));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf - NOTALMOSTEQ
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberNotalmosteqPrivate
{
public:
    dtkComposerTransmitterReceiver<qreal> *receiver_lhs;
    dtkComposerTransmitterReceiver<qreal> *receiver_rhs;
    dtkComposerTransmitterReceiver<qreal> *receiver_eps;

public:    
    dtkComposerTransmitterEmitter<bool> *emitter;
};

dtkComposerNodeNumberNotalmosteq::dtkComposerNodeNumberNotalmosteq(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberNotalmosteqPrivate)
{
    d->receiver_lhs = new dtkComposerTransmitterReceiver<qreal>;
    this->appendReceiver(d->receiver_lhs);

    d->receiver_rhs = new dtkComposerTransmitterReceiver<qreal>;
    this->appendReceiver(d->receiver_rhs);

    d->receiver_eps = new dtkComposerTransmitterReceiver<qreal>;
    this->appendReceiver(d->receiver_eps);

    d->emitter = new dtkComposerTransmitterEmitter<bool>;
    this->appendEmitter(d->emitter);
}

dtkComposerNodeNumberNotalmosteq::~dtkComposerNodeNumberNotalmosteq(void)
{
    delete d->receiver_lhs;
    delete d->receiver_rhs;
    delete d->receiver_eps;
    delete d->emitter;
    delete d;
    
    d = NULL;
}

void dtkComposerNodeNumberNotalmosteq::run(void)
{
    qreal a = d->receiver_lhs->data();
    qreal b = d->receiver_rhs->data();
    qreal eps = d->receiver_eps->data();

    d->emitter->setData(!dtkAlmostEqualUlpsSimple(a,b,eps));
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

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EUCLDIV
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryEucldiv::run(void)
{
    qlonglong a = d->receiver_lhs->data().toLongLong();
    qlonglong b = d->receiver_rhs->data().toLongLong();
    d->emitter->setData(a / b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - LOGN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryLogn::run(void)
{
    qreal a = d->receiver_lhs->data().toReal();
    qreal b = d->receiver_rhs->data().toReal();
    d->emitter->setData(log(a) / log(b));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MINUS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMinus::run(void)
{
    qreal a = d->receiver_lhs->data().toReal();
    qreal b = d->receiver_rhs->data().toReal();
    d->emitter->setData(a-b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MODULO
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryModulo::run(void)
{
    qlonglong a = d->receiver_lhs->data().toLongLong();
    qlonglong b = d->receiver_rhs->data().toLongLong();
    d->emitter->setData(a % b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MULT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMult::run(void)
{
    qreal a = d->receiver_lhs->data().toReal();
    qreal b = d->receiver_rhs->data().toReal();
    d->emitter->setData(a*b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - PLUS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPlus::run(void)
{
    qreal a = d->receiver_lhs->data().toReal();
    qreal b = d->receiver_rhs->data().toReal();
    d->emitter->setData(a+b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POSNTHROOT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPosnthroot::run(void)
{
    qreal a = d->receiver_lhs->data().toReal();
    qreal b = d->receiver_rhs->data().toReal();
    d->emitter->setData(pow(a,1/b));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POWER
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPower::run(void)
{
    qreal a = d->receiver_lhs->data().toReal();
    qreal b = d->receiver_rhs->data().toReal();
    d->emitter->setData(pow(a,b));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - RATIO
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryRatio::run(void)
{
    qreal a = d->receiver_lhs->data().toReal();
    qreal b = d->receiver_rhs->data().toReal();
    d->emitter->setData(a/b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EXPN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryExpn::run(void)
{
    qreal a = d->receiver_lhs->data().toReal();
    qreal b = d->receiver_rhs->data().toReal();
    d->emitter->setData(exp(a*log(b)));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - EQUAL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorEqual::run(void)
{
    qreal a = d->receiver_lhs->data();
    qreal b = d->receiver_rhs->data();
    d->emitter->setData(a==b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - NOTEQUAL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorNotequal::run(void)
{
    qreal a = d->receiver_lhs->data();
    qreal b = d->receiver_rhs->data();
    d->emitter->setData(a!=b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - GT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorGt::run(void)
{
    qreal a = d->receiver_lhs->data();
    qreal b = d->receiver_rhs->data();
    d->emitter->setData(a>b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - LT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorLt::run(void)
{
    qreal a = d->receiver_lhs->data();
    qreal b = d->receiver_rhs->data();
    d->emitter->setData(a<b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - GTE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorGte::run(void)
{
    qreal a = d->receiver_lhs->data();
    qreal b = d->receiver_rhs->data();
    d->emitter->setData(a>=b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - LTE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorLte::run(void)
{
    qreal a = d->receiver_lhs->data();
    qreal b = d->receiver_rhs->data();
    d->emitter->setData(a<=b);
}

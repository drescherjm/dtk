/* dtkComposerNodeNumberOperator.cpp --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Mon Feb 27 14:28:20 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed May  9 10:05:18 2012 (+0200)
 *           By: tkloczko
 *     Update #: 245
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

#include <dtkLog/dtkLog.h>

#include <dtkMath/dtkMath.h>

#include <math.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterVariant receiver;

public:
    dtkComposerTransmitterVariant emitter;
};

dtkComposerNodeNumberOperatorUnary::dtkComposerNodeNumberOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberOperatorUnaryPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;

    d->receiver.setTypes(variant_list);
    this->appendReceiver(&(d->receiver));

    d->emitter.setTypes(variant_list);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeNumberOperatorUnary::~dtkComposerNodeNumberOperatorUnary(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterVariant receiver_lhs;
    dtkComposerTransmitterVariant receiver_rhs;

public:    
    dtkComposerTransmitterVariant emitter;
};

dtkComposerNodeNumberOperatorBinary::dtkComposerNodeNumberOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberOperatorBinaryPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;

    d->receiver_lhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->emitter.setTypes(variant_list);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeNumberOperatorBinary::~dtkComposerNodeNumberOperatorBinary(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberComparatorPrivate
{
public:
    dtkComposerTransmitterVariant receiver_lhs;
    dtkComposerTransmitterVariant receiver_rhs;

public:    
    dtkComposerTransmitterEmitter<bool> emitter;
};

dtkComposerNodeNumberComparator::dtkComposerNodeNumberComparator(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberComparatorPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;

    d->receiver_lhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeNumberComparator::~dtkComposerNodeNumberComparator(void)
{
    delete d;
    
    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf - ALMOSTEQ
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberAlmosteqPrivate
{
public:
    dtkComposerTransmitterVariant receiver_lhs;
    dtkComposerTransmitterVariant receiver_rhs;
    dtkComposerTransmitterVariant receiver_eps;

public:    
    dtkComposerTransmitterEmitter<bool> emitter;
};

dtkComposerNodeNumberAlmosteq::dtkComposerNodeNumberAlmosteq(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberAlmosteqPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;

    d->receiver_lhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->receiver_eps.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_eps));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeNumberAlmosteq::~dtkComposerNodeNumberAlmosteq(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeNumberAlmosteq::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    qreal eps = d->receiver_eps.data().toReal();

    d->emitter.setData(dtkAlmostEqualUlpsSimple(a,b,eps));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf - NOTALMOSTEQ
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberNotalmosteqPrivate
{
public:
    dtkComposerTransmitterVariant receiver_lhs;
    dtkComposerTransmitterVariant receiver_rhs;
    dtkComposerTransmitterVariant receiver_eps;

public:    
    dtkComposerTransmitterEmitter<bool> emitter;
};

dtkComposerNodeNumberNotalmosteq::dtkComposerNodeNumberNotalmosteq(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberNotalmosteqPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;

    d->receiver_lhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->receiver_eps.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_eps));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeNumberNotalmosteq::~dtkComposerNodeNumberNotalmosteq(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeNumberNotalmosteq::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    qreal eps = d->receiver_eps.data().toReal();

    d->emitter.setData(!dtkAlmostEqualUlpsSimple(a,b,eps));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INCR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryIncr::run(void)
{
    switch(d->receiver.type()) {
    case QVariant::Int:
    case QVariant::UInt:
    case QVariant::LongLong:
    case QVariant::ULongLong:
        d->emitter.setData(qVariantValue<qlonglong>(d->receiver.data()) + 1);
        break;
    case QVariant::Double:
        d->emitter.setData(qVariantValue<double>(d->receiver.data()) + 1);
        break;
    default:
        dtkWarn() << "Type" << d->receiver.type() << "is not handled by the node.";
        break;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DECR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryDecr::run(void)
{
    switch(d->receiver.type()) {
    case QVariant::Int:
    case QVariant::UInt:
    case QVariant::LongLong:
    case QVariant::ULongLong:
        d->emitter.setData(qVariantValue<qlonglong>(d->receiver.data()) - 1);
        break;
    case QVariant::Double:
        d->emitter.setData(qVariantValue<double>(d->receiver.data()) - 1);
        break;
    default:
        dtkWarn() << "Type" << d->receiver.type() << "is not handled by the node.";
        break;
    }   
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SQRT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySqrt::run(void)
{
    switch(d->receiver.type()) {
    case QVariant::Int:
    case QVariant::UInt:
    case QVariant::LongLong:
<<<<<<< HEAD
//    case QVariant::ULongLong:
//        d->emitter->setData(sqrtl(qVariantValue<qlonglong>(d->receiver->data())));
//        break;
=======
    case QVariant::ULongLong:
        d->emitter.setData(sqrt(qVariantValue<qlonglong>(d->receiver.data())));
        break;
>>>>>>> cdf41cfcdde4be758fe34ac384f60a3eea379c85
    case QVariant::Double:
        d->emitter.setData(sqrt(qVariantValue<double>(d->receiver.data())));
        break;
    default:
        dtkWarn() << "Type" << d->receiver.type() << "is not handled by the node.";
        break;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SQUARE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySquare::run(void)
{
    qlonglong ll;
    double dd;

    switch(d->receiver.type()) {
    case QVariant::Int:
    case QVariant::UInt:
    case QVariant::LongLong:
    case QVariant::ULongLong:
        ll = qVariantValue<qlonglong>(d->receiver.data());
        d->emitter.setData(ll*ll);
        break;
    case QVariant::Double:
        dd = qVariantValue<double>(d->receiver.data());
        d->emitter.setData(dd*dd);
        break;
    default:
        dtkWarn() << "Type" << d->receiver.type() << "is not handled by the node.";
        break;
    }   
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryLn::run(void)
{
    d->emitter.setData(log(qVariantValue<double>(d->receiver.data())));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LOG10
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryLog10::run(void)
{
    d->emitter.setData(log10(qVariantValue<double>(d->receiver.data())));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - EXP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryExp::run(void)
{
    d->emitter.setData(exp(qVariantValue<double>(d->receiver.data())));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - COS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryCos::run(void)
{
    d->emitter.setData(cos(qVariantValue<double>(d->receiver.data())));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySin::run(void)
{
    d->emitter.setData(sin(qVariantValue<double>(d->receiver.data())));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - TAN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryTan::run(void)
{
    d->emitter.setData(tan(qVariantValue<double>(d->receiver.data())));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ACOS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAcos::run(void)
{
    d->emitter.setData(acos(qVariantValue<double>(d->receiver.data())));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ASIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAsin::run(void)
{
    d->emitter.setData(asin(qVariantValue<double>(d->receiver.data())));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ATAN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAtan::run(void)
{
    d->emitter.setData(atan(qVariantValue<double>(d->receiver.data())));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DEG2RAD
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryDeg2Rad::run(void)
{
    qreal a = qVariantValue<double>(d->receiver.data());
    d->emitter.setData(M_PI * a / 180.0);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - RAD2DEG
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRad2Deg::run(void)
{
    qreal a = qVariantValue<double>(d->receiver.data());
    d->emitter.setData(180.0 * a / M_PI);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INV
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryInv::run(void)
{
    d->emitter.setData(1.0 / qVariantValue<double>(d->receiver.data()));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - OPP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryOpp::run(void)
{
    d->emitter.setData(-qVariantValue<double>(d->receiver.data()));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - CEIL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryCeil::run(void)
{
    d->emitter.setData(ceil(qVariantValue<double>(d->receiver.data())));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - FLOOR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryFloor::run(void)
{
    d->emitter.setData(floor(qVariantValue<double>(d->receiver.data())));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ROUND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRound::run(void)
{
<<<<<<< HEAD
//    d->emitter->setData(round(qVariantValue<double>(d->receiver->data())));
=======
    d->emitter.setData(round(qVariantValue<double>(d->receiver.data())));
>>>>>>> cdf41cfcdde4be758fe34ac384f60a3eea379c85
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ABS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAbs::run(void)
{
    switch(d->receiver.type()) {
    case QVariant::Int:
    case QVariant::UInt:
    case QVariant::LongLong:
    case QVariant::ULongLong:
        d->emitter.setData(abs(qVariantValue<qlonglong>(d->receiver.data())));
        break;
    case QVariant::Double:
        d->emitter.setData(abs(qVariantValue<double>(d->receiver.data())));
        break;
    default:
        dtkWarn() << "Type" << d->receiver.type() << "is not handled by the node.";
        break;
    } 
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EUCLDIV
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryEucldiv::run(void)
{
    qlonglong a = d->receiver_lhs.data().toLongLong();
    qlonglong b = d->receiver_rhs.data().toLongLong();
    d->emitter.setData(a / b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - LOGN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryLogn::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(log(a) / log(b));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MINUS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMinus::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(a-b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MODULO
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryModulo::run(void)
{
    qlonglong a = d->receiver_lhs.data().toLongLong();
    qlonglong b = d->receiver_rhs.data().toLongLong();
    d->emitter.setData(a % b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MULT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMult::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(a*b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - PLUS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPlus::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(a+b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POSNTHROOT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPosnthroot::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(pow(a,1/b));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POWER
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPower::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(pow(a,b));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - RATIO
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryRatio::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();

    d->emitter.setData(a/b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EXPN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryExpn::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(exp(a*log(b)));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - EQUAL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorEqual::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(a==b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - NOTEQUAL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorNotequal::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(a!=b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - GT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorGt::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(a>b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - LT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorLt::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(a<b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - GTE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorGte::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(a>=b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - LTE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorLte::run(void)
{
    qreal a = d->receiver_lhs.data().toReal();
    qreal b = d->receiver_rhs.data().toReal();
    d->emitter.setData(a<=b);
}

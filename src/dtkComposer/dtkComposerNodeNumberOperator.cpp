/* dtkComposerNodeNumberOperator.cpp ---
 *
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Mon Feb 27 14:28:20 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Aug  4 01:56:41 2012 (+0200)
 *           By: tkloczko
 *     Update #: 345
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerMetatype.h"

#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterUtils.h"
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

public:
    qlonglong value_i;
    qreal     value_r;
};

dtkComposerNodeNumberOperatorUnary::dtkComposerNodeNumberOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberOperatorUnaryPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;

    d->receiver.setTypes(variant_list);
    this->appendReceiver(&(d->receiver));

    d->emitter.setData<double>(&d->value_r);
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

public:
    qlonglong value_i;
    qreal     value_r;
};

dtkComposerNodeNumberOperatorBinary::dtkComposerNodeNumberOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberOperatorBinaryPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;

    d->receiver_lhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->emitter.setData<double>(&d->value_r);
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

public:
    bool value;
};

dtkComposerNodeNumberComparator::dtkComposerNodeNumberComparator(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberComparatorPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;

    d->receiver_lhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->value = false;
    d->emitter.setData(&d->value);
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

public:
    bool value;
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

    d->value = false;
    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeNumberAlmosteq::~dtkComposerNodeNumberAlmosteq(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeNumberAlmosteq::run(void)
{
    qreal lhs, rhs, eps;

    if (d->receiver_lhs.type() == QVariant::Double)
        lhs = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    else
        lhs = static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver_lhs)));

    if (d->receiver_rhs.type() == QVariant::Double)
        rhs = *(dtkComposerTransmitterData<double>(d->receiver_rhs));
    else
        rhs = static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver_rhs)));

    if (d->receiver_eps.type() == QVariant::Double)
        eps = *(dtkComposerTransmitterData<double>(d->receiver_eps));
    else
        eps = static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver_eps)));

    d->value = dtkAlmostEqualUlpsSimple(lhs, rhs, eps);
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

public:
    bool value;
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

    d->value = false;
    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeNumberNotalmosteq::~dtkComposerNodeNumberNotalmosteq(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeNumberNotalmosteq::run(void)
{
    qreal lhs, rhs, eps;

    if (d->receiver_lhs.type() == QVariant::Double)
        lhs = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    else
        lhs = static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver_lhs)));

    if (d->receiver_rhs.type() == QVariant::Double)
        rhs = *(dtkComposerTransmitterData<double>(d->receiver_rhs));
    else
        rhs = static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver_rhs)));

    if (d->receiver_eps.type() == QVariant::Double)
        eps = *(dtkComposerTransmitterData<double>(d->receiver_eps));
    else
        eps = static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver_eps)));

    d->value = !dtkAlmostEqualUlpsSimple(lhs, rhs, eps);
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
        d->value_i = *(dtkComposerTransmitterData<qlonglong>(d->receiver)) + 1;
        d->emitter.setData<qlonglong>(&d->value_i);
        break;
    case QVariant::Double:
        d->value_r = *(dtkComposerTransmitterData<double>(d->receiver)) + 1;
        d->emitter.setData<double>(&d->value_r);
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
        d->value_i = *(dtkComposerTransmitterData<qlonglong>(d->receiver)) - 1;
        d->emitter.setData<qlonglong>(&d->value_i);
        break;
    case QVariant::Double:
        d->value_r = *(dtkComposerTransmitterData<double>(d->receiver)) - 1;
        d->emitter.setData<double>(&d->value_r);
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
    case QVariant::ULongLong:
        d->value_r = qSqrt(*(dtkComposerTransmitterData<qlonglong>(d->receiver)));
        break;
    case QVariant::Double:
        d->value_r = qSqrt(*(dtkComposerTransmitterData<double>(d->receiver)));
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
    switch(d->receiver.type()) {
    case QVariant::Int:
    case QVariant::UInt:
    case QVariant::LongLong:
    case QVariant::ULongLong:
        d->value_i = *(dtkComposerTransmitterData<qlonglong>(d->receiver));
        d->value_i *= d->value_i;
        d->emitter.setData<qlonglong>(&d->value_i);
        break;
    case QVariant::Double:
        d->value_r = *(dtkComposerTransmitterData<double>(d->receiver));
        d->value_r *= d->value_r;
        d->emitter.setData<double>(&d->value_r);
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
    if (d->receiver.type() == QVariant::Double)
        d->value_r = qLn(*(dtkComposerTransmitterData<double>(d->receiver)));
    else
        d->value_r = qLn(static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver))));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LOG10
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryLog10::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_r = qLn(*(dtkComposerTransmitterData<double>(d->receiver))) / qLn(10.);
    else
        d->value_r = qLn(static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver)))) / qLn(10.);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - EXP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryExp::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_r = qExp(*(dtkComposerTransmitterData<double>(d->receiver)));
    else
        d->value_r = qExp(static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver))));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - COS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryCos::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_r = qCos(*(dtkComposerTransmitterData<double>(d->receiver)));
    else
        d->value_r = qCos(static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver))));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySin::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_r = qSin(*(dtkComposerTransmitterData<double>(d->receiver)));
    else
        d->value_r = qSin(static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver))));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - TAN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryTan::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_r = qTan(*(dtkComposerTransmitterData<double>(d->receiver)));
    else
        d->value_r = qTan(static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver))));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ACOS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAcos::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_r = qAcos(*(dtkComposerTransmitterData<double>(d->receiver)));
    else
        d->value_r = qAcos(static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver))));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ASIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAsin::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_r = qAsin(*(dtkComposerTransmitterData<double>(d->receiver)));
    else
        d->value_r = qAsin(static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver))));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ATAN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAtan::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_r = qAtan(*(dtkComposerTransmitterData<double>(d->receiver)));
    else
        d->value_r = qAtan(static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver))));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DEG2RAD
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryDeg2Rad::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_r = *(dtkComposerTransmitterData<double>(d->receiver));
    else
        d->value_r = static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver)));

    d->value_r *= (M_PI / 180.);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - RAD2DEG
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRad2Deg::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_r = *(dtkComposerTransmitterData<double>(d->receiver));
    else
        d->value_r = static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver)));

    d->value_r *= (180. / M_PI);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INV
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryInv::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_r = *(dtkComposerTransmitterData<double>(d->receiver));
    else
        d->value_r = static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver)));

    d->value_r  = 1. / *(dtkComposerTransmitterData<double>(d->receiver));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - OPP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryOpp::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_r = *(dtkComposerTransmitterData<double>(d->receiver));
    else
        d->value_r = static_cast<qreal>(*(dtkComposerTransmitterData<qlonglong>(d->receiver)));

    d->value_r  = -1. * (*(dtkComposerTransmitterData<double>(d->receiver)));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - CEIL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryCeil::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_i = qCeil(*(dtkComposerTransmitterData<double>(d->receiver)));
    else
        d->value_i = qCeil(*(dtkComposerTransmitterData<qlonglong>(d->receiver)));

    d->emitter.setData<qlonglong>(&d->value_i);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - FLOOR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryFloor::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_i = qFloor(*(dtkComposerTransmitterData<double>(d->receiver)));
    else
        d->value_i = qFloor(*(dtkComposerTransmitterData<qlonglong>(d->receiver)));

    d->emitter.setData<qlonglong>(&d->value_i);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ROUND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRound::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_i = qRound(*(dtkComposerTransmitterData<double>(d->receiver)));
    else
        d->value_i = qRound(*(dtkComposerTransmitterData<qlonglong>(d->receiver)));

    d->emitter.setData<qlonglong>(&d->value_i);
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
        d->value_i = qAbs(*(dtkComposerTransmitterData<qlonglong>(d->receiver)));
        d->emitter.setData(&d->value_i);
        break;
    case QVariant::Double:
        d->value_r = qAbs(*(dtkComposerTransmitterData<double>(d->receiver)));
        d->emitter.setData<double>(&d->value_r);
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
    qlonglong a = *(dtkComposerTransmitterData<qlonglong>(d->receiver_lhs));
    qlonglong b = *(dtkComposerTransmitterData<qlonglong>(d->receiver_rhs));

    d->value_i = a / b;
    d->emitter.setData(&d->value_i);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - LOGN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryLogn::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value_r = (log(a) / log(b));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MINUS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMinus::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value_r = a - b;

    qDebug() << d->value_r;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMin::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value_r = qMin(a,b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MAX
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMax::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value_r = qMax(a,b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MODULO
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryModulo::run(void)
{
    qlonglong a = *(dtkComposerTransmitterData<qlonglong>(d->receiver_lhs));
    qlonglong b = *(dtkComposerTransmitterData<qlonglong>(d->receiver_rhs));

    d->value_i = a % b;
    d->emitter.setData(&d->value_i);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MULT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMult::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value_r = a * b;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - PLUS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPlus::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value_r = a + b;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POSNTHROOT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPosnthroot::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value_r = qPow(a, 1/b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POWER
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPower::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value_r = qPow(a, b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - RATIO
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryRatio::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value_r = a / b;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EXPN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryExpn::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value_r = qExp(a * qLn(b));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - EQUAL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorEqual::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value = (a == b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - NOTEQUAL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorNotequal::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value = (a != b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - GT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorGt::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value = (a > b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - LT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorLt::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value = (a < b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - GTE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorGte::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value = (a >= b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - LTE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorLte::run(void)
{
    qreal a = *(dtkComposerTransmitterData<double>(d->receiver_lhs));
    qreal b = *(dtkComposerTransmitterData<double>(d->receiver_rhs));

    d->value = (a <= b);
}

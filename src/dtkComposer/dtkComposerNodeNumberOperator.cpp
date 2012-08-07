/* dtkComposerNodeNumberOperator.cpp ---
 *
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Mon Feb 27 14:28:20 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Aug  7 16:54:15 2012 (+0200)
 *           By: tkloczko
 *     Update #: 405
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
    variant_list << QVariant::LongLong << QVariant::Double;

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
    variant_list << QVariant::LongLong << QVariant::Double;

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
    variant_list << QVariant::LongLong << QVariant::Double;

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
    variant_list << QVariant::LongLong << QVariant::Double;

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
    if (d->receiver_lhs.type() == QVariant::LongLong && d->receiver_rhs.type() == QVariant::LongLong) {

        d->value = (*(d->receiver_lhs.data<qlonglong>()) == *(d->receiver_rhs.data<qlonglong>()));
        
    } else {

            qreal lhs = *(d->receiver_lhs.data<qreal>());
            qreal rhs = *(d->receiver_rhs.data<qreal>());
            qreal eps = *(d->receiver_eps.data<qreal>());

            d->value = dtkAlmostEqualUlpsSimple(lhs, rhs, eps);
    }
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
    variant_list << QVariant::LongLong << QVariant::Double;

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
    if (d->receiver_lhs.type() == QVariant::LongLong && d->receiver_rhs.type() == QVariant::LongLong) {

        d->value = (*(d->receiver_lhs.data<qlonglong>()) != *(d->receiver_rhs.data<qlonglong>()));
        
    } else {

            qreal lhs = *(d->receiver_lhs.data<qreal>());
            qreal rhs = *(d->receiver_rhs.data<qreal>());
            qreal eps = *(d->receiver_eps.data<qreal>());

            d->value = !dtkAlmostEqualUlpsSimple(lhs, rhs, eps);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INCR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryIncr::run(void)
{
    switch(d->receiver.type()) {
    case QVariant::LongLong:
        d->value_i = *(d->receiver.data<qlonglong>()) + 1;
        d->emitter.setData<qlonglong>(&d->value_i);
        break;
    case QVariant::Double:
        d->value_r = *(d->receiver.data<qreal>()) + 1;
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
    case QVariant::LongLong:
        d->value_i = *(d->receiver.data<qlonglong>()) - 1;
        d->emitter.setData<qlonglong>(&d->value_i);
        break;
    case QVariant::Double:
        d->value_r = *(d->receiver.data<qreal>()) - 1;
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
    case QVariant::LongLong:
        d->value_r = qSqrt(*(d->receiver.data<qlonglong>()));
        break;
    case QVariant::Double:
        d->value_r = qSqrt(*(d->receiver.data<qreal>()));
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
    case QVariant::LongLong:
        d->value_i = *(d->receiver.data<qlonglong>());
        d->value_i *= d->value_i;
        d->emitter.setData<qlonglong>(&d->value_i);
        break;
    case QVariant::Double:
        d->value_r = *(d->receiver.data<qreal>());
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
    d->value_r = qLn(*(d->receiver.data<qreal>()));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LOG10
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryLog10::run(void)
{
    d->value_r = qLn(*(d->receiver.data<qreal>())) / qLn(10.);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - EXP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryExp::run(void)
{
    d->value_r = qExp(*(d->receiver.data<qreal>()));

}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - COS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryCos::run(void)
{
    d->value_r = qCos(*(d->receiver.data<qreal>()));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySin::run(void)
{
    d->value_r = qSin(*(d->receiver.data<qreal>()));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - TAN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryTan::run(void)
{
    d->value_r = qTan(*(d->receiver.data<qreal>()));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ACOS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAcos::run(void)
{
    d->value_r = qAcos(*(d->receiver.data<qreal>()));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ASIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAsin::run(void)
{
    d->value_r = qAsin(*(d->receiver.data<qreal>()));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ATAN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAtan::run(void)
{
    d->value_r = qAtan(*(d->receiver.data<qreal>()));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DEG2RAD
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryDeg2Rad::run(void)
{
    d->value_r = M_PI * (*(d->receiver.data<qreal>()) / 180.);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - RAD2DEG
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRad2Deg::run(void)
{
    d->value_r = 180. * (*(d->receiver.data<qreal>()) / M_PI);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INV
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryInv::run(void)
{
    d->value_r  = 1. / *(d->receiver.data<qreal>());
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - OPP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryOpp::run(void)
{
    d->value_r  = -1. * *(d->receiver.data<qreal>());
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - CEIL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryCeil::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_i = qCeil(*(d->receiver.data<qreal>()));
    else
        d->value_i = *d->receiver.data<qlonglong>();

    d->emitter.setData<qlonglong>(&d->value_i);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - FLOOR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryFloor::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_i = qFloor(*(d->receiver.data<qreal>()));
    else
        d->value_i = *d->receiver.data<qlonglong>();

    d->emitter.setData<qlonglong>(&d->value_i);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ROUND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRound::run(void)
{
    if (d->receiver.type() == QVariant::Double)
        d->value_i = qRound(*(d->receiver.data<qreal>()));
    else
        d->value_i = *d->receiver.data<qlonglong>();

    d->emitter.setData<qlonglong>(&d->value_i);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ABS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAbs::run(void)
{
    switch(d->receiver.type()) {
    case QVariant::LongLong:
        d->value_i = qAbs(*(d->receiver.data<qlonglong>()));
        d->emitter.setData<qlonglong>(&d->value_i);
        break;
    case QVariant::Double:
        d->value_r = qAbs(*(d->receiver.data<qreal>()));
        d->emitter.setData<qreal>(&d->value_r);
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
    d->value_i = *(d->receiver_lhs.data<qlonglong>()) / *(d->receiver_rhs.data<qlonglong>());
    d->emitter.setData<qlonglong>(&d->value_i);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - LOGN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryLogn::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value_r = (log(a) / log(b));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MINUS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMinus::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value_r = a - b;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMin::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value_r = qMin(a,b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MAX
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMax::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value_r = qMax(a,b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MODULO
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryModulo::run(void)
{
    d->value_i = *(d->receiver_lhs.data<qlonglong>()) % *(d->receiver_rhs.data<qlonglong>());
    d->emitter.setData(&d->value_i);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MULT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMult::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value_r = a * b;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - PLUS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPlus::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value_r = a + b;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POSNTHROOT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPosnthroot::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value_r = qPow(a, 1/b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POWER
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPower::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value_r = qPow(a, b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - RATIO
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryRatio::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value_r = a / b;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EXPN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryExpn::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value_r = qExp(a * qLn(b));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - EQUAL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorEqual::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value = (a == b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - NOTEQUAL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorNotequal::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value = (a != b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - GT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorGt::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value = (a > b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - LT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorLt::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value = (a < b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - GTE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorGte::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value = (a >= b);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - LTE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorLte::run(void)
{
    qreal a = *(d->receiver_lhs.data<qreal>());
    qreal b = *(d->receiver_rhs.data<qreal>());

    d->value = (a <= b);
}

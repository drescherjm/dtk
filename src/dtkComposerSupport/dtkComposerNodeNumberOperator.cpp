/* dtkComposerNodeNumberOperator.cpp ---
 *
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Mon Feb 27 14:28:20 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 17:43:02 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 496
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
#include "dtkComposerTransmitterVariant.h"

#include <dtkLog/dtkLog>

#include <dtkMathSupport/dtkMath.h>

#include <QtCore/qmath.h>

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
    double    value_r;
};

dtkComposerNodeNumberOperatorUnary::dtkComposerNodeNumberOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberOperatorUnaryPrivate)
{
    QList<int> variant_list;
    variant_list << QMetaType::LongLong << QMetaType::Double;

    d->receiver.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver));

    d->emitter.setData<double>(&d->value_r);
    d->emitter.setDataTypes(variant_list);
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
    double    value_r;
};

dtkComposerNodeNumberOperatorBinary::dtkComposerNodeNumberOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberOperatorBinaryPrivate)
{
    QList<int> variant_list;
    variant_list << QMetaType::LongLong << QMetaType::Double;

    d->receiver_lhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->emitter.setData<double>(&d->value_r);
    d->emitter.setDataTypes(variant_list);
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
    QList<int> variant_list;
    variant_list << QMetaType::LongLong << QMetaType::Double;

    d->receiver_lhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setDataTypes(variant_list);
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
    QList<int> variant_list;
    variant_list << QMetaType::LongLong << QMetaType::Double;

    d->receiver_lhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->receiver_eps.setDataTypes(variant_list);
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
    if (d->receiver_lhs.dataType() == QMetaType::LongLong && d->receiver_rhs.dataType() == QMetaType::LongLong) {

        d->value = (*(d->receiver_lhs.data<qlonglong>()) == *(d->receiver_rhs.data<qlonglong>()));

    } else {

        double lhs = *(d->receiver_lhs.data<double>());
        double rhs = *(d->receiver_rhs.data<double>());
        double eps = *(d->receiver_eps.data<double>());

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
    QList<int> variant_list;
    variant_list << QMetaType::LongLong << QMetaType::Double;

    d->receiver_lhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->receiver_eps.setDataTypes(variant_list);
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
    if (d->receiver_lhs.dataType() == QMetaType::LongLong && d->receiver_rhs.dataType() == QMetaType::LongLong) {

        d->value = (*(d->receiver_lhs.data<qlonglong>()) != *(d->receiver_rhs.data<qlonglong>()));

    } else {

        double lhs = *(d->receiver_lhs.data<double>());
        double rhs = *(d->receiver_rhs.data<double>());
        double eps = *(d->receiver_eps.data<double>());

        d->value = !dtkAlmostEqualUlpsSimple(lhs, rhs, eps);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INCR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryIncr::run(void)
{
    switch (d->receiver.dataType()) {
    case QMetaType::LongLong: {
        qlonglong *value = d->receiver.data<qlonglong>();
        ++(*value);
        d->emitter.setData<qlonglong>(value);
        break;
    }

    case QMetaType::Double: {
        double *value = d->receiver.data<double>();
        ++(*value);
        d->emitter.setData<double>(value);
        break;
    }

    default:
        dtkWarn() << "Type" << d->receiver.dataType() << "is not handled by the node.";
        break;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DECR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryDecr::run(void)
{
    switch (d->receiver.dataType()) {
    case QMetaType::LongLong: {
        qlonglong *value = d->receiver.data<qlonglong>();
        --(*value);
        d->emitter.setData<qlonglong>(value);
        break;
    }

    case QMetaType::Double: {
        double *value = d->receiver.data<double>();
        --(*value);
        d->emitter.setData<double>(value);
        break;
    }

    default:
        dtkWarn() << "Type" << d->receiver.dataType() << "is not handled by the node.";
        break;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SQRT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySqrt::run(void)
{
    switch (d->receiver.dataType()) {
    case QMetaType::LongLong: {
        qlonglong *value = d->receiver.data<qlonglong>();
        *value = qSqrt(*value);
        d->emitter.setData<qlonglong>(value);
        break;
    }

    case QMetaType::Double: {
        double *value = d->receiver.data<double>();
        *value = qSqrt(*value);
        d->emitter.setData<double>(value);
        break;
    }

    default:
        dtkWarn() << "Type" << d->receiver.dataType() << "is not handled by the node.";
        break;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SQUARE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySquare::run(void)
{
    switch (d->receiver.dataType()) {
    case QMetaType::LongLong: {
        qlonglong *value = d->receiver.data<qlonglong>();
        *value *= (*value);
        d->emitter.setData<qlonglong>(value);
        break;
    }

    case QMetaType::Double: {
        double *value = d->receiver.data<double>();
        *value *= (*value);
        d->emitter.setData<double>(value);
        break;
    }

    default:
        dtkWarn() << "Type" << d->receiver.dataType() << "is not handled by the node.";
        break;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryLn::run(void)
{
    double *value = d->receiver.data<double>();
    *value = qLn(*value);
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LOG10
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryLog10::run(void)
{
    double *value = d->receiver.data<double>();
    *value = qLn(*value) / qLn(10.);
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - EXP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryExp::run(void)
{
    double *value = d->receiver.data<double>();
    *value = qExp(*value);
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - COS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryCos::run(void)
{
    double *value = d->receiver.data<double>();
    *value = qCos(*value);
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySin::run(void)
{
    double *value = d->receiver.data<double>();
    *value = qSin(*value);
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - TAN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryTan::run(void)
{
    double *value = d->receiver.data<double>();
    *value = qTan(*value);
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ACOS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAcos::run(void)
{
    double *value = d->receiver.data<double>();
    *value = qAcos(*value);
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ASIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAsin::run(void)
{
    double *value = d->receiver.data<double>();
    *value = qAsin(*value);
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ATAN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAtan::run(void)
{
    double *value = d->receiver.data<double>();
    *value = qAtan(*value);
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DEG2RAD
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryDeg2Rad::run(void)
{
    double *value = d->receiver.data<double>();
    *value = dtkDeg2Rad(*value);
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - RAD2DEG
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRad2Deg::run(void)
{
    double *value = d->receiver.data<double>();
    *value = dtkRad2Deg(*value);
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INV
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryInv::run(void)
{
    double *value = d->receiver.data<double>();
    *value = 1. / (*value);
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - OPP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryOpp::run(void)
{
    double *value = d->receiver.data<double>();
    *value *= -1.;
    d->emitter.setData<double>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - CEIL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryCeil::run(void)
{
    if (d->receiver.dataType() == QMetaType::Double) {
        d->value_i = qCeil(*(d->receiver.data<double>()));
        d->emitter.setData<qlonglong>(&d->value_i);

    } else {
        d->emitter.setData<qlonglong>(d->receiver.data<qlonglong>());
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - FLOOR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryFloor::run(void)
{
    if (d->receiver.dataType() == QMetaType::Double) {
        d->value_i = qFloor(*(d->receiver.data<double>()));
        d->emitter.setData<qlonglong>(&d->value_i);

    } else {
        d->emitter.setData<qlonglong>(d->receiver.data<qlonglong>());
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ROUND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRound::run(void)
{
    if (d->receiver.dataType() == QMetaType::Double) {
        d->value_i = qRound(*(d->receiver.data<double>()));
        d->emitter.setData<qlonglong>(&d->value_i);

    } else {
        d->emitter.setData<qlonglong>(d->receiver.data<qlonglong>());
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ABS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAbs::run(void)
{
    switch (d->receiver.dataType()) {
    case QMetaType::LongLong: {
        qlonglong *value = d->receiver.data<qlonglong>();
        *value = qAbs(*value);
        d->emitter.setData<qlonglong>(value);
        break;
    }

    case QMetaType::Double: {
        double *value = d->receiver.data<double>();
        *value = qAbs(*value);
        d->emitter.setData<double>(value);
        break;
    }

    default:
        dtkWarn() << "Type" << d->receiver.dataType() << "is not handled by the node.";
        break;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EUCLDIV
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryEucldiv::run(void)
{
    qlonglong *lhs = d->receiver_lhs.data<qlonglong>();
    qlonglong *rhs = d->receiver_rhs.data<qlonglong>();

    d->value_i = (*lhs) / (*rhs);;

    d->emitter.setData<qlonglong>(&d->value_i);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - LOGN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryLogn::run(void)
{
    double *lhs = d->receiver_lhs.data<double>();
    double *rhs = d->receiver_rhs.data<double>();

    d->value_r = qLn(*lhs) / qLn(*rhs);

    d->emitter.setData<double>(&d->value_r);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMin::run(void)
{
    double *lhs = d->receiver_lhs.data<double>();
    double *rhs = d->receiver_rhs.data<double>();

    d->value_r = (*lhs) < (*rhs) ? (*lhs) : (*rhs);

    d->emitter.setData<double>(&d->value_r);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MINUS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMinus::run(void)
{
    double *lhs = d->receiver_lhs.data<double>();
    double *rhs = d->receiver_rhs.data<double>();

    d->value_r = (*lhs) - (*rhs);

    d->emitter.setData<double>(&d->value_r);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MAX
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMax::run(void)
{
    double *lhs = d->receiver_lhs.data<double>();
    double *rhs = d->receiver_rhs.data<double>();

    d->value_r = (*lhs) > (*rhs) ? (*lhs) : (*rhs);

    d->emitter.setData<double>(&d->value_r);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MODULO
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryModulo::run(void)
{
    qlonglong *value = d->receiver_lhs.data<qlonglong>();
    *value = (*value) % *(d->receiver_rhs.data<qlonglong>());
    d->emitter.setData<qlonglong>(value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MULT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMult::run(void)
{
    double *lhs = d->receiver_lhs.data<double>();
    double *rhs = d->receiver_rhs.data<double>();

    d->value_r = (*lhs) * (*rhs);

    d->emitter.setData<double>(&d->value_r);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - PLUS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPlus::run(void)
{
    double *lhs = d->receiver_lhs.data<double>();
    double *rhs = d->receiver_rhs.data<double>();

    d->value_r = (*lhs) + (*rhs);

    d->emitter.setData<double>(&d->value_r);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POSNTHROOT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPosnthroot::run(void)
{
    double *lhs = d->receiver_lhs.data<double>();
    double *rhs = d->receiver_rhs.data<double>();

    d->value_r = qPow((*lhs), 1. / (*rhs));

    d->emitter.setData<double>(&d->value_r);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POWER
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPower::run(void)
{
    double *lhs = d->receiver_lhs.data<double>();
    double *rhs = d->receiver_rhs.data<double>();

    d->value_r = qPow((*lhs), (*rhs));

    d->emitter.setData<double>(&d->value_r);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - RATIO
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryRatio::run(void)
{
    double *lhs = d->receiver_lhs.data<double>();
    double *rhs = d->receiver_rhs.data<double>();

    d->value_r = (*lhs) / (*rhs);

    d->emitter.setData<double>(&d->value_r);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EXPN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryExpn::run(void)
{
    double *lhs = d->receiver_lhs.data<double>();
    double *rhs = d->receiver_rhs.data<double>();

    d->value_r = qExp((*lhs) * qLn(*rhs));

    d->emitter.setData<double>(&d->value_r);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - EQUAL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorEqual::run(void)
{
    double lhs = *(d->receiver_lhs.data<double>());
    double rhs = *(d->receiver_rhs.data<double>());

    d->value = (lhs == rhs);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - NOTEQUAL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorNotequal::run(void)
{
    double lhs = *(d->receiver_lhs.data<double>());
    double rhs = *(d->receiver_rhs.data<double>());

    d->value = (lhs != rhs);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - GT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorGt::run(void)
{
    double lhs = *(d->receiver_lhs.data<double>());
    double rhs = *(d->receiver_rhs.data<double>());

    d->value = (lhs > rhs);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - LT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorLt::run(void)
{
    double lhs = *(d->receiver_lhs.data<double>());
    double rhs = *(d->receiver_rhs.data<double>());

    d->value = (lhs < rhs);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - GTE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorGte::run(void)
{
    double lhs = *(d->receiver_lhs.data<double>());
    double rhs = *(d->receiver_rhs.data<double>());

    d->value = (lhs >= rhs);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - LTE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorLte::run(void)
{
    double lhs = *(d->receiver_lhs.data<double>());
    double rhs = *(d->receiver_rhs.data<double>());

    d->value = (lhs <= rhs);
}

/* dtkComposerNodeNumberOperator.cpp ---
 *
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Mon Feb 27 14:28:20 2012 (+0100)
 * Version: $Id$
 * Last-Updated: 2013 Wed Jan 16 11:23:44 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 651
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
    QVector<const dtkComposerType*> variant_list;
    variant_list << dtkComposerTypeInfo<qlonglong>::type() << dtkComposerTypeInfo<double>::type();

    d->receiver.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver));

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
    QVector<const dtkComposerType*> variant_list;
    variant_list << dtkComposerTypeInfo<qlonglong>::type() << dtkComposerTypeInfo<double>::type();

    d->receiver_lhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

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
};

dtkComposerNodeNumberComparator::dtkComposerNodeNumberComparator(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberComparatorPrivate)
{
    QVector<const dtkComposerType*> variant_list;
    variant_list << dtkComposerTypeInfo<qlonglong>::type() << dtkComposerTypeInfo<double>::type();

    d->receiver_lhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setDataTypes(variant_list);
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

public:
    bool value;
};

dtkComposerNodeNumberAlmosteq::dtkComposerNodeNumberAlmosteq(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberAlmosteqPrivate)
{
    QVector<const dtkComposerType*> variant_list;
    variant_list << dtkComposerTypeInfo<qlonglong>::type() << dtkComposerTypeInfo<double>::type();

    d->receiver_lhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->receiver_eps.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_eps));

    d->value = false;
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeNumberAlmosteq::~dtkComposerNodeNumberAlmosteq(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeNumberAlmosteq::run(void)
{
    dtkComposerVariant lhs_var = d->receiver_lhs.variant();
    dtkComposerVariant rhs_var = d->receiver_rhs.variant();

    if (lhs_var.userType() == QMetaType::LongLong && rhs_var.userType() == QMetaType::LongLong) {
        d->value = ( lhs_var.value<qlonglong>() == rhs_var.value<qlonglong>() );

    } else {
        d->value = dtkAlmostEqualUlpsSimple(lhs_var.value<double>(), rhs_var.value<double>(), d->receiver_eps.data<double>());

    }
    d->emitter.setData(d->value);
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
    QVector<const dtkComposerType*> variant_list;
    variant_list << dtkComposerTypeInfo<qlonglong>::type() << dtkComposerTypeInfo<double>::type();

    d->receiver_lhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->receiver_eps.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver_eps));

    d->value = false;
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeNumberNotalmosteq::~dtkComposerNodeNumberNotalmosteq(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeNumberNotalmosteq::run(void)
{
    dtkComposerVariant lhs_var = d->receiver_lhs.variant();
    dtkComposerVariant rhs_var = d->receiver_rhs.variant();

    if (lhs_var.userType() == QMetaType::LongLong && rhs_var.userType() == QMetaType::LongLong) {
        d->value = ( lhs_var.value<qlonglong>() != rhs_var.value<qlonglong>() );

    } else {
        d->value = !(dtkAlmostEqualUlpsSimple(lhs_var.value<double>(), rhs_var.value<double>(), d->receiver_eps.data<double>()));

    }
    d->emitter.setData(d->value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INCR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryIncr::run(void)
{
    dtkComposerVariant var = d->receiver.variant();

    if (var.userType() == QMetaType::LongLong) {
        d->emitter.setData<qlonglong>(var.value<qlonglong>() + 1);

    } else {
        d->emitter.setData<double>(var.value<double>() + 1);

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DECR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryDecr::run(void)
{
    dtkComposerVariant var = d->receiver.variant();

    if (var.userType() == QMetaType::LongLong) {
        d->emitter.setData<qlonglong>(var.value<qlonglong>() - 1);

    } else {
        d->emitter.setData<double>(var.value<double>() - 1);

    } 
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SQRT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySqrt::run(void)
{ 
    d->value_r = qSqrt(d->receiver.data<double>());
    d->emitter.setData<double>(d->value_r);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SQUARE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySquare::run(void)
{
    dtkComposerVariant var = d->receiver.variant();

    if (var.userType() == QMetaType::LongLong) {
        qlonglong value = var.value<qlonglong>();
        d->emitter.setData<qlonglong>(value * value);

    } else {
        double value = var.value<double>();
        d->emitter.setData<double>(value * value);

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryLn::run(void)
{
    d->emitter.setData<double>( qLn( d->receiver.data<double>() ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LOG10
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryLog10::run(void)
{
    d->emitter.setData<double>( qLn( d->receiver.data<double>() ) / qLn(10.) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - EXP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryExp::run(void)
{
    d->emitter.setData<double>( qExp( d->receiver.data<double>() ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - COS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryCos::run(void)
{
    d->emitter.setData<double>( qCos( d->receiver.data<double>() ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnarySin::run(void)
{
    d->emitter.setData<double>( qSin( d->receiver.data<double>() ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - TAN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryTan::run(void)
{
    d->emitter.setData<double>( qTan( d->receiver.data<double>() ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ACOS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAcos::run(void)
{
    d->emitter.setData<double>( qAcos( d->receiver.data<double>() ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ASIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAsin::run(void)
{
    d->emitter.setData<double>( qAsin( d->receiver.data<double>() ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ATAN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAtan::run(void)
{
    d->emitter.setData<double>( qAtan( d->receiver.data<double>() ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DEG2RAD
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryDeg2Rad::run(void)
{
    d->emitter.setData<double>( dtkDeg2Rad( d->receiver.data<double>() ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - RAD2DEG
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRad2Deg::run(void)
{
    d->emitter.setData<double>( dtkRad2Deg( d->receiver.data<double>() ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INV
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryInv::run(void)
{
    d->emitter.setData<double>( 1. / d->receiver.data<double>() );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - OPP
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryOpp::run(void)
{
    d->emitter.setData<double>( -1. * d->receiver.data<double>() );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - CEIL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryCeil::run(void)
{
    dtkComposerVariant var = d->receiver.variant();

    if (var.userType() == QMetaType::Double) {
        d->emitter.setData<qlonglong>( qCeil( var.value<double>() ) );

    } else {
        d->emitter.setData<qlonglong>(var.value<qlonglong>());
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - FLOOR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryFloor::run(void)
{
    dtkComposerVariant var = d->receiver.variant();

    if (var.userType() == QMetaType::Double) {
        d->emitter.setData<qlonglong>( qFloor( var.value<double>() ) );

    } else {
        d->emitter.setData<qlonglong>(var.value<qlonglong>());
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ROUND
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRound::run(void)
{
    dtkComposerVariant var = d->receiver.variant();

    if (var.userType() == QMetaType::Double) {
        d->emitter.setData<qlonglong>( qRound( var.value<double>() ) );

    } else {
        d->emitter.setData<qlonglong>(var.value<qlonglong>());
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ABS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryAbs::run(void)
{
    dtkComposerVariant var = d->receiver.variant();

    if (var.userType() == QMetaType::Double) {
        d->emitter.setData<double>( qAbs( var.value<double>() ) );

    } else {
        d->emitter.setData<qlonglong>( qAbs( var.value<qlonglong>() ) );
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EUCLDIV
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryEucldiv::run(void)
{
    d->emitter.setData<qlonglong>( d->receiver_lhs.data<qlonglong>() / d->receiver_rhs.data<qlonglong>() );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - LOGN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryLogn::run(void)
{
    double lhs = d->receiver_lhs.data<double>();
    double rhs = d->receiver_rhs.data<double>();
    
    d->emitter.setData<double>( qLn(lhs) / qLn(rhs) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MIN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMin::run(void)
{
    double lhs = d->receiver_lhs.data<double>();
    double rhs = d->receiver_rhs.data<double>();

    d->emitter.setData<double>( lhs < rhs ? lhs : rhs );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MINUS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMinus::run(void)
{
    d->emitter.setData<double>( d->receiver_lhs.data<double>() - d->receiver_rhs.data<double>() );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MAX
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMax::run(void)
{
    double lhs = d->receiver_lhs.data<double>();
    double rhs = d->receiver_rhs.data<double>();
    
    d->emitter.setData<double>( lhs > rhs ? lhs : rhs );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MODULO
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryModulo::run(void)
{
    d->emitter.setData<qlonglong>( d->receiver_lhs.data<qlonglong>() % d->receiver_rhs.data<qlonglong>() );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MULT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryMult::run(void)
{
    d->emitter.setData<double>( d->receiver_lhs.data<double>() * d->receiver_rhs.data<double>() );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - PLUS
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPlus::run(void)
{
    d->emitter.setData<double>( d->receiver_lhs.data<double>() + d->receiver_rhs.data<double>() );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POSNTHROOT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPosnthroot::run(void)
{
    double lhs = d->receiver_lhs.data<double>();
    double rhs = d->receiver_rhs.data<double>();

    d->emitter.setData<double>( qPow( lhs, 1. / rhs ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POWER
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryPower::run(void)
{
    double lhs = d->receiver_lhs.data<double>();
    double rhs = d->receiver_rhs.data<double>();

    d->emitter.setData<double>( qPow( lhs, rhs ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - RATIO
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryRatio::run(void)
{
    d->emitter.setData<double>( d->receiver_lhs.data<double>() / d->receiver_rhs.data<double>() );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EXPN
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorBinaryExpn::run(void)
{
    double lhs = d->receiver_lhs.data<double>();
    double rhs = d->receiver_rhs.data<double>();

    d->emitter.setData<double>( qExp( lhs * qLn(rhs) ) );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - EQUAL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorEqual::run(void)
{
    double lhs = d->receiver_lhs.data<double>();
    double rhs = d->receiver_rhs.data<double>();

    d->emitter.setData( lhs == rhs );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - NOTEQUAL
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorNotequal::run(void)
{
    double lhs = d->receiver_lhs.data<double>();
    double rhs = d->receiver_rhs.data<double>();

    d->emitter.setData( lhs != rhs );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - GT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorGt::run(void)
{
    double lhs = d->receiver_lhs.data<double>();
    double rhs = d->receiver_rhs.data<double>();

    d->emitter.setData(lhs > rhs);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - LT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorLt::run(void)
{
    double lhs = d->receiver_lhs.data<double>();
    double rhs = d->receiver_rhs.data<double>();
    
    d->emitter.setData( lhs < rhs );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - GTE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorGte::run(void)
{
    double lhs = d->receiver_lhs.data<double>();
    double rhs = d->receiver_rhs.data<double>();

    d->emitter.setData( lhs >= rhs );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator - LTE
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberComparatorLte::run(void)
{
    double lhs = d->receiver_lhs.data<double>();
    double rhs = d->receiver_rhs.data<double>();

    d->emitter.setData( lhs <= rhs );
}

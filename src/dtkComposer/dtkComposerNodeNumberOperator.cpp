// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <QtCore/qmath.h>
#include <math.h>

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

#if !defined(Q_OS_WIN)
#include <inttypes.h>
#else
#define int32_t qint32
#define int64_t qint64
#endif

bool dtkComposerAlmostEqualUlpsSimple(float A, float B, int32_t maxUlps)
{
    if (A == B)
        return true;

    int32_t *AA = reinterpret_cast<int32_t*>(&A);
    int32_t *BB = reinterpret_cast<int32_t*>(&B);

    int32_t intDiff = abs(*AA) - abs(*BB);

    if (intDiff <= maxUlps)
        return true;

    return false;
}

bool dtkComposerAlmostEqualUlpsSimple(double A, double B, int64_t maxUlps)
{
    if (A == B)
        return true;

    int64_t *AA = reinterpret_cast<int64_t*>(&A);
    int64_t *BB = reinterpret_cast<int64_t*>(&B);

    int64_t intDiff = labs(*AA - *BB);

    if (intDiff <= maxUlps)
        return true;

    return false;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiverVariant receiver;

public:
    dtkComposerTransmitterEmitterVariant emitter;

public:
    qlonglong value_i;
    double    value_r;
};

dtkComposerNodeNumberOperatorUnary::dtkComposerNodeNumberOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberOperatorUnaryPrivate)
{
    dtkComposerTransmitter::TypeList type_list;
    type_list << QMetaType::LongLong << QMetaType::Double;

    d->receiver.setTypeList(type_list);
    this->appendReceiver(&(d->receiver));

    d->emitter.setTypeList(type_list);
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
    dtkComposerTransmitterReceiverVariant receiver_lhs;
    dtkComposerTransmitterReceiverVariant receiver_rhs;

public:
    dtkComposerTransmitterEmitterVariant emitter;

public:
    qlonglong value_i;
    double    value_r;
};

dtkComposerNodeNumberOperatorBinary::dtkComposerNodeNumberOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberOperatorBinaryPrivate)
{
    dtkComposerTransmitter::TypeList type_list;
    type_list << QMetaType::LongLong << QMetaType::Double;

    d->receiver_lhs.setTypeList(type_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypeList(type_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->emitter.setTypeList(type_list);
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
    dtkComposerTransmitterReceiverVariant receiver_lhs;
    dtkComposerTransmitterReceiverVariant receiver_rhs;

public:
    dtkComposerTransmitterEmitter<bool> emitter;
};

dtkComposerNodeNumberComparator::dtkComposerNodeNumberComparator(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberComparatorPrivate)
{
    dtkComposerTransmitter::TypeList type_list;
    type_list << QMetaType::LongLong << QMetaType::Double;

    d->receiver_lhs.setTypeList(type_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypeList(type_list);
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
    dtkComposerTransmitterReceiverVariant receiver_lhs;
    dtkComposerTransmitterReceiverVariant receiver_rhs;
    dtkComposerTransmitterReceiverVariant receiver_eps;

public:
    dtkComposerTransmitterEmitter<bool> emitter;

public:
    bool value;
};

dtkComposerNodeNumberAlmosteq::dtkComposerNodeNumberAlmosteq(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberAlmosteqPrivate)
{
    dtkComposerTransmitter::TypeList type_list;
    type_list << QMetaType::LongLong << QMetaType::Double;

    d->receiver_lhs.setTypeList(type_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypeList(type_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->receiver_eps.setTypeList(type_list);
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
    QVariant lhs_var = d->receiver_lhs.variant();
    QVariant rhs_var = d->receiver_rhs.variant();

    if (lhs_var.userType() == QMetaType::Double || rhs_var.userType() == QMetaType::Double) {
	d->value = dtkComposerAlmostEqualUlpsSimple(lhs_var.value<double>(), rhs_var.value<double>(), d->receiver_eps.data<double>());

    } else if (lhs_var.userType() == QMetaType::Float || rhs_var.userType() == QMetaType::Float) {
	d->value = dtkComposerAlmostEqualUlpsSimple(lhs_var.value<float>(), rhs_var.value<float>(), d->receiver_eps.data<float>());

    } else {
        d->value = ( lhs_var.value<qlonglong>() == rhs_var.value<qlonglong>() );

    }
    d->emitter.setData(d->value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf - NOTALMOSTEQ
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberNotalmosteqPrivate
{
public:
    dtkComposerTransmitterReceiverVariant receiver_lhs;
    dtkComposerTransmitterReceiverVariant receiver_rhs;
    dtkComposerTransmitterReceiverVariant receiver_eps;

public:
    dtkComposerTransmitterEmitter<bool> emitter;

public:
    bool value;
};

dtkComposerNodeNumberNotalmosteq::dtkComposerNodeNumberNotalmosteq(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeNumberNotalmosteqPrivate)
{
    dtkComposerTransmitter::TypeList type_list;
    type_list << QMetaType::LongLong << QMetaType::Double;

    d->receiver_lhs.setTypeList(type_list);
    this->appendReceiver(&(d->receiver_lhs));

    d->receiver_rhs.setTypeList(type_list);
    this->appendReceiver(&(d->receiver_rhs));

    d->receiver_eps.setTypeList(type_list);
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
    QVariant lhs_var = d->receiver_lhs.variant();
    QVariant rhs_var = d->receiver_rhs.variant();

    if (lhs_var.userType() == QMetaType::Double || rhs_var.userType() == QMetaType::Double) {
        d->value = !(dtkComposerAlmostEqualUlpsSimple(lhs_var.value<double>(), rhs_var.value<double>(), d->receiver_eps.data<double>()));

    } else if (lhs_var.userType() == QMetaType::Float || rhs_var.userType() == QMetaType::Float) {
        d->value = !(dtkComposerAlmostEqualUlpsSimple(lhs_var.value<float>(), rhs_var.value<float>(), d->receiver_eps.data<float>()));

    } else {
        d->value = ( lhs_var.value<qlonglong>() != rhs_var.value<qlonglong>() );

    }
    d->emitter.setData(d->value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INCR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryIncr::run(void)
{
    QVariant var = d->receiver.variant();

    if (var.userType() == QMetaType::Double || var.userType() == QMetaType::Float) {
        d->emitter.setData<double>(var.value<double>() + 1);

    } else {
        d->emitter.setData<qlonglong>(var.value<qlonglong>() + 1);

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DECR
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryDecr::run(void)
{
    QVariant var = d->receiver.variant();

    if (var.userType() == QMetaType::Double || var.userType() == QMetaType::Float) {
        d->emitter.setData<double>(var.value<double>() - 1);

    } else {
        d->emitter.setData<qlonglong>(var.value<qlonglong>() - 1);

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
    QVariant var = d->receiver.variant();

    if (var.userType() == QMetaType::Double || var.userType() == QMetaType::Float) {
        double value = var.value<double>();
        d->emitter.setData<double>(value * value);

    } else {
        qlonglong value = var.value<qlonglong>();
        d->emitter.setData<qlonglong>(value * value);

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
    d->emitter.setData<double>( M_PI / 180. * d->receiver.data<double>() );
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - RAD2DEG
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorUnaryRad2Deg::run(void)
{
    d->emitter.setData<double>( 180. / M_PI * d->receiver.data<double>() );
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
    QVariant var = d->receiver.variant();

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
    QVariant var = d->receiver.variant();

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
    QVariant var = d->receiver.variant();

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
    QVariant var = d->receiver.variant();

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

void dtkComposerNodeNumberOperatorBinaryNthroot::run(void)
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

//
// dtkComposerNodeNumberOperator.cpp ends here

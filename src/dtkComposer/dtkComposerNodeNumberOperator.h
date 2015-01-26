/* dtkComposerNodeNumberOperator.h --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Mon Feb 27 14:19:28 2012 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. oct. 23 15:27:49 2014 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 109
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODENUMBEROPERATOR_H
#define DTKCOMPOSERNODENUMBEROPERATOR_H

#include "dtkComposerExport.h"

#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorUnaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeNumberOperatorUnary(void);
    ~dtkComposerNodeNumberOperatorUnary(void);

protected:
    dtkComposerNodeNumberOperatorUnaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorBinaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinary : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeNumberOperatorBinary(void);
    ~dtkComposerNodeNumberOperatorBinary(void);

protected:
    dtkComposerNodeNumberOperatorBinaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberComparatorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparator : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeNumberComparator(void);
    ~dtkComposerNodeNumberComparator(void);

protected:
    dtkComposerNodeNumberComparatorPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf - ALMOSTEQ
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberAlmosteqPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberAlmosteq : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeNumberAlmosteq(void);
    ~dtkComposerNodeNumberAlmosteq(void);

public:
    void run(void);

protected:
    dtkComposerNodeNumberAlmosteqPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf - NOTALMOSTEQ
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberNotalmosteqPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberNotalmosteq : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeNumberNotalmosteq(void);
    ~dtkComposerNodeNumberNotalmosteq(void);

public:
    void run(void);

protected:
    dtkComposerNodeNumberNotalmosteqPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INCR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryIncr : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DECR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryDecr : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SQRT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnarySqrt : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SQUARE
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnarySquare : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryLn : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LOG10
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryLog10 : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - EXP
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryExp : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - COS
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryCos : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SIN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnarySin : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - TAN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryTan : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ACOS
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryAcos : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ASIN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryAsin : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ATAN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryAtan : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DEG2RAD
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryDeg2Rad : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - RAD2DEG
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryRad2Deg : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INV
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryInv : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - OPP
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryOpp : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - CEIL
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryCeil : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - FLOOR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryFloor : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ROUND
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryRound : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ROUND
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryAbs : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EUCLDIV
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryEucldiv : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - Min
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryMin: public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - Max
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryMax : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MINUS
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryMinus : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MODULO
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryModulo : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MULT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryMult : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - PLUS
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryPlus : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - NTHROOT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryNthroot : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POWER
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryPower : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - RATIO
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryRatio : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EQUAL
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparatorEqual : public dtkComposerNodeNumberComparator
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - NOTEQUAL
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparatorNotequal : public dtkComposerNodeNumberComparator
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - GT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparatorGt : public dtkComposerNodeNumberComparator
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - LT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparatorLt : public dtkComposerNodeNumberComparator
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - GTE
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparatorGte : public dtkComposerNodeNumberComparator
{
public:
    void run(void);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - LTE
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparatorLte : public dtkComposerNodeNumberComparator
{
public:
    void run(void);

};

#endif

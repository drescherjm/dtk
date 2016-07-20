/* dtkComposerNodeOperator.h ---
 *
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Mon Feb 27 14:19:28 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Aug  3 13:39:59 2012 (+0200)
 *           By: tkloczko
 *     Update #: 76
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODENUMBEROPERATOR_H
#define DTKCOMPOSERNODENUMBEROPERATOR_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorUnaryPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnary : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeNumberOperatorUnary(void);
    ~dtkComposerNodeNumberOperatorUnary(void);

    inline QString inputLabelHint(int) {
        return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeNumberOperatorUnaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorBinaryPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinary : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeNumberOperatorBinary(void);
    ~dtkComposerNodeNumberOperatorBinary(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "lhs";
        else if (port == 1)
            return "rhs";
        else
            return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeNumberOperatorBinaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberComparatorPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberComparator : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeNumberComparator(void);
    ~dtkComposerNodeNumberComparator(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "lhs";
        else if (port == 1)
            return "rhs";
        else
            return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeNumberComparatorPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf - ALMOSTEQ
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberAlmosteqPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberAlmosteq : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeNumberAlmosteq(void);
    ~dtkComposerNodeNumberAlmosteq(void);

public:
    void run(void);

public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "lhs";
        else if (port == 1)
            return "rhs";
        else if (port == 2)
            return "eps";
        else
            return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

    inline QString type(void) {
        return "almosteq";
    }

    inline QString titleHint(void) {
        return "Almosteq";
    }

protected:
    dtkComposerNodeNumberAlmosteqPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf - NOTALMOSTEQ
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberNotalmosteqPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberNotalmosteq : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeNumberNotalmosteq(void);
    ~dtkComposerNodeNumberNotalmosteq(void);

public:
    void run(void);

public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "lhs";
        else if (port == 1)
            return "rhs";
        else if (port == 2)
            return "eps";
        else
            return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

    inline QString type(void) {
        return "notalmosteq";
    }

    inline QString titleHint(void) {
        return "Notalmosteq";
    }

protected:
    dtkComposerNodeNumberNotalmosteqPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INCR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryIncr : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "incr";
    }

    inline QString titleHint(void) {
        return "Incr";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DECR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryDecr : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "decr";
    }

    inline QString titleHint(void) {
        return "Decr";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SQRT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnarySqrt : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "sqrt";
    }

    inline QString titleHint(void) {
        return "Sqrt";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SQUARE
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnarySquare : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "square";
    }

    inline QString titleHint(void) {
        return "Square";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryLn : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "ln";
    }

    inline QString titleHint(void) {
        return "Ln";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - LOG10
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryLog10 : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "log10";
    }

    inline QString titleHint(void) {
        return "Log10";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - EXP
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryExp : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "exp";
    }

    inline QString titleHint(void) {
        return "Exp";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - COS
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryCos : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "cos";
    }

    inline QString titleHint(void) {
        return "Cos";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - SIN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnarySin : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "sin";
    }

    inline QString titleHint(void) {
        return "Sin";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - TAN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryTan : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "tan";
    }

    inline QString titleHint(void) {
        return "Tan";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ACOS
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryAcos : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "acos";
    }

    inline QString titleHint(void) {
        return "Acos";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ASIN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryAsin : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "asin";
    }

    inline QString titleHint(void) {
        return "Asin";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ATAN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryAtan : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "atan";
    }

    inline QString titleHint(void) {
        return "Atan";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - DEG2RAD
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryDeg2Rad : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "deg2rad";
    }

    inline QString titleHint(void) {
        return "Deg2Rad";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - RAD2DEG
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryRad2Deg : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "rad2deg";
    }

    inline QString titleHint(void) {
        return "Rad2Deg";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - INV
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryInv : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "inv";
    }

    inline QString titleHint(void) {
        return "Inv";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - OPP
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryOpp : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "opp";
    }

    inline QString titleHint(void) {
        return "Opp";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - CEIL
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryCeil : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "ceil";
    }

    inline QString titleHint(void) {
        return "Ceil";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - FLOOR
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryFloor : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "floor";
    }

    inline QString titleHint(void) {
        return "Floor";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ROUND
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryRound : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "round";
    }

    inline QString titleHint(void) {
        return "Round";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary - ROUND
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorUnaryAbs : public dtkComposerNodeNumberOperatorUnary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "abs";
    }

    inline QString titleHint(void) {
        return "Abs";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EUCLDIV
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinaryEucldiv : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "eucldiv";
    }

    inline QString titleHint(void) {
        return "Eucldiv";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - Min
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinaryMin: public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "min";
    }

    inline QString titleHint(void) {
        return "Min";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - Max
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinaryMax : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "max";
    }

    inline QString titleHint(void) {
        return "Max";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - LOGN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinaryLogn : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "logn";
    }

    inline QString titleHint(void) {
        return "Logn";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MINUS
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinaryMinus : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "minus";
    }

    inline QString titleHint(void) {
        return "Minus";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MODULO
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinaryModulo : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "modulo";
    }

    inline QString titleHint(void) {
        return "Modulo";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - MULT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinaryMult : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "mult";
    }

    inline QString titleHint(void) {
        return "Mult";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - PLUS
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinaryPlus : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "plus";
    }

    inline QString titleHint(void) {
        return "Plus";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POSNTHROOT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinaryPosnthroot : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "posnthroot";
    }

    inline QString titleHint(void) {
        return "Posnthroot";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - POWER
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinaryPower : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "power";
    }

    inline QString titleHint(void) {
        return "Power";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - RATIO
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinaryRatio : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "ratio";
    }

    inline QString titleHint(void) {
        return "Ratio";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EXPN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberOperatorBinaryExpn : public dtkComposerNodeNumberOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "expn";
    }

    inline QString titleHint(void) {
        return "Expn";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - EQUAL
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberComparatorEqual : public dtkComposerNodeNumberComparator
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "equal";
    }

    inline QString titleHint(void) {
        return "Equal";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - NOTEQUAL
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberComparatorNotequal : public dtkComposerNodeNumberComparator
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "notequal";
    }

    inline QString titleHint(void) {
        return "Notequal";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - GT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberComparatorGt : public dtkComposerNodeNumberComparator
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "gt";
    }

    inline QString titleHint(void) {
        return "Gt";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - LT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberComparatorLt : public dtkComposerNodeNumberComparator
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "lt";
    }

    inline QString titleHint(void) {
        return "Lt";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - GTE
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberComparatorGte : public dtkComposerNodeNumberComparator
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "gte";
    }

    inline QString titleHint(void) {
        return "Gte";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorBinary - LTE
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeNumberComparatorLte : public dtkComposerNodeNumberComparator
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "lte";
    }

    inline QString titleHint(void) {
        return "Lte";
    }
};

#endif

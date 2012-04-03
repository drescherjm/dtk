/* dtkComposerNodeOperator.h --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Mon Feb 27 14:19:28 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 28 17:45:00 2012 (+0100)
 *           By: David Rey
 *     Update #: 74
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinary : public dtkComposerNodeLeaf
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparator : public dtkComposerNodeLeaf
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberAlmosteq : public dtkComposerNodeLeaf
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberNotalmosteq : public dtkComposerNodeLeaf
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryIncr : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryDecr : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnarySqrt : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnarySquare : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryLn : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryLog10 : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryExp : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryCos : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnarySin : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryTan : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryAcos : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryAsin : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryAtan : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryDeg2Rad : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryRad2Deg : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryInv : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryOpp : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryCeil : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryFloor : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryRound : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorUnaryAbs : public dtkComposerNodeNumberOperatorUnary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryEucldiv : public dtkComposerNodeNumberOperatorBinary
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
// dtkComposerNodeNumberOperatorBinary - LOGN
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryLogn : public dtkComposerNodeNumberOperatorBinary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryMinus : public dtkComposerNodeNumberOperatorBinary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryModulo : public dtkComposerNodeNumberOperatorBinary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryMult : public dtkComposerNodeNumberOperatorBinary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryPlus : public dtkComposerNodeNumberOperatorBinary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryPosnthroot : public dtkComposerNodeNumberOperatorBinary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryPower : public dtkComposerNodeNumberOperatorBinary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryRatio : public dtkComposerNodeNumberOperatorBinary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberOperatorBinaryExpn : public dtkComposerNodeNumberOperatorBinary
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparatorEqual : public dtkComposerNodeNumberComparator
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparatorNotequal : public dtkComposerNodeNumberComparator
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparatorGt : public dtkComposerNodeNumberComparator
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparatorLt : public dtkComposerNodeNumberComparator
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparatorGte : public dtkComposerNodeNumberComparator
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

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberComparatorLte : public dtkComposerNodeNumberComparator
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

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


#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorUnaryPrivate;

class  dtkComposerNodeNumberOperatorUnary : public dtkComposerNodeLeaf
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

class  dtkComposerNodeNumberOperatorBinary : public dtkComposerNodeLeaf
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

class  dtkComposerNodeNumberComparator : public dtkComposerNodeLeaf
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

class  dtkComposerNodeNumberAlmosteq : public dtkComposerNodeLeaf
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

class  dtkComposerNodeNumberNotalmosteq : public dtkComposerNodeLeaf
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

class  dtkComposerNodeNumberOperatorUnaryIncr : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryDecr : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnarySqrt : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnarySquare : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryLn : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryLog10 : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryExp : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryCos : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnarySin : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryTan : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryAcos : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryAsin : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryAtan : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryDeg2Rad : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryRad2Deg : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryInv : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryOpp : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryCeil : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryFloor : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryRound : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorUnaryAbs : public dtkComposerNodeNumberOperatorUnary
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

class  dtkComposerNodeNumberOperatorBinaryEucldiv : public dtkComposerNodeNumberOperatorBinary
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

class  dtkComposerNodeNumberOperatorBinaryMin: public dtkComposerNodeNumberOperatorBinary
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

class  dtkComposerNodeNumberOperatorBinaryMax : public dtkComposerNodeNumberOperatorBinary
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

class  dtkComposerNodeNumberOperatorBinaryLogn : public dtkComposerNodeNumberOperatorBinary
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

class  dtkComposerNodeNumberOperatorBinaryMinus : public dtkComposerNodeNumberOperatorBinary
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

class  dtkComposerNodeNumberOperatorBinaryModulo : public dtkComposerNodeNumberOperatorBinary
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

class  dtkComposerNodeNumberOperatorBinaryMult : public dtkComposerNodeNumberOperatorBinary
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

class  dtkComposerNodeNumberOperatorBinaryPlus : public dtkComposerNodeNumberOperatorBinary
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

class  dtkComposerNodeNumberOperatorBinaryPosnthroot : public dtkComposerNodeNumberOperatorBinary
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

class  dtkComposerNodeNumberOperatorBinaryPower : public dtkComposerNodeNumberOperatorBinary
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

class  dtkComposerNodeNumberOperatorBinaryRatio : public dtkComposerNodeNumberOperatorBinary
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

class  dtkComposerNodeNumberOperatorBinaryExpn : public dtkComposerNodeNumberOperatorBinary
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

class  dtkComposerNodeNumberComparatorEqual : public dtkComposerNodeNumberComparator
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

class  dtkComposerNodeNumberComparatorNotequal : public dtkComposerNodeNumberComparator
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

class  dtkComposerNodeNumberComparatorGt : public dtkComposerNodeNumberComparator
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

class  dtkComposerNodeNumberComparatorLt : public dtkComposerNodeNumberComparator
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

class  dtkComposerNodeNumberComparatorGte : public dtkComposerNodeNumberComparator
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

class  dtkComposerNodeNumberComparatorLte : public dtkComposerNodeNumberComparator
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

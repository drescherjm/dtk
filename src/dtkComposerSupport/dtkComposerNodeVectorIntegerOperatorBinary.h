/* dtkComposerNodeVectorIntegerOperatorBinary.h ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - Babette Lekouta, Inria.
 * Created: Thu Apr 26 16:14:44 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 29 15:16:03 2012 (+0200)
 *           By: tkloczko
 *     Update #: 39
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEVECTORINTEGEROPERATORBINARY_H
#define DTKCOMPOSERNODEVECTORINTEGEROPERATORBINARY_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinary interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorBinaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorIntegerOperatorBinary : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorIntegerOperatorBinary(void);
    ~dtkComposerNodeVectorIntegerOperatorBinary(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "vec_lhs";
        else
            return "vec_rhs";
    }

    inline QString outputLabelHint(int) {
        return "vector";
    }

protected:
    dtkComposerNodeVectorIntegerOperatorBinaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinaryScalar interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorBinaryScalarPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorIntegerOperatorBinaryScalar : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorIntegerOperatorBinaryScalar(void);
    ~dtkComposerNodeVectorIntegerOperatorBinaryScalar(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "vec_lhs";
        else
            return "vec_rhs";
    }

    inline QString outputLabelHint(int) {
        return "scalar";
    }

protected:
    dtkComposerNodeVectorIntegerOperatorBinaryScalarPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorHomothetic interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerOperatorHomotheticPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorIntegerOperatorHomothetic : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorIntegerOperatorHomothetic(void);
    ~dtkComposerNodeVectorIntegerOperatorHomothetic(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "vector";
        else
            return "scalar";
    }

    inline QString outputLabelHint(int) {
        return "vector";
    }

protected:
    dtkComposerNodeVectorIntegerOperatorHomotheticPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinary - SUM
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorIntegerOperatorBinarySum : public dtkComposerNodeVectorIntegerOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorInteger_sum";
    }

    inline QString titleHint(void) {
        return "Vector Integer Sum";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinary - SUBSTRACT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorIntegerOperatorBinarySubstract : public dtkComposerNodeVectorIntegerOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorInteger_substract";
    }

    inline QString titleHint(void) {
        return "Vector Integer Substract";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorBinaryScalar - DOT PRODUCT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorIntegerOperatorBinaryScalarDotProd : public dtkComposerNodeVectorIntegerOperatorBinaryScalar
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorInteger_dot_prod";
    }

    inline QString titleHint(void) {
        return "Vector Integer Dot Prod";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorHomothetic - MULTIPLY
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorIntegerOperatorHomotheticMult : public dtkComposerNodeVectorIntegerOperatorHomothetic
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorInteger_scal_mult";
    }

    inline QString titleHint(void) {
        return "Vector Integer: scal * vec";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerOperatorHomothetic - DIVIDE
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorIntegerOperatorHomotheticDivision : public dtkComposerNodeVectorIntegerOperatorHomothetic
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorInteger_scal_divide";
    }

    inline QString titleHint(void) {
        return "Vector Integer: vec / scal";
    }
};

#endif

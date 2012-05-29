/* dtkComposerNodeVectorRealOperatorBinary.h ---
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

#ifndef DTKCOMPOSERNODEVECTORREALOPERATORBINARY_H
#define DTKCOMPOSERNODEVECTORREALOPERATORBINARY_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinary interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorBinaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorBinary : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorRealOperatorBinary(void);
    ~dtkComposerNodeVectorRealOperatorBinary(void);

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
    dtkComposerNodeVectorRealOperatorBinaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinaryScalar interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorBinaryScalarPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorBinaryScalar : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorRealOperatorBinaryScalar(void);
    ~dtkComposerNodeVectorRealOperatorBinaryScalar(void);

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
    dtkComposerNodeVectorRealOperatorBinaryScalarPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorHomothetic interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorHomotheticPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorHomothetic : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorRealOperatorHomothetic(void);
    ~dtkComposerNodeVectorRealOperatorHomothetic(void);

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
    dtkComposerNodeVectorRealOperatorHomotheticPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinary - SUM
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorBinarySum : public dtkComposerNodeVectorRealOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorReal_sum";
    }

    inline QString titleHint(void) {
        return "VectorReal Sum";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinary - SUBSTRACT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorBinarySubstract : public dtkComposerNodeVectorRealOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorReal_substract";
    }

    inline QString titleHint(void) {
        return "VectorReal Substract";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorBinaryScalar - DOT PRODUCT
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorBinaryScalarDotProd : public dtkComposerNodeVectorRealOperatorBinaryScalar
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorReal_dot_prod";
    }

    inline QString titleHint(void) {
        return "VectorReal Dot Prod";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorHomothetic - MULTIPLY
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorHomotheticMult : public dtkComposerNodeVectorRealOperatorHomothetic
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorReal_scal_mult";
    }

    inline QString titleHint(void) {
        return "VectorReal: scal * vec";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorHomothetic - DIVIDE
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorHomotheticDivision : public dtkComposerNodeVectorRealOperatorHomothetic
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorReal_scal_divide";
    }

    inline QString titleHint(void) {
        return "VectorReal: vec / scal";
    }
};

#endif

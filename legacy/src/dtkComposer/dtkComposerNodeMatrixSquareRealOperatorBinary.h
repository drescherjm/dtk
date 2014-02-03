/* dtkComposerNodeMatrixSquareRealOperatorBinary.h ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - Babette Lekouta, Inria.
 * Created: Thu Apr 26 15:57:47 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jun 25 14:17:38 2012 (+0200)
 *           By: tkloczko
 *     Update #: 24
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEMATRIXSQUAREREALOPERATORBINARY_H
#define DTKCOMPOSERNODEMATRIXSQUAREREALOPERATORBINARY_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinary interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinary : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeMatrixSquareRealOperatorBinary(void);
    ~dtkComposerNodeMatrixSquareRealOperatorBinary(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "matrix_lhs";
        else
            return "matrix_rhs";
    }

    inline QString outputLabelHint(int) {
        return "matrix";
    }

protected:
    dtkComposerNodeMatrixSquareRealOperatorBinaryPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProduct interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryProductMVPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV  : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV(void);
    ~dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV (void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "matrix";
        else
            return "vector";
    }

    inline QString outputLabelHint(int) {
        return "vector";
    }

protected:
    dtkComposerNodeMatrixSquareRealOperatorBinaryProductMVPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrix interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVectorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVector : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVector(void);
    ~dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVector(void);

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "matrix";
        else if (port == 1)
            return "vector";
        else
            return "index";
    }

    inline QString outputLabelHint(int) {
        return "matrix ";
    }

protected:
    dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVectorPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinary Sum interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinarySum : public dtkComposerNodeMatrixSquareRealOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_sum";
    }

    inline QString titleHint(void) {
        return "Squared real matrix : Mat + Mat";
    }
};


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinary Substract interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinarySubstract: public dtkComposerNodeMatrixSquareRealOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_substract";
    }

    inline QString titleHint(void) {
        return "Squared real matrix : Mat - Mat";
    }
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinary Mult interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryMult: public dtkComposerNodeMatrixSquareRealOperatorBinary
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_mult";
    }

    inline QString titleHint(void) {
        return "Squared real matrix : Mat * Mat";
    }
};

// //////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductMV  interface
// /////////////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductMV : public dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_ProductMatrixVector";
    }

    inline QString titleHint(void) {
        return "Squared real matrix : Mat * Vec";
    }
};


// //////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV  interface
// /////////////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductVM : public dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_ProductVectorMatrix";
    }

    inline QString titleHint(void) {
        return "Squared real matrix : Vec * Mat";
    }
};

// //////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceRowMatrixByVector  interface
// /////////////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceRowMatrixByVector: public dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVector
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_ReplaceRowMatrixByVector";
    }

    inline QString titleHint(void) {
        return "Squared real matrix : replace row by vector";
    }
};

// //////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColMatrixByVector  interface
// /////////////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColMatrixByVector : public dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVector
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_ReplaceColMatrixByVector";
    }

    inline QString titleHint(void) {
        return "Squared real matrix : replace column by vector";
    }
};

#endif

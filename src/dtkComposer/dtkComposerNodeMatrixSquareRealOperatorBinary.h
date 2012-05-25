/* dtkComposerNodeMatrixSquareRealOperatorBinary.h ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - Babette Lekouta, Inria.
 * Created: Thu Apr 26 15:57:47 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 16:44:41 2012 (+0200)
 *           By: sblekout
 *     Update #: 12
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef dtkComposerNodeMatrixSquareRealOperatorBinary_H
#define dtkComposerNodeMatrixSquareRealOperatorBinary_H

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
// dtkComposerNodeMatrixSquareRealOperatorBinaryScalar interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryScalarPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryScalar : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMatrixSquareRealOperatorBinaryScalar(void);
    ~dtkComposerNodeMatrixSquareRealOperatorBinaryScalar(void);

    inline QString inputLabelHint(int port) {
        return "matrix";
    }

    inline QString outputLabelHint(int) {
        return "scalar";
    }

protected:
    dtkComposerNodeMatrixSquareRealOperatorBinaryScalarPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryRightProduct interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryRightProduct : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMatrixSquareRealOperatorBinaryRightProduct (void);
    ~dtkComposerNodeMatrixSquareRealOperatorBinaryRightProduct(void);

     inline QString inputLabelHint(int port) {
         if (port == 0)
             return "matrix";
         else
             return "vector_transpose";
     }

     inline QString outputLabelHint(int) {
         return "matrix";
     }

protected:
    dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProduct interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProduct  : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProduct(void);
    ~dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProduct (void);

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
    dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrix interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrixPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrix : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrix(void);
    ~dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrix(void);

     inline QString inputLabelHint(int port) {
         if (port == 0)
             return "matrix";
         else if (port == 1)
             return "vector";
         else
             return "index_value";
     }

     inline QString outputLabelHint(int) {
         return "matrix ";
     }

protected:
    dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrixPrivate *d;
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
        return "MatrixSquare Real Sum";
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
        return "MatrixSquare Real Substract";
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
        return "MatrixSquare Real Mult";
    }
};

// //////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryScalarProduct  interface
// /////////////////////////////////////////////////////////////////////////    // Revoir bien le nom

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryScalarProduct : public dtkComposerNodeMatrixSquareRealOperatorBinaryScalar
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_product";
    }

    inline QString titleHint(void) {
        return "MatrixSquare Real Product";
    }
};

// //////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductMV  interface
// /////////////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductMV : public dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProduct
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_ProductMatrixVector";
    }

    inline QString titleHint(void) {
        return "MatrixSquare Real ProductMatrixVector";
    }
};


// //////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV  interface
// /////////////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductVM : public dtkComposerNodeMatrixSquareRealOperatorBinaryRightProduct
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_ProductVectorMatrix";
    }

    inline QString titleHint(void) {
        return "MatrixSquare Real ProductVectorMatrix";
    }
};

// //////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryAddRowVM  interface
// /////////////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryAddRowVectorMatrix: public dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrix
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_AddRowVectorToMatrix";
    }

    inline QString titleHint(void) {
        return "MatrixSquare Real AddRowVectorToMatrix";
    }
};

// //////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryAddColVM  interface
// /////////////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorBinaryAddColVectorMatrix : public dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrix
{
public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_AddColVectorToMatrix";
    }

    inline QString titleHint(void) {
        return "MatrixSquare Real AddColVectorToMatrix";
    }
};

#endif

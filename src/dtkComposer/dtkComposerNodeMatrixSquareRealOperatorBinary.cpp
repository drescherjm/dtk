/* dtkComposerNodeMatrixSquareRealOperatorBinary.cpp ---
 *
 * Author: slekout
 * Copyright (C) 2011 - Babette lekouta, Inria.
 * Created: Thu Apr 26 15:58:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated:
 *           By:
 *     Update #:
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerNodeMatrixSquareRealOperatorBinary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_rhs;


public:
    dtkComposerTransmitterEmitter<dtkMatrixSquareReal> emitter_matrix;
};

dtkComposerNodeMatrixSquareRealOperatorBinary::dtkComposerNodeMatrixSquareRealOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorBinaryPrivate)
{
    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);
    this->appendEmitter(&d->emitter_matrix);
}

dtkComposerNodeMatrixSquareRealOperatorBinary::~dtkComposerNodeMatrixSquareRealOperatorBinary(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_matrix;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_val;
};

dtkComposerNodeMatrixSquareRealOperatorBinaryScalar::dtkComposerNodeMatrixSquareRealOperatorBinaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorBinaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_matrix);
    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeMatrixSquareRealOperatorBinaryScalar::~dtkComposerNodeMatrixSquareRealOperatorBinaryScalar(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryRightProduct
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_matrix;
    dtkComposerTransmitterReceiver<dtkVectorReal>       receiver_vector;


public:
    dtkComposerTransmitterEmitter<dtkMatrixSquareReal> emitter_matrix;
};

dtkComposerNodeMatrixSquareRealOperatorBinaryRightProduct::dtkComposerNodeMatrixSquareRealOperatorBinaryRightProduct(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductPrivate)
{
    this->appendReceiver(&d->receiver_matrix);
    this->appendReceiver(&d->receiver_vector);
    this->appendEmitter(&d->emitter_matrix);
}

dtkComposerNodeMatrixSquareRealOperatorBinaryRightProduct::~dtkComposerNodeMatrixSquareRealOperatorBinaryRightProduct(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProduct
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_matrix;
    dtkComposerTransmitterReceiver<dtkVectorReal>       receiver_vector;


public:
    dtkComposerTransmitterEmitter<dtkVectorReal>        emitter_vector;
};

dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProduct::dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProduct(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductPrivate)
{
    this->appendReceiver(&d->receiver_matrix);
    this->appendReceiver(&d->receiver_vector);
    this->appendEmitter(&d->emitter_vector);
}

dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProduct::~dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProduct(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrix
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrixPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_matrix;
    dtkComposerTransmitterReceiver<dtkVectorReal>       receiver_vector;
    dtkComposerTransmitterReceiver<qreal>              receiver_index;

public:
    dtkComposerTransmitterEmitter<dtkMatrixSquareReal> emitter_matrix;
};

dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrix::dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrix(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrixPrivate)
{
    this->appendReceiver(&d->receiver_matrix);
    this->appendReceiver(&d->receiver_vector);
    this->appendReceiver(&d->receiver_index);
    this->appendEmitter(&d->emitter_matrix);
}

dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrix::~dtkComposerNodeMatrixSquareRealOperatorBinaryAddVecortToMatrix(void)
{
    delete d;

    d = NULL;
}


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinary - Sum
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinarySum::run(void)
{
    bool isSquare = d->receiver_lhs.data().getRows()== d->receiver_lhs.data().getCols() && d->receiver_rhs.data().getRows()== d->receiver_rhs.data().getCols();

    if ( isSquare && (d->receiver_lhs.data().getRows()== d->receiver_rhs.data().getRows()))

        d->emitter_matrix.setData(d->receiver_lhs.data() + d->receiver_rhs.data());

    else
        dtkWarn()<< "Matrices do not have the same size" ;

}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinary - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinarySubstract::run(void)
{
    bool isSquare = d->receiver_lhs.data().getRows()== d->receiver_lhs.data().getCols() && d->receiver_rhs.data().getRows()== d->receiver_rhs.data().getCols();

    if ( isSquare && (d->receiver_lhs.data().getRows()== d->receiver_rhs.data().getRows()))

        d->emitter_matrix.setData(d->receiver_lhs.data() - d->receiver_rhs.data());

    else
        dtkWarn()<< "Matrices do not have the same size" ;

}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryScalar - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryMult::run(void)
{
    bool isSquare = d->receiver_lhs.data().getRows()== d->receiver_lhs.data().getCols() && d->receiver_rhs.data().getRows()== d->receiver_rhs.data().getCols();

    if ( isSquare && (d->receiver_lhs.data().getRows()== d->receiver_rhs.data().getRows()))

        d->emitter_matrix.setData(d->receiver_lhs.data() * d->receiver_rhs.data());

    else
        dtkWarn()<< "Matrices do not have the same size" ;

}


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryScalar - Product
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryScalarProduct::run(void)
{
    // a faire plus tard
}














//// a revoir demain  car rien me marche



// ///////////////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductMV - Product Vector Matrix
// //////////////////////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductMV::run(void)
{
//    bool isSquare = d->receiver_matrix.data().getRows()== d->receiver_matrix.data().getCols();
//    dtkVectorReal vec =d->receiver_vector.data();
//    dtkMatrixSquareReal matrix = d->receiver_matrix.data();

//    if ( isSquare && (d->receiver_matrix.data().getRows()== d->receiver_vector.data().getCols())) {

//        // d->emitter_vector.setData(d->receiver_matrix.data() * d->receiver_vector.data());

//        for(int i = 0 ; i < d->receiver_matrix.data().getRows(); i++){

//            for(int j = 0 ; j < d->receiver_vector.data().getRows(); i++){


//                vec[i] = matrix [i][j]*vec[i];

//                qDebug()<< i<< vec[i];

//            }
//        }
//    }

}
// /////////////////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductVM - Product Matrix Vector
// ////////////////////////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductVM::run(void)
{
    // d->emitter_matrix.setData(dtkInverse(d->receiver_matrix.data()));

}

// //////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryAddRowVM - Add row to Matrix
// //////////////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryAddRowVectorMatrix::run(void)
{
    //  d->emitter_val.setData(dtkDeterminant(d->receiver_matrix.data()));
}

// ///////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryAddColVM - Add col to Matrix
// //////////////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryAddColVectorMatrix::run(void)
{
    //  d->emitter_val.setData(dtkMatrixSquaredTrace(d->receiver_matrix.data()));
}

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
// dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryProductMVPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_matrix;
    dtkComposerTransmitterReceiver<dtkVectorReal>       receiver_vector;


public:
    dtkComposerTransmitterEmitter<dtkVectorReal>        emitter_vector;
};

dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV::dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorBinaryProductMVPrivate)
{
    this->appendReceiver(&d->receiver_matrix);
    this->appendReceiver(&d->receiver_vector);
    this->appendEmitter(&d->emitter_vector);
}

dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV::~dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVector
// /////////////////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVectorPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_matrix;
    dtkComposerTransmitterReceiver<dtkVectorReal>       receiver_vector;
    dtkComposerTransmitterVariant                       receiver_index;

public:
    dtkComposerTransmitterEmitter<dtkMatrixSquareReal>   emitter_matrix;
};

dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVector::dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVector(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVectorPrivate)
{
    this->appendReceiver(&d->receiver_matrix);
    this->appendReceiver(&d->receiver_vector);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong;
    d->receiver_index.setTypes(variant_list);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_matrix);
}

dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVector::~dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVector(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinary - Sum
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinarySum::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {

        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_matrix.setData(dtkMatrixSquareReal());

    } else {
        dtkMatrixSquareReal& matrix1(d->receiver_lhs.data());
        dtkMatrixSquareReal& matrix2(d->receiver_rhs.data());

        if ( matrix1.getRows() == matrix2.getRows())
            d->emitter_matrix.setData(matrix1 + matrix2 );

        else {
            dtkWarn()<< "Matrices do not have the same size";
            d->emitter_matrix.setData(dtkMatrixSquareReal());
        }
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinary - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinarySubstract::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {

        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_matrix.setData(dtkMatrixSquareReal());

    } else {
        dtkMatrixSquareReal& matrix1(d->receiver_lhs.data());
        dtkMatrixSquareReal& matrix2(d->receiver_rhs.data());

        if ( matrix1.getRows() == matrix2.getRows())
            d->emitter_matrix.setData(matrix1 - matrix2 );

        else {
            dtkWarn()<< "Matrices do not have the same size";
            d->emitter_matrix.setData(dtkMatrixSquareReal());
        }

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinary - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryMult::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {

        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_matrix.setData(dtkMatrixSquareReal());

    } else {
        dtkMatrixSquareReal& matrix1(d->receiver_lhs.data());
        dtkMatrixSquareReal& matrix2(d->receiver_rhs.data());

        if ( matrix1.getRows() == matrix2.getRows())
            d->emitter_matrix.setData(matrix1 * matrix2 );

        else {
            dtkWarn()<< "Matrices do not have the same size";
            d->emitter_matrix.setData(dtkMatrixSquareReal());
        }
    }
}

// ///////////////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV - Product Matrix Vector
// //////////////////////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductMV::run(void)
{
    if (d->receiver_matrix.isEmpty() || d->receiver_vector.isEmpty()) {

        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.setData(dtkVectorReal());

    } else {
        dtkMatrixSquareReal& matrix(d->receiver_matrix.data());
        dtkVectorReal& vector(d->receiver_vector.data());

        if ( matrix.getCols() == vector.getRows() )
            d->emitter_vector.setData(matrix * vector );

        else {
            dtkWarn() << "Matrix's row and vector's column are different size. Nothing is done";
            d->emitter_vector.setData(dtkVectorReal());
        }
    }
}


// /////////////////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV - Product Vector Matrix
// ////////////////////////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductVM::run(void)
{
    if (d->receiver_matrix.isEmpty() || d->receiver_vector.isEmpty()) {

        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_vector.setData(dtkVectorReal());

    } else {
        dtkMatrixSquareReal& matrix(d->receiver_matrix.data());
        dtkVectorReal vec(d->receiver_vector.data());
        dtkVectorReal result = dtkVectorReal(vec.getRows()) ;

        if (matrix.getCols() == vec.getRows()){

            for( int i = 0; i< matrix.getCols();++i ){
                for( int j = 0; j< vec.getRows();++j )
                    result[i] += vec[j] * matrix[j][i] ;
            }

            d->emitter_vector.setData(result);
        }

        else {
            dtkWarn() << "Matrix's row and vector's column are different size. Nothing is done";
            d->emitter_vector.setData(dtkVectorReal());
        }
    }
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceRowAndColMatrixByVector  Replace Row to Matrix
// ///////////////////////////////////////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceRowMatrixByVector::run(void)
{
    if (d->receiver_matrix.isEmpty() || d->receiver_vector.isEmpty()) {

        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_matrix.setData(dtkMatrixSquareReal());

    } else {

        if (qvariant_cast<qlonglong>(d->receiver_index.data()) < d->receiver_matrix.data().getRows()){

            dtkMatrixSquareReal& matrix (d->receiver_matrix.data());
            qlonglong value =  qvariant_cast<qlonglong>(d->receiver_index.data());
            dtkVectorReal vec(d->receiver_vector.data());

            for( int j = 0; j < matrix.getCols(); ++j)
                matrix[value][j]= vec[j] ;

            d->emitter_matrix.setData(matrix);

        } else {
            dtkWarn() << "index > row of the marix. Nothing is done" ;
            d->emitter_matrix.setData(dtkMatrixSquareReal());
        }
    }
}

// ////////////////////////////////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceRowAndColMatrixByVector - Replace Col to Matrix
// ////////////////////////////////////////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColMatrixByVector::run(void)
{
    if (d->receiver_matrix.isEmpty() || d->receiver_vector.isEmpty()) {

        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter_matrix.setData(dtkMatrixSquareReal());

    } else {

        if (qvariant_cast<qlonglong>(d->receiver_index.data())< d->receiver_matrix.data().getRows()){

            dtkMatrixSquareReal& matrix (d->receiver_matrix.data());
            qlonglong value =  qvariant_cast<qlonglong>(d->receiver_index.data());
            dtkVectorReal vec(d->receiver_vector.data());

            for ( int i = 0; i < matrix.getRows(); ++i) {
                for ( int j = 0; j < matrix.getRows(); ++j)
                    matrix[i][value]= vec[i] ;
                dtkDebug()<< matrix ;
                d->emitter_matrix.setData(matrix); }

        } else {
            dtkWarn() << "index > row of the marix. Nothing is done" ;
            d->emitter_matrix.setData(dtkMatrixSquareReal());

        }
    }
}

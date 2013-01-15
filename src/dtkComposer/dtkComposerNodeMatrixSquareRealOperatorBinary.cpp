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

public:
    dtkMatrixSquareReal *matrix;
};

dtkComposerNodeMatrixSquareRealOperatorBinary::dtkComposerNodeMatrixSquareRealOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorBinaryPrivate)
{
    d->matrix = NULL;

    this->appendReceiver(&d->receiver_lhs);
    this->appendReceiver(&d->receiver_rhs);
    this->appendEmitter(&d->emitter_matrix);
}

dtkComposerNodeMatrixSquareRealOperatorBinary::~dtkComposerNodeMatrixSquareRealOperatorBinary(void)
{
    if (d->matrix)
        delete d->matrix;

    d->matrix = NULL;

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

public:
    dtkVectorReal *vector;
};

dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV::dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorBinaryProductMVPrivate)
{
    d->vector = NULL;

    this->appendReceiver(&d->receiver_matrix);
    this->appendReceiver(&d->receiver_vector);
    this->appendEmitter(&d->emitter_vector);
}

dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV::~dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV(void)
{
    if (d->vector)
        delete d->vector;

    d->vector = NULL;

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

    QList<int> variant_list;

    variant_list << QMetaType::LongLong;
    d->receiver_index.setDataTypes(variant_list);
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

        if (d->matrix)
            d->matrix->deallocate();

    } else {

        if (!d->matrix) {
            d->matrix = new dtkMatrixSquareReal();
            d->emitter_matrix.setData(d->matrix);
        }

        const dtkMatrixSquareReal *m_lhs = d->receiver_lhs.constData();
        const dtkMatrixSquareReal *m_rhs = d->receiver_rhs.constData();

        if (m_lhs->size() != m_rhs->size()) {
            dtkWarn()<< "Input matrices do not have the same size. Nothing is done";
            d->matrix->deallocate();
        } else {
            *(d->matrix) = (*m_lhs + *m_rhs);
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

        if (d->matrix)
            d->matrix->deallocate();

    } else {

        if (!d->matrix) {
            d->matrix = new dtkMatrixSquareReal();
            d->emitter_matrix.setData(d->matrix);
        }

        const dtkMatrixSquareReal *m_lhs = d->receiver_lhs.constData();
        const dtkMatrixSquareReal *m_rhs = d->receiver_rhs.constData();

        if (m_lhs->size() != m_rhs->size()) {
            dtkWarn()<< "Input matrices do not have the same size. Nothing is done";
            d->matrix->deallocate();
        } else {
            *(d->matrix) = (*m_lhs - *m_rhs);
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

        if (d->matrix)
            d->matrix->deallocate();

    } else {

        if (!d->matrix) {
            d->matrix = new dtkMatrixSquareReal();
            d->emitter_matrix.setData(d->matrix);
        }

        const dtkMatrixSquareReal *m_lhs = d->receiver_lhs.constData();
        const dtkMatrixSquareReal *m_rhs = d->receiver_rhs.constData();

        if (m_lhs->size() != m_rhs->size()) {
            dtkWarn()<< "Input matrices do not have the same size. Nothing is done";
            d->matrix->deallocate();
        } else {
            *(d->matrix) = (*m_lhs * *m_rhs);
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

        if (d->vector)
            d->vector->deallocate();

    } else {

        if (!d->vector) {
            d->vector = new dtkVectorReal();
            d->emitter_vector.setData(d->vector);
        }

        const dtkMatrixSquareReal *matrix = d->receiver_matrix.constData();
        const dtkVectorReal       *vector = d->receiver_vector.constData();

        if ( matrix->size() != vector->size() ) {
            dtkWarn() << "Matrix's row and vector's column are different size. Nothing is done";
            d->vector->deallocate();
        } else {
            *d->vector = (*matrix) * (*vector);
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

        if (d->vector)
            d->vector->deallocate();

    } else {

        const dtkMatrixSquareReal *matrix = d->receiver_matrix.constData();
        const dtkVectorReal       *vector = d->receiver_vector.constData();

        if (!d->vector) {
            d->vector = new dtkVectorReal();
            d->emitter_vector.setData(d->vector);
        }

        if ( matrix->size() != vector->size() ) {
            dtkWarn() << "Matrix's row and vector's column are different size. Nothing is done";
            d->vector->deallocate();
        } else {
            d->vector->allocate(vector->size());

            for(qlonglong i = 0; i < matrix->size(); ++i) {
                for(qlonglong j = 0; j < vector->size(); ++j) {
                    (*d->vector)[i] += (*vector)[j] * (*matrix)[j][i] ;
                }
            }
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

        d->emitter_matrix.clearData();

    } else {

        qlonglong row_index = *d->receiver_index.data<qlonglong>();
        dtkMatrixSquareReal *matrix = d->receiver_matrix.data();

        if (row_index >= matrix->size()) {
            dtkWarn() << "Row index = " << row_index << " >= matrix size = " << matrix->size() << ". Nothing is done.";

            d->emitter_matrix.clearData();

        } else {

            const dtkVectorReal *vector = d->receiver_vector.constData();

            for(qlonglong j = 0; j < matrix->size(); ++j)
                (*matrix)[row_index][j] = (*vector)[j];

            d->emitter_matrix.setData(matrix);
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

        d->emitter_matrix.clearData();

    } else {

        qlonglong col_index = *d->receiver_index.data<qlonglong>();
        dtkMatrixSquareReal *matrix = d->receiver_matrix.data();

        if (col_index >= matrix->size()) {
            dtkWarn() << "Column index = " << col_index << " >= matrix size = " << matrix->size() << ". Nothing is done.";

            d->emitter_matrix.clearData();

        } else {

            const dtkVectorReal *vector = d->receiver_vector.constData();

            for(qlonglong i = 0; i < matrix->size(); ++i)
                (*matrix)[i][col_index] = (*vector)[i];

            d->emitter_matrix.setData(matrix);
        }
    }
}

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
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal*> receiver_lhs;
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal*> receiver_rhs;


public:
    dtkComposerTransmitterEmitter<dtkMatrixSquareReal*> emitter_matrix;

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
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal*> receiver_matrix;
    dtkComposerTransmitterReceiver<dtkVectorReal*>       receiver_vector;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal*>        emitter_vector;

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
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal*> receiver_matrix;
    dtkComposerTransmitterReceiver<dtkVectorReal*>       receiver_vector;
    dtkComposerTransmitterVariant                       receiver_index;

public:
    dtkComposerTransmitterEmitter<dtkMatrixSquareReal*>   emitter_matrix;
};

dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVector::dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVector(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColAndRowMatrixByVectorPrivate)
{
    this->appendReceiver(&d->receiver_matrix);
    this->appendReceiver(&d->receiver_vector);

    QVector<const dtkComposerType*> variant_list;
    variant_list << dtkComposerTypeInfo<qlonglong>::type();
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
        dtkWarn() << "dtkComposerNodeMatrixSquareRealOperatorBinarySum::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";

        if (d->matrix)
            d->matrix->deallocate();

        d->emitter_matrix.clearData();

    } else {

        if (!d->matrix) {
            d->matrix = new dtkMatrixSquareReal();
        }

        const dtkMatrixSquareReal *m_lhs = d->receiver_lhs.constData();
        const dtkMatrixSquareReal *m_rhs = d->receiver_rhs.constData();

        if (!m_lhs || !m_rhs) {
            dtkError() << "dtkComposerNodeMatrixSquareRealOperatorBinarySum::" << Q_FUNC_INFO << "Input matrices not set. Nothing is done";
            d->matrix->deallocate();
            d->emitter_matrix.clearData();
            return;
        }

        if (m_lhs->size() != m_rhs->size()) {
            dtkWarn() << "dtkComposerNodeMatrixSquareRealOperatorBinarySum::" << Q_FUNC_INFO << "Input matrices do not have the same size. Nothing is done";
            d->matrix->deallocate();
            d->emitter_matrix.clearData();
        } else {
            *(d->matrix) = (*m_lhs + *m_rhs);
            d->emitter_matrix.setData(d->matrix);
        }
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinary - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinarySubstract::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "dtkComposerNodeMatrixSquareRealOperatorBinarySubstract::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";

        if (d->matrix)
            d->matrix->deallocate();

        d->emitter_matrix.clearData();

    } else {

        if (!d->matrix) {
            d->matrix = new dtkMatrixSquareReal();
        }

        const dtkMatrixSquareReal *m_lhs = d->receiver_lhs.constData();
        const dtkMatrixSquareReal *m_rhs = d->receiver_rhs.constData();

        if (!m_lhs || !m_rhs) {
            dtkError() << "dtkComposerNodeMatrixSquareRealOperatorBinarySubstract::" << Q_FUNC_INFO << "Input matrices not set. Nothing is done";
            d->matrix->deallocate();
            d->emitter_matrix.clearData();
            return;
        }

        if (m_lhs->size() != m_rhs->size()) {
            dtkWarn() << "dtkComposerNodeMatrixSquareRealOperatorBinarySubstract::" << Q_FUNC_INFO << "Input matrices do not have the same size. Nothing is done";
            d->matrix->deallocate();
            d->emitter_matrix.clearData();
        } else {
            *(d->matrix) = (*m_lhs - *m_rhs);
            d->emitter_matrix.setData(d->matrix);
        }
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinary - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryMult::run(void)
{
    if (d->receiver_lhs.isEmpty() || d->receiver_rhs.isEmpty()) {
        dtkWarn() << "dtkComposerNodeMatrixSquareRealOperatorBinaryMult::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";

        if (d->matrix)
            d->matrix->deallocate();

        d->emitter_matrix.clearData();

    } else {

        if (!d->matrix) {
            d->matrix = new dtkMatrixSquareReal();
        }

        const dtkMatrixSquareReal *m_lhs = d->receiver_lhs.constData();
        const dtkMatrixSquareReal *m_rhs = d->receiver_rhs.constData();

        if (!m_lhs || !m_rhs) {
            dtkError() << "dtkComposerNodeMatrixSquareRealOperatorBinaryMult::" << Q_FUNC_INFO << "Input matrices not set. Nothing is done";
            d->matrix->deallocate();
            d->emitter_matrix.clearData();
            return;
        }

        if (m_lhs->size() != m_rhs->size()) {
            dtkWarn() << "dtkComposerNodeMatrixSquareRealOperatorBinaryMult::" << Q_FUNC_INFO << "Input matrices do not have the same size. Nothing is done";
            d->matrix->deallocate();
            d->emitter_matrix.clearData();
        } else {
            *(d->matrix) = (*m_lhs * *m_rhs);
            d->emitter_matrix.setData(d->matrix);
        }
    }
}

// ///////////////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV - Product Matrix Vector
// //////////////////////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductMV::run(void)
{
    if (d->receiver_matrix.isEmpty() || d->receiver_vector.isEmpty()) {
        dtkWarn() << "dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductMV::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";

        if (d->vector)
            d->vector->deallocate();

        d->emitter_vector.clearData();

    } else {

        if (!d->vector) {
            d->vector = new dtkVectorReal();
        }

        const dtkMatrixSquareReal *matrix = d->receiver_matrix.constData();
        const dtkVectorReal       *vector = d->receiver_vector.constData();

        if (!matrix || !vector) {
            dtkError() << "dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductMV::" << Q_FUNC_INFO << "Input matrix or input vector not set. Nothing is done";
            d->vector->deallocate();
            d->emitter_vector.clearData();
            return;
        }

        if ( matrix->size() != vector->size() ) {
            dtkWarn() << "dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductMV::" << Q_FUNC_INFO << "Matrix's row and vector's column have different size. Nothing is done";
            d->vector->deallocate();
            d->emitter_vector.clearData();
        } else {
            *d->vector = (*matrix) * (*vector);
            d->emitter_vector.setData(d->vector);
        }
    }
}


// /////////////////////////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorBinaryProductMV - Product Vector Matrix
// ////////////////////////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductVM::run(void)
{
    if (d->receiver_matrix.isEmpty() || d->receiver_vector.isEmpty()) {
        dtkWarn() << "dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductVM::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";

        if (d->vector)
            d->vector->deallocate();

        d->emitter_vector.clearData();

    } else {

        const dtkMatrixSquareReal *matrix = d->receiver_matrix.constData();
        const dtkVectorReal       *vector = d->receiver_vector.constData();

        if (!matrix || !vector) {
            dtkError() << "dtkComposerNodeMatrixSquareRealOperatorBinaryRightProductMV::" << Q_FUNC_INFO << "Input matrix or input vector not set. Nothing is done";
            d->vector->deallocate();
            d->emitter_vector.clearData();
            return;
        }

        if (!d->vector) {
            d->vector = new dtkVectorReal();
        }

        if ( matrix->size() != vector->size() ) {
            dtkWarn() << "dtkComposerNodeMatrixSquareRealOperatorBinaryLeftProductVM::" << Q_FUNC_INFO << "Matrix's row and vector's column are different size. Nothing is done";
            d->vector->deallocate();
            d->emitter_vector.clearData();
        } else {
            d->vector->allocate(vector->size());

            for(qlonglong i = 0; i < matrix->size(); ++i) {
                for(qlonglong j = 0; j < vector->size(); ++j) {
                    (*d->vector)[i] += (*vector)[j] * (*matrix)[j][i] ;
                }
            }
            d->emitter_vector.setData(d->vector);
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

        qlonglong row_index = d->receiver_index.data<qlonglong>();
        dtkMatrixSquareReal *matrix = d->receiver_matrix.data();

        if (!matrix) {
            dtkError() << "dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceRowMatrixByVector::" << Q_FUNC_INFO << "Input matrix not set. Nothing is done";
            d->emitter_matrix.clearData();
            return;
        }

        if (row_index >= matrix->size()) {
            dtkWarn() << "Row index = " << row_index << " >= matrix size = " << matrix->size() << ". Nothing is done.";

            d->emitter_matrix.clearData();

        } else {

            const dtkVectorReal *vector = d->receiver_vector.constData();

            if (!vector) {
                dtkError() << "dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceRowMatrixByVector::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
                d->emitter_matrix.clearData();
                return;
            }

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

        qlonglong col_index = d->receiver_index.data<qlonglong>();
        dtkMatrixSquareReal *matrix = d->receiver_matrix.data();

        if (!matrix) {
            dtkError() << "dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceColMatrixByVector::" << Q_FUNC_INFO << "Input matrix not set. Nothing is done";
            d->emitter_matrix.clearData();
            return;
        }

        if (col_index >= matrix->size()) {
            dtkWarn() << "Column index = " << col_index << " >= matrix size = " << matrix->size() << ". Nothing is done.";

            d->emitter_matrix.clearData();

        } else {

            const dtkVectorReal *vector = d->receiver_vector.constData();

            if (!vector) {
                dtkError() << "dtkComposerNodeMatrixSquareRealOperatorBinaryReplaceRowMatrixByVector::" << Q_FUNC_INFO << "Input vector not set. Nothing is done";
                d->emitter_matrix.clearData();
                return;
            }

            for(qlonglong i = 0; i < matrix->size(); ++i)
                (*matrix)[i][col_index] = (*vector)[i];

            d->emitter_matrix.setData(matrix);
        }
    }
}

/* dtkComposerNodeMatrixSquareRealOperatorUnary.cpp ---
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


#include "dtkComposerNodeMatrixSquareRealOperatorUnary.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_matrix;

public:
    dtkComposerTransmitterEmitter<dtkMatrixSquareReal> emitter_matrix;
};

dtkComposerNodeMatrixSquareRealOperatorUnary::dtkComposerNodeMatrixSquareRealOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorUnaryPrivate)
{
    this->appendReceiver(&d->receiver_matrix);
    this->appendEmitter(&d->emitter_matrix);
}

dtkComposerNodeMatrixSquareRealOperatorUnary::~dtkComposerNodeMatrixSquareRealOperatorUnary(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorUnaryScalar
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorUnaryScalarPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_matrix;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_val;
};

dtkComposerNodeMatrixSquareRealOperatorUnaryScalar::dtkComposerNodeMatrixSquareRealOperatorUnaryScalar(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorUnaryScalarPrivate)
{
    this->appendReceiver(&d->receiver_matrix);
    this->appendEmitter(&d->emitter_val);
}

dtkComposerNodeMatrixSquareRealOperatorUnaryScalar::~dtkComposerNodeMatrixSquareRealOperatorUnaryScalar(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorUnary - Transpose
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorUnaryTranspose::run(void)
{
    if (!d->receiver_matrix.isEmpty()) {
        dtkMatrixSquareReal& matrix = d->receiver_matrix.data();
        d->emitter_matrix.setData(dtkTranspose(matrix));

    } else {
        dtkWarn() << "Input not specified. Nothing is done";
        d->emitter_matrix.setData(dtkMatrixSquareReal());
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorUnary - Inverse
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorUnaryInverse::run(void)
{
    if (!d->receiver_matrix.isEmpty()) {
        dtkMatrixSquareReal& matrix = d->receiver_matrix.data();
        d->emitter_matrix.setData(dtkInverse(matrix));

    } else {
        dtkWarn() << "Input not specified. Nothing is done";
        d->emitter_matrix.setData(dtkMatrixSquareReal());
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorUnaryScalar - Determinant
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorUnaryScalarDeterminant::run(void)
{
    if (!d->receiver_matrix.isEmpty()){
        dtkMatrixSquareReal& matrix = d->receiver_matrix.data();
        d->emitter_val.setData(dtkDeterminant(matrix));

    }else {
        dtkWarn() << "Input not specified. Nothing is done";
        d->emitter_val.setData(qreal());
    }
}
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealOperatorUnaryScalar - Trace
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeMatrixSquareRealOperatorUnaryScalarTrace::run(void)
{
    if (!d->receiver_matrix.isEmpty()){
        dtkMatrixSquareReal& matrix = d->receiver_matrix.data();
        d->emitter_val.setData(dtkMatrixSquaredTrace(matrix));

    } else {
        dtkWarn() << "Input not specified. Nothing is done";
        d->emitter_val.setData(qreal());
    }
}

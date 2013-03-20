/* dtkComposerNodeMatrixSquareRealr.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette Lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2012 Thu Dec 20 09:13:11 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 97
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeMatrixSquareReal.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal*> receiver_matrix;
    dtkComposerTransmitterVariant receiver_size;
    dtkComposerTransmitterVariant receiver_value;

public:
    dtkComposerTransmitterEmitter<dtkMatrixSquareReal*> emitter_matrix;
    dtkComposerTransmitterEmitter<qlonglong> emitter_size;

public:
    dtkMatrixSquareReal *matrix;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareReal implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMatrixSquareReal::dtkComposerNodeMatrixSquareReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealPrivate)
{
    d->matrix = NULL;

    this->appendReceiver(&d->receiver_matrix);


    QVector<const dtkComposerType*> variant_list;

    variant_list << dtkComposerTypeInfo<qlonglong>::type();
    d->receiver_size.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_size);

    variant_list << dtkComposerTypeInfo<double>::type();
    d->receiver_value.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_matrix);
    
    this->appendEmitter(&d->emitter_size);
}

dtkComposerNodeMatrixSquareReal::~dtkComposerNodeMatrixSquareReal(void)
{
    if (d->matrix)
        delete d->matrix;

    d->matrix = NULL;

    delete d;

    d = NULL;
}

QString dtkComposerNodeMatrixSquareReal::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "matrix";
        break;
    case 1:
        return "size";
        break;
    case 2:
        return "value";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeMatrixSquareReal::outputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "matrix";
        break;
    case 1:
        return "size";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeMatrixSquareReal::run(void)
{
    if (!d->receiver_matrix.isEmpty()) {

        dtkMatrixSquareReal *matrix = d->receiver_matrix.constData();

        if (!matrix) {
            dtkError() << "dtkComposerNodeMatrixSquareReal::" << Q_FUNC_INFO << "Input matrix is not defined.";
            d->emitter_size.clearData();
            d->emitter_matrix.clearData();
            return;
        }

        d->emitter_size.setData(matrix->size());
        d->emitter_matrix.setData(matrix);

    } else {

        if (!d->matrix)
            d->matrix = new dtkMatrixSquareReal();

        qlonglong size = 0;
        if (!d->receiver_size.isEmpty())
            size = d->receiver_size.data<qlonglong>();

        if (size == 0) {

            d->matrix->allocate(0);

            dtkWarn() << "dtkComposerNodeMatrixSquareReal::" << Q_FUNC_INFO << "The size of the matrix is zero.";

        } else {

            if (size != d->matrix->size())
                d->matrix->allocate(size);

            qreal value = 0.;
            if (!d->receiver_value.isEmpty())
                value = d->receiver_value.data<qreal>();

            d->matrix->fill(value);
        }

        d->emitter_size.setData(size);
        d->emitter_matrix.setData(d->matrix);
    }
}

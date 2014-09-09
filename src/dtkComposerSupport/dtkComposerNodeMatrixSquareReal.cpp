/* dtkComposerNodeMatrixSquareRealr.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette Lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 17:25:15 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 79
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

#include <dtkMathSupport/dtkMatrix.h>

#include <dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_matrix;
    dtkComposerTransmitterVariant receiver_size;
    dtkComposerTransmitterVariant receiver_value;

public:
    dtkComposerTransmitterEmitter<dtkMatrixSquareReal> emitter_matrix;
    dtkComposerTransmitterEmitter<qlonglong> emitter_size;

public:
    dtkMatrixSquareReal *matrix;
    qlonglong size;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareReal implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMatrixSquareReal::dtkComposerNodeMatrixSquareReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealPrivate)
{
    d->matrix = NULL;
    d->size = 0;

    this->appendReceiver(&d->receiver_matrix);

    QList<int> variant_list;

    variant_list << QMetaType::LongLong;
    d->receiver_size.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_size);

    variant_list << QMetaType::Double;
    d->receiver_value.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_matrix);

    d->emitter_size.setData(&d->size);
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

        dtkMatrixSquareReal *matrix = d->receiver_matrix.data();
        d->size = matrix->size();

        d->emitter_matrix.setData(matrix);

    } else {

        if (!d->matrix)
            d->matrix = new dtkMatrixSquareReal();

        if (!d->receiver_size.isEmpty())
            d->size = *d->receiver_size.data<qlonglong>();
        else
            d->size = 0;

        if (d->size == 0) {

            d->matrix->allocate(0);

            dtkWarn() << "The size of the matrix is zero.";

        } else {

            if (d->size != d->matrix->size())
                d->matrix->allocate(d->size);

            qreal value = 0.;

            if (!d->receiver_value.isEmpty())
                value = *d->receiver_value.data<qreal>();

            d->matrix->fill(value);
        }

        d->emitter_matrix.setData(d->matrix);
    }
}

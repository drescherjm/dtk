/* dtkComposerNodeMatrixSquareRealr.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette Lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 15 15:28:57 2012 (+0200)
 *           By: sblekout
 *     Update #: 40
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
//
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal>  receiver_matrix;
    dtkComposerTransmitterVariant receiver_size;
    dtkComposerTransmitterVariant receiver_value;

public:
    dtkComposerTransmitterEmitter<dtkMatrixSquareReal>   emitter_matrix;
    dtkComposerTransmitterEmitter<qlonglong>             emitter_size;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMatrixSquareReal::dtkComposerNodeMatrixSquareReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealPrivate)
{
    this->appendReceiver(&d->receiver_matrix);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong;
    d->receiver_size.setTypes(variant_list);
    this->appendReceiver(&d->receiver_size);

    variant_list << QVariant::Double;
    d->receiver_value.setTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_matrix);
    this->appendEmitter(&d->emitter_size);
}

dtkComposerNodeMatrixSquareReal::~dtkComposerNodeMatrixSquareReal(void)
{
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

        dtkMatrixSquareReal matrix (d->receiver_matrix.data());

        // this->releaseReceivers();

        d->emitter_matrix.setData(matrix);
        d->emitter_size.setData(matrix.getRows());

    } else {

        qlonglong size = 0;
        qreal value = 0;
        dtkMatrixSquareReal matrix;

        if (!d->receiver_size.isEmpty())
            size = qvariant_cast<qlonglong>(d->receiver_size.data());

        if (size == 0) {
            dtkWarn() << "The size of the matrix is zero." ;
            //this->releaseReceivers();

        } else {

            matrix.allocate(size);

            if (!d->receiver_value.isEmpty())
                value = qvariant_cast<qreal>(d->receiver_value.data());

            //this->releaseReceivers();

            for(int i = 0 ; i < matrix.getRows(); i++) {
                for(int j = 0 ; j < matrix.getCols(); j++)
                    matrix[i][j] = value;
            }
        }

        d->emitter_size.setData(size);
        d->emitter_matrix.setData(matrix);
    }
}

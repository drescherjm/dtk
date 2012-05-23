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

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal>  receiver_matrix;
    dtkComposerTransmitterReceiver<qlonglong>            receiver_size;
    dtkComposerTransmitterReceiver<qreal>                receiver_value;

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
    this->appendReceiver(&d->receiver_size);
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

        d->emitter_matrix.setData(matrix);
        d->emitter_size.setData(matrix.getRows());

    } else {

        unsigned int t =  d->receiver_size.data();
        dtkMatrixSquareReal matrix(t,t);

        for(int i = 0 ; i < matrix.getRows(); i++){
            for(int j = 0 ; j < matrix.getCols(); j++)
                matrix[i][j] = d->receiver_value.data();

        }

        d->emitter_size.setData(matrix.getRows());
        d->emitter_matrix.setData(matrix);
    }
}

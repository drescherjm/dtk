/* dtkComposerNodeMatrixSquareRealOperatorExtractor.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun 15 09:51:39 2012 (+0200)
 *           By: sblekout
 *     Update #: 66
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeMatrixSquareRealOperatorExtractor.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkContainer/dtkContainerVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealOperatorExtractorPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_matrix;
    dtkComposerTransmitterVariant receiver_row;
    dtkComposerTransmitterVariant receiver_col;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_value;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMatrixSquareRealOperatorExtractor::dtkComposerNodeMatrixSquareRealOperatorExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealOperatorExtractorPrivate)
{
    this->appendReceiver(&d->receiver_matrix);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double ;
    d->receiver_row.setTypes(variant_list);
    this->appendReceiver(&d->receiver_row);

    d->receiver_col.setTypes(variant_list);
    this->appendReceiver(&d->receiver_col);

    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeMatrixSquareRealOperatorExtractor::~dtkComposerNodeMatrixSquareRealOperatorExtractor(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeMatrixSquareRealOperatorExtractor::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "matrix";
        break;
    case 1:
        return "row";
        break;
    case 2:
        return "col";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeMatrixSquareRealOperatorExtractor::outputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "value";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeMatrixSquareRealOperatorExtractor::run(void)
{
    if(d->receiver_matrix.isEmpty())
        return;

    if(d->receiver_row.isEmpty())
        return;

    if(d->receiver_col.isEmpty())
        return;

    dtkMatrixSquareReal& matrix(d->receiver_matrix.data());
    qlonglong row = qvariant_cast<qreal>(d->receiver_row.data());
    qlonglong col = qvariant_cast<qreal>(d->receiver_col.data());

    d->emitter_value.setData(matrix[row][col]);
}

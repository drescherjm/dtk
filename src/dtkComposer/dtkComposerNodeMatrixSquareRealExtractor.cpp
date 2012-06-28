/* dtkComposerNodeMatrixSquareRealExtractor.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 26 16:25:45 2012 (+0200)
 *           By: tkloczko
 *     Update #: 76
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeMatrixSquareRealExtractor.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkContainer/dtkContainerVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealExtractorPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMatrixSquareRealExtractorPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal> receiver_matrix;
    dtkComposerTransmitterVariant receiver_row;
    dtkComposerTransmitterVariant receiver_col;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealExtractor implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMatrixSquareRealExtractor::dtkComposerNodeMatrixSquareRealExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealExtractorPrivate)
{
    this->appendReceiver(&d->receiver_matrix);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double;
    d->receiver_row.setTypes(variant_list);
    this->appendReceiver(&d->receiver_row);

    d->receiver_col.setTypes(variant_list);
    this->appendReceiver(&d->receiver_col);

    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeMatrixSquareRealExtractor::~dtkComposerNodeMatrixSquareRealExtractor(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeMatrixSquareRealExtractor::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "matrix";
        break;
    case 1:
        return "row index";
        break;
    case 2:
        return "col index";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeMatrixSquareRealExtractor::outputLabelHint(int port)
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

void dtkComposerNodeMatrixSquareRealExtractor::run(void)
{
    if(d->receiver_matrix.isEmpty())
        return;

    if(d->receiver_row.isEmpty())
        return;

    if(d->receiver_col.isEmpty())
        return;

    dtkMatrixSquareReal& matrix(d->receiver_matrix.data());
    qlonglong row = qvariant_cast<qlonglong>(d->receiver_row.data());
    qlonglong col = qvariant_cast<qlonglong>(d->receiver_col.data());

    if (row < matrix.getRows() && col < matrix.getCols())
        d->emitter_value.setData(matrix[row][col]);
    else
        dtkWarn() << "Row or col index is larger than matrix rank:" << row << "or" << col << ">=" << matrix.size();
}

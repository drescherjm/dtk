/* dtkComposerNodeMatrixSquareRealExtractor.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 20 10:57:21 2012 (+0200)
 *           By: tkloczko
 *     Update #: 86
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

#include <dtkContainerSupport/dtkContainerVector.h>

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

public:
    qreal value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMatrixSquareRealExtractor implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMatrixSquareRealExtractor::dtkComposerNodeMatrixSquareRealExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMatrixSquareRealExtractorPrivate)
{
    this->appendReceiver(&d->receiver_matrix);

    QList<int> variant_list;

    variant_list << QMetaType::LongLong;
    d->receiver_row.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_row);

    d->receiver_col.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_col);

    d->value = 0.;
    d->emitter_value.setData(&d->value);
    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeMatrixSquareRealExtractor::~dtkComposerNodeMatrixSquareRealExtractor(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeMatrixSquareRealExtractor::inputLabelHint(int port)
{
    switch (port) {
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
    switch (port) {
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
    if (!d->receiver_matrix.isEmpty() && !d->receiver_row.isEmpty() && !d->receiver_col.isEmpty()) {

        dtkMatrixSquareReal *matrix = d->receiver_matrix.data();
        qlonglong row = *d->receiver_row.data<qlonglong>();
        qlonglong col = *d->receiver_col.data<qlonglong>();

        if (row < matrix->size() && col < matrix->size())
            d->value = (*matrix)[row][col];

        else
            dtkWarn() << "Row or col index is larger than matrix rank:" << row << "or" << col << ">=" << matrix->size();
    }
}

/* dtkComposerNodeMatrixSquareRealExtractor.cpp ---
 *
 * Author: Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
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
    dtkComposerTransmitterReceiver<dtkMatrixSquareReal*> receiver_matrix;
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

    QVector<const dtkComposerType*> variant_list;

    variant_list << dtkComposerTypeInfo<qlonglong>::type() ;
    d->receiver_row.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver_row);

    d->receiver_col.setDataTypes(variant_list);
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
    if (!d->receiver_matrix.isEmpty() && !d->receiver_row.isEmpty() && !d->receiver_col.isEmpty()) {

        dtkMatrixSquareReal *matrix = d->receiver_matrix.constData();
        qlonglong row = d->receiver_row.data<qlonglong>();
        qlonglong col = d->receiver_col.data<qlonglong>();

        if (!matrix) {
            dtkError() << "dtkComposerNodeMatrixSquareRealExtractor::" << Q_FUNC_INFO << "Input matrix is not defined.";
            d->emitter_value.clearData();
            return;            
        }

        if (row < matrix->size() && col < matrix->size()) {
            d->emitter_value.setData( (*matrix)[row][col] );

        } else {
            dtkWarn() << "dtkComposerNodeMatrixSquareRealExtractor::" << Q_FUNC_INFO << "Row or col index is larger than matrix rank:" << row << "or" << col << ">=" << matrix->size();
            d->emitter_value.setData(0);
        }
    }
}

/* dtkComposerNodeVectorIntegerExtractor.cpp ---
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

#include "dtkComposerNodeVectorIntegerExtractor.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerExtractorPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorInteger*> receiver_vector;
    dtkComposerTransmitterReceiver<qlonglong>         receiver_index;

public:
    dtkComposerTransmitterEmitter<qlonglong> emitter_value;

public:
    qlonglong value;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

dtkComposerNodeVectorIntegerExtractor::dtkComposerNodeVectorIntegerExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerExtractorPrivate)
{
    this->appendReceiver(&d->receiver_vector);
    this->appendReceiver(&d->receiver_index);

    d->value = 0.;
    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeVectorIntegerExtractor::~dtkComposerNodeVectorIntegerExtractor(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeVectorIntegerExtractor::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "vector";
        break;
    case 1:
        return "index";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeVectorIntegerExtractor::outputLabelHint(int port)
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

void dtkComposerNodeVectorIntegerExtractor::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty()) {

        dtkVectorInteger *vector = d->receiver_vector.data();
        qlonglong index = d->receiver_index.data();

        if (!vector) {
            dtkError() << "Input vector is not defined.";
            return;
        }

        if (index >= vector->size()) {
            dtkWarn() << "index > size of the input vector. Zero is returned.";
            d->value = 0;

        } else {
            d->value = (*vector)[index];

        }

    } else {
        dtkWarn() << "Inputs not specified. Zero is returned.";
        d->value = 0;
    }
    
    d->emitter_value.setData(d->value);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerExtractorSubVectorPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerExtractorSubVectorPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector<qlonglong>*> receiver_vector;
    dtkComposerTransmitterReceiver<qlonglong>             receiver_from;
    dtkComposerTransmitterReceiver<qlonglong>             receiver_length;

public:
    dtkComposerTransmitterEmitter<dtkVector<qlonglong>*> emitter_subvector;

public:
    dtkVector<qlonglong> *subvector;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerExtractorSubVector implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeVectorIntegerExtractorSubVector::dtkComposerNodeVectorIntegerExtractorSubVector(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorIntegerExtractorSubVectorPrivate)
{
    this->appendReceiver(&d->receiver_vector);
    this->appendReceiver(&d->receiver_from);
    this->appendReceiver(&d->receiver_length);

    d->subvector = new dtkVectorInteger();
    d->emitter_subvector.setData(d->subvector);
    this->appendEmitter(&d->emitter_subvector);

}

dtkComposerNodeVectorIntegerExtractorSubVector::~dtkComposerNodeVectorIntegerExtractorSubVector(void)
{
    if (d->subvector)
        delete d->subvector;
    d->subvector = NULL;

    delete d;
    
    d = NULL;
}

QString dtkComposerNodeVectorIntegerExtractorSubVector::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "vector";
        break;
    case 1:
        return "from";
        break;
        break;
    case 2:
        return "length";
        break;
    default:
        break;
    }

    return "input";
}

QString dtkComposerNodeVectorIntegerExtractorSubVector::outputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "subvector";
        break;
    default:
        break;
    }

    return "output";
}

void dtkComposerNodeVectorIntegerExtractorSubVector::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_from.isEmpty()) {

        dtkVectorInteger *vector = d->receiver_vector.data();

        if (!vector) {
            dtkError() << "dtkComposerNodeVectorIntegerExtractorSubVector::" << Q_FUNC_INFO << "Input vector is not defined.";
            d->emitter_subvector.clearData();
            return;
        }

        qlonglong from = d->receiver_from.data();
        if (from >= vector->size()) {
            dtkWarn() << "dtkComposerNodeVectorIntegerExtractorSubVector::" << Q_FUNC_INFO << "Starting value from is greater than vector size:" << from << ">=" << vector->size();
            d->emitter_subvector.clearData();
            return;
        }

        qlonglong length = vector->size();
        if (!d->receiver_length.isEmpty())
            length = d->receiver_length.data();

        if (length < 0) {
            dtkWarn() << "dtkComposerNodeVectorIntegerExtractorSubVector::" << Q_FUNC_INFO << "Length value is negative:" << length << "<" << 0;
            d->emitter_subvector.clearData();
            return;
        }

        qlonglong to = qMin((from + length), static_cast<qlonglong>(vector->size()));
        qlonglong size = to - from;
        
        if (d->subvector->size() != size)
            d->subvector->allocate(size);
        
        for(qlonglong i = from, count = 0; i < to; ++i, ++count)
            (*d->subvector)[count] = (*vector)[i];

    } else {
        dtkWarn() << "dtkComposerNodeVectorIntegerExtractorSubVector::" << Q_FUNC_INFO << "Inputs not specified. Nothing is done";
        d->emitter_subvector.clearData();
    }
}


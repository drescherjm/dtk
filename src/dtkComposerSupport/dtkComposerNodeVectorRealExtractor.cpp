/* dtkComposerNodeVectorRealExtractor.cpp ---
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

#include "dtkComposerNodeVectorRealExtractor.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMathSupport/dtkVector>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealExtractorPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector;
    dtkComposerTransmitterReceiver<qlonglong>     receiver_index;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_value;

public:
    qreal value;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

dtkComposerNodeVectorRealExtractor::dtkComposerNodeVectorRealExtractor(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealExtractorPrivate)
{
    this->appendReceiver(&d->receiver_vector);
    this->appendReceiver(&d->receiver_index);

    d->value = 0.;
    d->emitter_value.setData(&d->value);
    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeVectorRealExtractor::~dtkComposerNodeVectorRealExtractor(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeVectorRealExtractor::inputLabelHint(int port)
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

QString dtkComposerNodeVectorRealExtractor::outputLabelHint(int port)
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

void dtkComposerNodeVectorRealExtractor::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_index.isEmpty()) {

        dtkVectorReal *vector = d->receiver_vector.data();
        qlonglong index = *d->receiver_index.data();

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
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealExtractorSubVectorPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealExtractorSubVectorPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector<qreal> > receiver_vector;
    dtkComposerTransmitterReceiver<qlonglong>         receiver_from;
    dtkComposerTransmitterReceiver<qlonglong>         receiver_length;

public:
    dtkComposerTransmitterEmitter<dtkVector<qreal> > emitter_subvector;

public:
    dtkVector<qreal> *subvector;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealExtractorSubVector implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeVectorRealExtractorSubVector::dtkComposerNodeVectorRealExtractorSubVector(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealExtractorSubVectorPrivate)
{
    this->appendReceiver(&d->receiver_vector);
    this->appendReceiver(&d->receiver_from);
    this->appendReceiver(&d->receiver_length);

    d->subvector = new dtkVectorReal();
    d->emitter_subvector.setData(d->subvector);
    this->appendEmitter(&d->emitter_subvector);

}

dtkComposerNodeVectorRealExtractorSubVector::~dtkComposerNodeVectorRealExtractorSubVector(void)
{
    if (d->subvector)
        delete d->subvector;
    d->subvector = NULL;

    delete d;
    
    d = NULL;
}

QString dtkComposerNodeVectorRealExtractorSubVector::inputLabelHint(int port)
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

QString dtkComposerNodeVectorRealExtractorSubVector::outputLabelHint(int port)
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

void dtkComposerNodeVectorRealExtractorSubVector::run(void)
{
    if (!d->receiver_vector.isEmpty() && !d->receiver_from.isEmpty()) {

        dtkVectorReal *vector = d->receiver_vector.data();

        if (!vector) {
            dtkError() << DTK_PRETTY_FUNCTION << "Input vector is not defined.";
            d->emitter_subvector.clearData();
            return;
        }

        qlonglong from = *d->receiver_from.data();
        if (from >= vector->size()) {
            dtkWarn() << DTK_PRETTY_FUNCTION << "Starting value from is greater than vector size:" << from << ">=" << vector->size();
            d->emitter_subvector.clearData();
            return;
        }

        qlonglong length = vector->size();
        if (!d->receiver_length.isEmpty())
            length = *d->receiver_length.data();

        if (length < 0) {
            dtkWarn() << DTK_PRETTY_FUNCTION << "Length value is negative:" << length << "<" << 0;
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
        dtkWarn() << DTK_PRETTY_FUNCTION << "Inputs not specified. Nothing is done";
        d->emitter_subvector.clearData();
    }
}


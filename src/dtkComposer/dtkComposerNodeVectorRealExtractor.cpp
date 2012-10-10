/* dtkComposerNodeVectorRealExtractor.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 20 14:56:11 2012 (+0200)
 *           By: tkloczko
 *     Update #: 83
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

#include <dtkMath>

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

/* dtkComposerNodeVectorRealOperatorModifier.h ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Thu Apr 26 16:14:44 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 17:34:34 2012 (+0200)
 *           By: sblekout
 *     Update #: 38
 */
/* dtkComposerNodeVectorRealOperatorModifier.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 15 13:58:18 2012 (+0200)
 *           By: sblekout
 *     Update #: 33
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerNodeVectorRealOperatorModifier.h"

#include <dtkMath>

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodearrayScalarOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorModifierPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector;
    dtkComposerTransmitterReceiver<qlonglong>     receiver_index;
    dtkComposerTransmitterReceiver<qreal>         receiver_value;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal>  emitter_vector;
};

dtkComposerNodeVectorRealOperatorModifier::dtkComposerNodeVectorRealOperatorModifier(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorModifierPrivate)
{
    this->appendReceiver(&d->receiver_vector);
    this->appendReceiver(&d->receiver_index);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_vector);
}

dtkComposerNodeVectorRealOperatorModifier::~dtkComposerNodeVectorRealOperatorModifier(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier - SET
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierSet::run(void)
{
    dtkVectorReal vec(d->receiver_vector.data());

    if (!d->receiver_vector.isEmpty()) {
        vec[d->receiver_index.data()] = d->receiver_value.data();

    }

    d->emitter_vector.setData(vec);
}


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier - Sum
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierSum::run(void)
{
    dtkVectorReal vec;

    if (!d->receiver_vector.isEmpty()) {
        vec = d->receiver_vector.data();
        vec[d->receiver_index.data()] += d->receiver_value.data();
    }

    d->emitter_vector.setData(vec);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierSubstract::run(void)
{
    dtkVectorReal vec;

    if (!d->receiver_vector.isEmpty()) {
        vec = d->receiver_vector.data();
        vec[d->receiver_index.data()] -= d->receiver_value.data();

    }

    d->emitter_vector.setData(vec);

}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierMult::run(void)
{
    dtkVectorReal vec;

    if (!d->receiver_vector.isEmpty()) {
        vec = d->receiver_vector.data();
        vec[d->receiver_index.data()] *= d->receiver_value.data();

    }

    d->emitter_vector.setData(vec);

}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Divide
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierDivide::run(void)
{
    dtkVectorReal vec;

    if (!d->receiver_vector.isEmpty()) {
        vec = d->receiver_vector.data();
        vec[d->receiver_index.data()] /= d->receiver_value.data();

    }

    d->emitter_vector.setData(vec);

}















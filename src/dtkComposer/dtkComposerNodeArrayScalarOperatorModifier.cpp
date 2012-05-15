/* dtkComposerNodeArrayScalarOperatorModifierOperatorModifier.cpp ---
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

#include "dtkComposerNodeArrayScalarOperatorModifier.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkCore/dtkContainerVector.h>



// /////////////////////////////////////////////////////////////////
//  dtkComposerNodearrayScalarOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarOperatorModifierPrivate
{
public:
    dtkComposerTransmitterReceiver<qreal> receiver_array;
    dtkComposerTransmitterReceiver<qlonglong>              receiver_index;
    dtkComposerTransmitterReceiver<qreal>                  receiver_value;

public:
    dtkComposerTransmitterEmitter<qreal> emitter_array;
};


dtkComposerNodeArrayScalarOperatorModifier::dtkComposerNodeArrayScalarOperatorModifier(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeArrayScalarOperatorModifierPrivate)
{
    this->appendReceiver(&d->receiver_array);
    this->appendReceiver(&d->receiver_index);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_array);
}

dtkComposerNodeArrayScalarOperatorModifier::~dtkComposerNodeArrayScalarOperatorModifier(void)
{
    delete d;

    d = NULL;
}


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Insert
// /////////////////////////////////////////////////////////////////
void dtkComposerNodeArrayScalarOperatorInsert::run(void)
{
    dtkContainerVectorReal array;

    if (!d->receiver_array.isEmpty()) {
        array = d->receiver_array.vector();
        array.vector().insert(d->receiver_index.data(), d->receiver_value.data());

    }
    d->emitter_array.setVector(array);
   // dtkContainerVectorReal temp = d->emitter_array.vector();
    //qDebug() << temp.vector();
}

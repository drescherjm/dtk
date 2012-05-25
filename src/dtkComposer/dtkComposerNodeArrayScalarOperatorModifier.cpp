/* dtkComposerNodeArrayScalarOperatorModifier.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 24 12:02:24 2012 (+0200)
 *           By: tkloczko
 *     Update #: 35
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerNodeArrayScalarOperatorModifier.h"

#include <dtkCore/dtkContainerVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodearrayScalarOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarOperatorModifierPrivate
{
public:
    dtkComposerTransmitterReceiver<qreal>      receiver_array;
    dtkComposerTransmitterReceiver<qlonglong>  receiver_index;
    dtkComposerTransmitterReceiver<qreal>      receiver_value;

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
// dtkComposerNodeArrayScalarOperator - INSERT
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorInsert::run(void)
{
    if (!d->receiver_array.isEmpty()) {

        dtkContainerVectorReal array(d->receiver_array.vector());

        if (d->receiver_index.isEmpty() || d->receiver_value.isEmpty()) {

            dtkWarn() << "Inputs not specified. Nothing is done";

	} else {

	    if (d->receiver_index.data() < array.count())
                array.insert(d->receiver_index.data(), d->receiver_value.data());
	    else
	        dtkWarn() << "index > size of the vector. Nothing is done" ;
	}

        d->emitter_array.setVector(array);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - SUM
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorSum::run(void)
{

    if (!d->receiver_array.isEmpty()) {

        dtkContainerVectorReal array(d->receiver_array.vector());

        if (d->receiver_index.isEmpty() || d->receiver_value.isEmpty()) {

            dtkWarn() << "Inputs not specified. Nothing is done";

	} else {

	    if (d->receiver_index.data() < array.count())
                array[d->receiver_index.data()] += d->receiver_value.data();
	    else
                dtkWarn() << "index > size of the vector. Nothing is done" ;

	}

        d->emitter_array.setVector(array);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorSubstract::run(void)
{
    if (!d->receiver_array.isEmpty()) {

        dtkContainerVectorReal array(d->receiver_array.vector());

        if (!d->receiver_index.isEmpty() &&  d->receiver_index.data() < array.count())
            array[d->receiver_index.data()] -= d->receiver_value.data();

        else
            dtkWarn() << "index > size of the vector" ;

        d->emitter_array.setVector(array);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorMult::run(void)
{
    if (!d->receiver_array.isEmpty()) {

        dtkContainerVectorReal array(d->receiver_array.vector());

        if (d->receiver_index.isEmpty() || d->receiver_value.isEmpty()) {

            dtkWarn() << "Inputs not specified. Nothing is done";

	} else {

	    if (d->receiver_index.data() < array.count())
                array[d->receiver_index.data()] *= d->receiver_value.data();
	    else
                dtkWarn() << "index > size of the vector. Nothing is done" ;

	}

        d->emitter_array.setVector(array);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Divide
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeArrayScalarOperatorDivide::run(void)
{
    if (!d->receiver_array.isEmpty()) {

        dtkContainerVectorReal array(d->receiver_array.vector());

        if (d->receiver_index.isEmpty() || d->receiver_value.isEmpty()) {

            dtkWarn() << "Inputs not specified. Nothing is done";

	} else {

	    if (d->receiver_value.data() == 0)
	        dtkWarn() << "Value is zero. Nothing is done" ;
	    else if (d->receiver_index.data() < array.count())
                array[d->receiver_index.data()] /= d->receiver_value.data();
	    else
                dtkWarn() << "index > size of the vector. Nothing is done" ;

	}

        d->emitter_array.setVector(array);
    }
}

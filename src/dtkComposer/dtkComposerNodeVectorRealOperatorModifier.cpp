/* dtkComposerNodeVectorRealOperatorModifier.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 24 22:33:00 2012 (+0200)
 *           By: tkloczko
 *     Update #: 34
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

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//  dtkComposerNodearrayScalarOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealOperatorModifierPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector;
    dtkComposerTransmitterVariant receiver_value;
    dtkComposerTransmitterVariant receiver_index;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal>  emitter_vector;
};

dtkComposerNodeVectorRealOperatorModifier::dtkComposerNodeVectorRealOperatorModifier(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealOperatorModifierPrivate)
{
    this->appendReceiver(&d->receiver_vector);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong;
    d->receiver_index.setTypes(variant_list);
    this->appendReceiver(&d->receiver_index);

    variant_list << QVariant::Double;
    d->receiver_value.setTypes(variant_list);
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
    if (!d->receiver_vector.isEmpty()) {

        dtkVectorReal vec(d->receiver_vector.data());

        if (d->receiver_index.isEmpty() || d->receiver_value.isEmpty()) {

            dtkWarn() << "Inputs not specified. Nothing is done";

        } else {

            if (qvariant_cast<qlonglong>(d->receiver_index.data()) < vec.getRows())
                vec[qvariant_cast<qlonglong>(d->receiver_index.data())] = qvariant_cast<qreal>(d->receiver_value.data());

            else
                dtkWarn() << "index > size of the vector. Nothing is done" ;
        }

        d->emitter_vector.setData(vec);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorRealOperatorModifier - Sum
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierSum::run(void)
{
    if (!d->receiver_vector.isEmpty()) {

        dtkVectorReal vec(d->receiver_vector.data());

        if (d->receiver_index.isEmpty() || d->receiver_value.isEmpty()) {

            dtkWarn() << "Inputs not specified. Nothing is done";

        } else {

            if (qvariant_cast<qlonglong>(d->receiver_index.data()) < vec.getRows())
                vec[qvariant_cast<qlonglong>(d->receiver_index.data())] += qvariant_cast<qreal>(d->receiver_value.data());

            else
                dtkWarn() << "index > size of the vector. Nothing is done" ;
        }

        d->emitter_vector.setData(vec);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Substract
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierSubstract::run(void)
{
    if (!d->receiver_vector.isEmpty()) {

        dtkVectorReal vec(d->receiver_vector.data());

        if (d->receiver_index.isEmpty() || d->receiver_value.isEmpty()) {

            dtkWarn() << "Inputs not specified. Nothing is done";

        } else {

            if (qvariant_cast<qlonglong>(d->receiver_index.data()) < vec.getRows())
                vec[qvariant_cast<qlonglong>(d->receiver_index.data())] -= qvariant_cast<qreal>(d->receiver_value.data());

            else
                dtkWarn() << "index > size of the vector. Nothing is done" ;
        }

        d->emitter_vector.setData(vec);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Mult
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierMult::run(void)
{
    if (!d->receiver_vector.isEmpty()) {

        dtkVectorReal vec(d->receiver_vector.data());

        if (d->receiver_index.isEmpty() || d->receiver_value.isEmpty()) {

            dtkWarn() << "Inputs not specified. Nothing is done";

        } else {

            if (qvariant_cast<qlonglong>(d->receiver_index.data()) < vec.getRows())
                vec[qvariant_cast<qlonglong>(d->receiver_index.data())] *= qvariant_cast<qreal>(d->receiver_value.data());

            else
                dtkWarn() << "index > size of the vector. Nothing is done" ;
        }

        d->emitter_vector.setData(vec);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarOperator - Divide
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeVectorRealOperatorModifierDivide::run(void)
{
    if (!d->receiver_vector.isEmpty()) {

        dtkVectorReal vec(d->receiver_vector.data());

        if (d->receiver_index.isEmpty() || d->receiver_value.isEmpty()) {

            dtkWarn() << "Inputs not specified. Nothing is done";

        } else {

            if (qvariant_cast<qreal>(d->receiver_value.data()) == 0)
                dtkWarn() << "Value is zero. Nothing is done" ;

            if (qvariant_cast<qlonglong>(d->receiver_index.data()) < vec.getRows())
                vec[qvariant_cast<qlonglong>(d->receiver_index.data())] /= qvariant_cast<qreal>(d->receiver_value.data());

            else
                dtkWarn() << "index > size of the vector. Nothing is done" ;
        }

        d->emitter_vector.setData(vec);

    }
}

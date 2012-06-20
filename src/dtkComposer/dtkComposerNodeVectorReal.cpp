/* dtkComposerNodeVectorReal.cpp ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette Lekouta, Inria.
 * Created: Tue May 15 11:35:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 24 18:32:17 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 58
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeVectorReal.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorRealPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVectorReal>  receiver_vector;
    dtkComposerTransmitterVariant receiver_size;
    dtkComposerTransmitterVariant receiver_value;

public:
    dtkComposerTransmitterEmitter<dtkVectorReal>   emitter_vector;
    dtkComposerTransmitterEmitter<qlonglong>       emitter_size;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

dtkComposerNodeVectorReal::dtkComposerNodeVectorReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorRealPrivate)
{
    this->appendReceiver(&d->receiver_vector);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong;
    d->receiver_size.setTypes(variant_list);
    this->appendReceiver(&d->receiver_size);

    variant_list << QVariant::Double;
    d->receiver_value.setTypes(variant_list);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_vector);
    this->appendEmitter(&d->emitter_size);
}

dtkComposerNodeVectorReal::~dtkComposerNodeVectorReal(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeVectorReal::inputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "vector";
        break;
    case 1:
        return "size";
        break;
    case 2:
        return "value";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeVectorReal::outputLabelHint(int port)
{
    switch(port) {
    case 0:
        return "vector";
        break;
    case 1:
        return "size";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeVectorReal::run(void)
{
    if (!d->receiver_vector.isEmpty()) {

        dtkVectorReal& vec(d->receiver_vector.data());

        d->emitter_vector.setData(vec);
        d->emitter_size.setData(vec.getRows());

    } else {

        qlonglong size = 0;
        qreal value = 0;
        dtkVectorReal vec;

        if (!d->receiver_size.isEmpty())
            size = qvariant_cast<qlonglong>(d->receiver_size.data());

        if (size == 0) {
            dtkWarn() << "The size of the vector is zero." ;

        } else {

            vec.allocate(size);

            if (!d->receiver_value.isEmpty())
                value = qvariant_cast<qreal>(d->receiver_value.data());

            for(int i = 0 ; i < vec.getRows(); i++)
                vec[i] = value;

        }

        d->emitter_size.setData(size);
        d->emitter_vector.setData(vec);
    }
}

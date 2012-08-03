/* dtkComposerNodeReal.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Aug  4 01:05:15 2012 (+0200)
 *           By: tkloczko
 *     Update #: 80
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerMetatype.h"

#include "dtkComposerNodeReal.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterUtils.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRealPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRealPrivate
{
public:
    dtkComposerTransmitterVariant receiver;

public:
    dtkComposerTransmitterEmitter<qreal> emitter;

public:
    qreal value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeReal implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeReal::dtkComposerNodeReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeRealPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double ;

    d->receiver.setTypes(variant_list);
    this->appendReceiver(&(d->receiver));

    d->value = 0.0;
    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeReal::~dtkComposerNodeReal(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeReal::run(void)
{
    if (!d->receiver.isEmpty()) {
        if (d->receiver.type() == QVariant::Double) {
            d->value = *dtkComposerTransmitterData<qreal>(d->receiver);
        } else {
            d->value = static_cast<qreal>(*dtkComposerTransmitterData<qlonglong>(d->receiver));
        }
    }
}

qreal dtkComposerNodeReal::value(void)
{
    return d->value;
}

void dtkComposerNodeReal::setValue(qreal value)
{
    d->value = value;
}

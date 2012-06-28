/* dtkComposerNodeReal.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jun 26 16:16:31 2012 (+0200)
 *           By: tkloczko
 *     Update #: 52
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeReal.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

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

    d->emitter.setData(0);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeReal::~dtkComposerNodeReal(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeReal::run(void)
{
    if (!d->receiver.isEmpty())
        d->emitter.setData(qvariant_cast<qreal>(d->receiver.data()));
}

qreal dtkComposerNodeReal::value(void)
{
    return d->emitter.data();
}

void dtkComposerNodeReal::setValue(qreal value)
{
    d->emitter.setData(value);
}

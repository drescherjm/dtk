/* dtkComposerNodeInteger.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jun 26 16:18:04 2012 (+0200)
 *           By: tkloczko
 *     Update #: 40
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeInteger.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeIntegerPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeIntegerPrivate
{
public:
    dtkComposerTransmitterVariant receiver;

public:
    dtkComposerTransmitterEmitter<dtkxarch_int> emitter;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeInteger implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeInteger::dtkComposerNodeInteger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeIntegerPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong;

    d->receiver.setTypes(variant_list);
    this->appendReceiver(&(d->receiver));

    d->emitter.setData(0);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeInteger::~dtkComposerNodeInteger(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeInteger::run(void)
{
    if (!d->receiver.isEmpty())
        d->emitter.setData(qvariant_cast<dtkxarch_int>(d->receiver.data()));
}

dtkxarch_int dtkComposerNodeInteger::value(void)
{
    return d->emitter.data();
}

void dtkComposerNodeInteger::setValue(dtkxarch_int value)
{
    d->emitter.setData(value);
}

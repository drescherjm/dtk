/* dtkComposerNodeReal.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Sep 18 13:17:59 2012 (+0200)
 *           By: tkloczko
 *     Update #: 87
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

#include <dtkCoreSupport/dtkGlobal.h>

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
    QList<int> variant_list;
    variant_list << QMetaType::Int << QMetaType::UInt << QMetaType::LongLong << QMetaType::ULongLong << QMetaType::Double << QMetaType::QString << QMetaType::Bool;

    d->receiver.setDataTypes(variant_list);
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
    if (!d->receiver.isEmpty())
        d->value = *(d->receiver.data<qreal>());
}

qreal dtkComposerNodeReal::value(void)
{
    return d->value;
}

void dtkComposerNodeReal::setValue(qreal value)
{
    d->value = value;
}

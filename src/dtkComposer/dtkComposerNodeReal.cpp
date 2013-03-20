/* dtkComposerNodeReal.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: 2013 Mon Jan 14 12:32:48 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 98
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

public:
    qreal value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeReal implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeReal::dtkComposerNodeReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeRealPrivate)
{
    QVector<const dtkComposerType*> variant_list;

    variant_list << dtkComposerTypeInfo<int>::type() << dtkComposerTypeInfo<uint>::type() << dtkComposerTypeInfo<qlonglong>::type() << dtkComposerTypeInfo<qulonglong>::type() 
                 << dtkComposerTypeInfo<bool>::type() << dtkComposerTypeInfo<QString>::type() << dtkComposerTypeInfo<double>::type();
    d->receiver.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver));

    d->value = 0.0;
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
        d->value = d->receiver.data<qreal>();

    d->emitter.setData(d->value);
}

qreal dtkComposerNodeReal::value(void)
{
    return d->value;
}

void dtkComposerNodeReal::setValue(qreal value)
{
    d->value = value;
}

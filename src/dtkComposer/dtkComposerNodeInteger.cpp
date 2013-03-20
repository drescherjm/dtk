/* dtkComposerNodeInteger.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: 2013 Mon Jan 14 12:32:24 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 81
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
    dtkComposerTransmitterEmitter<qlonglong> emitter;

public:
    qlonglong value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeInteger implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeInteger::dtkComposerNodeInteger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeIntegerPrivate)
{
    QVector<const dtkComposerType*> variant_list;

    variant_list << dtkComposerTypeInfo<int*>::type() << dtkComposerTypeInfo<uint*>::type() << dtkComposerTypeInfo<qlonglong>::type() << dtkComposerTypeInfo<qulonglong*>::type() 
                 << dtkComposerTypeInfo<bool*>::type() << dtkComposerTypeInfo<QString*>::type() << dtkComposerTypeInfo<double*>::type();
    d->receiver.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver));

    d->value = 0;
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
        d->value = d->receiver.data<qlonglong>();

    d->emitter.setData(d->value);
}

qlonglong dtkComposerNodeInteger::value(void)
{
    return d->value;
}

void dtkComposerNodeInteger::setValue(qlonglong value)
{
    d->value = value;
}

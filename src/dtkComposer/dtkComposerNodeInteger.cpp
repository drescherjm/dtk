/* dtkComposerNodeInteger.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr  2 12:58:08 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 86
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
    dtkComposerTransmitterReceiver<qlonglong> receiver;

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
    this->appendReceiver(&(d->receiver));
    this->appendEmitter(&(d->emitter));

    d->value = 0;
}

dtkComposerNodeInteger::~dtkComposerNodeInteger(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeInteger::run(void)
{
    if (!d->receiver.isEmpty())
        d->value = d->receiver.data();

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

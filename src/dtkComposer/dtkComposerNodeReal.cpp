/* dtkComposerNodeReal.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr  2 13:00:16 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 108
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

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRealPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRealPrivate
{
public:
    dtkComposerTransmitterReceiver<double> receiver;

public:
    dtkComposerTransmitterEmitter<double> emitter;

public:
    double value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeReal implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeReal::dtkComposerNodeReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeRealPrivate)
{
    this->appendReceiver(&(d->receiver));
    this->appendEmitter(&(d->emitter));

    d->value = 0;
}

dtkComposerNodeReal::~dtkComposerNodeReal(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeReal::run(void)
{
    if (!d->receiver.isEmpty())
        d->value = d->receiver.data();

    d->emitter.setData(d->value);
}

qreal dtkComposerNodeReal::value(void)
{
    return d->value;
}

void dtkComposerNodeReal::setValue(double value)
{
    d->value = value;
}

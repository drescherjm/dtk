/* dtkComposerNodeBoolean.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 16:49:25 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr  2 12:58:25 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 61
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeBoolean.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanPrivate
{
public:
    dtkComposerTransmitterReceiver<bool> receiver;

public:    
    dtkComposerTransmitterEmitter<bool> emitter;

public:
    bool value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBoolean implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeBoolean::dtkComposerNodeBoolean(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanPrivate)
{
    this->appendReceiver(&d->receiver);
    this->appendEmitter(&d->emitter);

    d->value = false;
}

dtkComposerNodeBoolean::~dtkComposerNodeBoolean(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeBoolean::run(void)
{
    if (!d->receiver.isEmpty())
        d->value = (d->receiver.data());

    d->emitter.setData(d->value);
}

bool dtkComposerNodeBoolean::value(void)
{
    return d->value;
}

void dtkComposerNodeBoolean::setValue(bool value)
{
    d->value = value;
}

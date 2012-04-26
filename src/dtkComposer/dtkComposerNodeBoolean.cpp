/* dtkComposerNodeBoolean.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 16:49:25 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 11:14:51 2012 (+0200)
 *           By: tkloczko
 *     Update #: 18
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
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBoolean implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeBoolean::dtkComposerNodeBoolean(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanPrivate)
{
    this->appendReceiver(&d->receiver);
    this->appendEmitter(&d->emitter);
}

dtkComposerNodeBoolean::~dtkComposerNodeBoolean(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeBoolean::run(void)
{
    if (!d->receiver.isEmpty())
        d->emitter.setData(d->receiver.data());
}

bool dtkComposerNodeBoolean::value(void)
{
    return d->emitter.data();
}

void dtkComposerNodeBoolean::setValue(bool value)
{
    d->emitter.setData(value);
}




/* dtkComposerNodeString.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jun 26 17:28:26 2012 (+0200)
 *           By: tkloczko
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeString.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> receiver;

public:
    dtkComposerTransmitterEmitter<QString> emitter;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeString implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeString::dtkComposerNodeString(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringPrivate)
{
    this->appendReceiver(&(d->receiver));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeString::~dtkComposerNodeString(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeString::run(void)
{
    if (!d->receiver.isEmpty())
        d->emitter.setData(d->receiver.data());
}

QString dtkComposerNodeString::value(void)
{
    return d->emitter.data();
}
   
void dtkComposerNodeString::setValue(QString value)
{
    d->emitter.setData(value);
}

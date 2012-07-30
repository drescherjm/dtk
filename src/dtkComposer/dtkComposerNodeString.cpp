/* dtkComposerNodeString.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jul 25 16:37:22 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 30
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
    dtkComposerTransmitterReceiver<qreal>   receiver_real;

public:
    dtkComposerTransmitterEmitter<QString> emitter;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeString implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeString::dtkComposerNodeString(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringPrivate)
{
    this->appendReceiver(&(d->receiver));
    this->appendReceiver(&(d->receiver_real));

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

    else if (!d->receiver_real.isEmpty())
        d->emitter.setData(QString::number(d->receiver_real.data()));
}

QString dtkComposerNodeString::value(void)
{
    return d->emitter.data();
}
   
void dtkComposerNodeString::setValue(QString value)
{
    d->emitter.setData(value);
}

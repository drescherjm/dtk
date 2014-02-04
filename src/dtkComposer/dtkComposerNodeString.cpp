/* dtkComposerNodeString.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr  3 10:48:15 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 71
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

public:
    QString value;
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
        d->value = d->receiver.data();

    d->emitter.setData(d->value);
}

QString dtkComposerNodeString::value(void)
{
    return d->value;
}
   
void dtkComposerNodeString::setValue(QString value)
{
    d->value = value;
}

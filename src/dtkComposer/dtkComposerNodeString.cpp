/* dtkComposerNodeString.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. mars 26 15:43:06 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 17
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

class dtkComposerNodeStringPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> *receiver;

public:
    dtkComposerTransmitterEmitter<QString> *emitter;
};

dtkComposerNodeString::dtkComposerNodeString(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringPrivate)
{
    d->receiver = new dtkComposerTransmitterReceiver<QString>;
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerTransmitterEmitter<QString>;
    this->appendEmitter(d->emitter);
}

dtkComposerNodeString::~dtkComposerNodeString(void)
{
    delete d->receiver;
    delete d->emitter;
    delete d;

    d = NULL;
}

void dtkComposerNodeString::run(void)
{
    if (!d->receiver->isEmpty())
        d->emitter->setData(d->receiver->data());
}

QString dtkComposerNodeString::value(void)
{
    return d->emitter->data();
}

void dtkComposerNodeString::setValue(QString value)
{
    d->emitter->setData(value);
}

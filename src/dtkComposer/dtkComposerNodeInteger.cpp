/* dtkComposerNodeInteger.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 15 18:11:39 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 22
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

class dtkComposerNodeIntegerPrivate
{
public:
    dtkComposerTransmitterReceiver<qlonglong> *receiver;

public:    
    dtkComposerTransmitterEmitter<qlonglong> *emitter;
};

dtkComposerNodeInteger::dtkComposerNodeInteger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeIntegerPrivate)
{
    d->receiver = new dtkComposerTransmitterReceiver<qlonglong>;
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerTransmitterEmitter<qlonglong>;
    d->emitter->setData(0);
    this->appendEmitter(d->emitter);
}

dtkComposerNodeInteger::~dtkComposerNodeInteger(void)
{
    delete d->receiver;
    delete d->emitter;
    delete d;
    
    d = NULL;
}

void dtkComposerNodeInteger::run(void)
{
    d->emitter->setData(d->receiver->data());
}

qlonglong dtkComposerNodeInteger::value(void)
{
    return d->emitter->data();
}

void dtkComposerNodeInteger::setValue(qlonglong value)
{
    d->emitter->setData(value);
}

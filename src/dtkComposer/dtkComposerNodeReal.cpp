/* dtkComposerNodeReal.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 15 18:11:28 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 25
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

class dtkComposerNodeRealPrivate
{
public:
    dtkComposerTransmitterReceiver<qreal> *receiver;

public:    
    dtkComposerTransmitterEmitter<qreal> *emitter;
};

dtkComposerNodeReal::dtkComposerNodeReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeRealPrivate)
{
    d->receiver = new dtkComposerTransmitterReceiver<qreal>;
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerTransmitterEmitter<qreal>;
    d->emitter->setData(0);
    this->appendEmitter(d->emitter);
}

dtkComposerNodeReal::~dtkComposerNodeReal(void)
{
    delete d->receiver;
    delete d->emitter;
    delete d;
    
    d = NULL;
}

void dtkComposerNodeReal::run(void)
{
    d->emitter->setData(d->receiver->data());
}

double dtkComposerNodeReal::value(void)
{
    return d->emitter->data();
}

void dtkComposerNodeReal::setValue(double value)
{
    d->emitter->setData(value);
}

/* dtkComposerNodeReal.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 12:41:42 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeReal.h"
#include "dtkComposerEmitter.h"
#include "dtkComposerReceiver.h"

class dtkComposerNodeRealPrivate
{
public:
    dtkComposerReceiver<qreal> *receiver;

public:    
    dtkComposerEmitter<qreal> *emitter;
};

dtkComposerNodeReal::dtkComposerNodeReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeRealPrivate)
{
    d->receiver = new dtkComposerReceiver<qreal>;
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerEmitter<qreal>;
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
    d->emitter->setData(0);
}

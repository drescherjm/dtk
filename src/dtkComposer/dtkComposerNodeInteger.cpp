/* dtkComposerNodeInteger.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 12:39:47 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeInteger.h"
#include "dtkComposerEmitter.h"
#include "dtkComposerReceiver.h"

class dtkComposerNodeIntegerPrivate
{
public:
    dtkComposerReceiver<qlonglong> *receiver;

public:    
    dtkComposerEmitter<qlonglong> *emitter;
};

dtkComposerNodeInteger::dtkComposerNodeInteger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeIntegerPrivate)
{
    d->receiver = new dtkComposerReceiver<qlonglong>;
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerEmitter<qlonglong>;
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
    d->emitter->setData(0);
}

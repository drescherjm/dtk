/* dtkComposerNodeString.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 12:51:24 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeString.h"
#include "dtkComposerEmitter.h"
#include "dtkComposerReceiver.h"

class dtkComposerNodeStringPrivate
{
public:
    dtkComposerReceiver<QString> *receiver;

public:    
    dtkComposerEmitter<QString> *emitter;
};

dtkComposerNodeString::dtkComposerNodeString(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringPrivate)
{
    d->receiver = new dtkComposerReceiver<QString>;
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerEmitter<QString>;
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
    d->emitter->setData(0);
}

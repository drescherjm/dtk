/* dtkComposerNodeBoolean.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 16:49:25 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 09:09:48 2012 (+0100)
 *           By: tkloczko
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeBoolean.h"
#include "dtkComposerEmitter.h"
#include "dtkComposerReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanPrivate
{
public:
    dtkComposerReceiver<bool> *receiver;

public:    
    dtkComposerEmitter<bool> *emitter;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBoolean implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeBoolean::dtkComposerNodeBoolean(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanPrivate)
{
    d->receiver = new dtkComposerReceiver<bool>;
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerEmitter<bool>;
    this->appendEmitter(d->emitter);
}

dtkComposerNodeBoolean::~dtkComposerNodeBoolean(void)
{
    delete d->receiver;
    delete d->emitter;
    delete d;
    
    d = NULL;
}

void dtkComposerNodeBoolean::run(void)
{
    d->emitter->setData(true);
}




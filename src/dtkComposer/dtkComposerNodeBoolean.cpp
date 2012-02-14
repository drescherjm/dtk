/* dtkComposerNodeBoolean.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 16:49:25 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 14 16:58:37 2012 (+0100)
 *           By: tkloczko
 *     Update #: 7
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

dtkComposerNodeBoolean::dtkComposerNodeBoolean(void) : dtkComposerNode(), d(new dtkComposerNodeBooleanPrivate)
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




/* dtkComposerNodeList.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 16:57:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 17:01:15 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeList.h"

class dtkComposerNodeListPrivate
{
// public:
//     dtkComposerEmitter<??> *emitter;

// public:
//     dtkComposerReceiver<??> *receiver;
};

dtkComposerNodeList::dtkComposerNodeList(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeListPrivate)
{
    // d->emitter = new dtkComposerEmitter<??>;
    // this->appendEmitter(d->emitter);

    // d->emitter = new dtkComposerEmitter<??>;
    // this->appendEmitter(d->emitter);
}

dtkComposerNodeList::~dtkComposerNodeList(void)
{
    // delete d->emitter;
    // delete d->receiver;
    delete d;
    
    d = NULL;
}

void dtkComposerNodeList::run(void)
{
    // d->emitter->setData(d->receiver->data());
}

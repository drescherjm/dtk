/* dtkComposerNodeVector.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 16:57:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 17:04:53 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeVector.h"

class dtkComposerNodeVectorPrivate
{
// public:
//     dtkComposerEmitter<??> *emitter;

// public:
//     dtkComposerReceiver<??> *receiver;
};

dtkComposerNodeVector::dtkComposerNodeVector(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVectorPrivate)
{
    // d->emitter = new dtkComposerEmitter<??>;
    // this->appendEmitter(d->emitter);

    // d->emitter = new dtkComposerEmitter<??>;
    // this->appendEmitter(d->emitter);
}

dtkComposerNodeVector::~dtkComposerNodeVector(void)
{
    // delete d->emitter;
    // delete d->receiver;
    delete d;
    
    d = NULL;
}

void dtkComposerNodeVector::run(void)
{
    // d->emitter->setData(d->receiver->data());
}

/* dtkComposerNodePi.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:58:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 12:59:37 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodePi.h"
#include "dtkComposerEmitter.h"
#include "dtkComposerReceiver.h"

class dtkComposerNodePiPrivate
{
public:    
    dtkComposerEmitter<qreal> *emitter;
};

dtkComposerNodePi::dtkComposerNodePi(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodePiPrivate)
{
    d->emitter = new dtkComposerEmitter<qreal>;
    this->appendEmitter(d->emitter);
}

dtkComposerNodePi::~dtkComposerNodePi(void)
{
    delete d->emitter;
    delete d;
    
    d = NULL;
}

void dtkComposerNodePi::run(void)
{
    d->emitter->setData(3.1415);
}

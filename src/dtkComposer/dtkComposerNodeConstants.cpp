/* dtkComposerNodePi.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:58:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 16:34:37 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeConstants.h"

#include "dtkComposerEmitter.h"
#include "dtkComposerReceiver.h"

#include <math.h>

// /////////////////////////////////////////////////////////////////
// PI
// /////////////////////////////////////////////////////////////////

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
    d->emitter->setData(M_PI);
}

// /////////////////////////////////////////////////////////////////
// E
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeEPrivate
{
public:    
    dtkComposerEmitter<qreal> *emitter;
};

dtkComposerNodeE::dtkComposerNodeE(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeEPrivate)
{
    d->emitter = new dtkComposerEmitter<qreal>;
    this->appendEmitter(d->emitter);
}

dtkComposerNodeE::~dtkComposerNodeE(void)
{
    delete d->emitter;
    delete d;
    
    d = NULL;
}

void dtkComposerNodeE::run(void)
{
    d->emitter->setData(M_E);
}

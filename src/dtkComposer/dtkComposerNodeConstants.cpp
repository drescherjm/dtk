/* dtkComposerNodePi.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:58:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 29 10:14:06 2012 (+0100)
 *           By: tkloczko
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeConstants.h"

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <math.h>

// /////////////////////////////////////////////////////////////////
// PI
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePiPrivate
{
public:    
    dtkComposerTransmitterEmitter<qreal> *emitter;
};

dtkComposerNodePi::dtkComposerNodePi(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodePiPrivate)
{
    d->emitter = new dtkComposerTransmitterEmitter<qreal>;
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
    dtkComposerTransmitterEmitter<qreal> *emitter;
};

dtkComposerNodeE::dtkComposerNodeE(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeEPrivate)
{
    d->emitter = new dtkComposerTransmitterEmitter<qreal>;
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

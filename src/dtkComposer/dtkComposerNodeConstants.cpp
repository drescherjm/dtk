/* dtkComposerNodePi.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:58:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed May  9 09:44:30 2012 (+0200)
 *           By: tkloczko
 *     Update #: 22
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

#if defined(Q_OS_WIN)
#define M_E 2.718281
#endif

// /////////////////////////////////////////////////////////////////
// PI
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePiPrivate
{
public:    
    dtkComposerTransmitterEmitter<qreal> emitter;
};

dtkComposerNodePi::dtkComposerNodePi(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodePiPrivate)
{
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodePi::~dtkComposerNodePi(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodePi::run(void)
{
    d->emitter.setData(M_PI);
}

// /////////////////////////////////////////////////////////////////
// E
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeEPrivate
{
public:    
    dtkComposerTransmitterEmitter<qreal> emitter;
};

dtkComposerNodeE::dtkComposerNodeE(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeEPrivate)
{
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeE::~dtkComposerNodeE(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeE::run(void)
{
    d->emitter.setData(M_E);
}

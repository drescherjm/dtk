/* dtkComposerNodePi.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:58:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Sep 19 14:50:29 2012 (+0200)
 *           By: tkloczko
 *     Update #: 32
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

#if defined(Q_OS_WIN) && defined(Q_CC_MSVC)
#define M_E 2.718281
#endif

// /////////////////////////////////////////////////////////////////
// PI
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePiPrivate
{
public:    
    dtkComposerTransmitterEmitter<qreal> emitter;

public:
    qreal value;
};

dtkComposerNodePi::dtkComposerNodePi(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodePiPrivate)
{
    d->value = M_PI;
    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodePi::~dtkComposerNodePi(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodePi::run(void)
{

}

// /////////////////////////////////////////////////////////////////
// E
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeEPrivate
{
public:    
    dtkComposerTransmitterEmitter<qreal> emitter;

public:
    qreal value;
};

dtkComposerNodeE::dtkComposerNodeE(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeEPrivate)
{
    d->value = M_E;
    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeE::~dtkComposerNodeE(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeE::run(void)
{

}

/* dtkComposerNodePi.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:58:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  5 09:21:28 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 73
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

#if defined(Q_OS_WIN) && (defined(Q_CC_MSVC) || defined(__MINGW32__))
#define M_E 2.718281828
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
    d->emitter.setData(M_PI);
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
};

dtkComposerNodeE::dtkComposerNodeE(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeEPrivate)
{
    d->emitter.setData(M_E);
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

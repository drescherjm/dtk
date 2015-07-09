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

#include <dtkConfig.h>

#include "dtkComposerNodeConstants.h"

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <math.h>

#if defined(Q_OS_WIN) && (defined(Q_CC_MSVC) || defined(__MINGW32__))
#define M_E 2.718281828
#endif

#if defined(DTK_BUILD_DISTRIBUTED)
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedMessage.h>
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


#if defined(DTK_BUILD_DISTRIBUTED)

// /////////////////////////////////////////////////////////////////
// CONTROLLER_RANK
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControllerRankPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;

public:
    qlonglong value;
};

dtkComposerNodeControllerRank::dtkComposerNodeControllerRank(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeControllerRankPrivate)
{
    d->value = dtkDistributedMessage::CONTROLLER_RUN_RANK;
    d->emitter.setData(d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeControllerRank::~dtkComposerNodeControllerRank(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeControllerRank::run(void)
{

}

// /////////////////////////////////////////////////////////////////
// MPI_ANY_TAG
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeAnyTagPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;

public:
    qlonglong value;
};

dtkComposerNodeAnyTag::dtkComposerNodeAnyTag(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeAnyTagPrivate)
{
    d->value = dtkDistributedCommunicator::ANY_TAG;
    d->emitter.setData(d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeAnyTag::~dtkComposerNodeAnyTag(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeAnyTag::run(void)
{

}

// /////////////////////////////////////////////////////////////////
// MPI_ANY_SOURCE
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeAnySourcePrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;

public:
    qlonglong value;
};

dtkComposerNodeAnySource::dtkComposerNodeAnySource(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeAnySourcePrivate)
{
    d->value = dtkDistributedCommunicator::ANY_SOURCE;
    d->emitter.setData(d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeAnySource::~dtkComposerNodeAnySource(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeAnySource::run(void)
{

}

#endif

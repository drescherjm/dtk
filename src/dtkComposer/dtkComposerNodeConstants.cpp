/* dtkComposerNodePi.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:58:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: 2012 Wed Dec 12 15:33:58 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 67
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
#define M_E 2.718281
#endif

#if defined(DTK_BUILD_DISTRIBUTED)
#include <dtkDistributed/dtkDistributedCommunicator>
#include <dtkDistributed/dtkDistributedMessage>
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
// MPI_ANY_TAG
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControllerRunRankPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;
};

dtkComposerNodeControllerRunRank::dtkComposerNodeControllerRunRank(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeControllerRunRankPrivate)
{
    d->emitter.setData(dtkDistributedMessage::CONTROLLER_RUN_RANK);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeControllerRunRank::~dtkComposerNodeControllerRunRank(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeControllerRunRank::run(void)
{

}
#endif

#if defined(DTK_BUILD_DISTRIBUTED)

// /////////////////////////////////////////////////////////////////
// MPI_ANY_TAG
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeAnyTagPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;
};

dtkComposerNodeAnyTag::dtkComposerNodeAnyTag(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeAnyTagPrivate)
{
    d->emitter.setData(dtkDistributedCommunicator::ANY_TAG);
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
    d->emitter.setData(dtkDistributedCommunicator::ANY_SOURCE);
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

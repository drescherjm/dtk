/* dtkComposerNodePi.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:58:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mer. févr.  5 10:17:04 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 63
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

#if defined(DTK_BUILD_DISTRIBUTED_SUPPORT)
#include <dtkDistributedSupport/dtkDistributedCommunicator>
#include <dtkDistributedSupport/dtkDistributedMessage>
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

#if defined(DTK_BUILD_DISTRIBUTED_SUPPORT)

// /////////////////////////////////////////////////////////////////
// MPI_ANY_TAG
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControllerRunRankPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;

public:
    qlonglong value;
};

dtkComposerNodeControllerRunRank::dtkComposerNodeControllerRunRank(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeControllerRunRankPrivate)
{
    d->value = dtkDistributedMessage::CONTROLLER_RUN_RANK;
    d->emitter.setData(&d->value);
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

#if defined(DTK_BUILD_DISTRIBUTED_SUPPORT)

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
    d->emitter.setData(&d->value);
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
    d->emitter.setData(&d->value);
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

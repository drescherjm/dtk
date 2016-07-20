/* @(#)dtkComposerNodeWorld.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 13:04:23
 * Version: $Id$
 * Last-Updated: mer. févr.  5 10:30:59 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 112
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeWorld.h"
#include "dtkComposerTransmitterEmitter.h"

#include <dtkDistributedSupport/dtkDistributedCommunicator.h>
#include <dtkDistributedSupport/dtkDistributedCommunicatorMpi.h>
#include <dtkDistributedSupport/dtkDistributedCommunicatorTcp.h>

#include <dtkCoreSupport/dtkGlobal.h>
//#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeWorldPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeWorldPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter_rank;
    dtkComposerTransmitterEmitter<qlonglong> emitter_size;
    dtkComposerTransmitterEmitter<dtkDistributedCommunicator> emitter_communicator;

public:
    dtkDistributedCommunicatorMpi *communicator;
    qlonglong rank;
    qlonglong size;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeWorld implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeWorld::dtkComposerNodeWorld(void) : dtkComposerNodeComposite(), d(new dtkComposerNodeWorldPrivate)
{
    d->communicator = NULL;

    //FIXME: handle tcp/mpi
    this->appendReceiver(&(d->emitter_communicator));
    this->setInputLabelHint("communicator", 0);

    d->rank = 0;
    d->emitter_rank.setData(&d->rank);
    this->appendReceiver(&(d->emitter_rank));
    this->setInputLabelHint("rank", 1);

    d->size = 0;
    d->emitter_size.setData(&d->size);
    this->appendReceiver(&(d->emitter_size));
    this->setInputLabelHint("size", 2);


}

dtkComposerNodeWorld::~dtkComposerNodeWorld(void)
{
    if (d->communicator)
        delete d->communicator;

    d->communicator = NULL;

    delete d;

    d = NULL;
}

QString dtkComposerNodeWorld::type(void)
{
    return "world";
}

QString dtkComposerNodeWorld::titleHint(void)
{
    return "World";
}

void dtkComposerNodeWorld::begin(void)
{
    //FIXME: use a config parameter to choose between tcp and mpi communicator

    if (!d->communicator) {
        d->communicator = new dtkDistributedCommunicatorMpi;
        d->emitter_communicator.setData(d->communicator);
    }

    if (!d->communicator->initialized())
        d->communicator->initialize();

    d->rank = d->communicator->rank();
    d->size = d->communicator->size();
}

void dtkComposerNodeWorld::end(void)
{
}

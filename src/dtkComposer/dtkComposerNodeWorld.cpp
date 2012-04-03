/* @(#)dtkComposerNodeWorld.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 13:04:23
 * Version: $Id$
 * Last-Updated: mar. avril  3 16:34:53 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 61
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeWorld.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkDistributed/dtkDistributedCommunicatorMpi.h>

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeWorldPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeWorldPrivate
{
public:

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeWorld implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeWorld::dtkComposerNodeWorld(void) : dtkComposerNodeComposite(), d(new dtkComposerNodeWorldPrivate)
{

}

dtkComposerNodeWorld::~dtkComposerNodeWorld(void)
{
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

}

void dtkComposerNodeWorld::end(void)
{

}



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMpiWorldPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMpiWorldPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> *emitter_rank;
    dtkComposerTransmitterEmitter<qlonglong> *emitter_size;
    dtkComposerTransmitterEmitter<dtkDistributedCommunicatorMpi *> *emitter_communicator;

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMpiWorld implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMpiWorld::dtkComposerNodeMpiWorld(void) : dtkComposerNodeWorld(), d(new dtkComposerNodeMpiWorldPrivate)
{

    d->emitter_communicator = new dtkComposerTransmitterEmitter<dtkDistributedCommunicatorMpi *>;
    this->appendReceiver(d->emitter_communicator);
    this->setInputLabelHint("communicator", 0);

    d->emitter_rank = new dtkComposerTransmitterEmitter<qlonglong>;
    this->appendReceiver(d->emitter_rank);
    this->setInputLabelHint("rank", 1);

    d->emitter_rank = new dtkComposerTransmitterEmitter<qlonglong>;
    this->appendReceiver(d->emitter_rank);
    this->setInputLabelHint("size", 2);


}

dtkComposerNodeMpiWorld::~dtkComposerNodeMpiWorld(void)
{
    delete d->emitter_rank;
    delete d->emitter_size;
    delete d->emitter_communicator;
    delete d;

    d = NULL;
}

QString dtkComposerNodeMpiWorld::type(void)
{
    return "mpiworld";
}

QString dtkComposerNodeMpiWorld::titleHint(void)
{
    return "MPI World";
}

void dtkComposerNodeMpiWorld::begin(void)
{

    dtkTrace() <<  "running begin node of MPI world";
    d->emitter_communicator->setData(new dtkDistributedCommunicatorMpi);
    d->emitter_communicator->data()->initialize();

    d->emitter_rank->setData(d->emitter_communicator->data()->rank());
    d->emitter_size->setData(d->emitter_communicator->data()->size());

}

void dtkComposerNodeMpiWorld::end(void)
{
    d->emitter_communicator->data()->uninitialize();
}

/* @(#)dtkComposerNodeWorld.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 13:04:23
 * Version: $Id$
 * Last-Updated: lun. avril 16 12:23:51 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 97
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeWorld.h"
#include "dtkComposerTransmitterEmitter.h"

#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorMpi.h>
#include <dtkDistributed/dtkDistributedCommunicatorTcp.h>

#include <dtkCore/dtkGlobal.h>
//#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeWorldPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeWorldPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> *emitter_rank;
    dtkComposerTransmitterEmitter<qlonglong> *emitter_size;
    dtkComposerTransmitterEmitter<dtkDistributedCommunicatorMpi *> *emitter_communicator;

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeWorld implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeWorld::dtkComposerNodeWorld(void) : dtkComposerNodeComposite(), d(new dtkComposerNodeWorldPrivate)
{

    //FIXME: handle tcp/mpi
    d->emitter_communicator = new dtkComposerTransmitterEmitter<dtkDistributedCommunicatorMpi *>;
    this->appendReceiver(d->emitter_communicator);
    this->setInputLabelHint("communicator", 0);

    d->emitter_rank = new dtkComposerTransmitterEmitter<qlonglong>;
    this->appendReceiver(d->emitter_rank);
    this->setInputLabelHint("rank", 1);

    d->emitter_size = new dtkComposerTransmitterEmitter<qlonglong>;
    this->appendReceiver(d->emitter_size);
    this->setInputLabelHint("size", 2);


}

dtkComposerNodeWorld::~dtkComposerNodeWorld(void)
{
    delete d->emitter_rank;
    delete d->emitter_size;
    delete d->emitter_communicator;
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
    d->emitter_communicator->setData(new dtkDistributedCommunicatorMpi);
    if (!d->emitter_communicator->data()->initialized())
        d->emitter_communicator->data()->initialize();

    d->emitter_rank->setData(d->emitter_communicator->data()->rank());
    d->emitter_size->setData(d->emitter_communicator->data()->size());
}

void dtkComposerNodeWorld::end(void)
{
}

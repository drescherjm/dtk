/* @(#)dtkComposerNodeSpawn_p.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/10/07 10:28:23
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerNodeRemote_p.h"

#include <dtkDistributed/dtkDistributedCommunicator.h>


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeSpawnPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeSpawnPrivate: public dtkComposerNodeRemotePrivate
{

public:
    qlonglong np;
    qlonglong rank;

public:
    QString application;
    bool is_parent;

public:
    dtkDistributedCommunicator *internal_comm;
    dtkDistributedPolicy policy;

public:
    dtkComposerTransmitterEmitter<dtkDistributedCommunicator *> internal_comm_emitter;
    dtkComposerTransmitterEmitter<dtkDistributedCommunicator *> communicator_emitter;
    dtkComposerTransmitterEmitter<qlonglong > rank_emitter;
    dtkComposerTransmitterReceiver<qlonglong > size_receiver;

};




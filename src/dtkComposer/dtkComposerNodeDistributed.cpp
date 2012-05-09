/* @(#)dtkComposerNodeDistributed.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/26 09:03:42
 * Version: $Id$
 * Last-Updated: Wed May  9 09:53:27 2012 (+0200)
 *           By: tkloczko
 *     Update #: 223
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeDistributed.h"

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkDistributed/dtkDistributedCommunicator>
#include <dtkDistributed/dtkDistributedCommunicatorMpi>

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// Communicator Init
// /////////////////////////////////////////////////////////////////


class dtkComposerNodeCommunicatorInitPrivate
{
public:
    dtkComposerTransmitterEmitter<dtkDistributedCommunicatorMpi *> emitter;

public:
    dtkDistributedCommunicator *communicator;
};

dtkComposerNodeCommunicatorInit::dtkComposerNodeCommunicatorInit(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorInitPrivate)
{
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorInit::~dtkComposerNodeCommunicatorInit(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorInit::run(void)
{
    d->emitter.setData(new dtkDistributedCommunicatorMpi);
    d->emitter.data()->initialize();
}


// /////////////////////////////////////////////////////////////////
// Communicator Uninitialize
// /////////////////////////////////////////////////////////////////


class dtkComposerNodeCommunicatorUninitializePrivate
{
public:
    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> receiver;
    dtkComposerTransmitterVariant receiver_fake;

};

dtkComposerNodeCommunicatorUninitialize::dtkComposerNodeCommunicatorUninitialize(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorUninitializePrivate)
{
    this->appendReceiver(&(d->receiver));
    this->appendReceiver(&(d->receiver_fake));
}

dtkComposerNodeCommunicatorUninitialize::~dtkComposerNodeCommunicatorUninitialize(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorUninitialize::run(void)
{
    if (!d->receiver.data())
        return;

    d->receiver.data()->uninitialize();
}


// /////////////////////////////////////////////////////////////////
// Communicator Rank
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorRankPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;
    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> receiver;
};

dtkComposerNodeCommunicatorRank::dtkComposerNodeCommunicatorRank(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorRankPrivate)
{
    this->appendReceiver(&(d->receiver));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorRank::~dtkComposerNodeCommunicatorRank(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorRank::run(void)
{
    d->emitter.setData(d->receiver.data()->rank());
}


// /////////////////////////////////////////////////////////////////
// Communicator Size
// /////////////////////////////////////////////////////////////////


class dtkComposerNodeCommunicatorSizePrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;
    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> receiver;

};

dtkComposerNodeCommunicatorSize::dtkComposerNodeCommunicatorSize(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSizePrivate)
{
    this->appendReceiver(&(d->receiver));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorSize::~dtkComposerNodeCommunicatorSize(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSize::run(void)
{
    d->emitter.setData(d->receiver.data()->size());
}

// /////////////////////////////////////////////////////////////////
// Send Integer
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendIntegerPrivate
{
public:
    // dtkComposerTransmitterEmitter<qlonglong> emitter;
    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> receiver_data;
    dtkComposerTransmitterReceiver<qlonglong> receiver_target;

};

dtkComposerNodeCommunicatorSendInteger::dtkComposerNodeCommunicatorSendInteger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSendIntegerPrivate)
{
    this->appendReceiver(&(d->receiver_comm));
    this->appendReceiver(&(d->receiver_data));
    this->appendReceiver(&(d->receiver_target));

    // d->emitter = new dtkComposerTransmitterEmitter<qlonglong>(this);
    // this->appendEmitter(d->emitter);
}

dtkComposerNodeCommunicatorSendInteger::~dtkComposerNodeCommunicatorSendInteger(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSendInteger::run(void)
{
    qlonglong i = d->receiver_data.data();
    d->receiver_comm.data()->send(&i, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt64,d->receiver_target.data(),0 );
}

// /////////////////////////////////////////////////////////////////
// Send Real
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendRealPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> receiver_comm;
    dtkComposerTransmitterReceiver<double> receiver_data;
    dtkComposerTransmitterReceiver<qlonglong> receiver_target;

};

dtkComposerNodeCommunicatorSendReal::dtkComposerNodeCommunicatorSendReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSendRealPrivate)
{
    this->appendReceiver(&(d->receiver_comm));
    this->appendReceiver(&(d->receiver_data));

    this->appendReceiver(&(d->receiver_target));

}

dtkComposerNodeCommunicatorSendReal::~dtkComposerNodeCommunicatorSendReal(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSendReal::run(void)
{
    double data = d->receiver_data.data();
    d->receiver_comm.data()->send(&data, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorDouble,d->receiver_target.data(),0 );
}


// /////////////////////////////////////////////////////////////////
// Send dtkAbstractData
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> receiver_comm;
    dtkComposerTransmitterReceiver<dtkAbstractData *> receiver_data;
    dtkComposerTransmitterReceiver<qlonglong> receiver_target;

};

dtkComposerNodeCommunicatorSend::dtkComposerNodeCommunicatorSend(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSendPrivate)
{
    this->appendReceiver(&(d->receiver_comm));
    this->appendReceiver(&(d->receiver_data));

    this->appendReceiver(&(d->receiver_target));

}

dtkComposerNodeCommunicatorSend::~dtkComposerNodeCommunicatorSend(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSend::run(void)
{
    d->receiver_comm.data()->send(d->receiver_data.data(), d->receiver_target.data(), 0);
}

// /////////////////////////////////////////////////////////////////
// Receive Integer
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceiveIntegerPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;

    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> receiver_source;

};

dtkComposerNodeCommunicatorReceiveInteger::dtkComposerNodeCommunicatorReceiveInteger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorReceiveIntegerPrivate)
{
    this->appendReceiver(&(d->receiver_comm));
    this->appendReceiver(&(d->receiver_source));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorReceiveInteger::~dtkComposerNodeCommunicatorReceiveInteger(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorReceiveInteger::run(void)
{
    qlonglong i;
    d->receiver_comm.data()->receive(&i, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt64,d->receiver_source.data(),0 );
    d->emitter.setData(i);
}


// /////////////////////////////////////////////////////////////////
// Receive Real
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceiveRealPrivate
{
public:
    dtkComposerTransmitterEmitter<double> emitter;

    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> receiver_source;

};

dtkComposerNodeCommunicatorReceiveReal::dtkComposerNodeCommunicatorReceiveReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorReceiveRealPrivate)
{
    this->appendReceiver(&(d->receiver_comm));
    this->appendReceiver(&(d->receiver_source));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorReceiveReal::~dtkComposerNodeCommunicatorReceiveReal(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorReceiveReal::run(void)
{
    double data;
    d->receiver_comm.data()->receive(&data, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorDouble,d->receiver_source.data(),0 );
    d->emitter.setData(data);
}


// /////////////////////////////////////////////////////////////////
// Receive 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceivePrivate
{
public:
    dtkComposerTransmitterEmitter<dtkAbstractData *> emitter;

    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> receiver_source;

};

dtkComposerNodeCommunicatorReceive::dtkComposerNodeCommunicatorReceive(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorReceivePrivate)
{
    this->appendReceiver(&(d->receiver_comm));
    this->appendReceiver(&(d->receiver_source));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorReceive::~dtkComposerNodeCommunicatorReceive(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorReceive::run(void)
{
    dtkAbstractData *data = NULL;
    d->receiver_comm.data()->receive(data, d->receiver_source.data(), 0);
    d->emitter.setData(data);
}


/* @(#)dtkComposerNodeDistributed.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/26 09:03:42
 * Version: $Id$
 * Last-Updated: mer. mars 28 09:11:25 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 177
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

#include <dtkDistributed/dtkDistributedCommunicator>
#include <dtkDistributed/dtkDistributedCommunicatorMpi>

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// Communicator Init
// /////////////////////////////////////////////////////////////////


class dtkComposerNodeCommunicatorInitPrivate
{
public:
    dtkComposerTransmitterEmitter<dtkDistributedCommunicatorMpi *> *emitter;

public:
    dtkDistributedCommunicator *communicator;
};

dtkComposerNodeCommunicatorInit::dtkComposerNodeCommunicatorInit(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorInitPrivate)
{
    d->emitter = new dtkComposerTransmitterEmitter<dtkDistributedCommunicatorMpi*>(this);

    this->appendEmitter(d->emitter);
}

dtkComposerNodeCommunicatorInit::~dtkComposerNodeCommunicatorInit(void)
{
    delete d->emitter;
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorInit::run(void)
{
    //   if (!d->data())
    d->emitter->setData(new dtkDistributedCommunicatorMpi);
    d->emitter->data()->initialize();
}


// /////////////////////////////////////////////////////////////////
// Communicator Rank
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorRankPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> *emitter;
    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> *receiver;

};

dtkComposerNodeCommunicatorRank::dtkComposerNodeCommunicatorRank(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorRankPrivate)
{
    d->receiver = new dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *>(this);
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerTransmitterEmitter<qlonglong>(this);
    this->appendEmitter(d->emitter);
}

dtkComposerNodeCommunicatorRank::~dtkComposerNodeCommunicatorRank(void)
{
    delete d->emitter;
    delete d->receiver;
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorRank::run(void)
{
    d->emitter->setData(d->receiver->data()->rank());
}


// /////////////////////////////////////////////////////////////////
// Communicator Size
// /////////////////////////////////////////////////////////////////


class dtkComposerNodeCommunicatorSizePrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> *emitter;
    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> *receiver;

};

dtkComposerNodeCommunicatorSize::dtkComposerNodeCommunicatorSize(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSizePrivate)
{
    d->receiver = new dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *>(this);
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerTransmitterEmitter<qlonglong>(this);
    this->appendEmitter(d->emitter);
}

dtkComposerNodeCommunicatorSize::~dtkComposerNodeCommunicatorSize(void)
{
    delete d->emitter;
    delete d->receiver;
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSize::run(void)
{
    d->emitter->setData(d->receiver->data()->size());
}

// /////////////////////////////////////////////////////////////////
// Send Integer
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendIntegerPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> *emitter;
    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> *receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> *receiver_data;
    dtkComposerTransmitterReceiver<qlonglong> *receiver_target;

};

dtkComposerNodeCommunicatorSendInteger::dtkComposerNodeCommunicatorSendInteger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSendIntegerPrivate)
{
    d->receiver_comm = new dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *>(this);
    this->appendReceiver(d->receiver_comm);

    d->receiver_data = new dtkComposerTransmitterReceiver<qlonglong>(this);
    this->appendReceiver(d->receiver_data);

    d->receiver_target = new dtkComposerTransmitterReceiver<qlonglong>(this);
    this->appendReceiver(d->receiver_target);

    // d->emitter = new dtkComposerTransmitterEmitter<qlonglong>(this);
    // this->appendEmitter(d->emitter);
}

dtkComposerNodeCommunicatorSendInteger::~dtkComposerNodeCommunicatorSendInteger(void)
{
    delete d->receiver_comm;
    delete d->receiver_data;
    delete d->receiver_target;
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSendInteger::run(void)
{
    qlonglong i = d->receiver_data->data();
    d->receiver_comm->data()->send(&i, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt64,d->receiver_target->data(),0 );
}

// /////////////////////////////////////////////////////////////////
// Send Real
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendRealPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> *receiver_comm;
    dtkComposerTransmitterReceiver<double> *receiver_data;
    dtkComposerTransmitterReceiver<qlonglong> *receiver_target;

};

dtkComposerNodeCommunicatorSendReal::dtkComposerNodeCommunicatorSendReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSendRealPrivate)
{
    d->receiver_comm = new dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *>(this);
    this->appendReceiver(d->receiver_comm);

    d->receiver_data = new dtkComposerTransmitterReceiver<double>(this);
    this->appendReceiver(d->receiver_data);

    d->receiver_target = new dtkComposerTransmitterReceiver<qlonglong>(this);
    this->appendReceiver(d->receiver_target);

}

dtkComposerNodeCommunicatorSendReal::~dtkComposerNodeCommunicatorSendReal(void)
{
    delete d->receiver_comm;
    delete d->receiver_data;
    delete d->receiver_target;
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSendReal::run(void)
{
    double data = d->receiver_data->data();
    d->receiver_comm->data()->send(&data, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorDouble,d->receiver_target->data(),0 );
}


// /////////////////////////////////////////////////////////////////
// Send dtkAbstractData
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> *receiver_comm;
    dtkComposerTransmitterReceiver<dtkAbstractData *> *receiver_data;
    dtkComposerTransmitterReceiver<qlonglong> *receiver_target;

};

dtkComposerNodeCommunicatorSend::dtkComposerNodeCommunicatorSend(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSendPrivate)
{
    d->receiver_comm = new dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *>(this);
    this->appendReceiver(d->receiver_comm);

    d->receiver_data = new dtkComposerTransmitterReceiver<dtkAbstractData *>(this);
    this->appendReceiver(d->receiver_data);

    d->receiver_target = new dtkComposerTransmitterReceiver<qlonglong>(this);
    this->appendReceiver(d->receiver_target);

}

dtkComposerNodeCommunicatorSend::~dtkComposerNodeCommunicatorSend(void)
{
    delete d->receiver_comm;
    delete d->receiver_data;
    delete d->receiver_target;
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSend::run(void)
{
    d->receiver_comm->data()->send(d->receiver_data->data(), d->receiver_target->data(), 0);
}

// /////////////////////////////////////////////////////////////////
// Receive Integer
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceiveIntegerPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> *emitter;

    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> *receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> *receiver_source;

};

dtkComposerNodeCommunicatorReceiveInteger::dtkComposerNodeCommunicatorReceiveInteger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorReceiveIntegerPrivate)
{
    d->receiver_comm = new dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *>(this);
    this->appendReceiver(d->receiver_comm);

    d->receiver_source = new dtkComposerTransmitterReceiver<qlonglong>(this);
    this->appendReceiver(d->receiver_source);

    d->emitter = new dtkComposerTransmitterEmitter<qlonglong>(this);
    this->appendEmitter(d->emitter);
}

dtkComposerNodeCommunicatorReceiveInteger::~dtkComposerNodeCommunicatorReceiveInteger(void)
{
    delete d->receiver_comm;
    delete d->receiver_source;
    delete d->emitter;
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorReceiveInteger::run(void)
{
    qlonglong i;
    d->receiver_comm->data()->receive(&i, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt64,d->receiver_source->data(),0 );
    d->emitter->setData(i);
}


// /////////////////////////////////////////////////////////////////
// Receive Real
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceiveRealPrivate
{
public:
    dtkComposerTransmitterEmitter<double> *emitter;

    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> *receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> *receiver_source;

};

dtkComposerNodeCommunicatorReceiveReal::dtkComposerNodeCommunicatorReceiveReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorReceiveRealPrivate)
{
    d->receiver_comm = new dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *>(this);
    this->appendReceiver(d->receiver_comm);

    d->receiver_source = new dtkComposerTransmitterReceiver<qlonglong>(this);
    this->appendReceiver(d->receiver_source);

    d->emitter = new dtkComposerTransmitterEmitter<double>(this);
    this->appendEmitter(d->emitter);
}

dtkComposerNodeCommunicatorReceiveReal::~dtkComposerNodeCommunicatorReceiveReal(void)
{
    delete d->receiver_comm;
    delete d->receiver_source;
    delete d->emitter;
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorReceiveReal::run(void)
{
    double data;
    d->receiver_comm->data()->receive(&data, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorDouble,d->receiver_source->data(),0 );
    d->emitter->setData(data);
}


// /////////////////////////////////////////////////////////////////
// Receive 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceivePrivate
{
public:
    dtkComposerTransmitterEmitter<dtkAbstractData *> *emitter;

    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *> *receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> *receiver_source;

};

dtkComposerNodeCommunicatorReceive::dtkComposerNodeCommunicatorReceive(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorReceivePrivate)
{
    d->receiver_comm = new dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi *>(this);
    this->appendReceiver(d->receiver_comm);

    d->receiver_source = new dtkComposerTransmitterReceiver<qlonglong>(this);
    this->appendReceiver(d->receiver_source);

    d->emitter = new dtkComposerTransmitterEmitter<dtkAbstractData *>(this);
    this->appendEmitter(d->emitter);
}

dtkComposerNodeCommunicatorReceive::~dtkComposerNodeCommunicatorReceive(void)
{
    delete d->receiver_comm;
    delete d->receiver_source;
    delete d->emitter;
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorReceive::run(void)
{
    dtkAbstractData *data;
    d->receiver_comm->data()->receive(data, d->receiver_source->data(), 0);
    d->emitter->setData(data);
}


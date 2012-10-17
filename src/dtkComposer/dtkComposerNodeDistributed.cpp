/* @(#)dtkComposerNodeDistributed.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/26 09:03:42
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
#include <dtkDistributed/dtkDistributedCommunicatorTcp>

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// Communicator Init
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorInitPrivate
{
public:
    dtkComposerTransmitterEmitter<dtkDistributedCommunicatorMpi> emitter;

public:
    dtkDistributedCommunicatorMpi *communicator;
};

dtkComposerNodeCommunicatorInit::dtkComposerNodeCommunicatorInit(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorInitPrivate)
{
    d->communicator = NULL;

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorInit::~dtkComposerNodeCommunicatorInit(void)
{
    if (d->communicator)
        delete d->communicator;
    d->communicator = NULL;

    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorInit::run(void)
{
    if (!d->communicator) {
        d->communicator = new dtkDistributedCommunicatorMpi;
        d->emitter.setData(d->communicator);
    }

    if (!d->communicator->initialized())
        d->communicator->initialize();
}


// /////////////////////////////////////////////////////////////////
// Communicator Uninitialize
// /////////////////////////////////////////////////////////////////


class dtkComposerNodeCommunicatorUninitializePrivate
{
public:
    dtkComposerTransmitterReceiver<dtkDistributedCommunicator> receiver;
    dtkComposerTransmitterVariant receiver_fake;

};

dtkComposerNodeCommunicatorUninitialize::dtkComposerNodeCommunicatorUninitialize(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorUninitializePrivate)
{
    d->receiver.setDataTransmission(dtkComposerTransmitter::Reference);
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
    if (!d->receiver.isEmpty()) {
        dtkDistributedCommunicator *communicator = d->receiver.data();
        
        if (communicator) {
            communicator->uninitialize();
        } else {
            dtkError() << "Input communicator not valid.";
            return;
        }

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        
    }
}

// /////////////////////////////////////////////////////////////////
// Communicator Rank
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorRankPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkDistributedCommunicator> receiver;
    dtkComposerTransmitterEmitter<qlonglong> emitter;

public:
    qlonglong rank;
};

dtkComposerNodeCommunicatorRank::dtkComposerNodeCommunicatorRank(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorRankPrivate)
{
    d->receiver.setDataTransmission(dtkComposerTransmitter::Reference);
    this->appendReceiver(&(d->receiver));

    d->rank = -1;
    d->emitter.setData(&d->rank);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorRank::~dtkComposerNodeCommunicatorRank(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorRank::run(void)
{
    if (!d->receiver.isEmpty()) {

        dtkDistributedCommunicator *communicator = d->receiver.data();

        if (!communicator) {
            d->rank = -1;
            dtkError() << "Input communicator not valid.";
            return;
        }

        d->rank = communicator->rank();

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->rank = 0;

    }
}


// /////////////////////////////////////////////////////////////////
// Communicator Size
// /////////////////////////////////////////////////////////////////


class dtkComposerNodeCommunicatorSizePrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;
    dtkComposerTransmitterReceiver<dtkDistributedCommunicatorMpi> receiver;

public:
    qlonglong size;

};

dtkComposerNodeCommunicatorSize::dtkComposerNodeCommunicatorSize(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSizePrivate)
{
    d->receiver.setDataTransmission(dtkComposerTransmitter::Reference);
    this->appendReceiver(&(d->receiver));

    d->size = 0;
    d->emitter.setData(&d->size);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorSize::~dtkComposerNodeCommunicatorSize(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSize::run(void)
{
    if (!d->receiver.isEmpty()) {

        dtkDistributedCommunicatorMpi *communicator = d->receiver.data();
        
        if (!communicator) {
            d->size = 0;
            dtkError() << "Input communicator not valid.";
            return;
        }
        
        d->size = communicator->size();
    
    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->size = 0;

    }
}

// /////////////////////////////////////////////////////////////////
// Send Integer
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendIntegerPrivate
{
public:
    // dtkComposerTransmitterEmitter<qlonglong> emitter;
    dtkComposerTransmitterReceiver<dtkDistributedCommunicator > receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> receiver_data;
    dtkComposerTransmitterReceiver<qlonglong> receiver_target;

};

dtkComposerNodeCommunicatorSendInteger::dtkComposerNodeCommunicatorSendInteger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSendIntegerPrivate)
{
    d->receiver_comm.setDataTransmission(dtkComposerTransmitter::Reference);
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
    if (!d->receiver_data.isEmpty() && !d->receiver_comm.isEmpty() && !d->receiver_target.isEmpty() ) {

        qlonglong i = *d->receiver_data.data();
        dtkDistributedCommunicator *communicator = d->receiver_comm.data();

        if (!communicator) {
            dtkError() << "Input communicator not valid.";
            return;
        }

        communicator->send(&i, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt64, *d->receiver_target.data(), 0);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// Send Real
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendRealPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkDistributedCommunicator> receiver_comm;
    dtkComposerTransmitterReceiver<double> receiver_data;
    dtkComposerTransmitterReceiver<qlonglong> receiver_target;

};

dtkComposerNodeCommunicatorSendReal::dtkComposerNodeCommunicatorSendReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSendRealPrivate)
{
    d->receiver_comm.setDataTransmission(dtkComposerTransmitter::Reference);
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
    if (!d->receiver_data.isEmpty() && !d->receiver_comm.isEmpty() && !d->receiver_target.isEmpty() ) {

        double data = *d->receiver_data.data();
        dtkDistributedCommunicator *communicator = d->receiver_comm.data();

        if (!communicator) {
            dtkError() << "Input communicator not valid.";
            return;
        }

        communicator->send(&data, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt64, *d->receiver_target.data(), 0);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// Send dtkAbstractData
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkDistributedCommunicator> receiver_comm;
    dtkComposerTransmitterReceiver<dtkAbstractData> receiver_data;
    dtkComposerTransmitterReceiver<qlonglong> receiver_target;

};

dtkComposerNodeCommunicatorSend::dtkComposerNodeCommunicatorSend(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSendPrivate)
{
    d->receiver_comm.setDataTransmission(dtkComposerTransmitter::Reference);
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
    if (!d->receiver_data.isEmpty() && !d->receiver_comm.isEmpty() && !d->receiver_target.isEmpty() ) {

        dtkAbstractData *data = d->receiver_data.data();
        dtkDistributedCommunicator *communicator = d->receiver_comm.data();

        if (!communicator) {
            dtkError() << "Input communicator not valid.";
            return;
        }
        communicator->send(data, *d->receiver_target.data(), 0);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// Receive Integer
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceiveIntegerPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;

    dtkComposerTransmitterReceiver<dtkDistributedCommunicator> receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> receiver_source;

public:
    qlonglong value;
};

dtkComposerNodeCommunicatorReceiveInteger::dtkComposerNodeCommunicatorReceiveInteger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorReceiveIntegerPrivate)
{
    d->receiver_comm.setDataTransmission(dtkComposerTransmitter::Reference);
    this->appendReceiver(&(d->receiver_comm));
    this->appendReceiver(&(d->receiver_source));

    d->value = 0;
    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorReceiveInteger::~dtkComposerNodeCommunicatorReceiveInteger(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorReceiveInteger::run(void)
{
    if (!d->receiver_source.isEmpty() && !d->receiver_comm.isEmpty()) {

        qlonglong source = *d->receiver_source.data();
        dtkDistributedCommunicator *communicator = d->receiver_comm.data();

        if (!communicator) {
            dtkError() << "Input communicator not valid.";
            return;
        }

        communicator->receive(&(d->value), 1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt64, source, 0);

    } else {
        d->value = 0;
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}


// /////////////////////////////////////////////////////////////////
// Receive Real
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceiveRealPrivate
{
public:
    dtkComposerTransmitterEmitter<double> emitter;

    dtkComposerTransmitterReceiver<dtkDistributedCommunicator> receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> receiver_source;

public:
    double value;
};

dtkComposerNodeCommunicatorReceiveReal::dtkComposerNodeCommunicatorReceiveReal(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorReceiveRealPrivate)
{
    d->receiver_comm.setDataTransmission(dtkComposerTransmitter::Reference);
    this->appendReceiver(&(d->receiver_comm));
    this->appendReceiver(&(d->receiver_source));

    d->value = 0.;
    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorReceiveReal::~dtkComposerNodeCommunicatorReceiveReal(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorReceiveReal::run(void)
{
    if (!d->receiver_source.isEmpty() && !d->receiver_comm.isEmpty()) {

        qlonglong source = *d->receiver_source.data();
        dtkDistributedCommunicator *communicator = d->receiver_comm.data();

        if (!communicator) {
            dtkError() << "Input communicator not valid.";
            return;
        }

        communicator->receive(&(d->value), 1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt64, source, 0);

    } else {
        d->value = 0.;
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}


// /////////////////////////////////////////////////////////////////
// Receive 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceivePrivate
{
public:
    dtkComposerTransmitterEmitter<dtkAbstractData> emitter;

    dtkComposerTransmitterReceiver<dtkDistributedCommunicator> receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> receiver_source;
};

dtkComposerNodeCommunicatorReceive::dtkComposerNodeCommunicatorReceive(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorReceivePrivate)
{
    d->receiver_comm.setDataTransmission(dtkComposerTransmitter::Reference);
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
    if (!d->receiver_source.isEmpty() && !d->receiver_comm.isEmpty()) {

        qlonglong source = *d->receiver_source.data();
        dtkDistributedCommunicator *communicator = d->receiver_comm.data();

        if (!communicator) {
            dtkError() << "Input communicator not valid.";
            return;
        }

        dtkAbstractData *data = NULL;
        communicator->receive(data, source, 0); 
        if (data)
            d->emitter.setData(data);
        else
            d->emitter.clearData();

    } else {
        d->emitter.clearData();
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}


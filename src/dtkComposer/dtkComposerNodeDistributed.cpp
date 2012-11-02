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

#include <mpi.h>

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
// Send Variant
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkDistributedCommunicator> receiver_comm;
    dtkComposerTransmitterVariant receiver_data;
    dtkComposerTransmitterReceiver<qlonglong> receiver_target;
    dtkComposerTransmitterReceiver<qlonglong> receiver_tag;

};

dtkComposerNodeCommunicatorSend::dtkComposerNodeCommunicatorSend(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSendPrivate)
{
    d->receiver_comm.setDataTransmission(dtkComposerTransmitter::Reference);
    this->appendReceiver(&(d->receiver_comm));
    this->appendReceiver(&(d->receiver_data));

    this->appendReceiver(&(d->receiver_target));
    this->appendReceiver(&(d->receiver_tag));

}

dtkComposerNodeCommunicatorSend::~dtkComposerNodeCommunicatorSend(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSend::run(void)
{
    if (!d->receiver_data.isEmpty() && !d->receiver_comm.isEmpty() && !d->receiver_target.isEmpty() ) {

        QByteArray array = d->receiver_data.dataToByteArray();
        dtkTrace() << "Got data as byte array to be sent" << array.size();

        dtkDistributedCommunicator *communicator = d->receiver_comm.data();

        if (!communicator) {
            dtkError() << "Input communicator not valid.";
            return;
        }

        int tag = 0;
        if (!d->receiver_tag.isEmpty())
            tag = *(d->receiver_tag.data());

        communicator->send(array, *d->receiver_target.data(), tag);

    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}


// /////////////////////////////////////////////////////////////////
// Receive Variant
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceivePrivate
{
public:
    dtkComposerTransmitterVariant emitter;
    dtkComposerTransmitterEmitter<qlonglong> emitter_source;
    dtkComposerTransmitterEmitter<qlonglong> emitter_tag;

    dtkComposerTransmitterReceiver<dtkDistributedCommunicator> receiver_comm;
    dtkComposerTransmitterReceiver<qlonglong> receiver_source;
    dtkComposerTransmitterReceiver<qlonglong> receiver_tag;

    QMap<qlonglong, dtkDistributedMessage *> msg_map;

public:
    qlonglong source;
    qlonglong tag;
    qlonglong size;

};

dtkComposerNodeCommunicatorReceive::dtkComposerNodeCommunicatorReceive(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorReceivePrivate)
{
    d->receiver_comm.setDataTransmission(dtkComposerTransmitter::Reference);
    this->appendReceiver(&(d->receiver_comm));
    this->appendReceiver(&(d->receiver_source));
    this->appendReceiver(&(d->receiver_tag));

    this->appendEmitter(&(d->emitter));
    this->appendEmitter(&(d->emitter_source));
    this->appendEmitter(&(d->emitter_tag));

    d->source = 0;
    d->tag    = 0;

    d->emitter_source.setData(&(d->source));
    d->emitter_tag.setData(&(d->tag));
}

dtkComposerNodeCommunicatorReceive::~dtkComposerNodeCommunicatorReceive(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorReceive::run(void)
{
    if (!d->receiver_source.isEmpty() && !d->receiver_comm.isEmpty()) {

        d->source = *d->receiver_source.data();
        dtkDistributedCommunicator *communicator = d->receiver_comm.data();

        d->tag = 0;
        if (!d->receiver_tag.isEmpty())
            d->tag = *(d->receiver_tag.data());

        if (!communicator) {
            dtkError() << "Input communicator not valid.";
            return;
        }

        if (dtkDistributedCommunicatorTcp *tcp = dynamic_cast<dtkDistributedCommunicatorTcp *>(communicator)) {
            dtkDebug() << "TCP communicator. Parse message from socket";
            if (d->msg_map.contains(d->tag)) {
                dtkDebug() << "msg already received for tag" << d->tag;
                d->emitter.setTwinned(false);
                dtkDistributedMessage *msg = d->msg_map.take(d->tag);
                d->emitter.setDataFrom(msg->content());
                d->emitter.setTwinned(true);
                delete msg;
                return;
            }

            tcp->socket()->blockSignals(true); // needed ?

            if (!tcp->socket()->waitForReadyRead(300000)) {
                dtkWarn() << "Data not ready in receive for rank " << d->source;
            } else {
                dtkDistributedMessage *msg = tcp->socket()->parseRequest();
                int msg_tag = msg->header("Tag").toInt();
                if (msg_tag == d->tag || d->tag == dtkDistributedCommunicator::ANY_TAG) {
                    dtkTrace() << "OK, this is the expected tag " << d->tag;
                    d->emitter.setTwinned(false);
                    d->emitter.setDataFrom(msg->content());
                    d->emitter.setTwinned(true);
                    delete msg;
                    if (d->tag == dtkDistributedCommunicator::ANY_TAG)
                        d->tag = msg_tag;
                } else {
                    //store msg for another call with the right tag
                    dtkInfo() << "Msg received, but wrong tag, store the msg" << d->tag << msg_tag;
                    d->msg_map.insert(msg_tag,msg);
                    this->run(); // do it again
                }
            }
            tcp->socket()->blockSignals(false); // needed ?
        } else { // MPI
            QByteArray array;
            dtkDistributedCommunicatorStatus status;
            communicator->receive(array, d->source, d->tag, status);

            if (d->tag == dtkDistributedCommunicator::ANY_TAG)
                d->tag = status.tag();
            if (d->source == dtkDistributedCommunicator::ANY_SOURCE)
                d->source = status.source();

            if (!array.isEmpty()) {
                d->emitter.setTwinned(false);
                d->emitter.setDataFrom(array);
                d->emitter.setTwinned(true);
            } else {
                dtkWarn() << "Empty data in receive";
                d->emitter.clearData();
            }
        }
    } else {
        d->emitter.clearData();
        dtkWarn() << "Inputs not specified. Nothing is done";
    }
}


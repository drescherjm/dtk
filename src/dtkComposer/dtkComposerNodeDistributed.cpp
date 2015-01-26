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

#include <dtkLog>
#include <dtkDistributed>

#include <QTcpSocket>



// /////////////////////////////////////////////////////////////////
// Communicator Init
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorInitPrivate
{
public:
    dtkComposerTransmitterEmitter<dtkDistributedCommunicator*> emitter;

public:
    dtkComposerTransmitterReceiver<QString> receiver_type;

public:
    dtkDistributedCommunicator *communicator;
    QString type;
};

dtkComposerNodeCommunicatorInit::dtkComposerNodeCommunicatorInit(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorInitPrivate)
{
    d->communicator = NULL;

    d->type = QString::fromUtf8(qgetenv(qPrintable("DTK_DISTRIBUTED_POLICY")));
    if (d->type.isEmpty()) {
        d->type = "qthreads";
    }
    this->appendEmitter(&(d->emitter));
    this->appendReceiver(&(d->receiver_type));
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
    if (!d->receiver_type.isEmpty()) {
        d->type = d->receiver_type.data();
    }
    if (!d->communicator) {
        d->communicator = dtkDistributed::communicator::pluginFactory().create(d->type);

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
    dtkComposerTransmitterReceiver<dtkDistributedCommunicator*> receiver;
    dtkComposerTransmitterReceiverVariant receiver_fake;

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
        dtkDistributedCommunicator *communicator = NULL;
        //FIXME:[migration] new transmitter requieres a clone method in object, even if dataTransmission is set to reference
        // communicator = d->receiver.data();

        if (communicator) {
            communicator->uninitialize();
        } else {
            dtkError() << "Input communicator not valid.";
            return;
        }

    } else {
        dtkWarn() << "Communicator not connected. Nothing is done";
    }
}

// /////////////////////////////////////////////////////////////////
// Communicator Rank
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorRankPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkDistributedCommunicator*> receiver;
    dtkComposerTransmitterEmitter<qlonglong> emitter;

public:
    qlonglong rank;
};

dtkComposerNodeCommunicatorRank::dtkComposerNodeCommunicatorRank(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorRankPrivate)
{
    d->receiver.setDataTransmission(dtkComposerTransmitter::Reference);
    this->appendReceiver(&(d->receiver));

    d->rank = -1;
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

        dtkDistributedCommunicator *communicator = NULL;
        communicator = d->receiver.constData();

        if (!communicator) {
            d->rank = -1;
            dtkError() << "Input communicator not valid.";
            return;
        }

        d->rank = communicator->rank();

    } else {
        dtkWarn() << "Communicator not connected. Nothing is done";
        d->rank = 0;

    }

    d->emitter.setData(d->rank);
}


// /////////////////////////////////////////////////////////////////
// Communicator Size
// /////////////////////////////////////////////////////////////////


class dtkComposerNodeCommunicatorSizePrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;
    dtkComposerTransmitterReceiver<dtkDistributedCommunicator*> receiver;

public:
    qlonglong size;

};

dtkComposerNodeCommunicatorSize::dtkComposerNodeCommunicatorSize(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSizePrivate)
{
    d->receiver.setDataTransmission(dtkComposerTransmitter::Reference);
    this->appendReceiver(&(d->receiver));

    d->size = 0;
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

        dtkDistributedCommunicator *communicator = d->receiver.constData();

        if (!communicator) {
            d->size = 0;
            dtkError() << "Input communicator not valid.";
            return;
        }

        d->size = communicator->size();

    } else {
        dtkWarn() << "Communicator not connected. Nothing is done";
        d->size = 0;

    }

    d->emitter.setData(d->size);
}


// /////////////////////////////////////////////////////////////////
// Send Variant
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkDistributedCommunicator*> receiver_comm;
    dtkComposerTransmitterReceiver<QTcpSocket*> receiver_socket;
    dtkComposerTransmitterReceiverVariant receiver_data;
    dtkComposerTransmitterReceiver<qlonglong> receiver_target;
    dtkComposerTransmitterReceiver<qlonglong> receiver_tag;

    dtkComposerTransmitterEmitter<bool> emitter;

public:
    dtkDistributedCommunicator *communicator;
    QTcpSocket *socket;

};

dtkComposerNodeCommunicatorSend::dtkComposerNodeCommunicatorSend(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSendPrivate)
{
    d->communicator = NULL;
    d->socket       = NULL;
    d->receiver_comm.setDataTransmission(dtkComposerTransmitter::Reference);
    d->receiver_socket.setDataTransmission(dtkComposerTransmitter::Reference);
    this->appendReceiver(&(d->receiver_comm));
    this->appendReceiver(&(d->receiver_socket));
    this->appendReceiver(&(d->receiver_data));

    this->appendReceiver(&(d->receiver_target));
    this->appendReceiver(&(d->receiver_tag));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorSend::~dtkComposerNodeCommunicatorSend(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSend::run(void)
{
    d->emitter.setData(false);
    if (!d->receiver_data.isEmpty()  && !d->receiver_target.isEmpty() ) {

        if (d->receiver_comm.isEmpty() && d->receiver_socket.isEmpty()) {
            dtkError() << "Send node at either a socket or a communicator.";
            return;
        }

        QVariant v = d->receiver_data.variant();

        qint32 tag = 0;
        if (!d->receiver_tag.isEmpty())
            tag = d->receiver_tag.data();

        qlonglong target = d->receiver_target.data();

        if (d->receiver_comm.isEmpty()) {
            d->socket = d->receiver_socket.constData();
            d->communicator = NULL;
            //FIXME: we need the jobid
            QString jobid;
            dtkDistributedMessage *msg = new dtkDistributedMessage(dtkDistributedMessage::DATA, jobid, target, v);
            msg->addHeader("Tag",QString::number(tag));
            msg->send(d->socket);
        } else {
            //FIXME:[migration] new transmitter requieres a clone method in object, even if dataTransmission is set to reference
            d->communicator = d->receiver_comm.constData();
            d->socket = NULL;
            // FIXME: [migration] handle variant in send (should be ok with new distributed layer
            // d->communicator->send(v, target , tag);
        }


        d->emitter.setData(true);

        dtkTrace() << "send to target: " << target ;

    } else {
        dtkWarn() << "Inputs not specified in Send node. Nothing is done"  ;
    }
}


// /////////////////////////////////////////////////////////////////
// Receive Variant
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceivePrivate
{
public:
    dtkComposerTransmitterEmitterVariant emitter;
    dtkComposerTransmitterEmitter<qlonglong> emitter_source;
    dtkComposerTransmitterEmitter<qlonglong> emitter_tag;

    dtkComposerTransmitterReceiver<dtkDistributedCommunicator*> receiver_comm;
    dtkComposerTransmitterReceiver<QTcpSocket*> receiver_socket;
    dtkComposerTransmitterReceiver<qlonglong> receiver_source;
    dtkComposerTransmitterReceiver<qlonglong> receiver_tag;
    dtkComposerTransmitterReceiverVariant     receiver_data;

public:
    qlonglong source;
    qlonglong tag;
    QMap<qlonglong, dtkDistributedMessage *> msg_map;

};

dtkComposerNodeCommunicatorReceive::dtkComposerNodeCommunicatorReceive(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorReceivePrivate)
{
    d->receiver_comm.setDataTransmission(dtkComposerTransmitter::Reference);
    this->appendReceiver(&(d->receiver_comm));
    this->appendReceiver(&(d->receiver_socket));
    this->appendReceiver(&(d->receiver_source));
    this->appendReceiver(&(d->receiver_tag));
    this->appendReceiver(&(d->receiver_data));

    this->appendEmitter(&(d->emitter));
    this->appendEmitter(&(d->emitter_source));
    this->appendEmitter(&(d->emitter_tag));

    d->source = 0;
    d->tag    = 0;

}

dtkComposerNodeCommunicatorReceive::~dtkComposerNodeCommunicatorReceive(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorReceive::run(void)
{

    if (!d->receiver_source.isEmpty()) {


        if (d->receiver_comm.isEmpty() && d->receiver_socket.isEmpty()) {
            dtkError() << "Send node at either a socket or a communicator.";
            return;
        }

        d->source = d->receiver_source.data();

        d->tag = 0;
        if (!d->receiver_tag.isEmpty())
            d->tag = d->receiver_tag.data();

        d->emitter.clearData();
        if (!d->receiver_data.isEmpty()) {
            d->emitter.setData(d->receiver_data.variant());
        }

        if (d->receiver_comm.isEmpty()) {
            QTcpSocket *socket = d->receiver_socket.constData();
            dtkDebug() << "TCP communicator. Parse message from socket, waiting for tag" << d->tag;
            if (d->msg_map.contains(d->tag)) {
                dtkDebug() << "msg already received for tag" << d->tag;
                // d->emitter.setTwinned(false);
                dtkDistributedMessage *msg = d->msg_map.take(d->tag);
                d->emitter.setData(msg->content());
                // d->emitter.setTwinned(true);
                delete msg;
                return;
            } else {
                dtkTrace() << "msg not yet received, wait for data";
            }

            socket->blockSignals(true); // needed ?

            if (!socket->waitForReadyRead(300000)) {
                dtkWarn() << "Data not ready in receive for rank " << d->source;
            } else {
                dtkDistributedMessage msg;
                msg.parse(socket);
                qlonglong msg_tag = msg.header("Tag").toLongLong();
                if (msg_tag == d->tag || d->tag == dtkDistributedCommunicator::ANY_TAG) {
                    dtkTrace() << "OK, this is the expected tag " << d->tag;
                    // d->emitter.setTwinned(false);
                    d->emitter.setData(msg.content());
                    // d->emitter.setTwinned(true);
                    if (d->tag == dtkDistributedCommunicator::ANY_TAG)
                        d->tag = msg_tag;
                } else {
                    //store msg for another call with the right tag
                    dtkInfo() << "Msg received, but wrong tag, store the msg" << d->tag << msg_tag;
                    d->msg_map.insert(msg_tag, &msg);
                    this->run(); // do it again
                }
            }
            socket->blockSignals(false); // needed ?
        } else { // MPI
            QByteArray array;
            dtkDistributedCommunicatorStatus status;
            dtkDistributedCommunicator *communicator = d->receiver_comm.constData();
            //FIXME:[migration] new transmitter requieres a clone method in object, even if dataTransmission is set to reference
            communicator->receive(array, d->source, d->tag, status);

            if (d->tag == dtkDistributedCommunicator::ANY_TAG)
                d->tag = status.tag();
            if (d->source == dtkDistributedCommunicator::ANY_SOURCE)
                d->source = status.source();

            if (!array.isEmpty()) {
                // d->emitter.setTwinned(false);
                d->emitter.setData(array);
                // d->emitter.setTwinned(true);
            } else {
                dtkWarn() << "Empty data in receive";
                d->emitter.clearData();
            }
        }
    } else {
        d->emitter.clearData();
        dtkWarn() << "Inputs not specified in receive. Nothing is done";
        d->tag = 0;
        d->source = 0;
    }

    d->emitter_source.setData(d->source);
    d->emitter_tag.setData(d->tag);

}


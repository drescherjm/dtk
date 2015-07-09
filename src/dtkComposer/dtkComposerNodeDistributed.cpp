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
// Communicator Rank
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorRankPrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;

public:
    dtkDistributedCommunicator *communicator;

public:
    qlonglong rank;
};

dtkComposerNodeCommunicatorRank::dtkComposerNodeCommunicatorRank(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorRankPrivate)
{
    d->rank = -1;
    d->communicator = NULL;
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorRank::~dtkComposerNodeCommunicatorRank(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorRank::run(void)
{
    if (!d->communicator) {
        d->communicator = dtkDistributed::communicator::instance();
    }

    d->rank = d->communicator->rank();
    d->emitter.setData(d->rank);
}

// /////////////////////////////////////////////////////////////////
// Communicator Size
// /////////////////////////////////////////////////////////////////


class dtkComposerNodeCommunicatorSizePrivate
{
public:
    dtkComposerTransmitterEmitter<qlonglong> emitter;

public:
    dtkDistributedCommunicator *communicator;

public:
    qlonglong size;

};

dtkComposerNodeCommunicatorSize::dtkComposerNodeCommunicatorSize(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorSizePrivate)
{
    d->size = 1;
    d->communicator = NULL;
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorSize::~dtkComposerNodeCommunicatorSize(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSize::run(void)
{
    if (!d->communicator) {
        d->communicator = dtkDistributed::communicator::instance();
    }

    d->size = d->communicator->size();
    d->emitter.setData(d->size);
}


// /////////////////////////////////////////////////////////////////
// Send Variant
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendPrivate
{
public:
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
    d->receiver_socket.setDataTransmission(dtkComposerTransmitter::Reference);
    this->appendReceiver(&(d->receiver_data));
    this->appendReceiver(&(d->receiver_target));
    this->appendReceiver(&(d->receiver_tag));
    this->appendReceiver(&(d->receiver_socket));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeCommunicatorSend::~dtkComposerNodeCommunicatorSend(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorSend::run(void)
{
    if (!d->communicator) {
        d->communicator = dtkDistributed::communicator::instance();
    }

    d->emitter.setData(false);
    if (!d->receiver_data.isEmpty()  && !d->receiver_target.isEmpty() ) {

        QVariant v = d->receiver_data.variant();

        qint32 tag = 0;
        if (!d->receiver_tag.isEmpty())
            tag = d->receiver_tag.data();

        qlonglong target = d->receiver_target.data();

        if (!d->receiver_socket.isEmpty()) {
            d->socket = d->receiver_socket.constData();
            d->communicator = NULL;
            //FIXME: we need the jobid
            QString jobid;
            dtkDistributedMessage *msg = new dtkDistributedMessage(dtkDistributedMessage::DATA, jobid, target, v);
            msg->addHeader("Tag",QString::number(tag));
            msg->send(d->socket);
        } else {
            d->socket = NULL;
            d->communicator->send(v, target , tag);
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

    dtkComposerTransmitterReceiver<QTcpSocket*> receiver_socket;
    dtkComposerTransmitterReceiver<qlonglong> receiver_source;
    dtkComposerTransmitterReceiver<qlonglong> receiver_tag;
    dtkComposerTransmitterReceiverVariant     receiver_data;

public:
    dtkDistributedCommunicator *communicator;
    qlonglong source;
    qlonglong tag;
    QMap<qlonglong, dtkDistributedMessage *> msg_map;

};

dtkComposerNodeCommunicatorReceive::dtkComposerNodeCommunicatorReceive(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeCommunicatorReceivePrivate)
{
    this->appendReceiver(&(d->receiver_source));
    this->appendReceiver(&(d->receiver_tag));
    this->appendReceiver(&(d->receiver_data));
    this->appendReceiver(&(d->receiver_socket));

    this->appendEmitter(&(d->emitter));
    this->appendEmitter(&(d->emitter_source));
    this->appendEmitter(&(d->emitter_tag));

    d->source = 0;
    d->tag    = 0;
    d->communicator = NULL;

}

dtkComposerNodeCommunicatorReceive::~dtkComposerNodeCommunicatorReceive(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeCommunicatorReceive::run(void)
{
    if (!d->communicator) {
        d->communicator = dtkDistributed::communicator::instance();
    }

    if (!d->receiver_source.isEmpty()) {

        d->source = d->receiver_source.data();

        d->tag = 0;
        if (!d->receiver_tag.isEmpty())
            d->tag = d->receiver_tag.data();

        d->emitter.clearData();
        if (!d->receiver_data.isEmpty()) {
            d->emitter.setData(d->receiver_data.variant());
        }

        if (!d->receiver_socket.isEmpty()) {
            QTcpSocket *socket = d->receiver_socket.constData();
            dtkDebug() << "TCP communicator. Parse message from socket, waiting for tag" << d->tag;
            if (d->msg_map.contains(d->tag)) {
                dtkDebug() << "msg already received for tag" << d->tag;
                dtkDistributedMessage *msg = d->msg_map.take(d->tag);
                d->emitter.setData(msg->variant());
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
                    d->emitter.setData(msg.variant());
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
        } else { // communicator
            QVariant v;
            dtkDistributedCommunicatorStatus status;
            d->communicator->receive(v, d->source, d->tag, status);

            if (d->tag == dtkDistributedCommunicator::ANY_TAG)
                d->tag = status.tag();
            if (d->source == dtkDistributedCommunicator::ANY_SOURCE)
                d->source = status.source();

            d->emitter.setData(v);
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


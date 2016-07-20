// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:


#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterReceiver.h"

// ///////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverBase implementation
// ///////////////////////////////////////////////////////////////////

dtkComposerTransmitterReceiverBase::dtkComposerTransmitterReceiverBase(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{

}

dtkComposerTransmitterReceiverBase::~dtkComposerTransmitterReceiverBase(void)
{

}

dtkComposerTransmitter::Kind dtkComposerTransmitterReceiverBase::kind(void) const
{
    return dtkComposerTransmitter::Receiver;
}

QString dtkComposerTransmitterReceiverBase::kindName(void) const
{
    return "Receiver";
}

bool dtkComposerTransmitterReceiverBase::connect(dtkComposerTransmitter *transmitter)
{
    bool enable_connection = false;

    if (!d->emitters.contains(transmitter)) {

        enable_connection = transmitter->enableConnection(this);

        if (enable_connection) {
            d->emitters << transmitter;
            d->active_emitter = transmitter;
            transmitter->appendReceiver(this);
        }
    }

    return enable_connection;
}

bool dtkComposerTransmitterReceiverBase::disconnect(dtkComposerTransmitter *transmitter)
{
    transmitter->removeReceiver(this);
    bool disable_connection = d->emitters.removeOne(transmitter);

    if (transmitter == d->active_emitter) {
        d->active_emitter = NULL;

        foreach (dtkComposerTransmitter *em, d->emitters) {
            if (em->active()) {
                d->active_emitter = em;
                break;
            }
        }
    }

    return disable_connection;
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterReceiverBase::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    Q_UNUSED(transmitter);

    LinkMap link_map;

    foreach (dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}

// ///////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverVariant implementation
// ///////////////////////////////////////////////////////////////////

dtkComposerTransmitterReceiverVariant::dtkComposerTransmitterReceiverVariant(dtkComposerNode *parent) : dtkComposerTransmitterReceiverBase(parent)
{

}

dtkComposerTransmitterReceiverVariant::~dtkComposerTransmitterReceiverVariant(void)
{

}

//
// dtkComposerTransmitterReceiver.cpp ends here

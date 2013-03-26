/* dtkComposerTransmitterReceiver.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 17:01:02 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Mar 26 13:19:16 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 146
 */

/* Change Log:
 * 
 */

#include "dtkComposerTransmitterReceiver.h"

// ///////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverBase implementation
// ///////////////////////////////////////////////////////////////////

dtkComposerTransmitterReceiverBase::dtkComposerTransmitterReceiverBase(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{

};

dtkComposerTransmitterReceiverBase::~dtkComposerTransmitterReceiverBase(void)
{

};

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

    if (transmitter->kind() == Emitter && !d->emitters.contains(transmitter)) {

	enable_connection = true;

	if (!d->type_list.isEmpty()) {
	    int i = 0; 
	    int count = d->type_list.count();
	    while(enable_connection && i < count) {
		d->variant = QVariant(d->type_list.at(i++), 0);
		foreach(int t, transmitter->typeList()) {
		    if (!d->variant.canConvert(t)) {
			enable_connection = false;
			break;
		    }
		}
	    }
	}

	if (enable_connection) {
	    d->emitters << transmitter;
	    d->active_emitter = transmitter;
	    transmitter->appendReceiver(this);
	}
    }

    return enable_connection;
};

bool dtkComposerTransmitterReceiverBase::disconnect(dtkComposerTransmitter *transmitter)
{
    transmitter->removeReceiver(this);
    bool disable_connection = d->emitters.removeOne(transmitter);

    if (transmitter == d->active_emitter) {
	d->active_emitter = NULL;
	foreach(dtkComposerTransmitter *em, d->emitters) {
	    if (em->active()) {
		d->active_emitter = em;
		break;
	    }
	}
    }

    return disable_connection;
};

// ///////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverVariant implementation
// ///////////////////////////////////////////////////////////////////

dtkComposerTransmitterReceiverVariant::dtkComposerTransmitterReceiverVariant(dtkComposerNode *parent) : dtkComposerTransmitterReceiverBase(parent)
{

};

dtkComposerTransmitterReceiverVariant::~dtkComposerTransmitterReceiverVariant(void)
{

};

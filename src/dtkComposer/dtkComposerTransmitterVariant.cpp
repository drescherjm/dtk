/* dtkComposerTransmitterVariant.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Fri Mar 22 13:22:51 2013 (+0100)
 * Version: 
 * Last-Updated: Sat Mar 23 21:35:48 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 265
 */

/* Change Log:
 * 
 */

#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterVariant.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterVariant::dtkComposerTransmitterVariant(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{

}

dtkComposerTransmitterVariant::~dtkComposerTransmitterVariant(void)
{
}

dtkComposerTransmitter::Kind dtkComposerTransmitterVariant::kind(void) const
{
    return dtkComposerTransmitter::Variant;
}

QString dtkComposerTransmitterVariant::kindName(void) const
{
    return "Variant";
}

bool dtkComposerTransmitterVariant::enableCopy(void)
{
    if (d->active_emitter)
	return d->active_emitter->enableCopy();

    return (d->receivers.count() > 1);
}

QVariant dtkComposerTransmitterVariant::variant(void)
{
    if (d->active_emitter)
	return d->active_emitter->variant();
    
    return d->variant;
}

bool dtkComposerTransmitterVariant::connect(dtkComposerTransmitter *transmitter)
{
    bool enable_connection = false;

    if (!d->emitters.contains(transmitter)) {

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
}

bool dtkComposerTransmitterVariant::disconnect(dtkComposerTransmitter *transmitter)
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
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterVariant::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterVariant::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}


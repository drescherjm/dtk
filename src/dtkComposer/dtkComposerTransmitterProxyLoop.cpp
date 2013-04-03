/* dtkComposerTransmitterProxyLoop.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Fri Mar 29 15:05:13 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Apr  2 09:41:36 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 32
 */

/* Change Log:
 * 
 */

#include "dtkComposerTransmitterProxyLoop.h"

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

dtkComposerTransmitterProxyLoop::dtkComposerTransmitterProxyLoop(dtkComposerNode *parent) : dtkComposerTransmitter(parent), m_source(0), m_twin(0)
{
    
}

dtkComposerTransmitterProxyLoop::~dtkComposerTransmitterProxyLoop(void)
{

}

dtkComposerTransmitter::Kind dtkComposerTransmitterProxyLoop::kind(void) const
{
    return dtkComposerTransmitter::ProxyLoop;
}

QString dtkComposerTransmitterProxyLoop::kindName(void) const
{
    return "ProxyLoop";
}

bool dtkComposerTransmitterProxyLoop::connect(dtkComposerTransmitter *transmitter)
{
    bool enable_connection = false;

    if (!d->emitters.contains(transmitter)) {

	enable_connection = transmitter->enableConnection(this);

	if (enable_connection) {
	    d->emitters << transmitter;
	    d->active_emitter = transmitter;
	    m_source = transmitter;
	    transmitter->appendReceiver(this);
	}
    }

    return enable_connection;
}

bool dtkComposerTransmitterProxyLoop::disconnect(dtkComposerTransmitter *transmitter)
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

bool dtkComposerTransmitterProxyLoop::enableConnection(dtkComposerTransmitter *transmitter)
{
    Q_UNUSED(transmitter);

    return true;
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterProxyLoop::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    Q_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterProxyLoop::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    Q_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}


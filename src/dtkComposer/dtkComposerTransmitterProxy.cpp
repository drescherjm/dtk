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
#include "dtkComposerTransmitterProxy.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterProxy implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterProxy::dtkComposerTransmitterProxy(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{

}

dtkComposerTransmitterProxy::~dtkComposerTransmitterProxy(void)
{

}

//! Returns.
/*! 
 *  
 */
dtkComposerTransmitter::Kind dtkComposerTransmitterProxy::kind(void) const
{
    return dtkComposerTransmitter::Proxy;
}

QString dtkComposerTransmitterProxy::kindName(void) const
{
    return "Proxy";
}

void dtkComposerTransmitterProxy::setActive(bool active)
{
    dtkComposerTransmitter::setActive(active);

    foreach(dtkComposerTransmitter *prev, d->previous_list)
        prev->setActive(active);
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterProxy::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    Q_UNUSED(transmitter);

    LinkMap link_map;

    foreach(dtkComposerTransmitter *p, d->previous_list) {
        list << new dtkComposerTransmitterLink(p, this);
        link_map += p->leftLinks(this, list);
        list.removeLast();
    }

    return link_map;
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterProxy::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    Q_UNUSED(transmitter);

    LinkMap link_map;

    foreach(dtkComposerTransmitter *n, d->next_list) {
        list << new dtkComposerTransmitterLink(this, n);
        link_map += n->rightLinks(this, list);
        list.removeLast();
    }

    return link_map;
}

// 
// dtkComposerTransmitterProxy.cpp ends here

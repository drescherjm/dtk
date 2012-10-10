/* dtkComposerTransmitterProxy.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Feb 20 11:47:39 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Sep 18 16:20:45 2012 (+0200)
 *           By: tkloczko
 *     Update #: 59
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterProxy.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterProxyPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterProxyPrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterProxy implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterProxy::dtkComposerTransmitterProxy(dtkComposerNode *parent) : dtkComposerTransmitter(parent), e(new dtkComposerTransmitterProxyPrivate)
{

}

dtkComposerTransmitterProxy::~dtkComposerTransmitterProxy(void)
{
    delete e;

    e = NULL;
}

int dtkComposerTransmitterProxy::dataType(void)
{
    return 0;
}

QString dtkComposerTransmitterProxy::dataIdentifier(void)
{
    return QString();
}

QString dtkComposerTransmitterProxy::dataDescription(void)
{
    return QString();
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
    LinkMap link_map;

    foreach(dtkComposerTransmitter *n, d->next_list) {
        list << new dtkComposerTransmitterLink(this, n);
        link_map += n->rightLinks(this, list);
        list.removeLast();
    }

    return link_map;
}

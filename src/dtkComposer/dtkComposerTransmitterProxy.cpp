/* dtkComposerTransmitterProxy.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Feb 20 11:47:39 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 23 17:25:41 2012 (+0100)
 *           By: tkloczko
 *     Update #: 34
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitterProxy.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterProxyPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterProxyPrivate
{
public:
    QList<dtkComposerTransmitter *> previous;
    QList<dtkComposerTransmitter *> next;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterProxy implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterProxy::dtkComposerTransmitterProxy(dtkComposerNode *parent) : dtkComposerTransmitter(parent), d(new dtkComposerTransmitterProxyPrivate)
{

}

dtkComposerTransmitterProxy::~dtkComposerTransmitterProxy(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerTransmitterProxy::identifier(void) const
{
    return "dtkComposerTransmitterProxy";
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterProxy::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    LinkMap link_map;

    if (!d->next.contains(transmitter))
        d->next << transmitter;

    foreach(dtkComposerTransmitter *p, d->previous) {
        list << new dtkComposerTransmitterLink(p, this);
        link_map += p->leftLinks(this, list);
        list.removeLast();
    }

    return link_map;
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterProxy::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    LinkMap link_map;

    if (!d->previous.contains(transmitter))
        d->previous << transmitter;

    foreach(dtkComposerTransmitter *n, d->next) {
        list << new dtkComposerTransmitterLink(this, n);
        link_map += n->rightLinks(this, list);
        list.removeLast();
    }

    return link_map;
}

void dtkComposerTransmitterProxy::clear(void)
{
    d->previous.clear();
    d->next.clear();
}

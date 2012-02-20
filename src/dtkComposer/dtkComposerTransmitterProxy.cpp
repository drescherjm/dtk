/* dtkComposerTransmitterProxy.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Feb 20 11:47:39 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 20 17:07:55 2012 (+0100)
 *           By: tkloczko
 *     Update #: 23
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
};

dtkComposerTransmitter::LinkMap dtkComposerTransmitterProxy::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    LinkMap link_map;

    if (!d->next.contains(transmitter))
        d->next << transmitter;

    list << new dtkComposerTransmitterLink(this, transmitter);

    foreach(dtkComposerTransmitter *p, d->previous)
        link_map += p->leftLinks(this, list);

    return link_map;
};

dtkComposerTransmitter::LinkMap dtkComposerTransmitterProxy::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    LinkMap link_map;

    if (!d->previous.contains(transmitter))
        d->previous << transmitter;

    list << new dtkComposerTransmitterLink(transmitter, this);

    foreach(dtkComposerTransmitter *n, d->next)
        link_map += n->rightLinks(this, list);

    return link_map;
};

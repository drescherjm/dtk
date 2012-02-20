/* dtkComposerTransmitterProxy.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Feb 20 11:47:39 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 20 14:45:24 2012 (+0100)
 *           By: tkloczko
 *     Update #: 17
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

dtkComposerTransmitter::Chains dtkComposerTransmitterProxy::leftChains(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    Chains chains;

    list << new dtkComposerTransmitterLink(this, transmitter);

    foreach(dtkComposerTransmitter *p, d->previous)
        chains += p->leftChains(this, list);

    return chains;
};

dtkComposerTransmitter::Chains dtkComposerTransmitterProxy::rightChains(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    Chains chains;

    list << new dtkComposerTransmitterLink(transmitter, this);

    foreach(dtkComposerTransmitter *n, d->next)
        chains += n->rightChains(this, list);

    return chains;
};

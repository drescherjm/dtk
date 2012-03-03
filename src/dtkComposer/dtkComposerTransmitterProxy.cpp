/* dtkComposerTransmitterProxy.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Feb 20 11:47:39 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Mar  3 16:40:01 2012 (+0100)
 *           By: tkloczko
 *     Update #: 47
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
    QString data_type;
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

QString dtkComposerTransmitterProxy::typeName(void) const
{
    return "";
}

//! Returns
/*! 
 *  
 */
void *dtkComposerTransmitterProxy::variant(void)
{
    return (void *)(0);
}

//! Returns
/*! 
 *  
 */
const void *dtkComposerTransmitterProxy::variant(void) const
{
    return (void *)(0);
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterProxy::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    LinkMap link_map;

    foreach(dtkComposerTransmitter *p, this->previousList()) {
        list << new dtkComposerTransmitterLink(p, this);
        link_map += p->leftLinks(this, list);
        list.removeLast();
    }

    return link_map;
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterProxy::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    LinkMap link_map;

    foreach(dtkComposerTransmitter *n, this->nextList()) {
        list << new dtkComposerTransmitterLink(this, n);
        link_map += n->rightLinks(this, list);
        list.removeLast();
    }

    return link_map;
}

/* dtkComposerTransmitterProxy.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Feb 20 11:47:39 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar  4 16:53:08 2012 (+0100)
 *           By: tkloczko
 *     Update #: 48
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

QVariant::Type dtkComposerTransmitterProxy::type(void) const
{
    return QVariant::Invalid;
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

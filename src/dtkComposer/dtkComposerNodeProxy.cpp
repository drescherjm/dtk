/* dtkComposerNodeProxy.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Mar 21 10:28:20 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr  4 09:58:51 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeProxy.h"
#include "dtkComposerTransmitterProxy.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeProxyPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeProxyPrivate
{
public:
    dtkComposerTransmitterProxy receiver;
    dtkComposerTransmitterProxy  emitter;    
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeProxy implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeProxy::dtkComposerNodeProxy(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeProxyPrivate)
{
    this->appendReceiver(&(d->receiver));
    this->appendEmitter(&(d->emitter));    
}

dtkComposerNodeProxy::~dtkComposerNodeProxy(void)
{
    delete d;
    d = NULL;
}

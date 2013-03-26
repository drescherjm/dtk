/* dtkComposerNodeProxy.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Mar 21 10:28:20 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar 26 14:40:56 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 10
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
    dtkComposerTransmitterProxy emitter;    
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

/* dtkComposerNodeProxy.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Mar 21 10:28:20 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 21 10:43:09 2012 (+0100)
 *           By: tkloczko
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeProxy.h"
#include "dtkComposerTransmitterProxy.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeProxyPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeProxyPrivate
{
public:
    dtkComposerTransmitterProxy *receiver;
    dtkComposerTransmitterProxy *emitter;    
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeProxy implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeProxy::dtkComposerNodeProxy(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeProxyPrivate)
{
    d->receiver = new dtkComposerTransmitterProxy(this);
    this->appendReceiver(d->receiver);

    d->emitter = new dtkComposerTransmitterProxy(this);
    this->appendEmitter(d->emitter);    
}

dtkComposerNodeProxy::~dtkComposerNodeProxy(void)
{
    delete d->receiver;
    delete d->emitter;
    delete d;

    d = NULL;
}



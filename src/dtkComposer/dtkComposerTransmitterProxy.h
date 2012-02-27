/* dtkComposerTransmitterProxy.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Feb 20 11:17:31 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 24 09:36:52 2012 (+0100)
 *           By: tkloczko
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERPROXY_H
#define DTKCOMPOSERTRANSMITTERPROXY_H

#include "dtkComposerExport.h"
#include "dtkComposerTransmitter.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterProxy declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterProxyPrivate;

class DTKCOMPOSER_EXPORT dtkComposerTransmitterProxy : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterProxy(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterProxy(void);

public:
    QString identifier(void) const;    

public:
    LinkMap  leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
    LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

private:
    dtkComposerTransmitterProxyPrivate *d;
};

#endif

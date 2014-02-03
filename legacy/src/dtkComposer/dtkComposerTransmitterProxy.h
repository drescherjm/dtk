/* dtkComposerTransmitterProxy.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Feb 20 11:17:31 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. sept. 17 13:58:48 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 33
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
    Kind kind(void) const;

    QString kindName(void) const;

public:
    void setActive(bool active);

public:
    void setReady(bool ready);

public:
    LinkMap  leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
    LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

private:
    dtkComposerTransmitterProxyPrivate *e;
};

#endif

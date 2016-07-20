/* dtkComposerNodeProxy.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Mar 21 10:25:19 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 22 16:04:30 2012 (+0100)
 *           By: tkloczko
 *     Update #: 6
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEPROXY_H
#define DTKCOMPOSERNODEPROXY_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeProxyPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeProxy : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeProxy(void);
    ~dtkComposerNodeProxy(void);

public:
    inline QString type(void) {
        return "proxy";
    }

    inline QString titleHint(void) {
        return "Proxy";
    }

private:
    dtkComposerNodeProxyPrivate *d;
};

#endif

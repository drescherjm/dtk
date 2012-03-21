/* dtkComposerNodeProxy.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Mar 21 10:25:19 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 21 10:28:05 2012 (+0100)
 *           By: tkloczko
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEPROXY_H
#define DTKCOMPOSERNODEPROXY_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeProxyPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeProxy : public dtkComposerNodeLeaf
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

    inline QString inputLabelHint(int) {
        return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

private:
    dtkComposerNodeProxyPrivate *d;
};

#endif

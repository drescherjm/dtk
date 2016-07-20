/* dtkComposerNodeProxy.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Mar 21 10:25:19 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr  4 09:59:34 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 8
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeProxyPrivate;

class  dtkComposerNodeProxy : public dtkComposerNodeLeaf
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


/* @(#)dtkComposerGraphNodeBegin.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: mar. févr. 14 16:33:30 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 18
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODEBEGIN_H
#define DTKCOMPOSERGRAPHNODEBEGIN_H

#include "dtkComposerGraphNode.h"

class dtkComposerGraphNodeBeginPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeBegin
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeBegin : public dtkComposerGraphNode
{

public:
    void eval(void);

private:

    dtkComposerGraphNodeBeginPrivate *d;
};


#endif /* DTKCOMPOSERGRAPHNODEBEGIN_H */


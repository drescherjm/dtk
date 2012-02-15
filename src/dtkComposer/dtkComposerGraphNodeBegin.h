/* @(#)dtkComposerGraphNodeBegin.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: mer. févr. 15 16:09:14 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 33
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

class dtkComposerNode;
class dtkComposerGraphNodeBeginPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeBegin
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeBegin : public dtkComposerGraphNode
{
public:
     dtkComposerGraphNodeBegin(dtkComposerNode *node);

public:
    void eval(void);

private:
    dtkComposerGraphNodeBeginPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODEBEGIN_H */


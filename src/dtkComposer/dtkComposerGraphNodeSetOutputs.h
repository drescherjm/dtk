/* @(#)dtkComposerGraphNodeSetOutputs.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: mer. févr. 15 09:56:02 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 29
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODESETOUTPUTS_H
#define DTKCOMPOSERGRAPHNODESETOUTPUTS_H

#include "dtkComposerGraphNode.h"
#include "dtkComposerNode.h"

class dtkComposerGraphNodeSetOutputsPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeSetOutputs
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeSetOutputs : public dtkComposerGraphNode
{
public:
     dtkComposerGraphNodeSetOutputs(dtkComposerNode *node);

public:
    void eval(void);

private:
    dtkComposerGraphNodeSetOutputsPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODESETOUTPUTS_H */


/* @(#)dtkComposerGraphNodeSetOutputs.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: ven. mars  2 18:38:13 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 36
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

class dtkComposerNode;
class dtkComposerGraphNodeSetOutputsPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeSetOutputs
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeSetOutputs : public dtkComposerGraphNode
{
public:
    dtkComposerGraphNodeSetOutputs(dtkComposerNode *node, const QString& title = "Set Outputs");

public:
    void eval(void);

public:
    dtkComposerGraphNode::Kind kind(void);

public:
    dtkComposerNode *wrapee(void);

private:
    dtkComposerGraphNodeSetOutputsPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODESETOUTPUTS_H */


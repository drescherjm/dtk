/* @(#)dtkComposerGraphNodeSetInputs.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: ven. mars  2 18:38:09 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 34
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODESETINPUTS_H
#define DTKCOMPOSERGRAPHNODESETINPUTS_H

#include "dtkComposerGraphNode.h"

class dtkComposerNode;
class dtkComposerGraphNodeSetInputsPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeSetInputs
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeSetInputs : public dtkComposerGraphNode
{
public:
    dtkComposerGraphNodeSetInputs(dtkComposerNode *node, const QString& title = "Set Inputs");

public:
    void eval(void);

public:
    dtkComposerGraphNode::Kind kind(void);

public:
    dtkComposerNode *wrapee(void);

private:
    dtkComposerGraphNodeSetInputsPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODESETINPUTS_H */


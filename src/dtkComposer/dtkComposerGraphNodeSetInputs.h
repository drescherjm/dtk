/* @(#)dtkComposerGraphNodeSetInputs.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: mer. févr. 15 16:10:52 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 31
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
     dtkComposerGraphNodeSetInputs(dtkComposerNode *node);

public:
    void eval(void);

private:
    dtkComposerGraphNodeSetInputsPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODESETINPUTS_H */


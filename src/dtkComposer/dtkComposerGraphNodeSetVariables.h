/* @(#)dtkComposerGraphNodeSetVariables.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: mer. févr. 15 09:56:20 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 30
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODESETVARIABLES_H
#define DTKCOMPOSERGRAPHNODESETVARIABLES_H

#include "dtkComposerGraphNode.h"
#include "dtkComposerNode.h"

class dtkComposerGraphNodeSetVariablesPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeSetVariables
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeSetVariables : public dtkComposerGraphNode
{
public:
     dtkComposerGraphNodeSetVariables(dtkComposerNode *node);

public:
    void eval(void);

private:
    dtkComposerGraphNodeSetVariablesPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODESETVARIABLES_H */


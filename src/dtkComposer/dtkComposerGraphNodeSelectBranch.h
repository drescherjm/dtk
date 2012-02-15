/* @(#)dtkComposerGraphNodeSelectBranch.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: mer. févr. 15 09:55:20 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 29
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODESELECTBRANCH_H
#define DTKCOMPOSERGRAPHNODESELECTBRANCH_H

#include "dtkComposerGraphNode.h"
#include "dtkComposerNode.h"

class dtkComposerGraphNodeSelectBranchPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeSelectBranch
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeSelectBranch : public dtkComposerGraphNode
{
public:
     dtkComposerGraphNodeSelectBranch(dtkComposerNode *node);

public:
    void eval(void);

private:
    dtkComposerGraphNodeSelectBranchPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODESELECTBRANCH_H */


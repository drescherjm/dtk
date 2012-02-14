/* @(#)dtkComposerGraphNodeSelectBranch.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: mar. févr. 14 15:01:30 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 17
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

class dtkComposerGraphNodeSelectBranchPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeSelectBranch
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeSelectBranch : public dtkComposerGraphNode
{

public:
    void eval(void);

private:

    dtkComposerGraphNodeSelectBranchPrivate *d;
}


#endif /* DTKCOMPOSERGRAPHNODESELECTBRANCH_H */


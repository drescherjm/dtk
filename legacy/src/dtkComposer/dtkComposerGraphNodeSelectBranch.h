/* @(#)dtkComposerGraphNodeSelectBranch.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: jeu. sept. 12 10:23:43 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 42
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

class dtkComposerNode;
class dtkComposerGraphNodeSelectBranchPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeSelectBranch
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeSelectBranch : public dtkComposerGraphNode
{
public:
     dtkComposerGraphNodeSelectBranch(dtkComposerNode *node, const QString& title = "Select Branch");

public:
    dtkComposerGraphNode::Kind kind(void);

public:
     void addSuccessor(dtkComposerGraphNode *node, int id = 0);

public:
     void removeSuccessor(dtkComposerGraphNode *node);

public:
     dtkComposerGraphNodeList successors();
     dtkComposerGraphNode *firstSuccessor();

public:
    void eval(void);

public:
    void clean(void);

public:
    dtkComposerNode *wrapee(void);

private:
    dtkComposerGraphNodeSelectBranchPrivate *d;
};

#endif /* DTKCOMPOSERGRAPHNODESELECTBRANCH_H */


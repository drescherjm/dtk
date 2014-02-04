/* @(#)dtkComposerGraphNodeSelectBranch.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:55:56
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:27:07 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 39
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

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

public:
    void eval(void);

public:
    void clean(void);

public:
    dtkComposerNode *wrapee(void);

private:
    dtkComposerGraphNodeSelectBranchPrivate *d;
};



/* @(#)dtkComposerGraphNodeSelectBranch.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mar. févr. 14 15:39:55 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 32
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSelectBranch.h"

class dtkComposerGraphNodeSelectBranchPrivate
{
public:
    dtkComposerControlNode *composer_node;

};


dtkComposerGraphNodeSelectBranch::dtkComposerGraphNodeSelectBranch(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSelectBranchPrivate)
{
    d->composerNode = dynamic_cast<dtkComposerControlNode *>(cnode);
}



void dtkComposerGraphNodeSelectBranch::eval(void)
{
    if (this->composerNode() == NULL)
        return;

    this->composerNode()->selectBranch();
}



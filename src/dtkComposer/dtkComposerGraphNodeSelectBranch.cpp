/* @(#)dtkComposerGraphNodeSelectBranch.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: jeu. févr. 16 10:57:12 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 55
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSelectBranch.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"

class dtkComposerGraphNodeSelectBranchPrivate
{
public:
    dtkComposerNodeControl *composer_node;

};


dtkComposerGraphNodeSelectBranch::dtkComposerGraphNodeSelectBranch(dtkComposerNode *cnode) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSelectBranchPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
}



void dtkComposerGraphNodeSelectBranch::eval(void)
{
    if (d->composer_node == NULL)
        return;

    int branch = d->composer_node->selectBranch();

    //TODO: send the result to the evaluator.
}



/* @(#)dtkComposerGraphNodeSelectBranch.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: lun. févr. 20 10:37:10 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 57
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


dtkComposerGraphNodeSelectBranch::dtkComposerGraphNodeSelectBranch(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSelectBranchPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
    this->setTitle(title);
}



void dtkComposerGraphNodeSelectBranch::eval(void)
{
    if (d->composer_node == NULL)
        return;

    int branch = d->composer_node->selectBranch();

    //TODO: send the result to the evaluator.
}



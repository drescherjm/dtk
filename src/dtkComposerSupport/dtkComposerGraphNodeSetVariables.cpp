/* @(#)dtkComposerGraphNodeSetVariables.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: ven. mars  2 18:43:17 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 50
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSetVariables.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"

class dtkComposerGraphNodeSetVariablesPrivate
{
public:
    dtkComposerNodeControl *composer_node;

};


dtkComposerGraphNodeSetVariables::dtkComposerGraphNodeSetVariables(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(), d(new dtkComposerGraphNodeSetVariablesPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
    this->setTitle(title);
}

dtkComposerGraphNode::Kind dtkComposerGraphNodeSetVariables::kind(void)
{
    return dtkComposerGraphNode::SetVariables;
}

dtkComposerNode *dtkComposerGraphNodeSetVariables::wrapee(void)
{
    return d->composer_node;
}

void dtkComposerGraphNodeSetVariables::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->setVariables();
    this->setStatus(dtkComposerGraphNode::Done);
}



/* @(#)dtkComposerGraphNodeSetInputs.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: ven. mars  2 18:43:04 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 51
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSetInputs.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"

class dtkComposerGraphNodeSetInputsPrivate
{
public:
    dtkComposerNodeControl *composer_node;

};


dtkComposerGraphNodeSetInputs::dtkComposerGraphNodeSetInputs(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(), d(new dtkComposerGraphNodeSetInputsPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
    this->setTitle(title);
}


dtkComposerGraphNode::Kind dtkComposerGraphNodeSetInputs::kind(void)
{
    return dtkComposerGraphNode::SetInputs;
}

dtkComposerNode *dtkComposerGraphNodeSetInputs::wrapee(void)
{
    return d->composer_node;
}

void dtkComposerGraphNodeSetInputs::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->setInputs();
    this->setStatus(dtkComposerGraphNode::Done);
}



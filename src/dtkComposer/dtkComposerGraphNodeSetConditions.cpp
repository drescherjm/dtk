/* @(#)dtkComposerGraphNodeSetConditions.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: ven. mars  2 18:42:41 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 53
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeSetConditions.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"

class dtkComposerGraphNodeSetConditionsPrivate
{
public:
    dtkComposerNodeControl *composer_node;

};


dtkComposerGraphNodeSetConditions::dtkComposerGraphNodeSetConditions(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeSetConditionsPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
    this->setTitle(title);
}

dtkComposerGraphNode::Kind dtkComposerGraphNodeSetConditions::kind(void)
{
    return dtkComposerGraphNode::SetConditions;
}

dtkComposerNode *dtkComposerGraphNodeSetConditions::wrapee(void)
{
    return d->composer_node;
}

void dtkComposerGraphNodeSetConditions::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->setConditions();
    this->setStatus(dtkComposerGraphNode::Done);
}



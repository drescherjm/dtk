/* @(#)dtkComposerGraphNodeLeaf.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: ven. mars  2 18:42:15 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 58
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeLeaf.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerGraphNodeLeafPrivate
{
public:
    dtkComposerNodeLeaf *composer_node;

};


dtkComposerGraphNodeLeaf::dtkComposerGraphNodeLeaf(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeLeafPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeLeaf *>(cnode);
    this->setTitle(title);
}

dtkComposerGraphNode::Kind dtkComposerGraphNodeLeaf::kind(void)
{
    return dtkComposerGraphNode::Leaf;
}

dtkComposerNode *dtkComposerGraphNodeLeaf::wrapee(void)
{
    return d->composer_node;
}

void dtkComposerGraphNodeLeaf::eval(void)
{
    if (d->composer_node == NULL)
        return;

    d->composer_node->run();
    this->setStatus(dtkComposerGraphNode::Done);
}



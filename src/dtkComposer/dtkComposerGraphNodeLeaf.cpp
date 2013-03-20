/* @(#)dtkComposerGraphNodeLeaf.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: ven. sept. 21 10:03:14 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 72
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
#include "dtkComposerNodeLeafData.h"
#include "dtkComposerNodeLeafProcess.h"
#include "dtkComposerNodeLeafView.h"

class dtkComposerGraphNodeLeafPrivate
{
public:
    dtkComposerNodeLeaf *composer_node;

public:
    dtkComposerGraphNode::Kind kind;

};


dtkComposerGraphNodeLeaf::dtkComposerGraphNodeLeaf(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeLeafPrivate)
{
    d->composer_node = dynamic_cast<dtkComposerNodeLeaf *>(cnode);
    if (dynamic_cast<dtkComposerNodeLeafProcess *>(cnode))
        d->kind = dtkComposerGraphNode::Process;
    else if (dynamic_cast<dtkComposerNodeLeafView *>(cnode))
        d->kind = dtkComposerGraphNode::View;
    else if (dynamic_cast<dtkComposerNodeLeafData *>(cnode))
        d->kind = dtkComposerGraphNode::Data;
    else
        d->kind = dtkComposerGraphNode::Leaf;

    this->setTitle(title);
}

dtkComposerGraphNode::Kind dtkComposerGraphNodeLeaf::kind(void)
{
    return d->kind;
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



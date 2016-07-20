/* @(#)dtkComposerGraphNodeLeaf.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
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
#include "dtkComposerNodeMetaData.h"
// #include "dtkComposerNodeLeafData.h"
// #include "dtkComposerNodeLeafProcess.h"
// #include "dtkComposerNodeLeafView.h"
// #include "dtkComposerNodeLeafActor.h"

class dtkComposerGraphNodeLeafPrivate
{
public:
    dtkComposerNodeLeaf *composer_node;

public:
    dtkComposerGraphNode::Kind kind;

};


dtkComposerGraphNodeLeaf::dtkComposerGraphNodeLeaf(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(), d(new dtkComposerGraphNodeLeafPrivate)
{
    dtkComposerNodeMetaData *metaData = cnode->nodeMetaData();

    if (metaData != NULL && metaData->kind() == dtkComposerNode::View)
        d->kind = dtkComposerGraphNode::View;
    else
        d->kind = dtkComposerGraphNode::Leaf;

    d->composer_node = dynamic_cast<dtkComposerNodeLeaf *>(cnode);

    // if (dynamic_cast<dtkComposerNodeLeafProcess *>(cnode))
    //     d->kind = dtkComposerGraphNode::Process;
    // else if (dynamic_cast<dtkComposerNodeLeafView *>(cnode))
    //     d->kind = dtkComposerGraphNode::View;
    // else if (dynamic_cast<dtkComposerNodeLeafData *>(cnode))
    //     d->kind = dtkComposerGraphNode::Data;
    // else if (dynamic_cast<dtkComposerNodeLeafActor *>(cnode))
    //     d->kind = dtkComposerGraphNode::Actor;
    // else
    //d->kind = dtkComposerGraphNode::Leaf;

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



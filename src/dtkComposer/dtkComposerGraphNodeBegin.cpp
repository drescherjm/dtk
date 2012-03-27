/* @(#)dtkComposerGraphNodeBegin.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mar. mars 27 15:46:38 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 220
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeBegin.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeComposite.h"

#include <dtkLog/dtkLog.h>

class dtkComposerGraphNodeBeginPrivate
{
public:
    dtkComposerNodeControl *control_node;
    dtkComposerNodeComposite   *composite;
};


dtkComposerGraphNodeBegin::dtkComposerGraphNodeBegin(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeBeginPrivate)
{

    if (!dynamic_cast<dtkComposerNodeControl *>(cnode)) {
        d->composite = dynamic_cast<dtkComposerNodeComposite *>(cnode);
        d->control_node = NULL;
    } else {
        d->control_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
        d->composite = NULL;
    }

    this->setTitle(title);
}

dtkComposerGraphNode::Kind dtkComposerGraphNodeBegin::kind(void)
{
    return dtkComposerGraphNode::Begin;
}

dtkComposerNode *dtkComposerGraphNodeBegin::wrapee(void)
{
    if (!d->control_node)
        return d->composite;
    else
        return d->control_node;
}

void dtkComposerGraphNodeBegin::eval(void)
{

    if (!d->control_node) {
        this->setStatus(dtkComposerGraphNode::Done);
    } else {
        d->control_node->begin();
        this->setStatus(dtkComposerGraphNode::Done);
    }

    //TODO: build childs list during graph creation

    // need to clean state of all nodes in the composite/group
    dtkComposerGraphNodeList childs = this->successors();
    while (!childs.isEmpty()) {
        dtkComposerGraphNode *current = childs.takeFirst();
        if (current->status() == dtkComposerGraphNode::Done && !(( current->wrapee() == d->control_node || current->wrapee() == d->composite ) && current->kind() ==  dtkComposerGraphNode::End)) {
            childs << current->successors();
        }
        current->setStatus(dtkComposerGraphNode::Ready);
    }
}



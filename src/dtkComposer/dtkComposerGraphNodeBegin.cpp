/* @(#)dtkComposerGraphNodeBegin.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: ven. mars  2 18:41:52 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 112
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

class dtkComposerGraphNodeBeginPrivate
{
public:
    dtkComposerNodeControl *composer_node;
    dtkComposerNodeComposite   *composite;
};


dtkComposerGraphNodeBegin::dtkComposerGraphNodeBegin(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeBeginPrivate)
{

    if (!dynamic_cast<dtkComposerNodeControl *>(cnode)) {
        d->composite = dynamic_cast<dtkComposerNodeComposite *>(cnode);
        d->composer_node = NULL;
    } else {
        d->composer_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
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
    if (!d->composer_node)
        return d->composite;
    else
        return d->composer_node;
}

void dtkComposerGraphNodeBegin::eval(void)
{
    if (!d->composer_node) {
        this->setStatus(dtkComposerGraphNode::Done);
        return;
    }

    d->composer_node->end();
    this->setStatus(dtkComposerGraphNode::Done);
}



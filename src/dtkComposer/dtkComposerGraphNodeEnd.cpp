/* @(#)dtkComposerGraphNodeEnd.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mar. mars 27 12:58:47 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 157
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerGraphNodeEnd.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeComposite.h"

class dtkComposerGraphNodeEndPrivate
{
public:
    dtkComposerNodeControl   *control_node;
    dtkComposerNodeComposite     *composite;
};


dtkComposerGraphNodeEnd::dtkComposerGraphNodeEnd(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeEndPrivate)
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

dtkComposerGraphNode::Kind dtkComposerGraphNodeEnd::kind(void)
{
    return dtkComposerGraphNode::End;
}

dtkComposerNode *dtkComposerGraphNodeEnd::wrapee(void)
{
    if (!d->control_node)
        return d->composite;
    else
        return d->control_node;
}

void dtkComposerGraphNodeEnd::eval(void)
{
    if (!d->control_node) { // composite node end
        this->setStatus(dtkComposerGraphNode::Done);

    } else {
        d->control_node->end();
        this->setStatus(dtkComposerGraphNode::Done);
    }
}



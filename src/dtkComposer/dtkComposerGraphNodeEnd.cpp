/* @(#)dtkComposerGraphNodeEnd.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: ven. mars  2 18:57:59 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 151
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
    dtkComposerNodeControl   *composer_node;
    dtkComposerNodeComposite     *composite;
};


dtkComposerGraphNodeEnd::dtkComposerGraphNodeEnd(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeEndPrivate)
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

dtkComposerGraphNode::Kind dtkComposerGraphNodeEnd::kind(void)
{
    return dtkComposerGraphNode::End;
}

dtkComposerNode *dtkComposerGraphNodeEnd::wrapee(void)
{
    if (!d->composer_node)
        return d->composite;
    else
        return d->composer_node;
}

void dtkComposerGraphNodeEnd::eval(void)
{
    if (!d->composer_node) { // composite node end
        this->setStatus(dtkComposerGraphNode::Done);

    } else { //control node end
        d->composer_node->end();
        this->setStatus(dtkComposerGraphNode::Done);
    }
}



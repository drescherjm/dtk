/* @(#)dtkComposerGraphNodeBegin.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mar. avril  3 16:36:08 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 262
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

    if (!d->control_node  ) {
        if (d->composite)// may be NULL for root node
            d->composite->begin();
        this->setStatus(dtkComposerGraphNode::Done);
    } else {
        d->control_node->begin();
        this->setStatus(dtkComposerGraphNode::Done);
    }

    dtkComposerGraphNodeList childs = this->childs();
    int count = childs.count();

    for (int i = 0; i < count; i++) {
        childs.at(i)->clean();
    }
}



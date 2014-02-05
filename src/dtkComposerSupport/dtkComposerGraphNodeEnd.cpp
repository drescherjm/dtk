/* @(#)dtkComposerGraphNodeEnd.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:21:27 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 234
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkConfig.h>

#include "dtkComposerGraphNode.h"
#include "dtkComposerGraphNodeBegin.h"
#include "dtkComposerGraphNodeEnd.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeComposite.h"
#if defined(DTK_BUILD_DISTRIBUTED_SUPPORT)
#include "dtkComposerNodeRemote.h"
#endif

#include <dtkLog/dtkLogger.h>

class dtkComposerGraphNodeEndPrivate
{
public:
    dtkComposerNodeControl *control_node;
    dtkComposerNodeComposite *composite;

public:
    bool is_remote;

#if defined(DTK_BUILD_DISTRIBUTED_SUPPORT)
public:
    dtkComposerNodeRemote *remote;
#endif

public:
    dtkComposerGraphNodeBegin *begin;

};


dtkComposerGraphNodeEnd::dtkComposerGraphNodeEnd(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeEndPrivate)
{
    d->is_remote = false;
    if (!dynamic_cast<dtkComposerNodeControl *>(cnode)) {
#if defined(DTK_BUILD_DISTRIBUTED_SUPPORT)
        if (dtkComposerNodeRemote *remote = dynamic_cast<dtkComposerNodeRemote *>(cnode)) {
            d->is_remote = true;
            d->remote = remote ;
            //We can't call isSlave() now
        }
#endif
        d->composite = dynamic_cast<dtkComposerNodeComposite *>(cnode);
        d->control_node = NULL;
    } else {
        d->control_node = dynamic_cast<dtkComposerNodeControl *>(cnode);
        d->composite = NULL;
    }

    d->begin= NULL;
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
        if (d->composite)// may be NULL for root node
            d->composite->end();
    } else
        d->control_node->end();

    this->setStatus(dtkComposerGraphNode::Done);
}

void dtkComposerGraphNodeEnd::setBegin(dtkComposerGraphNodeBegin *begin)
{
    d->begin = begin;
}

dtkComposerGraphNodeList dtkComposerGraphNodeEnd::predecessors(void)
{
#if defined(DTK_BUILD_DISTRIBUTED_SUPPORT)
    if (d->is_remote && !d->remote->isSlave()) {
        dtkDebug() << "we are running the end statement of a remote node on a controller, predecessor is only the begin statement";
        dtkComposerGraphNodeList list;
        list << d->begin;
        return list;
    } else {
        return dtkComposerGraphNode::predecessors();
    }
#else
    return dtkComposerGraphNode::predecessors();
#endif
}

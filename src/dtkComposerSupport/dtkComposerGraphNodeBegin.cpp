/* @(#)dtkComposerGraphNodeBegin.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/02/14 13:59:57
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:21:17 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 392
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkConfig.h>

#include "dtkComposerGraph.h"
#include "dtkComposerGraphNodeBegin.h"
#include "dtkComposerGraphNode.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeComposite.h"
#if defined(DTK_BUILD_DISTRIBUTED_SUPPORT)
#include "dtkComposerNodeRemote.h"
#endif

#include <dtkLog/dtkLogger.h>
#include <dtkMathSupport/dtkGraph.h>

class dtkComposerGraphNodeBeginPrivate
{
public:
    dtkComposerNodeControl *control_node;
    dtkComposerNodeComposite *composite;
    dtkComposerGraphNodeList allchilds;

    dtkComposerGraphNode::Kind kind;

public:
    bool is_remote;

#if defined(DTK_BUILD_DISTRIBUTED_SUPPORT)
public:
    dtkComposerNodeRemote *remote;
#endif

public:
    dtkComposerGraphNode *end;
};


dtkComposerGraphNodeBegin::dtkComposerGraphNodeBegin(dtkComposerNode *cnode, const QString& title) : dtkComposerGraphNode(),d(new dtkComposerGraphNodeBeginPrivate)
{
    d->is_remote = false;
    d->kind = dtkComposerGraphNode::Begin;
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

    this->setTitle(title);
}

dtkComposerGraphNode::Kind dtkComposerGraphNodeBegin::kind(void)
{
    return d->kind ;
}

void dtkComposerGraphNodeBegin::setKind(dtkComposerGraphNode::Kind kind)
{
    d->kind = kind;
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
    } else
        d->control_node->begin();

    this->setStatus(dtkComposerGraphNode::Done);

    dtkComposerGraphNodeList childs = this->childs();
    dtkComposerGraphNodeList::const_iterator it;

    for (it = childs.constBegin(); it != childs.constEnd(); ++it)
        (*it)->clean();

}

void dtkComposerGraphNodeBegin::setEnd(dtkComposerGraphNode *end)
{
    d->end = end;
}

dtkComposerGraphNodeList dtkComposerGraphNodeBegin::evaluableChilds(void)
{
    if (d->allchilds.isEmpty()) {
        dtkGraph sg = this->graph()->subgraph(this, d->end);
        QList<QObject*> L = (d->kind ==  dtkComposerGraphNode::BeginIf) ? sg.nodes(): sg.topologicalSort();
        foreach (QObject * o,L) {
            d->allchilds << static_cast<dtkComposerGraphNode *>(o);
        }
    }
    return d->allchilds;
}

dtkComposerGraphNode *dtkComposerGraphNodeBegin::end(void)
{
    return d->end;
}

dtkComposerGraphNodeList dtkComposerGraphNodeBegin::successors(void)
{
#if defined(DTK_BUILD_DISTRIBUTED_SUPPORT)
    if (d->is_remote && !d->remote->isSlave()) {
        dtkDebug() << "we are running the begin statement of a remote node on a controller, successor is only the end statement";
        dtkComposerGraphNodeList list;
        list << d->end;
        return list;
    } else {
        return dtkComposerGraphNode::successors();
    }
#else
    return dtkComposerGraphNode::successors();
#endif
}


/* dtkComposerGraphNode.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:09:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 20 14:43:57 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 231
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerGraph.h"
#include "dtkComposerGraphEdge.h"
#include "dtkComposerGraphNode.h"

class dtkComposerGraphNodePrivate
{
public:
    QString title;

public:
    dtkComposerGraphNodeList successors;
    dtkComposerGraphNodeList predecessors;
    dtkComposerGraphNodeList childs;

public:
    dtkComposerGraphNode::Status status;

public:
    dtkComposerGraph *graph;

public:
    bool breakpoint;
    bool endloop_initial;
    bool endloop;

public:
    static int count;
};

int dtkComposerGraphNodePrivate::count = 0;

dtkComposerGraphNode::dtkComposerGraphNode() : QObject(), d(new dtkComposerGraphNodePrivate)
{
    this->setStatus(dtkComposerGraphNode::Ready);
    d->breakpoint      = false;
    d->endloop         = false;
    d->endloop_initial = false;
    d->graph           = NULL;
    d->count++;
}

dtkComposerGraphNode::~dtkComposerGraphNode(void)
{
    delete d;

    d = NULL;
}

dtkComposerNode *dtkComposerGraphNode::wrapee(void)
{
    return NULL;
}


dtkComposerGraphNode::Status dtkComposerGraphNode::status(void)
{
    return d->status;
}

dtkComposerGraph *dtkComposerGraphNode::graph(void)
{
    return d->graph;
}

void dtkComposerGraphNode::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
}

void dtkComposerGraphNode::setStatus(dtkComposerGraphNode::Status status)
{
    d->status = status;
}

bool dtkComposerGraphNode::breakpoint(void)
{
    return d->breakpoint;
}

bool dtkComposerGraphNode::endloop(void)
{
    return d->endloop;
}

void dtkComposerGraphNode::setBreakPoint(bool value)
{
    d->breakpoint = value;
}

void dtkComposerGraphNode::setEndLoop(bool value)
{
    d->endloop = value;

    if (value) // endloop is set to true, keep this info in endloop_initial (used to rerun node)
        d->endloop_initial = value;
}

void dtkComposerGraphNode::addSuccessor(dtkComposerGraphNode *node, int id)
{
    d->successors << node;
}

void dtkComposerGraphNode::addChild(dtkComposerGraphNode *node)
{
    d->childs << node;
}

void dtkComposerGraphNode::addPredecessor(dtkComposerGraphNode *node)
{
    d->predecessors << node;
}

void dtkComposerGraphNode::removeChild(dtkComposerGraphNode *node)
{
    d->childs.removeOne(node);
}

void dtkComposerGraphNode::removePredecessor(dtkComposerGraphNode *node)
{
    d->predecessors.removeOne(node);
}

void dtkComposerGraphNode::removeSuccessor(dtkComposerGraphNode *node)
{
    d->successors.removeOne(node);
}

dtkComposerGraphNodeList dtkComposerGraphNode::successors(void)
{
    return d->successors;
}

dtkComposerGraphNode *dtkComposerGraphNode::firstSuccessor(void)
{
    return d->successors[0];
}

dtkComposerGraphNodeList dtkComposerGraphNode::predecessors(void)
{
    return d->predecessors;
}

dtkComposerGraphNodeList dtkComposerGraphNode::childs(void)
{
    return d->childs;
}

dtkComposerGraphNodeList dtkComposerGraphNode::evaluableChilds(void)
{
    return d->childs;
}


const QString& dtkComposerGraphNode::title(void)
{
    return d->title;
}

void dtkComposerGraphNode::setTitle(const QString& title)
{
    d->title = title;
    // set unique object name
    QString id = QString::number(d->count);
    id.prepend("_");
    id.prepend(title);
    id.replace(" ", "_");
    this->setObjectName(id);
}

void dtkComposerGraphNode::eval(void)
{

}

void dtkComposerGraphNode::clean(void)
{
    this->setStatus(dtkComposerGraphNode::Ready);
    d->endloop = d->endloop_initial;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeList
// /////////////////////////////////////////////////////////////////

dtkComposerGraphNodeList::dtkComposerGraphNodeList(void) : QList<dtkComposerGraphNode * >()
{

}

dtkComposerGraphNodeList::dtkComposerGraphNodeList(const QList<dtkComposerGraphNode *>& other) : QList<dtkComposerGraphNode * >(other)
{

}

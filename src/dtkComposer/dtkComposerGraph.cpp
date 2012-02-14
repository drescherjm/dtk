/* dtkComposerGraph.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:43:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Feb 11 12:39:14 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 218
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerGraph.h"
#include "dtkComposerGraphEdge.h"
#include "dtkComposerGraphLayouter.h"
#include "dtkComposerGraphNode.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerScenePort.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphPrivate
{
public:
    bool exists(dtkComposerSceneEdge *edge);

public:
    QHash<dtkComposerSceneEdge *, dtkComposerGraphEdge *> edges;
    QHash<dtkComposerSceneNode *, dtkComposerGraphNode *> nodes;
};

bool dtkComposerGraphPrivate::exists(dtkComposerSceneEdge *edge)
{
    dtkComposerGraphNode *s = this->nodes.value(edge->source()->node());
    dtkComposerGraphNode *d = this->nodes.value(edge->destination()->node());

    foreach(dtkComposerGraphEdge *e, this->edges)
        if(e->source() == s && e->destination() == d)
            return true;

    return false;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerGraph
// /////////////////////////////////////////////////////////////////

dtkComposerGraph::dtkComposerGraph(void) : QGraphicsScene(), d(new dtkComposerGraphPrivate)
{
    this->connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
}

dtkComposerGraph::dtkComposerGraph(const dtkComposerGraph& other) : QGraphicsScene(), d(new dtkComposerGraphPrivate)
{
    d->edges = QHash<dtkComposerSceneEdge *, dtkComposerGraphEdge *>(other.d->edges);
    d->nodes = QHash<dtkComposerSceneNode *, dtkComposerGraphNode *>(other.d->nodes);

    this->connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
}

dtkComposerGraph::~dtkComposerGraph(void)
{
    delete d;

    d = NULL;
}

void dtkComposerGraph::addNode(dtkComposerSceneNode *node)
{
    dtkComposerGraphNode *n = new dtkComposerGraphNode;
    
    d->nodes.insert(node, n);

    this->addItem(n);

    this->layout();
}

void dtkComposerGraph::removeNode(dtkComposerSceneNode *node)
{
    dtkComposerGraphNode *n = d->nodes.value(node);
    
    d->nodes.remove(node);

    this->removeItem(n);

    this->layout();
}

void dtkComposerGraph::addEdge(dtkComposerSceneEdge *edge)
{
    if(!d->nodes.contains(edge->source()->node()))
        return;
    
    if(!d->nodes.contains(edge->destination()->node()))
        return;

    if(d->exists(edge))
        return;

    dtkComposerGraphEdge *e = new dtkComposerGraphEdge;
    e->setSource(d->nodes.value(edge->source()->node()));
    e->setDestination(d->nodes.value(edge->destination()->node()));
    
    d->edges.insert(edge, e);

    this->addItem(e);

    this->layout();
}

void dtkComposerGraph::removeEdge(dtkComposerSceneEdge *edge)
{
    if(!d->edges.contains(edge))
        return;

    dtkComposerGraphEdge *e = d->edges.value(edge);
    
    d->edges.remove(edge);

    this->removeItem(e);

    this->layout();
}

dtkComposerGraphEdgeList dtkComposerGraph::edges(void)
{
    return dtkComposerGraphEdgeList(d->edges.values());
}

dtkComposerGraphNodeList dtkComposerGraph::nodes(void)
{
    return dtkComposerGraphNodeList(d->nodes.values());
}

void dtkComposerGraph::layout(void)
{
    dtkComposerGraphLayouter layouter;
    layouter.setGraph(this);
    layouter.layout();

    this->update();
}

void dtkComposerGraph::onSelectionChanged(void)
{
    QList<QGraphicsItem *> selection = this->selectedItems();

    if(selection.count() != 1)
        return;

    dtkComposerGraphNode *node = dynamic_cast<dtkComposerGraphNode *>(selection.first());

    if(!node)
        return;

    dtkComposerSceneNode *n = d->nodes.key(node);

    if (n)
        n->setSelected(true);
}

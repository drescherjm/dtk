/* dtkComposerGraph.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:43:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  9 16:32:31 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 127
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
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"

class dtkComposerGraphPrivate
{
public:
    QHash<dtkComposerSceneEdge *, dtkComposerGraphEdge *> edges;
    QHash<dtkComposerSceneNode *, dtkComposerGraphNode *> nodes;
};

dtkComposerGraph::dtkComposerGraph(void) : QGraphicsScene(),d(new dtkComposerGraphPrivate)
{
    // dtkComposerGraphNode *n1 = new dtkComposerGraphNode;
    // n1->setPos(-100, 0);

    // dtkComposerGraphNode *n2 = new dtkComposerGraphNode;
    // n2->setPos(100, 0);

    // dtkComposerGraphNode *n3 = new dtkComposerGraphNode;
    // n3->setPos(0, 200);

    // dtkComposerGraphEdge *e1 = new dtkComposerGraphEdge;
    // e1->setSource(n1);
    // e1->setDestination(n3);

    // dtkComposerGraphEdge *e2 = new dtkComposerGraphEdge;
    // e2->setSource(n2);
    // e2->setDestination(n3);

    // this->addNode(n1);
    // this->addNode(n2);
    // this->addNode(n3);
    // this->addEdge(e1);
    // this->addEdge(e2);

    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
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

// void dtkComposerGraph::addEdge(dtkComposerGraphEdge *edge)
// {
//     d->edges << edge;

//     this->addItem(edge);

//     this->layout();
// }

// void dtkComposerGraph::removeEdge(dtkComposerGraphEdge *edge)
// {
//     d->edges.removeAll(edge);

//     this->removeItem(edge);

//     this->layout();
// }

// void dtkComposerGraph::addNode(dtkComposerGraphNode *node)
// {
//     d->nodes << node;

//     this->addItem(node);

//     this->layout();
// }

// void dtkComposerGraph::removeNode(dtkComposerGraphNode *node)
// {
//     d->nodes.removeAll(node);

//     this->removeItem(node);

//     this->layout();
// }

// dtkComposerGraphEdgeList dtkComposerGraph::edges(void)
// {
//     return d->edges;
// }

// dtkComposerGraphNodeList dtkComposerGraph::nodes(void)
// {
//     return d->nodes;
// }

void dtkComposerGraph::layout(void)
{
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

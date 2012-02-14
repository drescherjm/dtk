/* dtkComposerGraph.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:43:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 14 14:13:03 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 284
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

#include "dtkComposerSceneNodeLeaf.h"

dtkComposerGraph::dtkComposerGraph(void) : QGraphicsScene(), d(new dtkComposerGraphPrivate)
{
    this->connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));

    // // -- Layout testing

    // dtkComposerSceneNodeLeaf *n01 = new dtkComposerSceneNodeLeaf; this->addNode(n01);
    // dtkComposerSceneNodeLeaf *n02 = new dtkComposerSceneNodeLeaf; this->addNode(n02);
    // dtkComposerSceneNodeLeaf *n03 = new dtkComposerSceneNodeLeaf; this->addNode(n03);
    // dtkComposerSceneNodeLeaf *n04 = new dtkComposerSceneNodeLeaf; this->addNode(n04);
    // dtkComposerSceneNodeLeaf *n05 = new dtkComposerSceneNodeLeaf; this->addNode(n05);
    // dtkComposerSceneNodeLeaf *n06 = new dtkComposerSceneNodeLeaf; this->addNode(n06);
    // dtkComposerSceneNodeLeaf *n07 = new dtkComposerSceneNodeLeaf; this->addNode(n07);
    // dtkComposerSceneNodeLeaf *n08 = new dtkComposerSceneNodeLeaf; this->addNode(n08);
    // dtkComposerSceneNodeLeaf *n09 = new dtkComposerSceneNodeLeaf; this->addNode(n09);
    // dtkComposerSceneNodeLeaf *n10 = new dtkComposerSceneNodeLeaf; this->addNode(n10);
    // dtkComposerSceneNodeLeaf *n11 = new dtkComposerSceneNodeLeaf; this->addNode(n11);
    // dtkComposerSceneNodeLeaf *n12 = new dtkComposerSceneNodeLeaf; this->addNode(n12);
    // dtkComposerSceneNodeLeaf *n13 = new dtkComposerSceneNodeLeaf; this->addNode(n13);
    // dtkComposerSceneNodeLeaf *n14 = new dtkComposerSceneNodeLeaf; this->addNode(n14);
    // dtkComposerSceneNodeLeaf *n15 = new dtkComposerSceneNodeLeaf; this->addNode(n15);

    // dtkComposerSceneEdge *e01 = new dtkComposerSceneEdge; e01->setSource(n09->outputPorts().at(0)); e01->setDestination(n12->inputPorts().at(0)); this->addEdge(e01);
    // dtkComposerSceneEdge *e02 = new dtkComposerSceneEdge; e02->setSource(n09->outputPorts().at(0)); e02->setDestination(n13->inputPorts().at(0)); this->addEdge(e02);
    // dtkComposerSceneEdge *e03 = new dtkComposerSceneEdge; e03->setSource(n07->outputPorts().at(0)); e03->setDestination(n09->inputPorts().at(0)); this->addEdge(e03);
    // dtkComposerSceneEdge *e04 = new dtkComposerSceneEdge; e04->setSource(n06->outputPorts().at(0)); e04->setDestination(n07->inputPorts().at(0)); this->addEdge(e04);
    // dtkComposerSceneEdge *e05 = new dtkComposerSceneEdge; e05->setSource(n07->outputPorts().at(0)); e05->setDestination(n10->inputPorts().at(0)); this->addEdge(e05);
    // dtkComposerSceneEdge *e06 = new dtkComposerSceneEdge; e06->setSource(n07->outputPorts().at(0)); e06->setDestination(n11->inputPorts().at(0)); this->addEdge(e06);
    // dtkComposerSceneEdge *e07 = new dtkComposerSceneEdge; e07->setSource(n05->outputPorts().at(0)); e07->setDestination(n07->inputPorts().at(0)); this->addEdge(e07);
    // dtkComposerSceneEdge *e08 = new dtkComposerSceneEdge; e08->setSource(n06->outputPorts().at(0)); e08->setDestination(n10->inputPorts().at(0)); this->addEdge(e08);
    // dtkComposerSceneEdge *e09 = new dtkComposerSceneEdge; e09->setSource(n06->outputPorts().at(0)); e09->setDestination(n08->inputPorts().at(0)); this->addEdge(e09);
    // dtkComposerSceneEdge *e10 = new dtkComposerSceneEdge; e10->setSource(n04->outputPorts().at(0)); e10->setDestination(n06->inputPorts().at(0)); this->addEdge(e10);
    // dtkComposerSceneEdge *e11 = new dtkComposerSceneEdge; e11->setSource(n03->outputPorts().at(0)); e11->setDestination(n06->inputPorts().at(0)); this->addEdge(e11);
    // dtkComposerSceneEdge *e12 = new dtkComposerSceneEdge; e12->setSource(n10->outputPorts().at(0)); e12->setDestination(n14->inputPorts().at(0)); this->addEdge(e12);
    // dtkComposerSceneEdge *e13 = new dtkComposerSceneEdge; e13->setSource(n08->outputPorts().at(0)); e13->setDestination(n11->inputPorts().at(0)); this->addEdge(e13);
    // dtkComposerSceneEdge *e14 = new dtkComposerSceneEdge; e14->setSource(n11->outputPorts().at(0)); e14->setDestination(n14->inputPorts().at(0)); this->addEdge(e14);
    // dtkComposerSceneEdge *e15 = new dtkComposerSceneEdge; e15->setSource(n11->outputPorts().at(0)); e15->setDestination(n15->inputPorts().at(0)); this->addEdge(e15);
    // dtkComposerSceneEdge *e16 = new dtkComposerSceneEdge; e16->setSource(n14->outputPorts().at(0)); e16->setDestination(n02->inputPorts().at(0)); this->addEdge(e16);
    // dtkComposerSceneEdge *e17 = new dtkComposerSceneEdge; e17->setSource(n14->outputPorts().at(0)); e17->setDestination(n01->inputPorts().at(0)); this->addEdge(e17);
    // dtkComposerSceneEdge *e18 = new dtkComposerSceneEdge; e18->setSource(n02->outputPorts().at(0)); e18->setDestination(n04->inputPorts().at(0)); this->addEdge(e18);
    // dtkComposerSceneEdge *e19 = new dtkComposerSceneEdge; e19->setSource(n02->outputPorts().at(0)); e19->setDestination(n03->inputPorts().at(0)); this->addEdge(e19);
    // dtkComposerSceneEdge *e20 = new dtkComposerSceneEdge; e20->setSource(n15->outputPorts().at(0)); e20->setDestination(n02->inputPorts().at(0)); this->addEdge(e20);
    // dtkComposerSceneEdge *e21 = new dtkComposerSceneEdge; e21->setSource(n15->outputPorts().at(0)); e21->setDestination(n01->inputPorts().at(0)); this->addEdge(e21);
    // dtkComposerSceneEdge *e22 = new dtkComposerSceneEdge; e22->setSource(n15->outputPorts().at(0)); e22->setDestination(n05->inputPorts().at(0)); this->addEdge(e22);
    // dtkComposerSceneEdge *e23 = new dtkComposerSceneEdge; e23->setSource(n01->outputPorts().at(0)); e23->setDestination(n03->inputPorts().at(0)); this->addEdge(e23);
    // dtkComposerSceneEdge *e24 = new dtkComposerSceneEdge; e24->setSource(n03->outputPorts().at(0)); e24->setDestination(n05->inputPorts().at(0)); this->addEdge(e24);

    // this->layout();

    // // --
}

dtkComposerGraph::dtkComposerGraph(const dtkComposerGraph& other) : QGraphicsScene(), d(new dtkComposerGraphPrivate)
{
    d->edges = QHash<dtkComposerSceneEdge *, dtkComposerGraphEdge *>(other.d->edges);
    d->nodes = QHash<dtkComposerSceneNode *, dtkComposerGraphNode *>(other.d->nodes);

    this->connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
}

dtkComposerGraph::~dtkComposerGraph(void)
{
    // qDeleteAll(d->edges);
    // qDeleteAll(d->nodes);

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

void dtkComposerGraph::removeNode(dtkComposerGraphNode *node)
{
    foreach(dtkComposerGraphNode *n, d->nodes.values())
        if(n = node)
            d->nodes.remove(d->nodes.key(n));
}

void dtkComposerGraph::removeEdge(dtkComposerGraphEdge *edge)
{
    foreach(dtkComposerGraphEdge *e, d->edges.values())
        if(e = edge)
            d->edges.remove(d->edges.key(e));
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

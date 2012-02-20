/* dtkComposerGraph.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:43:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. févr. 20 14:49:13 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 583
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
#include "dtkComposerGraphNodeBegin.h"
#include "dtkComposerGraphNodeEnd.h"
#include "dtkComposerGraphNodeLeaf.h"
#include "dtkComposerGraphNodeSelectBranch.h"
#include "dtkComposerGraphNodeSetConditions.h"
#include "dtkComposerGraphNodeSetInputs.h"
#include "dtkComposerGraphNodeSetOutputs.h"
#include "dtkComposerGraphNodeSetVariables.h"
#include "dtkComposerNode.h"
//#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeFor.h"
#include "dtkComposerNodeLeaf.h"
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
    void addEdge(dtkComposerGraphNode *source, dtkComposerGraphNode *dest, dtkComposerSceneNode *node, int id = 0);

public:
    QMultiHash<dtkComposerSceneEdge *, dtkComposerGraphEdge *> edges;
    // for each control node, we need to create several graph nodes ("statements")
    QMultiHash<dtkComposerSceneNode *, dtkComposerGraphNode *> nodes;
    // for each control node, we need to create several graph edges, not linked to any scene edge
    QMultiHash<dtkComposerSceneNode *, dtkComposerGraphEdge *> dummy_edges;

public:
    dtkComposerGraph *q;
};

bool dtkComposerGraphPrivate::exists(dtkComposerSceneEdge *edge)
{

    // for control nodes, the graph

    dtkComposerGraphNode *s = this->nodes.value(edge->source()->node());
    dtkComposerGraphNode *d = this->nodes.value(edge->destination()->node());

    foreach(dtkComposerGraphEdge *e, this->edges)
        if(e->source() == s && e->destination() == d)
            return true;

    return false;
}

// add graph edge not related to scene edge (for a scene control nodes)
void dtkComposerGraphPrivate::addEdge(dtkComposerGraphNode *source, dtkComposerGraphNode *destination, dtkComposerSceneNode *node, int id)
{
    dtkComposerGraphEdge *e = new dtkComposerGraphEdge;
    e->setSource(source);
    e->setDestination(destination);
    e->setId(id);
    dummy_edges.insertMulti(node, e);
    edges.insertMulti(0, e);
    q->addItem(e);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerGraph
// /////////////////////////////////////////////////////////////////


dtkComposerGraph::dtkComposerGraph(void) : QGraphicsScene(), d(new dtkComposerGraphPrivate)
{
    d->q = this;

    this->connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
}

dtkComposerGraph::dtkComposerGraph(const dtkComposerGraph& other) : QGraphicsScene(), d(new dtkComposerGraphPrivate)
{
    d->edges = QMultiHash<dtkComposerSceneEdge *, dtkComposerGraphEdge *>(other.d->edges);
    d->nodes = QMultiHash<dtkComposerSceneNode *, dtkComposerGraphNode *>(other.d->nodes);

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

    dtkComposerNode *wrapee = node->wrapee();

    if (!dynamic_cast<dtkComposerNodeLeaf *>(wrapee)) {

        dtkComposerGraphNode *inputs    = new dtkComposerGraphNodeSetInputs(wrapee);
        dtkComposerGraphNode *outputs   = new dtkComposerGraphNodeSetOutputs(wrapee);
        dtkComposerGraphNode *begin     = new dtkComposerGraphNodeBegin(wrapee);
        dtkComposerGraphNode *end       = new dtkComposerGraphNodeEnd(wrapee);
        dtkComposerGraphNode *set_conds = new dtkComposerGraphNodeSetConditions(wrapee);
        dtkComposerGraphNode *select    = new dtkComposerGraphNodeSelectBranch(wrapee);

        d->nodes.insertMulti(node, inputs);
        d->nodes.insertMulti(node, outputs);
        d->nodes.insertMulti(node, begin);
        d->nodes.insertMulti(node, end);
        d->nodes.insertMulti(node, select);
        d->nodes.insertMulti(node, set_conds);

        if (dynamic_cast<dtkComposerNodeFor *>(wrapee)) {
            dtkComposerGraphNode *begin_cond  = new dtkComposerGraphNodeBegin(wrapee,"Begin Cond");
            dtkComposerGraphNode *end_cond      = new dtkComposerGraphNodeEnd(wrapee,"End Cond");
            dtkComposerGraphNode *begin_block = new dtkComposerGraphNodeBegin(wrapee,"Begin Block");
            dtkComposerGraphNode *end_block     = new dtkComposerGraphNodeEnd(wrapee,"End Block");
            dtkComposerGraphNode *begin_inc   = new dtkComposerGraphNodeBegin(wrapee,"Begin Inc");
            dtkComposerGraphNode *end_inc       = new dtkComposerGraphNodeEnd(wrapee,"End Inc");
            dtkComposerGraphNode *vars = new dtkComposerGraphNodeSetVariables(wrapee);

            d->nodes.insertMulti(node, begin_cond);
            d->nodes.insertMulti(node, end_cond);
            d->nodes.insertMulti(node, begin_block);
            d->nodes.insertMulti(node, end_block);
            d->nodes.insertMulti(node, begin_inc);
            d->nodes.insertMulti(node, end_inc);
            d->nodes.insertMulti(node, vars);

            d->addEdge(   begin,        inputs, node);
            d->addEdge(   inputs,   begin_cond, node);
            d->addEdge( end_cond,    set_conds, node);
            d->addEdge(set_conds,       select, node);
            d->addEdge(   select,  begin_block, node);
            d->addEdge(   select,          end, node, 1);
            d->addEdge(end_block,      outputs, node);
            d->addEdge(  outputs,    begin_inc, node);
            d->addEdge(  end_inc,         vars, node);
            d->addEdge(     vars,   begin_cond, node);
        }
        // } else if (dynamic_cast<dtkComposerNodeWhile *>(wrapee)) {
        //     dtkComposerGraphNode *begin_cond  = new dtkComposerGraphNodeBegin(wrapee,"Begin Cond");
        //     dtkComposerGraphNode *end_cond      = new dtkComposerGraphNodeEnd(wrapee,"End Cond");
        //     dtkComposerGraphNode *begin_block = new dtkComposerGraphNodeBegin(wrapee,"Begin Block");
        //     dtkComposerGraphNode *end_block     = new dtkComposerGraphNodeEnd(wrapee,"End Block");

        //     d->nodes.insertMulti(node, begin_cond);
        //     d->nodes.insertMulti(node, end_cond);
        //     d->nodes.insertMulti(node, begin_block);
        //     d->nodes.insertMulti(node, end_block);

        //     d->addEdge(   begin,       inputs, node);
        //     d->addEdge(   inputs,  begin_cond, node);
        //     d->addEdge( end_cond,   set_conds, node);
        //     d->addEdge(set_conds,      select, node);

        //     d->addEdge(   select, begin_block, node);
        //     d->addEdge(   select,         end, node, 1);
        //     d->addEdge(end_block,     outputs, node);
        //     d->addEdge(  outputs, begin_conds, node);
        // } else if (dynamic_cast<dtkComposerNodeIf *>(wrapee)) {
        //     dtkComposerGraphNode *begin_true  = new dtkComposerGraphNodeBegin(wrapee,"Begin True");
        //     dtkComposerGraphNode *end_true      = new dtkComposerGraphNodeEnd(wrapee,"End True");
        //     dtkComposerGraphNode *begin_false = new dtkComposerGraphNodeBegin(wrapee,"Begin False");
        //     dtkComposerGraphNode *end_false     = new dtkComposerGraphNodeEnd(wrapee,"End False");

        //     d->nodes.insertMulti(node, begin_true);
        //     d->nodes.insertMulti(node, end_true);
        //     d->nodes.insertMulti(node, begin_false);
        //     d->nodes.insertMulti(node, end_false);

        //     // FIXME: what about inputs ?
        //     d->addEdge(   begin,    set_conds, node);
        //     d->addEdge(set_conds,      select, node);

        //     d->addEdge(   select,  begin_true, node);
        //     d->addEdge(   select, begin_false, node, 1);
        //     d->addEdge( end_true,     outputs, node);
        //     d->addEdge(end_false,     outputs, node);
        //     d->addEdge(  outputs,         end, node);
        // }
    } else { // Leaf node
        dtkComposerGraphNode *leaf = new dtkComposerGraphNodeLeaf(wrapee);
        d->nodes.insertMulti(node, leaf);
    }
    foreach (dtkComposerGraphNode *n, d->nodes.values(node) )
        this->addItem(n);
    this->layout();
}


void dtkComposerGraph::removeNode(dtkComposerSceneNode *node)
{

    QList<dtkComposerGraphNode *> nodes = d->nodes.values(node);
    QList<dtkComposerGraphEdge *> edges = d->dummy_edges.values(node);

    d->nodes.remove(node);
    d->dummy_edges.remove(node);

    foreach(dtkComposerGraphNode *n, nodes)
        this->removeItem(n);

    foreach(dtkComposerGraphEdge *e, edges)
        this->removeItem(e);

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

    d->edges.insertMulti(edge, e);

    this->addItem(e);

    this->layout();
}

void dtkComposerGraph::removeEdge(dtkComposerSceneEdge *edge)
{
    if(!d->edges.contains(edge))
        return;

    QList<dtkComposerGraphEdge *> edges = d->edges.values(edge);

    d->edges.remove(edge);

    foreach (dtkComposerGraphEdge *e, edges)
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

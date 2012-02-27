/* dtkComposerGraph.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:43:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. févr. 27 10:54:58 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 1468
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
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControlDoWhile.h"
#include "dtkComposerNodeControlFor.h"
#include "dtkComposerNodeControlIf.h"
#include "dtkComposerNodeControlWhile.h"
#include "dtkComposerNodeLeaf.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerScenePort.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphPrivate
{
public:
    bool exists(dtkComposerSceneEdge *edge);
    bool exists(dtkComposerGraphNode *src, dtkComposerGraphNode *destination);

public:
    void addDummyEdge(dtkComposerGraphNode *source, dtkComposerGraphNode *dest, dtkComposerSceneNode *node, int id = 0);
    void remDummyEdge(dtkComposerGraphEdge *edge, dtkComposerSceneNode *node);
    void removeDummyEdge(dtkComposerGraphNode *source, dtkComposerGraphNode *dest, dtkComposerSceneNode *node);

public:
    dtkComposerGraphNode *begin(dtkComposerSceneNode *node);
    dtkComposerGraphNode *end(dtkComposerSceneNode *node);

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

bool dtkComposerGraphPrivate::exists(dtkComposerGraphNode *s, dtkComposerGraphNode *d)
{

    foreach(dtkComposerGraphEdge *e, this->edges)
        if(e->source() == s && e->destination() == d)
            return true;

    return false;
}

dtkComposerGraphNode *dtkComposerGraphPrivate::begin(dtkComposerSceneNode *node)
{
    if (!dynamic_cast<dtkComposerSceneNodeLeaf *>(node)) {
        foreach(dtkComposerGraphNode *n, this->nodes.values(node)) {
            if (dynamic_cast<dtkComposerGraphNodeBegin *>(n) )
                return n;
        }
    } else { //Leaf
        return this->nodes.value(node);
    }
    return NULL;
}

dtkComposerGraphNode *dtkComposerGraphPrivate::end(dtkComposerSceneNode *node)
{
    if (!dynamic_cast<dtkComposerSceneNodeLeaf *>(node)) {
        foreach(dtkComposerGraphNode *n, this->nodes.values(node)) {
            if (dynamic_cast<dtkComposerGraphNodeEnd *>(n) )
                return n;
        }
    } else { //Leaf
        return this->nodes.value(node);
    }
    return NULL;
}

// add graph edge not related to scene edge (for a scene control nodes)
void dtkComposerGraphPrivate::addDummyEdge(dtkComposerGraphNode *source, dtkComposerGraphNode *destination, dtkComposerSceneNode *node, int id)
{
    dtkComposerGraphEdge *e = new dtkComposerGraphEdge;
    e->setSource(source);
    e->setDestination(destination);
    e->setId(id);
    dummy_edges.insertMulti(node, e);
    edges.insertMulti(0, e);
    q->addItem(e);
}

void dtkComposerGraphPrivate::remDummyEdge(dtkComposerGraphEdge *edge, dtkComposerSceneNode *node)
{
    q->removeItem(edge);
    edges.remove(0, edge);
    if(node)
        dummy_edges.remove(node, edge);
    delete edge;
}

void dtkComposerGraphPrivate::removeDummyEdge(dtkComposerGraphNode *source, dtkComposerGraphNode *destination, dtkComposerSceneNode *node)
{
    foreach( dtkComposerGraphEdge *e, dummy_edges.values(node))
        if ((e->source() == begin(node)) && e->destination() == end(node) )
            remDummyEdge(e,node);
}


// /////////////////////////////////////////////////////////////////
// dtkComposerGraph
// /////////////////////////////////////////////////////////////////


dtkComposerGraph::dtkComposerGraph(void) : QGraphicsScene(), d(new dtkComposerGraphPrivate)
{
    d->q = this;

    this->connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
    this->setItemIndexMethod(NoIndex);
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
    // static int count = 0;

    dtkComposerNode *wrapee = node->wrapee();
    dtkComposerGraphNode *begin;
    dtkComposerGraphNode *end;

    if (dynamic_cast<dtkComposerNodeControl *>(wrapee)) {
        begin     = new dtkComposerGraphNodeBegin(wrapee, "Begin Control");
        end       = new dtkComposerGraphNodeEnd(wrapee,"End Control");
        dtkComposerGraphNode *inputs    = new dtkComposerGraphNodeSetInputs(wrapee);
        dtkComposerGraphNode *outputs   = new dtkComposerGraphNodeSetOutputs(wrapee);
        dtkComposerGraphNode *set_conds = new dtkComposerGraphNodeSetConditions(wrapee);
        dtkComposerGraphNode *select    = new dtkComposerGraphNodeSelectBranch(wrapee);

        d->nodes.insertMulti(node, inputs);
        d->nodes.insertMulti(node, outputs);
        d->nodes.insertMulti(node, begin);
        d->nodes.insertMulti(node, end);
        d->nodes.insertMulti(node, select);
        d->nodes.insertMulti(node, set_conds);
        foreach (dtkComposerGraphNode *n, d->nodes.values(node) ) {
            this->addItem(n);
        }

        if (dynamic_cast<dtkComposerNodeControlFor *>(wrapee)) {
            dtkComposerGraphNode *vars = new dtkComposerGraphNodeSetVariables(wrapee);
            d->nodes.insertMulti(node, vars);
            this->addItem(vars);

            QList<dtkComposerSceneNodeComposite *> blocks  = dynamic_cast<dtkComposerSceneNodeControl *>(node)->blocks();
            foreach (dtkComposerSceneNodeComposite *block,  blocks)
                this->addNode(block);

            int cond = 0; int main = 1; int incr = 2;
            d->addDummyEdge(    begin, inputs, node);
            d->addDummyEdge(   inputs, d->begin(blocks[cond]), node);
            d->addDummyEdge( d->end(blocks[cond]), set_conds,  node);
            d->addDummyEdge(set_conds, select,                 node);
            d->addDummyEdge(   select, d->begin(blocks[main]), node);
            d->addDummyEdge(   select, end,                    node, 1);
            d->addDummyEdge(d->end(blocks[main]), outputs,     node);
            d->addDummyEdge( outputs,  d->begin(blocks[incr]), node);
            d->addDummyEdge( d->end(blocks[incr]), vars,       node);
            d->addDummyEdge(     vars, d->begin(blocks[cond]), node);

        } else if (dynamic_cast<dtkComposerNodeControlWhile *>(wrapee)) {
            QList<dtkComposerSceneNodeComposite *> blocks  = dynamic_cast<dtkComposerSceneNodeControl *>(node)->blocks();
            foreach (dtkComposerSceneNodeComposite *block,  blocks)
                 this->addNode(block);

            int cond_block = 0; int body_block = 1;
            d->addDummyEdge(   begin,       inputs, node);
            d->addDummyEdge(   inputs,  d->begin(blocks[cond_block]), node);
            d->addDummyEdge( d->end(blocks[cond_block]),   set_conds, node);
            d->addDummyEdge(set_conds,      select, node);
            d->addDummyEdge(   select, d->begin(blocks[body_block]), node);
            d->addDummyEdge(   select,         end, node, 1);
            d->addDummyEdge(d->end(blocks[body_block]),     outputs, node);
            d->addDummyEdge(  outputs, d->begin(blocks[cond_block]), node);

        } else if (dynamic_cast<dtkComposerNodeControlDoWhile *>(wrapee)) {
            QList<dtkComposerSceneNodeComposite *> blocks  = dynamic_cast<dtkComposerSceneNodeControl *>(node)->blocks();
            foreach (dtkComposerSceneNodeComposite *block,  blocks)
                 this->addNode(block);

            int cond_block = 0; int body_block = 1;
            d->addDummyEdge( begin, inputs, node);
            d->addDummyEdge( inputs,  d->begin(blocks[body_block]), node);
            d->addDummyEdge( d->end(blocks[body_block]), outputs, node);
            d->addDummyEdge( outputs, d->begin(blocks[cond_block]), node);
            d->addDummyEdge( d->end(blocks[cond_block]), set_conds, node);
            d->addDummyEdge( set_conds, select, node);
            d->addDummyEdge( select, d->begin(blocks[body_block]), node);
            d->addDummyEdge( select, end, node, 1);

        } else if (dynamic_cast<dtkComposerNodeControlIf *>(wrapee)) {
            dtkComposerGraphNode *inputs_else = new dtkComposerGraphNodeSetInputs(wrapee);
            d->nodes.insertMulti(node, inputs_else);
            this->addItem(inputs_else);
            QList<dtkComposerSceneNodeComposite *> blocks  = dynamic_cast<dtkComposerSceneNodeControl *>(node)->blocks();
            foreach (dtkComposerSceneNodeComposite *block,  blocks)
                this->addNode(block);

            int then_block = 0; int else_block = 1;
            d->addDummyEdge(    begin, set_conds, node);
            d->addDummyEdge(set_conds, select, node);
            d->addDummyEdge(   select, inputs, node);
            d->addDummyEdge(   select, inputs_else, node, 1);
            d->addDummyEdge(   inputs, d->begin(blocks[then_block]), node);
            d->addDummyEdge(   inputs_else, d->begin(blocks[else_block]), node, 1);
            d->addDummyEdge(d->end(blocks[then_block]), outputs, node);
            d->addDummyEdge(d->end(blocks[else_block]), outputs, node);
            d->addDummyEdge(  outputs, end, node);
        }

        d->removeDummyEdge(  d->begin(node->parent()), d->end(node->parent()), node->parent());
        d->addDummyEdge(  d->begin(node->parent()), begin, node->parent());
        d->addDummyEdge(  end,  d->end(node->parent()),    node->parent());

    } else if (dynamic_cast<dtkComposerNodeLeaf *>(wrapee)) { // Leaf node
        dtkComposerGraphNode *leaf = new dtkComposerGraphNodeLeaf(wrapee,node->title());
        d->nodes.insertMulti(node, leaf);
        this->addItem(leaf);

        // if composite was empty, need to remove dummy edge
        if (d->dummy_edges.values(node->parent()).count() == 1) {
            d->removeDummyEdge(  d->begin(node->parent()), d->end(node->parent()), node->parent());
        }
        d->addDummyEdge(  d->begin(node->parent()), leaf, node->parent());
        d->addDummyEdge(  leaf,  d->end(node->parent()),  node->parent());

    } else if (dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {
        begin = new dtkComposerGraphNodeBegin(wrapee,"Begin"+node->title());
        end   = new dtkComposerGraphNodeEnd(wrapee,"End"+node->title());
        d->nodes.insertMulti(node, begin);
        d->nodes.insertMulti(node, end);
        this->addItem(begin);
        this->addItem(end);
        // count += 2;
        // empty composite, add dummy edge between 'begin' and 'end'
        d->addDummyEdge( begin, end, node);
        if (!composite->root()  && !(dynamic_cast<dtkComposerSceneNodeControl *>(node->parent())) ) {
            d->removeDummyEdge(  d->begin(node->parent()), d->end(node->parent()), node->parent());
            d->addDummyEdge(  d->begin(node->parent()), begin, node->parent());
            d->addDummyEdge(  end,  d->end(node->parent()),    node->parent());
        }
    }
}

void dtkComposerGraph::removeNode(dtkComposerSceneNode *node)
{
    // For control nodes, we have to remove its blocks and then it's pending dummy edges
    if (dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {
        foreach( dtkComposerSceneNodeComposite *block, control->blocks())
            this->removeNode(block);

        //remove dummy edges for this
        foreach(dtkComposerGraphEdge *e, d->dummy_edges.values(node))
            d->remDummyEdge(e, node);
    }

    if (!dynamic_cast<dtkComposerSceneNodeControl *>(node->parent())) {
        // remove dummy edges for this node on the parent
        dtkComposerGraphNode *parent_begin = d->begin(node->parent());
        dtkComposerGraphNode *parent_end   = d->end(node->parent());

        foreach( dtkComposerGraphEdge *e, d->dummy_edges.values(node->parent())) {
            if ((e->source() == parent_begin && e->destination() == d->begin(node) ) || (e->destination() == parent_end && e->source() == d->end(node)))
                d->remDummyEdge(e, node->parent());
        }
        // if parent composite is empty after removal, add back dummy edge
        if (d->dummy_edges.values(node->parent()).count() == 0) {
            d->addDummyEdge(  parent_begin, parent_end, node->parent());
        }

    }
    if (dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {
        d->removeDummyEdge(  d->begin(node), d->end(node), node);
    }

    foreach(dtkComposerGraphNode *n, d->nodes.values(node)) {
        this->removeItem(n);
        delete n;
    }
    d->nodes.remove(node);
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
    dtkComposerSceneNode *scene_src = edge->source()->node();
    dtkComposerSceneNode *scene_dest = edge->destination()->node();
    dtkComposerGraphNode *src  ;
    dtkComposerGraphNode *dest;

    if (scene_src->parent() == scene_dest) {
        src = d->end(scene_src);
        dest = d->end(scene_dest);
    } else if (scene_dest->parent() == scene_src) {
        src = d->begin(scene_src);
        dest = d->begin(scene_dest);
    } else {
        src = d->end(scene_src);
        dest = d->begin(scene_dest);
        // need to remove dummy edges that start with src
        // need to remove dummy edges that ends with dest
        foreach( dtkComposerGraphEdge *e, d->dummy_edges.values()) {
            if ((e->source() == src ) || (e->destination() == dest)) {
                // FIXME: is the condition ok for dummy edges in control nodes ?
                qDebug()<< "remove dummy edge because of addEdge";
                d->remDummyEdge(e,d->dummy_edges.key(e));
            }
        }
    }

    e->setSource(src);
    e->setDestination(dest);

    if(d->exists(src,dest)) {
        delete e;
        return;
    }

    d->edges.insertMulti(edge, e);

    this->addItem(e);
}

void dtkComposerGraph::removeEdge(dtkComposerSceneEdge *edge)
{
    qDebug() << "remove graph edge ";
    if(!d->edges.contains(edge))
        return;

    QList<dtkComposerGraphEdge *> edges = d->edges.values(edge);


    qDebug() << "add back dummy edges ";


    //add back dummy edges if necessary
    dtkComposerSceneNode *scene_src = edge->source()->node();
    dtkComposerSceneNode *scene_dest = edge->destination()->node();

    // first remove edges
    d->edges.remove(edge);
    foreach (dtkComposerGraphEdge *e, edges) {
        this->removeItem(e);
        delete e;
    }

    // if destination has edges on its input, don't add a dummy edge
    bool doit = true;
    foreach(dtkComposerGraphEdge *e, d->edges.values())
        doit = doit && (e->destination() !=  d->begin(scene_dest));
    if (doit)
        d->addDummyEdge(  d->begin(scene_src->parent()), d->begin(scene_dest), scene_src->parent());

    doit = true;
    // if source has edges on its output, don't add a dummy edge
    foreach(dtkComposerGraphEdge *e, d->edges.values())
        doit = doit && (e->source() !=  d->end(scene_src));
    if (doit)
        d->addDummyEdge(  d->end(scene_src), d->end(scene_dest->parent()), scene_src->parent());

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
        if(e = edge) {
            d->edges.remove(d->edges.key(e),e);
        }
}

QString dtkComposerGraph::toString(void)
{
    QStringList txt;
    foreach(dtkComposerGraphEdge *e, d->edges.values()) {
        txt <<  e->source()->title() + " -> "+ e->destination()->title();
    }
    return txt.join("\n");
}

void dtkComposerGraph::layout(void)
{
    dtkComposerGraphLayouter layouter;
    layouter.setGraph(this);
    layouter.layout();
    this->update();
    // qDebug() << this->toString();

    // qDebug() << "nodes:" <<  d->nodes.count();
    // qDebug() << "edges:" <<  d->edges.count();
    // qDebug() << "dummy edges:" <<  d->dummy_edges.count();
    // qDebug() << "items:" <<  this->items().count()<< "\n";
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

/* dtkComposerGraph.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:43:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: sam. févr. 25 23:43:45 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 1409
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
#include "dtkComposerNodeControlFor.h"
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
        return  this->nodes.value(node);
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
        return  this->nodes.value(node);
    }
    return NULL;
}

// add graph edge not related to scene edge (for a scene control nodes)
void dtkComposerGraphPrivate::addDummyEdge(dtkComposerGraphNode *source, dtkComposerGraphNode *destination, dtkComposerSceneNode *node, int id)
{
    // static int count = 0;

    dtkComposerGraphEdge *e = new dtkComposerGraphEdge;
    e->setSource(source);
    e->setDestination(destination);
    e->setId(id);
    dummy_edges.insertMulti(node, e);
    edges.insertMulti(0, e);
    q->addItem(e);

    // qDebug() << __func__ << ++count;
}

void dtkComposerGraphPrivate::remDummyEdge(dtkComposerGraphEdge *edge, dtkComposerSceneNode *node)
{
    // static int count = 0;

    q->removeItem(edge);
    edges.remove(0, edge);
    if(node)
        dummy_edges.remove(node, edge);
    delete edge;

    // qDebug() << __func__ << ++count;
}

void dtkComposerGraphPrivate::removeDummyEdge(dtkComposerGraphNode *source, dtkComposerGraphNode *destination, dtkComposerSceneNode *node)
{
    foreach( dtkComposerGraphEdge *e, dummy_edges.values(node)) {
        if ((e->source() == begin(node)) && e->destination() == end(node) )  {
                // qDebug() << "found one dummy edge to remove";
                edges.remove(0,e);
                dummy_edges.remove(node, e);
                q->removeItem(e);
//                delete e;
        }
    }
}


// /////////////////////////////////////////////////////////////////
// dtkComposerGraph
// /////////////////////////////////////////////////////////////////


dtkComposerGraph::dtkComposerGraph(void) : QGraphicsScene(), d(new dtkComposerGraphPrivate)
{
    d->q = this;

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
            // count++;
        }

        if (dynamic_cast<dtkComposerNodeControlFor *>(wrapee)) {
            dtkComposerGraphNode *vars = new dtkComposerGraphNodeSetVariables(wrapee);
            d->nodes.insertMulti(node, vars);
            this->addItem(vars);
            // count++;

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
        }
        // } else if (dynamic_cast<dtkComposerNodeWhile *>(wrapee)) {
        //     QList<dtkComposerSceneNodeComposite *> blocks  = dynamic_cast<dtkComposerSceneNodeControl *>(node)->blocks();
        //     foreach (dtkComposerSceneNodeComposite *block,  blocks)
        //          this->addNode(block);
        //     d->addDummyEdge(   begin,       inputs, node);
        //     d->addDummyEdge(   inputs,  begin_cond, node);
        //     d->addDummyEdge( end_cond,   set_conds, node);
        //     d->addDummyEdge(set_conds,      select, node);
        //     d->addDummyEdge(   select, begin_block, node);
        //     d->addDummyEdge(   select,         end, node, 1);
        //     d->addDummyEdge(end_block,     outputs, node);
        //     d->addDummyEdge(  outputs, begin_conds, node);
        // } else if (dynamic_cast<dtkComposerNodeIf *>(wrapee)) {
        //     QList<dtkComposerSceneNodeComposite *> blocks  = dynamic_cast<dtkComposerSceneNodeControl *>(node)->blocks();
        //     foreach (dtkComposerSceneNodeComposite *block,  blocks)
        //         this->addNode(block);
        //     d->nodes.insertMulti(node, begin_true);
        //     d->nodes.insertMulti(node, end_true);
        //     d->nodes.insertMulti(node, begin_false);
        //     d->nodes.insertMulti(node, end_false);
        //     // FIXME: what about inputs ?
        //     d->addDummyEdge(   begin,    set_conds, node);
        //     d->addDummyEdge(set_conds,      select, node);
        //     d->addDummyEdge(   select,  begin_true, node);
        //     d->addDummyEdge(   select, begin_false, node, 1);
        //     d->addDummyEdge( end_true,     outputs, node);
        //     d->addDummyEdge(end_false,     outputs, node);
        //     d->addDummyEdge(  outputs,         end, node);
        // }

        d->removeDummyEdge(  d->begin(node->parent()), d->end(node->parent()), node->parent());
        d->addDummyEdge(  d->begin(node->parent()), begin, node->parent());
        d->addDummyEdge(  end,  d->end(node->parent()),    node->parent());

    } else if (dynamic_cast<dtkComposerNodeLeaf *>(wrapee)) { // Leaf node
        dtkComposerGraphNode *leaf = new dtkComposerGraphNodeLeaf(wrapee,node->title());
        d->nodes.insertMulti(node, leaf);
        this->addItem(leaf);
        // count++;
        d->addDummyEdge(  d->begin(node->parent()), leaf, node->parent());
        d->addDummyEdge(  leaf,  d->end(node->parent()),  node->parent());
        // empty composite, add dummy edge between 'begin' and 'end'

        // if composite was empty, need to remove dummy edge
        if (dynamic_cast<dtkComposerSceneNodeComposite *>(node->parent())->nodes().count() == 0) {
            // qDebug() <<  "parent composite no longer empty, remove dummy edge";
            d->removeDummyEdge(  d->begin(node->parent()), d->end(node->parent()), node->parent());
        }
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

    // qDebug() << __func__ << count;
}

void dtkComposerGraph::removeNode(dtkComposerSceneNode *node)
{
    // static int count = 0;

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
        if (dynamic_cast<dtkComposerSceneNodeComposite *>(node->parent())->nodes().count() == 0) {
            // qDebug() <<  "parent composite is empty after removal, add back dummy edge";
            d->addDummyEdge(  parent_begin, parent_end, node->parent());
        }
    } else { // block node, remove dummy edge if empty
        // qDebug() <<  "empty block node, remove single dummy edge";
        d->removeDummyEdge(  d->begin(node), d->end(node), node);
    }

    QList<dtkComposerGraphNode *> nodes = d->nodes.values(node);
    foreach(dtkComposerGraphNode *n, nodes) {
        this->removeItem(n);
        // count++;
    }

    d->nodes.remove(node);

    // qDebug() << __func__ << count;
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
                // qDebug()<< "remove dummy edge because of addEdge";
                d->edges.remove(0,e);
                d->dummy_edges.remove(d->dummy_edges.key(e), e);
                this->removeItem(e);
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
    // qDebug() << "remove graph edge ";
    if(!d->edges.contains(edge))
        return;

    QList<dtkComposerGraphEdge *> edges = d->edges.values(edge);


    // qDebug() << "add back dummy edges ";
    //add back dummy edges if necessary
    dtkComposerSceneNode *scene_src = edge->source()->node();
    dtkComposerSceneNode *scene_dest = edge->destination()->node();
    d->addDummyEdge(  d->begin(scene_src->parent()), d->begin(scene_src), scene_src->parent());
    d->addDummyEdge(  d->end(scene_src), d->end(scene_dest->parent()), scene_src->parent());

    d->edges.remove(edge);
    foreach (dtkComposerGraphEdge *e, edges) {
        this->removeItem(e);
//        delete e;
    }
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
//    qDebug() << "remove graph node ";
    foreach(dtkComposerGraphNode *n, d->nodes.values())
        if(n = node)
            d->nodes.remove(d->nodes.key(n));
}

void dtkComposerGraph::removeEdge(dtkComposerGraphEdge *edge)
{
//    qDebug() << "remove graph edge ";
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
    // dtkComposerGraphLayouter layouter;
    // layouter.setGraph(this);
    // layouter.layout();

    this->update();
    //    qDebug() << this->toString();

    // qDebug() << "nodes:" <<  d->nodes.count();
    // qDebug() << "edges:" <<  d->edges.count();
    // qDebug() << "dummy edges:" <<  d->dummy_edges.count();
    // qDebug() << "items:" <<  this->items().count();
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

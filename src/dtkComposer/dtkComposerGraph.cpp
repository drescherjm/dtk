/* dtkComposerGraph.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:43:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. mars 20 14:38:43 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 1779
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
#include "dtkComposerNodeControlForEach.h"
#include "dtkComposerNodeControlIf.h"
#include "dtkComposerNodeControlWhile.h"
#include "dtkComposerNodeLeaf.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerScenePort.h"

#include <dtkLog/dtkLog.h>

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
    e->source()->addSuccessor(e->destination(),id);
    e->destination()->addPredecessor(e->source());
    dummy_edges.insertMulti(node, e);
    edges.insertMulti(0, e);
    q->addItem(e);
}

void dtkComposerGraphPrivate::remDummyEdge(dtkComposerGraphEdge *edge, dtkComposerSceneNode *node)
{
    q->removeItem(edge);
    edges.remove(0, edge);

    edge->source()->removeSuccessor(edge->destination());
    edge->destination()->removePredecessor(edge->source());

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

dtkComposerGraphNode *dtkComposerGraph::root(void)
{
    foreach(dtkComposerGraphNode *node, d->nodes)
        if (node->predecessors().count() == 0)
            return node;
    return NULL;
}

void dtkComposerGraph::addNode(dtkComposerSceneNode *node)
{
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
            vars->setEndLoop();

        } else if (dynamic_cast<dtkComposerNodeControlForEach *>(wrapee)) {
            dtkComposerGraphNode *vars = new dtkComposerGraphNodeSetVariables(wrapee);
            d->nodes.insertMulti(node, vars);
            this->addItem(vars);

            QList<dtkComposerSceneNodeComposite *> blocks  = dynamic_cast<dtkComposerSceneNodeControl *>(node)->blocks();
            foreach (dtkComposerSceneNodeComposite *block,  blocks)
                this->addNode(block);

            int body = 0;
            d->addDummyEdge(    begin, inputs, node);
            d->addDummyEdge(   inputs, set_conds, node);
            d->addDummyEdge(set_conds, select, node);
            d->addDummyEdge(   select, d->begin(blocks[body]), node);
            d->addDummyEdge(   select, end, node, 1);
            d->addDummyEdge( d->end(blocks[body]), outputs,  node);
            d->addDummyEdge(outputs, vars, node);
            d->addDummyEdge(     vars, set_conds, node);
            vars->setEndLoop();

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
            outputs->setEndLoop();

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
            outputs->setEndLoop();

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
    dtkTrace() << "removing node" << node->title();
    dtkComposerSceneNode *parent = node->parent();
    dtkTrace() <<  "node parent is " << parent->title();
    // For control nodes, we have to remove its blocks and then it's pending dummy edges
    if (dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {

        //remove dummy edges for this
        foreach(dtkComposerGraphEdge *e, d->dummy_edges.values(node))
            d->remDummyEdge(e, node);

        foreach( dtkComposerSceneNodeComposite *block, control->blocks())
            this->removeNode(block);

    }

    if (!dynamic_cast<dtkComposerSceneNodeControl *>(parent)) {
        // remove dummy edges for this node on the parent
        dtkComposerGraphNode *parent_begin = d->begin(parent);
        dtkComposerGraphNode *parent_end   = d->end(parent);

        dtkTrace() << " removing dummy edges of parent";
        foreach( dtkComposerGraphEdge *e, d->dummy_edges.values(parent)) {
            if ((e->source() == parent_begin && e->destination() == d->begin(node) ) || (e->destination() == parent_end && e->source() == d->end(node)))
                d->remDummyEdge(e, parent);
        }
        // if parent composite is empty after removal, add back dummy edge
        if (d->dummy_edges.values(parent).count() == 0) {
            dtkTrace()<< " add back dummy edge of empty parent";
            d->addDummyEdge(  parent_begin, parent_end, parent);
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


void dtkComposerGraph::reparentNode(dtkComposerSceneNode *node, dtkComposerSceneNode *newparent)
{
    // remove dummy edges for this node on the parent
    dtkComposerSceneNode *oldparent = node->parent();

    foreach( dtkComposerGraphEdge *e, d->dummy_edges.values(oldparent)) {
        if ((e->source() == d->begin(oldparent)  && e->destination() == d->begin(node) ) || (e->destination() == d->end(oldparent) && e->source() == d->end(node)))
            d->remDummyEdge(e, oldparent);
    }
    // if oldparent composite is empty after removal, add back dummy edge
    if (d->dummy_edges.values(oldparent).count() == 0)
        d->addDummyEdge(  d->begin(oldparent), d->end(oldparent), oldparent);

    // if new composite parent was empty, need to remove dummy edge
    if (d->dummy_edges.values(newparent).count() == 1)
        d->removeDummyEdge(  d->begin(newparent), d->end(newparent), newparent);

    d->addDummyEdge(  d->begin(newparent), d->begin(node), newparent);
    d->addDummyEdge(  d->end(node),  d->end(newparent),  newparent);
}

void dtkComposerGraph::addEdge(dtkComposerSceneEdge *edge)
{
    dtkComposerSceneNode *scene_src = edge->source()->node();
    dtkComposerSceneNode *scene_dest = edge->destination()->node();

    if(!d->nodes.contains(edge->source()->node()) && !dynamic_cast<dtkComposerSceneNodeControl *>(scene_src->parent()))
        return;

    if(!d->nodes.contains(edge->destination()->node()) && !dynamic_cast<dtkComposerSceneNodeControl *>(scene_dest->parent()))
        return;

    if(d->exists(edge))
        return;

    dtkComposerGraphEdge *e = new dtkComposerGraphEdge;
    dtkComposerGraphNode *src;
    dtkComposerGraphNode *dest;

    // if the destination is a control node port, then we must use the control node parent begin/end
    if (dynamic_cast<dtkComposerSceneNodeControl *>(scene_dest->parent()) && (scene_dest != scene_src->parent()))
        scene_dest = scene_dest->parent();
    if (dynamic_cast<dtkComposerSceneNodeControl *>(scene_src->parent()) && (scene_src != scene_dest->parent()) )
        scene_src = scene_src->parent();

    if (scene_src->parent() == scene_dest) {
        dtkTrace() << " add edge output edge to end of composite";
        src = d->end(scene_src);
        dest = d->end(scene_dest);
    } else if (scene_dest->parent() == scene_src) {
        dtkTrace() << " add input edge from composite";
        src = d->begin(scene_src);
        dest = d->begin(scene_dest);
    } else {
        dtkTrace() << " add regular edge" << scene_src->title() << scene_dest->title();
        src = d->end(scene_src);
        dest = d->begin(scene_dest);
        // need to remove dummy edges that start with src
        // need to remove dummy edges that ends with dest
        foreach( dtkComposerGraphEdge *e, d->dummy_edges.values()) {
            if ((e->source() == src ) || (e->destination() == dest)) {
                // FIXME: is the condition ok for dummy edges in control nodes ?
                dtkTrace() << " remove dummy edge because of addEdge";
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

    src->addSuccessor(dest);
    dest->addPredecessor(src);

    d->edges.insertMulti(edge, e);

    this->addItem(e);
}

void dtkComposerGraph::removeEdge(dtkComposerSceneEdge *edge)
{
    if(!d->edges.contains(edge))
        return;

    QList<dtkComposerGraphEdge *> edges = d->edges.values(edge);

    //add back dummy edges if necessary
    dtkComposerSceneNode *scene_src = edge->source()->node();
    dtkComposerSceneNode *scene_dest = edge->destination()->node();

    // first remove edges
    d->edges.remove(edge);
    foreach (dtkComposerGraphEdge *e, edges) {
        e->source()->removeSuccessor(e->destination());
        e->destination()->removePredecessor(e->source());

        this->removeItem(e);
        delete e;
    }

    // if destination has edges on its input, don't add a dummy edge
    bool doit = true;
    foreach(dtkComposerGraphEdge *e, d->edges.values())
        doit = doit && (e->destination() !=  d->begin(scene_dest));
    if (doit) {
        dtkTrace() << " add back dummy edge " << scene_src->parent()->title() << scene_dest->title();
        d->addDummyEdge(  d->begin(scene_src->parent()), d->begin(scene_dest), scene_src->parent());
    }

    doit = true;
    // if source has edges on its output, don't add a dummy edge
    foreach(dtkComposerGraphEdge *e, d->edges.values())
        doit = doit && (e->source() !=  d->end(scene_src));
    if (doit) {
        dtkTrace() << " add back dummy edge " << scene_src->title() << scene_dest->parent()->title();
        d->addDummyEdge(  d->end(scene_src), d->end(scene_dest->parent()), scene_src->parent());
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

void dtkComposerGraph::clear(void) {
    d->dummy_edges.clear();
    foreach(dtkComposerGraphEdge *e, d->edges.values()) {
        this->removeItem(e);
        delete e;
    }
    d->edges.clear();

    foreach(dtkComposerGraphNode *n, d->nodes.values()) {
        this->removeItem(n);
        delete n;
    }
    d->nodes.clear();
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

/* dtkComposerGraph.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:43:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 14:42:43 2014 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 2109
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
#include "dtkComposerGraphNodeBegin.h"
#include "dtkComposerGraphNodeEnd.h"
#include "dtkComposerGraphNodeLeaf.h"
#include "dtkComposerGraphNodeSelectBranch.h"
#include "dtkComposerGraphNodeSetInputs.h"
#include "dtkComposerGraphNodeSetOutputs.h"
#include "dtkComposerGraphNodeSetVariables.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControlCase.h"
#include "dtkComposerNodeControlDoWhile.h"
#include "dtkComposerNodeControlFor.h"
#include "dtkComposerNodeControlForEach.h"
#include "dtkComposerNodeControlMap.h"
#include "dtkComposerNodeControlIf.h"
#include "dtkComposerNodeControlWhile.h"
#include "dtkComposerNodeLeaf.h"
#include "dtkComposerNodeMetaData.h"

#include <dtkMathSupport/dtkGraph.h>
#include <dtkMathSupport/dtkGraphEdge.h>

#include <dtkLog/dtkLogger.h>

// /////////////////////////////////////////////////////////////////
// dtkLog categories
// /////////////////////////////////////////////////////////////////

//DTK_LOG_CATEGORY(FR_INRIA_DTK_COMPOSER_EVALUATOR, "fr.inria.dtk.composer.evaluator")

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphPrivate
{
public:
    void addDummyEdge(dtkComposerGraphNode *source, dtkComposerGraphNode *dest, dtkComposerNode *node, int id = 0);
    void remDummyEdge(dtkComposerGraphEdge *edge, dtkComposerNode *node);
    void removeDummyEdge(dtkComposerGraphNode *source, dtkComposerGraphNode *dest, dtkComposerNode *node);

    void addNode(dtkComposerNode *node, dtkComposerGraphNode *node_g, dtkComposerGraphNode *parent_g);
    void remNode(dtkComposerNode *node, dtkComposerGraphNode *node_g, dtkComposerGraphNode *parent_g);

public:
    dtkComposerGraphNode *begin(dtkComposerNode *node);
    dtkComposerGraphNode *end(dtkComposerNode *node);

public:
    QHash<QPair<dtkComposerNode *,dtkComposerNode *> , dtkComposerGraphEdge *> edges;
    QHash<QPair<dtkComposerNode *,dtkComposerNode *> , int> edges_count;
    // for each control node, we need to create several graph nodes ("statements")
    QMultiHash<dtkComposerNode *, dtkComposerGraphNode *> nodes;
    // for each control node, we need to create several graph edges, not linked to any scene edge
    QMultiHash<dtkComposerNode *, dtkComposerGraphEdge *> dummy_edges;

    QHash<dtkComposerNode *, dtkComposerNode *> control_nodes;
};


dtkComposerGraphNode *dtkComposerGraphPrivate::begin(dtkComposerNode *node)
{
    if (!node)
        return NULL;

    if (!dynamic_cast<dtkComposerNodeLeaf *>(node)) {
        foreach(dtkComposerGraphNode *n, this->nodes.values(node)) {
            if (dynamic_cast<dtkComposerGraphNodeBegin *>(n) )
                return n;
        }
    } else { //Leaf
        return this->nodes.value(node);
    }
    return NULL;
}

dtkComposerGraphNode *dtkComposerGraphPrivate::end(dtkComposerNode *node)
{
    if (!dynamic_cast<dtkComposerNodeLeaf *>(node)) {
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
void dtkComposerGraphPrivate::addDummyEdge(dtkComposerGraphNode *source, dtkComposerGraphNode *destination, dtkComposerNode *node, int id)
{
    if (!source || !destination) {
        return;
    }
    dtkComposerGraphEdge *e = new dtkComposerGraphEdge;
    e->setSource(source);
    e->setDestination(destination);
    e->setId(id);
    e->source()->addSuccessor(e->destination(),id);
    e->destination()->addPredecessor(e->source());
    dummy_edges.insertMulti(node, e);
}

void dtkComposerGraphPrivate::remDummyEdge(dtkComposerGraphEdge *edge, dtkComposerNode *node)
{
    edge->source()->removeSuccessor(edge->destination());
    edge->destination()->removePredecessor(edge->source());

    if(node)
        dummy_edges.remove(node, edge);
    delete edge;
}

void dtkComposerGraphPrivate::removeDummyEdge(dtkComposerGraphNode *source, dtkComposerGraphNode *destination, dtkComposerNode *node)
{
    foreach( dtkComposerGraphEdge *e, dummy_edges.values(node))
        if ((e->source() == begin(node)) && e->destination() == end(node) )
            remDummyEdge(e,node);
}

void dtkComposerGraphPrivate::addNode(dtkComposerNode *node, dtkComposerGraphNode *node_g, dtkComposerGraphNode *parent_g)
{
    nodes.insertMulti(node, node_g);
    if (parent_g)
        parent_g->addChild(node_g);
}

void dtkComposerGraphPrivate::remNode(dtkComposerNode *node, dtkComposerGraphNode *node_g, dtkComposerGraphNode *parent_g)
{
    if (parent_g)
        parent_g->removeChild(node_g);
    delete node_g;
    this->nodes.remove(node,node_g);
}



// /////////////////////////////////////////////////////////////////
// dtkComposerGraph
// /////////////////////////////////////////////////////////////////


dtkComposerGraph::dtkComposerGraph(void) : QObject(), d(new dtkComposerGraphPrivate)
{
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
    foreach(dtkComposerGraphNode *node, d->nodes.values())
        if (node->predecessors().count() == 0)
            return node;
    dtkWarn() << "empty root node!";
    return NULL;
}

void dtkComposerGraph::addNode(dtkComposerNode *node, dtkComposerNode *parent)
{
    dtkComposerGraphNodeBegin *begin;
    dtkComposerGraphNodeEnd     *end;

    dtkComposerNodeControl *control  = dynamic_cast<dtkComposerNodeControl *>(node);
    if (control) {
        int blockCount = control->blockCount();
        begin     = new dtkComposerGraphNodeBegin(node, "Begin Control");
        end       = new dtkComposerGraphNodeEnd(node,"End Control");
        begin->setKind(dtkComposerGraphNode::BeginLoop) ;
        begin->setEnd(end);
        end->setBegin(begin);
        begin->setGraph(this);
        end->setGraph(this);

        dtkComposerGraphNode *outputs   = new dtkComposerGraphNodeSetOutputs(node);
        dtkComposerGraphNode *select    = new dtkComposerGraphNodeSelectBranch(node);
        d->addNode(node,    begin, d->begin(parent));
        if (dynamic_cast<dtkComposerNodeControlIf *>(node)) {
            delete outputs;
        } else {
            d->addNode(node,  outputs, begin);
        }
        d->addNode(node,   select, begin);
        d->addNode(node,      end,  d->begin(parent));

        if (dynamic_cast<dtkComposerNodeControlFor *>(node)) {
            dtkComposerGraphNode *vars = new dtkComposerGraphNodeSetVariables(node);
            d->addNode(node, vars, begin);
            dtkComposerGraphNode *inputs    = new dtkComposerGraphNodeSetInputs(node);
            d->addNode(node,   inputs, begin);

            for (int i = 0; i < blockCount; ++i) {
                this->addNode(control->block(i), node);
            }
            this->addNode(control->header(), node);
            this->addNode(control->footer(), node);

            int cond = 0; int main = 1; int incr = 2;
            d->addDummyEdge(    begin, inputs, node);
            d->addDummyEdge(   inputs, d->begin(control->block(cond)), node);
            d->addDummyEdge( d->end(control->block(cond)), select,  node);
            d->addDummyEdge(   select, d->begin(control->block(main)), node);
            d->addDummyEdge(   select, end,                    node, 1);
            d->addDummyEdge(d->end(control->block(main)), outputs,     node);
            d->addDummyEdge( outputs,  d->begin(control->block(incr)), node);
            d->addDummyEdge( d->end(control->block(incr)), vars,       node);
            d->addDummyEdge(     vars, d->begin(control->block(cond)), node);
            vars->setEndLoop();

        } else if (dynamic_cast<dtkComposerNodeControlForEach *>(node) || dynamic_cast<dtkComposerNodeControlMap *>(node)) {

            dtkComposerGraphNode *vars = new dtkComposerGraphNodeSetVariables(node);
            d->addNode(node, vars, begin);
            dtkComposerGraphNode *inputs    = new dtkComposerGraphNodeSetInputs(node);
            d->addNode(node,   inputs, begin);

            for (int i = 0; i < blockCount; ++i) {
                this->addNode(control->block(i), node);
            }
            this->addNode(control->header(), node);
            if(dynamic_cast<dtkComposerNodeControlMap *>(node))
                this->addNode(control->footer(), node);

            int body = 0;
            d->addDummyEdge(    begin, inputs, node);
            d->addDummyEdge(   inputs, select, node);
            d->addDummyEdge(   select, vars, node);
            d->addDummyEdge(   vars, d->begin(control->block(body)), node);
            d->addDummyEdge(   select, end, node, 1);
            d->addDummyEdge( d->end(control->block(body)), outputs,  node);
            d->addDummyEdge(outputs, select, node);
            outputs->setEndLoop();

        } else if (dynamic_cast<dtkComposerNodeControlWhile *>(node)) {
            dtkComposerGraphNode *inputs    = new dtkComposerGraphNodeSetInputs(node);
            d->addNode(node,   inputs, begin);
            for (int i = 0; i < blockCount; ++i) {
                this->addNode(control->block(i), node);
            }

            int cond_block = 0; int body_block = 1;
            d->addDummyEdge(   begin,       inputs, node);
            d->addDummyEdge(   inputs,  d->begin(control->block(cond_block)), node);
            d->addDummyEdge( d->end(control->block(cond_block)),   select, node);
            d->addDummyEdge(   select, d->begin(control->block(body_block)), node);
            d->addDummyEdge(   select,         end, node, 1);
            d->addDummyEdge(d->end(control->block(body_block)),     outputs, node);
            d->addDummyEdge(  outputs, d->begin(control->block(cond_block)), node);
            outputs->setEndLoop();

        } else if (dynamic_cast<dtkComposerNodeControlDoWhile *>(node)) {
            dtkComposerGraphNode *inputs    = new dtkComposerGraphNodeSetInputs(node);
            d->addNode(node,   inputs, begin);
            for (int i = 0; i < blockCount; ++i) {
                this->addNode(control->block(i), node);
            }

            int cond_block = 1; int body_block = 0;
            d->addDummyEdge( begin, inputs, node);
            d->addDummyEdge( inputs,  d->begin(control->block(body_block)), node);
            d->addDummyEdge( d->end(control->block(body_block)), outputs, node);
            d->addDummyEdge( outputs, d->begin(control->block(cond_block)), node);
            d->addDummyEdge( d->end(control->block(cond_block)), select, node);
            d->addDummyEdge( select, d->begin(control->block(body_block)), node);
            d->addDummyEdge( select, end, node, 1);
            select->setEndLoop();

        } else if (dynamic_cast<dtkComposerNodeControlIf *>(node)) {
            begin->setKind(dtkComposerGraphNode::BeginIf) ;
            for (int i = 0; i < blockCount; ++i) {
                this->addNode(control->block(i), node);
            }
            this->addNode(control->header(), node);
            this->addNode(control->footer(), node);

            int then_block = 0; int else_block = 1;
            d->addDummyEdge(    begin, select, node);
            d->addDummyEdge(   select, d->begin(control->block(then_block)), node);
            d->addDummyEdge(   select, d->begin(control->block(else_block)), node,1);
            d->addDummyEdge(d->end(control->block(then_block)), end, node);
            d->addDummyEdge(d->end(control->block(else_block)), end, node);
            d->end(control->block(then_block))->setEndLoop();
            d->end(control->block(else_block))->setEndLoop();
        } else if (dynamic_cast<dtkComposerNodeControlCase *>(node) ) {
            begin->setKind(dtkComposerGraphNode::BeginIf) ;
            d->addDummyEdge(    begin, select, node);
            d->addDummyEdge(  outputs, end, node);
            this->addBlock(node);
            this->addNode(control->header(), node);
            this->addNode(control->footer(), node);
        }

        d->removeDummyEdge(  d->begin(parent), d->end(parent), parent);
        d->addDummyEdge(  d->begin(parent), begin, parent);
        d->addDummyEdge(  end,  d->end(parent),    parent);

    } else if (dynamic_cast<dtkComposerNodeLeaf *>(node)) { // Leaf node
        if ( parent && dynamic_cast<dtkComposerNodeControl *>(parent)) {
            // header or footer node, add it to control_nodes hash (will be used in addEdge)
            d->control_nodes.insert(node,parent);
            return;
        }
        dtkComposerGraphNode *leaf = new dtkComposerGraphNodeLeaf(node,node->nodeMetaData()->title());
        d->addNode(node, leaf,  d->begin(parent));

        // if composite was empty, need to remove dummy edge
        if (d->dummy_edges.values(parent).count() == 1) {
            d->removeDummyEdge(  d->begin(parent), d->end(parent), parent);
        }
        d->addDummyEdge(  d->begin(parent), leaf, parent);
        d->addDummyEdge(  leaf,  d->end(parent),  parent);

    } else if (dtkComposerNodeComposite *composite = dynamic_cast<dtkComposerNodeComposite *>(node)) {
        QString beginTitle;
        QString endTitle;
        if (parent) { // parent is NULL for root {
            beginTitle = "Begin"+ node->nodeMetaData()->title();
            endTitle = "End"+ node->nodeMetaData()->title();
        } else {
            beginTitle = "BeginRoot";
            endTitle = "EndRoot";
        }
        begin = new dtkComposerGraphNodeBegin(node,beginTitle);
        end   = new dtkComposerGraphNodeEnd(node,endTitle);
        begin->setKind(dtkComposerGraphNode::BeginComposite) ;
        begin->setEnd(end);
        begin->setGraph(this);
        end->setBegin(begin);
        d->addNode(node, begin, d->begin(parent));
        d->addNode(node, end, d->begin(parent));
        // empty composite, add dummy edge between 'begin' and 'end'
        d->addDummyEdge( begin, end, node);
        if (parent) {
            if ( dynamic_cast<dtkComposerNodeControl *>(parent)) {
                d->control_nodes.insert(node,parent);
            } else {
                d->removeDummyEdge(  d->begin(parent), d->end(parent), parent);
                d->addDummyEdge(  d->begin(parent), begin, parent);
                d->addDummyEdge(  end,  d->end(parent),    parent);
            }
        }
    }
}

void dtkComposerGraph::removeNode(dtkComposerNode *node, dtkComposerNode *parent)
{
//    dtkTrace() << "removing node" << node->nodeMetaData()->title();
    // For control nodes, we have to remove its blocks and then it's pending dummy edges
    if (dtkComposerNodeControl *control = dynamic_cast<dtkComposerNodeControl *>(node)) {

        //remove dummy edges for this
        foreach(dtkComposerGraphEdge *e, d->dummy_edges.values(node))
            d->remDummyEdge(e, node);

        int blockCount = control->blockCount();
        for (int i = 0; i < blockCount; ++i) {
            this->removeNode(control->block(i), control);
        }
        foreach (dtkComposerNode *n, d->control_nodes.keys(node) ) {
            d->control_nodes.remove(n);
        }
    }

    if (!dynamic_cast<dtkComposerNodeControl *>(parent)) {
        // remove dummy edges for this node on the parent
        dtkComposerGraphNode *parent_begin = d->begin(parent);
        dtkComposerGraphNode *parent_end   = d->end(parent);

        foreach( dtkComposerGraphEdge *e, d->dummy_edges.values(parent)) {
            if ((e->source() == parent_begin && e->destination() == d->begin(node) ) || (e->destination() == parent_end && e->source() == d->end(node)))
                d->remDummyEdge(e, parent);
        }
        // if parent composite is empty after removal, add back dummy edge
        if (d->dummy_edges.values(parent).count() == 0) {
            d->addDummyEdge(  parent_begin, parent_end, parent);
        }
    } else {
        d->control_nodes.remove(node);
    }
    if (dynamic_cast<dtkComposerNodeComposite *>(node)) {
        foreach(dtkComposerGraphEdge *e, d->dummy_edges.values(node))
            d->remDummyEdge(e, node);
    }

    foreach(dtkComposerGraphNode *n, d->nodes.values(node)) {
        if (dynamic_cast<dtkComposerNodeControl *>(node) && !(dynamic_cast<dtkComposerGraphNodeBegin *>(n) || dynamic_cast<dtkComposerGraphNodeEnd *>(n) ))
            d->remNode(node, n, d->begin(node));
        else
            d->remNode(node, n, d->begin(parent));
    }
    d->nodes.remove(node);
}

void dtkComposerGraph::addBlock(dtkComposerNode *node)
{
    dtkComposerGraphNode *inputs_block = new dtkComposerGraphNodeSetInputs(node);
    if (dtkComposerNodeControlCase * caseNode = dynamic_cast<dtkComposerNodeControlCase *>(node)) {
        int blockCount = caseNode->blockCount();
        dtkComposerNode *last = caseNode->block(blockCount-1);
        d->addNode(last, inputs_block, d->begin(node));
        this->addNode(last, node);
        dtkComposerGraphNode *select = NULL;
        dtkComposerGraphNode *outputs = NULL;
        foreach(dtkComposerGraphNode *n, d->nodes.values(node)) {
            if (dynamic_cast<dtkComposerGraphNodeSelectBranch *>(n) )
                select = n;
            if (dynamic_cast<dtkComposerGraphNodeSetOutputs *>(n) )
                outputs = n;
        }
        d->addDummyEdge(select,       inputs_block,           last, blockCount-1);
        d->addDummyEdge(inputs_block, d->begin(last),last);
        d->addDummyEdge(d->end(last), outputs,       last);
        d->end(last)->setEndLoop();
    } else  {
        dtkInfo() << "addGroup called on unsupported node" << node->nodeMetaData()->title();
        return;
    }
}

void dtkComposerGraph::removeBlock(dtkComposerNode *node, dtkComposerNode *parent)
{
    foreach(dtkComposerGraphEdge *e, d->dummy_edges.values(node))
        d->remDummyEdge(e, node);
    foreach(dtkComposerGraphNode *n, d->nodes.values(node))
        if (dynamic_cast<dtkComposerGraphNodeSetInputs *>(n))
            d->remNode(node, n, d->begin(parent));
    this->removeNode(node, parent);
}

void dtkComposerGraph::reparentNode(dtkComposerNode *node, dtkComposerNode *oldparent, dtkComposerNode *newparent)
{
    // remove dummy edges for this node on the parent

    dtkComposerGraphNode *oldparent_g = d->begin(oldparent);
    dtkComposerGraphNode *newparent_g = d->begin(newparent);

    oldparent_g->removeChild(d->begin(node));
    newparent_g->addChild(d->begin(node));
    if (d->begin(node) != d->end(node)) { // not a leaf node
        oldparent_g->removeChild(d->end(node));
        newparent_g->addChild(d->end(node));
    }

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

void dtkComposerGraph::addEdge(dtkComposerNode *source, dtkComposerNode *destination, QString src_type, QString dst_type)
{
    dtkComposerGraphNode *src;
    dtkComposerGraphNode *dst;

    bool src_control = d->control_nodes.contains(source);
    bool dst_control = d->control_nodes.contains(destination);

    if ((src_control || dynamic_cast<dtkComposerNodeComposite *>(source) ) && src_type == "input") {
//        src = d->begin(source);
        // input inside a composite, there is already a dummy edge
        return;
    } else if (src_control) {
        src = d->end(d->control_nodes.value(source));
    } else {
        src = d->end(source);
    }
    if ((dst_control || dynamic_cast<dtkComposerNodeComposite *>(destination) ) && dst_type == "output") {
        // output inside a composite, there is already a dummy edge
//        dst = d->end(destination);
        return;
    } else if (dst_control) {
        dst = d->begin(d->control_nodes.value(destination));
    } else {
        dst = d->begin(destination);
    }

    dtkComposerGraphEdge *edge = new dtkComposerGraphEdge;
    QPair<dtkComposerNode *,dtkComposerNode *> pair = qMakePair(source, destination);

    if (d->edges.contains(pair)) {
        d->edges_count[pair]++;
    } else {
        d->edges_count.insert(pair,1);
        foreach( dtkComposerGraphEdge *e, d->dummy_edges.values()) {
            if ((e->source() == src ) || (e->destination() == dst)) {
                dtkTrace() << " remove dummy edge because of addEdge" << e->source()->title() << e->destination()->title() ;
                d->remDummyEdge(e,d->dummy_edges.key(e));
            }
        }
        edge->setSource(src);
        edge->setDestination(dst);

        src->addSuccessor(dst);
        dst->addPredecessor(src);

        d->edges.insert(pair, edge);
    }
}

void dtkComposerGraph::removeEdge(dtkComposerNode *source, dtkComposerNode *destination, QString src_type, QString dst_type, dtkComposerNode *parent)
{

//    dtkTrace() << "remove edge" << source->nodeMetaData()->title() << destination->nodeMetaData()->title() <<    d->edges.count()  <<  src_type << dst_type;

    QPair<dtkComposerNode *,dtkComposerNode *> pair = qMakePair(source, destination);

    if (d->edges_count.value(pair,0) > 1) {
        d->edges_count[pair]--;
        return;
    }

    dtkComposerGraphNode *src;
    dtkComposerGraphNode *dst;

    bool src_control = d->control_nodes.contains(source);
    bool dst_control = d->control_nodes.contains(destination);

    if ((src_control || dynamic_cast<dtkComposerNodeComposite *>(source) ) && src_type == "input") {
        // input inside a composite, there is a dummy edge
        return;
    } else if (src_control) {
        src = d->end(d->control_nodes.value(source));
    } else {
        src = d->end(source);
    }
    if ((dst_control || dynamic_cast<dtkComposerNodeComposite *>(destination) ) && dst_type == "output") {
        // output inside a composite, there is a dummy edge
        return;
    } else if (dst_control) {
        dst = d->begin(d->control_nodes.value(destination));
    } else {
        dst = d->begin(destination);
    }

    d->edges.remove(pair);
    d->edges_count.remove(pair);

    // if destination has edges on its input, don't add a dummy edge
    bool doit = true;
    foreach(dtkComposerGraphEdge *e, d->edges.values())
        doit = doit && (e->destination() !=  dst);
    if (doit) {
        dtkTrace() << "add dummy edge from source parent to destination ";
        d->addDummyEdge(  d->begin(parent), dst, parent);
    }

    doit = true;
    // if source has edges on its output, don't add a dummy edge
    foreach(dtkComposerGraphEdge *e, d->edges.values())
        doit = doit && (e->source() !=  src);
    if (doit) {
        dtkTrace() << "add dummy edge from source to destination parent ";
        d->addDummyEdge( src, d->end(parent), parent);
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
        if ((n = node)) {
            d->nodes.remove(d->nodes.key(n));
        }
}

void dtkComposerGraph::removeEdge(dtkComposerGraphEdge *edge)
{
    foreach(dtkComposerGraphEdge *e, d->edges.values())
        if ((e = edge)) {
            d->edges.remove(d->edges.key(e));
        }
}

// export as dot format in a string.
QString dtkComposerGraph::toString(void)
{
    QStringList txt;
    txt <<"digraph dtkComposerGraph {";
    foreach(dtkComposerGraphEdge *e, d->edges.values()) {
        txt << e->source()->objectName() + " -> "+ e->destination()->objectName();
    }
    foreach(dtkComposerGraphEdge *e, d->dummy_edges.values()) {
        txt << e->source()->objectName() + " -> "+ e->destination()->objectName();
    }
    txt << "}";
    return txt.join("\n");
}

void dtkComposerGraph::clear(void)
{
    d->dummy_edges.clear();
    foreach(dtkComposerGraphEdge *e, d->edges.values()) {
        delete e;
        e = NULL;
    }
    d->edges.clear();

    foreach(dtkComposerGraphNode *n, d->nodes.values()) {
        delete n;
        n = NULL;
    }
    d->nodes.clear();
    d->control_nodes.clear();
    d->edges_count.clear();
    emit cleared();
}

dtkGraph dtkComposerGraph::graph(void)
{
    dtkGraph g;
    foreach(dtkComposerGraphNode *node, d->nodes.values() ) {
        g.addNode(node);
    }
    foreach(dtkComposerGraphEdge *edge, d->edges.values() ) {
        dtkGraphEdge e;
        e.setSource(edge->source());
        e.setDestination(edge->destination());
        g.addEdge(e);
    }
    foreach(dtkComposerGraphEdge *edge, d->dummy_edges.values() ) {
        dtkGraphEdge e;
        e.setSource(edge->source());
        e.setDestination(edge->destination());
        g.addEdge(e);
    }
    return g;
}

dtkGraph dtkComposerGraph::subgraph(dtkComposerGraphNode *from, dtkComposerGraphNode *to)
{
//    dtkTrace() << "generate dtk graph from composer graph";
    dtkGraph g = this->graph();

    dtkGraph sg = g.subgraph(from, to);
    // remove nested nodes: keep only child nodes of from
    dtkComposerGraphNodeList childs = from->childs();

    // check all childs if they are BeginControl; if yes, need to remove subgraph of control from the current subgraph
    foreach(dtkComposerGraphNode *n, childs ) {
//        dtkTrace() << "check child node" << n->title();
        if (n->kind() == dtkComposerGraphNode::BeginLoop || n->kind() == dtkComposerGraphNode::BeginIf) {
//            dtkTrace() << "begin loop/if" ;
            QObject *end = static_cast<dtkComposerGraphNodeBegin *>(n)->end();
            dtkGraph sg_control = g.subgraph(n, end );
            foreach(QObject *o, sg_control.nodes()) {
                if (o != n && o != end) {
                    sg.deleteNode(o);
                }
            }
            dtkGraphEdge e(n, end) ;
            sg.addEdge(e); // add edge between begin and end control
        } else if (n->endloop()) {
             sg.deleteEdge(dtkGraphEdge(n, sg.succcessors(n)[0]));
        } else if (n->kind() == dtkComposerGraphNode::BeginComposite ) {
            // need to check also childs of composite
//            dtkTrace() << "need to check childs of composite" ;
            dtkComposerGraphNode *end = static_cast<dtkComposerGraphNodeBegin *>(n)->end();
            dtkGraph ssg = subgraph(n, end); //recursive call
            dtkGraph full_ssg = sg.subgraph(n, end);

            bool removed =false;
            foreach(QObject *o, full_ssg.nodes()) {
                if (!ssg.contains(o) && sg.contains(o) && o != n && o != end) {
//                    dtkTrace() << "removing" << o->objectName();
                    removed = true;
                    sg.deleteNode(o);
                }
            }
            if (removed) {
//                dtkTrace() << "ssg edges count:" << ssg.edges().count();
                for (int i =0; i < ssg.edges().count(); ++i) {
                    if (!sg.edges().contains(ssg.edges().at(i))) {
                        sg.addEdge( ssg.edges().at(i)); // add edge between begin and end control
                    }
                }
            }
        }
    }


    sg.deleteNode(from);
    sg.deleteNode(to);

    // dtkTrace() << sg.description();
    return sg;
}

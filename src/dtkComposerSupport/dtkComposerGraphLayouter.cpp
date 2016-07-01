/* dtkComposerGraphLayouter.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb 10 10:17:18 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 24 14:47:01 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 493
 */

/* Commentary:
 *
 * - removeCycle: greedy cycle removal algorithm
 */

/* Change log:
 *
 */

#include "dtkComposerGraph.h"
#include "dtkComposerGraphEdge.h"
#include "dtkComposerGraphLayouter.h"
#include "dtkComposerGraphNode.h"

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

dtkComposerGraphNodeList sort(dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges);

dtkComposerGraphNode *isolated(dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges);
dtkComposerGraphNode *source(dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges);
dtkComposerGraphNode *sink(dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges);

int i_degree(dtkComposerGraphNode *node, dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges);
int o_degree(dtkComposerGraphNode *node, dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges);

void reverse(dtkComposerGraphEdge *edge);

dtkComposerGraphEdgeList  inset(dtkComposerGraphNode *node, dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges);
dtkComposerGraphEdgeList outset(dtkComposerGraphNode *node, dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges);

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphLayouterPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphLayouterPrivate
{
public:
    dtkComposerGraphNodeList node_list;
    dtkComposerGraphEdgeList edge_list;

public:
    dtkComposerGraphEdgeList feedback;
    dtkComposerGraphEdgeList reversed;

public:
    QHash<dtkComposerGraphNode *, int> layers;

public:
    void layout(void);

public:
    void removeCycles(void);
    void assignLayers(void);
    void createDummys(void);
    void assignPostns(void);
    void createCycles(void);
};

void dtkComposerGraphLayouterPrivate::layout(void)
{
    this->removeCycles();
    this->assignLayers();
    this->createDummys();
    this->assignPostns();
    this->createCycles();
}

void dtkComposerGraphLayouterPrivate::removeCycles(void)
{
    dtkComposerGraphNodeList nodes = this->node_list;
    dtkComposerGraphEdgeList edges = this->edge_list;

    this->reversed = edges;

    while(nodes.count()) {

        // Handle sink nodes

        while(dtkComposerGraphNode *s = sink(nodes, edges)) {

            foreach(dtkComposerGraphEdge *edge, inset(s, nodes, edges)) {
                this->feedback << edge;
                this->reversed.removeAll(edge);
                edges.removeAll(edge);
            }
        }

        // Handle isolated nodes

        while(dtkComposerGraphNode *i = isolated(nodes, edges)) {
            nodes.removeAll(i);
        }

        // Handle source nodes

        while(dtkComposerGraphNode *s = source(nodes, edges)) {

            foreach(dtkComposerGraphEdge *edge, outset(s, nodes, edges)) {
                this->feedback << edge;
                this->reversed.removeAll(edge);
                edges.removeAll(edge);
            }
        }

        // Handle connected nodes

        if(nodes.count()) {

            dtkComposerGraphNode *m = nodes.first();

            foreach(dtkComposerGraphNode *n, nodes)
                if(o_degree(n, nodes, edges) - i_degree(n, nodes, edges) > o_degree(m, nodes, edges) - i_degree(m, nodes, edges))
                    m = n;

            foreach(dtkComposerGraphEdge *e, outset(m, nodes, edges)) {
                this->feedback << e;
                this->reversed.removeAll(e);
                edges.removeAll(e);
            }

            foreach(dtkComposerGraphEdge *e, inset(m, nodes, edges)) {
                edges.removeAll(e);
            }

            nodes.removeAll(m);
        }
    }

    foreach(dtkComposerGraphEdge *edge, this->reversed)
        reverse(edge);
}

void dtkComposerGraphLayouterPrivate::assignLayers(void)
{
    dtkComposerGraphNodeList nodes = this->node_list;
    dtkComposerGraphEdgeList edges = this->edge_list;

    QList<dtkComposerGraphNode *> sortd = sort(nodes, edges);

    foreach(dtkComposerGraphNode *node, sortd)
        this->layers.insert(node, 1);

    int height = 1;

    foreach(dtkComposerGraphNode *u, sortd) {
        foreach(dtkComposerGraphEdge *edge, outset(u, nodes, edges)) {
            dtkComposerGraphNode *v = edge->destination();
            this->layers[v] = qMax(this->layers[v], this->layers[u]+1);
            height = qMax(height, this->layers[v]);
        }
    }
}

void dtkComposerGraphLayouterPrivate::createDummys(void)
{

}

void dtkComposerGraphLayouterPrivate::assignPostns(void)
{
    dtkComposerGraphNodeList nodes = this->node_list;
    dtkComposerGraphEdgeList edges = this->edge_list;

    // y-coordinate assignment

    foreach(dtkComposerGraphNode *n, layers.keys())
        n->setPos(QPointF(n->pos().x(), layers[n] * 2 * n->boundingRect().height()));

    // x-coordinate assignment (left aligned)

    QHash<int, int> layer_count;
    QHash<int, qreal> layer_width;

    int max_layer = 0;
    qreal max_width = 0.0;

    foreach(dtkComposerGraphNode *n, nodes) {

        int layer = this->layers[n];

        if(!layer_count.contains(layer))
            layer_count.insert(layer, 0);
        else
            layer_count[layer] = layer_count[layer]+1;

        n->setPos(QPointF(2*n->boundingRect().width()*layer_count[layer], n->pos().y()));

        layer_width[layer] = n->sceneBoundingRect().right();

        if(layer_width[layer] > max_width) {
            max_width = layer_width[layer];
            max_layer = layer;
        }
    }

    // x-coordinate assignment (center aligned)

    foreach(dtkComposerGraphNode *n, nodes)
        if(this->layers[n] != max_layer)
            n->setPos(n->pos() + QPointF((max_width-layer_width[this->layers[n]])/2.0, 0));
}

void dtkComposerGraphLayouterPrivate::createCycles(void)
{
    foreach(dtkComposerGraphEdge *edge, this->reversed)
        reverse(edge);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphLayouter
// /////////////////////////////////////////////////////////////////

dtkComposerGraphLayouter::dtkComposerGraphLayouter(void) : d(new dtkComposerGraphLayouterPrivate)
{

}

dtkComposerGraphLayouter::~dtkComposerGraphLayouter(void)
{
    delete d;

    d = NULL;
}

void dtkComposerGraphLayouter::setGraph(dtkComposerGraph *graph)
{
    d->node_list = graph->nodes();
    d->edge_list = graph->edges();
}

void dtkComposerGraphLayouter::layout(void)
{
    d->layout();
}

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

dtkComposerGraphNodeList sort(dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges)
{
    dtkComposerGraphNodeList node_list = nodes;
    dtkComposerGraphEdgeList edge_list = edges;

    dtkComposerGraphNodeList nodel;
    dtkComposerGraphNodeList sortd;

    foreach(dtkComposerGraphNode *node, node_list)
        if(!(inset(node, node_list, edge_list).count()))
            nodel << node;

    while(!nodel.isEmpty()) {

        dtkComposerGraphNode *n = nodel.takeFirst(); sortd << n;

        foreach(dtkComposerGraphEdge *edge, outset(n, node_list, edge_list)) {

            dtkComposerGraphNode *m = edge->destination();

            edge_list.removeAll(edge);

            if(inset(m, node_list, edge_list).count() == 0)
                nodel << m;
        }
    }

    return sortd;
}

dtkComposerGraphNode *isolated(dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges)
{
    foreach(dtkComposerGraphNode *node, nodes) {
        if(!inset(node, nodes, edges).count() && !outset(node, nodes, edges).count()) {
            nodes.removeAll(node);
            return node;
        }
    }

    return NULL;
}

dtkComposerGraphNode *source(dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges)
{
    foreach(dtkComposerGraphNode *node, nodes) {
        if(!inset(node, nodes, edges).count() && outset(node, nodes, edges).count()) {
            nodes.removeAll(node);
            return node;
        }
    }

    return NULL;
}

dtkComposerGraphNode *sink(dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges)
{
    foreach(dtkComposerGraphNode *node, nodes) {
        if(inset(node, nodes, edges).count() && !outset(node, nodes, edges).count()) {
            nodes.removeAll(node);
            return node;
        }
    }

    return NULL;
}

int i_degree(dtkComposerGraphNode *node, dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges)
{
    int degree = 0;

    foreach(dtkComposerGraphEdge *edge, edges)
        if(edge->destination() == node)
            degree++;

    return degree;
}

int o_degree(dtkComposerGraphNode *node, dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges)
{
    int degree = 0;

    foreach(dtkComposerGraphEdge *edge, edges)
        if(edge->source() == node)
            degree++;

    return degree;
}

void reverse(dtkComposerGraphEdge *edge)
{
    dtkComposerGraphNode *t = edge->source();

    edge->setSource(edge->destination());
    edge->setDestination(t);
}

dtkComposerGraphEdgeList inset(dtkComposerGraphNode *node, dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges)
{
    dtkComposerGraphEdgeList list;

    foreach(dtkComposerGraphEdge *edge, edges)
        if(edge->destination() == node)
            list << edge;

    return list;
}

dtkComposerGraphEdgeList outset(dtkComposerGraphNode *node, dtkComposerGraphNodeList& nodes, dtkComposerGraphEdgeList& edges)
{
    dtkComposerGraphEdgeList list;

    foreach(dtkComposerGraphEdge *edge, edges)
        if(edge->source() == node)
            list << edge;

    return list;
}

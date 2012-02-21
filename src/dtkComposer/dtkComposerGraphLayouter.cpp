/* dtkComposerGraphLayouter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb 10 10:17:18 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr. 21 13:26:48 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 409
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

dtkComposerGraphNodeList sort(const dtkComposerGraph& graph);

dtkComposerGraphNode *isolated(dtkComposerGraph& graph);
dtkComposerGraphNode *source(dtkComposerGraph& graph);
dtkComposerGraphNode *sink(dtkComposerGraph& graph);

int i_degree(dtkComposerGraphNode *node, dtkComposerGraph& graph);
int o_degree(dtkComposerGraphNode *node, dtkComposerGraph& graph);

void reverse(dtkComposerGraphEdge *edge);

dtkComposerGraphEdgeList  inset(dtkComposerGraphNode *node, dtkComposerGraph& graph);
dtkComposerGraphEdgeList outset(dtkComposerGraphNode *node, dtkComposerGraph& graph);

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphLayouterPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphLayouterPrivate
{
public:
    dtkComposerGraph *graph;

    dtkComposerGraphEdgeList feedback;
    dtkComposerGraphEdgeList reversed;

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
    if(!this->graph)
        return;

    dtkComposerGraph g(*(this->graph));

    this->reversed = g.edges();

    while(g.nodes().count()) {

        // Handle sink nodes

        while(dtkComposerGraphNode *s = sink(g)) {

            foreach(dtkComposerGraphEdge *edge, inset(s, g)) {
                this->feedback << edge;
                this->reversed.removeAll(edge);
                g.removeEdge(edge);
            }
        }

        // Handle isolated nodes

        while(dtkComposerGraphNode *i = isolated(g)) {
            g.removeNode(i);
        }

        // Handle source nodes

        while(dtkComposerGraphNode *s = source(g)) {

            foreach(dtkComposerGraphEdge *edge, outset(s, g)) {
                this->feedback << edge;
                this->reversed.removeAll(edge);
                g.removeEdge(edge);
            }
        }

        // Handle connected nodes

        if(g.nodes().count()) {

            dtkComposerGraphNode *m = g.nodes().first();

            foreach(dtkComposerGraphNode *n, g.nodes())
                if(o_degree(n, g) - i_degree(n, g) > o_degree(m, g) - i_degree(m, g))
                    m = n;

            foreach(dtkComposerGraphEdge *e, outset(m, g)) {
                this->feedback << e;
                this->reversed.removeAll(e);
                g.removeEdge(e);
            }

            foreach(dtkComposerGraphEdge *e, inset(m, g)) {
                g.removeEdge(e);
            }
            
            g.removeNode(m);
        }
    }

    foreach(dtkComposerGraphEdge *edge, this->reversed)
        reverse(edge);

//     qDebug() << __func__ << this->reversed.count() << "edges reversed";
}

void dtkComposerGraphLayouterPrivate::assignLayers(void)
{
    if(!this->graph)
        return;

    dtkComposerGraph g(*(this->graph));

    QList<dtkComposerGraphNode *> nodes = sort(g);

    foreach(dtkComposerGraphNode *node, nodes)
        this->layers.insert(node, 1);

    int height = 1;

    foreach(dtkComposerGraphNode *u, nodes) {
        foreach(dtkComposerGraphEdge *edge, outset(u, g)) {
            dtkComposerGraphNode *v = edge->destination();
            this->layers[v] = qMax(this->layers[v], this->layers[u]+1);
            height = qMax(height, this->layers[v]);
        }
    }

    // qDebug() << __func__ << "Layout height is" << height;
}

void dtkComposerGraphLayouterPrivate::createDummys(void)
{

}

void dtkComposerGraphLayouterPrivate::assignPostns(void)
{
    if(!this->graph)
        return;
    
    dtkComposerGraph g(*(this->graph));

    // y-coordinate assignment

    foreach(dtkComposerGraphNode *n, layers.keys())
        n->setPos(QPointF(n->pos().x(), layers[n] * 2 * n->boundingRect().height()));

    // x-coordinate assignment (left aligned)

    QHash<int, int> layer_count;
    QHash<int, qreal> layer_width;

    int max_layer = 0;
    qreal max_width = 0.0;

    foreach(dtkComposerGraphNode *n, g.nodes()) {

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

    foreach(dtkComposerGraphNode *n, g.nodes())
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
    d->graph = NULL;
}

dtkComposerGraphLayouter::~dtkComposerGraphLayouter(void)
{
    delete d;

    d = NULL;
}

void dtkComposerGraphLayouter::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
}

void dtkComposerGraphLayouter::layout(void)
{
    d->layout();
}

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

dtkComposerGraphNodeList sort(const dtkComposerGraph& graph)
{
    dtkComposerGraph g(graph);

    dtkComposerGraphNodeList nodes;
    dtkComposerGraphNodeList sortd;

    foreach(dtkComposerGraphNode *node, g.nodes())
        if(!(inset(node, g).count()))
            nodes << node;

    // qDebug() << __func__ << nodes.count() << "nodes to be sorted";

    while(!nodes.isEmpty()) {

        dtkComposerGraphNode *n = nodes.takeFirst(); sortd << n;

        foreach(dtkComposerGraphEdge *edge, outset(n, g)) {

            dtkComposerGraphNode *m = edge->destination();
            
            g.removeEdge(edge);

            if(inset(m, g).count() == 0)
                nodes << m;
        }
    }

    // qDebug() << __func__ << sortd.count() << "nodes sorted";

    return sortd;
}

dtkComposerGraphNode *isolated(dtkComposerGraph& graph)
{
    foreach(dtkComposerGraphNode *node, graph.nodes()) {
        if(!inset(node, graph).count() && !outset(node, graph).count()) {
            graph.removeNode(node);
            return node;
        }
    }

    return NULL;
}

dtkComposerGraphNode *source(dtkComposerGraph& graph)
{
    foreach(dtkComposerGraphNode *node, graph.nodes()) {
        if(!inset(node, graph).count() && outset(node, graph).count()) {
            graph.removeNode(node);
            return node;
        }
    }

    return NULL;
}

dtkComposerGraphNode *sink(dtkComposerGraph& graph)
{
    foreach(dtkComposerGraphNode *node, graph.nodes()) {
        if(inset(node, graph).count() && !outset(node, graph).count()) {
            graph.removeNode(node);
            return node;
        }
    }

    return NULL;
}

int i_degree(dtkComposerGraphNode *node, dtkComposerGraph& graph)
{
    int degree = 0;

    foreach(dtkComposerGraphEdge *edge, graph.edges())
        if(edge->destination() == node)
            degree++;

    return degree;
}

int o_degree(dtkComposerGraphNode *node, dtkComposerGraph& graph)
{
    int degree = 0;

    foreach(dtkComposerGraphEdge *edge, graph.edges())
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

dtkComposerGraphEdgeList inset(dtkComposerGraphNode *node, dtkComposerGraph& graph)
{
    dtkComposerGraphEdgeList edges;

    foreach(dtkComposerGraphEdge *edge, graph.edges())
        if(edge->destination() == node)
            edges << edge;

    return edges;
}

dtkComposerGraphEdgeList outset(dtkComposerGraphNode *node, dtkComposerGraph& graph)
{
    dtkComposerGraphEdgeList edges;

    foreach(dtkComposerGraphEdge *edge, graph.edges())
        if(edge->source() == node)
            edges << edge;

    return edges;
}

/* dtkComposerSceneNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:01:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Feb  4 14:52:19 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNode_p.h"
#include "dtkComposerScenePort.h"

dtkComposerSceneNode::dtkComposerSceneNode(void) : QGraphicsItem(), d(new dtkComposerSceneNodePrivate)
{
    d->parent = NULL;

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

dtkComposerSceneNode::~dtkComposerSceneNode(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNode::addInputEdge(dtkComposerSceneEdge *edge)
{
    d->input_edges << edge;
}

void dtkComposerSceneNode::addOutputEdge(dtkComposerSceneEdge *edge)
{
    d->output_edges << edge;
}

void dtkComposerSceneNode::removeInputEdge(dtkComposerSceneEdge *edge)
{
    d->input_edges.removeAll(edge);
}

void dtkComposerSceneNode::removeOutputEdge(dtkComposerSceneEdge *edge)
{
    d->output_edges.removeAll(edge);
}

QList<dtkComposerSceneEdge *> dtkComposerSceneNode::inputEdges(void)
{
    return d->input_edges;
}

QList<dtkComposerSceneEdge *> dtkComposerSceneNode::outputEdges(void)
{
    return d->output_edges;
}

dtkComposerScenePort *dtkComposerSceneNode::port(unsigned int id)
{
    dtkComposerScenePort *p = NULL;

    foreach(dtkComposerScenePort *port, d->input_ports)
        if (port->id() == id)
            p = port;

    foreach(dtkComposerScenePort *port, d->output_ports)
        if (port->id() == id)
            p = port;

    return p;
}

void dtkComposerSceneNode::setParent(dtkComposerSceneNode *parent)
{
    d->parent = parent;
}

QList<dtkComposerScenePort *> dtkComposerSceneNode::inputPorts(void)
{
    return d->input_ports;
}

QList<dtkComposerScenePort *> dtkComposerSceneNode::outputPorts(void)
{
    return d->output_ports;
}

dtkComposerSceneNode *dtkComposerSceneNode::parent(void)
{
    return d->parent;
}

// QVariant dtkComposerSceneNode::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
// {
//     if(change == QGraphicsItem::ItemSelectedHasChanged) {

//         if(value.toBool()) {
//             ; // TO SELECTED STATE
//         } else {
//             ; // TO UNUSELECTED STATE
//         }
//     }

//     return QGraphicsItem::itemChange(change, value);
// }

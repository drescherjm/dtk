/* dtkComposerSceneNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:01:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. janv.  9 15:17:10 2015 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 99
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNode_p.h"

dtkComposerSceneNode::dtkComposerSceneNode(void) : QGraphicsItem(), d(new dtkComposerSceneNodePrivate)
{
    d->wrapee = NULL;
    d->parent = NULL;
    d->embedded = false;

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

dtkComposerSceneNode::~dtkComposerSceneNode(void)
{
    delete d;
}

void dtkComposerSceneNode::setParent(dtkComposerSceneNode *parent)
{
    d->parent = parent;
}

dtkComposerSceneNode *dtkComposerSceneNode::parent(void)
{
    return d->parent;
}

void dtkComposerSceneNode::wrap(dtkComposerNode *wrapee)
{
    d->wrapee = wrapee;

    d->title = wrapee->titleHint();
}

dtkComposerNode *dtkComposerSceneNode::wrapee(void)
{
    return d->wrapee;
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

dtkComposerSceneEdgeList dtkComposerSceneNode::inputEdges(void)
{
    return d->input_edges;
}

dtkComposerSceneEdgeList dtkComposerSceneNode::outputEdges(void)
{
    return d->output_edges;
}

int dtkComposerSceneNode::addInputPort(dtkComposerScenePort *port)
{
    d->input_ports << port;
    return d->input_ports.size() - 1;
}

void dtkComposerSceneNode::addOutputPort(dtkComposerScenePort *port)
{
    d->output_ports << port;
}

void dtkComposerSceneNode::removeInputPort(dtkComposerScenePort *port)
{
    d->input_ports.removeAll(port);
}

void dtkComposerSceneNode::removeOutputPort(dtkComposerScenePort *port)
{
    d->output_ports.removeAll(port);
}

dtkComposerScenePortList dtkComposerSceneNode::inputPorts(void)
{
    return d->input_ports;
}

dtkComposerScenePortList dtkComposerSceneNode::outputPorts(void)
{
    return d->output_ports;
}

const QString& dtkComposerSceneNode::title(void)
{
    return d->title;
}

void dtkComposerSceneNode::setTitle(const QString& title)
{
    d->title = title;
}

bool dtkComposerSceneNode::embedded(void)
{
    return d->embedded;
}

void dtkComposerSceneNode::setEmbedded(bool embedded)
{
    d->embedded = embedded;
}

// QVariant dtkComposerSceneNode::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
// {
//     if(change == QGraphicsItem::ItemSelectedHasChanged) {
//
//         if(value.toBool()) {
//             ; // TO SELECTED STATE
//         } else {
//             ; // TO UNUSELECTED STATE
//         }
//     }
//
//     return QGraphicsItem::itemChange(change, value);
// }

/* dtkComposerSceneNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:01:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 23:46:49 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 58
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
#include "dtkComposerScenePort.h"

#include <dtkCore/dtkGlobal>

dtkComposerSceneNode::dtkComposerSceneNode(void) : QGraphicsItem(), d(new dtkComposerSceneNodePrivate)
{
    d->wrapee = NULL;
    d->parent = NULL;

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

dtkComposerSceneNode::~dtkComposerSceneNode(void)
{
    delete d;

    d = NULL;
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

QList<dtkComposerSceneEdge *> dtkComposerSceneNode::inputEdges(void)
{
    return d->input_edges;
}

QList<dtkComposerSceneEdge *> dtkComposerSceneNode::outputEdges(void)
{
    return d->output_edges;
}

void dtkComposerSceneNode::addInputPort(dtkComposerScenePort *port)
{
    d->input_ports << port;
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

QList<dtkComposerScenePort *> dtkComposerSceneNode::inputPorts(void)
{
    return d->input_ports;
}

QList<dtkComposerScenePort *> dtkComposerSceneNode::outputPorts(void)
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

void dtkComposerSceneNode::setParent(dtkComposerSceneNodeComposite *parent)
{
    d->parent = parent;
}

dtkComposerSceneNodeComposite *dtkComposerSceneNode::parent(void)
{
    return d->parent;
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

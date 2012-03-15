/* dtkComposerGraphNode.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:09:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. mars 13 13:27:22 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 130
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkGlobal.h>

#include "dtkComposerGraphEdge.h"
#include "dtkComposerGraphNode.h"

class dtkComposerGraphNodePrivate
{
public:
    QString title;

public:
    QList<dtkComposerGraphNode *> successors;
    QList<dtkComposerGraphNode *> predecessors;

public:
    dtkComposerGraphNode::Status status;
};

dtkComposerGraphNode::dtkComposerGraphNode() : QGraphicsItem(),d(new dtkComposerGraphNodePrivate)
{
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setZValue(1);
    this->setTitle("Graph node");
    this->setStatus(dtkComposerGraphNode::Ready);
}

dtkComposerGraphNode::~dtkComposerGraphNode(void)
{
    delete d;

    d = NULL;
}

dtkComposerNode *dtkComposerGraphNode::wrapee(void)
{
    return NULL;
}


dtkComposerGraphNode::Status dtkComposerGraphNode::status(void)
{
    return d->status;
}

void dtkComposerGraphNode::setStatus(dtkComposerGraphNode::Status status)
{
    d->status = status;
}

QRectF dtkComposerGraphNode::boundingRect(void) const
{
    return QRectF(0, 0, 125, 25);
}

void dtkComposerGraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(this->isSelected())
        painter->setPen(Qt::red);
    else
        painter->setPen(Qt::black);
    if (d->status == Done)
        painter->setBrush(Qt::green);
    else
        painter->setBrush(Qt::white);
    painter->drawRect(this->boundingRect());
    painter->drawText(this->boundingRect(), Qt::AlignCenter, d->title);
}

void dtkComposerGraphNode::addSuccessor(dtkComposerGraphNode *node, int id)
{
    d->successors << node;
}

void dtkComposerGraphNode::addPredecessor(dtkComposerGraphNode *node)
{
    d->predecessors << node;
}

void dtkComposerGraphNode::removePredecessor(dtkComposerGraphNode *node)
{
    d->predecessors.removeOne(node);
}

void dtkComposerGraphNode::removeSuccessor(dtkComposerGraphNode *node)
{
    d->successors.removeOne(node);
}

dtkComposerGraphNodeList dtkComposerGraphNode::successors(void)
{
    return d->successors;
}

dtkComposerGraphNodeList dtkComposerGraphNode::predecessors(void)
{
    return d->predecessors;
}


const QString& dtkComposerGraphNode::title(void)
{
    return d->title;
}

void dtkComposerGraphNode::setTitle(const QString& title)
{
    d->title = title;
}

void dtkComposerGraphNode::eval(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeList
// /////////////////////////////////////////////////////////////////

dtkComposerGraphNodeList::dtkComposerGraphNodeList(void) : QList<dtkComposerGraphNode *>()
{

}

dtkComposerGraphNodeList::dtkComposerGraphNodeList(const QList<dtkComposerGraphNode *>& other) : QList<dtkComposerGraphNode *>(other)
{

}

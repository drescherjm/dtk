/* dtkComposerGraphNode.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:09:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. sept. 13 18:34:31 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 256
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCoreSupport/dtkGlobal.h>

#include "dtkComposerGraph.h"
#include "dtkComposerGraphEdge.h"
#include "dtkComposerGraphNode.h"

class dtkComposerGraphNodePrivate
{
public:
    QString title;

public:
    dtkComposerGraphNodeList successors;
    dtkComposerGraphNodeList predecessors;
    dtkComposerGraphNodeList childs;

public:
    dtkComposerGraphNode::Status status;

public:
    dtkComposerGraph *graph;

public:
    bool breakpoint;
    bool endloop_initial;
    bool endloop;
};

dtkComposerGraphNode::dtkComposerGraphNode() : QGraphicsObject(), d(new dtkComposerGraphNodePrivate)
{
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setZValue(1);
    this->setTitle("Graph node");
    this->setStatus(dtkComposerGraphNode::Ready);
    d->breakpoint      = false;
    d->endloop         = false;
    d->endloop_initial = false;
    d->graph           = NULL;
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

dtkComposerGraph *dtkComposerGraphNode::graph(void)
{
    return d->graph;
}

void dtkComposerGraphNode::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
}

void dtkComposerGraphNode::setStatus(dtkComposerGraphNode::Status status)
{
    d->status = status;
}

bool dtkComposerGraphNode::breakpoint(void)
{
    return d->breakpoint;
}

bool dtkComposerGraphNode::endloop(void)
{
    return d->endloop;
}

void dtkComposerGraphNode::setBreakPoint(bool value)
{
    d->breakpoint = value;
}

void dtkComposerGraphNode::setEndLoop(bool value)
{
    d->endloop = value;

    if (value) // endloop is set to true, keep this info in endloop_initial (used to rerun node)
        d->endloop_initial = value;
}

QRectF dtkComposerGraphNode::boundingRect(void) const
{
    return QRectF(0, 0, 125, 25);
}

void dtkComposerGraphNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    d->breakpoint = !(d->breakpoint);
}

void dtkComposerGraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (this->isSelected())
        painter->setPen(Qt::red);
    else
        painter->setPen(Qt::black);

    if (d->status == Done)
        painter->setBrush(Qt::green);
    else if (d->breakpoint)
        painter->setBrush(Qt::yellow);
    else
        painter->setBrush(Qt::white);

    painter->drawRect(this->boundingRect());
    painter->drawText(this->boundingRect(), Qt::AlignCenter, d->title);
}

void dtkComposerGraphNode::addSuccessor(dtkComposerGraphNode *node, int id)
{
    d->successors << node;
}

void dtkComposerGraphNode::addChild(dtkComposerGraphNode *node)
{
    d->childs << node;
}

void dtkComposerGraphNode::addPredecessor(dtkComposerGraphNode *node)
{
    d->predecessors << node;
}

void dtkComposerGraphNode::removeChild(dtkComposerGraphNode *node)
{
    d->childs.removeOne(node);
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

dtkComposerGraphNode *dtkComposerGraphNode::firstSuccessor(void)
{
    return d->successors[0];
}

dtkComposerGraphNodeList dtkComposerGraphNode::predecessors(void)
{
    return d->predecessors;
}

dtkComposerGraphNodeList dtkComposerGraphNode::childs(void)
{
    return d->childs;
}

dtkComposerGraphNodeList dtkComposerGraphNode::evaluableChilds(void)
{
    return d->childs;
}


const QString& dtkComposerGraphNode::title(void)
{
    return d->title;
}

void dtkComposerGraphNode::setTitle(const QString& title)
{
    this->setObjectName(title);
    d->title = title;
}

void dtkComposerGraphNode::eval(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerGraphNode::clean(void)
{
    this->setStatus(dtkComposerGraphNode::Ready);
    d->endloop = d->endloop_initial;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeList
// /////////////////////////////////////////////////////////////////

dtkComposerGraphNodeList::dtkComposerGraphNodeList(void) : QList<dtkComposerGraphNode * >()
{

}

dtkComposerGraphNodeList::dtkComposerGraphNodeList(const QList<dtkComposerGraphNode *>& other) : QList<dtkComposerGraphNode * >(other)
{

}

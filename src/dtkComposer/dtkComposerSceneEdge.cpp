/* dtkComposerSceneEdge.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:00:23 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 16 18:25:51 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 40
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerScenePort.h"

class dtkComposerSceneEdgePrivate
{
public:
    dtkComposerSceneNode *parent;

public:
    dtkComposerScenePort *source;
    dtkComposerScenePort *destination;

public:
    QPainterPath path;
};

dtkComposerSceneEdge::dtkComposerSceneEdge(void) : QGraphicsItem(), d(new dtkComposerSceneEdgePrivate)
{
    d->source = NULL;
    d->destination = NULL;

    d->parent = NULL;

    this->setZValue(-1);
}

dtkComposerSceneEdge::~dtkComposerSceneEdge(void)
{
    delete d;

    d = NULL;
}

QRectF dtkComposerSceneEdge::boundingRect(void) const
{
    return d->path.boundingRect();
}

void dtkComposerSceneEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(Qt::gray);

    painter->drawPath(d->path);

    painter->restore();
}

dtkComposerScenePort *dtkComposerSceneEdge::source(void)
{
    return d->source;
}

dtkComposerScenePort *dtkComposerSceneEdge::destination(void)
{
    return d->destination;
}

void dtkComposerSceneEdge::setSource(dtkComposerScenePort *port)
{
    d->source = port;

    this->adjust();
}

void dtkComposerSceneEdge::setDestination(dtkComposerScenePort *port)
{
    d->destination = port;

    this->adjust();
}

void dtkComposerSceneEdge::adjust(void)
{
    if (!d->source || !d->destination)
        return;

    if (!this->isVisible())
        return;

    QRectF rect;
    rect = d->source->boundingRect();
    QPointF start = d->source->mapToScene(rect.center());
    rect = d->destination->boundingRect();
    QPointF end = d->destination->mapToScene(rect.center());

    this->adjust(start, end);
}

void dtkComposerSceneEdge::adjust(const QPointF& start, const QPointF& end)
{
    this->prepareGeometryChange();
    
    QPointF midPoint = (start + end) / 2;

    qreal halfMid = (midPoint.x() - start.x())/2;

    QPainterPath path;
    path.moveTo(start);
    path.cubicTo(QPointF(end.x() - halfMid, start.y()), QPointF(start.x() + halfMid, end.y()), end);

    QPainterPathStroker stroker;
    stroker.setWidth(3);
    stroker.setCapStyle(Qt::RoundCap);
    d->path = stroker.createStroke(path);

    this->update();
}

bool dtkComposerSceneEdge::link(bool anyway)
{
    Q_UNUSED(anyway);
    
    if(!d->source || !d->destination)
        return false;

    if(d->source == d->destination)
        return false;

    if(d->source->node() == d->destination->node())
        return false;

    if (d->source->type() == dtkComposerScenePort::Output)
        d->source->node()->addOutputEdge(this);


    if (d->destination->type() == dtkComposerScenePort::Input)
        d->destination->node()->addInputEdge(this);

    return true;
}

bool dtkComposerSceneEdge::unlink(void)
{
    if(!d->source || !d->destination)
        return false;

    if (d->source->type() == dtkComposerScenePort::Output)
        d->source->node()->removeOutputEdge(this);

    if (d->destination->type() == dtkComposerScenePort::Input)
        d->destination->node()->removeInputEdge(this);

    return true;
}

dtkComposerSceneNode *dtkComposerSceneEdge::parent(void)
{
    return d->parent;
}

void dtkComposerSceneEdge::setParent(dtkComposerSceneNode *parent)
{
    d->parent = parent;
}

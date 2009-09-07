/* dtkComposerEdge.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 14:30:13 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  7 23:26:50 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 74
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkLog.h>

class dtkComposerEdgePrivate
{
public:
    QPainterPath path;
    QRectF sourceRect;
    QRectF destRect;

    dtkComposerNodeProperty *source;
    dtkComposerNodeProperty *destination;
};

dtkComposerEdge::dtkComposerEdge(void) : QObject(), QGraphicsItem(), d(new dtkComposerEdgePrivate)
{
    d->source = NULL;
    d->destination = NULL;

    this->setZValue(5);
}

dtkComposerEdge::~dtkComposerEdge(void)
{

}

dtkComposerNodeProperty *dtkComposerEdge::source(void)
{
    return d->source;
}

dtkComposerNodeProperty *dtkComposerEdge::destination(void)
{
    return d->destination;
}

void dtkComposerEdge::setSource(dtkComposerNodeProperty *property)
{
    d->source = property;

    this->adjust();
}

void dtkComposerEdge::setDestination(dtkComposerNodeProperty *property)
{
    d->destination = property;

    this->adjust();
}

QRectF dtkComposerEdge::boundingRect(void) const
{
    return QRectF(0, 0, 0, 0);
}

QPointF dtkComposerEdge::start(void) const
{
    if (d->source) {
        QRectF rect = d->source->rect();
        return d->source->mapToScene(rect.center());
    }

    return QPointF();
}

QPointF dtkComposerEdge::end(void) const
{
    if (d->destination) {
        QRectF rect = d->destination->rect();
        return d->destination->mapToScene(rect.center());
    }

    return QPointF();
}

void dtkComposerEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->setPen(QPen(Qt::black, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::yellow);
    painter->drawPath(d->path);
    painter->restore();
}

void dtkComposerEdge::adjust(void)
{
    if (!d->source || !d->destination)
        return;

    QRectF rect;

    rect = d->source->rect();
    d->sourceRect = d->source->mapToScene(rect).boundingRect();
    QPointF start = d->source->mapToScene(rect.center());

    rect = d->destination->rect();
    d->destRect = d->destination->mapToScene(rect).boundingRect();
    QPointF end = d->destination->mapToScene(rect.center());

    adjust(start, end);
}

void dtkComposerEdge::adjust(const QPointF& start, const QPointF& end)
{
    prepareGeometryChange();

    QPointF midPoint = (start + end) / 2;

    qreal halfMid = (midPoint.x() - start.x())/2;

    QPainterPath path;
    path.moveTo(start);
    path.cubicTo(QPointF(end.x() - halfMid, start.y()), QPointF(start.x() + halfMid, end.y()), end);

    QPainterPathStroker stroker;
    stroker.setWidth(3);
    stroker.setCapStyle(Qt::FlatCap);
    d->path = stroker.createStroke(path);

    update();
}

bool dtkComposerEdge::link(void)
{
    if (!d->source || !d->destination)
        return false;

    if (d->source->type() == dtkComposerNodeProperty::Input) {
        dtkDebug() << "Source should be an output property!";
        return false;
    }

    if (d->destination->type() == dtkComposerNodeProperty::Output) {
        dtkDebug() << "Destination should be an input property!";
        return false;
    }

    d->source->node()->addInputEdge(this);
    d->destination->node()->addOutputEdge(this);

    return true;
}


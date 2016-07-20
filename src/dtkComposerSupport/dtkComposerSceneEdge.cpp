/* dtkComposerSceneEdge.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:00:23 2012 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. févr. 28 19:35:10 2013 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 186
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerSceneEdge.h"

#include "dtkComposerScene.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerScenePort.h"

class dtkComposerSceneEdgePrivate
{
public:
    dtkComposerSceneNode *parent;
    dtkComposerScene     *scene;

public:
    dtkComposerScenePort *source;
    dtkComposerScenePort *destination;

public:
    QPainterPath path;

public:
    bool valid;
    bool flagged;
    bool connected_to_selection;
};

dtkComposerSceneEdge::dtkComposerSceneEdge(void) : QGraphicsItem(), d(new dtkComposerSceneEdgePrivate)
{
    d->source = NULL;
    d->destination = NULL;
    d->scene = NULL;


    d->parent = NULL;

    d->valid   = false;
    d->flagged = false;
    d->connected_to_selection = false;

    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setZValue(0);
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


    if (!d->scene)
        if (dtkComposerScene *scene = dynamic_cast<dtkComposerScene * > ( this->scene()))
            d->scene = scene;

    if (d->scene && d->scene->maskedEdges())
        this->setOpacity(0.05);

    if (d->connected_to_selection) {
        painter->setBrush(Qt::yellow);
        this->setOpacity(1);
    } else if (!d->flagged)
        painter->setBrush(Qt::gray);
    else if (d->valid)
        painter->setBrush(Qt::green);
    else
        painter->setBrush(Qt::red);

    if (this->isSelected())
        painter->setBrush(Qt::magenta);

    painter->drawPath(d->path);

    painter->restore();
}

QPainterPath dtkComposerSceneEdge::shape(void) const
{
    QPainterPathStroker stroker;
    stroker.setWidth(10);
    return stroker.createStroke(d->path);
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

    qreal halfMid = (midPoint.x() - start.x()) / 2;

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

    if (!d->source || !d->destination)
        return false;

    if (d->source == d->destination)
        return false;

    if (d->source->node() == d->destination->node())
        return false;

    if (d->source->type() == dtkComposerScenePort::Output)
        d->source->node()->addOutputEdge(this);


    if (d->destination->type() == dtkComposerScenePort::Input)
        d->destination->node()->addInputEdge(this);

    return true;
}

bool dtkComposerSceneEdge::unlink(void)
{
    if (!d->source || !d->destination)
        return false;

    if (d->source->type() == dtkComposerScenePort::Output)
        d->source->node()->removeOutputEdge(this);

    if (d->destination->type() == dtkComposerScenePort::Input)
        d->destination->node()->removeInputEdge(this);

    return true;
}

bool dtkComposerSceneEdge::valid(void)
{
    return (d->valid == true);
}

bool dtkComposerSceneEdge::invalid(void)
{
    return (d->valid == false);
}

void dtkComposerSceneEdge::validate(void)
{
    d->valid = true;

    d->flagged = true;
}

void dtkComposerSceneEdge::invalidate(void)
{
    d->valid = false;

    d->flagged = true;
}

void dtkComposerSceneEdge::setConnected(bool value)
{
    d->connected_to_selection = value;
    this->update();
}

dtkComposerSceneNode *dtkComposerSceneEdge::parent(void)
{
    return d->parent;
}

void dtkComposerSceneEdge::setParent(dtkComposerSceneNode *parent)
{
    d->parent = parent;
}

/* dtkComposerEdge.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 14:30:13 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Feb 24 15:58:32 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 338
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

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

class dtkComposerEdgePrivate
{
public:
    QPainterPath path;
    QRectF sourceRect;
    QRectF destRect;

    QPointF progress;

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
    qDebug() << DTK_PRETTY_FUNCTION << this;

    if (d->source && d->source->node()) {
        d->source->node()->removeGhostInputEdge(this);
        d->source->node()->removeOutputEdge(this);
    }

    if (d->destination && d->destination->node()) { 
        d->destination->node()->removeInputEdge(this);
        d->destination->node()->removeGhostOutputEdge(this);
    }

    delete d;

    d = NULL;
}

QString dtkComposerEdge::description(void)
{
    return QString("(%1, %2) -> (%3, %4)")
        .arg(d->source->node()->title())
        .arg(d->source->name())
        .arg(d->destination->node()->title())
        .arg(d->destination->name());
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
    return QRectF(start(), end());
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
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(Qt::yellow);
    painter->drawPath(d->path);

    if(!d->progress.isNull()) {
        painter->setBrush(Qt::cyan);
        painter->drawEllipse(d->progress.x()-8, d->progress.y()-8, 16, 16);
    }

    painter->restore();
}

void dtkComposerEdge::adjust(void)
{
    if (!d->source || !d->destination)
        return;

    if (!this->isVisible())
        return;

    QRectF rect;

    rect = d->source->rect();
    d->sourceRect = d->source->mapToScene(rect).boundingRect();
    QPointF start = d->source->mapToScene(rect.center());

    rect = d->destination->rect();
    d->destRect = d->destination->mapToScene(rect).boundingRect();
    QPointF end = d->destination->mapToScene(rect.center());

    this->adjust(start, end);
}

void dtkComposerEdge::adjust(const QPointF& start, const QPointF& end)
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

bool dtkComposerEdge::link(bool anyway)
{
    if(anyway) {

        if (d->source->node()->kind() == dtkComposerNode::Composite && d->destination->node()->parentNode() == d->source->node())
            d->source->node()->addGhostInputEdge(this, d->source);
        else
            d->source->node()->addOutputEdge(this, d->source);
        
        if (d->destination->node()->kind() == dtkComposerNode::Composite && d->source->node()->parentNode() == d->destination->node())
            d->destination->node()->addGhostOutputEdge(this, d->destination);
        else
            d->destination->node()->addInputEdge(this, d->destination);

        return true;
    }

    if (!d->source || !d->destination) {
        qDebug() << "Cannot connect undefined properties";
        return false;
    }

    if(d->source->node() == d->destination->node()) {
        qDebug() << "Cannot connect a node to itself.";
        return false;
    }

    if(d->source->node()->isGhost() && d->destination->node()->isGhost()) {
        qDebug() << "Cannot connect ghost nodes together.";
        return false;
    }

    if (d->source->node()->isGhost() && d->source->type() == dtkComposerNodeProperty::Output) {
        qDebug() << "Source property cannot be the output property of a ghost";
        return false;
    }

    if (d->source->node()->isGhost() && d->destination->type() == dtkComposerNodeProperty::Output) {
        qDebug() << "Destination property cannot be the output property of a non ghost node if source property node is a ghost.";
        return false;
    }

    if (d->destination->node()->isGhost() && d->destination->type() == dtkComposerNodeProperty::Input) {
        qDebug() << "Destination property cannot be the input property of a ghost";
        return false;
    }

    if (!d->source->node()->isGhost() && !d->destination->node()->isGhost() && d->source->type() == d->destination->type()) {
        qDebug() << "Cannot connect properties of non ghost nodes if they are of the same type";
        return false;
    }

    if(d->source->type() == dtkComposerNodeProperty::Output) {
        foreach(dtkComposerEdge *edge, d->source->node()->outputEdges()) {
            if(edge->source() == d->source && edge->destination() == d->destination) {
                qDebug() << "Edge already exist.";
                return false;
            }
        }
    }

    if(d->destination->type() == dtkComposerNodeProperty::Input) {
        foreach(dtkComposerEdge *edge, d->destination->node()->inputEdges()) {
            if(edge->source() == d->source && edge->destination() == d->destination) {
                qDebug() << "Edge already exist.";
                return false;
            }
        }
    }

    if (d->source->node()->isGhost())
        d->source->node()->addGhostInputEdge(this, d->source);
    else
        d->source->node()->addOutputEdge(this, d->source);

    if (d->destination->node()->isGhost())
        d->destination->node()->addGhostOutputEdge(this, d->destination);
    else
        d->destination->node()->addInputEdge(this, d->destination);

    return true;
}

bool dtkComposerEdge::unlink(void)
{
    if(!d->source)
        return false;

    if(!d->destination)
        return false;  

    if(d->source->node()->isGhost())
        d->source->node()->removeGhostInputEdge(this);
    else
        d->source->node()->removeOutputEdge(this);

    if(d->destination->node()->isGhost())
        d->destination->node()->removeGhostOutputEdge(this);
    else
        d->destination->node()->removeInputEdge(this);

    return true;
}

// void dtkComposerEdge::onTransition(QEvent *event)
// {
//     QRectF rect;

//     rect = d->source->rect();
//     QPointF start = d->source->mapToScene(rect.center());

//     rect = d->destination->rect();
//     QPointF end = d->destination->mapToScene(rect.center());

//     QPointF midPoint = (start + end) / 2;

//     qreal halfMid = (midPoint.x() - start.x())/2;

//     QPainterPath path;
//     path.moveTo(start);
//     path.cubicTo(QPointF(end.x() - halfMid, start.y()), QPointF(start.x() + halfMid, end.y()), end);

//     for(int i = 0; i <= 100; i++) {
//         usleep(10000);
//         d->progress = path.pointAtPercent(i/100.0);
//         this->scene()->update(this->boundingRect());
//         this->scene()->views().first()->update();
//         qApp->processEvents();
//     }

//     d->progress = QPointF(0, 0);
// }

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

QDebug operator<<(QDebug dbg, dtkComposerEdge  edge)
{
    dbg.nospace() << edge.description();
    
    return dbg.space();
}

QDebug operator<<(QDebug dbg, dtkComposerEdge& edge)
{
    dbg.nospace() << edge.description();
    
    return dbg.space();
}

QDebug operator<<(QDebug dbg, dtkComposerEdge *edge)
{
    dbg.nospace() << edge->description();
    
    return dbg.space();
}

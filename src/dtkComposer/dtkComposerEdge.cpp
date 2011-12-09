/* dtkComposerEdge.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 14:30:13 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Dec  9 22:57:52 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 490
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

    dtkComposerNodeProperty *source;
    dtkComposerNodeProperty *destination;

    dtkComposerEdge::Flag flag;
};

dtkComposerEdge::dtkComposerEdge(void) : QObject(), QGraphicsItem(), d(new dtkComposerEdgePrivate)
{
    d->source = NULL;
    d->destination = NULL;

    d->flag = dtkComposerEdge::Valid;

    this->setZValue(5);
}

dtkComposerEdge::~dtkComposerEdge(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerEdge::description(void)
{
    if(!d->source || !d->destination)
        return QString("Invalid edge");

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
}

void dtkComposerEdge::setDestination(dtkComposerNodeProperty *property)
{
    d->destination = property;
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

    if(d->flag == dtkComposerEdge::Valid) {
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(Qt::yellow);
    }

    if(d->flag == dtkComposerEdge::Invalid) {
        painter->setPen(QPen(Qt::gray, 1, Qt::DashLine));
        painter->setBrush(Qt::red);
    }

    painter->drawPath(d->path);

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
    if(!d->source) {
        qDebug() << DTK_PRETTY_FUNCTION << "No source set";
        return false;
    }

    if(!d->destination) {
        qDebug() << DTK_PRETTY_FUNCTION << "No destination set";
        return false;
    }

    if(anyway) {

        if (d->source->node()->kind() == dtkComposerNode::Composite && d->destination->node()->parentNode() == d->source->node())
            d->source->node()->g->appendLeftRelayEdge(this, d->source);
        else if (d->source->node()->kind() == dtkComposerNode::Control && d->destination->node()->parentNode() == d->source->node())
            d->source->node()->g->appendLeftRelayEdge(this, d->source);
        else
            d->source->node()->g->appendRightEdge(this, d->source);
        
        if (d->destination->node()->kind() == dtkComposerNode::Composite && d->source->node()->parentNode() == d->destination->node())
            d->destination->node()->g->appendRightRelayEdge(this, d->destination);
        else if (d->destination->node()->kind() == dtkComposerNode::Control && d->source->node()->parentNode() == d->destination->node())
            d->destination->node()->g->appendRightRelayEdge(this, d->destination);
        else
            d->destination->node()->g->appendLeftEdge(this, d->destination);
        
        d->source->node()->g->onEdgeConnected(this);
        d->destination->node()->g->onEdgeConnected(this);

        return true;
    }

    if (!d->source || !d->destination) {
        qDebug() << "Cannot connect undefined properties";
        return false;
    }

    if (d->source->node() == d->destination->node()) {
        qDebug() << "Cannot connect a node to itself.";
        return false;
    }

    if (d->source->node()->isGhost() && d->destination->node()->isGhost()) {
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

    if (!d->source->node()->isGhost() && !d->destination->node()->isGhost() && d->source->type() == d->destination->type() && (d->source->type() == dtkComposerNodeProperty::Input || d->source->type() == dtkComposerNodeProperty::Output)) {
        qDebug() << "Cannot connect properties of non ghost nodes if they are of the same type";
        return false;
    }

    if (d->destination->node()->kind() == dtkComposerNode::Control && d->destination->node() == d->source->node()->parentNode() && (d->destination->type() == dtkComposerNodeProperty::HybridInput || d->destination->type() == dtkComposerNodeProperty::PassThroughInput)) {
        qDebug() << "Hybrid input property of a block cannot be the destination property of a node contained by this block";
        return false;
    }

    if ((d->source->type() == dtkComposerNodeProperty::HybridInput || d->source->type() == dtkComposerNodeProperty::PassThroughInput) && d->destination->type() == dtkComposerNodeProperty::Output) {
        qDebug() << "Cannot connect Hybrid input property to an Output property";
        return false;
    }

    if ((d->source->type() == dtkComposerNodeProperty::HybridInput || d->source->type() == dtkComposerNodeProperty::PassThroughInput) && d->source->node() != d->destination->node()->parentNode()) {
        qDebug() << "Cannot connect Hybrid input property of a control node to a node that is not inside this control node";
        return false;
    }

    if (d->source->node() == d->destination->node()->parentNode() && (d->source->type() == dtkComposerNodeProperty::HybridOutput || d->source->type() == dtkComposerNodeProperty::PassThroughOutput)) {
        qDebug() << "Hybrid output property of a block cannot be the source of an edge whose destination is a node contained by this block";
        return false;
    }

    if (d->destination->type() == dtkComposerNodeProperty::Input && d->destination->multiplicity() == dtkComposerNodeProperty::Single) {
        if (d->destination->edge()) {
            qDebug() << "This input property only accepts one edge.";
            return false;
        }
    }            

    if (d->source->type() == dtkComposerNodeProperty::Output || d->source->type() == dtkComposerNodeProperty::HybridOutput || d->source->type() == dtkComposerNodeProperty::PassThroughOutput) {
        foreach (dtkComposerEdge *edge, d->source->node()->g->rightEdges()) {
            if (edge->source() == d->source && edge->destination() == d->destination) {
                qDebug() << "Edge already exist.";
                return false;
            }
        }
    }

    if (d->destination->type() == dtkComposerNodeProperty::Input || d->destination->type() == dtkComposerNodeProperty::HybridInput || d->destination->type() == dtkComposerNodeProperty::PassThroughInput) {        
        foreach (dtkComposerEdge *edge, d->destination->node()->g->leftEdges()) {
            if (edge->source() == d->source && edge->destination() == d->destination) {
                qDebug() << "Edge already exist.";
                return false;
            }
        }
    }

    if (d->destination->type() == dtkComposerNodeProperty::HybridOutput || d->destination->type() == dtkComposerNodeProperty::PassThroughOutput) {
        foreach (dtkComposerEdge *edge, d->destination->node()->g->rightRelayEdges()) {
            if (edge->source() == d->source && edge->destination() == d->destination) {
                qDebug() << "Edge already exist.";
                return false;
            }
        }
    }

    if (d->source->type() == dtkComposerNodeProperty::HybridInput || d->source->type() == dtkComposerNodeProperty::PassThroughInput) {
        foreach (dtkComposerEdge *edge, d->source->node()->g->leftRelayEdges()) {
            if (edge->source() == d->source && edge->destination() == d->destination) {
                qDebug() << "Edge already exist.";
                return false;
            }
        }
    }

    if (d->source->node()->kind() == dtkComposerNode::Composite && d->destination->node()->parentNode() == d->source->node())
        d->source->node()->g->appendLeftRelayEdge(this, d->source);
    else if (d->source->node()->kind() == dtkComposerNode::Control && d->destination->node()->parentNode() == d->source->node())
        d->source->node()->g->appendLeftRelayEdge(this, d->source);
    else
        d->source->node()->g->appendRightEdge(this, d->source);

    if (d->destination->node()->kind() == dtkComposerNode::Composite && d->source->node()->parentNode() == d->destination->node())
        d->destination->node()->g->appendRightRelayEdge(this, d->destination);
    else if (d->destination->node()->kind() == dtkComposerNode::Control && d->source->node()->parentNode() == d->destination->node())
        d->destination->node()->g->appendRightRelayEdge(this, d->destination);
    else
        d->destination->node()->g->appendLeftEdge(this, d->destination);

    d->destination->node()->g->onEdgeConnected(this);

    return true;
}

bool dtkComposerEdge::unlink(void)
{
    if (!d->source)
        return false;

    if (!d->destination)
        return false;
    
    d->destination->node()->g->onEdgeDisconnected(this);

    if (d->source->node()->kind() == dtkComposerNode::Composite && d->destination->node()->parentNode() == d->source->node()) {
        d->source->node()->g->removeLeftRelayEdge(this);
    } else if (d->source->node()->kind() == dtkComposerNode::Control && d->destination->node()->parentNode() == d->source->node()) {
        d->source->node()->g->removeLeftRelayEdge(this);
    } else {
        d->source->node()->g->removeRightEdge(this);
    }

    if (d->destination->node()->kind() == dtkComposerNode::Composite && d->source->node()->parentNode() == d->destination->node()) {
        d->destination->node()->g->removeRightRelayEdge(this);
    } else if (d->destination->node()->kind() == dtkComposerNode::Control && d->source->node()->parentNode() == d->destination->node()) {
        d->destination->node()->g->removeRightRelayEdge(this);
    } else {
        d->destination->node()->g->removeLeftEdge(this);
    }

    return true;
}

void dtkComposerEdge::validate(void)
{
    d->flag = dtkComposerEdge::Valid;

    this->update();
}

void dtkComposerEdge::invalidate(void)
{
    d->flag = dtkComposerEdge::Invalid;

    this->update();
}

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

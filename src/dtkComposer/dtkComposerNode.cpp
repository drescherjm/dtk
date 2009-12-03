/* dtkComposerNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:23 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep 16 15:42:53 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 272
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
#include "dtkComposerScene.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractView.h>

class dtkComposerNodePrivate
{
public:
    qreal penWidth;
    qreal width;
    qreal height;
    qreal header_height;
    qreal node_radius;
    qreal margin_left;
    qreal margin_right;
    qreal margin_top;
    qreal margin_bottom;

    QGraphicsTextItem *title;

    QList<dtkComposerNodeProperty *> input_properties;
    QList<dtkComposerNodeProperty *> output_properties;

    QHash<dtkComposerEdge *, dtkComposerNodeProperty *> input_edges;
    QHash<dtkComposerEdge *, dtkComposerNodeProperty *> output_edges;

    dtkComposerNodeProperty *clicked_property;

    dtkComposerNode::Type type;

    dtkAbstractObject *object;

    QString script;
};

dtkComposerNode::dtkComposerNode(dtkComposerNode *parent) : QObject(), QGraphicsItem(parent), d(new dtkComposerNodePrivate)
{
    d->type = Unknown;
    d->object = NULL;

    d->penWidth = 1;
    d->header_height = 20;
    d->node_radius = 5;
    d->margin_left = 5;
    d->margin_right = 5;
    d->margin_top = 5;
    d->margin_bottom = 5;

    d->width = 150;
    d->height = d->header_height*2;

    d->title = new QGraphicsTextItem(this);
#if defined(Q_WS_MAC)
    d->title->setFont(QFont("Lucida Grande", 13));
#else
    d->title->setFont(QFont("Lucida Grande", 11));
#endif
    d->title->setHtml("Title");
    d->title->setDefaultTextColor(Qt::black);
    d->title->setPos(-d->width/2 + d->margin_left/2, -d->header_height-2);

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    this->setZValue(10);
}

dtkComposerNode::~dtkComposerNode(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNode::setType(Type type)
{
    d->type = type;
}

void dtkComposerNode::setObject(dtkAbstractObject *object)
{
    d->object = object;

    d->title->setHtml(object->name());
}

void dtkComposerNode::addScript(const QString& script)
{
    d->script += script + "\n";
}

void dtkComposerNode::setScript(const QString& script)
{
    d->script = script;
}

dtkComposerNode::Type dtkComposerNode::type(void)
{
    return d->type;
}

dtkAbstractObject *dtkComposerNode::object(void)
{
    return d->object;
}

dtkComposerEdge *dtkComposerNode::edge(dtkComposerNodeProperty *property)
{
    if(property->type() == dtkComposerNodeProperty::Input)
        return d->input_edges.key(property);
    
    if(property->type() == dtkComposerNodeProperty::Output)
        return d->output_edges.key(property);

    return 0;
}

QString dtkComposerNode::script(void) const
{
    return d->script;
}

void dtkComposerNode::addInputProperty(dtkComposerNodeProperty *property)
{
    property->setRect(QRectF(-d->width/2+d->node_radius, d->margin_top+(3*d->input_properties.count() +1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));

    d->input_properties << property;

    d->height = d->header_height + (3*qMax(d->input_properties.count(), d->output_properties.count())) * d->node_radius + d->margin_bottom;
}

void dtkComposerNode::addOutputProperty(dtkComposerNodeProperty *property)
{
    property->setRect(QRectF(d->width/2-3*d->node_radius, d->margin_top+(3*d->output_properties.count() + 1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));

    d->output_properties << property;

    d->height = d->header_height + (3*qMax(d->input_properties.count(), d->output_properties.count())) * d->node_radius + d->margin_bottom;
}

void dtkComposerNode::addInputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    d->input_edges.insert(edge, property);
}

void dtkComposerNode::addOutputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    d->output_edges.insert(edge, property);
}

void dtkComposerNode::removeInputEdge(dtkComposerEdge *edge)
{
    d->input_edges.remove(edge);
}

void dtkComposerNode::removeOutputEdge(dtkComposerEdge *edge)
{
    d->output_edges.remove(edge);
}

int dtkComposerNode::count(dtkComposerNodeProperty *property)
{
    if(property->type() == dtkComposerNodeProperty::Input)
        return d->input_edges.keys(property).count();

    if(property->type() == dtkComposerNodeProperty::Output)
        return d->output_edges.keys(property).count();

    return 0;
}

QList<dtkComposerEdge *> dtkComposerNode::inputEdges(void)
{
    return d->input_edges.keys();
}

QList<dtkComposerEdge *> dtkComposerNode::outputEdges(void)
{
    return d->output_edges.keys();
}

QList<dtkComposerNode *> dtkComposerNode::inputNodes(void)
{
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerEdge *edge, d->input_edges.keys())
        nodes << edge->source()->node();

    return nodes;
}

QList<dtkComposerNode *> dtkComposerNode::outputNodes(void)
{
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerEdge *edge, d->output_edges.keys())
        nodes << edge->destination()->node();

    return nodes;
}

dtkComposerNodeProperty *dtkComposerNode::propertyAt(const QPointF& point) const
{
    foreach(dtkComposerNodeProperty *property, d->input_properties)
        if(property->rect().contains(point))
            return property;

    foreach(dtkComposerNodeProperty *property, d->output_properties)
        if(property->rect().contains(point))
            return property;
    
    return NULL;
}

QRectF dtkComposerNode::boundingRect(void) const
{
    return QRectF(-d->width/2 - d->penWidth / 2, -d->header_height - d->penWidth / 2, d->width + d->penWidth, d->height + d->penWidth);
}

void dtkComposerNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    { // Drawing node header

    QRectF rect(-d->width/2, -d->header_height, d->width, d->header_height);

    qreal leftBottomRadius = 0;
    qreal leftTopRadius = 5;
    qreal rightBottomRadius = 0;
    qreal rightTopRadius = 5;

    painter->save();

    QPainterPath path(QPoint(rect.left(), rect.top() + leftTopRadius));
    path.quadTo(rect.left(), rect.top(), rect.left() + leftTopRadius, rect.top());
    path.lineTo(rect.right() - rightTopRadius, rect.top());
    path.quadTo(rect.right(), rect.top(), rect.right(), rect.top() + rightTopRadius);
    path.lineTo(rect.right(), rect.bottom() - rightBottomRadius);
    path.quadTo(rect.right(), rect.bottom(), rect.right() - rightBottomRadius, rect.bottom());
    path.lineTo(rect.left() + leftBottomRadius, rect.bottom());
    path.quadTo(rect.left(), rect.bottom(), rect.left(), rect.bottom() - leftBottomRadius);
    path.closeSubpath();

    switch(d->type) {
    case Unknown:
        painter->setBrush(Qt::gray);
        break;
    case GenericData:
        painter->setBrush(QColor(220, 155, 50));
        break;
    case Data:
        painter->setBrush(QColor(Qt::blue).lighter());
        break;
    case Process:
        painter->setBrush(QColor(Qt::red).lighter());
        break;
    case View:
        painter->setBrush(QColor(Qt::green).lighter());
        break;
    }

    painter->setPen(Qt::darkGray);
    painter->drawPath(path);

    painter->restore();

    }

    { // Drawing node body

    QRectF rect(-d->width/2, 0, d->width, d->height-d->header_height);

    qreal leftBottomRadius = 5;
    qreal leftTopRadius = 0;
    qreal rightBottomRadius = 5;
    qreal rightTopRadius = 0;

    painter->save();

    QPainterPath path(QPoint(rect.left(), rect.top() + leftTopRadius));
    path.quadTo(rect.left(), rect.top(), rect.left() + leftTopRadius, rect.top());
    path.lineTo(rect.right() - rightTopRadius, rect.top());
    path.quadTo(rect.right(), rect.top(), rect.right(), rect.top() + rightTopRadius);
    path.lineTo(rect.right(), rect.bottom() - rightBottomRadius);
    path.quadTo(rect.right(), rect.bottom(), rect.right() - rightBottomRadius, rect.bottom());
    path.lineTo(rect.left() + leftBottomRadius, rect.bottom());
    path.quadTo(rect.left(), rect.bottom(), rect.left(), rect.bottom() - leftBottomRadius);
    path.closeSubpath();

    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::lightGray);
    painter->drawPath(path);

    painter->restore();

    }

    if(this->isSelected()) { // Drawing selection outline

    QRectF rect(-d->width/2, -d->header_height, d->width, d->height);
         
    qreal leftBottomRadius = 5;
    qreal leftTopRadius = 5;
    qreal rightBottomRadius = 5;
    qreal rightTopRadius = 5;

    painter->save();

    QPainterPath path(QPoint(rect.left(), rect.top() + leftTopRadius));
    path.quadTo(rect.left(), rect.top(), rect.left() + leftTopRadius, rect.top());
    path.lineTo(rect.right() - rightTopRadius, rect.top());
    path.quadTo(rect.right(), rect.top(), rect.right(), rect.top() + rightTopRadius);
    path.lineTo(rect.right(), rect.bottom() - rightBottomRadius);
    path.quadTo(rect.right(), rect.bottom(), rect.right() - rightBottomRadius, rect.bottom());
    path.lineTo(rect.left() + leftBottomRadius, rect.bottom());
    path.quadTo(rect.left(), rect.bottom(), rect.left(), rect.bottom() - leftBottomRadius);
    path.closeSubpath();

    painter->setPen(QPen(Qt::magenta, 2));
    painter->drawPath(path);

    painter->restore();

    }
}

void dtkComposerNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!d->clicked_property)
        QGraphicsItem::mouseMoveEvent(event);

    foreach(dtkComposerEdge *edge, d->input_edges.keys())
	edge->adjust();

    foreach(dtkComposerEdge *edge, d->output_edges.keys())
	edge->adjust();
}

void dtkComposerNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    d->clicked_property = this->propertyAt(event->pos());

    if(d->clicked_property)
        return;

    if(event->button() == Qt::RightButton) {
        QMenu menu;
        menu.addAction("Action 1");
        menu.addAction("Action 2");
        menu.exec(QCursor::pos());
    }

    QGraphicsItem::mousePressEvent(event);
}

void dtkComposerNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!d->clicked_property)
        QGraphicsItem::mouseReleaseEvent(event);

    d->clicked_property = NULL;
}

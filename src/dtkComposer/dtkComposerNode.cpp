/* dtkComposerNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:23 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Sep  8 13:22:58 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 112
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
    QGraphicsTextItem *button;

    QList<dtkComposerNodeProperty *> input_properties;
    QList<dtkComposerNodeProperty *> output_properties;

    QHash<dtkComposerEdge *, dtkComposerNodeProperty *> input_edges;
    QHash<dtkComposerEdge *, dtkComposerNodeProperty *> output_edges;

    dtkComposerNodeProperty *clicked_property;
};

dtkComposerNode::dtkComposerNode(dtkComposerNode *parent) : QObject(), QGraphicsItem(parent), d(new dtkComposerNodePrivate)
{
    int n_input_properties = 3;
    int n_output_properties = 2;

    d->penWidth = 1;
    d->header_height = 20;
    d->node_radius = 5;
    d->margin_left = 5;
    d->margin_right = 5;
    d->margin_top = 5;
    d->margin_bottom = 5;

    d->width = 150;
    d->height = d->header_height + (3*qMax(n_input_properties, n_output_properties) + 1) * d->node_radius;

    d->title = new QGraphicsTextItem(this);
    d->title->setHtml("Title");
    d->title->setDefaultTextColor(Qt::black);
    d->title->setPos(-d->width/2 + d->margin_left/2, -d->height/2-2);

    d->button = new QGraphicsTextItem(this);
    // d->button->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    // d->button->setHtml("<a href=\"node://more\">?</a>");
    d->button->setHtml("?");
    d->button->setDefaultTextColor(Qt::black);
    d->button->setPos(d->width/2 - d->margin_right*3, -d->height/2-2);

    for(int i = 0 ; i < n_input_properties ; i++) {
        dtkComposerNodeProperty *input = new dtkComposerNodeProperty(dtkComposerNodeProperty::Input, this);
        input->setText(QString("Input %1").arg(i));
        input->setRect(QRectF(-d->width/2+d->node_radius, -d->height/2+d->header_height+d->margin_top+(3*i+1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));
        d->input_properties << input;
    }

    for(int i = 0 ; i < n_output_properties ; i++) {
        dtkComposerNodeProperty *output = new dtkComposerNodeProperty(dtkComposerNodeProperty::Output, this);
        output->setText(QString("Output %1").arg(i));
        output->setRect(QRectF(d->width/2-3*d->node_radius, -d->height/2+d->header_height+d->margin_top+(3*i+1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));
        d->output_properties << output;
    }

    this->setFlags(QGraphicsItem::ItemIsMovable);
    this->setZValue(10);
}

dtkComposerNode::~dtkComposerNode(void)
{
    delete d;

    d = NULL;
}

dtkComposerEdge *dtkComposerNode::edge(dtkComposerNodeProperty *property)
{
    if(property->type() == dtkComposerNodeProperty::Input)
        return d->input_edges.key(property);
    
    if(property->type() == dtkComposerNodeProperty::Output)
        return d->output_edges.key(property);

    return 0;
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
    return QRectF(-d->width/2 - d->penWidth / 2, -d->height/2 - d->penWidth / 2, d->width + d->penWidth, d->height + d->penWidth);
}

void dtkComposerNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    { // Drawing node header

    QRectF rect(-d->width/2, -d->height/2, d->width, d->header_height);

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

    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::gray);
    painter->drawPath(path);

    painter->restore();

    }

    { // Drawing node body

    QRectF rect(-d->width/2, -d->height/2+d->header_height, d->width, d->height-d->header_height);

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

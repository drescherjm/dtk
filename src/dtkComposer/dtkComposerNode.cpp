/* dtkComposerNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:23 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  7 15:52:27 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 49
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

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

    QList<dtkComposerNodeProperty *> inputs;
    QList<dtkComposerNodeProperty *> outputs;
};

dtkComposerNode::dtkComposerNode(dtkComposerNode *parent) : QObject(), QGraphicsItem(parent), d(new dtkComposerNodePrivate)
{
    int n_inputs = 3;
    int n_outputs = 2;

    d->penWidth = 1;
    d->header_height = 20;
    d->node_radius = 5;
    d->margin_left = 5;
    d->margin_right = 5;
    d->margin_top = 5;
    d->margin_bottom = 5;

    d->width = 150;
    d->height = d->header_height + (3*qMax(n_inputs, n_outputs) + 1) * d->node_radius;

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

    for(int i = 0 ; i < n_inputs ; i++) {
        dtkComposerNodeProperty *input = new dtkComposerNodeProperty(dtkComposerNodeProperty::Input, this);
        input->setText(QString("Input %1").arg(i));
        input->setRect(QRectF(-d->width/2+d->node_radius, -d->height/2+d->header_height+d->margin_top+(3*i+1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));
        d->inputs << input;
    }

    for(int i = 0 ; i < n_outputs ; i++) {
        dtkComposerNodeProperty *output = new dtkComposerNodeProperty(dtkComposerNodeProperty::Output, this);
        output->setText(QString("Output %1").arg(i));
        output->setRect(QRectF(d->width/2-3*d->node_radius, -d->height/2+d->header_height+d->margin_top+(3*i+1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));
        d->outputs << output;
    }

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
}

dtkComposerNode::~dtkComposerNode(void)
{
    
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

void dtkComposerNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
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
    QGraphicsItem::mouseReleaseEvent(event);
}

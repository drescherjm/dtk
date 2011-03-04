/* dtkComposerNodeControlBlock.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar  3 14:48:10 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Mar  4 20:45:26 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 107
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerNodeControlBlock.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBlockPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlBlockPrivate
{
public:
    QColor pen_color;
    QColor brush_color;

    QString title;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBlock
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlBlock::dtkComposerNodeControlBlock(const QString& title, QGraphicsItem *parent) : QGraphicsRectItem(parent), d(new dtkComposerNodeControlBlockPrivate)
{
    d->pen_color = QColor("#c7c7c7");
    d->brush_color = Qt::transparent;

    d->title = title;

    this->setPen(d->pen_color);
    this->setBrush(Qt::NoBrush);
    this->setZValue(parent->zValue());
}

dtkComposerNodeControlBlock::~dtkComposerNodeControlBlock(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeControlBlock::title(void) const
{
    return d->title;
}

QColor dtkComposerNodeControlBlock::brushColor(void) const
{
    return d->brush_color;
}

QColor dtkComposerNodeControlBlock::penColor(void) const
{
    return d->pen_color;
}

void dtkComposerNodeControlBlock::setBrushColor(const QColor& color)
{
    d->brush_color = color;

    if(color == Qt::transparent)
        this->setBrush(Qt::NoBrush);
    else
        this->setBrush(d->brush_color);

    this->update();
}

void dtkComposerNodeControlBlock::setPenColor(const QColor& color)
{
    d->pen_color = color;

    this->setPen(d->pen_color);
    this->update();
}

void dtkComposerNodeControlBlock::setRect(const QRectF& rectangle)
{
    if(this->childItems().count()) {

        if(rectangle.topLeft() != this->rect().topLeft()) {

            QPointF delta = rectangle.topLeft() - this->rect().topLeft();

            foreach(QGraphicsItem *item, this->childItems()) {
                item->setX(item->x() + delta.x());
                item->setY(item->y() + delta.y());
            }
        }
    }

    QGraphicsRectItem::setRect(rectangle);
}

void dtkComposerNodeControlBlock::setRect(qreal x, qreal y, qreal width, qreal height)
{
    this->setRect(QRectF(x, y, width, height));
}

QList<dtkComposerNode *> dtkComposerNodeControlBlock::nodes(void)
{
    QList<dtkComposerNode *> nodes;

    foreach(QGraphicsItem *item, this->childItems())
        if(dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item))
            nodes << node;

    return nodes;
}

QList<dtkComposerNode *> dtkComposerNodeControlBlock::startNodes(void)
{
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerNode *node, this->nodes())
        if(node->inputEdges().count() == 0)
            nodes << node;

    return nodes;
}

QList<dtkComposerNode *> dtkComposerNodeControlBlock::endNodes(void)
{
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerNode *node, this->nodes())
        if(node->outputEdges().count() == 0)
            nodes << node;

    return nodes;
}

void dtkComposerNodeControlBlock::highlight(void)
{
    static dtkComposerNodeControlBlock *highlighted = NULL;

    if(highlighted == this)
        return;

    QPropertyAnimation *animation = new QPropertyAnimation(this, "brushColor");
    animation->setDuration(500);
    animation->setKeyValueAt(0.0, Qt::red);
    animation->setKeyValueAt(1.0, Qt::transparent);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    highlighted = this;
}

/* dtkComposerNodeControlBlock.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar  3 14:48:10 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Mar 18 16:12:12 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 557
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeControlBlock_p.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBlockLabel
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlBlockLabel : public QGraphicsTextItem
{
public:
     dtkComposerNodeControlBlockLabel(dtkComposerNodeControlBlock *parent = 0);
    ~dtkComposerNodeControlBlockLabel(void);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    dtkComposerNodeControlBlock *block;
};

dtkComposerNodeControlBlockLabel::dtkComposerNodeControlBlockLabel(dtkComposerNodeControlBlock *parent) : QGraphicsTextItem(parent)
{
    this->block = parent;

#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 10);
#else
    QFont font("Lucida Grande", 8);
#endif

    this->setDefaultTextColor(Qt::lightGray);
    this->setFont(font);
    this->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->setTextWidth(100);
    this->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
}

dtkComposerNodeControlBlockLabel::~dtkComposerNodeControlBlockLabel(void)
{

}

void dtkComposerNodeControlBlockLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath s_rect; s_rect.addRect(QRectF(option->rect.topLeft(), QSizeF(option->rect.width(), option->rect.height() / 2)));
    QPainterPath r_rect; r_rect.addRoundedRect(option->rect, 5, 5);
    QPainterPath path = s_rect.united(r_rect);

    painter->save();
    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::black);
    painter->drawPath(path);
    painter->restore();

    QStyleOptionGraphicsItem *o = const_cast<QStyleOptionGraphicsItem*>(option);
    o->state &= ~QStyle::State_Selected;
    o->state &= ~QStyle::State_HasFocus;

    QGraphicsTextItem::paint(painter, option, widget);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBlockButtonRemove
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlBlockButtonRemove : public QGraphicsItem
{
public:
     dtkComposerNodeControlBlockButtonRemove(dtkComposerNodeControlBlock *parent = 0);
    ~dtkComposerNodeControlBlockButtonRemove(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeControlBlock *block;

    QPainterPath path;
    QString text;
};

dtkComposerNodeControlBlockButtonRemove::dtkComposerNodeControlBlockButtonRemove(dtkComposerNodeControlBlock *parent) : QGraphicsItem(parent)
{
    int margin = 10;
    int length = 30;
    int height = 10;
    int radius =  5;
    int origin_x = -(length + margin) / 2;
    int origin_y = parent->boundingRect().height() / 2;

    QPainterPath b; b.addRoundedRect(origin_x,              origin_y, margin,          -height,     radius, radius);
    QPainterPath c; c.addRoundedRect(origin_x + margin,     origin_y, length - margin, -height,     radius, radius);
    QPainterPath d; d.addRoundedRect(origin_x + length,     origin_y, margin,          -height,     radius, radius);
    QPainterPath e; e.addRoundedRect(origin_x + margin / 2, origin_y, length,          -height / 2,      0,      0);

    this->path = c.united(e.subtracted(b.united(c.united(d))));

    this->block = parent;

    this->text = "-";

    this->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
}

dtkComposerNodeControlBlockButtonRemove::~dtkComposerNodeControlBlockButtonRemove(void)
{

}

QRectF dtkComposerNodeControlBlockButtonRemove::boundingRect(void) const
{
    return this->path.boundingRect();
}

void dtkComposerNodeControlBlockButtonRemove::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QLinearGradient gradient(option->rect.left(), option->rect.top(), option->rect.left(), option->rect.bottom());
    gradient.setColorAt(0.0, QColor("#bbbbbb"));
    gradient.setColorAt(0.3, QColor("#333333"));
    gradient.setColorAt(1.0, QColor("#222222"));

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(gradient);
    painter->drawPath(path);
    
#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 8);
#else
    QFont font("Lucida Grande", 6);
#endif
    font.setBold(true);

    QFontMetrics metrics(font);
    
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, text);
}

void dtkComposerNodeControlBlockButtonRemove::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    this->block->parentNode()->removeBlock(this->block, true);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBlockButton
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlBlockButton : public QGraphicsItem
{
public:
     dtkComposerNodeControlBlockButton(dtkComposerNodeControlBlock *parent = 0);
    ~dtkComposerNodeControlBlockButton(void);

    QRectF boundingRect(void) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeControlBlockLabel *label;

private:
    dtkComposerNodeControlBlock *block;
};

dtkComposerNodeControlBlockButton::dtkComposerNodeControlBlockButton(dtkComposerNodeControlBlock *parent) : QGraphicsItem(parent)
{
    this->block = parent;
    this->label = NULL;

    this->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
}

dtkComposerNodeControlBlockButton::~dtkComposerNodeControlBlockButton(void)
{

}

QRectF dtkComposerNodeControlBlockButton::boundingRect(void) const
{
    return QRectF(0, 0, 20, 10);
}

void dtkComposerNodeControlBlockButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath s_rect; s_rect.addRect(QRectF(option->rect.topLeft(), QSizeF(option->rect.width(), option->rect.height() / 2)));
    QPainterPath r_rect; r_rect.addRoundedRect(option->rect, 5, 5);
    QPainterPath path = s_rect.united(r_rect);

    painter->save();
    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::black);
    painter->drawPath(path);
    painter->restore();
}

void dtkComposerNodeControlBlockButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->label)
        return;

    dtkComposerNodeProperty *input_property = block->addInputProperty(this->label->toPlainText(), block->parentNode());
    input_property->setBlockedFrom(block->title());
    
    dtkComposerNodeProperty *output_property = block->addOutputProperty(this->label->toPlainText(), block->parentNode());
    output_property->setBlockedFrom(block->title());

    block->parentNode()->addInputProperty(input_property);
    block->parentNode()->addOutputProperty(output_property);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBlock
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlBlock::dtkComposerNodeControlBlock(const QString& title, dtkComposerNodeControl *parent) : QGraphicsRectItem(parent), d(new dtkComposerNodeControlBlockPrivate)
{
    d->parent = parent;
    
    d->remove_button = new dtkComposerNodeControlBlockButtonRemove(this);
    d->remove_button->setZValue(this->zValue() + 1);
    d->remove_button->hide();

    d->button = NULL;
    d->label = NULL;
    
    d->interactive = false;
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

dtkComposerNodeControl *dtkComposerNodeControlBlock::parentNode(void)
{
    return d->parent;
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

void dtkComposerNodeControlBlock::setRemoveButtonVisible(bool visible)
{
    d->remove_button->setVisible(visible);
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

void dtkComposerNodeControlBlock::setInteractive(bool interactive)
{
    d->interactive = interactive;

    if(d->interactive && !d->button) {
        d->button = new dtkComposerNodeControlBlockButton(this);
        d->button->setZValue(this->zValue() - 1);
        d->button->setVisible(false);
    }

    if(d->interactive && !d->label) {
        d->label = new dtkComposerNodeControlBlockLabel(this);
        d->label->setZValue(this->zValue() - 1);
        d->label->setVisible(false);

        if(d->button)
            if(!d->button->label)
                d->button->label = d->label;
    }

    this->setAcceptHoverEvents(interactive);
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

    if (d->remove_button && d->remove_button->isVisible())
        d->remove_button->setPos(rectangle.width()/2 - 150/2, this->rect().bottom());

    if (d->button)
        d->button->setPos((rectangle.left() + rectangle.width() - 100) / 2 + 50, this->rect().top());

    if (d->label)
        d->label->setPos((rectangle.left() + rectangle.width() - 100) / 2 - 50, this->rect().top());
    
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

QList<dtkComposerNodeProperty *> dtkComposerNodeControlBlock::inputProperties(void)
{
    return d->input_properties;
}

QList<dtkComposerNodeProperty *> dtkComposerNodeControlBlock::outputProperties(void)
{
    return d->output_properties;
}

dtkComposerNodeProperty *dtkComposerNodeControlBlock::addInputProperty(QString name, dtkComposerNode *parent)
{
    dtkComposerNodeProperty *property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::HybridInput, dtkComposerNodeProperty::Multiple, parent);
    property->setBlockedFrom(this->title());

    d->input_properties << property;
    
    return property;
}

dtkComposerNodeProperty *dtkComposerNodeControlBlock::addOutputProperty(QString name, dtkComposerNode *parent)
{
    dtkComposerNodeProperty *property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::HybridOutput, dtkComposerNodeProperty::Multiple, parent);
    property->setBlockedFrom(this->title());

    d->output_properties << property;

    return property;
}

void dtkComposerNodeControlBlock::adjustChildNodes(qreal dw, qreal dh)
{
    qreal scaling_factor = 0.5;
    qreal dx;
    qreal dy;
    qreal width;
    qreal height;

    foreach(dtkComposerNode *child, this->nodes()) {
        width  = qAbs(child->mapRectToParent(child->boundingRect()).left() - this->boundingRect().left());
        height = qAbs( child->mapRectToParent(child->boundingRect()).top() -  this->boundingRect().top());        
        dx = scaling_factor * dw *  width /  this->boundingRect().width();
        dy = scaling_factor * dh * height / this->boundingRect().height();
        
        child->setPos(child->pos().x() + dx, child->pos().y() + dy);
    }

    this->update();
}

QRectF dtkComposerNodeControlBlock::minimalBoundingRect(void)
{
    qreal min_height = 75;
    qreal min_width = 200;

    if (this->nodes().count()) {

        QRectF child_rect = this->nodes().first()->mapRectToParent(this->nodes().first()->boundingRect());
        //qreal top  = child_rect.top();
        //qreal left = child_rect.left();
        qreal bottom = child_rect.bottom();
        qreal right  = child_rect.right();

        foreach(dtkComposerNode *child, this->nodes()) {

            child_rect = child->mapRectToParent(child->boundingRect());

            //top = top < child_rect.top() ? top : child_rect.top();
            //left = left < child_rect.left() ? left : child_rect.left();
            bottom = bottom > child_rect.bottom() ? bottom : child_rect.bottom();
            right = right > child_rect.right() ? right : child_rect.right();
        }

        //min_height = (1.1 * qAbs(top - bottom)) > min_height ? (1.1 * qAbs(top - bottom)) : min_height;
        //min_width  = (1.1 * qAbs(right - left)) >  min_width ? (1.1 * qAbs(right - left)) :  min_width;

        min_height = (1.1 * qAbs(this->rect().top() - bottom)) > min_height ? (1.1 * qAbs(this->rect().top() - bottom)) : min_height;
        min_width  = (1.1 * qAbs(right - this->rect().left())) >  min_width ? (1.1 * qAbs(right - this->rect().left())) :  min_width;
    }
    return QRectF(this->rect().top(), this->rect().left(), min_width, min_height);
}

void dtkComposerNodeControlBlock::highlight(dtkComposerNodeControlBlock *block)
{
    static dtkComposerNodeControlBlock *highlighted = NULL;

    if(highlighted == block)
        return;

    if(block) {
        QPropertyAnimation *animation = new QPropertyAnimation(block, "brushColor");
        animation->setDuration(500);
        animation->setKeyValueAt(0.0, Qt::red);
        animation->setKeyValueAt(1.0, Qt::transparent);
        animation->setEasingCurve(QEasingCurve::Linear);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }

    highlighted = block;
}

void dtkComposerNodeControlBlock::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    DTK_UNUSED(event);

    if (d->button)
        d->button->setVisible(true);

    if (d->label)
        d->label->setVisible(true);
}

void dtkComposerNodeControlBlock::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    DTK_UNUSED(event);

    qDebug() << DTK_PRETTY_FUNCTION;

    if (d->button)
        d->button->setVisible(false);

    if (d->label)
        d->label->setVisible(false);
}

void dtkComposerNodeControlBlock::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    DTK_UNUSED(event);
}

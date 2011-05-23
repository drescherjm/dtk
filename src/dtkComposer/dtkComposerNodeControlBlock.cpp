/* dtkComposerNodeControlBlock.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar  3 14:48:10 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon May 23 14:24:28 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 956
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeCase.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeControlBlock_p.h"
#include "dtkComposerNodeLoop.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerScene.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

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
    QFont font("Lucida Grande", 11);
#else
    QFont font("Lucida Grande", 9);
#endif

    this->setDefaultTextColor(Qt::lightGray);
    this->setFont(font);
    this->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->setTextWidth(130);
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
    int origin_y = 0;

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

    QString text;

    bool left;
    bool right;
    bool both;

private:
    dtkComposerNodeControlBlock *block;
};

dtkComposerNodeControlBlockButton::dtkComposerNodeControlBlockButton(dtkComposerNodeControlBlock *parent) : QGraphicsItem(parent)
{
    this->block = parent;
    this->label = NULL;

    this->left = false;
    this->right = false;
    this->both = false;


    this->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
}

dtkComposerNodeControlBlockButton::~dtkComposerNodeControlBlockButton(void)
{

}

QRectF dtkComposerNodeControlBlockButton::boundingRect(void) const
{
    if (this->both)
        return QRectF(0, 0, 50, 11);

    return QRectF(0, 0, 20, 11);
}

void dtkComposerNodeControlBlockButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath s_rect;
    QPainterPath r_rect;
    QPainterPath path;

    if (!this->both) {

        if (this->text == "+") {
            s_rect.addRect(QRectF(option->rect.topLeft(), QSizeF(option->rect.width(), option->rect.height() / 2)));
            r_rect.addRoundedRect(option->rect, 5, 5);
            path = s_rect.united(r_rect);
        }
        if (this->text == "-") {
            s_rect.addRect(QRectF(option->rect.topLeft(), QSizeF(option->rect.width(), option->rect.height())));
            path = s_rect;
        }

    } else {

        s_rect.addRect(QRectF(option->rect.topLeft(), QSizeF(option->rect.width(), option->rect.height() / 2)));
        r_rect.addRoundedRect(option->rect, 5, 5);
        path = s_rect.united(r_rect);

    }

    painter->save();
    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::black);
    painter->drawPath(path);
    painter->restore();
    
#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 8);
#else
    QFont font("Lucida Grande", 6);
#endif
    font.setBold(true);

    QFontMetrics metrics(font);
    
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, this->text);
}

void dtkComposerNodeControlBlockButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if (!this->label)
        return;

    if (this->label->toPlainText().isEmpty()) {
        qDebug() << "Please enter a valid name for the new property.";
        return;
    }

    if (this->text == "+") {

        if (this->left) {

            foreach(dtkComposerNodeProperty *property, block->inputProperties()) {
                if (property->name() == this->label->toPlainText()) {
                    qDebug() << QString("Property %1 already exists. Please choose another name.").arg(property->name());
                    return;
                }
            }

            dtkComposerNodeProperty *input_property = block->addInputProperty(this->label->toPlainText(), block->parentNode());
            if (input_property)
                this->block->parentNode()->addInputProperty(input_property);

        } else if (this->right) { 
            
            foreach(dtkComposerNodeProperty *property, block->outputProperties()) {
                if (property->name() == this->label->toPlainText()) {
                    qDebug() << QString("Property %1 already exists. Please choose another name.").arg(property->name());
                    //dtkLog::debug(QString("Property %1 already exists. Please choose another name.").arg(property->name()));
                    return;
                }
            }

            dtkComposerNodeProperty *output_property = block->addOutputProperty(this->label->toPlainText(), block->parentNode());
            if (output_property)
                this->block->parentNode()->addOutputProperty(output_property);

        } else if (this->both) {

            foreach(dtkComposerNodeControlBlock *other, block->parentNode()->blocks()) { 

                foreach(dtkComposerNodeProperty *property, other->inputProperties()) {
                    if (property->name() == this->label->toPlainText()) {
                        qDebug() << QString("Property %1 already exists. Please choose another name.").arg(property->name());
                        return;
                    }
                }
            
                foreach(dtkComposerNodeProperty *property, other->outputProperties()) {
                    if (property->name() == this->label->toPlainText()) {
                        qDebug() << QString("Property %1 already exists. Please choose another name.").arg(property->name());
                        //dtkLog::debug(QString("Property %1 already exists. Please choose another name.").arg(property->name()));
                        return;
                    }
                }
            }

            foreach(dtkComposerNodeControlBlock *other, block->parentNode()->blocks()) {
                dtkComposerNodeProperty *input_property = other->addInputPassThroughProperty(this->label->toPlainText(), block->parentNode());
                if (input_property)
                    this->block->parentNode()->addInputProperty(input_property);
                dtkComposerNodeProperty *output_property = other->addOutputPassThroughProperty(this->label->toPlainText(), block->parentNode());
                if (output_property)
                    this->block->parentNode()->addOutputProperty(output_property);
            }
        }

    } else if (this->text == "-") {   

        dtkComposerScene *scene = dynamic_cast<dtkComposerScene *>(this->scene());
        if(!scene)
            return;

        if (this->left) {

            foreach(dtkComposerNodeProperty *property, block->inputProperties()) {
                if (property->name() == this->label->toPlainText() && property->type() == dtkComposerNodeProperty::HybridInput) {

                    block->removeInputProperty(property);  
       
                    foreach(dtkComposerEdge *edge, block->parentNode()->inputEdges()) {
                        if(edge->destination() == property) {
                            block->parentNode()->removeInputEdge(edge);
                            scene->removeEdge(edge);
                        }
                    }
                    
                    foreach(dtkComposerEdge *edge, block->parentNode()->inputRelayEdges()) {
                        if(edge->source() == property) {
                            block->parentNode()->removeInputRelayEdge(edge);
                            scene->removeEdge(edge);
                        }
                    }
                    
                    block->parentNode()->removeInputProperty(property);
                    delete property;
                }
            }

        } else if (this->right) {

            foreach(dtkComposerNodeProperty *property, block->outputProperties()) {
                if (property->name() == this->label->toPlainText() && property->type() == dtkComposerNodeProperty::HybridOutput) {
                    
                    block->removeOutputProperty(property);
                    
                    foreach(dtkComposerEdge *edge, block->parentNode()->outputEdges()) {
                        if(edge->source() == property) {
                            block->parentNode()->removeOutputEdge(edge);
                            scene->removeEdge(edge);
                        }
                    }
                    
                    foreach(dtkComposerEdge *edge, block->parentNode()->outputRelayEdges()) {
                        if(edge->destination() == property) {
                            block->parentNode()->removeOutputRelayEdge(edge);
                            scene->removeEdge(edge);
                        }
                    }
                    
                    block->parentNode()->removeOutputProperty(property);
                    delete property;                
                }
            }

        } else if (this->both) {

            foreach(dtkComposerNodeControlBlock *other, block->parentNode()->blocks()) { 

                foreach(dtkComposerNodeProperty *property, other->inputProperties()) {
                    if (property->name() == this->label->toPlainText() && (property->type() == dtkComposerNodeProperty::PassThroughInput || property->type() == dtkComposerNodeProperty::Output)) {

                        other->removeInputProperty(property);
       
                        foreach(dtkComposerEdge *edge, block->parentNode()->inputEdges()) {
                            if(edge->destination() == property) {
                                block->parentNode()->removeInputEdge(edge);
                                scene->removeEdge(edge);
                            }
                        }
                    
                        foreach(dtkComposerEdge *edge, block->parentNode()->inputRelayEdges()) {
                            if(edge->source() == property) {
                                block->parentNode()->removeInputRelayEdge(edge);
                                scene->removeEdge(edge);
                            }
                        }
                    
                        block->parentNode()->removeInputProperty(property);
                        delete property;
                    }
                }

                foreach(dtkComposerNodeProperty *property, other->outputProperties()) {
                    if (property->name() == this->label->toPlainText() && property->type() == dtkComposerNodeProperty::PassThroughOutput) {
                    
                        other->removeOutputProperty(property);
                    
                        foreach(dtkComposerEdge *edge, block->parentNode()->outputEdges()) {
                            if(edge->source() == property) {
                                block->parentNode()->removeOutputEdge(edge);
                                scene->removeEdge(edge);
                            }
                        }
                    
                        foreach(dtkComposerEdge *edge, block->parentNode()->outputRelayEdges()) {
                            if(edge->destination() == property) {
                                block->parentNode()->removeOutputRelayEdge(edge);
                                scene->removeEdge(edge);
                            }
                        }
                    
                        block->parentNode()->removeOutputProperty(property);
                        delete property;                
                    }
                }
            }
        }
    }
    
    block->parentNode()->touch();
    block->parentNode()->resize();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBlock
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlBlock::dtkComposerNodeControlBlock(const QString& title, dtkComposerNodeControl *parent) : QGraphicsRectItem(parent), d(new dtkComposerNodeControlBlockPrivate)
{
    d->parent = parent;
    this->setZValue(parent->zValue());
    
    d->remove_button = new dtkComposerNodeControlBlockButtonRemove(this);
    d->remove_button->setZValue(this->zValue() + 1);
    d->remove_button->hide();

    d->button_add_left = NULL;
    d->button_rem_left = NULL;
    d->button_add_right = NULL;
    d->button_rem_right = NULL;
    d->button_add_both = NULL;
    d->button_rem_both = NULL;
    d->label = NULL;
    
    d->interactive = false;
    d->pen_color = QColor("#c7c7c7");
    d->brush_color = Qt::transparent;
    d->title = title;

    this->setPen(d->pen_color);
    this->setBrush(Qt::NoBrush);

    this->setFlag(QGraphicsItem::ItemStacksBehindParent, false);

    this->setRect(QRectF(0, 0, 250, 100));
    d->height = 100.;
    d->height_ratio = 1.0;
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

    if(!d->button_add_left) {
        d->button_add_left = new dtkComposerNodeControlBlockButton(this);
        d->button_add_left->setZValue(this->zValue() - 1);
        d->button_add_left->setVisible(!d->interactive);
        d->button_add_left->left = true;
    }

    if(!d->button_rem_left) {
        d->button_rem_left = new dtkComposerNodeControlBlockButton(this);
        d->button_rem_left->setZValue(this->zValue() - 1);
        d->button_rem_left->setVisible(!d->interactive);
        d->button_rem_left->left = true;
    }

    if(!d->button_add_right) {
        d->button_add_right = new dtkComposerNodeControlBlockButton(this);
        d->button_add_right->setZValue(this->zValue() - 1);
        d->button_add_right->setVisible(!d->interactive);
        d->button_add_right->right = true;
    }

    if(!d->button_rem_right) {
        d->button_rem_right = new dtkComposerNodeControlBlockButton(this);
        d->button_rem_right->setZValue(this->zValue() - 1);
        d->button_rem_right->setVisible(!d->interactive);
        d->button_rem_right->right = true;
    }

    if(!d->button_add_both && this->title() == "loop") {
        d->button_add_both = new dtkComposerNodeControlBlockButton(this);
        d->button_add_both->setZValue(this->zValue() - 1);
        d->button_add_both->setVisible(!d->interactive);
        d->button_add_both->both = true;
    }

    if(!d->button_rem_both && this->title() == "loop") {
        d->button_rem_both = new dtkComposerNodeControlBlockButton(this);
        d->button_rem_both->setZValue(this->zValue() - 1);
        d->button_rem_both->setVisible(!d->interactive);
        d->button_rem_both->both = true;
    }

    if(!d->label) {
        d->label = new dtkComposerNodeControlBlockLabel(this);
        d->label->setZValue(this->zValue() - 1);
        d->label->setVisible(!d->interactive);

        if(d->button_add_left)
            if(!d->button_add_left->label)
                d->button_add_left->label = d->label;

        if(d->button_rem_left)
            if(!d->button_rem_left->label)
                d->button_rem_left->label = d->label;

        if(d->button_add_right)
            if(!d->button_add_right->label)
                d->button_add_right->label = d->label;

        if(d->button_rem_right)
            if(!d->button_rem_right->label)
                d->button_rem_right->label = d->label;

        if(d->button_add_both)
            if(!d->button_add_both->label)
                d->button_add_both->label = d->label;

        if(d->button_rem_both)
            if(!d->button_rem_both->label)
                d->button_rem_both->label = d->label;
    }

    // if(d->interactive && !d->button_add_left) {
    //     d->button_add_left = new dtkComposerNodeControlBlockButton(this);
    //     d->button_add_left->setZValue(this->zValue() - 1);
    //     d->button_add_left->setVisible(false);
    //     d->button_add_left->left = true;
    // }

    // if(d->interactive && !d->button_rem_left) {
    //     d->button_rem_left = new dtkComposerNodeControlBlockButton(this);
    //     d->button_rem_left->setZValue(this->zValue() - 1);
    //     d->button_rem_left->setVisible(false);
    //     d->button_rem_left->left = true;
    // }

    // if(d->interactive && !d->button_add_right) {
    //     d->button_add_right = new dtkComposerNodeControlBlockButton(this);
    //     d->button_add_right->setZValue(this->zValue() - 1);
    //     d->button_add_right->setVisible(false);
    //     d->button_add_right->right = true;
    // }

    // if(d->interactive && !d->button_rem_right) {
    //     d->button_rem_right = new dtkComposerNodeControlBlockButton(this);
    //     d->button_rem_right->setZValue(this->zValue() - 1);
    //     d->button_rem_right->setVisible(false);
    //     d->button_rem_right->right = true;
    // }

    // if(d->interactive && !d->button_add_both && this->title() == "loop") {
    //     d->button_add_both = new dtkComposerNodeControlBlockButton(this);
    //     d->button_add_both->setZValue(this->zValue() - 1);
    //     d->button_add_both->setVisible(false);
    //     d->button_add_both->both = true;
    // }

    // if(d->interactive && !d->button_rem_both && this->title() == "loop") {
    //     d->button_rem_both = new dtkComposerNodeControlBlockButton(this);
    //     d->button_rem_both->setZValue(this->zValue() - 1);
    //     d->button_rem_both->setVisible(false);
    //     d->button_rem_both->both = true;
    // }

    // if(d->interactive && !d->label) {
    //     d->label = new dtkComposerNodeControlBlockLabel(this);
    //     d->label->setZValue(this->zValue() - 1);
    //     d->label->setVisible(false);

    //     if(d->button_add_left)
    //         if(!d->button_add_left->label)
    //             d->button_add_left->label = d->label;

    //     if(d->button_rem_left)
    //         if(!d->button_rem_left->label)
    //             d->button_rem_left->label = d->label;

    //     if(d->button_add_right)
    //         if(!d->button_add_right->label)
    //             d->button_add_right->label = d->label;

    //     if(d->button_rem_right)
    //         if(!d->button_rem_right->label)
    //             d->button_rem_right->label = d->label;

    //     if(d->button_add_both)
    //         if(!d->button_add_both->label)
    //             d->button_add_both->label = d->label;

    //     if(d->button_rem_both)
    //         if(!d->button_rem_both->label)
    //             d->button_rem_both->label = d->label;
    // }
    
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
        d->remove_button->setPos(rectangle.left() + 0.5 * rectangle.width(), this->rect().bottom());
    
    if (d->button_add_left) {
        d->button_add_left->text = "+";
        d->button_add_left->setPos(rectangle.left() + (rectangle.width() - d->label->boundingRect().width()) / 2 - d->button_add_left->boundingRect().width(), this->rect().top() + d->button_add_left->boundingRect().height());
    }
    
    if (d->button_rem_left) {
        d->button_rem_left->text = "-";
        d->button_rem_left->setPos(rectangle.left() + (rectangle.width() - d->label->boundingRect().width()) / 2 - d->button_rem_left->boundingRect().width(), this->rect().top());
    }
        
    if (d->button_add_right) {
        d->button_add_right->text = "+";
        d->button_add_right->setPos(rectangle.left() + (rectangle.width() + d->label->boundingRect().width()) / 2, this->rect().top() + d->button_add_right->boundingRect().height());
    }
    
    if (d->button_rem_right) {
        d->button_rem_right->text = "-";
        d->button_rem_right->setPos(rectangle.left() + (rectangle.width() + d->label->boundingRect().width()) / 2, this->rect().top());
    }
        
    if (d->button_add_both) {
        d->button_add_both->text = "+";
        d->button_add_both->setPos(rectangle.left() + rectangle.width() / 2, this->rect().top() + d->label->boundingRect().height());
    }
    
    if (d->button_rem_both) {
        d->button_rem_both->text = "-";
        d->button_rem_both->setPos(rectangle.left() + rectangle.width() / 2 - d->button_rem_both->boundingRect().width(), this->rect().top() + d->label->boundingRect().height());
    }
    
    if (d->label)
        d->label->setPos(rectangle.left() + (rectangle.width() - d->label->boundingRect().width()) / 2, this->rect().top());
    
    QGraphicsRectItem::setRect(rectangle);
}

void dtkComposerNodeControlBlock::setRect(qreal x, qreal y, qreal width, qreal height)
{
    this->setRect(QRectF(x, y, width, height));
}

QList<dtkComposerNode *> dtkComposerNodeControlBlock::nodes(void)
{
    return d->nodes;
}

QList<dtkComposerNode *> dtkComposerNodeControlBlock::startNodes(void)
{
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerNode *node, this->nodes())
        if (!node->inputEdges().count() && node->outputEdges().count())
            nodes << node;

    foreach(dtkComposerEdge *edge, d->parent->inputRelayEdges())
        if (edge->source()->blockedFrom() == this->title() && !nodes.contains(edge->destination()->node()))
            nodes << edge->destination()->node();

    return nodes;
}

QList<dtkComposerNode *> dtkComposerNodeControlBlock::endNodes(void)
{
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerNode *node, this->nodes())
        if(!node->outputEdges().count() && node->inputEdges().count())
            nodes << node;

    foreach(dtkComposerEdge *edge, d->parent->outputRelayRoutes())
        if (edge->destination()->blockedFrom() == this->title() && !nodes.contains(edge->source()->node()))
            nodes << edge->source()->node();

    return nodes;
}

void dtkComposerNodeControlBlock::addNode(dtkComposerNode *node)
{
    if (!d->nodes.contains(node))
        d->nodes << node;
}

void dtkComposerNodeControlBlock::removeNode(dtkComposerNode *node)
{
    d->nodes.removeAll(node);
}

void dtkComposerNodeControlBlock::removeAllNodes(void)
{
    d->nodes.clear();
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
    dtkComposerNodeProperty *property = NULL;
    dtkComposerNodeCase *node_case = dynamic_cast<dtkComposerNodeCase *>(d->parent);
    dtkComposerNodeLoop *node_loop = dynamic_cast<dtkComposerNodeLoop *>(d->parent);

    if (node_case) {

        if (name == "constant") {

            property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, parent);

        } else if (name == "variable") {

            property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, parent);

        } else {

            property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::HybridInput, dtkComposerNodeProperty::Multiple, parent);

        }

    } else if (node_loop) {

        if (name == "variable") {

            property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, parent);
            property->setBehavior(dtkComposerNodeProperty::AsLoopInput);

        } else {

            property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::HybridInput, dtkComposerNodeProperty::Multiple, parent);

        }

    } else {

        property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::HybridInput, dtkComposerNodeProperty::Multiple, parent);

    }

    property->setBlockedFrom(this->title());

    d->input_properties << property;
    
    return property;
}

dtkComposerNodeProperty *dtkComposerNodeControlBlock::addOutputProperty(QString name, dtkComposerNode *parent)
{
    dtkComposerNodeProperty *property = NULL;
    dtkComposerNodeCase *node_case = NULL;
    dtkComposerNodeLoop *node_loop = NULL;

    if ((node_case = dynamic_cast<dtkComposerNodeCase *>(d->parent)) && (name == "variable")) {

        property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, parent);

    } else if (node_loop = dynamic_cast<dtkComposerNodeLoop *>(d->parent)) {

        if (this->title() == "loop" && name == "variable") {

            property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, parent);

        } else if (this->title() == "post" && name == "variable") {

            property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, parent);
            property->setBehavior(dtkComposerNodeProperty::AsLoopOutput);

        } else if (this->title() == "condition" && name == "condition") {

            property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, parent);
            property->setBehavior(dtkComposerNodeProperty::AsLoopOutput);

        } else {

            property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::HybridOutput, dtkComposerNodeProperty::Multiple, parent);

        }

    } else {

        property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::HybridOutput, dtkComposerNodeProperty::Multiple, parent);

    }

    property->setBlockedFrom(this->title());

    d->output_properties << property;

    return property;
}

dtkComposerNodeProperty *dtkComposerNodeControlBlock::addInputPassThroughProperty(QString name, dtkComposerNode *parent)
{
    dtkComposerNodeProperty *property = NULL;
    dtkComposerNodeLoop *node_loop = dynamic_cast<dtkComposerNodeLoop *>(d->parent);

    if (node_loop) {

        if (this->title() == "loop")
            property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::PassThroughInput, dtkComposerNodeProperty::Single, parent);
        else
            property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, parent);

        property->setBlockedFrom(this->title());
        
        d->input_properties << property;
    }
    
    return property;
}

dtkComposerNodeProperty *dtkComposerNodeControlBlock::addOutputPassThroughProperty(QString name, dtkComposerNode *parent)
{
    dtkComposerNodeProperty *property = NULL;
    dtkComposerNodeLoop *node_loop = dynamic_cast<dtkComposerNodeLoop *>(d->parent);

    if (node_loop) {
        if (this->title() == "loop") {
            property = new dtkComposerNodeProperty(name, dtkComposerNodeProperty::PassThroughOutput, dtkComposerNodeProperty::Single, parent);

            property->setBlockedFrom(this->title());
            
            d->output_properties << property;
        }
    }
    
    return property;
}

void dtkComposerNodeControlBlock::removeInputProperty(dtkComposerNodeProperty *property)
{
    d->input_properties.removeAll(property);
}

void dtkComposerNodeControlBlock::removeOutputProperty(dtkComposerNodeProperty *property)
{
    d->output_properties.removeAll(property);
}

void dtkComposerNodeControlBlock::removeAllProperties(void)
{
    d->input_properties.clear();
    d->output_properties.clear();
}

qreal dtkComposerNodeControlBlock::height(void)
{
    return d->height;
}

qreal dtkComposerNodeControlBlock::heightRatio(void)
{
    return d->height_ratio;
}

void dtkComposerNodeControlBlock::setHeight(qreal height)
{
    d->height = height;
}

void dtkComposerNodeControlBlock::setHeightRatio(qreal height_ratio)
{
    d->height_ratio = height_ratio;
}

void dtkComposerNodeControlBlock::adjustChildNodes(qreal dw, qreal dh)
{
    qreal scaling_factor = 0.05;
    qreal dx;
    qreal dy;
    qreal width;
    qreal height;

    qreal block_left = this->boundingRect().left();
    qreal block_top  = this->boundingRect().top();
    qreal block_width  = this->boundingRect().width();
    qreal block_height = this->boundingRect().height();

    foreach(dtkComposerNode *child, this->nodes()) {
        width  = qAbs(child->mapRectToParent(child->boundingRect()).left() - block_left);
        height = qAbs( child->mapRectToParent(child->boundingRect()).top() - block_top);        
        dx = scaling_factor * dw *  width / block_width;
        dy = scaling_factor * dh * height / block_height;
        
        child->setPos(child->pos().x() + dx, child->pos().y() + dy);
    }

    this->update();
}

QRectF dtkComposerNodeControlBlock::minimalBoundingRect(void)
{
    QRectF prop_rect;
    foreach(dtkComposerNodeProperty *p, d->input_properties)
        prop_rect = prop_rect.united(p->mapRectToParent(p->boundingRect()));
    foreach(dtkComposerNodeProperty *p, d->output_properties)
        prop_rect = prop_rect.united(p->mapRectToParent(p->boundingRect()));

    qreal min_height = 170;
    qreal  min_width = 370;
    min_height = prop_rect.height() > min_height ? prop_rect.height() : min_height;
    QRectF block_rect(this->boundingRect().left(), this->boundingRect().top(), min_width, min_height);

    QList<dtkComposerNode *> block_nodes = this->nodes();

    foreach(dtkComposerNode *child, block_nodes)
        block_rect = block_rect.united(child->mapRectToParent(child->boundingRect()));
    
    block_rect.setWidth(block_rect.width() + 30);
    block_rect.setHeight(block_rect.height() + 30);

    return block_rect;
}

void dtkComposerNodeControlBlock::highlight(bool ok)
{
    if (ok) {

        foreach(dtkComposerNodeControlBlock *block, d->parent->blocks())
            block->stackBefore(this);

        QPropertyAnimation *p_animation = new QPropertyAnimation(this, "penColor");
        p_animation->setDuration(300);
        p_animation->setKeyValueAt(0.0, Qt::green);
        p_animation->setKeyValueAt(1.0, Qt::white);
        p_animation->setEndValue(Qt::white);
        p_animation->setEasingCurve(QEasingCurve::Linear);
        p_animation->start(QAbstractAnimation::DeleteWhenStopped);

        // QPropertyAnimation *b_animation = new QPropertyAnimation(this, "brushColor");
        // b_animation->setDuration(300);
        // b_animation->setKeyValueAt(0.0, Qt::blue);
        // b_animation->setKeyValueAt(1.0, Qt::transparent);
        // b_animation->setEasingCurve(QEasingCurve::Linear);
        // b_animation->start(QAbstractAnimation::DeleteWhenStopped);

    } else {

        QPropertyAnimation *p_animation = new QPropertyAnimation(this, "penColor");
        p_animation->setDuration(300);
        p_animation->setKeyValueAt(0.0, Qt::red);
        p_animation->setKeyValueAt(1.0, Qt::white);
        p_animation->setEndValue(Qt::white);
        p_animation->setEasingCurve(QEasingCurve::Linear);
        p_animation->start(QAbstractAnimation::DeleteWhenStopped);

        // QPropertyAnimation *animation = new QPropertyAnimation(this, "brushColor");
        // animation->setDuration(250);
        // animation->setKeyValueAt(0.0, Qt::darkRed);
        // animation->setKeyValueAt(1.0, Qt::transparent);
        // animation->setEasingCurve(QEasingCurve::Linear);
        // animation->start(QAbstractAnimation::DeleteWhenStopped);

    }
}

void dtkComposerNodeControlBlock::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    DTK_UNUSED(event);
                           
    if (d->button_add_left)
        d->button_add_left->setVisible(true);

    if (d->button_rem_left)
        d->button_rem_left->setVisible(true);
                           
    if (d->button_add_right)
        d->button_add_right->setVisible(true);

    if (d->button_rem_right)
        d->button_rem_right->setVisible(true);
                           
    if (d->button_add_both)
        d->button_add_both->setVisible(true);

    if (d->button_rem_both)
        d->button_rem_both->setVisible(true);

    if (d->label)
        d->label->setVisible(true);
}

void dtkComposerNodeControlBlock::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    DTK_UNUSED(event);

    if (d->button_add_left)
        d->button_add_left->setVisible(false);

    if (d->button_rem_left)
        d->button_rem_left->setVisible(false);

    if (d->button_add_right)
        d->button_add_right->setVisible(false);

    if (d->button_rem_right)
        d->button_rem_right->setVisible(false);

    if (d->button_add_both)
        d->button_add_both->setVisible(false);

    if (d->button_rem_both)
        d->button_rem_both->setVisible(false);

    if (d->label)
        d->label->setVisible(false);
}

void dtkComposerNodeControlBlock::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    DTK_UNUSED(event);
}

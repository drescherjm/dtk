/* dtkComposerNodeControlBlock.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar  3 14:48:10 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  7 15:57:24 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 1164
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
#include "dtkComposerRoute.h"
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

    this->block->parentNode()->removeBlock(this->block);
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

            this->block->parentNode()->appendBlockLeftProperty(this->label->toPlainText(), dtkComposerNodeProperty::AsRelay, dtkComposerNodeProperty::Multiple, this->block);

        } else if (this->right) { 

            this->block->parentNode()->appendBlockRightProperty(this->label->toPlainText(), dtkComposerNodeProperty::AsRelay, dtkComposerNodeProperty::Multiple, this->block);

        } else if (this->both) {          

            foreach(dtkComposerNodeControlBlock *other, block->parentNode()->blocks()) {

                if (other != this->block)
                    this->block->parentNode()->appendBlockLeftProperty(this->label->toPlainText(), dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, other);
                else
                   this->block->parentNode()->appendBlockProperty(this->label->toPlainText(), dtkComposerNodeProperty::AsLoop, dtkComposerNodeProperty::Multiple, other); 

            }

        }

    } else if (this->text == "-") {

        if (this->left) {

            this->block->parentNode()->removeBlockLeftProperty(this->label->toPlainText(), dtkComposerNodeProperty::AsRelay, this->block);

        } else if (this->right) {

            this->block->parentNode()->removeBlockRightProperty(this->label->toPlainText(), dtkComposerNodeProperty::AsRelay, this->block);

        } else if (this->both) {            

            foreach(dtkComposerNodeControlBlock *other, block->parentNode()->blocks()) {

                if (other != this->block)
                    this->block->parentNode()->removeBlockLeftProperty(this->label->toPlainText(), dtkComposerNodeProperty::AsOutput, other);
                else
                   this->block->parentNode()->removeBlockProperty(this->label->toPlainText(), dtkComposerNodeProperty::AsLoop, other); 

            }

        }
    }
    
    block->parentNode()->touch();
    block->parentNode()->resize();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBlock
// /////////////////////////////////////////////////////////////////

//! Constructs a block for a control node.
/*! 
 *  
 */
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

//! Destroys block.
/*! 
 *  
 */
dtkComposerNodeControlBlock::~dtkComposerNodeControlBlock(void)
{
    delete d;

    d = NULL;
}

//! Returns node that contains the block.
/*! 
 *  
 */
dtkComposerNodeControl *dtkComposerNodeControlBlock::parentNode(void) const
{
    return d->parent;
}

//! Returns title of the block.
/*! 
 *  
 */
QString dtkComposerNodeControlBlock::title(void) const
{
    return d->title;
}

//! Appends \a node in the list of nodes.
/*! 
 *  
 */
void dtkComposerNodeControlBlock::appendNode(dtkComposerNode *node)
{
    if(!d->nodes.contains(node))
        d->nodes << node;
}

//! Removes \a node from the list of nodes.
/*! 
 *  
 */
void dtkComposerNodeControlBlock::removeNode(dtkComposerNode *node)
{
    d->nodes.removeAll(node);
}

//! Clears list of nodes.
/*! 
 *  
 */
void dtkComposerNodeControlBlock::removeAllNodes(void)
{
    d->nodes.clear();
}

//! Appends \a property in list of left properties.
/*! 
 *  
 */
void dtkComposerNodeControlBlock::appendLeftProperty(dtkComposerNodeProperty *property)
{ 
    if (d->left_properties.contains(property))
        return;

    d->left_properties << property;
}

//! Appends \a property in list of right properties.
/*! 
 *  
 */
void dtkComposerNodeControlBlock::appendRightProperty(dtkComposerNodeProperty *property)
{ 
    if (d->right_properties.contains(property))
        return;

    d->right_properties << property;
}

//! Removes \a property from list of left properties
/*! 
 *  
 */
void dtkComposerNodeControlBlock::removeLeftProperty(dtkComposerNodeProperty *property)
{
    d->left_properties.removeAll(property);
}

//! Removes \a property from list of right properties
/*! 
 *  
 */
void dtkComposerNodeControlBlock::removeRightProperty(dtkComposerNodeProperty *property)
{
    d->right_properties.removeAll(property);
}

//! Clears left and right lists of properties
/*! 
 *  
 */
void dtkComposerNodeControlBlock::removeAllProperties(void)
{
    d->left_properties.clear();
    d->right_properties.clear();
}

//! Clears all nodes, edges and properties that the node contains.
/*! 
 *  
 */
void dtkComposerNodeControlBlock::clear(void)
{
    dtkComposerScene *scene = dynamic_cast<dtkComposerScene *>(d->parent->scene());
    if(!scene)
        return;

    foreach(dtkComposerNode *child, d->nodes)
        scene->removeNode(child);
    
    foreach(dtkComposerNodeProperty *property, d->left_properties) {
        
        foreach(dtkComposerEdge *edge, d->parent->g->leftEdges()) {
            if(edge->destination() == property)
                scene->removeEdge(edge);
        }
        
        foreach(dtkComposerEdge *edge, d->parent->g->leftRelayEdges()) {
            if(edge->source() == property)
                scene->removeEdge(edge);
        }
        
        d->parent->g->removeLeftProperty(property);
        delete property;
    }
        
    foreach(dtkComposerNodeProperty *property, d->right_properties) {
       
        foreach(dtkComposerEdge *edge, d->parent->g->rightEdges()) {
            if(edge->source() == property)
                scene->removeEdge(edge);
        }
        
        foreach(dtkComposerEdge *edge, d->parent->g->rightRelayEdges()) {
            if(edge->destination() == property)
                scene->removeEdge(edge);
        }
        
        d->parent->g->removeRightProperty(property);
        delete property;
    }
}

//! Returns the list of nodes.
/*! 
 *  
 */
const QList<dtkComposerNode *>& dtkComposerNodeControlBlock::nodes(void) const
{
    return d->nodes;
}

//! Returns the list of start nodes.
/*! 
 *  There are two types of start nodes: the ones with no left edges
 *  but with right edges and the ones that are connected to left
 *  properties of the block.
 */
QList<dtkComposerNode *> dtkComposerNodeControlBlock::startNodes(QList<dtkComposerNode *> parents)
{
    QList<dtkComposerNode *> nodes;
    QList<dtkComposerNode *> scope;

    if(parents.isEmpty())
        scope = this->nodes();
    else
        scope = parents;

    foreach(dtkComposerNode *node, scope) {

        if (node->kind() != dtkComposerNode::Composite) {

            if(!node->g->leftEdges().count() && node->g->rightEdges().count()) {
                node->setDirty(true);
                nodes << node;
            } else {
                foreach(dtkComposerRoute *edge, d->parent->inputRelayRoutes()) {
                    if (edge->source()->blockedFrom() == this->title() && !nodes.contains(edge->destination()->node())) {
                        dtkComposerNode *node = edge->destination()->node();
                        node->setDirty(true);
                        nodes << node;
                    }
                }
            }
        } else {
            nodes << this->startNodes(node->childNodes());
        }
    }

    // foreach(dtkComposerNode *node, scope) {
    //     if (node->kind() != dtkComposerNode::Composite) {
    //         node->setDirty(true);
    //         nodes << node;
    //     } else {
    //         nodes << this->startNodes(node->childNodes());
    //     }
    // }

    return nodes;
}

//! Returns the list of left properties.
/*! 
 *  
 */
const QList<dtkComposerNodeProperty *>& dtkComposerNodeControlBlock::leftProperties(void) const
{
    return d->left_properties;
}

//! Returns the list of right properties.
/*! 
 *  
 */
const QList<dtkComposerNodeProperty *>& dtkComposerNodeControlBlock::rightProperties(void) const
{
    return d->right_properties;
}

//! Returns the property defined by its \a name and its \a position.
/*! 
 *  The property is searched in both left and right lists. When input
 *  \a name does not match with any property, NULL is returned.
 */
dtkComposerNodeProperty *dtkComposerNodeControlBlock::property(QString name, dtkComposerNodeProperty::Position position)
{
    switch(position) {
    case dtkComposerNodeProperty::Left:
        foreach(dtkComposerNodeProperty *property, d->left_properties) {
            if(property->name() == name)
                return property;
        }
        break;
    case dtkComposerNodeProperty::Right:
        foreach(dtkComposerNodeProperty *property, d->right_properties) {
            if(property->name() == name)
                return property;
        }        
        break;
    }

    return NULL;
}

// /////////////////////////////////////////////////////////////////
// Methods dealing with graphical aspects.
// /////////////////////////////////////////////////////////////////

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

//! Returns height of the block.
/*! 
 *  
 */
qreal dtkComposerNodeControlBlock::height(void)
{
    return d->height;
}

//! Returns height ratio of the block.
/*! 
 *  
 */
qreal dtkComposerNodeControlBlock::heightRatio(void)
{
    return d->height_ratio;
}

//! Sets the value of block height.
/*! 
 *  Calls also prepareGeometryChange().
 */
void dtkComposerNodeControlBlock::setHeight(qreal height)
{
    this->prepareGeometryChange();

    d->height = height;
}

//! Sets the value of block height ratio.
/*! 
 *  
 */
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
    foreach(dtkComposerNodeProperty *p, d->left_properties)
        prop_rect = prop_rect.united(p->mapRectToParent(p->boundingRect()));
    foreach(dtkComposerNodeProperty *p, d->right_properties)
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

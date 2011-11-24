/* dtkComposerNodeNumber.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Feb 25 16:21:13 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 21 09:51:20 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 627
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeTransmitter.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberLabel declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberLabel : public QGraphicsItem
{
public:
     dtkComposerNodeNumberLabel(dtkComposerNodeNumber *parent);
    ~dtkComposerNodeNumberLabel(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

public:
    void setLabelText(const QString& value);

public:
    dtkComposerNodeNumber *parent_node;
    QPainterPath path;
    QString text;
    bool expanded;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberLabel implementation
// /////////////////////////////////////////////////////////////////

//! Constructs number label.
/*! 
 *  
 */
dtkComposerNodeNumberLabel::dtkComposerNodeNumberLabel(dtkComposerNodeNumber *parent) : QGraphicsItem(parent)
{
    int margin = 10;
    int length = 77;
    int height = 15;
    int radius =  5;
    int origin_x = parent->boundingRect().width() / 2 - length - margin;
    int origin_y = -parent->boundingRect().height() / 2;

    QPainterPath b; b.addRoundedRect(origin_x,              origin_y, margin,          height,     radius, radius);
    QPainterPath c; c.addRoundedRect(origin_x + margin,     origin_y, length - margin, height,     radius, radius);
    QPainterPath d; d.addRoundedRect(origin_x + length,     origin_y, margin,          height,     radius, radius);
    QPainterPath e; e.addRoundedRect(origin_x + margin / 2, origin_y, length,          height / 2,      0,      0);

    path = c.united(e.subtracted(b.united(c.united(d))));

    parent_node = parent;

    text = "";

    expanded = false;
}

//! Destroys number label.
/*! 
 *  
 */
dtkComposerNodeNumberLabel::~dtkComposerNodeNumberLabel(void)
{

}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
QRectF dtkComposerNodeNumberLabel::boundingRect(void) const
{
    return path.boundingRect();
}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
void dtkComposerNodeNumberLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    QFont font("Lucida Grande", 11);
#else
    QFont font("Lucida Grande", 9);
#endif
    font.setBold(true);

    QFontMetrics metrics(font);
    
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, text);
}

//! Sets label text.
/*! 
 *  
 */
void dtkComposerNodeNumberLabel::setLabelText(const QString& value)
{
    text = value;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberButton declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberButton : public QGraphicsItem
{
public:
     dtkComposerNodeNumberButton(dtkComposerNodeNumber *parent);
    ~dtkComposerNodeNumberButton(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeNumber *parent_node;
    QPainterPath path;
    QString text;
    bool expanded;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberButton implementation
// /////////////////////////////////////////////////////////////////

//! Constructs number button.
/*! 
 *  It enables to hide or show edition aera.
 */
dtkComposerNodeNumberButton::dtkComposerNodeNumberButton(dtkComposerNodeNumber *parent) : QGraphicsItem(parent)
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

    path = c.united(e.subtracted(b.united(c.united(d))));

    parent_node = parent;
    
    text = "+";

    expanded = false;
}

//! Destroys number button.
/*! 
 *  
 */
dtkComposerNodeNumberButton::~dtkComposerNodeNumberButton(void)
{

}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
QRectF dtkComposerNodeNumberButton::boundingRect(void) const
{
    return path.boundingRect();
}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
void dtkComposerNodeNumberButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

//! Enables to expand or collapse edition aera.
/*! 
 *  Reimplemented from QGraphicsItem.
 */
void dtkComposerNodeNumberButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if(!this->expanded) {
        parent_node->expand();
        text = "-";
    } else {
        parent_node->collapse();
        text = "+";
    }
        
    parent_node->touch();

    this->expanded = !this->expanded;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberEditor declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberEditor : public QGraphicsTextItem
{
public:
    dtkComposerNodeNumberEditor(dtkComposerNodeNumber *parent);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    dtkComposerNodeNumber *parent_node;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberEditor implementation
// /////////////////////////////////////////////////////////////////

//! Constructs number editor.
/*! 
 *  It enables to edit the text of the number node.
 */
dtkComposerNodeNumberEditor::dtkComposerNodeNumberEditor(dtkComposerNodeNumber *parent) : QGraphicsTextItem(parent)
{
#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 10);
#else
    QFont font("Lucida Grande", 8);
#endif

    this->setDefaultTextColor(Qt::lightGray);
    this->setFont(font);
    this->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->setFlag(QGraphicsItem::ItemStacksBehindParent, true);

    this->parent_node = parent;
}

//! 
/*! 
 *  Reimplemented from QGraphicsTextItem.
 */
void dtkComposerNodeNumberEditor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

//! 
/*! 
 *  Reimplemented from QGraphicsTextItem.
 */
void dtkComposerNodeNumberEditor::keyPressEvent(QKeyEvent *event)
{
    QGraphicsTextItem::keyPressEvent(event);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberPrivate
{
public:
    dtkComposerNodeNumberLabel *label;
    dtkComposerNodeNumberButton *button;
    dtkComposerNodeNumberEditor *editor;

public:
    QPropertyAnimation *animation;

public:
    bool interactive;

public:
    QVariant::Type genre;    
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumber implementation
// /////////////////////////////////////////////////////////////////

//! Constructs number node.
/*! 
 *  Number node is interactive by while it has no left edge.
 */
dtkComposerNodeNumber::dtkComposerNodeNumber(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeNumberPrivate)
{
    d->label = new dtkComposerNodeNumberLabel(this);
    d->label->setPos(0, 0);

    d->button = new dtkComposerNodeNumberButton(this);
    d->button->setPos(0, 0);
    
    d->editor = new dtkComposerNodeNumberEditor(this);
    d->editor->setPos(-d->editor->boundingRect().width() / 2, 0);
    d->editor->setTextWidth(0.8 * this->boundingRect().width());
    d->editor->hide();

    d->animation = new QPropertyAnimation(d->editor, "pos");
    d->animation->setDuration(500);
    d->animation->setStartValue(QPointF(-d->editor->boundingRect().width()/2, 0));
    d->animation->setEndValue(QPointF(-d->editor->boundingRect().width()/2, 0.85 * d->editor->boundingRect().height()));
    d->animation->setEasingCurve(QEasingCurve::OutBounce);

    d->interactive = true;

    d->genre = QVariant::Invalid;
}

//! Destroys number node.
/*! 
 *  
 */
dtkComposerNodeNumber::~dtkComposerNodeNumber(void)
{
    delete d;

    d = NULL;
}

//! Sets number type using QVariant flags.
/*! 
 *  
 */
void dtkComposerNodeNumber::setGenre(const QVariant::Type& genre)
{
    d->genre = genre;
}

//! Returns number type using QVariant flags.
/*! 
 *  
 */
const QVariant::Type& dtkComposerNodeNumber::genre(void) const
{
    return d->genre;
}

//! Sets the label of the node.
/*! 
 *  
 */
void dtkComposerNodeNumber::setLabelText(const QString& value)
{
    d->label->setLabelText(value);
}

//! Sets the text of the node.
/*! 
 *  
 */
void dtkComposerNodeNumber::setEditorText(const QString& value)
{
    d->editor->setPlainText(value);
}

//! Turns on interactive mode.
/*! 
 *  
 */
void dtkComposerNodeNumber::interactiveOn(void)
{
    d->interactive = true;
    d->editor->setTextInteractionFlags(Qt::TextEditorInteraction);
}

//! Turns off interactive mode.
/*! 
 *  
 */
void dtkComposerNodeNumber::interactiveOff(void)
{
    d->interactive = false;
    d->editor->setTextInteractionFlags(Qt::NoTextInteraction);
    d->editor->setPlainText("");
}

//! Returns true when interactive mode is on. 
/*! 
 *  
 */
QString dtkComposerNodeNumber::editorText(void) const
{
    return d->editor->toPlainText();
}

//! Returns true when interactive mode is on. 
/*! 
 *  
 */
bool dtkComposerNodeNumber::isInteractive(void) const
{
    return d->interactive;
}

//! Expands node to show edition aera.
/*! 
 *  
 */
void dtkComposerNodeNumber::expand(void)
{
    d->editor->show();
    d->animation->setDirection(QAbstractAnimation::Forward);
    d->animation->start();
}

//! Collapses node to hide edition aera.
/*! 
 *  
 */
void dtkComposerNodeNumber::collapse(void)
{
    d->animation->setDirection(QAbstractAnimation::Backward);
    d->animation->start();

    connect(d->animation, SIGNAL(finished()), this, SLOT(onCollapseFinised()));
}

//! Hides edition aera at the end of collapsing.
/*! 
 *  
 */
void dtkComposerNodeNumber::onCollapseFinised(void)
{
    d->editor->hide();

    disconnect(d->animation, SIGNAL(finished()), this, SLOT(onCollapseFinised()));
}

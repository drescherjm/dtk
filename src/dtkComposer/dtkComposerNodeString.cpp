/* dtkComposerNodeString.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 15:12:01 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 14:39:45 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 430
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeTransmitter.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringButton declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringButton : public QGraphicsItem
{
public:
     dtkComposerNodeStringButton(dtkComposerNodeString *parent);
    ~dtkComposerNodeStringButton(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeString *parent_node;
    QPainterPath path;
    QString text;
    bool expanded;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringButton implementation
// /////////////////////////////////////////////////////////////////

//! Constructs string button.
/*! 
 *  It enables to hide or show edition aera.
 */
dtkComposerNodeStringButton::dtkComposerNodeStringButton(dtkComposerNodeString *parent) : QGraphicsItem(parent)
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

//! Destroys string button.
/*! 
 *  
 */
dtkComposerNodeStringButton::~dtkComposerNodeStringButton(void)
{

}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
QRectF dtkComposerNodeStringButton::boundingRect(void) const
{
    return path.boundingRect();
}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
void dtkComposerNodeStringButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
void dtkComposerNodeStringButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
// dtkComposerNodeStringEditor declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringEditor : public QGraphicsTextItem
{
public:
    dtkComposerNodeStringEditor(dtkComposerNodeString *parent);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    dtkComposerNodeString *parent_node;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringEditor implementation
// /////////////////////////////////////////////////////////////////

//! Constructs string editor.
/*! 
 *  It enables to edit the text of the string node.
 */
dtkComposerNodeStringEditor::dtkComposerNodeStringEditor(dtkComposerNodeString *parent) : QGraphicsTextItem(parent)
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
void dtkComposerNodeStringEditor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
void dtkComposerNodeStringEditor::keyPressEvent(QKeyEvent *event)
{
    QGraphicsTextItem::keyPressEvent(event);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringPrivate
{
public:
    dtkComposerNodeProperty *property_left_value;
    dtkComposerNodeProperty *property_right_value;

public:
    dtkComposerNodeStringButton *button;
    dtkComposerNodeStringEditor *editor;

public:
    QPropertyAnimation *animation;

public:
    bool interactive;

public:
    dtkComposerNodeTransmitter<QString> *emitter;
    dtkComposerNodeTransmitter<QString> *receiver;

public:
    QHash<dtkComposerEdge *, dtkComposerNodeTransmitter<QString> *> receivers;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeString implementation
// /////////////////////////////////////////////////////////////////

//! Constructs string node.
/*! 
 *  String node is interactive by while it has no left edge.
 */
dtkComposerNodeString::dtkComposerNodeString(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeStringPrivate)
{
    d->property_left_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);
    d->property_right_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);

    d->button = new dtkComposerNodeStringButton(this);
    d->button->setPos(0,0);

    this->setTitle("String");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerString");

    this->g->appendLeftProperty(d->property_left_value);
    this->g->appendRightProperty(d->property_right_value);

    // --
    
    d->editor = new dtkComposerNodeStringEditor(this);
    d->editor->setPos(-d->editor->boundingRect().width() / 2, 0);
    d->editor->setTextWidth(0.8 * this->boundingRect().width());
    d->editor->hide();

    // --

    d->animation = new QPropertyAnimation(d->editor, "pos");
    d->animation->setDuration(500);
    d->animation->setStartValue(QPointF(-d->editor->boundingRect().width()/2, 0));
    d->animation->setEndValue(QPointF(-d->editor->boundingRect().width()/2, 0.85 * d->editor->boundingRect().height()));
    d->animation->setEasingCurve(QEasingCurve::OutBounce);

    // --

    d->interactive = true;

    d->emitter = new dtkComposerNodeTransmitter<QString>();
    d->receiver = NULL;
}

//! Destroys string node.
/*! 
 *  
 */
dtkComposerNodeString::~dtkComposerNodeString(void)
{
    delete d;

    d = NULL;
}

const QString dtkComposerNodeString::value(void)
{
    return d->editor->toPlainText();
}

//! Sets the text of the node.
/*! 
 *  
 */
void dtkComposerNodeString::setEditorText(const QString& value)
{
    d->editor->setPlainText(value);
}

//! Expands node to show edition aera.
/*! 
 *  
 */
void dtkComposerNodeString::expand(void)
{
    d->editor->show();
    d->animation->setDirection(QAbstractAnimation::Forward);
    d->animation->start();
}

//! Collapses node to hide edition aera.
/*! 
 *  
 */
void dtkComposerNodeString::collapse(void)
{
    d->animation->setDirection(QAbstractAnimation::Backward);
    d->animation->start();

    connect(d->animation, SIGNAL(finished()), this, SLOT(onCollapseFinised()));
}

//! Updates the graphical aspect of the node.
/*! 
 *  
 */
void dtkComposerNodeString::touch(void)
{
    if(!d->interactive && d->receiver) {
        d->editor->setPlainText(d->receiver->data());
        d->editor->update();
    }

    dtkComposerNode::touch();
}

//! Hides edition aera at the end of collapsing.
/*! 
 *  
 */
void dtkComposerNodeString::onCollapseFinised(void)
{
    d->editor->hide();

    disconnect(d->animation, SIGNAL(finished()), this, SLOT(onCollapseFinised()));    
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeString::pull(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(property);

    d->receiver = d->receivers.value(route);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeString::run(void)
{
    if (d->interactive) {
        d->emitter->setData(this->value());
    } else {
        d->emitter->setData(d->receiver->data());
    }
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeString::push(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
dtkComposerNodeAbstractTransmitter *dtkComposerNodeString::emitter(dtkComposerNodeProperty *property)
{
    if (property == d->property_right_value)
        return d->emitter;
    
    return NULL;
}

//! Sets the receiver from the emitter of the node at the source of \a
//! route.
/*! 
 *  When the source emitter can be casted into current receiver type,
 *  true is returned. Else it returns false.
 *
 *  It makes also the node non-interactive nad clears the text of
 *  edition aera.
 *
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeString::onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination)
{
    Q_UNUSED(destination);

    if (!(dynamic_cast<dtkComposerNodeTransmitter<QString> *>(route->source()->node()->emitter(route->source()))))
        return false;

    d->receivers.insert(route, static_cast<dtkComposerNodeTransmitter<QString> *>(route->source()->node()->emitter(route->source())));

    if (d->receivers.count() == 1)
        d->receiver = d->receivers.values().first();

    d->interactive = false;

    d->editor->setTextInteractionFlags(Qt::NoTextInteraction);
    d->editor->setPlainText("");

    return true;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeString::onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    return true;
}

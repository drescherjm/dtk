/* dtkComposerNodeBoolean.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 25 10:07:34 2011 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. nov. 17 22:51:16 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 283
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeTransmitter.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanLabel declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanLabel : public QGraphicsItem
{
public:
     dtkComposerNodeBooleanLabel(dtkComposerNodeBoolean *parent);
    ~dtkComposerNodeBooleanLabel(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    void setLabelText(bool value);

public:
    dtkComposerNodeBoolean *parent_node;
    QPainterPath path;
    QString text;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanLabel implementation
// /////////////////////////////////////////////////////////////////

//! Constructs boolean label.
/*! 
 *  
 */
dtkComposerNodeBooleanLabel::dtkComposerNodeBooleanLabel(dtkComposerNodeBoolean *parent) : QGraphicsItem(parent)
{
    int margin = 10;
    int length = 30;
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
}

//! Destroys boolean label
/*! 
 *  
 */
dtkComposerNodeBooleanLabel::~dtkComposerNodeBooleanLabel(void)
{

}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
QRectF dtkComposerNodeBooleanLabel::boundingRect(void) const
{
    return path.boundingRect();
}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
void dtkComposerNodeBooleanLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
void dtkComposerNodeBooleanLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if (parent_node->interactive())
        this->setLabelText((text != "T"));
}

//! Sets label text.
/*! 
 *  
 */
void dtkComposerNodeBooleanLabel::setLabelText(bool value)
{
    if (value)
        text = "T";
    else
        text = "F";

    this->update();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanPrivate
{
public:
    dtkComposerNodeProperty *property_left_value;
    dtkComposerNodeProperty *property_right_value;

public:
    dtkComposerNodeBooleanLabel *label;

public:
    bool interactive;

public:
    dtkComposerNodeTransmitter<bool> *emitter;

    dtkComposerNodeTransmitter<bool> *receiver;
    QHash<dtkComposerEdge *, dtkComposerNodeTransmitter<bool> *> receivers;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBoolean
// /////////////////////////////////////////////////////////////////

//! Constructs boolean node.
/*! 
 *  Boolean node is set to false by default and it is interactive.
 */
dtkComposerNodeBoolean::dtkComposerNodeBoolean(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeBooleanPrivate)
{
    d->property_left_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);
    d->property_right_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeBooleanLabel(this);
    d->label->setPos(0, 0);
    d->label->text = "F";

    this->setTitle("Boolean");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerBoolean");

    this->g->appendLeftProperty(d->property_left_value);
    this->g->appendRightProperty(d->property_right_value);

    d->interactive = true;

    d->receiver = NULL;
    d->emitter = new dtkComposerNodeTransmitter<bool>();
}

//! Destroys boolean node.
/*! 
 *  
 */
dtkComposerNodeBoolean::~dtkComposerNodeBoolean(void)
{
    delete d;

    d = NULL;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeBoolean::pull(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(property);

    d->receiver = d->receivers.value(route);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeBoolean::run(void)
{
    if (d->interactive) {
        d->emitter->setData(d->label->text == "T");
    } else {
        d->emitter->setData(d->receiver->data());
        d->label->setLabelText(d->receiver->data());
    }
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeBoolean::push(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
}

//! Returns emitter containing boolean value.
/*! 
 *  Reimplemented from dtkComposerNode.
 */
dtkComposerNodeAbstractTransmitter *dtkComposerNodeBoolean::emitter(dtkComposerNodeProperty *property)
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
 *  It makes also the node non-interactive.
 *
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeBoolean::onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination)
{
    Q_UNUSED(destination);

    if (!(dynamic_cast<dtkComposerNodeTransmitter<bool> *> (route->source()->node()->emitter(route->source()))))
        return false;

    d->receivers.insert(route, static_cast<dtkComposerNodeTransmitter<bool> *> (route->source()->node()->emitter(route->source())));

    d->interactive = false;

    return true;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeBoolean::onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    return true;
}

//! Returns true when node is interactive.
/*! 
 *  
 */
bool dtkComposerNodeBoolean::interactive(void)
{
    return d->interactive;
}

//! Sets the label of the node.
/*! 
 *  
 */
void dtkComposerNodeBoolean::setLabelText(bool value)
{
    d->label->setLabelText(value);
}

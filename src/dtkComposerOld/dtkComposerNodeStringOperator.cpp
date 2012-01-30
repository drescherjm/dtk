/* dtkComposerNodeStringOperator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 18:00:48 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  7 16:21:46 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 94
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeStringOperator.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeTransmitter.h"
#include "dtkComposerRoute.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorLabel declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorLabel : public QGraphicsItem
{
public:
     dtkComposerNodeStringOperatorLabel(dtkComposerNodeStringOperator *parent);
    ~dtkComposerNodeStringOperatorLabel(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeStringOperator *parent_node;
    QPainterPath path;
    QString text;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorLabel implementation
// /////////////////////////////////////////////////////////////////

//! Constructs string operator label.
/*! 
 *  It is set to << by default.
 */
dtkComposerNodeStringOperatorLabel::dtkComposerNodeStringOperatorLabel(dtkComposerNodeStringOperator *parent) : QGraphicsItem(parent)
{
    int margin = 10;
    int length = 50;
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

    text = "<<";
}

//! Destroys string operator label.
/*! 
 *  
 */
dtkComposerNodeStringOperatorLabel::~dtkComposerNodeStringOperatorLabel(void)
{

}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
QRectF dtkComposerNodeStringOperatorLabel::boundingRect(void) const
{
    return path.boundingRect();
}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
void dtkComposerNodeStringOperatorLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

//! Enables to switch between string operations.
/*! 
 *  Reimplemented from QGraphicsItem.
 */
void dtkComposerNodeStringOperatorLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if (text == "<<") {

        text = ">>";
        parent_node->setOperation(dtkComposerNodeStringOperator::Prepend);

    } else if (text == ">>") {

        text = "<<";
        parent_node->setOperation(dtkComposerNodeStringOperator::Append);

    }

    this->update();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorPrivate
{
public:
    dtkComposerNodeProperty *property_left_value_op1;
    dtkComposerNodeProperty *property_left_value_op2;
    dtkComposerNodeProperty *property_right_value;

public:
    dtkComposerNodeStringOperatorLabel *label;

public:
    dtkComposerNodeStringOperator::Operation operation;

public:
    QString value_op1;
    QString value_op2;
    QString value;

public:
    dtkComposerNodeTransmitter<QString> *emitter;

    QHash<dtkComposerRoute *, dtkComposerNodeTransmitter<QString> *> receivers;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperator implementation
// /////////////////////////////////////////////////////////////////

//! Constructs string operator node.
/*! 
 *  << operation is set by default.
 */
dtkComposerNodeStringOperator::dtkComposerNodeStringOperator(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeStringOperatorPrivate)
{
    d->property_left_value_op1 = new dtkComposerNodeProperty("left operand", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);
    d->property_left_value_op2 = new dtkComposerNodeProperty("right operand", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);

    d->property_right_value = new dtkComposerNodeProperty("result", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeStringOperatorLabel(this);
    d->label->setPos(0, 0);

    d->operation = dtkComposerNodeStringOperator::Append;

    this->setTitle("StringOperator");
    this->setKind(dtkComposerNode::Process);
    this->setType("dtkComposerStringOperator");

    this->g->appendLeftProperty(d->property_left_value_op1);
    this->g->appendLeftProperty(d->property_left_value_op2);
    this->g->appendRightProperty(d->property_right_value);

    d->emitter = new dtkComposerNodeTransmitter<QString>();
}

//! Destroys string operator node.
/*! 
 *  
 */
dtkComposerNodeStringOperator::~dtkComposerNodeStringOperator(void)
{
    delete d;

    d = NULL;
}

//! Sets current operator type.
/*! 
 *  Following types are avalaible:
 *
 *  - << operator
 *  - >> operator
 */
void dtkComposerNodeStringOperator::setOperation(dtkComposerNodeStringOperator::Operation operation)
{
    d->operation = operation;

    switch(operation) {
    case dtkComposerNodeStringOperator::Append:
        d->label->text = "<<";
        break;
    case dtkComposerNodeStringOperator::Prepend:
        d->label->text = ">>";
        break;
    default:
        break;
    }
}

//! Returns current operation type.
/*! 
 *  
 */
dtkComposerNodeStringOperator::Operation dtkComposerNodeStringOperator::operation(void)
{
    return d->operation;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeStringOperator::pull(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    if(property == d->property_left_value_op1)
        d->value_op1 = d->receivers.value(route)->data();

    else if(property == d->property_left_value_op2)
        d->value_op2 = d->receivers.value(route)->data();
}

//! Runs node logics.
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeStringOperator::run(void)
{
    switch(d->operation) {
    case dtkComposerNodeStringOperator::Append:
        d->value = d->value_op1.append(d->value_op2);
        break;
    case dtkComposerNodeStringOperator::Prepend:
        d->value = d->value_op1.prepend(d->value_op2);
        break;
    default:
        break;
    }

    d->emitter->setData(d->value);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeStringOperator::push(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
dtkComposerNodeAbstractTransmitter *dtkComposerNodeStringOperator::emitter(dtkComposerNodeProperty *property)
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
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeStringOperator::onLeftRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *destination)
{
    Q_UNUSED(destination);

    if (!(dynamic_cast<dtkComposerNodeTransmitter<QString> *> (route->source()->node()->emitter(route->source()))))
        return false;
    
    d->receivers.insert(route, static_cast<dtkComposerNodeTransmitter<QString> *> (route->source()->node()->emitter(route->source())));
    
    return true;
}

//! 
/*! 
 *  
 */
bool dtkComposerNodeStringOperator::onRightRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    return true;
}

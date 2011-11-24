/* dtkComposerNodeBooleanOperator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 25 10:07:34 2011 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. nov. 17 23:38:17 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 276
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeBooleanOperator.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeTransmitter.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperatorLabel declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorLabel : public QGraphicsItem
{
public:
     dtkComposerNodeBooleanOperatorLabel(dtkComposerNodeBooleanOperator *parent);
    ~dtkComposerNodeBooleanOperatorLabel(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeBooleanOperator *parent_node;
    QPainterPath path;
    QString text;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperatorLabel implementations
// /////////////////////////////////////////////////////////////////

//! Constructs boolean operator label.
/*! 
 *  It is set to AND by default.
 */
dtkComposerNodeBooleanOperatorLabel::dtkComposerNodeBooleanOperatorLabel(dtkComposerNodeBooleanOperator *parent) : QGraphicsItem(parent)
{
    int margin = 10;
    int length = 60;
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

    text = "AND";
}

//! Destroys boolean operator label.
/*! 
 *  
 */
dtkComposerNodeBooleanOperatorLabel::~dtkComposerNodeBooleanOperatorLabel(void)
{

}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
QRectF dtkComposerNodeBooleanOperatorLabel::boundingRect(void) const
{
    return path.boundingRect();
}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
void dtkComposerNodeBooleanOperatorLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

//! Enables to switch between boolean operations.
/*! 
 *  Reimplemented from QGraphicsItem.
 */
void dtkComposerNodeBooleanOperatorLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if (text == "AND") {

        text = "OR";
        parent_node->setOperation(dtkComposerNodeBooleanOperator::Or);

    } else if (text == "OR") {

        text = "XOR";
        parent_node->setOperation(dtkComposerNodeBooleanOperator::Xor);

    } else if (text == "XOR") {

        text = "NAND";
        parent_node->setOperation(dtkComposerNodeBooleanOperator::Nand);

    } else if (text == "NAND") {

        text = "NOR";
        parent_node->setOperation(dtkComposerNodeBooleanOperator::Nor);

    } else if (text == "NOR") {

        text = "XNOR";
        parent_node->setOperation(dtkComposerNodeBooleanOperator::Xnor);

    } else if (text == "XNOR") {

        text = "IMP";
        parent_node->setOperation(dtkComposerNodeBooleanOperator::Imp);

    } else if (text == "IMP") {

        text = "NIMP";
        parent_node->setOperation(dtkComposerNodeBooleanOperator::Nimp);

    } else if (text == "NIMP") {

        text = "AND";
        parent_node->setOperation(dtkComposerNodeBooleanOperator::And);

    }

    this->update();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperatorPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorPrivate
{
public:
    dtkComposerNodeProperty *property_left_value_op1;
    dtkComposerNodeProperty *property_left_value_op2;
    dtkComposerNodeProperty *property_right_value;

public:
    dtkComposerNodeBooleanOperatorLabel *label;

public:
    dtkComposerNodeBooleanOperator::Operation operation;

public:
    bool value_op1;
    bool value_op2;
    bool value;

public:
    dtkComposerNodeTransmitter<bool> *emitter;

    QHash<dtkComposerEdge *, dtkComposerNodeTransmitter<bool> *> receivers;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperator implementation
// /////////////////////////////////////////////////////////////////

//! Constructs boolean operator node.
/*! 
 *  AND operation is set by default.
 */
dtkComposerNodeBooleanOperator::dtkComposerNodeBooleanOperator(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeBooleanOperatorPrivate)
{
    d->property_left_value_op1 = new dtkComposerNodeProperty("left operand", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);
    d->property_left_value_op2 = new dtkComposerNodeProperty("right operand", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);

    d->property_right_value = new dtkComposerNodeProperty("result", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeBooleanOperatorLabel(this);
    d->label->setPos(0, 0);

    d->operation = dtkComposerNodeBooleanOperator::And;

    d->value_op1 = false;
    d->value_op2 = false;
    d->value = false;

    this->setTitle("BooleanOperator");
    this->setKind(dtkComposerNode::Process);
    this->setType("dtkComposerBooleanOperator");

    this->g->appendLeftProperty(d->property_left_value_op1);
    this->g->appendLeftProperty(d->property_left_value_op2);
    this->g->appendRightProperty(d->property_right_value);

    d->emitter = new dtkComposerNodeTransmitter<bool>();
}

//! Destroys boolean operator node.
/*! 
 *  
 */
dtkComposerNodeBooleanOperator::~dtkComposerNodeBooleanOperator(void)
{
    delete d;

    d = NULL;
}

//! Sets current operator type.
/*! 
 *  Following types are avalaible:
 *
 *  -  AND operator
 *  -   OR operator
 *  -  XOR operator (exclusive OR)
 *  - NAND operator (AND negation)
 *  -  NOR operator (OR negation)
 *  - XNOR operator (exclusive OR negation)
 *  -  IMP operator (implication)
 *  - NIMP operator (negation of implication)
 */
void dtkComposerNodeBooleanOperator::setOperation(dtkComposerNodeBooleanOperator::Operation operation)
{
    d->operation = operation;

    switch(operation) {
    case dtkComposerNodeBooleanOperator::And:
        d->label->text = "AND";
        break;
    case dtkComposerNodeBooleanOperator::Or:
        d->label->text = "OR";
        break;
    case dtkComposerNodeBooleanOperator::Xor:
        d->label->text = "XOR";
        break;
    case dtkComposerNodeBooleanOperator::Nand:
        d->label->text = "NAND";
        break;
    case dtkComposerNodeBooleanOperator::Nor:
        d->label->text = "NOR";
        break;
    case dtkComposerNodeBooleanOperator::Xnor:
        d->label->text = "XNOR";
        break;
    case dtkComposerNodeBooleanOperator::Imp:
        d->label->text = "IMP";
        break;
    case dtkComposerNodeBooleanOperator::Nimp:
        d->label->text = "NIMP";
        break;
    default:
        break;
    }
}

//! Returns current operation type.
/*! 
 *  
 */
dtkComposerNodeBooleanOperator::Operation dtkComposerNodeBooleanOperator::operation(void)
{
    return d->operation;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeBooleanOperator::pull(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    if(property == d->property_left_value_op1)
        d->value_op1 = d->receivers.value(route)->data();

    else if(property == d->property_left_value_op2)
        d->value_op2 = d->receivers.value(route)->data();
}

//! Runs node logics.
/*! 
 *  
 */
void dtkComposerNodeBooleanOperator::run(void)
{
    bool a = d->value_op1;
    bool b = d->value_op2;

    switch(d->operation) {
    case dtkComposerNodeBooleanOperator::And:
        d->value = a && b;
        break;
    case dtkComposerNodeBooleanOperator::Or:
        d->value = a || b;
        break;
    case dtkComposerNodeBooleanOperator::Xor:
        d->value = (a && !b) || (!a && b);
        break;
    case dtkComposerNodeBooleanOperator::Nand:
        d->value = !(a && b);
        break;
    case dtkComposerNodeBooleanOperator::Nor:
        d->value = !(a || b);
        break;
    case dtkComposerNodeBooleanOperator::Xnor:
        d->value = ((a && b) || (!a && !b));
        break;
    case dtkComposerNodeBooleanOperator::Imp:
        d->value = (!a || b);
        break;
    case dtkComposerNodeBooleanOperator::Nimp:
        d->value = (a && !b);
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
void dtkComposerNodeBooleanOperator::push(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
dtkComposerNodeAbstractTransmitter *dtkComposerNodeBooleanOperator::emitter(dtkComposerNodeProperty *property)
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
bool dtkComposerNodeBooleanOperator::onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination)
{
    Q_UNUSED(destination);

    if (!(dynamic_cast<dtkComposerNodeTransmitter<bool> *> (route->source()->node()->emitter(route->source()))))
        return false;
    
    d->receivers.insert(route, static_cast<dtkComposerNodeTransmitter<bool> *> (route->source()->node()->emitter(route->source())));

    return true;
}

//! 
/*! 
 *  
 */
bool dtkComposerNodeBooleanOperator::onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    return true;
}

/* dtkComposerNodeBooleanOperator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 25 10:07:34 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:27:36 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 231
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

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperatorLabel
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

dtkComposerNodeBooleanOperatorLabel::~dtkComposerNodeBooleanOperatorLabel(void)
{

}

QRectF dtkComposerNodeBooleanOperatorLabel::boundingRect(void) const
{
    return path.boundingRect();
}

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
// dtkComposerNodeBooleanOperatorPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanOperatorPrivate
{
public:
    dtkComposerNodeProperty *property_input_value_op1;
    dtkComposerNodeProperty *property_input_value_op2;
    dtkComposerNodeProperty *property_output_value;

public:
    dtkComposerNodeBooleanOperatorLabel *label;

public:
    dtkComposerNodeBooleanOperator::Operation operation;

public:
    bool value_op1;
    bool value_op2;
    bool value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanOperator
// /////////////////////////////////////////////////////////////////

dtkComposerNodeBooleanOperator::dtkComposerNodeBooleanOperator(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeBooleanOperatorPrivate)
{
    d->property_input_value_op1 = new dtkComposerNodeProperty("operand 1", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_input_value_op2 = new dtkComposerNodeProperty("operand 2", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_output_value = new dtkComposerNodeProperty("result", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeBooleanOperatorLabel(this);
    d->label->setPos(0, 0);

    d->operation = dtkComposerNodeBooleanOperator::And;

    d->value_op1 = false;
    d->value_op2 = false;
    d->value = false;

    this->setTitle("BooleanOperator");
    this->setKind(dtkComposerNode::Process);
    this->setType("dtkComposerBooleanOperator");

    this->g->appendLeftProperty(d->property_input_value_op1);
    this->g->appendLeftProperty(d->property_input_value_op2);
    this->g->appendRightProperty(d->property_output_value);
}

dtkComposerNodeBooleanOperator::~dtkComposerNodeBooleanOperator(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeBooleanOperator::value(dtkComposerNodeProperty *property)
{
    if(property == d->property_output_value)
        return QVariant(d->value);

	return QVariant();
}

dtkComposerNodeBooleanOperator::Operation dtkComposerNodeBooleanOperator::operation(void)
{
    return d->operation;
}

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

void dtkComposerNodeBooleanOperator::pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if(property == d->property_input_value_op1)
        d->value_op1 = edge->source()->node()->value(edge->source()).toBool();

    if(property == d->property_input_value_op2)
        d->value_op2 = edge->source()->node()->value(edge->source()).toBool();
}

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
}

void dtkComposerNodeBooleanOperator::push(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);
}

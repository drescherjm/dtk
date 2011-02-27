/* dtkComposerNodeStringOperator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 18:00:48 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb 27 19:19:05 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 33
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

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorLabel
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

dtkComposerNodeStringOperatorLabel::dtkComposerNodeStringOperatorLabel(dtkComposerNodeStringOperator *parent) : QGraphicsItem(parent)
{
    QPainterPath b; b.addRoundedRect( 0, 0, 10, 15, 5, 5);
    QPainterPath c; c.addRoundedRect(10, 0, 40, 15, 5, 5);
    QPainterPath d; d.addRoundedRect(50, 0, 10, 15, 5, 5);
    QPainterPath e; e.addRoundedRect( 5, 0, 50,  7, 0, 0);

    path = c.united(e.subtracted(b.united(c.united(d))));
    
    path.translate(path.boundingRect().width()/2 * -1, 0);

    parent_node = parent;

    text = "<<";
}

dtkComposerNodeStringOperatorLabel::~dtkComposerNodeStringOperatorLabel(void)
{

}

QRectF dtkComposerNodeStringOperatorLabel::boundingRect(void) const
{
    return path.boundingRect();
}

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
    painter->drawText(option->rect.left() + option->rect.width()/2 - metrics.width(text)/2, 11, text);
}

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
// dtkComposerNodeStringOperatorPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorPrivate
{
public:
    dtkComposerNodeProperty *property_input_value_op1;
    dtkComposerNodeProperty *property_input_value_op2;
    dtkComposerNodeProperty *property_output_value;

public:
    dtkComposerNodeStringOperatorLabel *label;

public:
    dtkComposerNodeStringOperator::Operation operation;

public:
    QString value_op1;
    QString value_op2;
    QString value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperator
// /////////////////////////////////////////////////////////////////

dtkComposerNodeStringOperator::dtkComposerNodeStringOperator(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeStringOperatorPrivate)
{
    d->property_input_value_op1 = new dtkComposerNodeProperty("operand 1", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_input_value_op2 = new dtkComposerNodeProperty("operand 2", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_output_value = new dtkComposerNodeProperty("result", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeStringOperatorLabel(this);
    d->label->setPos(40, -20);

    d->operation = dtkComposerNodeStringOperator::Append;

    this->setTitle("StringOperator");
    this->setKind(dtkComposerNode::Process);
    this->setType("dtkComposerStringOperator");

    this->addInputProperty(d->property_input_value_op1);
    this->addInputProperty(d->property_input_value_op2);
    this->addOutputProperty(d->property_output_value);
}

dtkComposerNodeStringOperator::~dtkComposerNodeStringOperator(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeStringOperator::value(dtkComposerNodeProperty *property)
{
    if(property == d->property_output_value)
        return QVariant(d->value);
}

dtkComposerNodeStringOperator::Operation dtkComposerNodeStringOperator::operation(void)
{
    return d->operation;
}

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

void dtkComposerNodeStringOperator::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if(property == d->property_input_value_op1)
        d->value_op1 = edge->source()->node()->value(edge->source()).toString();

    if(property == d->property_input_value_op2)
        d->value_op2 = edge->source()->node()->value(edge->source()).toString();
}

void dtkComposerNodeStringOperator::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);
}

void dtkComposerNodeStringOperator::run(void)
{
    QString a = d->value_op1;
    QString b = d->value_op2;
    QString r = a;

    switch(d->operation) {
    case dtkComposerNodeStringOperator::Append:
        d->value = r.append(b);
        break;
    case dtkComposerNodeStringOperator::Prepend:
        d->value = r.prepend(b);
        break;
    default:
        break;
    }
}

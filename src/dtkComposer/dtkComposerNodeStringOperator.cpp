/* dtkComposerNodeStringOperator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 18:00:48 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:35:02 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 36
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
    painter->drawText(this->boundingRect(), Qt::AlignCenter, text);
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
    d->label->setPos(0, 0);

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

	return QVariant();
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

void dtkComposerNodeStringOperator::pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if(property == d->property_input_value_op1)
        d->value_op1 = edge->source()->node()->value(edge->source()).toString();

    if(property == d->property_input_value_op2)
        d->value_op2 = edge->source()->node()->value(edge->source()).toString();
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

void dtkComposerNodeStringOperator::push(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);
}

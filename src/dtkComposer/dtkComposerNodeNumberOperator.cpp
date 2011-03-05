/* dtkComposerNodeNumberOperator.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Mar  1 10:18:08 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Mar  5 22:59:12 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 130
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeNumberOperator.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorLabel
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorLabel : public QGraphicsItem
{
public:
     dtkComposerNodeNumberOperatorLabel(dtkComposerNodeNumberOperator *parent);
    ~dtkComposerNodeNumberOperatorLabel(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeNumberOperator *parent_node;
    QPainterPath path;
    QString text;
};

dtkComposerNodeNumberOperatorLabel::dtkComposerNodeNumberOperatorLabel(dtkComposerNodeNumberOperator *parent) : QGraphicsItem(parent)
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

    text = "+";
}

dtkComposerNodeNumberOperatorLabel::~dtkComposerNodeNumberOperatorLabel(void)
{

}

QRectF dtkComposerNodeNumberOperatorLabel::boundingRect(void) const
{
    return path.boundingRect();
}

void dtkComposerNodeNumberOperatorLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void dtkComposerNodeNumberOperatorLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if (text == "+") {

        text = "-";
        parent_node->setOperation(dtkComposerNodeNumberOperator::Substraction);

    } else if (text == "-") {

        text = "x";
        parent_node->setOperation(dtkComposerNodeNumberOperator::Multiplication);

    } else if (text == "x") {

        text = "/";
        parent_node->setOperation(dtkComposerNodeNumberOperator::Division);

    } else if (text == "/") {

        text = "++";
        parent_node->setOperation(dtkComposerNodeNumberOperator::Increment);

    } else if (text == "++") {

        text = "--";
        parent_node->setOperation(dtkComposerNodeNumberOperator::Decrement);

    } else if (text == "--") {

        text = "%";
        parent_node->setOperation(dtkComposerNodeNumberOperator::Modulo);

    } else if (text == "%") {

        text = "MIN";
        parent_node->setOperation(dtkComposerNodeNumberOperator::Min);

    } else if (text == "MIN") {

        text = "MAX";
        parent_node->setOperation(dtkComposerNodeNumberOperator::Max);

    } else if (text == "MAX") {

        text = "+";
        parent_node->setOperation(dtkComposerNodeNumberOperator::Addition);

    }

    this->update();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorPrivate
{
public:
    dtkComposerNodeProperty *property_input_value_op1;
    dtkComposerNodeProperty *property_input_value_op2;
    dtkComposerNodeProperty *property_output_value;

public:
    dtkComposerNodeNumberOperatorLabel *label;

public:
    dtkComposerNodeNumberOperator::Operation operation;

public:
    QVariant value_op1;
    QVariant value_op2;
    QVariant value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperator
// /////////////////////////////////////////////////////////////////

dtkComposerNodeNumberOperator::dtkComposerNodeNumberOperator(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeNumberOperatorPrivate)
{
    d->property_input_value_op1 = new dtkComposerNodeProperty("operand 1", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_input_value_op2 = new dtkComposerNodeProperty("operand 2", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_output_value = new dtkComposerNodeProperty("result", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeNumberOperatorLabel(this);
    d->label->setPos(0, 0);

    d->operation = dtkComposerNodeNumberOperator::Addition;

    this->setTitle("NumberOperator");
    this->setKind(dtkComposerNode::Process);
    this->setType("dtkComposerNumberOperator");

    this->addInputProperty(d->property_input_value_op1);
    this->addInputProperty(d->property_input_value_op2);
    this->addOutputProperty(d->property_output_value);
}

dtkComposerNodeNumberOperator::~dtkComposerNodeNumberOperator(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeNumberOperator::value(dtkComposerNodeProperty *property)
{
    if(property == d->property_output_value)
        return d->value;

    return QVariant();
}

dtkComposerNodeNumberOperator::Operation dtkComposerNodeNumberOperator::operation(void)
{
    return d->operation;
}

void dtkComposerNodeNumberOperator::setOperation(dtkComposerNodeNumberOperator::Operation operation)
{
    d->operation = operation;

    switch(operation) {
    case dtkComposerNodeNumberOperator::Addition:
        d->label->text = "+";
        break;
    case dtkComposerNodeNumberOperator::Substraction:
        d->label->text = "-";
        break;
    case dtkComposerNodeNumberOperator::Multiplication:
        d->label->text = "x";
        break;
    case dtkComposerNodeNumberOperator::Division:
        d->label->text = "/";
        break;
    case dtkComposerNodeNumberOperator::Increment:
        d->label->text = "++";
        break;
    case dtkComposerNodeNumberOperator::Decrement:
        d->label->text = "--";
        break;
    case dtkComposerNodeNumberOperator::Modulo:
        d->label->text = "%";
        break;
    case dtkComposerNodeNumberOperator::Min:
        d->label->text = "MIN";
        break;
    case dtkComposerNodeNumberOperator::Max:
        d->label->text = "MAX";
        break;
    default:
        break;
    }
}

void dtkComposerNodeNumberOperator::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if(property == d->property_input_value_op1)
        d->value_op1 = edge->source()->node()->value(edge->source());

    if(property == d->property_input_value_op2)
        d->value_op2 = edge->source()->node()->value(edge->source());
}

void dtkComposerNodeNumberOperator::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);
}

void dtkComposerNodeNumberOperator::run(void)
{
    QVariant a = d->value_op1;
    QVariant b = d->value_op2;
    QVariant r;

    dtkComposerNodeNumber::Genre genre = dtkComposerNodeNumber::genre(a, b);

    if (genre != dtkComposerNodeNumber::Invalid) {

        switch (d->operation) {

        case dtkComposerNodeNumberOperator::Addition:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                r = qVariantFromValue(a.toInt() + b.toInt());
                break;
            case dtkComposerNodeNumber::UInt:
                r = qVariantFromValue(a.toUInt() + b.toUInt());
                break;
            case dtkComposerNodeNumber::Long:
                r = qVariantFromValue(a.value<long>() + b.value<long>());
                break;
            case dtkComposerNodeNumber::ULong:
                r = qVariantFromValue(a.value<ulong>() + b.value<ulong>());
                break;
            case dtkComposerNodeNumber::LongLong:
                r = qVariantFromValue(a.toLongLong() + b.toLongLong());
                break;
            case dtkComposerNodeNumber::ULongLong:
                r = qVariantFromValue(a.toULongLong() + b.toULongLong());
                break;
            case dtkComposerNodeNumber::Float:
                r = qVariantFromValue(a.value<float>() + b.value<float>());
                break;
            case dtkComposerNodeNumber::Double:
                r = qVariantFromValue(a.toDouble() + b.toDouble());
                break;
            }
            break;

        case dtkComposerNodeNumberOperator::Substraction:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                r = qVariantFromValue(a.toInt() - b.toInt());
                break;
            case dtkComposerNodeNumber::UInt:
                r = qVariantFromValue(a.toUInt() - b.toUInt());
                break;
            case dtkComposerNodeNumber::Long:
                r = qVariantFromValue(a.value<long>() - b.value<long>());
                break;
            case dtkComposerNodeNumber::ULong:
                r = qVariantFromValue(a.value<ulong>() - b.value<ulong>());
                break;
            case dtkComposerNodeNumber::LongLong:
                r = qVariantFromValue(a.toLongLong() - b.toLongLong());
                break;
            case dtkComposerNodeNumber::ULongLong:
                r = qVariantFromValue(a.toULongLong() - b.toULongLong());
                break;
            case dtkComposerNodeNumber::Float:
                r = qVariantFromValue(a.value<float>() - b.value<float>());
                break;
            case dtkComposerNodeNumber::Double:
                r = qVariantFromValue(a.toDouble() - b.toDouble());
                break;
            }
            break;

        case dtkComposerNodeNumberOperator::Multiplication:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                r = qVariantFromValue(a.toInt() * b.toInt());
                break;
            case dtkComposerNodeNumber::UInt:
                r = qVariantFromValue(a.toUInt() * b.toUInt());
                break;
            case dtkComposerNodeNumber::Long:
                r = qVariantFromValue(a.value<long>() * b.value<long>());
                break;
            case dtkComposerNodeNumber::ULong:
                r = qVariantFromValue(a.value<ulong>() * b.value<ulong>());
                break;
            case dtkComposerNodeNumber::LongLong:
                r = qVariantFromValue(a.toLongLong() * b.toLongLong());
                break;
            case dtkComposerNodeNumber::ULongLong:
                r = qVariantFromValue(a.toULongLong() * b.toULongLong());
                break;
            case dtkComposerNodeNumber::Float:
                r = qVariantFromValue(a.value<float>() * b.value<float>());
                break;
            case dtkComposerNodeNumber::Double:
                r = qVariantFromValue(a.toDouble() * b.toDouble());
                break;
            }
            break;

        case dtkComposerNodeNumberOperator::Division:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                r = qVariantFromValue(a.toInt() / b.toInt());
                break;
            case dtkComposerNodeNumber::UInt:
                r = qVariantFromValue(a.toUInt() / b.toUInt());
                break;
            case dtkComposerNodeNumber::Long:
                r = qVariantFromValue(a.value<long>() / b.value<long>());
                break;
            case dtkComposerNodeNumber::ULong:
                r = qVariantFromValue(a.value<ulong>() / b.value<ulong>());
                break;
            case dtkComposerNodeNumber::LongLong:
                r = qVariantFromValue(a.toLongLong() / b.toLongLong());
                break;
            case dtkComposerNodeNumber::ULongLong:
                r = qVariantFromValue(a.toULongLong() / b.toULongLong());
                break;
            case dtkComposerNodeNumber::Float:
                r = qVariantFromValue(a.value<float>() / b.value<float>());
                break;
            case dtkComposerNodeNumber::Double:
                r = qVariantFromValue(a.toDouble() / b.toDouble());
                break;
            }
            break;
        case dtkComposerNodeNumberOperator::Increment:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                r = qVariantFromValue(a.toInt() + 1);
                break;
            case dtkComposerNodeNumber::UInt:
                r = qVariantFromValue(a.toUInt() + 1);
                break;
            case dtkComposerNodeNumber::Long:
                r = qVariantFromValue(a.value<long>() + 1);
                break;
            case dtkComposerNodeNumber::ULong:
                r = qVariantFromValue(a.value<ulong>() + 1);
                break;
            case dtkComposerNodeNumber::LongLong:
                r = qVariantFromValue(a.toLongLong() + 1);
                break;
            case dtkComposerNodeNumber::ULongLong:
                r = qVariantFromValue(a.toULongLong() + 1);
                break;
            case dtkComposerNodeNumber::Float:
                r = qVariantFromValue(a.value<float>() + 1);
                break;
            case dtkComposerNodeNumber::Double:
                r = qVariantFromValue(a.toDouble() + 1);
                break;
            }
            break;
        case dtkComposerNodeNumberOperator::Decrement:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                r = qVariantFromValue(a.toInt() - 1);
                break;
            case dtkComposerNodeNumber::UInt:
                r = qVariantFromValue(a.toUInt() - 1);
                break;
            case dtkComposerNodeNumber::Long:
                r = qVariantFromValue(a.value<long>() - 1);
                break;
            case dtkComposerNodeNumber::ULong:
                r = qVariantFromValue(a.value<ulong>() - 1);
                break;
            case dtkComposerNodeNumber::LongLong:
                r = qVariantFromValue(a.toLongLong() - 1);
                break;
            case dtkComposerNodeNumber::ULongLong:
                r = qVariantFromValue(a.toULongLong() - 1);
                break;
            case dtkComposerNodeNumber::Float:
                r = qVariantFromValue(a.value<float>() - 1);
                break;
            case dtkComposerNodeNumber::Double:
                r = qVariantFromValue(a.toDouble() - 1);
                break;
            }
            break;

        case dtkComposerNodeNumberOperator::Modulo:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                r = qVariantFromValue(a.toInt() % b.toInt());
                break;
            case dtkComposerNodeNumber::UInt:
                r = qVariantFromValue(a.toUInt() % b.toUInt());
                break;
            case dtkComposerNodeNumber::Long:
                r = qVariantFromValue(a.value<long>() % b.value<long>());
                break;
            case dtkComposerNodeNumber::ULong:
                r = qVariantFromValue(a.value<ulong>() % b.value<ulong>());
                break;
            case dtkComposerNodeNumber::LongLong:
                r = qVariantFromValue(a.toLongLong() % b.toLongLong());
                break;
            case dtkComposerNodeNumber::ULongLong:
                r = qVariantFromValue(a.toULongLong() % b.toULongLong());
                break;
            case dtkComposerNodeNumber::Float:
                r = qVariantFromValue(a.value<long>() % b.value<long>());
                break;
            case dtkComposerNodeNumber::Double:
                r = qVariantFromValue(a.toLongLong() % b.toLongLong());
                break;
            }
            break;

        case dtkComposerNodeNumberOperator::Min:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                r = qVariantFromValue((a.toInt() < b.toInt() ? a.toInt() : b.toInt()));
                break;
            case dtkComposerNodeNumber::UInt:
                r = qVariantFromValue((a.toUInt() < b.toUInt() ? a.toUInt() : b.toUInt()));
                break;
            case dtkComposerNodeNumber::Long:
                r = qVariantFromValue((a.value<long>() < b.value<long>() ? a.value<long>() : b.value<long>()));
                break;
            case dtkComposerNodeNumber::ULong:
                r = qVariantFromValue((a.value<ulong>() < b.value<ulong>() ? a.value<ulong>() : b.value<ulong>()));
                break;
            case dtkComposerNodeNumber::LongLong:
                r = qVariantFromValue((a.toLongLong() < b.toLongLong() ? a.toLongLong() : b.toLongLong()));
                break;
            case dtkComposerNodeNumber::ULongLong:
                r = qVariantFromValue((a.toULongLong() < b.toULongLong() ? a.toULongLong() : b.toULongLong()));
                break;
            case dtkComposerNodeNumber::Float:
                r = qVariantFromValue((a.value<float>() < b.value<float>() ? a.value<float>() : b.value<float>()));
                break;
            case dtkComposerNodeNumber::Double:
                r = qVariantFromValue((a.toDouble() < b.toDouble() ? a.toDouble() : b.toDouble()));
                break;
            }
            break;

        case dtkComposerNodeNumberOperator::Max:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                r = qVariantFromValue((a.toInt() > b.toInt() ? a.toInt() : b.toInt()));
                break;
            case dtkComposerNodeNumber::UInt:
                r = qVariantFromValue((a.toUInt() > b.toUInt() ? a.toUInt() : b.toUInt()));
                break;
            case dtkComposerNodeNumber::Long:
                r = qVariantFromValue((a.value<long>() > b.value<long>() ? a.value<long>() : b.value<long>()));
                break;
            case dtkComposerNodeNumber::ULong:
                r = qVariantFromValue((a.value<ulong>() > b.value<ulong>() ? a.value<ulong>() : b.value<ulong>()));
                break;
            case dtkComposerNodeNumber::LongLong:
                r = qVariantFromValue((a.toLongLong() > b.toLongLong() ? a.toLongLong() : b.toLongLong()));
                break;
            case dtkComposerNodeNumber::ULongLong:
                r = qVariantFromValue((a.toULongLong() > b.toULongLong() ? a.toULongLong() : b.toULongLong()));
                break;
            case dtkComposerNodeNumber::Float:
                r = qVariantFromValue((a.value<float>() > b.value<float>() ? a.value<float>() : b.value<float>()));
                break;
            case dtkComposerNodeNumber::Double:
                r = qVariantFromValue((a.toDouble() > b.toDouble() ? a.toDouble() : b.toDouble()));
                break;
            }
            break;

        default:
            break;
        }
    }

    d->value = r;
}

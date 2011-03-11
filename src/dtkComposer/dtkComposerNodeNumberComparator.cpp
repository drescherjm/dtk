/* dtkComposerNodeNumberComparator.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Mar  7 09:24:11 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar  9 16:37:50 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 42
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */


#include "dtkComposerEdge.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeNumberComparator.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkMath/dtkMath.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparatorLabel
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberComparatorLabel : public QGraphicsItem
{
public:
     dtkComposerNodeNumberComparatorLabel(dtkComposerNodeNumberComparator *parent);
    ~dtkComposerNodeNumberComparatorLabel(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeNumberComparator *parent_node;
    QPainterPath path;
    QString text;
};

dtkComposerNodeNumberComparatorLabel::dtkComposerNodeNumberComparatorLabel(dtkComposerNodeNumberComparator *parent) : QGraphicsItem(parent)
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

    text = "<";
}

dtkComposerNodeNumberComparatorLabel::~dtkComposerNodeNumberComparatorLabel(void)
{

}

QRectF dtkComposerNodeNumberComparatorLabel::boundingRect(void) const
{
    return path.boundingRect();
}

void dtkComposerNodeNumberComparatorLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void dtkComposerNodeNumberComparatorLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if (text == "<") {

        text = "<=";
        parent_node->setOperation(dtkComposerNodeNumberComparator::LesserThanOrEqual);

    } else if (text == "<=") {

        text = ">";
        parent_node->setOperation(dtkComposerNodeNumberComparator::GreaterThan);

    } else if (text == ">") {

        text = ">=";
        parent_node->setOperation(dtkComposerNodeNumberComparator::GreaterThanOrEqual);

    } else if (text == ">=") {

        text = "==";
        parent_node->setOperation(dtkComposerNodeNumberComparator::Equal);

    } else if (text == "==") {

        text = "!=";
        parent_node->setOperation(dtkComposerNodeNumberComparator::Differ);

    } else if (text == "!=") {

        text = "<";
        parent_node->setOperation(dtkComposerNodeNumberComparator::LesserThan);

    }

    this->update();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparatorPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberComparatorPrivate
{
public:
    dtkComposerNodeProperty *property_input_value_op1;
    dtkComposerNodeProperty *property_input_value_op2;
    dtkComposerNodeProperty *property_output_value;

public:
    dtkComposerNodeNumberComparatorLabel *label;

public:
    dtkComposerNodeNumberComparator::Operation operation;

public:
    QVariant value_op1;
    QVariant value_op2;
    bool value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator
// /////////////////////////////////////////////////////////////////

dtkComposerNodeNumberComparator::dtkComposerNodeNumberComparator(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeNumberComparatorPrivate)
{
    d->property_input_value_op1 = new dtkComposerNodeProperty("operand 1", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_input_value_op2 = new dtkComposerNodeProperty("operand 2", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_output_value = new dtkComposerNodeProperty("result", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeNumberComparatorLabel(this);
    d->label->setPos(0, 0);

    d->operation = dtkComposerNodeNumberComparator::LesserThan;

    d->value = false;

    this->setTitle("NumberComparator");
    this->setKind(dtkComposerNode::Process);
    this->setType("dtkComposerNumberComparator");

    this->addInputProperty(d->property_input_value_op1);
    this->addInputProperty(d->property_input_value_op2);
    this->addOutputProperty(d->property_output_value);
}

dtkComposerNodeNumberComparator::~dtkComposerNodeNumberComparator(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeNumberComparator::value(dtkComposerNodeProperty *property)
{
    if(property == d->property_output_value)
        return d->value;

    return QVariant();
}

dtkComposerNodeNumberComparator::Operation dtkComposerNodeNumberComparator::operation(void)
{
    return d->operation;
}

void dtkComposerNodeNumberComparator::setOperation(dtkComposerNodeNumberComparator::Operation operation)
{
    d->operation = operation;

    switch(operation) {
    case dtkComposerNodeNumberComparator::LesserThan:
        d->label->text = "<";
        break;
    case dtkComposerNodeNumberComparator::LesserThanOrEqual:
        d->label->text = "<=";
        break;
    case dtkComposerNodeNumberComparator::GreaterThan:
        d->label->text = ">";
        break;
    case dtkComposerNodeNumberComparator::GreaterThanOrEqual:
        d->label->text = ">=";
        break;
    case dtkComposerNodeNumberComparator::Equal:
        d->label->text = "==";
        break;
    case dtkComposerNodeNumberComparator::Differ:
        d->label->text = "!=";
        break;
    default:
        break;
    }
}

void dtkComposerNodeNumberComparator::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if(property == d->property_input_value_op1)
        d->value_op1 = edge->source()->node()->value(edge->source());

    if(property == d->property_input_value_op2)
        d->value_op2 = edge->source()->node()->value(edge->source());
}

void dtkComposerNodeNumberComparator::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);
}

void dtkComposerNodeNumberComparator::run(void)
{
    QVariant a = d->value_op1;
    QVariant b = d->value_op2;

    dtkComposerNodeNumber::Genre genre = dtkComposerNodeNumber::genre(a, b);

    if (genre != dtkComposerNodeNumber::Invalid) {

        switch (d->operation) {

        case dtkComposerNodeNumberComparator::LesserThan:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                d->value = a.toInt() < b.toInt();
                break;
            case dtkComposerNodeNumber::UInt:
                d->value = a.toUInt() < b.toUInt();
                break;
            case dtkComposerNodeNumber::Long:
            case dtkComposerNodeNumber::LongLong:
                d->value = a.toLongLong() < b.toLongLong();
                break;
            case dtkComposerNodeNumber::ULong:
            case dtkComposerNodeNumber::ULongLong:
                d->value = a.toULongLong() < b.toULongLong();
                break;
            case dtkComposerNodeNumber::Float:
                d->value = dtkLesserThanUlps(a.value<float>(), b.value<float>(), 10);
                break;
            case dtkComposerNodeNumber::Double:
                d->value = dtkLesserThanUlps(a.toDouble(), b.toDouble(), (long long int)10);
                break;
            }
            break;

        case dtkComposerNodeNumberComparator::LesserThanOrEqual:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                d->value = a.toInt() <= b.toInt();
                break;
            case dtkComposerNodeNumber::UInt:
                d->value = a.toUInt() <= b.toUInt();
                break;
            case dtkComposerNodeNumber::Long:
            case dtkComposerNodeNumber::LongLong:
                d->value = a.toLongLong() <= b.toLongLong();
                break;
            case dtkComposerNodeNumber::ULong:
            case dtkComposerNodeNumber::ULongLong:
                d->value = a.toULongLong() <= b.toULongLong();
                break;
            case dtkComposerNodeNumber::Float:
                d->value = dtkLesserThanOrAlmostEqualUlps(a.value<float>(), b.value<float>(), 10);
                break;
            case dtkComposerNodeNumber::Double:
                d->value = dtkLesserThanOrAlmostEqualUlps(a.toDouble(), b.toDouble(), (long long int)10);
                break;
            }
            break;

        case dtkComposerNodeNumberComparator::GreaterThan:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                d->value = a.toInt() > b.toInt();
                break;
            case dtkComposerNodeNumber::UInt:
                d->value = a.toUInt() > b.toUInt();
                break;
            case dtkComposerNodeNumber::Long:
            case dtkComposerNodeNumber::LongLong:
                d->value = a.toLongLong() > b.toLongLong();
                break;
            case dtkComposerNodeNumber::ULong:
            case dtkComposerNodeNumber::ULongLong:
                d->value = a.toULongLong() > b.toULongLong();
                break;
            case dtkComposerNodeNumber::Float:
                d->value = dtkGreaterThanUlps(a.value<float>(), b.value<float>(), 10);
                break;
            case dtkComposerNodeNumber::Double:
                d->value = dtkGreaterThanUlps(a.toDouble(), b.toDouble(), (long long int)10);
                break;
            }
            break;

        case dtkComposerNodeNumberComparator::GreaterThanOrEqual:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                d->value = a.toInt() >= b.toInt();
                break;
            case dtkComposerNodeNumber::UInt:
                d->value = a.toUInt() >= b.toUInt();
                break;
            case dtkComposerNodeNumber::Long:
            case dtkComposerNodeNumber::LongLong:
                d->value = a.toLongLong() >= b.toLongLong();
                break;
            case dtkComposerNodeNumber::ULong:
            case dtkComposerNodeNumber::ULongLong:
                d->value = a.toULongLong() >= b.toULongLong();
                break;
            case dtkComposerNodeNumber::Float:
                d->value = dtkGreaterThanOrAlmostEqualUlps(a.value<float>(), b.value<float>(), 10);
                break;
            case dtkComposerNodeNumber::Double:
                d->value = dtkGreaterThanOrAlmostEqualUlps(a.toDouble(), b.toDouble(), (long long int)10);
                break;
            }
            break;

        case dtkComposerNodeNumberComparator::Equal:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                d->value = a.toInt() == b.toInt();
                break;
            case dtkComposerNodeNumber::UInt:
                d->value = a.toUInt() == b.toUInt();
                break;
            case dtkComposerNodeNumber::Long:
            case dtkComposerNodeNumber::LongLong:
                d->value = a.toLongLong() == b.toLongLong();
                break;
            case dtkComposerNodeNumber::ULong:
            case dtkComposerNodeNumber::ULongLong:
                d->value = a.toULongLong() == b.toULongLong();
                break;
            case dtkComposerNodeNumber::Float:
                d->value = dtkAlmostEqualUlps(a.value<float>(), b.value<float>(), 10);
                break;
            case dtkComposerNodeNumber::Double:
                d->value = dtkAlmostEqualUlps(a.toDouble(), b.toDouble(), (long long int)10);
                break;
            }
            break;

        case dtkComposerNodeNumberComparator::Differ:
            switch (genre) {
            case dtkComposerNodeNumber::Int:
                d->value = a.toInt() != b.toInt();
                break;
            case dtkComposerNodeNumber::UInt:
                d->value = a.toUInt() != b.toUInt();
                break;
            case dtkComposerNodeNumber::Long:
            case dtkComposerNodeNumber::LongLong:
                d->value = a.toLongLong() != b.toLongLong();
                break;
            case dtkComposerNodeNumber::ULong:
            case dtkComposerNodeNumber::ULongLong:
                d->value = a.toULongLong() != b.toULongLong();
                break;
            case dtkComposerNodeNumber::Float:
                d->value = !(dtkAlmostEqualUlps(a.value<float>(), b.value<float>(), 10));
                break;
            case dtkComposerNodeNumber::Double:
                d->value = !(dtkAlmostEqualUlps(a.toDouble(), b.toDouble(), (long long int)10));
                break;
            }
            break;

        default:
            break;
        }
    }
}

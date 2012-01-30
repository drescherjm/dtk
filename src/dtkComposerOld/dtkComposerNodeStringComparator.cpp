/* dtkComposerNodeStringComparator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 18:00:48 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  7 16:20:18 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 49
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeStringComparator.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeTransmitter.h"
#include "dtkComposerRoute.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringComparatorLabel
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringComparatorLabel : public QGraphicsItem
{
public:
     dtkComposerNodeStringComparatorLabel(dtkComposerNodeStringComparator *parent);
    ~dtkComposerNodeStringComparatorLabel(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeStringComparator *parent_node;
    QPainterPath path;
    QString text;
};

dtkComposerNodeStringComparatorLabel::dtkComposerNodeStringComparatorLabel(dtkComposerNodeStringComparator *parent) : QGraphicsItem(parent)
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

    text = "==";
}

dtkComposerNodeStringComparatorLabel::~dtkComposerNodeStringComparatorLabel(void)
{

}

QRectF dtkComposerNodeStringComparatorLabel::boundingRect(void) const
{
    return path.boundingRect();
}

void dtkComposerNodeStringComparatorLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void dtkComposerNodeStringComparatorLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if (text == "==") {

        text = "!=";
        parent_node->setOperation(dtkComposerNodeStringComparator::Differ);

    } else if (text == "!=") {

        text = "<";
        parent_node->setOperation(dtkComposerNodeStringComparator::LesserThan);

    } else if (text == "<") {

        text = "<=";
        parent_node->setOperation(dtkComposerNodeStringComparator::LesserThanOrEqual);

    } else if (text == "<=") {

        text = ">";
        parent_node->setOperation(dtkComposerNodeStringComparator::GreaterThan);

    } else if (text == ">") {

        text = ">=";
        parent_node->setOperation(dtkComposerNodeStringComparator::GreaterThanOrEqual);

    } else if (text == ">=") {

        text = "==";
        parent_node->setOperation(dtkComposerNodeStringComparator::Equal);

    }

    this->update();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringComparatorPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringComparatorPrivate
{
public:
    dtkComposerNodeProperty *property_input_value_op1;
    dtkComposerNodeProperty *property_input_value_op2;
    dtkComposerNodeProperty *property_output_value;

    dtkComposerNodeTransmitter<bool> *emitter;

public:
    QHash<dtkComposerRoute *, dtkComposerNodeTransmitter<QString> *> receivers;

public:
    dtkComposerNodeStringComparatorLabel *label;

public:
    dtkComposerNodeStringComparator::Operation operation;

public:
    QString value_op1;
    QString value_op2;
    bool value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringComparator
// /////////////////////////////////////////////////////////////////

dtkComposerNodeStringComparator::dtkComposerNodeStringComparator(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeStringComparatorPrivate)
{
    d->property_input_value_op1 = new dtkComposerNodeProperty("left operand", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);
    d->property_input_value_op2 = new dtkComposerNodeProperty("right operand", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);

    d->property_output_value = new dtkComposerNodeProperty("result", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeStringComparatorLabel(this);
    d->label->setPos(0, 0);

    d->operation = dtkComposerNodeStringComparator::Equal;

    d->value = false;

    this->setTitle("StringComparator");
    this->setKind(dtkComposerNode::Process);
    this->setType("dtkComposerStringComparator");

    this->g->appendLeftProperty(d->property_input_value_op1);
    this->g->appendLeftProperty(d->property_input_value_op2);
    this->g->appendRightProperty(d->property_output_value);

    d->emitter = new dtkComposerNodeTransmitter<bool>();
}

dtkComposerNodeStringComparator::~dtkComposerNodeStringComparator(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeStringComparator::value(dtkComposerNodeProperty *property)
{
    if(property == d->property_output_value)
        return QVariant(d->value);

	return QVariant();
}

dtkComposerNodeStringComparator::Operation dtkComposerNodeStringComparator::operation(void)
{
    return d->operation;
}

void dtkComposerNodeStringComparator::setOperation(dtkComposerNodeStringComparator::Operation operation)
{
    d->operation = operation;

    switch(operation) {
    case dtkComposerNodeStringComparator::LesserThan:
        d->label->text = "<";
        break;
    case dtkComposerNodeStringComparator::LesserThanOrEqual:
        d->label->text = "<=";
        break;
    case dtkComposerNodeStringComparator::GreaterThan:
        d->label->text = ">";
        break;
    case dtkComposerNodeStringComparator::GreaterThanOrEqual:
        d->label->text = ">=";
        break;
    case dtkComposerNodeStringComparator::Equal:
        d->label->text = "==";
        break;
    case dtkComposerNodeStringComparator::Differ:
        d->label->text = "!=";
        break;
    default:
        break;
    }
}

void dtkComposerNodeStringComparator::pull(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    if(property == d->property_input_value_op1)
        d->value_op1 = d->receivers.value(route)->data();

    else if(property == d->property_input_value_op2)
        d->value_op2 = d->receivers.value(route)->data();
}

void dtkComposerNodeStringComparator::run(void)
{
    QString a = d->value_op1;
    QString b = d->value_op2;

    switch(d->operation) {
    case dtkComposerNodeStringComparator::LesserThan:
        d->value = a < b;
        break;
    case dtkComposerNodeStringComparator::LesserThanOrEqual:
        d->value = a <= b;
        break;
    case dtkComposerNodeStringComparator::GreaterThan:
        d->value = a > b;
        break;
    case dtkComposerNodeStringComparator::GreaterThanOrEqual:
        d->value = a >= b;
        break;
    case dtkComposerNodeStringComparator::Equal:
        d->value = a == b;
        break;
    case dtkComposerNodeStringComparator::Differ:
        d->value = a != b;
        break;
    default:
        break;
    }

    d->emitter->setData(d->value);
}

void dtkComposerNodeStringComparator::push(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
}

dtkComposerNodeAbstractTransmitter *dtkComposerNodeStringComparator::emitter(dtkComposerNodeProperty *property)
{
    if (property == d->property_output_value)
        return d->emitter;
    
    return NULL;
}

bool dtkComposerNodeStringComparator::onLeftRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *destination)
{
    Q_UNUSED(destination);

    if (!(dynamic_cast<dtkComposerNodeTransmitter<QString> *> (route->source()->node()->emitter(route->source()))))
        return false;
    
    d->receivers.insert(route, static_cast<dtkComposerNodeTransmitter<QString> *> (route->source()->node()->emitter(route->source())));
    
    return true;
}

bool dtkComposerNodeStringComparator::onRightRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    return true;
}

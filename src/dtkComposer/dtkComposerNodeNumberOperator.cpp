/* dtkComposerNodeNumberOperator.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Mar  1 10:18:08 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  7 16:19:14 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 352
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
#include "dtkComposerNodeTransmitter.h"
#include "dtkComposerRoute.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorLabel declaration
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

public:
    QPainterPath path;
    QString text;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorLabel implementation
// /////////////////////////////////////////////////////////////////

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
// dtkComposerNodeNumberOperatorPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberOperatorPrivate
{
public:
    double    operate(const double&, const double&, dtkComposerNodeNumberOperator::Operation);
    qlonglong operate(const qlonglong&, const qlonglong&, dtkComposerNodeNumberOperator::Operation);
    int       operate(const int&, const int&, dtkComposerNodeNumberOperator::Operation);

public:
    void setValueType(void);

public:
    dtkComposerNodeProperty *property_left_value_op1;
    dtkComposerNodeProperty *property_left_value_op2;
    dtkComposerNodeProperty *property_right_value;

public:
    dtkComposerNodeNumberOperatorLabel *label;

public:
    dtkComposerNodeNumberOperator::Operation operation;

public:
    QVariant::Type value_type;

public:    
    int op1_value_i; qlonglong op1_value_l; double op1_value_d;
    int op2_value_i; qlonglong op2_value_l; double op2_value_d;

    QVariant::Type op1_type;
    QVariant::Type op2_type;

public:
    dtkComposerNodeTransmitter<int>       *emitter_i;
    dtkComposerNodeTransmitter<qlonglong> *emitter_l;
    dtkComposerNodeTransmitter<double>    *emitter_d;

    QHash<dtkComposerRoute *, dtkComposerNodeTransmitter<int> *> receivers_i;
    QHash<dtkComposerRoute *, dtkComposerNodeTransmitter<qlonglong> *> receivers_l;
    QHash<dtkComposerRoute *, dtkComposerNodeTransmitter<double> *> receivers_d;

public:
    dtkComposerNodeNumberOperator *q;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperatorPrivate implementation
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeNumberOperatorPrivate::setValueType(void)
{
    if (this->op1_type == QVariant::Invalid || this->op2_type == QVariant::Invalid)
        return;

    if (this->op1_type == QVariant::Double || this->op2_type == QVariant::Double) {
        this->value_type = QVariant::Double;
        this->emitter_d = new dtkComposerNodeTransmitter<double>();
    }
    else if (this->op1_type == QVariant::LongLong || this->op2_type == QVariant::LongLong) {
        this->value_type = QVariant::LongLong;
        this->emitter_l = new dtkComposerNodeTransmitter<qlonglong>();
    }
    else {
        this->value_type = QVariant::Int;
        this->emitter_i = new dtkComposerNodeTransmitter<int>();
    }

    foreach(dtkComposerEdge *edge, q->g->rightEdges())
        edge->destination()->node()->g->onEdgeConnected(edge);
}

double dtkComposerNodeNumberOperatorPrivate::operate(const double& lhs, const double& rhs, dtkComposerNodeNumberOperator::Operation operation)
{
    switch(operation) {
    case dtkComposerNodeNumberOperator::Addition:
        return lhs + rhs;
    case dtkComposerNodeNumberOperator::Substraction:
        return lhs - rhs;
    case dtkComposerNodeNumberOperator::Multiplication:
        return lhs * rhs;
    case dtkComposerNodeNumberOperator::Division:
        return lhs / rhs;
    case dtkComposerNodeNumberOperator::Increment:
        return lhs + 1;
    case dtkComposerNodeNumberOperator::Decrement:
        return lhs - 1;
    case dtkComposerNodeNumberOperator::Modulo:
        return qlonglong(lhs) % qlonglong(rhs);
    case dtkComposerNodeNumberOperator::Min:
        return qMin(lhs, rhs);
    case dtkComposerNodeNumberOperator::Max:
        return qMax(lhs, rhs);
    default:
        return 0;
    }
}

qlonglong dtkComposerNodeNumberOperatorPrivate::operate(const qlonglong& lhs, const qlonglong& rhs, dtkComposerNodeNumberOperator::Operation operation)
{
    switch(operation) {
    case dtkComposerNodeNumberOperator::Addition:
        return lhs + rhs;
    case dtkComposerNodeNumberOperator::Substraction:
        return lhs - rhs;
    case dtkComposerNodeNumberOperator::Multiplication:
        return lhs * rhs;
    case dtkComposerNodeNumberOperator::Division:
        return lhs / rhs;
    case dtkComposerNodeNumberOperator::Increment:
        return lhs + 1;
    case dtkComposerNodeNumberOperator::Decrement:
        return lhs - 1;
    case dtkComposerNodeNumberOperator::Modulo:
        return lhs % rhs;
    case dtkComposerNodeNumberOperator::Min:
        return qMin(lhs, rhs);
    case dtkComposerNodeNumberOperator::Max:
        return qMax(lhs, rhs);
    default:
        return 0;
    }
}

int dtkComposerNodeNumberOperatorPrivate::operate(const int& lhs, const int& rhs, dtkComposerNodeNumberOperator::Operation operation)
{
    switch(operation) {
    case dtkComposerNodeNumberOperator::Addition:
        return lhs + rhs;
    case dtkComposerNodeNumberOperator::Substraction:
        return lhs - rhs;
    case dtkComposerNodeNumberOperator::Multiplication:
        return lhs * rhs;
    case dtkComposerNodeNumberOperator::Division:
        return lhs / rhs;
    case dtkComposerNodeNumberOperator::Increment:
        return lhs + 1;
    case dtkComposerNodeNumberOperator::Decrement:
        return lhs - 1;
    case dtkComposerNodeNumberOperator::Modulo:
        return lhs % rhs;
    case dtkComposerNodeNumberOperator::Min:
        return qMin(lhs, rhs);
    case dtkComposerNodeNumberOperator::Max:
        return qMax(lhs, rhs);
    default:
        return 0;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberOperator implementation
// /////////////////////////////////////////////////////////////////

//! Constructs number operator node.
/*! 
 *  operation + is set by default.
 */
dtkComposerNodeNumberOperator::dtkComposerNodeNumberOperator(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeNumberOperatorPrivate)
{
    d->q = this;

    d->property_left_value_op1 = new dtkComposerNodeProperty("left operand", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);
    d->property_left_value_op2 = new dtkComposerNodeProperty("right operand", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);

    d->property_right_value = new dtkComposerNodeProperty("result", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeNumberOperatorLabel(this);
    d->label->setPos(0, 0);

    d->operation = dtkComposerNodeNumberOperator::Addition;

    this->setTitle("NumberOperator");
    this->setKind(dtkComposerNode::Process);
    this->setType("dtkComposerNumberOperator");

    this->g->appendLeftProperty(d->property_left_value_op1);
    this->g->appendLeftProperty(d->property_left_value_op2);
    this->g->appendRightProperty(d->property_right_value);

    d->op1_type = QVariant::Invalid;
    d->op2_type = QVariant::Invalid;

    d->emitter_i = NULL;
    d->emitter_l = NULL;
    d->emitter_d = NULL;
}

//! Destroys number operator node.
/*! 
 *  
 */
dtkComposerNodeNumberOperator::~dtkComposerNodeNumberOperator(void)
{
    delete d;

    d = NULL;
}

//! Sets current operator type.
/*! 
 *  Following types are avalaible:
 *
 *  -   + operator
 *  -   - operator
 *  -   x operator
 *  -   / operator
 *  -  ++ operator
 *  -  -- operator
 *  -   % operator
 *  - MIN operator
 *  - MAX operator
 */
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

//! Returns current operation type.
/*! 
 *  
 */
dtkComposerNodeNumberOperator::Operation dtkComposerNodeNumberOperator::operation(void)
{
    return d->operation;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberOperator::pull(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    if(property == d->property_left_value_op1) {

        switch(d->op1_type) {
            
        case QVariant::Int:
            d->op1_value_i = d->receivers_i.value(route)->data();
            break;
        case QVariant::LongLong:
            d->op1_value_l = d->receivers_l.value(route)->data();
            break;
        case QVariant::Double:
            d->op1_value_d = d->receivers_d.value(route)->data();
            break;
        }

    } else if (property == d->property_left_value_op2) {

        switch(d->op2_type) {
            
        case QVariant::Int:
            d->op2_value_i = d->receivers_i.value(route)->data();
            break;
        case QVariant::LongLong:
            d->op2_value_l = d->receivers_l.value(route)->data();
            break;
        case QVariant::Double:
            d->op2_value_d = d->receivers_d.value(route)->data();
            break;
        }
    }
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberOperator::run(void)
{
    if (d->op1_type == QVariant::Double) {

        if (d->op2_type == QVariant::Double)
            d->emitter_d->setData(d->operate(d->op1_value_d, d->op2_value_d, d->operation));

        else if (d->op2_type == QVariant::LongLong)
            d->emitter_d->setData(d->operate(d->op1_value_d, (double)d->op2_value_l, d->operation));

        else if (d->op2_type == QVariant::Int)
            d->emitter_d->setData(d->operate(d->op1_value_d, (double)d->op2_value_i, d->operation));

    } else if (d->op1_type == QVariant::LongLong) {

        if (d->op2_type == QVariant::Double)
            d->emitter_d->setData(d->operate((double)d->op1_value_l, d->op2_value_d, d->operation));

        else if (d->op2_type == QVariant::LongLong)
            d->emitter_l->setData(d->operate(d->op1_value_l, d->op2_value_l, d->operation));

        else if (d->op2_type == QVariant::Int)
            d->emitter_l->setData(d->operate(d->op1_value_l, (qlonglong)d->op2_value_i, d->operation));
    
    } else if (d->op1_type == QVariant::Int) {

        if (d->op2_type == QVariant::Double)
            d->emitter_d->setData(d->operate((double)d->op1_value_i, d->op2_value_d, d->operation));

        else if (d->op2_type == QVariant::LongLong)
            d->emitter_l->setData(d->operate((qlonglong)d->op1_value_i, d->op2_value_l, d->operation));

        else if (d->op2_type == QVariant::Int)
            d->emitter_i->setData(d->operate(d->op1_value_i, d->op2_value_i, d->operation));
    }
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberOperator::push(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
dtkComposerNodeAbstractTransmitter *dtkComposerNodeNumberOperator::emitter(dtkComposerNodeProperty *property)
{
    if(!(property == d->property_right_value))
        return NULL;

    if (d->value_type == QVariant::Int)
        return d->emitter_i;
    else if (d->value_type == QVariant::LongLong)
        return d->emitter_l;
    else if (d->value_type == QVariant::Double)
        return d->emitter_d;
    
    return NULL;
}

//! Sets the receiver from the emitter of the node at the source of \a
//! route.
/*! 
 *  When the source emitter can be casted into current receiver type,
 *  true is returned. Else it returns false.
 *
 *  It makes also the node non-interactive and clears the text of
 *  edition aera.
 *
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeNumberOperator::onLeftRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *destination)
{
    Q_UNUSED(destination);

    bool receiver_set = true;

    if (destination == d->property_left_value_op1) {

        if (d->op1_type == QVariant::Invalid) {

            if (dtkComposerNodeTransmitter<int> *receiver_i = dynamic_cast<dtkComposerNodeTransmitter<int> *>(route->source()->node()->emitter(route->source()))) {
                d->op1_type = QVariant::Int;
                d->receivers_i.insert(route, receiver_i);

            } else if (dtkComposerNodeTransmitter<qlonglong> *receiver_l = dynamic_cast<dtkComposerNodeTransmitter<qlonglong> *>(route->source()->node()->emitter(route->source()))) {
                d->op1_type = QVariant::LongLong;
                d->receivers_l.insert(route, receiver_l);

            } else if (dtkComposerNodeTransmitter<double> *receiver_d = dynamic_cast<dtkComposerNodeTransmitter<double> *>(route->source()->node()->emitter(route->source()))) {
                d->op1_type = QVariant::Double;
                d->receivers_d.insert(route, receiver_d);

            } else {

                receiver_set = false;
            }

        } else if (d->op1_type == QVariant::Int) {

            if (dtkComposerNodeTransmitter<int> *receiver_i = dynamic_cast<dtkComposerNodeTransmitter<int> *>(route->source()->node()->emitter(route->source()))) {
                d->receivers_i.insert(route, receiver_i);

            } else {

                receiver_set = false;
            }

        } else if (d->op1_type == QVariant::LongLong) {

            if (dtkComposerNodeTransmitter<qlonglong> *receiver_l = dynamic_cast<dtkComposerNodeTransmitter<qlonglong> *>(route->source()->node()->emitter(route->source()))) {
                d->receivers_l.insert(route, receiver_l);

            } else {

                receiver_set = false;
            }

        } else if (d->op1_type == QVariant::Double) {

            if (dtkComposerNodeTransmitter<double> *receiver_d = dynamic_cast<dtkComposerNodeTransmitter<double> *>(route->source()->node()->emitter(route->source()))) {
                d->receivers_d.insert(route, receiver_d);

            } else {

                receiver_set = false;
            }
        }
    
    } else {

        if (d->op2_type == QVariant::Invalid) {

            if (dtkComposerNodeTransmitter<int> *receiver_i = dynamic_cast<dtkComposerNodeTransmitter<int> *>(route->source()->node()->emitter(route->source()))) {
                d->op2_type = QVariant::Int;
                d->receivers_i.insert(route, receiver_i);

            } else if (dtkComposerNodeTransmitter<qlonglong> *receiver_l = dynamic_cast<dtkComposerNodeTransmitter<qlonglong> *>(route->source()->node()->emitter(route->source()))) {
                d->op2_type = QVariant::LongLong;
                d->receivers_l.insert(route, receiver_l);

            } else if (dtkComposerNodeTransmitter<double> *receiver_d = dynamic_cast<dtkComposerNodeTransmitter<double> *>(route->source()->node()->emitter(route->source()))) {
                d->op2_type = QVariant::Double;
                d->receivers_d.insert(route, receiver_d);

            }

        } else if (d->op2_type == QVariant::Int) {

            if (dtkComposerNodeTransmitter<int> *receiver_i = dynamic_cast<dtkComposerNodeTransmitter<int> *>(route->source()->node()->emitter(route->source()))) {
                d->receivers_i.insert(route, receiver_i);

            } else {

                receiver_set = false;
            }

        } else if (d->op2_type == QVariant::LongLong) {

            if (dtkComposerNodeTransmitter<qlonglong> *receiver_l = dynamic_cast<dtkComposerNodeTransmitter<qlonglong> *>(route->source()->node()->emitter(route->source()))) {
                d->receivers_l.insert(route, receiver_l);

            } else {

                receiver_set = false;
            }

        } else if (d->op2_type == QVariant::Double) {

            if (dtkComposerNodeTransmitter<double> *receiver_d = dynamic_cast<dtkComposerNodeTransmitter<double> *>(route->source()->node()->emitter(route->source()))) {
                d->receivers_d.insert(route, receiver_d);

            } else {

                receiver_set = false;
            }
        }
    }

    d->setValueType();

    return receiver_set;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeNumberOperator::onRightRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    return true;
}

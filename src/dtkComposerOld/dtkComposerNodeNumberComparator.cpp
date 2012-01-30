/* dtkComposerNodeNumberComparator.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Mar  7 09:24:11 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  7 16:18:42 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 134
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
#include "dtkComposerNodeTransmitter.h"
#include "dtkComposerRoute.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparatorLabel declaration
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

public:
    QPainterPath path;
    QString text;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparatorLabel implementation
// /////////////////////////////////////////////////////////////////

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
// dtkComposerNodeNumberComparatorPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberComparatorPrivate
{
public:
    bool compare(const double&, const double&, dtkComposerNodeNumberComparator::Operation);
    bool compare(const qlonglong&, const qlonglong&, dtkComposerNodeNumberComparator::Operation);
    bool compare(const int&, const int&, dtkComposerNodeNumberComparator::Operation);

public:
    dtkComposerNodeProperty *property_left_value_op1;
    dtkComposerNodeProperty *property_left_value_op2;
    dtkComposerNodeProperty *property_right_value;

public:
    dtkComposerNodeNumberComparatorLabel *label;

public:
    dtkComposerNodeNumberComparator::Operation operation;

public:    
    int op1_value_i; qlonglong op1_value_l; double op1_value_d;
    int op2_value_i; qlonglong op2_value_l; double op2_value_d;

    QVariant::Type op1_type;
    QVariant::Type op2_type;

public:
    dtkComposerNodeTransmitter<bool> *emitter;

    QHash<dtkComposerRoute *, dtkComposerNodeTransmitter<int> *> receivers_i;
    QHash<dtkComposerRoute *, dtkComposerNodeTransmitter<qlonglong> *> receivers_l;
    QHash<dtkComposerRoute *, dtkComposerNodeTransmitter<double> *> receivers_d;

public:
    dtkComposerNodeNumberComparator *q;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparatorPrivate implementation
// /////////////////////////////////////////////////////////////////

bool dtkComposerNodeNumberComparatorPrivate::compare(const double& lhs, const double& rhs, dtkComposerNodeNumberComparator::Operation operation)
{
    switch(operation) {
    case dtkComposerNodeNumberComparator::LesserThan:
        return lhs < rhs;
    case dtkComposerNodeNumberComparator::LesserThanOrEqual:
        return lhs <= rhs;
    case dtkComposerNodeNumberComparator::GreaterThan:
        return lhs > rhs;
    case dtkComposerNodeNumberComparator::GreaterThanOrEqual:
        return lhs >= rhs;
    case dtkComposerNodeNumberComparator::Equal:
        return lhs == rhs;
    case dtkComposerNodeNumberComparator::Differ:
        return lhs != rhs;
    default:
        return false;
    }
}

bool dtkComposerNodeNumberComparatorPrivate::compare(const qlonglong& lhs, const qlonglong& rhs, dtkComposerNodeNumberComparator::Operation operation)
{
    switch(operation) {
    case dtkComposerNodeNumberComparator::LesserThan:
        return lhs < rhs;
    case dtkComposerNodeNumberComparator::LesserThanOrEqual:
        return lhs <= rhs;
    case dtkComposerNodeNumberComparator::GreaterThan:
        return lhs > rhs;
    case dtkComposerNodeNumberComparator::GreaterThanOrEqual:
        return lhs >= rhs;
    case dtkComposerNodeNumberComparator::Equal:
        return lhs == rhs;
    case dtkComposerNodeNumberComparator::Differ:
        return lhs != rhs;
    default:
        return false;
    }
}

bool dtkComposerNodeNumberComparatorPrivate::compare(const int& lhs, const int& rhs, dtkComposerNodeNumberComparator::Operation operation)
{
    switch(operation) {
    case dtkComposerNodeNumberComparator::LesserThan:
        return lhs < rhs;
    case dtkComposerNodeNumberComparator::LesserThanOrEqual:
        return lhs <= rhs;
    case dtkComposerNodeNumberComparator::GreaterThan:
        return lhs > rhs;
    case dtkComposerNodeNumberComparator::GreaterThanOrEqual:
        return lhs >= rhs;
    case dtkComposerNodeNumberComparator::Equal:
        return lhs == rhs;
    case dtkComposerNodeNumberComparator::Differ:
        return lhs != rhs;
    default:
        return false;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberComparator implementation
// /////////////////////////////////////////////////////////////////

//! Constructs number operator node.
/*! 
 *  operation < is set by default.
 */
dtkComposerNodeNumberComparator::dtkComposerNodeNumberComparator(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeNumberComparatorPrivate)
{
    d->q = this;

    d->property_left_value_op1 = new dtkComposerNodeProperty("left operand", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);
    d->property_left_value_op2 = new dtkComposerNodeProperty("right operand", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);

    d->property_right_value = new dtkComposerNodeProperty("result", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeNumberComparatorLabel(this);
    d->label->setPos(0, 0);

    d->operation = dtkComposerNodeNumberComparator::LesserThan;

    this->setTitle("NumberComparator");
    this->setKind(dtkComposerNode::Process);
    this->setType("dtkComposerNumberComparator");

    this->g->appendLeftProperty(d->property_left_value_op1);
    this->g->appendLeftProperty(d->property_left_value_op2);
    this->g->appendRightProperty(d->property_right_value);

    d->op1_type = QVariant::Invalid;
    d->op2_type = QVariant::Invalid;

    d->emitter = new dtkComposerNodeTransmitter<bool>();
}

//! Destroys number operator node.
/*! 
 *  
 */
dtkComposerNodeNumberComparator::~dtkComposerNodeNumberComparator(void)
{
    delete d;

    d = NULL;
}

//! Sets current operator type.
/*! 
 *
 */
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

//! Returns current operation type.
/*! 
 *  
 */
dtkComposerNodeNumberComparator::Operation dtkComposerNodeNumberComparator::operation(void)
{
    return d->operation;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberComparator::pull(dtkComposerRoute *route, dtkComposerNodeProperty *property)
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
void dtkComposerNodeNumberComparator::run(void)
{
    if (d->op1_type == QVariant::Double) {

        if (d->op2_type == QVariant::Double)
            d->emitter->setData(d->compare(d->op1_value_d, d->op2_value_d, d->operation));

        else if (d->op2_type == QVariant::LongLong)
            d->emitter->setData(d->compare(d->op1_value_d, (double)d->op2_value_l, d->operation));

        else if (d->op2_type == QVariant::Int)
            d->emitter->setData(d->compare(d->op1_value_d, (double)d->op2_value_i, d->operation));

    } else if (d->op1_type == QVariant::LongLong) {

        if (d->op2_type == QVariant::Double)
            d->emitter->setData(d->compare((double)d->op1_value_l, d->op2_value_d, d->operation));

        else if (d->op2_type == QVariant::LongLong)
            d->emitter->setData(d->compare(d->op1_value_l, d->op2_value_l, d->operation));

        else if (d->op2_type == QVariant::Int)
            d->emitter->setData(d->compare(d->op1_value_l, (qlonglong)d->op2_value_i, d->operation));
    
    } else if (d->op1_type == QVariant::Int) {

        if (d->op2_type == QVariant::Double)
            d->emitter->setData(d->compare((double)d->op1_value_i, d->op2_value_d, d->operation));

        else if (d->op2_type == QVariant::LongLong)
            d->emitter->setData(d->compare((qlonglong)d->op1_value_i, d->op2_value_l, d->operation));

        else if (d->op2_type == QVariant::Int)
            d->emitter->setData(d->compare(d->op1_value_i, d->op2_value_i, d->operation));
    }
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberComparator::push(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
dtkComposerNodeAbstractTransmitter *dtkComposerNodeNumberComparator::emitter(dtkComposerNodeProperty *property)
{
    if(!(property == d->property_right_value))
        return NULL;

    return d->emitter;
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
bool dtkComposerNodeNumberComparator::onLeftRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *destination)
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

    return receiver_set;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeNumberComparator::onRightRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    return true;
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

    // dtkComposerNodeNumber::Genre genre = dtkComposerNodeNumber::genre(a, b);

    // if (genre != dtkComposerNodeNumber::Invalid) {

    //     switch (d->operation) {

    //     case dtkComposerNodeNumberComparator::LesserThan:
    //         switch (genre) {
    //         case dtkComposerNodeNumber::Int:
    //             d->value = a.toInt() < b.toInt();
    //             break;
    //         case dtkComposerNodeNumber::UInt:
    //             d->value = a.toUInt() < b.toUInt();
    //             break;
    //         case dtkComposerNodeNumber::Long:
    //         case dtkComposerNodeNumber::LongLong:
    //             d->value = a.toLongLong() < b.toLongLong();
    //             break;
    //         case dtkComposerNodeNumber::ULong:
    //         case dtkComposerNodeNumber::ULongLong:
    //             d->value = a.toULongLong() < b.toULongLong();
    //             break;
    //         case dtkComposerNodeNumber::Float:
    //             d->value = dtkLesserThanUlps(qVariantValue<float>(a), qVariantValue<float>(b), (int32_t)10);
    //             break;
    //         case dtkComposerNodeNumber::Double:
    //             d->value = dtkLesserThanUlps(a.toDouble(), b.toDouble(), (int64_t)10);
    //             break;
    //         case dtkComposerNodeNumber::Invalid:
    //         default:
    //             break;
    //         }
    //         break;

    //     case dtkComposerNodeNumberComparator::LesserThanOrEqual:
    //         switch (genre) {
    //         case dtkComposerNodeNumber::Int:
    //             d->value = a.toInt() <= b.toInt();
    //             break;
    //         case dtkComposerNodeNumber::UInt:
    //             d->value = a.toUInt() <= b.toUInt();
    //             break;
    //         case dtkComposerNodeNumber::Long:
    //         case dtkComposerNodeNumber::LongLong:
    //             d->value = a.toLongLong() <= b.toLongLong();
    //             break;
    //         case dtkComposerNodeNumber::ULong:
    //         case dtkComposerNodeNumber::ULongLong:
    //             d->value = a.toULongLong() <= b.toULongLong();
    //             break;
    //         case dtkComposerNodeNumber::Float:
    //             d->value = dtkLesserThanOrAlmostEqualUlps(qVariantValue<float>(a), qVariantValue<float>(b), (int32_t)10);
    //             break;
    //         case dtkComposerNodeNumber::Double:
    //             d->value = dtkLesserThanOrAlmostEqualUlps(a.toDouble(), b.toDouble(), (int64_t)10);
    //             break;
    //         case dtkComposerNodeNumber::Invalid:
    //         default:
    //             break;
    //         }
    //         break;

    //     case dtkComposerNodeNumberComparator::GreaterThan:
    //         switch (genre) {
    //         case dtkComposerNodeNumber::Int:
    //             d->value = a.toInt() > b.toInt();
    //             break;
    //         case dtkComposerNodeNumber::UInt:
    //             d->value = a.toUInt() > b.toUInt();
    //             break;
    //         case dtkComposerNodeNumber::Long:
    //         case dtkComposerNodeNumber::LongLong:
    //             d->value = a.toLongLong() > b.toLongLong();
    //             break;
    //         case dtkComposerNodeNumber::ULong:
    //         case dtkComposerNodeNumber::ULongLong:
    //             d->value = a.toULongLong() > b.toULongLong();
    //             break;
    //         case dtkComposerNodeNumber::Float:
    //             d->value = dtkGreaterThanUlps(qVariantValue<float>(a), qVariantValue<float>(b), (int32_t)10);
    //             break;
    //         case dtkComposerNodeNumber::Double:
    //             d->value = dtkGreaterThanUlps(a.toDouble(), b.toDouble(), (int64_t)10);
    //             break;
    //         case dtkComposerNodeNumber::Invalid:
    //         default:
    //             break;
    //         }
    //         break;

    //     case dtkComposerNodeNumberComparator::GreaterThanOrEqual:
    //         switch (genre) {
    //         case dtkComposerNodeNumber::Int:
    //             d->value = a.toInt() >= b.toInt();
    //             break;
    //         case dtkComposerNodeNumber::UInt:
    //             d->value = a.toUInt() >= b.toUInt();
    //             break;
    //         case dtkComposerNodeNumber::Long:
    //         case dtkComposerNodeNumber::LongLong:
    //             d->value = a.toLongLong() >= b.toLongLong();
    //             break;
    //         case dtkComposerNodeNumber::ULong:
    //         case dtkComposerNodeNumber::ULongLong:
    //             d->value = a.toULongLong() >= b.toULongLong();
    //             break;
    //         case dtkComposerNodeNumber::Float:
    //             d->value = dtkGreaterThanOrAlmostEqualUlps(qVariantValue<float>(a), qVariantValue<float>(b), (int32_t)10);
    //             break;
    //         case dtkComposerNodeNumber::Double:
    //             d->value = dtkGreaterThanOrAlmostEqualUlps(a.toDouble(), b.toDouble(), (int64_t)10);
    //             break;
    //         case dtkComposerNodeNumber::Invalid:
    //         default:
    //             break;
    //         }
    //         break;

    //     case dtkComposerNodeNumberComparator::Equal:
    //         switch (genre) {
    //         case dtkComposerNodeNumber::Int:
    //             d->value = a.toInt() == b.toInt();
    //             break;
    //         case dtkComposerNodeNumber::UInt:
    //             d->value = a.toUInt() == b.toUInt();
    //             break;
    //         case dtkComposerNodeNumber::Long:
    //         case dtkComposerNodeNumber::LongLong:
    //             d->value = a.toLongLong() == b.toLongLong();
    //             break;
    //         case dtkComposerNodeNumber::ULong:
    //         case dtkComposerNodeNumber::ULongLong:
    //             d->value = a.toULongLong() == b.toULongLong();
    //             break;
    //         case dtkComposerNodeNumber::Float:
    //             d->value = dtkAlmostEqualUlps(qVariantValue<float>(a), qVariantValue<float>(b), (int32_t)10);
    //             break;
    //         case dtkComposerNodeNumber::Double:
    //             d->value = dtkAlmostEqualUlps(a.toDouble(), b.toDouble(), (int64_t)10);
    //             break;
    //         case dtkComposerNodeNumber::Invalid:
    //         default:
    //             break;
    //         }
    //         break;

    //     case dtkComposerNodeNumberComparator::Differ:
    //         switch (genre) {
    //         case dtkComposerNodeNumber::Int:
    //             d->value = a.toInt() != b.toInt();
    //             break;
    //         case dtkComposerNodeNumber::UInt:
    //             d->value = a.toUInt() != b.toUInt();
    //             break;
    //         case dtkComposerNodeNumber::Long:
    //         case dtkComposerNodeNumber::LongLong:
    //             d->value = a.toLongLong() != b.toLongLong();
    //             break;
    //         case dtkComposerNodeNumber::ULong:
    //         case dtkComposerNodeNumber::ULongLong:
    //             d->value = a.toULongLong() != b.toULongLong();
    //             break;
    //         case dtkComposerNodeNumber::Float:
    //             d->value = !(dtkAlmostEqualUlps(qVariantValue<float>(a), qVariantValue<float>(b), (int32_t)10));
    //             break;
    //         case dtkComposerNodeNumber::Double:
    //             d->value = !(dtkAlmostEqualUlps(a.toDouble(), b.toDouble(), (int64_t)10));
    //             break;
    //         case dtkComposerNodeNumber::Invalid:
    //         default:
    //             break;
    //         }
    //         break;

    //     default:
    //         break;
    //     }
    // }

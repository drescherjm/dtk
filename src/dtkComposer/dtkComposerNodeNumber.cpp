/* dtkComposerNodeNumber.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Feb 25 16:21:13 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 28 11:09:36 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberLabel
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberLabel : public QGraphicsItem
{
public:
     dtkComposerNodeNumberLabel(dtkComposerNodeNumber *parent);
    ~dtkComposerNodeNumberLabel(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeNumber *parent_node;
    QPainterPath path;
    QString text;
};

dtkComposerNodeNumberLabel::dtkComposerNodeNumberLabel(dtkComposerNodeNumber *parent) : QGraphicsItem(parent)
{
    QPainterPath b; b.addRoundedRect( 0, 0, 10, 15, 5, 5);
    QPainterPath c; c.addRoundedRect(10, 0, 20, 15, 5, 5);
    QPainterPath d; d.addRoundedRect(30, 0, 10, 15, 5, 5);
    QPainterPath e; e.addRoundedRect( 5, 0, 30,  7, 0, 0);

    path = c.united(e.subtracted(b.united(c.united(d))));
    
    path.translate(path.boundingRect().width()/2 * -1, 0);

    parent_node = parent;

    //text = parent_node->value() ? "T" : "F";
}

dtkComposerNodeNumberLabel::~dtkComposerNodeNumberLabel(void)
{

}

QRectF dtkComposerNodeNumberLabel::boundingRect(void) const
{
    return path.boundingRect();
}

void dtkComposerNodeNumberLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void dtkComposerNodeNumberLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if (text == "T")
        text = "F";
    else
        text = "T";

    parent_node->setValue(text == "T" ? true : false);

    this->update();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberPrivate
{
public:
    dtkComposerNodeProperty *property_input_value;
    dtkComposerNodeProperty *property_output_value;

public:
    dtkComposerNodeNumberLabel *label;

public:
    QVariant value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumber
// /////////////////////////////////////////////////////////////////

dtkComposerNodeNumber::dtkComposerNodeNumber(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeNumberPrivate)
{
    d->property_input_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_output_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeNumberLabel(this);
    d->label->setPos(40, -20);

    d->value = QVariant(0);

    this->setTitle("Number");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerNumber");

    this->addInputProperty(d->property_input_value);
    this->addOutputProperty(d->property_output_value);
}

dtkComposerNodeNumber::~dtkComposerNodeNumber(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeNumber::value(dtkComposerNodeProperty *property)
{
    if(property == d->property_output_value)
        return d->value;
}

QVariant dtkComposerNodeNumber::value(void)
{
    return d->value;
}

void dtkComposerNodeNumber::setValue(int value)
{
    d->value = QVariant(value);
}

void dtkComposerNodeNumber::setValue(uint value)
{
    d->value = QVariant(value);
}

void dtkComposerNodeNumber::setValue(long value)
{
    d->value = qVariantFromValue(value);
}

void dtkComposerNodeNumber::setValue(ulong value)
{
    d->value = qVariantFromValue(value);
}

void dtkComposerNodeNumber::setValue(qlonglong value)
{
    d->value = QVariant(value);
}

void dtkComposerNodeNumber::setValue(qulonglong value)
{
    d->value = QVariant(value);
}

void dtkComposerNodeNumber::setValue(float value)
{
    d->value = qVariantFromValue(value);
}

void dtkComposerNodeNumber::setValue(double value)
{
    d->value = QVariant(value);
}

void dtkComposerNodeNumber::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if (property == d->property_input_value) {

        // QVariant value = edge->source()->node()->value(edge->source());
        
        // if(value.canConvert(QVariant::Integer)) {
        //     this->setValue(value.toBool());
        // } else {
        //     qDebug() << DTK_PRETTY_FUNCTION << "Input value expected to be boolean. Assuming false.";
        //     this->setValue(false);
        // }
    }
}

void dtkComposerNodeNumber::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);
}

void dtkComposerNodeNumber::run(void)
{

}

/* dtkComposerNodeBoolean.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 25 10:07:34 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 25 15:44:23 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 190
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanLabel
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanLabel : public QGraphicsItem
{
public:
     dtkComposerNodeBooleanLabel(dtkComposerNodeBoolean *parent);
    ~dtkComposerNodeBooleanLabel(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerNodeBoolean *parent_node;
    QPainterPath path;
    QString text;
};

dtkComposerNodeBooleanLabel::dtkComposerNodeBooleanLabel(dtkComposerNodeBoolean *parent) : QGraphicsItem(parent)
{
    QPainterPath b; b.addRoundedRect( 0, 0, 10, 15, 5, 5);
    QPainterPath c; c.addRoundedRect(10, 0, 20, 15, 5, 5);
    QPainterPath d; d.addRoundedRect(30, 0, 10, 15, 5, 5);
    QPainterPath e; e.addRoundedRect( 5, 0, 30,  7, 0, 0);

    path = c.united(e.subtracted(b.united(c.united(d))));
    
    path.translate(path.boundingRect().width()/2 * -1, 0);

    parent_node = parent;

    text = parent_node->value() ? "T" : "F";
}

dtkComposerNodeBooleanLabel::~dtkComposerNodeBooleanLabel(void)
{

}

QRectF dtkComposerNodeBooleanLabel::boundingRect(void) const
{
    return path.boundingRect();
}

void dtkComposerNodeBooleanLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void dtkComposerNodeBooleanLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
// dtkComposerNodeBooleanPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanPrivate
{
public:
    dtkComposerNodeProperty *property_input_value;
    dtkComposerNodeProperty *property_output_value;

public:
    dtkComposerNodeBooleanLabel *label;

public:
    bool value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBoolean
// /////////////////////////////////////////////////////////////////

dtkComposerNodeBoolean::dtkComposerNodeBoolean(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeBooleanPrivate)
{
    d->property_input_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_output_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeBooleanLabel(this);
    d->label->setPos(40, -20);

    d->value = false;

    this->setTitle("Boolean");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerBoolean");

    this->addInputProperty(d->property_input_value);
    this->addOutputProperty(d->property_output_value);
}

dtkComposerNodeBoolean::~dtkComposerNodeBoolean(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeBoolean::value(dtkComposerNodeProperty *property)
{
    if(property == d->property_output_value)
        return QVariant(d->value);
}

bool dtkComposerNodeBoolean::value(void)
{
    return d->value;
}

void dtkComposerNodeBoolean::setValue(bool value)
{
    d->value = value;

    d->label->text = value ? "T" : "F";
    d->label->update();
}

void dtkComposerNodeBoolean::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if (property == d->property_input_value) {

        QVariant value = edge->source()->node()->value(edge->source());
        
        if(value.canConvert(QVariant::Bool)) {
            this->setValue(value.toBool());
        } else {
            qDebug() << DTK_PRETTY_FUNCTION << "Input value expected to be boolean. Assuming false.";
            this->setValue(false);
        }
    }
}

void dtkComposerNodeBoolean::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);
}

void dtkComposerNodeBoolean::run(void)
{

}

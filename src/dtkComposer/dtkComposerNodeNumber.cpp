/* dtkComposerNodeNumber.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Feb 25 16:21:13 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed May 18 16:23:31 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 391
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
    bool expanded;
};

dtkComposerNodeNumberLabel::dtkComposerNodeNumberLabel(dtkComposerNodeNumber *parent) : QGraphicsItem(parent)
{
    int margin = 10;
    int length = 77;
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

    text = "INT";

    expanded = false;
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
    painter->drawText(this->boundingRect(), Qt::AlignCenter, text);
}

void dtkComposerNodeNumberLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);    

    if (text == "INT")
        text = "UINT";
    else if (text == "UINT")
        text = "LONG";
    else if (text == "LONG")
        text = "ULONG";
    else if (text == "ULONG")
        text = "LLONG";
    else if (text == "LLONG")
        text = "ULLONG";
    else if (text == "ULLONG")
        text = "FLOAT";
    else if (text == "FLOAT")
        text = "DOUBLE";
    else if (text == "DOUBLE")
        text = "INT";

    this->update();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberButton
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberButton : public QGraphicsItem
{
public:
     dtkComposerNodeNumberButton(dtkComposerNodeNumber *parent);
    ~dtkComposerNodeNumberButton(void);

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
    bool expanded;
};

dtkComposerNodeNumberButton::dtkComposerNodeNumberButton(dtkComposerNodeNumber *parent) : QGraphicsItem(parent)
{
    int margin = 10;
    int length = 30;
    int height = 10;
    int radius =  5;
    int origin_x = -(length + margin) / 2;
    int origin_y = parent->boundingRect().height() / 2;

    QPainterPath b; b.addRoundedRect(origin_x,              origin_y, margin,          -height,     radius, radius);
    QPainterPath c; c.addRoundedRect(origin_x + margin,     origin_y, length - margin, -height,     radius, radius);
    QPainterPath d; d.addRoundedRect(origin_x + length,     origin_y, margin,          -height,     radius, radius);
    QPainterPath e; e.addRoundedRect(origin_x + margin / 2, origin_y, length,          -height / 2,      0,      0);

    path = c.united(e.subtracted(b.united(c.united(d))));

    parent_node = parent;
    
    text = "+";

    expanded = false;
}

dtkComposerNodeNumberButton::~dtkComposerNodeNumberButton(void)
{

}

QRectF dtkComposerNodeNumberButton::boundingRect(void) const
{
    return path.boundingRect();
}

void dtkComposerNodeNumberButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    QFont font("Lucida Grande", 8);
#else
    QFont font("Lucida Grande", 6);
#endif
    font.setBold(true);

    QFontMetrics metrics(font);
    
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, text);
}

void dtkComposerNodeNumberButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if(!this->expanded) {
        parent_node->expand();
        text = "-";
    } else {
        parent_node->collapse();
        text = "+";
    }

    this->expanded = !this->expanded;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberEditor
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberEditor : public QGraphicsTextItem
{
public:
    dtkComposerNodeNumberEditor(dtkComposerNodeNumber *parent);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    dtkComposerNodeNumber *parent_node;
};

dtkComposerNodeNumberEditor::dtkComposerNodeNumberEditor(dtkComposerNodeNumber *parent) : QGraphicsTextItem(parent)
{
#if defined(Q_WS_MAC)
    QFont font("Lucida Grande", 10);
#else
    QFont font("Lucida Grande", 8);
#endif

    this->setDefaultTextColor(Qt::lightGray);
    this->setFont(font);
    this->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->setFlag(QGraphicsItem::ItemStacksBehindParent, true);

    this->parent_node = parent;
}

void dtkComposerNodeNumberEditor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath s_rect; s_rect.addRect(QRectF(option->rect.topLeft(), QSizeF(option->rect.width(), option->rect.height() / 2)));
    QPainterPath r_rect; r_rect.addRoundedRect(option->rect, 5, 5);
    QPainterPath path = s_rect.united(r_rect);

    painter->save();
    painter->setPen(Qt::darkGray);
    painter->setBrush(Qt::black);
    painter->drawPath(path);
    painter->restore();

    QStyleOptionGraphicsItem *o = const_cast<QStyleOptionGraphicsItem*>(option);
    o->state &= ~QStyle::State_Selected;
    o->state &= ~QStyle::State_HasFocus;

    QGraphicsTextItem::paint(painter, option, widget);
}

void dtkComposerNodeNumberEditor::keyPressEvent(QKeyEvent *event)
{
    QGraphicsTextItem::keyPressEvent(event);

    this->parent_node->setValue(qVariantFromValue(this->toPlainText()));
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
    dtkComposerNodeNumberButton *button;
    dtkComposerNodeNumberEditor *editor;

public:
    QPropertyAnimation *animation;

public:
    QHash<QString, int> genres;

    QVariant value;

    bool source_node;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumber
// /////////////////////////////////////////////////////////////////

dtkComposerNodeNumber::dtkComposerNodeNumber(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeNumberPrivate)
{
    d->property_input_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_output_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeNumberLabel(this);
    d->label->setPos(0, 0);

    d->button = new dtkComposerNodeNumberButton(this);
    d->button->setPos(0, 0);
    
    d->value = QVariant();
    d->source_node = true;

    d->genres.insert(   QString("INT"),       (int)dtkComposerNodeNumber::Int);
    d->genres.insert(  QString("UINT"),      (int)dtkComposerNodeNumber::UInt);
    d->genres.insert(  QString("LONG"),      (int)dtkComposerNodeNumber::Long);
    d->genres.insert( QString("ULONG"),     (int)dtkComposerNodeNumber::ULong);
    d->genres.insert( QString("LLONG"),  (int)dtkComposerNodeNumber::LongLong);
    d->genres.insert(QString("ULLONG"), (int)dtkComposerNodeNumber::ULongLong);
    d->genres.insert( QString("FLOAT"),     (int)dtkComposerNodeNumber::Float);
    d->genres.insert(QString("DOUBLE"),    (int)dtkComposerNodeNumber::Double);

    this->setTitle("Number");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerNumber");

    this->addInputProperty(d->property_input_value);
    this->addOutputProperty(d->property_output_value);

    // --
    
    d->editor = new dtkComposerNodeNumberEditor(this);
    d->editor->setPos(-d->editor->boundingRect().width() / 2, 0);
    d->editor->setTextWidth(0.8 * this->boundingRect().width());
    d->editor->hide();

    // --

    d->animation = new QPropertyAnimation(d->editor, "pos");
    d->animation->setDuration(500);
    d->animation->setStartValue(QPointF(-d->editor->boundingRect().width()/2, 0));
    d->animation->setEndValue(QPointF(-d->editor->boundingRect().width()/2, 0.85 * d->editor->boundingRect().height()));
    d->animation->setEasingCurve(QEasingCurve::OutBounce);
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

    return QVariant();
}

QVariant dtkComposerNodeNumber::value(void)
{
    if (d->value.userType() != d->genres.value(d->label->text))
        this->convertTo(d->genres.value(d->label->text));

    return d->value;
}

void dtkComposerNodeNumber::setValue(QVariant value)
{
    d->value = value;
}

//! Convenient function to sidestep the bug in
//! QVariant::convert(QVariant::Type) method.
/*! 
 * 
 * 
 */
void dtkComposerNodeNumber::convertTo(int genre)
{
    switch (genre) { 
    case (dtkComposerNodeNumber::Int): 
        this->setValue(qVariantFromValue(d->editor->toPlainText().toInt()));
        break; 
    case (dtkComposerNodeNumber::UInt): 
        this->setValue(qVariantFromValue(d->editor->toPlainText().toUInt())); 
        break; 
    case (dtkComposerNodeNumber::Long): 
        this->setValue(qVariantFromValue(d->editor->toPlainText().toLong())); 
        break; 
    case (dtkComposerNodeNumber::ULong): 
        this->setValue(qVariantFromValue(d->editor->toPlainText().toULong())); 
        break; 
    case (dtkComposerNodeNumber::LongLong): 
        this->setValue(qVariantFromValue(d->editor->toPlainText().toLongLong())); 
        break; 
    case (dtkComposerNodeNumber::ULongLong): 
        this->setValue(qVariantFromValue(d->editor->toPlainText().toULongLong())); 
        break; 
    case (dtkComposerNodeNumber::Float): 
        this->setValue(qVariantFromValue(d->editor->toPlainText().toFloat())); 
        break; 
    case (dtkComposerNodeNumber::Double): 
        this->setValue(qVariantFromValue(d->editor->toPlainText().toDouble())); 
        break; 
     default: 
         break;
    }
}

void dtkComposerNodeNumber::expand(void)
{
    d->editor->show();
    d->animation->setDirection(QAbstractAnimation::Forward);
    d->animation->start();
}

void dtkComposerNodeNumber::collapse(void)
{
    d->animation->setDirection(QAbstractAnimation::Backward);
    d->animation->start();

    connect(d->animation, SIGNAL(finished()), this, SLOT(onCollapseFinised()));
}

void dtkComposerNodeNumber::touch(void)
{
    d->editor->setPlainText(d->value.toString()); 
    d->editor->update();

    d->label->text = d->genres.key(d->value.userType()); 
    d->label->update();

    dtkComposerNode::touch();
}

void dtkComposerNodeNumber::onCollapseFinised(void)
{
    d->editor->hide();

    disconnect(d->animation, SIGNAL(finished()), this, SLOT(onCollapseFinised()));    
}

void dtkComposerNodeNumber::pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if (property == d->property_input_value) {

        QVariant value = edge->source()->node()->value(edge->source());
        if (value.userType() == dtkComposerNodeNumber::Invalid) {
            qDebug() << DTK_PRETTY_FUNCTION << "Input number has an invalid genre.";
            return;
        }
        d->value = value;

        d->source_node = false;

        d->editor->setPlainText(d->value.toString()); 
        d->editor->update();

        d->label->text = d->genres.key(d->value.userType()); 
        d->label->update();
    }
    return;
}

void dtkComposerNodeNumber::run(void)
{
    if (d->source_node)
        this->convertTo(d->genres.value(d->label->text));
    
    d->source_node = true;
}

void dtkComposerNodeNumber::push(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);
}

dtkComposerNodeNumber::Genre dtkComposerNodeNumber::genre(QVariant& a, QVariant& b)
{
    if (a.userType() == dtkComposerNodeNumber::Invalid && b.userType() == dtkComposerNodeNumber::Invalid) {

        return dtkComposerNodeNumber::Invalid;

    } else if (a.userType() == dtkComposerNodeNumber::Invalid) {

        return (dtkComposerNodeNumber::Genre)b.userType();

    } else if (b.userType() == dtkComposerNodeNumber::Invalid) {

        return (dtkComposerNodeNumber::Genre)a.userType();

    } else if (a.userType() == dtkComposerNodeNumber::Double || b.userType() == dtkComposerNodeNumber::Double) {

        return dtkComposerNodeNumber::Double;

    } else if (a.userType() == dtkComposerNodeNumber::Float || b.userType() == dtkComposerNodeNumber::Float) {

        return dtkComposerNodeNumber::Float;

    } else if (a.userType() == dtkComposerNodeNumber::ULongLong) {

        if (b.userType() == dtkComposerNodeNumber::ULongLong || b.userType() == dtkComposerNodeNumber::ULong || b.userType() == dtkComposerNodeNumber::UInt)
            return dtkComposerNodeNumber::ULongLong;
        else
            return dtkComposerNodeNumber::Invalid;

    } else if (b.userType() == dtkComposerNodeNumber::ULongLong) {

        if (a.userType() == dtkComposerNodeNumber::ULong || a.userType() == dtkComposerNodeNumber::UInt)
            return dtkComposerNodeNumber::ULongLong;
        else
            return dtkComposerNodeNumber::Invalid;

    } else if (a.userType() == dtkComposerNodeNumber::ULong) {

        if (b.userType() == dtkComposerNodeNumber::ULong || b.userType() == dtkComposerNodeNumber::UInt)
            return dtkComposerNodeNumber::ULong;
        else
            return dtkComposerNodeNumber::Invalid;

    } else if (b.userType() == dtkComposerNodeNumber::ULong) {

        if (a.userType() == dtkComposerNodeNumber::UInt)
            return dtkComposerNodeNumber::ULong;
        else
            return dtkComposerNodeNumber::Invalid;

    } else if (a.userType() == dtkComposerNodeNumber::UInt) {

        if (b.userType() == dtkComposerNodeNumber::UInt)
            return dtkComposerNodeNumber::UInt;
        else
            return dtkComposerNodeNumber::Invalid;

    } else if (a.userType() == dtkComposerNodeNumber::LongLong || b.userType() == dtkComposerNodeNumber::LongLong) {

        return dtkComposerNodeNumber::LongLong;

    } else if (a.userType() == dtkComposerNodeNumber::Long || b.userType() == dtkComposerNodeNumber::Long) {

        return dtkComposerNodeNumber::Long;

    } else if (a.userType() == dtkComposerNodeNumber::Int || b.userType() == dtkComposerNodeNumber::Int) {

        return dtkComposerNodeNumber::Int;

    }

    return dtkComposerNodeNumber::Invalid;
}

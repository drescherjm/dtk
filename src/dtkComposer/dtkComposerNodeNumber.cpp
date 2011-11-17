/* dtkComposerNodeNumber.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Feb 25 16:21:13 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 17 17:02:57 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 582
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
#include "dtkComposerNodeTransmitter.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberLabel declaration
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
    void setLabelText(void);
    void setLabelText(const QString& value);

public:
    dtkComposerNodeNumber::Genre genre(void);
    void setLabelText(dtkComposerNodeNumber::Genre genre);

public:
    dtkComposerNodeNumber *parent_node;
    QPainterPath path;
    QString text;
    bool expanded;

    QHash<QString, dtkComposerNodeNumber::Genre> genres;    
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberLabel implementation
// /////////////////////////////////////////////////////////////////

//! Constructs number label.
/*! 
 *  
 */
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

    genres.insert(   QString("INT"),       dtkComposerNodeNumber::Int);
    genres.insert(  QString("UINT"),      dtkComposerNodeNumber::UInt);
    genres.insert(  QString("LONG"),      dtkComposerNodeNumber::Long);
    genres.insert( QString("ULONG"),     dtkComposerNodeNumber::ULong);
    genres.insert( QString("LLONG"),  dtkComposerNodeNumber::LongLong);
    genres.insert(QString("ULLONG"), dtkComposerNodeNumber::ULongLong);
    genres.insert( QString("FLOAT"),     dtkComposerNodeNumber::Float);
    genres.insert(QString("DOUBLE"),    dtkComposerNodeNumber::Double);
}

//! Destroys number label.
/*! 
 *  
 */
dtkComposerNodeNumberLabel::~dtkComposerNodeNumberLabel(void)
{

}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
QRectF dtkComposerNodeNumberLabel::boundingRect(void) const
{
    return path.boundingRect();
}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
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

//! Enables to switch between number types.
/*! 
 *  Reimplemented from QGraphicsItem.
 */
void dtkComposerNodeNumberLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event); 

    if (parent_node->interactive())
        this->setLabelText();
}

//! Sets label text.
/*! 
 *  
 */
void dtkComposerNodeNumberLabel::setLabelText(void)
{
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

//! Sets label text.
/*! 
 *  
 */
void dtkComposerNodeNumberLabel::setLabelText(const QString& value)
{
    text = value;
}

//! Sets label text.
/*! 
 *  
 */
void dtkComposerNodeNumberLabel::setLabelText(dtkComposerNodeNumber::Genre genre)
{
    text = genres.key(genre);
}

//! Sets label text.
/*! 
 *  
 */
dtkComposerNodeNumber::Genre dtkComposerNodeNumberLabel::genre(void)
{
    return genres.value(text);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberButton declaration
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

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberButton implementation
// /////////////////////////////////////////////////////////////////

//! Constructs number button.
/*! 
 *  It enables to hide or show edition aera.
 */
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

//! Destroys number button.
/*! 
 *  
 */
dtkComposerNodeNumberButton::~dtkComposerNodeNumberButton(void)
{

}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
QRectF dtkComposerNodeNumberButton::boundingRect(void) const
{
    return path.boundingRect();
}

//! 
/*! 
 *  Reimplemented from QGraphicsItem.
 */
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

//! Enables to expand or collapse edition aera.
/*! 
 *  Reimplemented from QGraphicsItem.
 */
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
        
    parent_node->touch();

    this->expanded = !this->expanded;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberEditor declaration
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

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberEditor implementation
// /////////////////////////////////////////////////////////////////

//! Constructs number editor.
/*! 
 *  It enables to edit the text of the number node.
 */
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

//! 
/*! 
 *  Reimplemented from QGraphicsTextItem.
 */
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

//! 
/*! 
 *  Reimplemented from QGraphicsTextItem.
 */
void dtkComposerNodeNumberEditor::keyPressEvent(QKeyEvent *event)
{
    QGraphicsTextItem::keyPressEvent(event);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberPrivate
{
public:
    dtkComposerNodeProperty *property_left_value;
    dtkComposerNodeProperty *property_right_value;

public:
    dtkComposerNodeNumberLabel *label;
    dtkComposerNodeNumberButton *button;
    dtkComposerNodeNumberEditor *editor;

public:
    QPropertyAnimation *animation;

public:
    QHash<QString, int> genres;

    QVariant value;

public:
    bool interactive;

public:
    dtkComposerNodeAbstractTransmitter *transmitter;
    dtkComposerNodeTransmitter<int>    *default_emitter;

public:
    QString type_int;
    QString type_uint;
    QString type_long;
    QString type_ulong;
    QString type_llong;
    QString type_ullong;
    QString type_float;
    QString type_double;

    QHash<dtkComposerNodeNumber::Genre, QString> types;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumber implementation
// /////////////////////////////////////////////////////////////////

//! Constructs number node.
/*! 
 *  Number node is interactive by while it has no left edge.
 */
dtkComposerNodeNumber::dtkComposerNodeNumber(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeNumberPrivate)
{
    d->property_left_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);
    d->property_right_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);

    d->label = new dtkComposerNodeNumberLabel(this);
    d->label->setPos(0, 0);

    d->button = new dtkComposerNodeNumberButton(this);
    d->button->setPos(0, 0);
    
    d->value = QVariant();

    d->type_int    = typeid(int).name();
    d->type_uint   = typeid(uint).name();
    d->type_long   = typeid(long).name();
    d->type_ulong  = typeid(ulong).name();
    d->type_llong  = typeid(qlonglong).name();
    d->type_ullong = typeid(qulonglong).name();
    d->type_float  = typeid(float).name();
    d->type_double = typeid(double).name();

    d->types.insert(      dtkComposerNodeNumber::Int,    d->type_int);
    d->types.insert(     dtkComposerNodeNumber::UInt,   d->type_uint);
    d->types.insert(     dtkComposerNodeNumber::Long,   d->type_long);
    d->types.insert(    dtkComposerNodeNumber::ULong,  d->type_ulong);
    d->types.insert( dtkComposerNodeNumber::LongLong,  d->type_llong);
    d->types.insert(dtkComposerNodeNumber::ULongLong, d->type_ullong);
    d->types.insert(    dtkComposerNodeNumber::Float,  d->type_float);
    d->types.insert(   dtkComposerNodeNumber::Double, d->type_double);

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

    this->g->appendLeftProperty(d->property_left_value);
    this->g->appendRightProperty(d->property_right_value);

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

    // --

    d->interactive = true;

    d->transmitter = NULL;
    d->default_emitter = new dtkComposerNodeTransmitter<int>();
}

//! Destroys number node.
/*! 
 *  
 */
dtkComposerNodeNumber::~dtkComposerNodeNumber(void)
{
    delete d->default_emitter;

    delete d;

    d = NULL;
}

QVariant dtkComposerNodeNumber::value(void)
{
    // if (d->value.userType() != d->genres.value(d->label->text))
    //     this->convertTo(d->genres.value(d->label->text));

    // return d->value;

    return QVariant();
}

void dtkComposerNodeNumber::setValue(QVariant value)
{
    d->value = value;
}

//! Expands node to show edition aera.
/*! 
 *  
 */
void dtkComposerNodeNumber::expand(void)
{
    d->editor->show();
    d->animation->setDirection(QAbstractAnimation::Forward);
    d->animation->start();
}

//! Collapses node to hide edition aera.
/*! 
 *  
 */
void dtkComposerNodeNumber::collapse(void)
{
    d->animation->setDirection(QAbstractAnimation::Backward);
    d->animation->start();

    connect(d->animation, SIGNAL(finished()), this, SLOT(onCollapseFinised()));
}

//! Updates the graphical aspect of the node.
/*! 
 *  
 */
void dtkComposerNodeNumber::touch(void)
{
    QString value;

    if (!d->interactive && d->transmitter) {

        dtkComposerNodeNumber::Genre genre = d->types.key(d->transmitter->metadata("Type"));

        switch (genre) {

        case dtkComposerNodeNumber::Int:
            value = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<int> *>(d->transmitter)->data());
            break;

        case dtkComposerNodeNumber::UInt:
            value = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<uint> *>(d->transmitter)->data());
            break;

        case dtkComposerNodeNumber::Long:
            value = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<long> *>(d->transmitter)->data());
            break;

        case dtkComposerNodeNumber::ULong:
            value = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<ulong> *>(d->transmitter)->data());
            break;

        case dtkComposerNodeNumber::LongLong:
            value = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<qlonglong> *>(d->transmitter)->data());
            break;

        case dtkComposerNodeNumber::ULongLong:
            value = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<qulonglong> *>(d->transmitter)->data());
            break;

        case dtkComposerNodeNumber::Float:
            value = QString("%1").arg((double)static_cast<dtkComposerNodeTransmitter<float> *>(d->transmitter)->data());
            break;

        case dtkComposerNodeNumber::Double:
            value = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<double> *>(d->transmitter)->data());
            break;

        }
    
        d->editor->setPlainText(value); 
        d->editor->update();
    }

    dtkComposerNode::touch();
}

//! Hides edition aera at the end of collapsing.
/*! 
 *  
 */
void dtkComposerNodeNumber::onCollapseFinised(void)
{
    d->editor->hide();

    disconnect(d->animation, SIGNAL(finished()), this, SLOT(onCollapseFinised()));
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumber::pull(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(property);

    d->transmitter = route->source()->node()->emitter(route->source());
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumber::run(void)
{
    if (d->interactive)
        this->setTransmitterData(d->editor->toPlainText());
    else
        d->label->setLabelText(d->types.key(d->transmitter->metadata("Type")));
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumber::push(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
dtkComposerNodeAbstractTransmitter *dtkComposerNodeNumber::emitter(dtkComposerNodeProperty *property)
{
    if (property == d->property_right_value) {
        if (!d->transmitter)
            return d->default_emitter;
        else
            return d->transmitter;
    }
    
    return NULL;
}

//! Sets the receiver from the emitter of the node at the source of \a
//! route.
/*! 
 *  When the source emitter can be casted into current receiver type,
 *  true is returned. Else it returns false.
 *
 *  It makes also the node non-interactive nad clears the text of
 *  edition aera.
 *
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeNumber::setReceiver(dtkComposerEdge *route, dtkComposerNodeProperty *destination)
{
    Q_UNUSED(destination);

    d->transmitter = route->source()->node()->emitter(route->source());

    if (d->transmitter) {

        if (!(dynamic_cast<dtkComposerNodeTransmitter<int>        *>(d->transmitter)) &&
            !(dynamic_cast<dtkComposerNodeTransmitter<uint>       *>(d->transmitter)) &&
            !(dynamic_cast<dtkComposerNodeTransmitter<long>       *>(d->transmitter)) &&
            !(dynamic_cast<dtkComposerNodeTransmitter<ulong>      *>(d->transmitter)) &&
            !(dynamic_cast<dtkComposerNodeTransmitter<qlonglong>  *>(d->transmitter)) &&
            !(dynamic_cast<dtkComposerNodeTransmitter<qulonglong> *>(d->transmitter)) &&
            !(dynamic_cast<dtkComposerNodeTransmitter<float>      *>(d->transmitter)) &&
            !(dynamic_cast<dtkComposerNodeTransmitter<double>     *>(d->transmitter))) {

            qDebug() << DTK_PRETTY_FUNCTION << ": Type from node" << route->source()->node() << "is not handled by node number.";
            return false;
            
        }

        d->interactive = false;
        d->editor->setTextInteractionFlags(Qt::NoTextInteraction);
        d->editor->setPlainText("");    
        
        return true;

    }

    qDebug() << DTK_PRETTY_FUNCTION << "Transmitter of source node" << route->source()->node() << "has not been instanciated. Connection failed.";
    return false;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeNumber::onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    return true;
}

//! Returns true when node is interactive.
/*! 
 *  
 */
bool dtkComposerNodeNumber::interactive(void) const
{
    return d->interactive;
}

//! Sets the label of the node.
/*! 
 *  
 */
void dtkComposerNodeNumber::setLabelText(const QString& value)
{
    d->label->setLabelText(value);
}

//! Sets the text of the node.
/*! 
 *  
 */
void dtkComposerNodeNumber::setEditorText(const QString& value)
{
    d->editor->setPlainText(value);
}

//! Sets the label of the node.
/*! 
 *  
 */
void dtkComposerNodeNumber::setTransmitterData(const QString& value)
{    
    dtkComposerNodeTransmitter<int>        *emitter_i   = NULL;
    dtkComposerNodeTransmitter<uint>       *emitter_ui  = NULL;
    dtkComposerNodeTransmitter<long>       *emitter_l   = NULL;
    dtkComposerNodeTransmitter<ulong>      *emitter_ul  = NULL;
    dtkComposerNodeTransmitter<qlonglong>  *emitter_ll  = NULL;
    dtkComposerNodeTransmitter<qulonglong> *emitter_ull = NULL;
    dtkComposerNodeTransmitter<float>      *emitter_f   = NULL;
    dtkComposerNodeTransmitter<double>     *emitter_d   = NULL;

    switch (d->label->genre()) {

    case dtkComposerNodeNumber::Int:
        emitter_i = new dtkComposerNodeTransmitter<int>();
        emitter_i->setData(value.toInt());
        d->transmitter = emitter_i;
        break;

    case dtkComposerNodeNumber::UInt:
        emitter_ui = new dtkComposerNodeTransmitter<uint>();
        emitter_ui->setData(value.toUInt());
        d->transmitter = emitter_ui;
        break;

    case dtkComposerNodeNumber::Long:
        emitter_l = new dtkComposerNodeTransmitter<long>();
        emitter_l->setData(value.toLong());
        d->transmitter = emitter_l;
        break;

    case dtkComposerNodeNumber::ULong:
        emitter_ul = new dtkComposerNodeTransmitter<ulong>();
        emitter_ul->setData(value.toULong());
        d->transmitter = emitter_ul;
        break;

    case dtkComposerNodeNumber::LongLong:
        emitter_ll = new dtkComposerNodeTransmitter<qlonglong>();
        emitter_ll->setData(value.toLongLong());
        d->transmitter = emitter_ll;
        break;

    case dtkComposerNodeNumber::ULongLong:
        emitter_ull = new dtkComposerNodeTransmitter<qulonglong>();
        emitter_ull->setData(value.toULongLong());
        d->transmitter = emitter_ull;
        break;

    case dtkComposerNodeNumber::Float:
        emitter_f = new dtkComposerNodeTransmitter<float>();
        emitter_f->setData(value.toFloat());
        d->transmitter = emitter_f;
        break;

    case dtkComposerNodeNumber::Double:
        emitter_d = new dtkComposerNodeTransmitter<double>();
        emitter_d->setData(value.toDouble());
        d->transmitter = emitter_d;
        break;

    }
}

//! 
/*! 
 *  
 */
dtkComposerNodeNumber::Genre dtkComposerNodeNumber::compatibleType(const QString& left_type, const QString& right_type)
{


}

//! 
/*! 
 *  
 */
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

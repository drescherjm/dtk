/* dtkComposerNodeProperty.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:26:05 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Feb 24 10:12:27 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 257
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeProperty.h"

class dtkComposerNodePropertyPrivate
{
public:
    dtkComposerNode *parent;
    dtkComposerNode *clone;

    dtkComposerNodeProperty::Type type;
    dtkComposerNodeProperty::Multiplicity multiplicity;

    QGraphicsEllipseItem *ellipse;
    QGraphicsTextItem *text;

    bool displayed;
};

dtkComposerNodeProperty::dtkComposerNodeProperty(QString name, Type type, Multiplicity multiplicity, dtkComposerNode *parent) : QObject(), QGraphicsItem(parent), d(new dtkComposerNodePropertyPrivate)
{
    d->type = type;
    d->multiplicity = multiplicity;
    d->parent = parent;
    d->clone = NULL;

    d->displayed = true;

    d->text = new QGraphicsTextItem(this);
#if defined(Q_WS_MAC)
    d->text->setFont(QFont("Lucida Grande", 11));
#else
    d->text->setFont(QFont("Lucida Grande", 9));
#endif
    d->text->setPlainText(name);
    d->text->setDefaultTextColor(Qt::white);

    d->ellipse = new QGraphicsEllipseItem(this);
    d->ellipse->setPen(QPen(Qt::gray, 1));

    this->setZValue(20);
}

dtkComposerNodeProperty::~dtkComposerNodeProperty(void)
{
    qDebug() << "Deleting property" << this;

    delete d;

    d = NULL;
}

QString dtkComposerNodeProperty::description(void)
{
    QString property_type;

    switch(d->type) {
        
    case(dtkComposerNodeProperty::Input):
        property_type = "Input";
        break;
        
    case(dtkComposerNodeProperty::Output):
        property_type = "Output";
        break;

    default:
        property_type = "";
        break;
    }

    QString property_multiplicity;

    switch(d->multiplicity) {
        
    case(dtkComposerNodeProperty::Null):
        property_multiplicity = "Null";
        break;
        
    case(dtkComposerNodeProperty::Single):
        property_multiplicity = "Single";
        break;
        
    case(dtkComposerNodeProperty::Multiple):
        property_multiplicity = "Multiple";
        break;

    default:
        property_multiplicity = "";
        break;
    }

    if(d->clone)
        return QString("Property: name %1, parent %2, clone of %3, type %4, multiplicity %5, displayed %6")
            .arg(d->text->toPlainText())
            .arg(d->parent->description())
            .arg(d->clone->description())
            .arg(property_type)
            .arg(property_multiplicity)
            .arg(d->displayed);

    else
        return QString("Property: name %1, parent %2, no cloned, type %3, multiplicty %4, displayed %5")
            .arg(d->text->toPlainText())
            .arg(d->parent->description())
            .arg(property_type)
            .arg(property_multiplicity)
            .arg(d->displayed);
}

dtkComposerNodeProperty *dtkComposerNodeProperty::clone(dtkComposerNode *node)
{
    dtkComposerNodeProperty *property = new dtkComposerNodeProperty(d->text->toPlainText(), d->type, d->multiplicity, node);

    if(d->parent->kind() == dtkComposerNode::Composite)
        property->d->clone = d->clone;
    else
        property->d->clone = d->parent;

    property->d->displayed = false;

    if(node)
        property->hide();
    
    return property;
}

dtkComposerEdge *dtkComposerNodeProperty::edge(void)
{
    return d->parent->edge(this);
}

dtkComposerNode *dtkComposerNodeProperty::node(void)
{
    return d->parent;
}

QString dtkComposerNodeProperty::name(void) const
{
    return d->text->toPlainText();
}

dtkComposerNodeProperty::Type dtkComposerNodeProperty::type(void)
{
    return d->type;
}

int dtkComposerNodeProperty::count(void)
{
    return d->parent->count(this);
}

void dtkComposerNodeProperty::hide(void)
{
    QGraphicsItem::hide();
    
    d->displayed = false;

    d->parent->layout();
}

void dtkComposerNodeProperty::show(void)
{
    QGraphicsItem::show();

    d->displayed = true;

    d->parent->layout();
}

dtkComposerNode *dtkComposerNodeProperty::clonedFrom(void)
{
    return d->clone;
}

void dtkComposerNodeProperty::setClonedFrom(dtkComposerNode *node)
{
    d->clone = node;
}

bool dtkComposerNodeProperty::isDisplayed(void)
{
    return d->displayed;
}

//! Mark the property as displayed independently from whether it is currently visible or not.
/*! 
 *  A property can be displayed while not visible. This occurs when a
 *  node relies within a group. It's property is displayed but not
 *  currently visible if the scene shows a higher or deeper level of
 *  the composition.
 */
void dtkComposerNodeProperty::setDisplayed(bool displayed)
{
    d->displayed = displayed;
}

QRectF dtkComposerNodeProperty::boundingRect(void) const
{
    return d->ellipse->rect();
}

QRectF dtkComposerNodeProperty::rect(void) const
{
    return d->ellipse->rect();
}

void dtkComposerNodeProperty::setText(const QString& text)
{
    d->text->setPlainText(text);
}

void dtkComposerNodeProperty::setRect(const QRectF& rect)
{
    QFontMetrics fm(d->text->font());

    d->ellipse->setRect(rect);

    switch(d->type) {
    case Input:
        d->ellipse->setBrush(Qt::yellow);
        d->text->setPos(rect.topRight() + QPointF(0, (fm.height()/2-1)*-1));
        break;
    case Output:
        d->ellipse->setBrush(Qt::red);
        d->text->setPos(rect.topLeft() + QPointF(fm.width(d->text->toPlainText())*-1 - d->ellipse->rect().width(), (fm.height()/2-1)*-1));
        break;
    default:
        break;
    };
}

void dtkComposerNodeProperty::mirror(void)
{
    const QRectF& rect = this->rect();

    QFontMetrics fm(d->text->font());

    d->ellipse->setRect(rect);

    switch(d->type) {
    case Output:
        d->text->setPos(rect.topRight() + QPointF(0, (fm.height()/2-1)*-1));
        break;
    case Input:
        d->text->setPos(rect.topLeft() + QPointF(fm.width(d->text->toPlainText())*-1 - d->ellipse->rect().width(), (fm.height()/2-1)*-1));
        break;
    default:
        break;
    };
}

void dtkComposerNodeProperty::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

QDebug operator<<(QDebug dbg, dtkComposerNodeProperty  property)
{
    dbg.nospace() << property.description();

    return dbg.space();
}

QDebug operator<<(QDebug dbg, dtkComposerNodeProperty& property)
{
    dbg.nospace() << property.description();

    return dbg.space();
}

QDebug operator<<(QDebug dbg, dtkComposerNodeProperty *property)
{
    dbg.nospace() << property->description();

    return dbg.space();
}

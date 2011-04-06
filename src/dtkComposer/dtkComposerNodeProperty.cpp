/* dtkComposerNodeProperty.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:26:05 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr  5 17:19:12 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 409
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

#include <dtkCore/dtkGlobal.h>

class dtkComposerNodePropertyPrivate
{
public:
    dtkComposerNode *parent;
    dtkComposerNode *clone;

    dtkComposerNodeProperty::Type type;
    dtkComposerNodeProperty::Multiplicity multiplicity;
    dtkComposerNodeProperty::Behavior behavior;

    QGraphicsPathItem *path_left;
    QGraphicsPathItem *path_right;
    QGraphicsEllipseItem *ellipse;
    QGraphicsTextItem *text;

    bool displayed;

    QString block;
};

dtkComposerNodeProperty::dtkComposerNodeProperty(QString name, Type type, Multiplicity multiplicity, dtkComposerNode *parent) : QObject(), QGraphicsItem(parent), d(new dtkComposerNodePropertyPrivate)
{
    d->type = type;
    d->multiplicity = multiplicity;
    d->behavior = dtkComposerNodeProperty::None;
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

    switch(d->type) {
    case Input:
    case Output:
        d->ellipse = new QGraphicsEllipseItem(this);
        d->ellipse->setPen(QPen(Qt::gray, 1));
        d->path_left = NULL;
        d->path_right = NULL;
        break;
    case HybridInput:
    case HybridOutput:
        d->ellipse = NULL;
        d->path_left = new QGraphicsPathItem(this);
        d->path_left->setPen(QPen(Qt::gray, 1));
        d->path_right = new QGraphicsPathItem(this);
        d->path_right->setPen(QPen(Qt::gray, 1));
        break;
    default:
        break;
    };

    this->setZValue(20);
}

dtkComposerNodeProperty::~dtkComposerNodeProperty(void)
{
    d->parent = NULL;
    d->clone = NULL;

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

    case(dtkComposerNodeProperty::HybridInput):
        property_type = "HybridInput";
        break;

    case(dtkComposerNodeProperty::HybridOutput):
        property_type = "HybridInput";
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

    QString property_behavior;

    switch(d->behavior) {
        
    case(dtkComposerNodeProperty::None):
        property_behavior = "Node";
        break;
        
    case(dtkComposerNodeProperty::AsRelay):
        property_behavior = "AsRelay";
        break;
        
    case(dtkComposerNodeProperty::AsInput):
        property_behavior = "AsInput";
        break;
        
    case(dtkComposerNodeProperty::AsOutput):
        property_behavior = "AsOutput";
        break;

    default:
        property_behavior = "";
        break;
    }

    if(!d->parent)
        return QString("Invalid property");

    // if(d->clone)
    //     return QString("Property: name %1, parent %2, clone of %3, type %4, multiplicity %5, displayed %6")
    //         .arg(d->text->toPlainText())
    //         .arg(d->parent->description())
    //         .arg(d->clone->description())
    //         .arg(property_type)
    //         .arg(property_multiplicity)
    //         .arg(d->displayed);

    // else
        // return QString("Property: name %1, parent %2, no cloned, type %3, multiplicty %4, displayed %5")
        //     .arg(d->text->toPlainText())
        //     .arg(d->parent->description())
        //     .arg(property_type)
        //     .arg(property_multiplicity)
        //     .arg(d->displayed);

    return QString("Valid property %1").arg(d->text->toPlainText());
}

dtkComposerNodeProperty *dtkComposerNodeProperty::clone(dtkComposerNode *node)
{
    dtkComposerNodeProperty *property = new dtkComposerNodeProperty(d->text->toPlainText(), d->type, d->multiplicity, node);

    if(d->parent && d->parent->kind() == dtkComposerNode::Composite)
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
    if(!d->parent)
        return NULL;

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

dtkComposerNodeProperty::Multiplicity dtkComposerNodeProperty::multiplicity(void)
{
    return d->multiplicity;
}

dtkComposerNodeProperty::Behavior dtkComposerNodeProperty::behavior(void)
{
    return d->behavior;
}

bool dtkComposerNodeProperty::contains(const QPointF& point) const
{
    if (d->ellipse)
        return d->ellipse->contains(point);

    return d->path_right->contains(point);
}

int dtkComposerNodeProperty::count(void)
{
    if(!d->parent)
        return -1;

    return d->parent->count(this);
}

void dtkComposerNodeProperty::hide(void)
{
    QGraphicsItem::hide();
    
    d->displayed = false;

    if (d->parent)
        d->parent->layout();
}

void dtkComposerNodeProperty::show(void)
{
    QGraphicsItem::show();

    d->displayed = true;

    if (d->parent)
        d->parent->layout();
}

dtkComposerNode *dtkComposerNodeProperty::parent(void)
{
    return d->parent;
}

dtkComposerNode *dtkComposerNodeProperty::clonedFrom(void)
{
    return d->clone;
}

QString dtkComposerNodeProperty::blockedFrom(void) const
{
    return d->block;
}

void dtkComposerNodeProperty::setBlockedFrom(const QString& name)
{
    d->block = name;
}

void dtkComposerNodeProperty::setClonedFrom(dtkComposerNode *node)
{
    d->clone = node;
}

void dtkComposerNodeProperty::setParentNode(dtkComposerNode *node)
{
    d->parent = node;
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

void dtkComposerNodeProperty::setName(const QString& name)
{
    d->text->setPlainText(name);

    this->update();
}

void dtkComposerNodeProperty::setBehavior(dtkComposerNodeProperty::Behavior behavior)
{
    d->behavior = behavior;
}

QRectF dtkComposerNodeProperty::boundingRect(void) const
{
    if (d->ellipse)
        return d->ellipse->rect();

    return d->path_left->boundingRect().united(d->path_right->boundingRect());
}

QRectF dtkComposerNodeProperty::rect(void) const
{
    if (d->ellipse)
        return d->ellipse->rect();

    return d->path_left->boundingRect().united(d->path_right->boundingRect());
}

void dtkComposerNodeProperty::setText(const QString& text)
{
    d->text->setPlainText(text);
}

void dtkComposerNodeProperty::setRect(const QRectF& rect)
{
    QFontMetrics fm(d->text->font());

    QPainterPath lp; 
    QPainterPath rp; 

    switch(d->type) {
    case Input:
        d->ellipse->setRect(rect);
        d->ellipse->setBrush(Qt::yellow);
        if (d->parent->isGhost())
            d->text->setPos(rect.topRight() + QPointF(fm.width(d->text->toPlainText()) * (-1) - 3 * rect.width(), (fm.height()/2-1)*-1));
        else
            d->text->setPos(rect.topRight() + QPointF(0, (fm.height()/2-1)*-1));
        break;
    case Output:
        d->ellipse->setRect(rect);
        d->ellipse->setBrush(Qt::red);
        if (d->parent->isGhost())
            d->text->setPos(rect.topRight() + QPointF(rect.width(), (fm.height()/2-1)*-1));
        else
            d->text->setPos(rect.topLeft() + QPointF(fm.width(d->text->toPlainText()) * (-1) - rect.width(), (fm.height()/2-1)*-1));
        break;
    case HybridInput:
        lp.moveTo(rect.center()); lp.arcTo(rect, 90., 180.); lp.closeSubpath();
        d->path_left->setPath(lp);
        d->path_left->setBrush(Qt::yellow);
        rp.moveTo(rect.center()); rp.arcTo(rect, 270., 180.); rp.closeSubpath();
        d->path_right->setPath(rp);
        d->path_right->setBrush(Qt::red);
        d->text->setPos(rect.topRight() + QPointF(0, (fm.height()/2-1)*-1));
        break;
    case HybridOutput: 
        lp.moveTo(rect.center()); lp.arcTo(rect, 90., 180.); lp.closeSubpath();
        d->path_left->setPath(lp);
        d->path_left->setBrush(Qt::yellow);
        rp.moveTo(rect.center()); rp.arcTo(rect, 270., 180.); rp.closeSubpath();
        d->path_right->setPath(rp);
        d->path_right->setBrush(Qt::red);
        d->text->setPos(rect.topLeft() + QPointF(fm.width(d->text->toPlainText())*-1 - rect.width(), (fm.height()/2-1)*-1));
        break;
    default:
        break;
    };
}

void dtkComposerNodeProperty::mirror(void)
{
    const QRectF& rect = this->rect();

    QFontMetrics fm(d->text->font());

    switch(d->type) {
    case Output:
        d->text->setPos(rect.topRight() + QPointF(0, (fm.height()/2-1)*-1));
        break;
    case Input:
        d->text->setPos(rect.topLeft() + QPointF(fm.width(d->text->toPlainText())*-1 - rect.width(), (fm.height()/2-1)*-1));
        break;
    case HybridOutput:
        d->text->setPos(rect.topRight() + QPointF(0, (fm.height()/2-1)*-1));
        break;
    case HybridInput:
        d->text->setPos(rect.topLeft() + QPointF(fm.width(d->text->toPlainText())*-1 - rect.width(), (fm.height()/2-1)*-1));
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

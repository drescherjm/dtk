/* dtkComposerNodeProperty.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:26:05 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Dec  5 12:56:16 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 499
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

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

QGraphicsTextItem *dtkComposerNodePropertyElided(QGraphicsTextItem *item);

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeProperty
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePropertyPrivate
{
public:
    dtkComposerNode *parent;
    dtkComposerNode *clone;

    dtkComposerNodeProperty::Type type;
    dtkComposerNodeProperty::Position position;
    dtkComposerNodeProperty::Multiplicity multiplicity;
    dtkComposerNodeProperty::Behavior behavior;

    QGraphicsPathItem *path_left;
    QGraphicsPathItem *path_right;
    QGraphicsEllipseItem *ellipse;
    QGraphicsTextItem *text;

    bool displayed;

    QString block;
    QString name;
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
    d->name = name;
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
    case PassThroughInput:
    case PassThroughOutput:
        d->ellipse = NULL;
        d->path_left = new QGraphicsPathItem(this);
        d->path_left->setPen(QPen(Qt::black, 1));
        d->path_right = new QGraphicsPathItem(this);
        d->path_right->setPen(QPen(Qt::black, 1));
        break;
    default:
        break;
    };

    this->setZValue(20);
    
    Q_UNUSED (dtkComposerNodePropertyElided(d->text));
}

dtkComposerNodeProperty::dtkComposerNodeProperty(QString name, Position position, Behavior behavior, Multiplicity multiplicity, dtkComposerNode *parent) : QObject(), QGraphicsItem(parent), d(new dtkComposerNodePropertyPrivate)
{
    d->type = dtkComposerNodeProperty::Generic;
    d->position = position;
    d->behavior = behavior;
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

    d->name = name;

    switch(d->behavior) {
    case AsInput:
    case AsOutput:
        d->ellipse = new QGraphicsEllipseItem(this);
        d->ellipse->setPen(QPen(Qt::gray, 1));
        d->path_left = NULL;
        d->path_right = NULL;
        break;
    case AsRelay:
        d->ellipse = NULL;
        d->path_left = new QGraphicsPathItem(this);
        d->path_left->setPen(QPen(Qt::gray, 1));
        d->path_right = new QGraphicsPathItem(this);
        d->path_right->setPen(QPen(Qt::gray, 1));
        break;
    case AsLoop:
        d->ellipse = NULL;
        d->path_left = new QGraphicsPathItem(this);
        d->path_left->setPen(QPen(Qt::black, 1));
        d->path_right = new QGraphicsPathItem(this);
        d->path_right->setPen(QPen(Qt::black, 1));
        break;
    default:
        break;
    };

    this->setZValue(20);

    Q_UNUSED(dtkComposerNodePropertyElided(d->text));
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
    if(!d->parent)
        return QString("Invalid property");

    return QString("Valid property %1").arg(d->name);
}

dtkComposerNodeProperty *dtkComposerNodeProperty::clone(dtkComposerNode *node)
{
    QString name = d->name;
    name.append(" ");
    name.append(d->parent->title());

    dtkComposerNodeProperty *property = new dtkComposerNodeProperty(name, d->position, AsRelay, d->multiplicity, node);

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

    return d->parent->g->edge(this);
}

dtkComposerNode *dtkComposerNodeProperty::node(void)
{
    return d->parent;
}

QString dtkComposerNodeProperty::name(void) const
{
    return d->name;
}

dtkComposerNodeProperty::Type dtkComposerNodeProperty::type(void)
{
    return d->type;
}

dtkComposerNodeProperty::Position dtkComposerNodeProperty::position(void)
{
    return d->position;
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

    if (d->parent->kind() == dtkComposerNode::Composite) {
        if ((d->parent->isGhost() && d->position == Left) || 
            (!d->parent->isGhost() && d->position == Right))
            return d->path_right->contains(point);
        else 
            return false;
    }

    return d->path_right->contains(point);
}

int dtkComposerNodeProperty::count(void)
{
    if(!d->parent)
        return -1;

    return d->parent->g->edgeCount(this);
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

    d->name = name;

    Q_UNUSED(dtkComposerNodePropertyElided(d->text));

    this->update();
}

void dtkComposerNodeProperty::setType(dtkComposerNodeProperty::Type type)
{
    d->type = type;
}

void dtkComposerNodeProperty::setPosition(dtkComposerNodeProperty::Position position)
{
    d->position = position;
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

    Q_UNUSED(dtkComposerNodePropertyElided(d->text));
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
            d->text->setPos(rect.topRight() + QPointF(fm.width(d->text->toPlainText()) * (-1) - 3 * rect.width(), (fm.height() / 2. - 1) * (-1)));
        else
            d->text->setPos(rect.topRight() + QPointF(0, (fm.height() / 2. - 1) * (-1)));
        break;

    case Output:
        d->ellipse->setRect(rect);
        d->ellipse->setBrush(Qt::red);
        if (d->parent->isGhost())
            d->text->setPos(rect.topRight() + QPointF(rect.width(), (fm.height() / 2. - 1) * (-1)));
        else
            d->text->setPos(rect.topLeft() + QPointF(fm.width(d->text->toPlainText()) * (-1) - rect.width(), (fm.height() / 2. - 1) * (-1)));
        break;

    case HybridInput:
    case PassThroughInput:
        lp.moveTo(rect.center()); lp.arcTo(rect, 90., 180.); lp.closeSubpath();
        d->path_left->setPath(lp);
        d->path_left->setBrush(Qt::yellow);
        rp.moveTo(rect.center()); rp.arcTo(rect, 270., 180.); rp.closeSubpath();
        d->path_right->setPath(rp);
        d->path_right->setBrush(Qt::red);
        d->text->setPos(rect.topRight() + QPointF(0, (fm.height() / 2. - 1) * (-1)));
        break;

    case HybridOutput:
    case PassThroughOutput:
        lp.moveTo(rect.center()); lp.arcTo(rect, 90., 180.); lp.closeSubpath();
        d->path_left->setPath(lp);
        d->path_left->setBrush(Qt::yellow);
        rp.moveTo(rect.center()); rp.arcTo(rect, 270., 180.); rp.closeSubpath();
        d->path_right->setPath(rp);
        d->path_right->setBrush(Qt::red);
        d->text->setPos(rect.topLeft() + QPointF(fm.width(d->text->toPlainText()) * (-1) - rect.width(), (fm.height() / 2. - 1) * (-1)));
        break;

    case Generic:
        switch(d->behavior) {
        case AsInput:
            d->ellipse->setRect(rect);
            d->ellipse->setBrush(Qt::yellow);
            break;
        case AsOutput:
            d->ellipse->setRect(rect);
            d->ellipse->setBrush(Qt::red);
            break;
        case AsRelay:
        case AsLoop:
            lp.moveTo(rect.center()); lp.arcTo(rect, 90., 180.); lp.closeSubpath();
            d->path_left->setPath(lp);
            d->path_left->setBrush(Qt::yellow);
            rp.moveTo(rect.center()); rp.arcTo(rect, 270., 180.); rp.closeSubpath();
            d->path_right->setPath(rp);
            d->path_right->setBrush(Qt::red);
            break;
        default:
            break;
        };
    
        switch(d->position) {
        case Left:
            if (d->parent->isGhost()) {
                d->path_left->setBrush(Qt::lightGray);
                d->text->setPos(rect.topRight() + QPointF(fm.width(d->text->toPlainText()) * (-1) - 3 * rect.width(), (fm.height() / 2. - 1) * (-1)));
            } else {
                if (d->parent->kind() == dtkComposerNode::Composite)
                    d->path_right->setBrush(Qt::lightGray);
                d->text->setPos(rect.topRight() + QPointF(0, (fm.height() / 2. - 1) * (-1)));
            }
            break;
        case Right:
            if (d->parent->isGhost()) {
                d->path_right->setBrush(Qt::lightGray);
                d->text->setPos(rect.topRight() + QPointF(rect.width(), (fm.height() / 2. - 1) * (-1)));
            } else {
                if (d->parent->kind() == dtkComposerNode::Composite)
                    d->path_left->setBrush(Qt::lightGray);
                d->text->setPos(rect.topLeft() + QPointF(fm.width(d->text->toPlainText()) * (-1) - rect.width(), (fm.height() / 2. - 1) * (-1)));
            }
            break;
        default:
            break;
        };
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
    case PassThroughInput:
        d->text->setPos(rect.topRight() + QPointF(0, (fm.height()/2-1)*-1));
        break;
    case HybridInput:
    case PassThroughOutput:
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

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

QGraphicsTextItem *dtkComposerNodePropertyElided(QGraphicsTextItem *item)
{
    QFontMetricsF metrics(item->font());
    
    item->setPlainText(metrics.elidedText(item->toPlainText(), Qt::ElideMiddle, 50));

    return item;
}

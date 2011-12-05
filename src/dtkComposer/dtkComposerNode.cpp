/* dtkComposerNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:23 2009 (+0200)
 * Version: $Id$
<<<<<<< HEAD
 * Last-Updated: Mon Dec  5 13:10:52 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 2640
=======
 * Last-Updated: Mon Dec  5 12:54:09 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 2660
>>>>>>> 24384be6c876dbd7ed94b0db20bb45bcbc582a8f
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerEvaluator_p.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeLoop.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerScene.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkGlobal.h>

// #define DTK_DEBUG_COMPOSER_INTERACTION 1

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

QGraphicsTextItem *dtkComposerNodeElided(QGraphicsTextItem *item);

// /////////////////////////////////////////////////////////////////
// dtkComposerNodePrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePrivate
{
public:
    QRectF ghostRect(void);

public:
    dtkComposerNode *q;

    qreal penWidth;
    qreal header_height;
    qreal node_radius;
    qreal margin_left;
    qreal margin_right;
    qreal margin_top;
    qreal margin_bottom;

    QGraphicsTextItem *title;

    QString name;

    dtkComposerNodeProperty *clicked_property;

    dtkComposerNode::Attribute attribute;
    dtkComposerNode::Kind kind;

    QString type;

    dtkAbstractObject *object;

    QList<QAction *> actions;

    bool active;
    bool dirty;
    bool ghost;
    bool resizable;

          dtkComposerNode *  parent;
    QList<dtkComposerNode *> children;

    int count;

    QPointF ghost_position;
    QPointF non_ghost_position;

public:
    QPointF drag_point;
    QRectF bounding_rect;

    QColor pen_color;
    QPen pen;
};

QRectF dtkComposerNodePrivate::ghostRect(void)
{
    QRectF rect;

    foreach(dtkComposerNode *node, this->children)
        rect |= q->mapRectFromScene(node->sceneBoundingRect());

    rect.adjust(-75, -40, 75, 40);

    return rect;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNode
// /////////////////////////////////////////////////////////////////

dtkComposerNode::dtkComposerNode(dtkComposerNode *parent) : QObject(), QGraphicsItem(parent), d(new dtkComposerNodePrivate), g(new dtkComposerNodeGraphic(this)), l(new dtkComposerNodeLogic(this)) 
{
    d->count = 0; // TO BE REMOVED

    d->q = this;
    
    d->attribute = Sequential;
    d->kind = Unknown;
    d->object = NULL;
    d->parent = parent;

    d->penWidth = 1;
    d->header_height = 20;
    d->node_radius = 5;
    d->margin_left = 5;
    d->margin_right = 5;
    d->margin_top = 5;
    d->margin_bottom = 5;

    d->bounding_rect = QRectF(-75, -20, 150, 40);

    d->title = new QGraphicsTextItem(this);
#if defined(Q_WS_MAC)
    d->title->setFont(QFont("Lucida Grande", 13));
#else
    d->title->setFont(QFont("Lucida Grande", 11));
#endif
    d->title->setPlainText("Title");
    d->title->setDefaultTextColor(Qt::white);
    d->title->setPos(d->bounding_rect.topLeft());

    Q_UNUSED(dtkComposerNodeElided(d->title));

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    this->setZValue(10);

// #if QT_VERSION >= 0x040600
//     QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
//     shadow->setBlurRadius(5);
//     shadow->setOffset(3);
//     shadow->setColor(QColor(0, 0, 0, 127));
//     this->setGraphicsEffect(shadow);
// #endif

    d->clicked_property = NULL;

    d->active = false;
    d->dirty = true;
    d->ghost = false;
    d->resizable = false;

    d->pen_color = Qt::transparent;
}

dtkComposerNode::~dtkComposerNode(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    foreach(dtkComposerNodeProperty *property, g->leftProperties())
        property->setParentNode(NULL);

    foreach(dtkComposerNodeProperty *property, g->rightProperties())
        property->setParentNode(NULL);

    delete d;

    d = NULL;
}

QString dtkComposerNode::description(void)
{
    QString node_kind;

    switch (d->kind) {
        
    case(dtkComposerNode::Unknown):
        node_kind = "Unknown";
        break;

    case(dtkComposerNode::Atomic):
        node_kind = "Atomic";
        break;

    case(dtkComposerNode::Composite):
        node_kind = "Composite";
        break;

    case(dtkComposerNode::Control):
        node_kind = "Control";
        break;

    case(dtkComposerNode::Data):
        node_kind = "Data";
        break;

    case(dtkComposerNode::Process):
        node_kind = "Process";
        break;

    case(dtkComposerNode::View):
        node_kind = "View";
        break;

    default:
        node_kind = "";
        break;
    }

    return QString("Node: name %1, kind %2")
        .arg(d->title->toPlainText())
        .arg(node_kind);
}

void dtkComposerNode::setTitle(const QString& title)
{
    d->title->setPlainText(title);

    d->name = title;

    Q_UNUSED(dtkComposerNodeElided(d->title));
}

void dtkComposerNode::setAttribute(Attribute attribute)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->attribute = attribute;
}

void dtkComposerNode::setKind(Kind kind)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->kind = kind;
}

void dtkComposerNode::setType(QString type)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->type = type;
}

//! Sets the wrappee of the node
/*! A node is nothing more than a visual wrapper around a core concept
 *  of dtk, a subclass of dtkAbstractObject among dtkAbstractData,
 *  dtkAbstractProcess or dtkAbstractView.
 * 
 * This method allows to set this object up and performs the following
 * things:
 * - sets the title of the node to the one of the object
 * - checks wether the obejct has "hidden-input-properties" metadata,
 *   if so, should corresponding properties exist, they will be hidden
 *   regardless of their default state.
 * - checks wether the obejct has "hidden-output-properties" metadata,
 *   if so, should corresponding properties exist, they will be hidden
 *   regardless of their default state.
 * - checks wether the obejct has "shown-input-properties" metadata,
 *   if so, should corresponding properties exist, they will be shown
 *   regardless of their default state.
 * - checks wether the obejct has "shown-output-properties" metadata,
 *   if so, should corresponding properties exist, they will be shown
 *   regardless of their default state.
 */

void dtkComposerNode::setObject(dtkAbstractObject *object, bool update)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->object = object;

    if(!update)
        return;

    if(object->hasMetaData("hidden-input-properties"))
        foreach(QString property, object->metaDataValues("hidden-input-properties"))
            if(dtkComposerNodeProperty *p = this->g->leftProperty(property))
                p->hide();

    if(object->hasMetaData("hidden-output-properties"))
        foreach(QString property, object->metaDataValues("hidden-output-properties"))
            if(dtkComposerNodeProperty *p = this->g->rightProperty(property))
                p->hide();

    if(object->hasMetaData("shown-input-properties"))
        foreach(QString property, object->metaDataValues("shown-input-properties"))
            if(dtkComposerNodeProperty *p = this->g->leftProperty(property))
                p->show();

    if(object->hasMetaData("shown-output-properties"))
        foreach(QString property, object->metaDataValues("shown-output-properties"))
            if(dtkComposerNodeProperty *p = this->g->rightProperty(property))
                p->show();

    if (d->object) {
        d->title->setPlainText(object->name());

        d->name = object->name();
    }

    Q_UNUSED(dtkComposerNodeElided(d->title));
}

dtkComposerNode::Attribute dtkComposerNode::attribute(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    return d->attribute;
}

dtkComposerNode::Kind dtkComposerNode::kind(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    return d->kind;
}

QString dtkComposerNode::type(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    return d->type;
}

dtkAbstractObject *dtkComposerNode::object(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    return d->object;
}

void dtkComposerNode::addAction(const QString& text, const QObject *receiver, const char *slot)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    QAction *action = new QAction(text, this);

    connect(action, SIGNAL(triggered()), receiver, slot);

    d->actions << action;
}

QList<dtkComposerNode *> dtkComposerNode::inputNodes(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerEdge *edge, g->leftEdges())
        nodes << edge->source()->node();

    return nodes;
}

QList<dtkComposerNode *> dtkComposerNode::outputNodes(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerEdge *edge, g->rightEdges())
        nodes << edge->destination()->node();

    return nodes;
}

dtkComposerNodeProperty *dtkComposerNode::propertyAt(const QPointF& point) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, g->leftProperties())
        if (property->rect().contains(point))
            return property;

    foreach(dtkComposerNodeProperty *property, g->rightProperties())
        if (property->rect().contains(point))
            return property;
    
    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::leftProperty(const QString& name, dtkComposerNode *from) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, g->leftProperties())
        if (property->name() == name)
            // if (property->clonedFrom() == from)
                return property;
    
    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::rightProperty(const QString& name, dtkComposerNode *from) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, g->rightProperties())
        if (property->name() == name)
            // if (property->clonedFrom() == from)
                return property;

    return NULL;
}

QString dtkComposerNode::title(void)
{
    return QString(d->name);
}

bool dtkComposerNode::dirty(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    return d->dirty;
}

void dtkComposerNode::setDirty(bool dirty)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->dirty = dirty;

    // if (d->kind == dtkComposerNode::Composite) {
    //     if (d->dirty) {
    //         foreach(dtkComposerNode *child, d->children)
    //             if(!child->g->leftEdges().count() && child->g->rightEdges().count())
    //                 child->setDirty(dirty);
    //         foreach(dtkComposerEdge *ghost_edge, d->ghost_input_edges.keys())
    //             ghost_edge->destination()->node()->setDirty(dirty);
    //     } else {
    //         foreach(dtkComposerNode *child, d->children)
    //             child->setDirty(dirty);
    //     }
    // }
}

bool dtkComposerNode::resizable(void)
{
    return d->resizable;
}

void dtkComposerNode::setResizable(bool resizable)
{
    d->resizable = resizable;
}

void dtkComposerNode::layout(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if (d->ghost) {

        d->title->setPos(d->ghostRect().topLeft());
    
    } else if (d->kind == dtkComposerNode::Control) {

#if defined(Q_WS_MAC)
        QFont font("Lucida Grande", 13);
#else
        QFont font("Lucida Grande", 11);
#endif
        QFontMetrics metrics(font);
        
        d->title->setPos(d->bounding_rect.topRight() + QPointF(-metrics.width(d->title->toPlainText()) - 2*d->margin_right, 0));

    } else  {
        d->title->setPos(d->bounding_rect.topLeft());
    }

    if (d->kind == Control)
        return;

    int exposed_input_properties = 0;

    foreach(dtkComposerNodeProperty *property, g->leftProperties())
        if (property->isDisplayed())
            if (d->ghost)
                property->setRect(QRectF(d->ghostRect().left() + d->node_radius, d->ghostRect().top() + 40 + (4 * (exposed_input_properties++) + 1) * d->node_radius - d->node_radius, d->node_radius * 2, d->node_radius * 2));
            else
                property->setRect(QRectF(d->bounding_rect.left() + d->node_radius, d->margin_top + (3 * (exposed_input_properties++) + 1) * d->node_radius - d->node_radius, d->node_radius * 2, d->node_radius * 2));

    int exposed_output_properties = 0;

    foreach(dtkComposerNodeProperty *property, g->rightProperties())
        if (property->isDisplayed())
            if (d->ghost)
                property->setRect(QRectF(d->ghostRect().right() - 3 * d->node_radius, d->ghostRect().top() + 40 + (4 * (exposed_output_properties++) + 1) * d->node_radius - d->node_radius, d->node_radius * 2, d->node_radius * 2));
            else
                property->setRect(QRectF(d->bounding_rect.right() - 3 * d->node_radius, d->margin_top + (3 * (exposed_output_properties++) + 1) * d->node_radius - d->node_radius, d->node_radius * 2, d->node_radius * 2));
    
    d->bounding_rect.setHeight(d->header_height + (3*qMax(exposed_input_properties, exposed_output_properties)) * d->node_radius + d->margin_bottom);
}

void dtkComposerNode::setParentNode(dtkComposerNode *node)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    d->parent = node;
}

void dtkComposerNode::addChildNode(dtkComposerNode *node)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if(!d->children.contains(node))
        d->children << node;
}

void dtkComposerNode::removeChildNode(dtkComposerNode *node)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if (d->children.contains(node))
        d->children.removeAll(node);
}

QList<dtkComposerNode *> dtkComposerNode::childNodes(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    return d->children;
}

dtkComposerNode *dtkComposerNode::parentNode(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    return d->parent;
}

bool dtkComposerNode::isChildOf(dtkComposerNode *node)
{
    if (this == node)
        return true;

    dtkComposerNode *p = d->parent;

    while (p)
        if (p == node)
            return true;
        else
            p = p->d->parent;
    
    return false;
}

bool dtkComposerNode::isChildOfControlNode(dtkComposerNode *node)
{
    dtkComposerNode *p = d->parent;

    while (p)
        if (p->kind() == dtkComposerNode::Control)
            return (p == node);
        else
            p = p->d->parent;

    return false;
}

void dtkComposerNode::setGhost(bool ghost)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->ghost = ghost;

    if (d->ghost) {

        if (d->parent && d->parent->kind() == dtkComposerNode::Control)
            this->setParentItem(NULL);

        this->setZValue(-10000);

        foreach(dtkComposerNode *node, d->children)
            node->setParentItem(this);

    } else {  

        if (d->parent && d->parent->kind() == dtkComposerNode::Control) {            
            foreach(dtkComposerNodeControlBlock *block, (dynamic_cast<dtkComposerNodeControl *>(d->parent))->blocks())
                if (block->nodes().contains(this))
                    this->setParentItem(block);
        }        

        this->setZValue(10);

        foreach(dtkComposerNode *node, d->children)
            node->setParentItem(NULL);
    }

    this->layout();
}

bool dtkComposerNode::isGhost(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    return d->ghost;
}

void dtkComposerNode::setGhostPosition(QPointF pos)
{
    d->ghost_position = pos;
}

QPointF dtkComposerNode::ghostPosition(void)
{
    return d->ghost_position;
}

void dtkComposerNode::setNonGhostPosition(QPointF pos)
{
    d->non_ghost_position = pos;
}

QPointF dtkComposerNode::nonGhostPosition(void)
{
    return d->non_ghost_position;
}

void dtkComposerNode::setSize(const QSizeF& size)
{
    d->bounding_rect.setHeight(size.height());
    d->bounding_rect.setWidth(size.width());
    
    QGraphicsItem::update();
}

void dtkComposerNode::setSize(qreal w, qreal h)
{
    d->bounding_rect.setHeight(h);
    d->bounding_rect.setWidth(w);

    QGraphicsItem::update();
}

// void dtkComposerNode::alter(void)
// {
// #if defined(DTK_DEBUG_COMPOSER_INTERACTION)
//     qDebug() << DTK_PRETTY_FUNCTION << this;
// #endif

//     if (dtkComposerScene *scene = dynamic_cast<dtkComposerScene *>(this->scene())) {
//         scene->stopEvaluation();
//         scene->clearSelection();
//         this->setSelected(true);
//         scene->startEvaluation();
//     }
// }

//! Ask the node to redraw itself
/*! 
 * 
 */
void dtkComposerNode::touch(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    QGraphicsItem::update(this->boundingRect());
    
    if (this->scene()->views().count())
        this->scene()->views().first()->update();
}

//! Node delegates its own evaluation to the evaluator according to
//! Visitor Design Pattern.
/*! 
 * 
 */
bool dtkComposerNode::evaluate(dtkComposerEvaluatorPrivate *evaluator)
{
    return evaluator->evaluate(this);
}

QRectF dtkComposerNode::boundingRect(void) const
{
    if (d->ghost)
        return d->ghostRect();
    else
        return d->bounding_rect;
}

void dtkComposerNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    Q_UNUSED(option);
    Q_UNUSED(widget);

    if ((d->kind == Composite) || (d->kind == Control))
        this->layout();

    QRectF rect = this->boundingRect();

    QLinearGradient gradiant(rect.left(), rect.top(), rect.left(), rect.bottom());

    switch (d->kind) {
    case Unknown:
        gradiant.setColorAt(0.0, QColor(Qt::white));
        gradiant.setColorAt(0.3, QColor(Qt::gray));
        gradiant.setColorAt(1.0, QColor(Qt::gray).darker());
        break;
    case Atomic:
        gradiant.setColorAt(0.0, QColor(Qt::white));
        gradiant.setColorAt(0.3, QColor("#ffa500"));
        gradiant.setColorAt(1.0, QColor("#ffa500").darker());
        break;
    case Composite:
        if (!d->ghost) {
            gradiant.setColorAt(0.0, QColor("#515151"));
            gradiant.setColorAt(1.0, QColor("#000000"));
        }
        break;
    case Data:
        gradiant.setColorAt(0.0, QColor(Qt::white));
        gradiant.setColorAt(0.3, QColor(Qt::blue));
        gradiant.setColorAt(1.0, QColor(Qt::blue).darker());
        break;
    case Process:
        gradiant.setColorAt(0.0, QColor(Qt::white));
        gradiant.setColorAt(0.3, QColor(Qt::red));
        gradiant.setColorAt(1.0, QColor(Qt::red).darker());
        break;
    case View:
        gradiant.setColorAt(0.0, QColor(Qt::white));
        gradiant.setColorAt(0.3, QColor(Qt::green));
        gradiant.setColorAt(1.0, QColor(Qt::green).darker());
        break;
    case Control:
    default:
        break;
    }

    if (this->isSelected()) {
        if (this->isGhost() && this->kind() == dtkComposerNode::Composite)
            this->setPen(Qt::magenta, Qt::DashLine, 3);
        else
            this->setPen(Qt::magenta, Qt::SolidLine, 2);
    } else {
        if (this->isGhost() && this->kind() == dtkComposerNode::Composite)
            this->setPen(QColor("#cccccc"), Qt::DashLine, 3);
        else if (this->kind() == dtkComposerNode::Control)
            this->setPen(QColor("#c7c7c7"), Qt::SolidLine, 1);
        else
            this->setPen(Qt::black, Qt::SolidLine, 1);
    }
    painter->setPen(d->pen);

    d->pen_color = Qt::transparent;

    if (this->kind() == dtkComposerNode::Control) {
        painter->setBrush(Qt::NoBrush);
    } else if (this->isGhost() && this->kind() == dtkComposerNode::Composite) {
        painter->setBrush(Qt::NoBrush);        
    } else {
        painter->setBrush(gradiant);
    }

    painter->drawRoundedRect(rect, d->node_radius, d->node_radius);

    // Draw attribute visual couterpart

    if(d->attribute == dtkComposerNode::Parallel) {

        int p_d = 10;
        int p_w = 10;
        int p_h = 10;

        QPolygon t_rubber = QPolygon() << QPoint(rect.bottomRight().x() - 2*p_w - 2* p_d, rect.bottomRight().y())
                                       << QPoint(rect.bottomRight().x() - 1*p_w - 2* p_d, rect.bottomRight().y())
                                       << QPoint(rect.bottomRight().x(), rect.bottomRight().y() - 1*p_h - 2* p_d)
                                       << QPoint(rect.bottomRight().x(), rect.bottomRight().y() - 2*p_h - 2* p_d);
        QPolygon b_rubber = QPolygon() << QPoint(rect.bottomRight().x() - 1*p_w - 1* p_d, rect.bottomRight().y())
                                       << QPoint(rect.bottomRight().x() - 0*p_w - 1* p_d, rect.bottomRight().y())
                                       << QPoint(rect.bottomRight().x(), rect.bottomRight().y() - 0*p_h - 1* p_d)
                                       << QPoint(rect.bottomRight().x(), rect.bottomRight().y() - 1*p_h - 1* p_d);

        painter->setPen(QPen(Qt::darkGray, 1));
        painter->setBrush(Qt::black);
        painter->drawPolygon(t_rubber);
        painter->drawPolygon(b_rubber);
    }

    // Drawing size grip

    if (d->resizable) {

        QPainterPath path;
        path.moveTo(this->boundingRect().bottomRight() + QPointF(0.5, 0.5));
        path.lineTo(this->boundingRect().bottomRight() + QPointF(0.5, 0.5) + QPointF(-15, 0));
        path.lineTo(this->boundingRect().bottomRight() + QPointF(0.5, 0.5) + QPointF(0, -15));
        path.lineTo(this->boundingRect().bottomRight() + QPointF(0.5, 0.5));
        
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor("#c7c7c7"));
        painter->drawPath(path);
    }
}

void dtkComposerNode::highlight(bool ok)
{
    if (ok) {

        QPropertyAnimation *animation = new QPropertyAnimation(this, "penColor");
        animation->setDuration(300);
        animation->setKeyValueAt(0.0, Qt::green);
        animation->setKeyValueAt(1.0, Qt::magenta);
        animation->setEasingCurve(QEasingCurve::Linear);
        animation->start(QAbstractAnimation::DeleteWhenStopped);

    } else {

        QPropertyAnimation *animation = new QPropertyAnimation(this, "penColor");
        animation->setDuration(300);
        animation->setKeyValueAt(0.0, Qt::red);
        animation->setKeyValueAt(1.0, Qt::magenta);
        animation->setEasingCurve(QEasingCurve::Linear);
        animation->start(QAbstractAnimation::DeleteWhenStopped);

    }
}

QColor dtkComposerNode::penColor(void) const
{
    return d->pen_color;
}

QPen dtkComposerNode::pen(void) const
{
    return d->pen;
}

void dtkComposerNode::setPenColor(const QColor& color)
{
    d->pen_color = color;

    this->touch();
}

void dtkComposerNode::setPen(const QColor& color, const Qt::PenStyle& style, const qreal& width)
{
    if (d->pen_color == Qt::transparent)
        d->pen.setColor(color);
    else
        d->pen.setColor(d->pen_color);

    d->pen.setStyle(style);
    d->pen.setWidth(width);
}

qreal dtkComposerNode::nodeRadius(void)
{
    return d->node_radius;
}

void dtkComposerNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if (event->buttons() & Qt::LeftButton && !d->drag_point.isNull()) { 

        if (dtkComposerNodeControl *control = dynamic_cast<dtkComposerNodeControl *>(this)) {

            QPointF br = this->mapRectToScene(this->boundingRect()).bottomRight();
            QRectF corner(br.x() - 23, br.y() - 23, 23, 23);

            QPointF delta;

            if (!corner.contains(event->lastScenePos()))
                delta = QPointF(0, 0);
            else
                delta = QPointF(event->scenePos() - d->drag_point);

            if (delta.x() * delta.x() + delta.y() * delta.y() >= 1) {

                control->resize(delta);
                d->drag_point = event->scenePos();
                event->accept();            
                QGraphicsItem::update();

            } else {

                d->drag_point = this->mapRectToScene(this->boundingRect()).bottomRight();
                event->accept();          
                QGraphicsItem::update();

            }
        }

        return;
    }

    if (!d->clicked_property)
        QGraphicsItem::mouseMoveEvent(event);

    foreach(dtkComposerEdge *edge, g->leftEdges())
	edge->adjust();

    foreach(dtkComposerEdge *edge, g->rightEdges())
	edge->adjust();

    foreach(dtkComposerEdge *edge, g->leftRelayEdges())
	edge->adjust();

    foreach(dtkComposerEdge *edge, g->rightRelayEdges())
	edge->adjust();
}

void dtkComposerNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    // -- Handling of properties

    d->clicked_property = this->propertyAt(event->pos());

    if (d->clicked_property)
        return;

    // -- Handling of menus

    if (event->button() == Qt::RightButton) {
        QMenu menu;
        
        foreach(QAction *action, d->actions)
            menu.addAction(action);

        menu.exec(QCursor::pos());

        QGraphicsItem::mousePressEvent(event);

        return;
    }

    // -- Handling of resizing

    QPointF br = this->mapRectToScene(this->boundingRect()).bottomRight();

    QRectF corner(br.x() - 23, br.y() - 23, 23, 23);

    if (d->kind == Control && event->button() & Qt::LeftButton && corner.contains(event->scenePos())) {

        //d->drag_point = event->scenePos();
        d->drag_point = this->mapRectToScene(this->boundingRect()).bottomRight();

        event->accept();

        QGraphicsItem::mousePressEvent(event);
        
        return;
    }

    QGraphicsItem::mousePressEvent(event);
}

void dtkComposerNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if (event->button() & Qt::LeftButton && !d->drag_point.isNull()) {
        d->drag_point = QPointF(0, 0);
        event->accept();

        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    QGraphicsItem::mouseReleaseEvent(event);

    if (!d->clicked_property)
        QGraphicsItem::mouseReleaseEvent(event);

    d->clicked_property = NULL;
}

QList<dtkComposerEdge *> dtkComposerNode::allRoutes(void)
{
    QList<dtkComposerEdge *> routes;
    routes << l->leftRoutes();
    routes << l->rightRoutes();

    return routes;
}

void dtkComposerNode::removeRoute(dtkComposerEdge *route)
{
    l->removeLeftRoute(route);
    l->removeRightRoute(route);
}
    
QVariant dtkComposerNode::value(dtkComposerNodeProperty *property)
{
    DTK_UNUSED(property);

    DTK_DEFAULT_IMPLEMENTATION;

    return QVariant();
}
    
void dtkComposerNode::chooseImplementation(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkComposerNode::setupImplementation(QString implementation)
{
    DTK_UNUSED(implementation);

    DTK_DEFAULT_IMPLEMENTATION;
}

bool dtkComposerNode::dirtyUpstreamNodes(void)
{
    foreach(dtkComposerNode *up_node, this->l->leftNodes())
        if (up_node->dirty())
            return true;

    return false;


    // foreach(dtkComposerEdge *i_route, l->leftRoutes()) {

    //     if(dtkComposerNodeLoop *loop = dynamic_cast<dtkComposerNodeLoop *>(i_route->source()->node())) {

    //         if(this->isChildOf(loop)) {

    //             continue;

    //             // if(loop->isRunning())
    //             //     continue;
    //             // else {
    //             //     qDebug() << DTK_PRETTY_FUNCTION;
    //             //     return true;
    //             // }

    //         } else {

    //             if (i_route->source()->node()->dirty()) {
    //                 return true;
    //             }
    //         }

    //     } else {

    //         if (i_route->source()->node()->dirty()) {
    //             return true;
    //         }
    //     }
    // }
    // return false;
}

void dtkComposerNode::markDirtyDownstreamNodes(void)
{
    foreach(dtkComposerNode *down_node, this->l->rightNodes())
        down_node->setDirty(true);

    // foreach(dtkComposerEdge *o_route, l->rightRoutes())
    //     o_route->destination()->node()->setDirty(true);
}

void dtkComposerNode::pull(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);

    DTK_DEFAULT_IMPLEMENTATION;    
}

void dtkComposerNode::run(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkComposerNode::push(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);

    DTK_DEFAULT_IMPLEMENTATION;    
}

dtkComposerNodeAbstractTransmitter *dtkComposerNode::emitter(dtkComposerNodeProperty *property)
{
    DTK_UNUSED(property);

    DTK_DEFAULT_IMPLEMENTATION;
    return NULL;
}

bool dtkComposerNode::onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination)
{
    DTK_UNUSED(route);
    DTK_UNUSED(destination);

    return false;
}

bool dtkComposerNode::onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    DTK_UNUSED(route);
    DTK_UNUSED(property);

    return true;
}

void dtkComposerNode::updateSourceRoutes(dtkComposerEdge *route)
{
    this->l->appendLeftRoute(route);
}

void dtkComposerNode::updateDestinationRoutes(dtkComposerEdge *route)
{
    this->l->appendRightRoute(route);
}

void dtkComposerNode::updateSourceNodes(dtkComposerEdge *route)
{
    this->l->appendLeftNode(route->source()->node());
}

void dtkComposerNode::updateDestinationNodes(dtkComposerEdge *route)
{
    this->l->appendRightNode(route->destination()->node());
}

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

QDebug operator<<(QDebug dbg, dtkComposerNode node)
{
    dbg.nospace() << node.description();
    
    return dbg.space();
}

QDebug operator<<(QDebug dbg, dtkComposerNode& node)
{
    dbg.nospace() << node.description();
    
    return dbg.space();
}

QDebug operator<<(QDebug dbg, dtkComposerNode *node)
{
    dbg.nospace() << node->description();
    
    return dbg.space();
}

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

QGraphicsTextItem *dtkComposerNodeElided(QGraphicsTextItem *item)
{
    QFontMetricsF metrics(item->font());
    
    item->setPlainText(metrics.elidedText(item->toPlainText(), Qt::ElideMiddle, 130));

    return item;
}

/* dtkComposerNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:23 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Mar  1 19:09:19 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 1615
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
#include "dtkComposerScene.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkGlobal.h>

// #define DTK_DEBUG_COMPOSER_INTERACTION 1
// #define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerNodePrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePrivate
{
public:
    QRectF ghostRect(void);

    QList<dtkComposerEdge *> iRoute(dtkComposerEdge *edge);
    QList<dtkComposerEdge *> oRoute(dtkComposerEdge *edge);

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

    QList<dtkComposerNodeProperty *> input_properties;
    QList<dtkComposerNodeProperty *> output_properties;

    QHash<dtkComposerEdge *, dtkComposerNodeProperty *> input_edges;
    QHash<dtkComposerEdge *, dtkComposerNodeProperty *> output_edges;

    QHash<dtkComposerEdge *, dtkComposerNodeProperty *> ghost_input_edges;
    QHash<dtkComposerEdge *, dtkComposerNodeProperty *> ghost_output_edges;

    dtkComposerNodeProperty *clicked_property;

    dtkComposerNode::Kind kind;

    QString type;

    dtkAbstractObject *object;

    QList<QAction *> actions;

    bool dirty;    
    bool ghost;
    bool resizable;

          dtkComposerNode *  parent;
    QList<dtkComposerNode *> children;

    int count;

    QPointF drag_point;

    QRectF bounding_rect;
};

QRectF dtkComposerNodePrivate::ghostRect(void)
{
    QRectF rect;

    foreach(dtkComposerNode *node, this->children)
        rect |= q->mapRectFromScene(node->sceneBoundingRect());

    rect.adjust(-75, -40, 75, 40);

    return rect;
}

QList<dtkComposerEdge *> dtkComposerNodePrivate::iRoute(dtkComposerEdge *edge)
{
    QList<dtkComposerEdge *> edges;

    if(edge->source()->node()->kind() != dtkComposerNode::Composite) {

        // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->source()->node()->title() << "is not composite" << DTK_NO_COLOR;

        edges << edge;

    } else {

        if(edge->source()->node() == edge->destination()->node()->parentNode()) {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->source()->node()->title() << "parent is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *i_edge, edge->source()->node()->inputEdges())
                if(i_edge->destination() == edge->source())
                    edges << iRoute(i_edge);
        } else {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->source()->node()->title() << "source is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *ghost, edge->source()->node()->outputGhostEdges())
                if(ghost->destination() == edge->source())
                    edges << iRoute(ghost);
        }
    }

    return edges;
}

QList<dtkComposerEdge *> dtkComposerNodePrivate::oRoute(dtkComposerEdge *edge)
{
    QList<dtkComposerEdge *> edges;

    if(edge->destination()->node()->kind() != dtkComposerNode::Composite) {

        // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->destination()->node()->title() << "is not composite" << DTK_NO_COLOR;

        edges << edge;

    } else {

        if(edge->destination()->node() == edge->source()->node()->parentNode()) {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->destination()->node()->title() << "parent is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *o_edge, edge->destination()->node()->outputEdges())
                if(o_edge->source() == edge->destination())
                    edges << oRoute(o_edge);

        } else {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->destination()->node()->title() << "destination is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *ghost, edge->destination()->node()->inputGhostEdges())
                if(ghost->source() == edge->destination())
                    edges << oRoute(ghost);

        }
    }

    return edges;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNode
// /////////////////////////////////////////////////////////////////

dtkComposerNode::dtkComposerNode(dtkComposerNode *parent) : QObject(), QGraphicsItem(parent), d(new dtkComposerNodePrivate)
{
    d->count = 0; // TO BE REMOVED

    d->q = this;
    
    d->kind = Unknown;
    d->object = NULL;
    d->parent = NULL;

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

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    this->setZValue(10);

#if QT_VERSION >= 0x040600
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(5);
    shadow->setOffset(3);
    shadow->setColor(QColor(0, 0, 0, 127));
    this->setGraphicsEffect(shadow);
#endif

    d->clicked_property = NULL;

    d->dirty = true;
    d->ghost = false;
    d->resizable = false;
}

dtkComposerNode::~dtkComposerNode(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    // if (this->scene() && this->scene()->items().contains(this))
    //     this->scene()->removeItem(this);

    foreach(dtkComposerNodeProperty *property, d->input_properties)
        property->setParentNode(NULL);

    foreach(dtkComposerNodeProperty *property, d->output_properties)
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

void dtkComposerNode::setObject(dtkAbstractObject *object)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->object = object;

    d->title->setHtml(object->name());
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

dtkComposerEdge *dtkComposerNode::edge(dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if(this->kind() != dtkComposerNode::Composite) {

        if(property->type() == dtkComposerNodeProperty::Input)
            return d->input_edges.key(property);
        
        if(property->type() == dtkComposerNodeProperty::Output)
            return d->output_edges.key(property);

    } else {

        if(property->type() == dtkComposerNodeProperty::Input) {
            if(this->isGhost())            
                return d->ghost_input_edges.key(property);
            else
                return d->input_edges.key(property);
        }

        if(property->type() == dtkComposerNodeProperty::Output) {
            if(this->isGhost())
                return d->ghost_output_edges.key(property);
            else 
                return d->output_edges.key(property);
        }
    }
        
    return NULL;
}

void dtkComposerNode::addInputProperty(dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->input_properties << property;

    this->layout();
}

void dtkComposerNode::addOutputProperty(dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->output_properties << property;

    this->layout();
}

void dtkComposerNode::removeInputProperty(dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->input_properties.removeAll(property);
}

void dtkComposerNode::removeOutputProperty(dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->output_properties.removeAll(property);
}

void dtkComposerNode::addInputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->input_edges.insert(edge, property);
}

void dtkComposerNode::addOutputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    d->output_edges.insert(edge, property);
}

void dtkComposerNode::addGhostInputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->ghost_input_edges.insert(edge, property);
}

void dtkComposerNode::addGhostOutputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->ghost_output_edges.insert(edge, property);
}

void dtkComposerNode::removeInputEdge(dtkComposerEdge *edge)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->input_edges.remove(edge);
}

void dtkComposerNode::removeOutputEdge(dtkComposerEdge *edge)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->output_edges.remove(edge);
}

void dtkComposerNode::removeAllEdges(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->input_edges.clear();
    d->output_edges.clear();
}

void dtkComposerNode::removeGhostInputEdge(dtkComposerEdge *edge)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->ghost_input_edges.remove(edge);
}

void dtkComposerNode::removeGhostOutputEdge(dtkComposerEdge *edge)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->ghost_output_edges.remove(edge);
}

void dtkComposerNode::removeAllGhostEdges(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->ghost_input_edges.clear();
    d->ghost_output_edges.clear();
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

int dtkComposerNode::count(dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    if(property->type() == dtkComposerNodeProperty::Input)
        return d->input_edges.keys(property).count();

    if(property->type() == dtkComposerNodeProperty::Output)
        return d->output_edges.keys(property).count();

    return 0;
}

int dtkComposerNode::number(dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    if(property->type() == dtkComposerNodeProperty::Input)
        return d->input_properties.indexOf(property);

    if(property->type() == dtkComposerNodeProperty::Output)
        return d->output_properties.indexOf(property);

    return -1;
}

QList<dtkComposerNodeProperty *> dtkComposerNode::inputProperties(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    return d->input_properties;
}

QList<dtkComposerNodeProperty *> dtkComposerNode::outputProperties(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    return d->output_properties;
}

QList<dtkComposerEdge *> dtkComposerNode::inputEdges(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    return d->input_edges.keys();
}

QList<dtkComposerEdge *> dtkComposerNode::outputEdges(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    return d->output_edges.keys();
}

QList<dtkComposerEdge *> dtkComposerNode::inputGhostEdges(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    return d->ghost_input_edges.keys();
}

QList<dtkComposerEdge *> dtkComposerNode::outputGhostEdges(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    return d->ghost_output_edges.keys();
}

QList<dtkComposerNode *> dtkComposerNode::inputNodes(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerEdge *edge, d->input_edges.keys())
        nodes << edge->source()->node();

    return nodes;
}

QList<dtkComposerNode *> dtkComposerNode::outputNodes(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerEdge *edge, d->output_edges.keys())
        nodes << edge->destination()->node();

    return nodes;
}

dtkComposerNodeProperty *dtkComposerNode::propertyAt(const QPointF& point) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, d->input_properties)
        if(property->rect().contains(point))
            return property;

    foreach(dtkComposerNodeProperty *property, d->output_properties)
        if(property->rect().contains(point))
            return property;
    
    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::inputProperty(const QString& name) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, d->input_properties)
        if(property->name() == name)
            return property;
    
    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::inputProperty(const QString& name, dtkComposerNode *from) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, d->input_properties)
        if(property->name() == name)
            if(property->clonedFrom() == from)
                return property;
    
    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::outputProperty(const QString& name) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, d->output_properties)
        if(property->name() == name)
            return property;

    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::outputProperty(const QString& name, dtkComposerNode *from) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, d->output_properties)
        if(property->name() == name)
            if(property->clonedFrom() == from)
                return property;

    return NULL;
}

QString dtkComposerNode::title(void)
{
    return QString(d->title->toPlainText());
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
    
    } else if(d->kind == dtkComposerNode::Control) {

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

    if(d->kind == Control)
        return;

    int exposed_input_properties = 0;

    foreach(dtkComposerNodeProperty *property, d->input_properties)
        if(property->isDisplayed())
            if(d->ghost)
                property->setRect(QRectF(d->ghostRect().left()+d->node_radius, d->ghostRect().top() + 40 + (3*(exposed_input_properties++) + 1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));
            else
                property->setRect(QRectF(d->bounding_rect.left()+d->node_radius, d->margin_top+(3*(exposed_input_properties++) + 1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));

    int exposed_output_properties = 0;

    foreach(dtkComposerNodeProperty *property, d->output_properties)
        if(property->isDisplayed())
            if(d->ghost)
                property->setRect(QRectF(d->ghostRect().right() - 3*d->node_radius, d->ghostRect().top() + 40 + (3*(exposed_output_properties++) + 1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));
            else
                property->setRect(QRectF(d->bounding_rect.right()-3*d->node_radius, d->margin_top+(3*(exposed_output_properties++) + 1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));
    
    d->bounding_rect.setHeight(d->header_height + (3*qMax(exposed_input_properties, exposed_output_properties)) * d->node_radius + d->margin_bottom);
}

void dtkComposerNode::setParentNode(dtkComposerNode *node)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    d->parent = node;

    QObject::setParent(node);
}

void dtkComposerNode::addChildNode(dtkComposerNode *node)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if(!d->children.contains(node))
        d->children << node;

    if(d->ghost)
        node->setParentItem(this);
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

void dtkComposerNode::setGhost(bool ghost)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->ghost = ghost;

    if(d->ghost) {

        this->setZValue(0);

        foreach(dtkComposerNode *node, d->children)
            node->setParentItem(this);

    } else {

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

void dtkComposerNode::alter(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if(dtkComposerScene *scene = dynamic_cast<dtkComposerScene *>(this->scene())) {
        scene->stopEvaluation();
        scene->clearSelection();
        this->setSelected(true);
        scene->startEvaluation();
    }
}

//! Ask the node to redraw itself
/*! 
 * 
 */
void dtkComposerNode::touch(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    // QGraphicsItem::update(this->boundingRect());
}

//! 
/*! 
 * 
 */
void dtkComposerNode::update(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if(!dtkComposerScene::s_evaluate)
        return;

    if(d->kind == dtkComposerNode::Process && !d->dirty)
        return;

    QList<dtkComposerEdge *> input_edges = d->input_edges.keys();
    QList<dtkComposerEdge *> output_edges = d->output_edges.keys();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_COLOR_BG_GREEN << "-- Check dirty inputs" << this->title() << DTK_NO_COLOR;
#endif

    // -- Check dirty inputs
    
    foreach(dtkComposerEdge *i_edge, input_edges)
        foreach(dtkComposerEdge *e, d->iRoute(i_edge))
            if(e->source()->node()->dirty())
                return;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_COLOR_BG_GREEN << "-- Mark dirty outputs" << this->title() << DTK_NO_COLOR;
#endif

    // -- Mark dirty outputs

    foreach(dtkComposerEdge *o_edge, output_edges)
        foreach(dtkComposerEdge *e, d->oRoute(o_edge))
            e->destination()->node()->setDirty(true);

    // -- Event handling

    emit evaluated(this); qApp->processEvents();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_COLOR_BG_GREEN << "Updating" << this->title() << DTK_NO_COLOR;
#endif

    // -- Pull

    foreach(dtkComposerEdge *i_edge, input_edges) {
        dtkComposerNodeProperty *p = i_edge->destination();
        dtkComposerNode         *n = i_edge->destination()->node();
        foreach(dtkComposerEdge *e, d->iRoute(i_edge)) {
            
            dtkComposerEdge *edge = new dtkComposerEdge;
            edge->setSource(e->source());
            edge->setDestination(p);
            
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
            qDebug() << DTK_COLOR_BG_YELLOW << "Pulling" << n->title() << edge << DTK_NO_COLOR;
#endif
            

// --
            if(dtkComposerNode *source = e->source()->node()) {
                if (source->kind() == dtkComposerNode::Data) {
                    source->onOutputEdgeConnected(e, e->source());
                }
            }
// --

            n->onInputEdgeConnected(edge, p);
            
            delete edge;
        }
    }

    // -- Run node's logic

    this->run();

    // -- Push

    foreach(dtkComposerEdge *o_edge, output_edges) {
        dtkComposerNodeProperty *p = o_edge->source();
        dtkComposerNode         *n = o_edge->source()->node();
        foreach(dtkComposerEdge *e, d->oRoute(o_edge)) {
            
            dtkComposerEdge *edge = new dtkComposerEdge;
            edge->setSource(p);
            edge->setDestination(e->destination());
            
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
            qDebug() << DTK_COLOR_BG_RED << "Pushing" << n->title() << edge << DTK_NO_COLOR;
#endif
            
            n->onOutputEdgeConnected(edge, p);
            
            delete edge;
        }
    }

    // -- Forward

    this->setDirty(false);

    foreach(dtkComposerEdge *o_edge, output_edges) {
        foreach(dtkComposerEdge *e, d->oRoute(o_edge)) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
            qDebug() << DTK_COLOR_BG_GREEN << "Forwarding" << this->title() << "->" << e->destination()->node()->title() << DTK_NO_COLOR;
#endif

            e->destination()->node()->update();
        }
    }
}

QRectF dtkComposerNode::boundingRect(void) const
{
    if(d->ghost)
        return d->ghostRect();
    else
        return d->bounding_rect;

    // return QRectF(-d->width/2 - d->penWidth / 2, -d->header_height - d->penWidth / 2, d->width + d->penWidth, d->height + d->penWidth);
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

    QRectF rect;

    if(!d->ghost) {
        rect = d->bounding_rect;

        // rect = QRectF(-d->width/2, -d->header_height, d->width, d->height);
    } else {
        rect = d->ghostRect();
    }

    QLinearGradient gradiant(rect.left(), rect.top(), rect.left(), rect.bottom());

    switch(d->kind) {
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
        if(d->ghost) {
            gradiant.setColorAt(0.0, QColor("#959595"));
            gradiant.setColorAt(1.0, QColor("#525252"));
        } else {
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
    }

    QPen pen;

    if(this->isSelected()) {
        pen.setColor(Qt::magenta);
        pen.setWidth(2);
    } else {
        if(this->kind() == dtkComposerNode::Composite && this->isGhost()) {
            pen.setColor(QColor("#c7c7c7"));
            pen.setStyle(Qt::DashLine);
            pen.setWidth(1);
        } else if(this->kind() == dtkComposerNode::Control) {
            pen.setColor(QColor("#c7c7c7"));
            pen.setStyle(Qt::DashLine);
            pen.setWidth(1);
        } else {    
            pen.setColor(Qt::black);
            pen.setWidth(1);
        }
    }

    painter->setPen(pen);

    if(this->kind() == dtkComposerNode::Control) {
        painter->setBrush(Qt::NoBrush);
    } else {
        painter->setBrush(gradiant);
    }

    painter->drawRoundedRect(rect, d->node_radius, d->node_radius);

    // Drawing size grip

    if(d->resizable) {

        QPainterPath path;
        path.moveTo(this->boundingRect().bottomRight() + QPointF(0.5, 0.5));
        path.lineTo(this->boundingRect().bottomRight() + QPointF(0.5, 0.5) + QPointF(-12, 0));
        path.lineTo(this->boundingRect().bottomRight() + QPointF(0.5, 0.5) + QPointF(0, -12));
        path.lineTo(this->boundingRect().bottomRight() + QPointF(0.5, 0.5));
        
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor("#c7c7c7"));
        painter->drawPath(path);
    }
}

void dtkComposerNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if (event->buttons() & Qt::LeftButton && !d->drag_point.isNull()) {
        
        QPointF delta = QPointF(event->scenePos() - d->drag_point);

        d->bounding_rect.setBottomRight(d->bounding_rect.bottomRight() + delta);

        d->drag_point = event->scenePos();

        event->accept();

        QGraphicsItem::update();

        return;
    }

    if(!d->clicked_property)
        QGraphicsItem::mouseMoveEvent(event);

    foreach(dtkComposerEdge *edge, d->input_edges.keys())
	edge->adjust();

    foreach(dtkComposerEdge *edge, d->output_edges.keys())
	edge->adjust();
}

void dtkComposerNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    // -- Handling of properties

    d->clicked_property = this->propertyAt(event->pos());

    if(d->clicked_property)
        return;

    // -- Handling of menus

    if(event->button() == Qt::RightButton) {
        QMenu menu;
        
        foreach(QAction *action, d->actions)
            menu.addAction(action);
        menu.exec(QCursor::pos());

        QGraphicsItem::mousePressEvent(event);

        return;
    }

    // -- Handling of resizing

    QPointF br = this->boundingRect().bottomRight();

    QRectF corner(br.x() - 16, br.y() - 16, 16, 16);

    if (d->kind == Control && event->button() & Qt::LeftButton && corner.contains(event->pos())) {
        d->drag_point = event->scenePos();

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

    if(!d->clicked_property)
        QGraphicsItem::mouseReleaseEvent(event);

    d->clicked_property = NULL;
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

void dtkComposerNode::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkComposerNode::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkComposerNode::run(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
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

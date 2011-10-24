/* dtkComposerNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:23 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 14:25:47 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 2485
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
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

    QHash<dtkComposerEdge *, dtkComposerNodeProperty *> input_relay_edges;
    QHash<dtkComposerEdge *, dtkComposerNodeProperty *> output_relay_edges;

    QList<dtkComposerEdge *> input_routes;
    QList<dtkComposerEdge *> output_routes;

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

QList<dtkComposerEdge *> dtkComposerNodePrivate::iRoute(dtkComposerEdge *edge)
{
    QList<dtkComposerEdge *> edges;

    if (edge->source()->node()->kind() != dtkComposerNode::Composite) {

        // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->source()->node()->title() << "is not composite" << DTK_NO_COLOR;

        edges << edge;

    } else {

        if (edge->source()->node() == edge->destination()->node()->parentNode()) {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->source()->node()->title() << "parent is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *i_edge, edge->source()->node()->inputEdges())
                if (i_edge->destination() == edge->source())
                    edges << iRoute(i_edge);
        } else {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->source()->node()->title() << "source is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *ghost, edge->source()->node()->outputGhostEdges())
                if (ghost->destination() == edge->source())
                    edges << iRoute(ghost);
        }
    }

    return edges;
}

QList<dtkComposerEdge *> dtkComposerNodePrivate::oRoute(dtkComposerEdge *edge)
{
    QList<dtkComposerEdge *> edges;

    if (edge->destination()->node()->kind() != dtkComposerNode::Composite) {

        // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->destination()->node()->title() << "is not composite" << DTK_NO_COLOR;

        edges << edge;

    } else {

        if (edge->destination()->node() == edge->source()->node()->parentNode()) {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->destination()->node()->title() << "parent is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *o_edge, edge->destination()->node()->outputEdges())
                if (o_edge->source() == edge->destination())
                    edges << oRoute(o_edge);

        } else {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->destination()->node()->title() << "destination is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *ghost, edge->destination()->node()->inputGhostEdges())
                if (ghost->source() == edge->destination())
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

void dtkComposerNode::setObject(dtkAbstractObject *object)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->object = object;

    if(object->hasMetaData("hidden-input-properties"))
        foreach(QString property, object->metaDataValues("hidden-input-properties"))
            if(dtkComposerNodeProperty *p = this->inputProperty(property))
                p->hide();

    if(object->hasMetaData("hidden-output-properties"))
        foreach(QString property, object->metaDataValues("hidden-output-properties"))
            if(dtkComposerNodeProperty *p = this->outputProperty(property))
                p->hide();

    if(object->hasMetaData("shown-input-properties"))
        foreach(QString property, object->metaDataValues("shown-input-properties"))
            if(dtkComposerNodeProperty *p = this->inputProperty(property))
                p->show();

    if(object->hasMetaData("shown-output-properties"))
        foreach(QString property, object->metaDataValues("shown-output-properties"))
            if(dtkComposerNodeProperty *p = this->outputProperty(property))
                p->show();

    if (d->object)
        d->title->setHtml(object->name());
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

dtkComposerEdge *dtkComposerNode::edge(dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if (this->kind() != dtkComposerNode::Composite) {

        if (property->type() == dtkComposerNodeProperty::Input && property->behavior() == dtkComposerNodeProperty::AsLoopOutput) {
            return d->output_relay_edges.key(property);

        } else if (property->type() == dtkComposerNodeProperty::Input) {
            return d->input_edges.key(property);

        } else if (property->type() == dtkComposerNodeProperty::HybridInput || property->type() == dtkComposerNodeProperty::PassThroughInput) {
            if (property->behavior() == dtkComposerNodeProperty::AsInput)
                return d->input_edges.key(property);
            else if (property->behavior() == dtkComposerNodeProperty::AsRelay)
                return d->input_relay_edges.key(property);
        
            else if (property->type() == dtkComposerNodeProperty::Output)
                return d->output_edges.key(property);

        } else if (property->type() == dtkComposerNodeProperty::HybridOutput || property->type() == dtkComposerNodeProperty::PassThroughOutput) {
            if (property->behavior() == dtkComposerNodeProperty::AsRelay)
                return d->output_relay_edges.key(property);
            else if (property->behavior() == dtkComposerNodeProperty::AsOutput)
                return d->output_edges.key(property);

        }

    } else {

        if (property->type() == dtkComposerNodeProperty::Input) {
            if (this->isGhost())            
                return d->ghost_input_edges.key(property);
            else
                return d->input_edges.key(property);
        }

        if (property->type() == dtkComposerNodeProperty::Output) {
            if (this->isGhost())
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

void dtkComposerNode::addInputRelayEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->input_relay_edges.insert(edge, property);
}

void dtkComposerNode::addOutputRelayEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    d->output_relay_edges.insert(edge, property);
}

void dtkComposerNode::addInputRoute(dtkComposerEdge *route)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->input_routes << route;
}

void dtkComposerNode::addOutputRoute(dtkComposerEdge *route)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->output_routes << route;
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

void dtkComposerNode::removeInputRelayEdge(dtkComposerEdge *edge)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->input_relay_edges.remove(edge);
}

void dtkComposerNode::removeOutputRelayEdge(dtkComposerEdge *edge)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->output_relay_edges.remove(edge);
}

void dtkComposerNode::removeAllRelayEdges(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->input_relay_edges.clear();
    d->output_relay_edges.clear();
}

void dtkComposerNode::removeInputRoute(dtkComposerEdge *route)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->input_routes.removeAll(route);
}

void dtkComposerNode::removeOutputRoute(dtkComposerEdge *route)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->output_routes.removeAll(route);
}

void dtkComposerNode::removeAllRoutes(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    d->input_routes.clear();
    d->output_routes.clear();
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

    int property_count = 0;

    if (property->type() == dtkComposerNodeProperty::Input) {

        property_count = d->input_edges.keys(property).count();

    } else if (property->type() == dtkComposerNodeProperty::HybridInput) {

        if (!d->input_edges.keys(property).count())
            property_count = d->input_relay_edges.keys(property).count();
        else
            property_count = d->input_edges.keys(property).count();

    } else if (property->type() == dtkComposerNodeProperty::PassThroughInput) {

        if (!d->input_edges.keys(property).count())
            property_count = d->input_relay_edges.keys(property).count();
        else
            property_count = d->input_edges.keys(property).count();

    } else if (property->type() == dtkComposerNodeProperty::Output) {

        property_count = d->output_edges.keys(property).count();

    } else if (property->type() == dtkComposerNodeProperty::HybridOutput) {

        if (!d->output_edges.keys(property).count())
            property_count = d->output_relay_edges.keys(property).count();
        else
            property_count = d->output_edges.keys(property).count();

    } else if (property->type() == dtkComposerNodeProperty::PassThroughOutput) {

        if (!d->output_edges.keys(property).count())
            property_count = d->output_relay_edges.keys(property).count();
        else
            property_count = d->output_edges.keys(property).count();

    }
    return property_count;
}

int dtkComposerNode::number(dtkComposerNodeProperty *property)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    int index = -1;

    if (property->type() == dtkComposerNodeProperty::Input) {
        index = d->input_properties.indexOf(property);

    } else if (property->type() == dtkComposerNodeProperty::HybridInput) {
        index = d->input_properties.indexOf(property);

    } else if (property->type() == dtkComposerNodeProperty::PassThroughInput) {
        index = d->input_properties.indexOf(property);

    } else if (property->type() == dtkComposerNodeProperty::Output) {
        index = d->output_properties.indexOf(property);

    } else if (property->type() == dtkComposerNodeProperty::HybridOutput) {
        index = d->output_properties.indexOf(property);

    } else if (property->type() == dtkComposerNodeProperty::PassThroughOutput) {
        index = d->output_properties.indexOf(property);

    }

    return index;
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

QList<dtkComposerEdge *> dtkComposerNode::inputRelayEdges(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    return d->input_relay_edges.keys();
}

QList<dtkComposerEdge *> dtkComposerNode::outputRelayEdges(void)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    return d->output_relay_edges.keys();
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

QList<dtkComposerEdge *> dtkComposerNode::inputRoutes(void)
{
    return d->input_routes;
}

QList<dtkComposerEdge *> dtkComposerNode::outputRoutes(void)
{
    return d->output_routes;
}

dtkComposerNodeProperty *dtkComposerNode::propertyAt(const QPointF& point) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, d->input_properties)
        if (property->rect().contains(point))
            return property;

    foreach(dtkComposerNodeProperty *property, d->output_properties)
        if (property->rect().contains(point))
            return property;
    
    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::inputProperty(const QString& name) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, d->input_properties)
        if (property->name() == name)
            return property;
    
    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::inputProperty(const QString& name, dtkComposerNode *from) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, d->input_properties)
        if (property->name() == name)
            if (property->clonedFrom() == from)
                return property;
    
    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::outputProperty(const QString& name) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, d->output_properties)
        if (property->name() == name)
            return property;

    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::outputProperty(const QString& name, dtkComposerNode *from) const
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    foreach(dtkComposerNodeProperty *property, d->output_properties)
        if (property->name() == name)
            if (property->clonedFrom() == from)
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

    if (d->kind == dtkComposerNode::Composite) {
        if (d->dirty) {
            foreach(dtkComposerNode *child, d->children)
                if (!child->inputEdges().count() && child->outputEdges().count())
                    child->setDirty(dirty);            
            foreach(dtkComposerEdge *ghost_edge, d->ghost_input_edges.keys())
                ghost_edge->destination()->node()->setDirty(dirty);
        } else {
            foreach(dtkComposerNode *child, d->children)
                child->setDirty(dirty);            
        }
    }
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

    foreach(dtkComposerNodeProperty *property, d->input_properties)
        if (property->isDisplayed())
            if (d->ghost)
                property->setRect(QRectF(d->ghostRect().left() + d->node_radius, d->ghostRect().top() + 40 + (4 * (exposed_input_properties++) + 1) * d->node_radius - d->node_radius, d->node_radius * 2, d->node_radius * 2));
            else
                property->setRect(QRectF(d->bounding_rect.left() + d->node_radius, d->margin_top + (3 * (exposed_input_properties++) + 1) * d->node_radius - d->node_radius, d->node_radius * 2, d->node_radius * 2));

    int exposed_output_properties = 0;

    foreach(dtkComposerNodeProperty *property, d->output_properties)
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

    if (!d->children.contains(node))
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

//! 
/*! 
 * 
 */
void dtkComposerNode::update(void)
{

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

    foreach(dtkComposerEdge *edge, d->input_edges.keys())
	edge->adjust();

    foreach(dtkComposerEdge *edge, d->output_edges.keys())
	edge->adjust();

    foreach(dtkComposerEdge *edge, d->input_relay_edges.keys())
	edge->adjust();

    foreach(dtkComposerEdge *edge, d->output_relay_edges.keys()) 
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

void dtkComposerNode::onEdgeConnected(dtkComposerEdge *edge)
{
    QList<dtkComposerNodeProperty *> sources;
    QList<dtkComposerNodeProperty *> destinations;
        
    foreach(dtkComposerEdge *e, d->iRoute(edge))
        if (!sources.contains(e->source()) && e->source()->node()->kind() != dtkComposerNode::Composite)
            sources << e->source();
        
    foreach(dtkComposerEdge *e, d->oRoute(edge))
        if (!destinations.contains(e->destination()) && e->destination()->node()->kind() != dtkComposerNode::Composite)
            destinations << e->destination();
        
    foreach(dtkComposerNodeProperty *source, sources) {
        foreach(dtkComposerNodeProperty *destin, destinations) {
                
            dtkComposerEdge *route = new dtkComposerEdge;
            route->setSource(source);
            route->setDestination(destin);
                
            foreach(dtkComposerEdge *input, destin->node()->d->input_routes) {
                if (input->source() == source && input->destination() == destin) {
                    delete route;                    
                    return;
                }
            }
            foreach(dtkComposerEdge *output, source->node()->d->output_routes) {
                if (output->source() == source && output->destination() == destin) {
                    delete route;
                    return;
                }
            }

            if (source->type() == dtkComposerNodeProperty::HybridOutput || 
                source->type() == dtkComposerNodeProperty::PassThroughOutput || 
                (source->type() == dtkComposerNodeProperty::Output && source->node()->kind() == dtkComposerNode::Control && !destin->node()->isChildOfControlNode(source->node()))) {

                dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());                    
                control_node->addOutputRoute(route);

                dtkComposerEdge *active_route = new dtkComposerEdge;
                active_route->setSource(route->source());
                active_route->setDestination(route->destination());

                control_node->addOutputActiveRoute(active_route);

                if (destin->type() == dtkComposerNodeProperty::HybridOutput || 
                    destin->type() == dtkComposerNodeProperty::PassThroughOutput || 
                    (destin->type() == dtkComposerNodeProperty::Input && destin->node()->kind() == dtkComposerNode::Control && source->node()->isChildOfControlNode(destin->node()))) {
                    dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
                    output_control_node->addOutputRelayRoute(active_route);
                } else {
                    destin->node()->d->input_routes << active_route;
                }

            } else if (source->type() == dtkComposerNodeProperty::HybridInput || 
                       source->type() == dtkComposerNodeProperty::PassThroughInput || 
                       (source->type() == dtkComposerNodeProperty::Output && source->node()->kind() == dtkComposerNode::Control && destin->node()->isChildOfControlNode(source->node()))) {

                dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());
                control_node->addInputRelayRoute(route);

            } else if (destin->type() == dtkComposerNodeProperty::HybridOutput || 
                       destin->type() == dtkComposerNodeProperty::PassThroughOutput || 
                       (destin->type() == dtkComposerNodeProperty::Input && destin->node()->kind() == dtkComposerNode::Control && source->node()->isChildOfControlNode(destin->node()))) {

                dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
                control_node->addOutputRelayRoute(route);
                source->node()->d->output_routes << route;

            } else {
                
                destin->node()->d->input_routes << route;
                source->node()->d->output_routes << route;
            }
        }
    }
}

void dtkComposerNode::onEdgeDisconnected(dtkComposerEdge *edge)
{
    QList<dtkComposerNodeProperty *> sources;
    QList<dtkComposerNodeProperty *> destinations;

    foreach(dtkComposerEdge *e, d->iRoute(edge))
        if (!sources.contains(e->source()) && e->source()->node()->kind() != dtkComposerNode::Composite)
            sources << e->source();

    foreach(dtkComposerEdge *e, d->oRoute(edge))
        if (!destinations.contains(e->destination()) && e->destination()->node()->kind() != dtkComposerNode::Composite)
            destinations << e->destination();

    dtkComposerEdge *input_route = NULL;
    dtkComposerEdge *output_route = NULL;
        
    foreach(dtkComposerNodeProperty *source, sources) {
        foreach(dtkComposerNodeProperty *destin, destinations) {

            if (source->type() == dtkComposerNodeProperty::HybridOutput || 
                source->type() == dtkComposerNodeProperty::PassThroughOutput || 
                (source->type() == dtkComposerNodeProperty::Output && source->node()->kind() == dtkComposerNode::Control && !destin->node()->isChildOfControlNode(source->node()))) {

                dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());  

                foreach(dtkComposerEdge *o_route, source->node()->d->output_routes) {
                    if (o_route->source() == source && o_route->destination() == destin) {
                        output_route = o_route;
                        source->node()->d->output_routes.removeAll(output_route);
                        break;
                    }
                }

                foreach(dtkComposerEdge *active_route, control_node->outputActiveRoutes()) {
                    if (active_route->source() == source && active_route->destination() == destin) {                            
                        control_node->removeOutputActiveRoute(active_route);
                        if (destin->type() == dtkComposerNodeProperty::HybridOutput || 
                            destin->type() == dtkComposerNodeProperty::PassThroughOutput || 
                            (destin->type() == dtkComposerNodeProperty::Input && destin->node()->kind() == dtkComposerNode::Control && source->node()->isChildOfControlNode(destin->node()))) {
                            dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
                            output_control_node->removeOutputRelayRoute(active_route);
                        } else {
                            destin->node()->d->input_routes.removeAll(active_route);
                        }
                        delete active_route;
                        active_route = NULL;
                    }
                }
                    
                if (output_route)
                    delete output_route;
                output_route = NULL;
                    
            } else if (source->type() == dtkComposerNodeProperty::HybridInput || 
                       source->type() == dtkComposerNodeProperty::PassThroughInput || 
                       (source->type() == dtkComposerNodeProperty::Output && source->node()->kind() == dtkComposerNode::Control && destin->node()->isChildOfControlNode(source->node()))) {

                dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());
                foreach(dtkComposerEdge *i_route, control_node->inputRelayRoutes()) {
                    if (i_route->source() == source && i_route->destination() == destin) {
                        foreach(dtkComposerEdge *active_route, control_node->inputActiveRoutes()) {
                            if (active_route->destination() == destin) {
                                active_route->destination()->node()->removeRoute(active_route);
                                control_node->removeInputActiveRoute(active_route);
                                delete active_route;
                                active_route = NULL;
                            }
                        }
                        output_route = i_route;
                        control_node->removeInputRelayRoute(output_route);
                        break;
                    }
                }

                if (output_route)
                    delete output_route;
                output_route = NULL;
              
            } else if (destin->type() == dtkComposerNodeProperty::Input && destin->node()->kind() == dtkComposerNode::Control && source->node()->isChildOfControlNode(destin->node())) {

                dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
                foreach(dtkComposerEdge *o_route, control_node->outputRelayRoutes()) {
                    if (o_route->source() == source && o_route->destination() == destin) {
                        input_route = o_route;
                        control_node->removeOutputRelayRoute(input_route);
                        input_route->source()->node()->removeOutputRoute(input_route);
                        break;
                    }
                }

                if (input_route)
                    delete input_route;
                input_route = NULL;

            } else if (destin->type() == dtkComposerNodeProperty::HybridOutput || destin->type() == dtkComposerNodeProperty::PassThroughOutput) {

                dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
                foreach(dtkComposerEdge *o_route, control_node->outputRelayRoutes()) {
                    if (o_route->source() == source && o_route->destination() == destin) {
                        foreach(dtkComposerEdge *active_route, control_node->outputActiveRoutes()) {
                            if (active_route->source() == destin || active_route->source() == source) {
                                active_route->destination()->node()->removeRoute(active_route);
                                control_node->removeOutputActiveRoute(active_route);
                                delete active_route;
                                active_route = NULL;
                            }
                        }
                        input_route = o_route;
                        control_node->removeOutputRelayRoute(input_route);
                        input_route->source()->node()->removeOutputRoute(input_route);
                        break;
                    }
                }

                if (input_route)
                    delete input_route;
                input_route = NULL;

            } else {

                foreach(dtkComposerEdge *i_route, destin->node()->d->input_routes) {
                    if (i_route->source() == source && i_route->destination() == destin) {
                        input_route = i_route;
                        destin->node()->d->input_routes.removeAll(input_route);
                        break;
                    }
                }

                foreach(dtkComposerEdge *o_route, source->node()->d->output_routes) {
                    if (o_route->source() == source && o_route->destination() == destin) {
                        output_route = o_route;
                        source->node()->d->output_routes.removeAll(output_route);
                        break;
                    }
                }
                
                if (input_route == output_route)
                    output_route = NULL;

                if (input_route)
                    delete input_route;

                if (output_route)
                    delete output_route;

                input_route = NULL;
                output_route = NULL;
            }
        }
    }
}

QList<dtkComposerEdge *> dtkComposerNode::allRoutes(void)
{
    QList<dtkComposerEdge *> routes;
    routes << d->input_routes;
    routes << d->output_routes;

    return routes;
}

void dtkComposerNode::removeRoute(dtkComposerEdge *route)
{
    d->input_routes.removeAll(route);
    d->output_routes.removeAll(route);
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
    foreach(dtkComposerEdge *i_route, d->input_routes) {

        if(dtkComposerNodeLoop *loop = dynamic_cast<dtkComposerNodeLoop *>(i_route->source()->node())) {

            if(this->isChildOf(loop)) {

                if(loop->isPreRunning() || loop->isRunning() || loop->isPostRunning())
                    continue;
                else
                    return true;

            } else {

                if (i_route->source()->node()->dirty())
                    return true;
            }

        } else {

            if (i_route->source()->node()->dirty())
                return true;
        }
    }
    return false;
}

void dtkComposerNode::markDirtyDownstreamNodes(void)
{
    foreach(dtkComposerEdge *o_route, d->output_routes)
        o_route->destination()->node()->setDirty(true);
}

void dtkComposerNode::pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);

    DTK_DEFAULT_IMPLEMENTATION;    
}

void dtkComposerNode::run(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkComposerNode::push(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);

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

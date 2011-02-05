/* dtkComposerNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:23 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Sat Feb  5 15:09:07 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 1360
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

#define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerNodePrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePrivate
{
public:
    QRectF ghostRect(void);

    QList<dtkComposerEdge *> iRoute(dtkComposerEdge *edge);
    QList<dtkComposerEdge *> oRoute(dtkComposerEdge *edge);

    bool loop(void);

public:
    dtkComposerNode *q;

    qreal penWidth;
    qreal width;
    qreal height;
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

    dtkComposerNodeProperty *loop_property;
    dtkComposerNodeProperty *clicked_property;

    dtkComposerNode::Behavior behavior;
    dtkComposerNode::Kind kind;

    QString type;
    QString condition;

    dtkAbstractObject *object;

    QList<QAction *> actions;

    bool dirty;
    
    bool ghost;

          dtkComposerNode *  parent;
    QList<dtkComposerNode *> children;

    int count;
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

        if(edge->destination()->node() == q && edge->source()->node() == edge->destination()->node()->parentNode()) {

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

    if(edge->destination()->node()->behavior() == dtkComposerNode::Loop && edge->destination() == edge->destination()->node()->d->loop_property)
        return edges;

    if(edge->destination()->node()->kind() != dtkComposerNode::Composite) {

        // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->destination()->node()->title() << "is not composite" << DTK_NO_COLOR;

        edges << edge;

    } else {

        if(edge->source()->node() == q && edge->destination()->node() == edge->source()->node()->parentNode()) {

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

bool dtkComposerNodePrivate::loop(void)
{
    QRegExp r("(\\w+)\\s*(>|>=|<|<=|==|!=)\\s*([\\d\\.]+)");
    
    QString op1, op, op2;

    if(r.indexIn(this->condition) != -1) {
        op1 = r.cap(1);
        op  = r.cap(2);
        op2 = r.cap(3);
    }

    if(op1.isEmpty() || op.isEmpty() || op2.isEmpty()) {
        qDebug() << DTK_PRETTY_FUNCTION << "Malformed condition expression";
        return false;
    } else {
        // qDebug() << "op1" << op1;
        // qDebug() << "op " << op;
        // qDebug() << "op2" << op2;
    }

    QVariant v1;

    foreach(dtkComposerEdge *edge, this->ghost_output_edges.keys()) {
        if(edge->destination() == this->loop_property) {
            v1 = edge->source()->node()->value(edge->source());
        }
    }

    if(!v1.isValid()) {
        qDebug() << DTK_PRETTY_FUNCTION << "Unable to retrieve first operand value";
        return false;
    } else {
        // qDebug() << DTK_PRETTY_FUNCTION << "First operand value is" << v1;
    }

    if(!v1.canConvert<double>()) {
        qDebug() << DTK_PRETTY_FUNCTION << "Unable to convert first operand to double";
        return false;
    }

    double d; bool ok; d = op2.toDouble(&ok);

    if(!ok) {
        qDebug() << DTK_PRETTY_FUNCTION << "Unable to cast second argument into a double";
        return false;
    } else {
        // qDebug() << "Second argument is" << d;
    }

    if(op == "<")
        return (v1.toDouble()  < d);
    else if(op == "<=")
        return (v1.toDouble() <= d);
    else if(op == "==")
        return (v1.toDouble() == d);
    else if(op == "!=")
        return (v1.toDouble() != d);
    else if(op == ">=")
        return (v1.toDouble() >= d);
    else if(op == ">")
        return (v1.toDouble()  > d);

    return false;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNode
// /////////////////////////////////////////////////////////////////

dtkComposerNode::dtkComposerNode(dtkComposerNode *parent) : QObject(), QGraphicsItem(parent), d(new dtkComposerNodePrivate)
{
    d->count = 0; // TO BE REMOVED

    d->q = this;
    
    d->behavior = Default;
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

    d->width = 150;
    d->height = d->header_height*2;

    d->title = new QGraphicsTextItem(this);
#if defined(Q_WS_MAC)
    d->title->setFont(QFont("Lucida Grande", 13));
#else
    d->title->setFont(QFont("Lucida Grande", 11));
#endif
    d->title->setPlainText("Title");
    d->title->setDefaultTextColor(Qt::white);
    d->title->setPos(-d->width/2 + d->margin_left/2, -d->header_height-2);

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable); // | QGraphicsItem::ItemSendsGeometryChanges);
    this->setZValue(10);

#if QT_VERSION >= 0x040600
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(5);
    shadow->setOffset(3);
    shadow->setColor(QColor(0, 0, 0, 127));
    this->setGraphicsEffect(shadow);
#endif

    d->loop_property = new dtkComposerNodeProperty("condition", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Single, this);
    d->loop_property->setClonedFrom(this);
    d->loop_property->hide();

    d->clicked_property = NULL;

    d->dirty = true;

    d->ghost = false;
}

dtkComposerNode::~dtkComposerNode(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNode::setTitle(const QString& title)
{
    d->title->setPlainText(title);
}

void dtkComposerNode::setBehavior(Behavior behavior)
{
    d->behavior = behavior;

    if(behavior == dtkComposerNode::Loop) {

        d->output_properties << d->loop_property;

        if (d->ghost)
            d->loop_property->show();
        
    } else {

        foreach(dtkComposerEdge *edge, d->ghost_output_edges.keys()) {
            if(edge->destination() == d->loop_property) {
                d->ghost_output_edges.remove(edge);
                if(dtkComposerScene *scene = dynamic_cast<dtkComposerScene *>(this->scene()))
                    scene->removeEdge(edge);
            }
        }

        d->loop_property->hide();
        d->output_properties.removeAll(d->loop_property);
    }
}

void dtkComposerNode::setCondition(const QString& condition)
{
    d->condition = condition;
}

void dtkComposerNode::setKind(Kind kind)
{
    d->kind = kind;
}

void dtkComposerNode::setType(QString type)
{
    d->type = type;
}

void dtkComposerNode::setObject(dtkAbstractObject *object)
{
    d->object = object;

    d->title->setHtml(object->name());
}

dtkComposerNode::Behavior dtkComposerNode::behavior(void)
{
    return d->behavior;
}

dtkComposerNode::Kind dtkComposerNode::kind(void)
{
    return d->kind;
}

QString dtkComposerNode::type(void)
{
    return d->type;
}

dtkAbstractObject *dtkComposerNode::object(void)
{
    return d->object;
}

dtkComposerEdge *dtkComposerNode::edge(dtkComposerNodeProperty *property)
{
    if(property->type() == dtkComposerNodeProperty::Input)
        return d->input_edges.key(property);
    
    if(property->type() == dtkComposerNodeProperty::Output)
        return d->output_edges.key(property);

    return NULL;
}

void dtkComposerNode::addInputProperty(dtkComposerNodeProperty *property)
{
    d->input_properties << property;

    this->layout();
}

void dtkComposerNode::addOutputProperty(dtkComposerNodeProperty *property)
{
    d->output_properties << property;

    this->layout();
}

void dtkComposerNode::removeInputProperty(dtkComposerNodeProperty *property)
{
    d->input_properties.removeAll(property);
}

void dtkComposerNode::removeOutputProperty(dtkComposerNodeProperty *property)
{
    d->output_properties.removeAll(property);
}

void dtkComposerNode::addInputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    d->input_edges.insert(edge, property);

    // this->onInputEdgeConnected(edge, property);
}

void dtkComposerNode::addOutputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    d->output_edges.insert(edge, property);

    // this->onOutputEdgeConnected(edge, property);
}

void dtkComposerNode::addGhostInputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    d->ghost_input_edges.insert(edge, property);
}

void dtkComposerNode::addGhostOutputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    d->ghost_output_edges.insert(edge, property);
}

void dtkComposerNode::removeInputEdge(dtkComposerEdge *edge)
{
    d->input_edges.remove(edge);
}

void dtkComposerNode::removeOutputEdge(dtkComposerEdge *edge)
{
    d->output_edges.remove(edge);
}

void dtkComposerNode::removeAllEdges(void)
{
    d->input_edges.clear();
    d->output_edges.clear();
}

void dtkComposerNode::addAction(const QString& text, const QObject *receiver, const char *slot)
{
    QAction *action = new QAction(text, this);

    connect(action, SIGNAL(triggered()), receiver, slot);

    d->actions << action;
}

int dtkComposerNode::count(dtkComposerNodeProperty *property)
{
    if(property->type() == dtkComposerNodeProperty::Input)
        return d->input_edges.keys(property).count();

    if(property->type() == dtkComposerNodeProperty::Output)
        return d->output_edges.keys(property).count();

    return 0;
}

int dtkComposerNode::number(dtkComposerNodeProperty *property)
{
    if(property->type() == dtkComposerNodeProperty::Input)
        return d->input_properties.indexOf(property);

    if(property->type() == dtkComposerNodeProperty::Output)
        return d->output_properties.indexOf(property);
}

QList<dtkComposerNodeProperty *> dtkComposerNode::inputProperties(void)
{
    return d->input_properties;
}

QList<dtkComposerNodeProperty *> dtkComposerNode::outputProperties(void)
{
    return d->output_properties;
}

QList<dtkComposerEdge *> dtkComposerNode::inputEdges(void)
{
    return d->input_edges.keys();
}

QList<dtkComposerEdge *> dtkComposerNode::outputEdges(void)
{
    return d->output_edges.keys();
}

QList<dtkComposerEdge *> dtkComposerNode::inputGhostEdges(void)
{
    return d->ghost_input_edges.keys();
}

QList<dtkComposerEdge *> dtkComposerNode::outputGhostEdges(void)
{
    return d->ghost_output_edges.keys();
}

QList<dtkComposerNode *> dtkComposerNode::inputNodes(void)
{
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerEdge *edge, d->input_edges.keys())
        nodes << edge->source()->node();

    return nodes;
}

QList<dtkComposerNode *> dtkComposerNode::outputNodes(void)
{
    QList<dtkComposerNode *> nodes;

    foreach(dtkComposerEdge *edge, d->output_edges.keys())
        nodes << edge->destination()->node();

    return nodes;
}

dtkComposerNodeProperty *dtkComposerNode::propertyAt(const QPointF& point) const
{
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
    foreach(dtkComposerNodeProperty *property, d->input_properties)
        if(property->name() == name)
            return property;
    
    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::inputProperty(const QString& name, dtkComposerNode *from) const
{
    foreach(dtkComposerNodeProperty *property, d->input_properties)
        if(property->name() == name)
            if(property->clonedFrom() == from)
                return property;
    
    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::outputProperty(const QString& name) const
{
    foreach(dtkComposerNodeProperty *property, d->output_properties)
        if(property->name() == name)
            return property;

    return NULL;
}

dtkComposerNodeProperty *dtkComposerNode::outputProperty(const QString& name, dtkComposerNode *from) const
{
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

QString dtkComposerNode::condition(void)
{
    return d->condition;
}

bool dtkComposerNode::dirty(void)
{
    return d->dirty;
}

void dtkComposerNode::setDirty(bool dirty)
{
    d->dirty = dirty;
}

void dtkComposerNode::layout(void)
{
    if (d->ghost)
        d->title->setPos(d->ghostRect().topLeft());
    else 
        d->title->setPos(-d->width/2 + d->margin_left/2, -d->header_height-2);

    int exposed_input_properties = 0;

    foreach(dtkComposerNodeProperty *property, d->input_properties)
        if(property->isDisplayed())
            if(d->ghost)
                property->setRect(QRectF(d->ghostRect().left()+d->node_radius, d->ghostRect().top() + 40 + (3*(exposed_input_properties++) + 1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));
            else
                property->setRect(QRectF(-d->width/2+d->node_radius, d->margin_top+(3*(exposed_input_properties++) + 1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));

    int exposed_output_properties = 0;

    foreach(dtkComposerNodeProperty *property, d->output_properties)
        if(property->isDisplayed())
            if(d->ghost)
                property->setRect(QRectF(d->ghostRect().right() - 3*d->node_radius, d->ghostRect().top() + 40 + (3*(exposed_output_properties++) + 1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));
            else
                property->setRect(QRectF(d->width/2-3*d->node_radius, d->margin_top+(3*(exposed_output_properties++) + 1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));

    if(d->ghost && d->loop_property->isVisible()) {
        d->loop_property->setRect(QRectF(d->ghostRect().right() - 3*d->node_radius, d->ghostRect().bottom() - 40 - 2*d->node_radius, d->node_radius*2, d->node_radius*2));
        exposed_output_properties++;
    }

    d->height = d->header_height + (3*qMax(exposed_input_properties, exposed_output_properties)) * d->node_radius + d->margin_bottom;

    QGraphicsItem::update(this->boundingRect());
}

void dtkComposerNode::setParentNode(dtkComposerNode *node)
{
    d->parent = node;

    QObject::setParent(node);
}

void dtkComposerNode::addChildNode(dtkComposerNode *node)
{
    if(!d->children.contains(node))
        d->children << node;

    if(d->ghost)
        node->setParentItem(this);
}

void dtkComposerNode::removeChildNode(dtkComposerNode *node)
{
    if (d->children.contains(node))
        d->children.removeAll(node);
}

QList<dtkComposerNode *> dtkComposerNode::childNodes(void)
{
    return d->children;
}

dtkComposerNode *dtkComposerNode::parentNode(void)
{
    return d->parent;
}

void dtkComposerNode::setGhost(bool ghost)
{
    d->ghost = ghost;

    if(d->ghost) {

        this->setZValue(0);

        foreach(dtkComposerNode *node, d->children)
            node->setParentItem(this);

        if(d->behavior == dtkComposerNode::Loop) {
            d->loop_property->show();
            d->output_properties << d->loop_property;
        }

    } else {

        this->setZValue(10);

        foreach(dtkComposerNode *node, d->children)
            node->setParentItem(NULL);

        if(d->behavior == dtkComposerNode::Loop) {
            d->loop_property->hide();
            d->output_properties.removeAll(d->loop_property);
        }
    }

    this->layout();
}

bool dtkComposerNode::isGhost(void)
{
    return d->ghost;
}

void dtkComposerNode::alter(void)
{
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
    QGraphicsItem::update(this->boundingRect());
}

//! 
/*! 
 * 
 */
void dtkComposerNode::update(void)
{
    if(!dtkComposerScene::s_evaluate)
        return;

    if(d->kind != dtkComposerNode::View && !d->dirty)
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
            
            n->onInputEdgeConnected(edge, p);
            
            delete edge;
        }
    }

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

    // -- Loop

    foreach(dtkComposerEdge *o_edge, output_edges) {
        if (o_edge->destination()->node()->behavior() == dtkComposerNode::Loop && o_edge->destination() == o_edge->destination()->node()->d->loop_property) {
            
            if(o_edge->destination()->node()->d->loop()) {
                
                foreach(dtkComposerEdge *e, o_edge->destination()->node()->inputGhostEdges())
                    e->destination()->node()->setDirty(true);

                foreach(dtkComposerEdge *e, o_edge->destination()->node()->inputGhostEdges()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                    qDebug() << DTK_COLOR_BG_BLUE << "Forwarding" << this->title() << "->" << e->destination()->node()->title() << DTK_NO_COLOR;
#endif

                    e->destination()->node()->update();
                }
            }
        }
    }
}

QRectF dtkComposerNode::boundingRect(void) const
{
    if(d->ghost)
        return d->ghostRect();
    else
        return QRectF(-d->width/2 - d->penWidth / 2, -d->header_height - d->penWidth / 2, d->width + d->penWidth, d->height + d->penWidth);
}

void dtkComposerNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (d->kind == Composite)
        this->layout();

    QRectF rect;

    if(!d->ghost) {
        rect = QRectF(-d->width/2, -d->header_height, d->width, d->height);
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
        if(d->behavior == dtkComposerNode::Loop)
            if(d->ghost) {
                gradiant.setColorAt(0.0, QColor("#b6b71b"));
                gradiant.setColorAt(1.0, QColor("#76670c"));
            } else {
                gradiant.setColorAt(0.0, QColor("#67670a"));
                gradiant.setColorAt(1.0, QColor("#352d02"));
            }
        else
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

    painter->setBrush(gradiant);

    QPen pen;

    if(this->isSelected()) {
        pen.setColor(Qt::magenta);
        pen.setWidth(2);
    } else {
        if(this->isGhost()) {
            if(d->behavior == dtkComposerNode::Loop) {
                pen.setColor(QColor("#76670c"));
                pen.setStyle(Qt::DashLine);
                pen.setWidth(1);
            } else {
                pen.setColor(QColor("#c7c7c7"));
                pen.setStyle(Qt::DashLine);
                pen.setWidth(1);
            }
        } else {    
            if(d->behavior == dtkComposerNode::Loop) {
                pen.setColor(QColor("#352d02"));
                pen.setWidth(1);
            } else {
                pen.setColor(Qt::black);
                pen.setWidth(1);
            }
        }
    }

    painter->setPen(pen);
    painter->drawRoundedRect(rect, d->node_radius, d->node_radius);
}

void dtkComposerNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!d->clicked_property)
        QGraphicsItem::mouseMoveEvent(event);

    foreach(dtkComposerEdge *edge, d->input_edges.keys())
	edge->adjust();

    foreach(dtkComposerEdge *edge, d->output_edges.keys())
	edge->adjust();
}

void dtkComposerNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    d->clicked_property = this->propertyAt(event->pos());

    if(d->clicked_property)
        return;

    if(event->button() == Qt::RightButton) {
        QMenu menu;
        
        foreach(QAction *action, d->actions)
            menu.addAction(action);
        menu.exec(QCursor::pos());
    }

    QGraphicsItem::mousePressEvent(event);
}

void dtkComposerNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
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

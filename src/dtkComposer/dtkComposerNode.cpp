/* dtkComposerNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:23 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Nov  1 16:29:53 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 502
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

class dtkComposerNodePrivate
{
public:
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

    dtkComposerNodeProperty *clicked_property;

    dtkComposerNode::Kind kind;

    QString type;

    dtkAbstractObject *object;

    QList<QAction *> actions;

    bool dirty;
};

dtkComposerNode::dtkComposerNode(dtkComposerNode *parent) : QObject(), QGraphicsItem(parent), d(new dtkComposerNodePrivate)
{
    d->kind = Unknown;
    d->object = NULL;

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

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    this->setZValue(10);

#if QT_VERSION >= 0x040600
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(5);
    shadow->setOffset(3);
    shadow->setColor(QColor(0, 0, 0, 127));
    this->setGraphicsEffect(shadow);
#endif

    d->dirty = false;
}

dtkComposerNode::~dtkComposerNode(void)
{
    // foreach(dtkComposerEdge *edge, d->input_edges.keys())
    //     delete edge;

    // foreach(dtkComposerEdge *edge, d->output_edges.keys())
    //     delete edge;
    
    delete d;

    d = NULL;
}

void dtkComposerNode::setTitle(const QString& title)
{
    d->title->setPlainText(title);
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
    property->setRect(QRectF(-d->width/2+d->node_radius, d->margin_top+(3*d->input_properties.count() +1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));

    d->input_properties << property;

    d->height = d->header_height + (3*qMax(d->input_properties.count(), d->output_properties.count())) * d->node_radius + d->margin_bottom;
}

void dtkComposerNode::addOutputProperty(dtkComposerNodeProperty *property)
{
    property->setRect(QRectF(d->width/2-3*d->node_radius, d->margin_top+(3*d->output_properties.count() + 1)*d->node_radius - d->node_radius, d->node_radius*2, d->node_radius*2));

    d->output_properties << property;

    d->height = d->header_height + (3*qMax(d->input_properties.count(), d->output_properties.count())) * d->node_radius + d->margin_bottom;
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

void dtkComposerNode::removeInputEdge(dtkComposerEdge *edge)
{
    d->input_edges.remove(edge);
}

void dtkComposerNode::removeOutputEdge(dtkComposerEdge *edge)
{
    d->output_edges.remove(edge);
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

dtkComposerNodeProperty *dtkComposerNode::outputProperty(const QString& name) const
{
    foreach(dtkComposerNodeProperty *property, d->output_properties)
        if(property->name() == name)
            return property;

    return NULL;
}

QString dtkComposerNode::title(void)
{
    return QString(d->title->toPlainText());
}

bool dtkComposerNode::dirty(void)
{
    return d->dirty;
}

void dtkComposerNode::setDirty(bool dirty)
{
    d->dirty = dirty;
}

void dtkComposerNode::update(void)
{
    foreach(dtkComposerEdge *edge, d->input_edges.keys())
        if(edge->source()->node()->dirty())
            return;

    foreach(dtkComposerEdge *edge, d->output_edges.keys())
        edge->destination()->node()->setDirty(true);

    emit evaluated(this); qApp->processEvents(QEventLoop::ExcludeUserInputEvents | QEventLoop::ExcludeSocketNotifiers, 10);

    foreach(dtkComposerEdge *edge, d->input_edges.keys())
        this->onInputEdgeConnected(edge, edge->destination());

    foreach(dtkComposerEdge *edge, d->output_edges.keys())
        this->onOutputEdgeConnected(edge, edge->source());

    d->dirty = false;

    foreach(dtkComposerEdge *edge, d->output_edges.keys())
        edge->destination()->node()->update();
}

QRectF dtkComposerNode::boundingRect(void) const
{
    QRectF rect(-d->width/2 - d->penWidth / 2, -d->header_height - d->penWidth / 2, d->width + d->penWidth, d->height + d->penWidth);

    return rect;
}

void dtkComposerNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rect(-d->width/2, -d->header_height, d->width, d->height);

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
    case Control:
        gradiant.setColorAt(0.0, QColor(Qt::white));
        gradiant.setColorAt(0.3, QColor(Qt::red));
        gradiant.setColorAt(1.0, QColor(Qt::red).darker());
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

    if(this->isSelected()) 
        painter->setPen(QPen(Qt::magenta, 2));
    else
        painter->setPen(QPen(Qt::black, 1));

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

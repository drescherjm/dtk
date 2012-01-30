/* dtkComposerScene.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:13:25
 * Version: $Id$
 * Last-Updated: Tue Jan 31 00:17:49 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 434
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerScenePort
// /////////////////////////////////////////////////////////////////

class dtkComposerScenePortPrivate
{
public:
    QGraphicsEllipseItem *ellipse;
};

dtkComposerScenePort::dtkComposerScenePort(QGraphicsItem *parent) : QGraphicsItem(parent), d(new dtkComposerScenePortPrivate)
{
    d->ellipse = new QGraphicsEllipseItem(this);
    d->ellipse->setPen(QPen(Qt::darkGray, 1));
    d->ellipse->setBrush(Qt::lightGray);
    d->ellipse->setRect(0, 0, 10, 10);
    
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setZValue(1);
}

dtkComposerScenePort::~dtkComposerScenePort(void)
{
    delete d;

    d = NULL;
}

QRectF dtkComposerScenePort::boundingRect(void) const
{
    return QRectF(0, 0, 10, 10);
}

void dtkComposerScenePort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneEdge
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneEdgePrivate
{
public:
    dtkComposerScenePort *source;
    dtkComposerScenePort *destination;

public:
    QPainterPath path;
};

dtkComposerSceneEdge::dtkComposerSceneEdge(void) : QGraphicsItem(), d(new dtkComposerSceneEdgePrivate)
{
    d->source = NULL;
    d->destination = NULL;

    this->setZValue(-1);
}

dtkComposerSceneEdge::~dtkComposerSceneEdge(void)
{
    delete d;

    d = NULL;
}

QRectF dtkComposerSceneEdge::boundingRect(void) const
{
    return d->path.boundingRect();
}

void dtkComposerSceneEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(Qt::gray);

    painter->drawPath(d->path);

    painter->restore();
}

dtkComposerScenePort *dtkComposerSceneEdge::source(void)
{
    return d->source;
}

dtkComposerScenePort *dtkComposerSceneEdge::destination(void)
{
    return d->destination;
}

void dtkComposerSceneEdge::setSource(dtkComposerScenePort *port)
{
    d->source = port;

    this->adjust();
}

void dtkComposerSceneEdge::setDestination(dtkComposerScenePort *port)
{
    d->destination = port;

    this->adjust();
}

void dtkComposerSceneEdge::adjust(void)
{
    if (!d->source || !d->destination)
        return;

    if (!this->isVisible())
        return;

    QRectF rect;
    rect = d->source->boundingRect();
    QPointF start = d->source->mapToScene(rect.center());
    rect = d->destination->boundingRect();
    QPointF end = d->destination->mapToScene(rect.center());

    this->adjust(start, end);
}

void dtkComposerSceneEdge::adjust(const QPointF& start, const QPointF& end)
{
    this->prepareGeometryChange();
    
    QPointF midPoint = (start + end) / 2;

    qreal halfMid = (midPoint.x() - start.x())/2;

    QPainterPath path;
    path.moveTo(start);
    path.cubicTo(QPointF(end.x() - halfMid, start.y()), QPointF(start.x() + halfMid, end.y()), end);

    QPainterPathStroker stroker;
    stroker.setWidth(3);
    stroker.setCapStyle(Qt::RoundCap);
    d->path = stroker.createStroke(path);

    this->update();
}

bool dtkComposerSceneEdge::link(bool anyway)
{
    if(!d->source || !d->destination)
        return false;

    dynamic_cast<dtkComposerSceneNode *>(d->source->parentItem())->addOutputEdge(this);
    dynamic_cast<dtkComposerSceneNode *>(d->destination->parentItem())->addInputEdge(this);

    return true;
}

bool dtkComposerSceneEdge::unlink(void)
{
    return true;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNode
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodePrivate
{
public:
    QList<dtkComposerScenePort *>  input_ports;
    QList<dtkComposerScenePort *> output_ports;

    QList<dtkComposerSceneEdge *>  input_edges;
    QList<dtkComposerSceneEdge *> output_edges;

public:
    QRectF rect;
};

dtkComposerSceneNode::dtkComposerSceneNode(void) : QGraphicsItem(), d(new dtkComposerSceneNodePrivate)
{
    d->input_ports << new dtkComposerScenePort(this);
    d->input_ports << new dtkComposerScenePort(this);

    d->output_ports << new dtkComposerScenePort(this);

    d->rect = QRectF(0, 0, 150, 50);

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    this->layout();
}

dtkComposerSceneNode::~dtkComposerSceneNode(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNode::addInputEdge(dtkComposerSceneEdge *edge)
{
    d->input_edges << edge;
}

void dtkComposerSceneNode::addOutputEdge(dtkComposerSceneEdge *edge)
{
    d->output_edges << edge;
}

void dtkComposerSceneNode::removeInputEdge(dtkComposerSceneEdge *edge)
{
    d->input_edges.removeAll(edge);
}

void dtkComposerSceneNode::removeOutputEdge(dtkComposerSceneEdge *edge)
{
    d->output_edges.removeAll(edge);
}

QList<dtkComposerSceneEdge *> dtkComposerSceneNode::inputEdges(void)
{
    return d->input_edges;
}

QList<dtkComposerSceneEdge *> dtkComposerSceneNode::outputEdges(void)
{
    return d->output_edges;
}

QRectF dtkComposerSceneNode::boundingRect(void) const
{
    return d->rect;
}

void dtkComposerSceneNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    static qreal radius = 5.0;

    QLinearGradient gradiant(this->boundingRect().left(), this->boundingRect().top(), this->boundingRect().left(), this->boundingRect().bottom());
    gradiant.setColorAt(0.0, QColor(Qt::white));
    gradiant.setColorAt(0.3, QColor(Qt::gray));
    gradiant.setColorAt(1.0, QColor(Qt::gray).darker());

    if (this->isSelected())
        painter->setPen(QPen(Qt::magenta, 2, Qt::SolidLine));
    else
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));

    painter->setBrush(gradiant);

    painter->drawRoundedRect(this->boundingRect(), radius, radius);
}

QList<dtkComposerScenePort *> dtkComposerSceneNode::inputPorts(void)
{
    return d->input_ports;
}

QList<dtkComposerScenePort *> dtkComposerSceneNode::outputPorts(void)
{
    return d->output_ports;
}

void dtkComposerSceneNode::layout(void)
{
    int port_margin_top = 10;
    int port_margin_bottom = 10;
    int port_margin_left = 10;
    int port_spacing = 10;

    int node_width = d->rect.width();

    for(int i = 0; i < d->input_ports.count(); i++)
        d->input_ports.at(i)->setPos(QPointF(port_margin_left, i*d->input_ports.at(i)->boundingRect().height() + i*port_spacing + port_margin_top));

    for(int i = 0; i < d->output_ports.count(); i++)
        d->output_ports.at(i)->setPos(QPointF(node_width - port_margin_left - d->output_ports.at(i)->boundingRect().width(), i*d->output_ports.at(i)->boundingRect().height() + i*port_spacing + port_margin_top));

    if(d->input_ports.count() || d->output_ports.count())
        if(d->input_ports.count() >= d->output_ports.count())
            d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), d->input_ports.count() * d->input_ports.at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (d->input_ports.count()-1) * port_spacing));
        else
            d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), d->output_ports.count() * d->output_ports.at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (d->output_ports.count()-1) * port_spacing));
}

QVariant dtkComposerSceneNode::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if(change == QGraphicsItem::ItemSelectedHasChanged) {

        if(value.toBool()) {
            ; // TO SELECTED STATE
        } else {
            ; // TO UNUSELECTED STATE
        }
    }

    return QGraphicsItem::itemChange(change, value);
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkComposerScene::dtkComposerScene(QObject *parent) : QGraphicsScene(parent), d(new dtkComposerScenePrivate)
{
    d->current_edge = NULL;

    // temporary scene

    dtkComposerSceneNode *n1 = new dtkComposerSceneNode;
    dtkComposerSceneNode *n2 = new dtkComposerSceneNode;
    dtkComposerSceneNode *n3 = new dtkComposerSceneNode;

    this->addItem(n1);
    this->addItem(n2);
    this->addItem(n3);
}

dtkComposerScene::~dtkComposerScene(void)
{
    delete d;

    d = NULL;
}

void dtkComposerScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    // Managnig grabbing of selected nodes

    foreach(QGraphicsItem *item, this->selectedItems()) {

        if(dtkComposerSceneNode *node = dynamic_cast<dtkComposerSceneNode *>(item)) {

            QRectF updateRect;

            foreach(dtkComposerSceneEdge *edge, node->inputEdges()) {
                edge->adjust();
                updateRect |= edge->boundingRect();
            }
            
            foreach(dtkComposerSceneEdge *edge, node->outputEdges()) {
                edge->adjust();
                updateRect |= edge->boundingRect();
            }
            
            this->update(updateRect);
        }
    }

    // Managing grabbing of current edge

    if (d->current_edge)
        d->current_edge->adjust(d->current_edge->source()->scenePos(), event->scenePos());

    if (d->current_edge)
        this->update(d->current_edge->boundingRect());

    if (d->current_edge)
        event->accept();
}

void dtkComposerScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    dtkComposerScenePort *source = this->portAt(event->scenePos());

    if(!source)
        return;

    if(d->current_edge)
        return;

    d->current_edge = new dtkComposerSceneEdge;
    d->current_edge->setSource(source);

    this->addItem(d->current_edge);
}

void dtkComposerScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);

    if(!d->current_edge)
        return;

    if(dtkComposerScenePort *destination = this->portAt(event->scenePos()))
        d->current_edge->setDestination(destination);

    if(!d->current_edge->link()) {
        this->removeItem(d->current_edge);
        delete d->current_edge;
    } else {
        d->edges << d->current_edge;
    }
    
    d->current_edge = NULL;
}

void dtkComposerScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);
}

dtkComposerScenePort *dtkComposerScene::portAt(const QPointF& point) const
{
    QList<QGraphicsItem *> items = this->items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect);

    foreach(QGraphicsItem *item, items)
        if (dtkComposerScenePort *port = dynamic_cast<dtkComposerScenePort *>(item))
            return port;

    return NULL;
}

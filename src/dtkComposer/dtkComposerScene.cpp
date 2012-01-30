/* dtkComposerScene.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:13:25
 * Version: $Id$
 * Last-Updated: Mon Jan 30 17:42:57 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 193
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
    d->ellipse->setPen(QPen(Qt::gray, 1));
    d->ellipse->setBrush(Qt::yellow);
    d->ellipse->setRect(0, 0, 10, 10);
    
    this->setZValue(1);
}

dtkComposerScenePort::~dtkComposerScenePort(void)
{
    
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

}

void dtkComposerSceneEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(Qt::yellow);

    painter->drawPath(d->path);

    painter->restore();
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

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNode
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodePrivate
{
public:
    QList<dtkComposerScenePort *>  input_ports;
    QList<dtkComposerScenePort *> output_ports;

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

QRectF dtkComposerSceneNode::boundingRect(void) const
{
    return d->rect;
}

void dtkComposerSceneNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->isSelected())
        painter->fillRect(option->rect, Qt::red);
    else
        painter->fillRect(option->rect, Qt::magenta);
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

    qDebug() << "Done positionnign ports";

    if(d->input_ports.count() || d->output_ports.count())
        if(d->input_ports.count() >= d->output_ports.count())
            d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), d->input_ports.count() * d->input_ports.at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (d->input_ports.count()-1) * port_spacing));
        else
            d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), d->output_ports.count() * d->output_ports.at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (d->output_ports.count()-1) * port_spacing));
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkComposerScene::dtkComposerScene(QObject *parent) : QGraphicsScene(parent), d(new dtkComposerScenePrivate)
{
    // temporary scene

    dtkComposerSceneNode *n1 = new dtkComposerSceneNode;
    dtkComposerSceneNode *n2 = new dtkComposerSceneNode;
    dtkComposerSceneNode *n3 = new dtkComposerSceneNode;

    dtkComposerSceneEdge *e1 = new dtkComposerSceneEdge;
    e1->setSource(n1->outputPorts().at(0));
    e1->setDestination(n2->inputPorts().at(0));

    this->addItem(n1);
    this->addItem(n2);
    this->addItem(n3);

    this->addItem(e1);
}

dtkComposerScene::~dtkComposerScene(void)
{
    delete d;

    d = NULL;
}

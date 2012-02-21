/* dtkComposerSceneNodeControl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 15:53:59 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 21 22:21:12 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 372
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControl.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerSceneNote.h"
#include "dtkComposerScenePort.h"

class dtkComposerSceneNodeControlPrivate
{
public:
    dtkComposerSceneNodeLeaf *header;
    dtkComposerSceneNodeLeaf *footer;

public:
    QList<dtkComposerSceneNodeComposite *> blocks;

public:
    QRectF rect;

public:
    QPointF drag_point;
};

dtkComposerSceneNodeControl::dtkComposerSceneNodeControl(void) : dtkComposerSceneNode(), d(new dtkComposerSceneNodeControlPrivate)
{
    d->rect = QRectF(0, 0, 150, 50);

    d->header = NULL;
    d->footer = NULL;

// -- Development code

    dtkComposerSceneNodeLeaf *header = new dtkComposerSceneNodeLeaf;
    header->addInputPort(new dtkComposerScenePort(0, dtkComposerScenePort::Input, "variable", header));
    header->setParent(this);

    dtkComposerSceneNodeComposite *cond_block = new dtkComposerSceneNodeComposite;
    cond_block->setParent(this);
    cond_block->setTitle("Conditional");
    
    dtkComposerSceneNodeComposite *body_block = new dtkComposerSceneNodeComposite;
    body_block->setParent(this);
    body_block->setTitle("Body");

    dtkComposerSceneNodeComposite *incr_block = new dtkComposerSceneNodeComposite;
    incr_block->setParent(this);
    incr_block->setTitle("Incrementat");

    dtkComposerSceneNodeLeaf *footer = new dtkComposerSceneNodeLeaf;
    footer->addOutputPort(new dtkComposerScenePort(1, dtkComposerScenePort::Output, footer));
    footer->setParent(this);

// --

    this->setHeader(header);
    this->setFooter(footer);

    this->addBlock(cond_block);
    this->addBlock(body_block);
    this->addBlock(incr_block);

// -- Development code
}

dtkComposerSceneNodeControl::~dtkComposerSceneNodeControl(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNodeControl::wrap(dtkComposerNode *wrapee)
{
    dtkComposerNodeControl *control = dynamic_cast<dtkComposerNodeControl *>(wrapee);

    if(!control)
        return;

    dtkComposerSceneNode::wrap(wrapee);    
    
    if (d->header)
        d->header->setTitle(wrapee->titleHint());
}

QList<dtkComposerSceneNodeComposite *> dtkComposerSceneNodeControl::blocks(void)
{
    return d->blocks;
}

void dtkComposerSceneNodeControl::setHeader(dtkComposerSceneNodeLeaf *header)
{
    d->header = header;
    d->header->setEmbedded(true);
    d->header->setParent(this);
    d->header->setParentItem(this);
    d->header->setFlag(QGraphicsItem::ItemIsMovable, false);
    d->header->setFlag(QGraphicsItem::ItemIsSelectable, false);
    // d->header->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
    d->header->layout();

    this->layout();
}

void dtkComposerSceneNodeControl::setFooter(dtkComposerSceneNodeLeaf *footer)
{
    d->footer = footer;
    d->footer->setEmbedded(true);
    d->footer->setParent(this);
    d->footer->setParentItem(this);
    d->footer->setFlag(QGraphicsItem::ItemIsMovable, false);
    d->footer->setFlag(QGraphicsItem::ItemIsSelectable, false);
    // d->footer->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
    d->footer->layout();

    this->layout();
}

void dtkComposerSceneNodeControl::addBlock(dtkComposerSceneNodeComposite *block)
{
    d->blocks << block;

    block->flatten();
    block->setEmbedded(true);
    block->setParent(this);
    block->setParentItem(this);
    block->setFlag(QGraphicsItem::ItemIsMovable, false);
    block->setFlag(QGraphicsItem::ItemIsSelectable, false);
    // block->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
    block->layout();

    this->layout();
}

void dtkComposerSceneNodeControl::removeBlock(dtkComposerSceneNodeComposite *block)
{
    d->blocks.removeAll(block);

    this->layout();
}

void dtkComposerSceneNodeControl::layout(void)
{
    if(!d->header)
        return;

    if(!d->footer)
        return;

    d->header->layout();
    d->footer->layout();

    qreal h = 0;
    qreal b = (d->rect.size().height()
              -d->header->boundingRect().adjusted(2, 2, -2, -2).size().height()
              -d->footer->boundingRect().adjusted(2, 2, -2, -2).size().height())
              /d->blocks.count();

    if (d->header) {
        d->header->setPos(0, 0);
        h = d->header->boundingRect().adjusted(2, 2, -2, -2).height();
        d->header->resize(d->rect.size().width(), h);
    }

    foreach(dtkComposerSceneNodeComposite *block, d->blocks) {
        block->setPos(0, h);
        block->resize(d->rect.size().width(), b);
        h += b;
    }

    if (d->footer) {
        d->footer->setPos(0, h);
        h = d->footer->boundingRect().adjusted(2, 2, -2, -2).height();
        d->footer->resize(d->rect.size().width(), h);
    }

    this->update();
}

void dtkComposerSceneNodeControl::resize(qreal width, qreal height)
{
    Q_UNUSED(width);
    Q_UNUSED(height);
}

dtkComposerSceneNodeComposite *dtkComposerSceneNodeControl::blockAt(const QPointF& point) const
{
    QPointF position = this->mapFromScene(point);

    foreach(dtkComposerSceneNodeComposite *block, d->blocks) {

        QRectF rect = QRectF(block->pos(), block->boundingRect().size());

        if(rect.contains(position))
            return block;
    }

    return NULL;
}

QRectF dtkComposerSceneNodeControl::boundingRect(void) const
{
    return d->rect.adjusted(-2, -2, 2, 2);
}

void dtkComposerSceneNodeControl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing, false);

    if (this->isSelected()) {
        painter->setPen(QPen(Qt::magenta, 2, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(d->rect.adjusted(-2, -2, 2, 2));
    }

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));

    {
        QPointF left  = d->header->pos() + d->header->boundingRect().adjusted(2, 2, -2, -2).bottomLeft();
        QPointF right = d->header->pos() + d->header->boundingRect().adjusted(2, 2, -2, -2).bottomRight();

        painter->drawLine(left, right);
    }

    painter->setPen(QPen(Qt::black, 1, Qt::DashLine));

    for(int i = 0; i < d->blocks.count()-1; i++) {

        dtkComposerSceneNodeComposite *block = d->blocks.at(i);
        
        QPointF left  = block->pos() + block->boundingRect().adjusted(2, 2, -2, -2).bottomLeft();
        QPointF right = block->pos() + block->boundingRect().adjusted(2, 2, -2, -2).bottomRight();

        painter->drawLine(left, right);
    }

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));

    {
        QPointF left  = d->footer->pos() + d->footer->boundingRect().adjusted(2, 1, -2, -2).topLeft();
        QPointF right = d->footer->pos() + d->footer->boundingRect().adjusted(2, 1, -2, -2).topRight();

        painter->drawLine(left, right);
    }

    painter->setPen(QPen(Qt::black, 0.5, Qt::SolidLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(d->rect.adjusted(-1, -1, 0, 0));
}

void dtkComposerSceneNodeControl::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && !d->drag_point.isNull()) {
        
        QPointF delta = QPointF(event->scenePos() - d->drag_point);

        d->rect.setBottomRight(d->rect.bottomRight() + delta);

        d->drag_point = event->scenePos();

        this->layout();

        event->accept();

        return;
    }

    foreach(dtkComposerSceneNodeComposite *block, d->blocks) {
        
        QPointF delta = event->pos() - event->lastPos();
        qreal delta_x = delta.x();
        qreal delta_y = delta.y();

        foreach(dtkComposerSceneNode *node, block->nodes())
            node->moveBy(delta_x, delta_y);

        foreach(dtkComposerSceneNote *note, block->notes())
            note->moveBy(delta_x, delta_y);

        foreach(dtkComposerSceneEdge *edge, block->edges())
            edge->adjust();
    }

    QGraphicsItem::mouseMoveEvent(event);
}

void dtkComposerSceneNodeControl::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF br = d->rect.bottomRight();

    QRectF corner(br.x() - 16, br.y() - 16, 16, 16);

    if (event->button() & Qt::LeftButton && corner.contains(event->pos())) {
        d->drag_point = event->scenePos();
        event->accept();
    }

    QGraphicsItem::mousePressEvent(event);
}

void dtkComposerSceneNodeControl::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton && !d->drag_point.isNull()) {
        d->drag_point = QPointF(0, 0);
        event->accept();
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

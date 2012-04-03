/* dtkComposerSceneNodeControl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 15:53:59 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 14:35:23 2012 (+0200)
 *           By: tkloczko
 *     Update #: 509
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeLeaf.h"
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
    d->rect = QRectF(0, 0, 200, 300);

    d->header = NULL;
    d->footer = NULL;
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

    d->header = new dtkComposerSceneNodeLeaf;
    d->header->wrap(control->header());
    d->header->setParent(this);
    d->header->setTitle(wrapee->titleHint());
    this->setHeader(d->header);

    for(int i = 0; i < control->blockCount(); i++) {
    
        dtkComposerSceneNodeComposite *block = new dtkComposerSceneNodeComposite;
        block->wrap(control->block(i));
        block->setParent(this);
        // block->setTitle(block->titleHint());
        this->addBlock(block);

    }
    
    d->footer = new dtkComposerSceneNodeLeaf;
    d->footer->wrap(control->footer());
    d->footer->setParent(this);
    d->footer->setTitle("");
    this->setFooter(d->footer);

    dtkComposerSceneNode::wrap(wrapee);
}

QList<dtkComposerSceneNodeComposite *> dtkComposerSceneNodeControl::blocks(void)
{
    return d->blocks;
}

dtkComposerSceneNodeComposite *dtkComposerSceneNodeControl::block(const QString& title)
{
    foreach(dtkComposerSceneNodeComposite *block, d->blocks)
        if(block->title() == title)
            return block;

    return NULL;
}

dtkComposerSceneNodeLeaf *dtkComposerSceneNodeControl::header(void)
{
    return d->header;
}

dtkComposerSceneNodeLeaf *dtkComposerSceneNodeControl::footer(void)
{
    return d->footer;
}

void dtkComposerSceneNodeControl::setHeader(dtkComposerSceneNodeLeaf *header)
{
    d->header = header;
    d->header->setEmbedded(true);
    d->header->setParent(this);
    d->header->setParentItem(this);
    d->header->setFlag(QGraphicsItem::ItemIsMovable, false);
    d->header->setFlag(QGraphicsItem::ItemIsSelectable, false);
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
        block->layout();
        block->setPos(0, h);
        block->resize(d->rect.size().width(), b);
        block->obfuscate();
        block->layout();
        h += b;
    }

    if (d->footer) {
        d->footer->setPos(0, h);
        h = d->footer->boundingRect().adjusted(2, 2, -2, -2).height();
        d->footer->resize(d->rect.size().width(), h);
    }

// /////////////////////////////////////////////////////////////////
// Redraw parent
// /////////////////////////////////////////////////////////////////

    dtkComposerSceneNode *node = this;

    if (dtkComposerSceneNodeComposite *parent = dynamic_cast<dtkComposerSceneNodeComposite *>(node->parent())) {

        if(!parent->root()){

            if (parent->entered() || (parent->flattened() && !parent->embedded()))
                parent->layout();
        }
    }

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

    this->update();
}

void dtkComposerSceneNodeControl::resize(qreal width, qreal height)
{
    d->rect.setWidth(width);
    d->rect.setHeight(height);
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
    if (event->buttons() && Qt::LeftButton && !d->drag_point.isNull()) {

        QGraphicsItem::prepareGeometryChange();

        QPointF delta = QPointF(event->scenePos() - d->drag_point);

        d->rect.setBottomRight(d->rect.bottomRight() + delta);

        d->drag_point = event->scenePos();

        this->layout();

        qreal delta_y = 0;

        for(int i = 0; i < d->blocks.count(); i++) {            
            
            foreach(dtkComposerSceneNode *node, d->blocks.at(i)->nodes())
                node->moveBy(0, delta_y);
            
            foreach(dtkComposerSceneNote *note, d->blocks.at(i)->notes())
                note->moveBy(0, delta_y);
            
            foreach(dtkComposerSceneEdge *edge, d->blocks.at(i)->edges())
                edge->adjust();

            delta_y += delta.y()/d->blocks.count();
        }

        event->accept();

        return;
    }

    QPointF delta = event->pos() - event->lastPos();
    qreal delta_x = delta.x();
    qreal delta_y = delta.y();
    
    QStack<dtkComposerSceneNodeComposite *> nodes; foreach(dtkComposerSceneNodeComposite *block, this->blocks()) nodes.push(block);

    while(!nodes.isEmpty()) {

        dtkComposerSceneNodeComposite *n = nodes.pop();

        foreach(dtkComposerSceneNode *node, n->nodes()) {
            node->moveBy(delta_x, delta_y);
            
            if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node))
                foreach(dtkComposerSceneNodeComposite *block, control->blocks())
                    nodes.push(block);
            
            if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node))
                nodes.push(composite);
        }
        
        foreach(dtkComposerSceneNote *note, n->notes())
            note->moveBy(delta_x, delta_y);
        
        foreach(dtkComposerSceneEdge *edge, n->edges())
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

/* dtkComposerSceneNodeControl.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 15:53:59 2012 (+0100)
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
#include "dtkComposerSceneNodeHandle.h"
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
    QList<dtkComposerSceneNodeHandle *> handles;

public:
    QHash<dtkComposerSceneNodeComposite *, QRectF> sizes;

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

    if(d->blocks.count() > 1) {
        dtkComposerSceneNodeComposite *top = d->blocks.at(d->blocks.count()-2);
        dtkComposerSceneNodeComposite *bot = d->blocks.at(d->blocks.count()-1);

        dtkComposerSceneNodeHandle *handle = new dtkComposerSceneNodeHandle(this);
        handle->setTopBlock(top);
        handle->setBotBlock(bot);

        d->handles << handle;
    }

    this->layout();
}

void dtkComposerSceneNodeControl::removeBlock(dtkComposerSceneNodeComposite *block)
{
    int block_id = d->blocks.indexOf(block);
    d->blocks.removeAt(block_id);
    delete d->handles.takeAt(block_id - 1);

    if (d->blocks.count() > 1) {
        if (block_id != d->blocks.count()) {
            dtkComposerSceneNodeComposite *top = d->blocks.at(block_id - 1);
            dtkComposerSceneNodeComposite *bot = d->blocks.at(block_id);
            dtkComposerSceneNodeHandle *handle = d->handles.at(block_id - 1);
            handle->setTopBlock(top);
            handle->setBotBlock(bot);
        }
    }

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

    if(d->sizes.empty() || d->sizes.count() != d->blocks.count()) {
        d->sizes.clear();
        foreach(dtkComposerSceneNodeComposite *block, d->blocks) {
            d->sizes.insert(block, QRectF(0, h, d->rect.size().width(), b));
            h += b;
        }
    }

    foreach(dtkComposerSceneNodeComposite *block, d->blocks) {
        block->layout();
        block->setPos(d->sizes.value(block).topLeft());
        block->resize(d->sizes.value(block).size());
        block->obfuscate();
        block->layout();
    }

    foreach(dtkComposerSceneNodeHandle *handle, d->handles)
        handle->layout();

    if(d->blocks.count())
        h = d->blocks.last()->boundingRect().top() + d->blocks.last()->boundingRect().height();

    if (d->footer) {
        h = d->footer->boundingRect().adjusted(2, 2, -2, -2).height();
        d->footer->setPos(0, this->boundingRect().bottom()-h-2);
        d->footer->resize(d->rect.size().width(), h);
    }

// /////////////////////////////////////////////////////////////////
// Redraw parent
// /////////////////////////////////////////////////////////////////

    dtkComposerSceneNode *node = this;

    if (dtkComposerSceneNodeComposite *parent = dynamic_cast<dtkComposerSceneNodeComposite *>(node->parent())) {

        if(parent->visible())
            parent->layout();
    }

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

    this->update();
}

void dtkComposerSceneNodeControl::setBlockSize(dtkComposerSceneNodeComposite *block, qreal x, qreal y, qreal w, qreal h)
{
    if(!d->sizes.keys().contains(block))
        return;

    d->sizes[block] = QRectF(x, y, w, h);

    // this->layout(); // <- Not a mistake, do not uncomment!
}

void dtkComposerSceneNodeControl::resizeBlock(dtkComposerSceneNodeComposite *block, qreal dx, qreal dy)
{
    if(!d->sizes.keys().contains(block))
        return;

    QRectF rect = d->sizes.value(block);
    rect.setWidth(rect.width()+dx);
    rect.setHeight(rect.height()+dy);

    d->sizes[block] = rect;

    this->layout();
}

void dtkComposerSceneNodeControl::moveBlock(dtkComposerSceneNodeComposite *block, qreal dx, qreal dy)
{
    if(!d->sizes.keys().contains(block))
        return;

    QRectF rect = d->sizes.value(block);
    qreal x = rect.x()+dx;
    qreal y = rect.y()+dy;
    qreal w = rect.width()-dx;
    qreal h = rect.height()-dy;

    d->sizes[block] = QRectF(x, y, w, h);

    this->layout();
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

    painter->setPen(QPen(Qt::white, 1, Qt::DashLine));

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
    QGraphicsItem::prepareGeometryChange();

    if (event->buttons() && Qt::LeftButton && !d->drag_point.isNull()) {

        QPointF delta = QPointF(event->scenePos() - d->drag_point);

        d->rect.setBottomRight(d->rect.bottomRight() + delta);

// /////////////////////////////////////////////////////////////////

    for(int i = 0; i < d->blocks.count(); i++) {

        dtkComposerSceneNodeComposite *previous = NULL;
        dtkComposerSceneNodeComposite *current = d->blocks.at(i);

        if(i >= 1)
            previous = d->blocks.at(i-1);

        QRectF size = d->sizes.value(current);

        qreal x = size.x();
        qreal y = size.y();
        qreal w = size.width();
        qreal h = size.height();

        if(previous)
            y = d->sizes.value(previous).y() + d->sizes.value(previous).height();

        w  = d->rect.width();
        h += delta.y()/d->sizes.count();

        d->sizes[current] = QRectF(x, y, w, h);
    }

// /////////////////////////////////////////////////////////////////

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

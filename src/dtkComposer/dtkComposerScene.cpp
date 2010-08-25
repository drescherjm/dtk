/* dtkComposerScene.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:06:06 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Aug 17 13:22:23 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 349
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeFactory.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerScene.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkLog.h>

class dtkComposerScenePrivate
{
public:
    dtkComposerEdge *current_edge;
    dtkComposerNodeFactory *factory;

    bool modified;
};

dtkComposerScene::dtkComposerScene(QObject *parent) : QGraphicsScene(parent), d(new dtkComposerScenePrivate)
{
    d->current_edge = NULL;
    d->factory = new dtkComposerNodeFactory;
    d->modified = false;

    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
}

dtkComposerScene::~dtkComposerScene(void)
{
    delete d->factory;
    delete d;

    d = NULL;
}

QList<dtkComposerEdge *> dtkComposerScene::edges(void)
{
    QList<dtkComposerEdge *> list;

    foreach(QGraphicsItem *item, this->items())
        if (dtkComposerEdge *edge = dynamic_cast<dtkComposerEdge *>(item))
            list << edge;

    return list;
}

QList<dtkComposerNode *> dtkComposerScene::nodes(void)
{
    QList<dtkComposerNode *> list;

    foreach(QGraphicsItem *item, this->items())
        if (dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item))
            list << node;

    return list;
}

QList<dtkComposerNode *> dtkComposerScene::nodes(QString name)
{
    QList<dtkComposerNode *> list;

    foreach(QGraphicsItem *item, this->items())
        if (dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item))
            if(node->object()->name() == name)
                list << node;

    return list;
}

QList<dtkComposerNodeProperty *> dtkComposerScene::properties(void)
{
    QList<dtkComposerNodeProperty *> list;

    foreach(QGraphicsItem *item, this->items())
        if (dtkComposerNodeProperty *property = dynamic_cast<dtkComposerNodeProperty *>(item))
            list << property;

    return list;
}

QList<dtkComposerNodeProperty *> dtkComposerScene::properties(QString name)
{
    QList<dtkComposerNodeProperty *> list;

    foreach(QGraphicsItem *item, this->items())
        if (dtkComposerNodeProperty *property = dynamic_cast<dtkComposerNodeProperty *>(item))
            if(property->name() == name)
                list << property;

    return list;
}

void dtkComposerScene::clear(void)
{
    foreach(dtkComposerNode *node, this->nodes())
        delete node;
}

bool dtkComposerScene::isModified(void)
{
    return d->modified;
}

void dtkComposerScene::setModified(bool modified)
{
    d->modified = modified;

    if(d->modified)
        emit compositionChanged();
}

void dtkComposerScene::addEdge(dtkComposerEdge *edge)
{
    this->addItem(edge);

    this->setModified(true);
}

void dtkComposerScene::addNode(dtkComposerNode *node)
{
    this->addItem(node);

    emit nodeAdded(node);

    this->setModified(true);
}

void dtkComposerScene::removeNode(dtkComposerNode *node)
{
    foreach(dtkComposerEdge *edge, node->inputEdges())
        delete edge; // this->removeItem(edge);
    
    foreach(dtkComposerEdge *edge, node->outputEdges())
        delete edge; // this->removeItem(edge);
    
    // this->removeItem(node);
    
    delete node;

    this->setModified(true);
}

dtkComposerNode *dtkComposerScene::createNode(QString type, QPointF position)
{
    if(dtkComposerNode *node = d->factory->create(type)) {
        node->setPos(position);
        this->addNode(node);
        return node;
    } else {
        qDebug() << "Unable to create node for type" << type;
        return NULL;
    }
}

void dtkComposerScene::setFactory(dtkComposerNodeFactory *factory)
{
    d->factory = factory;
}

void dtkComposerScene::startEvaluation(void)
{
    foreach(QGraphicsItem *item, this->selectedItems())
        if(dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item))
            node->update();

    emit evaluationStarted();
}

void dtkComposerScene::stopEvaluation(void)
{
    emit evaluationStopped();
}

dtkComposerNode *dtkComposerScene::nodeAt(const QPointF& point) const
{
    QList<QGraphicsItem *> items = this->items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect);

    foreach(QGraphicsItem *item, items)
        if (dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item))
            return node;

    return NULL;
}

dtkComposerNodeProperty *dtkComposerScene::propertyAt(const QPointF& point) const
{
    QList<QGraphicsItem *> items = this->items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect);

    foreach(QGraphicsItem *item, items)
        if (dtkComposerNodeProperty *property = dynamic_cast<dtkComposerNodeProperty *>(item))
            return property;

    return NULL;
}

void dtkComposerScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
}

void dtkComposerScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();
}

void dtkComposerScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
}

void dtkComposerScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QUrl url = event->mimeData()->urls().first();

    if (url.scheme() != "type") {
        event->ignore();
        return;
    }

    this->createNode(url.path(), event->pos());

    event->acceptProposedAction();
}

void dtkComposerScene::keyPressEvent(QKeyEvent *event)
{
    // Item deletion - Delete | Backspace

    if(event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete)
        foreach(QGraphicsItem *item, this->selectedItems())
            if(dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item))
                this->removeNode(node);

    // Pipeline update - U

    if(event->key() == Qt::Key_U)
        this->startEvaluation();
}

void dtkComposerScene::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void dtkComposerScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);

    if (d->current_edge) {
        d->current_edge->adjust(d->current_edge->start(), mouseEvent->scenePos());
        this->update(QRectF(d->current_edge->start(), mouseEvent->scenePos()));
    }
}

void dtkComposerScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);

    dtkComposerNodeProperty *property = propertyAt(mouseEvent->scenePos());

    if(!property)
        return;

    if (property->type() == dtkComposerNodeProperty::Output /*&& property->count() == 0*/) {
        delete d->current_edge;
        d->current_edge = new dtkComposerEdge;
        this->addItem(d->current_edge);
        d->current_edge->setSource(property);
        d->current_edge->show();
        return;
    }

    if (property->type() == dtkComposerNodeProperty::Input /*&& property->count() > 0*/) {
        d->current_edge = property->edge();
        d->current_edge->unlink();
        return;
    }
}

void dtkComposerScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);

    if (!d->current_edge)
        return;

    dtkComposerNodeProperty *property = propertyAt(mouseEvent->scenePos());
    
    if (d->current_edge->source() == property) {
        delete d->current_edge;
        d->current_edge = 0;
    } else {
        d->current_edge->setDestination(property);
        if (!d->current_edge->link())
            delete d->current_edge;
        d->current_edge = 0;
    }

    this->setModified(true);
}

void dtkComposerScene::onSelectionChanged(void)
{
    foreach(QGraphicsItem *item, this->selectedItems()) {
        if(dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item)) {
            if(dtkAbstractData *data = dynamic_cast<dtkAbstractData *>(node->object()))
                emit dataSelected(data);
            if(dtkAbstractProcess *process = dynamic_cast<dtkAbstractProcess *>(node->object()))
                emit processSelected(process);
            if(dtkAbstractView *view = dynamic_cast<dtkAbstractView *>(node->object()))
                emit viewSelected(view);
        }
    }
}

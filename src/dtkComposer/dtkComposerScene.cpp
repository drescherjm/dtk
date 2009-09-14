/* dtkComposerScene.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:06:06 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Sep 11 23:39:06 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 167
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
};

dtkComposerScene::dtkComposerScene(QObject *parent) : QGraphicsScene(parent), d(new dtkComposerScenePrivate)
{
    d->current_edge = NULL;

    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
}

dtkComposerScene::~dtkComposerScene(void)
{
    delete d;

    d = NULL;
}

void dtkComposerScene::addNode(const QString& type)
{
    Q_UNUSED(type);

    dtkComposerNode *node = NULL;

    if(dtkAbstractData *data = dtkAbstractDataFactory::instance()->create(type))
        node = data->node();

    if(dtkAbstractProcess *process = dtkAbstractProcessFactory::instance()->create(type))
        node = process->node();

    if(dtkAbstractView *view = dtkAbstractViewFactory::instance()->create(type))
        node = view->node();

    if (node)
        this->addItem(node);
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

void dtkComposerScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);

    if (d->current_edge)
        d->current_edge->adjust(d->current_edge->start(), mouseEvent->scenePos());
}

void dtkComposerScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);

    dtkComposerNodeProperty *property = propertyAt(mouseEvent->scenePos());

    if(!property)
        return;

    if (property->type() == dtkComposerNodeProperty::Output && property->count() == 0) {
        delete d->current_edge;
        d->current_edge = new dtkComposerEdge;
        this->addItem(d->current_edge);
        d->current_edge->setSource(property);
        d->current_edge->show();
        return;
    }

    if (property->type() == dtkComposerNodeProperty::Input && property->count() > 0) {
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

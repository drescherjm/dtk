/* dtkComposerScene.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:06:06 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Dec  1 12:12:20 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 791
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

// /////////////////////////////////////////////////////////////////
// dtkComposerScenePrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerScenePrivate
{
public:
    dtkComposerEdge *edge(dtkComposerEdge *edge);

public:
    dtkComposerNode *current_node; // current_node is NULL for the root, !NULL when inside a composite node.
    dtkComposerEdge *current_edge;

    dtkComposerNodeFactory *factory;

    bool modified;

    QList<dtkComposerNode *> nodes;
    QList<dtkComposerEdge *> edges;

    // QList<dtkComposerNodeProperty *>  current_input_properties; // composite node's view  left_property_area items
    // QList<dtkComposerNodeProperty *> current_output_properties; // composite node's view right_property_area items
};

dtkComposerEdge *dtkComposerScenePrivate::edge(dtkComposerEdge *edge)
{
    foreach(dtkComposerEdge *e, this->edges)
        if(edge->source() == e->source() && edge->destination() == e->destination())
            return e;

    return NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerScene
// /////////////////////////////////////////////////////////////////

dtkComposerScene::dtkComposerScene(QObject *parent) : QGraphicsScene(parent), d(new dtkComposerScenePrivate)
{
    d->current_edge = NULL;
    d->current_node = NULL;

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
    return d->nodes;
}

QList<dtkComposerNode *> dtkComposerScene::nodes(QString name)
{
    QList<dtkComposerNode *> list;

    foreach(dtkComposerNode *node, d->nodes)
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

    d->edges << edge;

    this->setModified(true);
}

void dtkComposerScene::addNode(dtkComposerNode *node)
{
    this->addItem(node);

    d->nodes << node;

    emit nodeAdded(node);

    this->setModified(true);
}

void dtkComposerScene::removeNode(dtkComposerNode *node)
{
    d->nodes.removeAll(node);

    foreach(dtkComposerEdge *edge, node->inputEdges()) {
        d->edges.removeAll(d->edge(edge));
        delete edge;
    }
    
    foreach(dtkComposerEdge *edge, node->outputEdges()) {
        d->edges.removeAll(d->edge(edge));
        delete edge;
    }
    
    dtkComposerNode *n = node;

    while(dtkComposerNode *parent = n->parentNode()) {

        parent->removeChildNode(node);

        foreach(dtkComposerNodeProperty *property, parent->inputProperties()) {
            if(property->clonedFrom() == node) {                
                parent->removeInputProperty(property);
                this->removeItem(property);
                delete property;
            }
        }

        foreach(dtkComposerNodeProperty *property, parent->outputProperties()) {
            if(property->clonedFrom() == node) {
                parent->removeOutputProperty(property);
                this->removeItem(property);
                delete property;
            }
        }

        n = parent;
    }

    delete node;

    this->setModified(true);
}

//! Group creation. Creates a composite node.
/*! 
 * \param nodes The list of nodes to be grouped together. Beware not
 * to group a not together with a composite node the node is a child
 * of.
 * 
 * \return The composite node that form the group.
 */

dtkComposerNode *dtkComposerScene::createGroup(QList<dtkComposerNode *> nodes)
{
    dtkComposerNode *group = new dtkComposerNode;
    group->setTitle("Composite node");
    group->setType("dtkComposerNodeComposite");
    group->setKind(dtkComposerNode::Composite);
    group->setParentNode(d->current_node);

    if (d->current_node)
        d->current_node->addChildNode(group);

    foreach(dtkComposerNode *node, nodes) {

        if(dtkComposerNode *parent = node->parentNode())
            parent->removeChildNode(node);

        node->setParentNode(group);
        node->hide();

        foreach(dtkComposerNodeProperty *property, node->inputProperties())
            group->addInputProperty(property->clone(group));

        foreach(dtkComposerNodeProperty *property, node->outputProperties())
            group->addOutputProperty(property->clone(group));

        this->removeItem(node);

        group->addChildNode(node);
    }

    this->addNode(group);
    this->updateEdgesVisibility();
    this->setModified(true);

    return group;
}

dtkComposerNode *dtkComposerScene::createNode(QString type, QPointF position)
{
    if(dtkComposerNode *node = d->factory->create(type)) {
        node->setPos(position);
        node->setParentNode(d->current_node);

        if (d->current_node) {
            d->current_node->addChildNode(node);
            
            foreach(dtkComposerNodeProperty *property, node->inputProperties())
                d->current_node->addInputProperty(property->clone(d->current_node));
            
            foreach(dtkComposerNodeProperty *property, node->outputProperties())
                d->current_node->addOutputProperty(property->clone(d->current_node));
        }

        this->addNode(node);

        return node;

    } else {

        return NULL;
    }
}

void dtkComposerScene::explodeGroup(dtkComposerNode *node)
{
    if(!node)
        return;
    
    if(node->kind() != dtkComposerNode::Composite) {
        qDebug() << "Only composite nodes can be ungrouped.";
        return;
    }

    foreach(dtkComposerNode *child, node->childNodes()) {

        node->removeChildNode(child);

        child->setParentNode(node->parentNode());
        child->show();

        if (node->parentNode())
            node->parentNode()->addChildNode(child);

        this->addItem(child);
    }

    this->removeNode(node);
    this->setModified(true);
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

void dtkComposerScene::setCurrentNode(dtkComposerNode *node)
{
    d->current_node = node;

    // foreach(dtkComposerNodeProperty *property, d->current_input_properties)
    //     delete property;
    
    // d->current_input_properties.clear();

    // foreach(dtkComposerNodeProperty *property, d->current_output_properties)
    //     delete property;
    
    // d->current_output_properties.clear();

    // if(!node)
    //     return;

    // foreach(dtkComposerNodeProperty *property, d->current_node->inputProperties()) {
    //     dtkComposerNodeProperty *clone = property->clone();
    //     this->addItem(clone);
    //     d->current_input_properties << clone;
    // }

    // foreach(dtkComposerNodeProperty *property, d->current_node->outputProperties()) {
    //     dtkComposerNodeProperty *clone = property->clone();
    //     this->addItem(clone);
    //     d->current_output_properties << clone;
    // }
}

void dtkComposerScene::hideAllNodes(void)
{
    foreach(QGraphicsItem *item, this->items()) {
        if(dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item)) {
            if(node->isVisible()) {
                node->hide();
                this->removeItem(node);
            }
        }
    }
}

void dtkComposerScene::showAllNodes(void)
{
    foreach(dtkComposerNode *node, d->nodes) {
        if(!node->parentNode()) {
            node->show();
            this->addItem(node);
        }
    }
}

void dtkComposerScene::showChildNodes(dtkComposerNode *node)
{
    node->show();
    this->addItem(node);

    foreach(dtkComposerNode *child, node->childNodes()) {
        child->show();
        // this->addItem(child);
    }
}

void dtkComposerScene::updateEdgesVisibility(void)
{
    foreach(dtkComposerEdge *edge, d->edges) {
        
        if (edge->source()->node()->isVisible() && edge->destination()->node()->isVisible() && !edge->isVisible()) {
            edge->show();
            this->addItem(edge);
        }

        if(!edge->source()->node()->isVisible() && edge->destination()->node()->isVisible() && edge->isVisible()) {
            edge->hide();
            this->removeItem(edge);
        }

        if(edge->source()->node()->isVisible() && !edge->destination()->node()->isVisible() && edge->isVisible()) {
            edge->hide();
            this->removeItem(edge);
        }

        if(!edge->source()->node()->isVisible() && !edge->destination()->node()->isVisible() && edge->isVisible()) {
            edge->hide();
            this->removeItem(edge);
        }
    }
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

    this->update();
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

        if (d->current_edge = property->edge())
            d->current_edge->unlink();

        d->edges.removeAll(d->edge(d->current_edge));

        return;
    }

    this->update();
}

void dtkComposerScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);

    if (!d->current_edge)
        return;

    dtkComposerNodeProperty *property = propertyAt(mouseEvent->scenePos());
    
    if (d->current_edge->source() == property) {

        delete d->current_edge;

        d->current_edge = NULL;

    } else {
        d->current_edge->setDestination(property);

        if (!d->current_edge->link()) {

            delete d->current_edge;

        } else {

            dtkComposerEdge *edge = d->current_edge;

            d->edges << edge;
        }

        d->current_edge = NULL;
    }

    this->setModified(true);
}

void dtkComposerScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    dtkComposerNode *node = nodeAt(mouseEvent->scenePos());

    if(!node)
        return;

    if(!(mouseEvent->buttons() & Qt::LeftButton))
        return;

    if(!node->isGhost()) {

        if(node->kind() != dtkComposerNode::Composite)
            return;
                
        node->setGhost(true);

        this->hideAllNodes();
        this->showChildNodes(node);
        this->updateEdgesVisibility();
        this->setCurrentNode(node);

        emit pathChanged(d->current_node);

    } else {
     
        if(dtkComposerNode *parent = node->parentNode()) {
            
            if(parent->kind() != dtkComposerNode::Composite)
                return;

            node->setGhost(false);
            parent->setGhost(true);
       
            this->hideAllNodes();
            this->showChildNodes(parent);
            this->updateEdgesVisibility();
            this->setCurrentNode(parent);
            
            emit pathChanged(d->current_node);
            
        } else {

            node->setGhost(false);
            
            this->hideAllNodes();
            this->showAllNodes();
            this->updateEdgesVisibility();
            this->setCurrentNode(NULL);
            
            emit pathChanged(d->current_node);
        }
    }
}

void dtkComposerScene::onSelectionChanged(void)
{
    foreach(QGraphicsItem *item, this->selectedItems()) {

        if(dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item)) {

            emit nodeSelected(node);

            if(dtkAbstractData *data = dynamic_cast<dtkAbstractData *>(node->object()))
                emit dataSelected(data);

            if(dtkAbstractProcess *process = dynamic_cast<dtkAbstractProcess *>(node->object()))
                emit processSelected(process);

            if(dtkAbstractView *view = dynamic_cast<dtkAbstractView *>(node->object()))
                emit viewSelected(view);
        }
    }

    if(this->selectedItems().count() == 0)
        emit selectionCleared();
}

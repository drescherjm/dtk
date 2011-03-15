/* dtkComposerScene.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:06:06 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Mar 15 14:43:47 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 1727
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeFactory.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNote.h"
#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"

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
    d->grabber_node = NULL;
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

QList<dtkComposerNote *> dtkComposerScene::notes(void)
{
    return d->notes;
}

QList<dtkComposerEdge *> dtkComposerScene::edges(void)
{
    return d->edges;
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

//! Start nodes
/*! 
 *  Returns the list of nodes that are not within a composite nor
 *  within a control block, with no input edges
 */

QList<dtkComposerNode *> dtkComposerScene::startNodes(void)
{
    QList<dtkComposerNode *> list;

    foreach(dtkComposerNode *node, d->nodes)
        if(!node->parentNode() && !node->parentItem() && node->inputEdges().count() == 0)
            list << node;

    return list;
}

QList<dtkComposerNode *> dtkComposerScene::endNodes(void)
{
    QList<dtkComposerNode *> list;

    foreach(dtkComposerNode *node, d->nodes)
        if(!node->parentNode() && !node->parentItem()  && node->outputEdges().count() == 0)
            list << node;

    return list;
}

void dtkComposerScene::touch(void)
{
    this->updateEdgesVisibility();
}

void dtkComposerScene::clear(void)
{
    foreach(dtkComposerNode *node, this->nodes())
        delete node;

    foreach(dtkComposerNote *note, this->notes())
        delete note;

    d->nodes.clear();
    d->notes.clear();
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

void dtkComposerScene::addNote(dtkComposerNote *note)
{
    this->addItem(note);

    d->notes << note;

    this->setModified(true);
}

void dtkComposerScene::removeEdge(dtkComposerEdge *edge)
{
    edge->unlink();

    d->edges.removeAll(edge);

    delete edge;
}

void dtkComposerScene::removeNode(dtkComposerNode *node)
{
    foreach(dtkComposerEdge *edge, node->inputEdges()) {
        d->edges.removeAll(d->edge(edge));
        delete edge;
    }
    
    foreach(dtkComposerEdge *edge, node->outputEdges()) {
        d->edges.removeAll(d->edge(edge));
        delete edge;
    }

    foreach(dtkComposerEdge *edge, node->inputGhostEdges()) {
        d->edges.removeAll(d->edge(edge));
        delete edge;
    }
    
    foreach(dtkComposerEdge *edge, node->outputGhostEdges()) {
        d->edges.removeAll(d->edge(edge));
        delete edge;
    }

    dtkComposerNode *n = node;
    dtkComposerNode *parent;

    while(n->parentNode()) {

        parent = n->parentNode();

        parent->removeChildNode(node);

        foreach(dtkComposerNodeProperty *property, parent->inputProperties()) {
            if(property->clonedFrom() == node) {         
                foreach(dtkComposerEdge *edge, parent->inputEdges()) {
                    if(edge->destination() == property) {
                        d->edges.removeAll(d->edge(edge));
                        delete edge;
                    }
                }         
                foreach(dtkComposerEdge *edge, parent->inputGhostEdges()) {
                    if(edge->source() == property) {
                        d->edges.removeAll(d->edge(edge));
                        delete edge;
                    }
                }
                parent->removeInputProperty(property);
                delete property;
            }
        }

        foreach(dtkComposerNodeProperty *property, parent->outputProperties()) {
            if(property->clonedFrom() == node) {                
                foreach(dtkComposerEdge *edge, parent->outputEdges()) {
                    if(edge->source() == property) {
                        d->edges.removeAll(d->edge(edge));
                        delete edge;
                    }
                }               
                foreach(dtkComposerEdge *edge, parent->outputGhostEdges()) {
                    if(edge->destination() == property) {
                        d->edges.removeAll(d->edge(edge));
                        delete edge;
                    }
                }
                parent->removeOutputProperty(property);
                delete property;
            }
        }

        n = parent;
    }

    // --

    foreach(dtkComposerNode *child, node->childNodes()) {

        if(child->childNodes().count()) {

            foreach(dtkComposerNode *child1, child->childNodes()) {
                
                if(child1->childNodes().count()) {
                    
                    foreach(dtkComposerNode *child2, child1->childNodes()) {
                        
                        if(child2->childNodes().count()) {
                            
                            foreach(dtkComposerNode *child3, child2->childNodes()) {
                                
                                if(child3->childNodes().count()) {
                                    
                                    foreach(dtkComposerNode *child4, child3->childNodes()) {
                                        
                                        if(child4->childNodes().count()) {
                                            
                                            foreach(dtkComposerNode *child5, child4->childNodes()) {
                                                
                                                if(child5->childNodes().count()) {
                                                    
                                                    foreach(dtkComposerNode *child6, child5->childNodes()) {
                                                        
                                                        d->nodes.removeAll(child6);
                                                    }
                                                    
                                                }
                                                
                                                d->nodes.removeAll(child5);
                                            }
                                            
                                        }
                                        
                                        d->nodes.removeAll(child4);
                                    }
                                    
                                }
                                
                                d->nodes.removeAll(child3);
                            }
                            
                        }
                        
                        d->nodes.removeAll(child2);
                    }
                    
                }
                
                d->nodes.removeAll(child1);
            }
            
        }
        
        d->nodes.removeAll(child);
    }

    // --

    d->nodes.removeAll(node);
    
    delete node;

    this->setModified(true);
}

void dtkComposerScene::removeNote(dtkComposerNote *note)
{
    d->notes.removeAll(note);

    delete note;
}

//! Group creation. Creates a composite node.
/*! 
 * \param nodes The list of nodes to be grouped together. Beware not
 * to group a not together with a composite node the node is a child
 * of.
 * 
 * \return The composite node that form the group.
 */

dtkComposerNode *dtkComposerScene::createGroup(QList<dtkComposerNode *> nodes, QPointF position)
{
    dtkComposerNode *group = new dtkComposerNode;
    group->setTitle("Composite node");
    group->setType("dtkComposerNodeComposite");
    group->setKind(dtkComposerNode::Composite);
    group->setParentNode(d->current_node);
    group->setPos(position);

    if (d->current_node)
        d->current_node->addChildNode(group);

    foreach(dtkComposerNode *node, nodes) {

        foreach(dtkComposerEdge *edge, node->inputEdges()) {
            d->edges.removeAll(edge);
            delete edge;
        }
        
        foreach(dtkComposerEdge *edge, node->outputEdges()) {
            d->edges.removeAll(edge);
            delete edge;
        }
       
        if(dtkComposerNode *parent = node->parentNode())
            parent->removeChildNode(node);

        node->removeAllEdges();
        node->setParentNode(group);
        node->hide();

        foreach(dtkComposerNodeProperty *property, node->inputProperties())
            group->addInputProperty(property->clone(group));

        foreach(dtkComposerNodeProperty *property, node->outputProperties())
            group->addOutputProperty(property->clone(group));

        group->addChildNode(node);
    }

    this->addNode(group);
    this->updateEdgesVisibility();
    this->setModified(true);

    // QGraphicsScene::update();

    return group;
}

dtkComposerNode *dtkComposerScene::createNode(QString type, QPointF position)
{
    if(dtkComposerNode *node = d->factory->create(type)) {
        node->setPos(position);
        node->setParentNode(d->current_node);

        if (d->current_node)
            d->current_node->addChildNode(node);

        dtkComposerNode *n = d->current_node;

        while (n) {
            
            foreach(dtkComposerNodeProperty *property, node->inputProperties())
                n->addInputProperty(property->clone(n));
            
            foreach(dtkComposerNodeProperty *property, node->outputProperties())
                n->addOutputProperty(property->clone(n));
            
            n = n->parentNode();

        }

        this->addNode(node);

        return node;

    } else {

        return NULL;
    }
}

dtkComposerNote *dtkComposerScene::createNote(QString text, QPointF position, QSizeF size)
{
    dtkComposerNote *note = new dtkComposerNote(d->current_node);
    
    if(!text.isNull())
        note->setText(text);

    if(!position.isNull())
        note->setPos(position);

    if(size.isValid() && !size.isNull())
        note->setSize(size);

    this->addNote(note);

    return note;
}

void dtkComposerScene::explodeGroup(dtkComposerNode *node)
{
    if(!node)
        return;
    
    if(node->kind() != dtkComposerNode::Composite) {
        qDebug() << "Only composite nodes can be ungrouped.";
        return;
    }
    
    // --- When node is Ghost, we first go to the parent level

    if(node->isGhost()) {
 
        if(dtkComposerNode *parent = node->parentNode()) {
            
            if(parent->kind() != dtkComposerNode::Composite)
                return;

            node->setGhost(false);
            parent->setGhost(true);
       
            this->hideAllNodes();
            this->showChildNodes(parent);
            this->updateEdgesVisibility();
            this->setCurrentNode(parent);
            
            emit centerOn(parent->sceneBoundingRect().center());
            // emit fitInView(parent->sceneBoundingRect());
            emit pathChanged(d->current_node);
            
        } else {

            node->setGhost(false);
            
            this->hideAllNodes();
            this->showAllNodes();
            this->updateEdgesVisibility();
            this->setCurrentNode(NULL);
            
            emit centerOn(this->sceneRect().center());
            // emit fitInView(this->sceneRect());
            emit pathChanged(d->current_node);
        }

    }

    foreach(dtkComposerNode *child, node->childNodes()) {

        node->removeChildNode(child);

        child->setParentNode(node->parentNode());
        child->show();

        if (node->parentNode())
            node->parentNode()->addChildNode(child);

        foreach(dtkComposerEdge *ghost, node->inputGhostEdges()) {
            if(ghost->destination()->node() == child) {
                foreach(dtkComposerEdge *input, node->inputEdges()) {
                    dtkComposerEdge *e = new dtkComposerEdge;
                    e->setSource(input->source());
                    e->setDestination(ghost->destination());
                    this->addItem(e);
                    e->show();
                    e->source()->node()->addOutputEdge(e, e->source());
                    child->addInputEdge(e, e->destination());
                }
            }
        } 

        foreach(dtkComposerEdge *ghost, node->outputGhostEdges()) {
            if(ghost->source()->node() == child) {
                foreach(dtkComposerEdge *output, node->outputEdges()) {
                    dtkComposerEdge *e = new dtkComposerEdge;
                    e->setSource(ghost->source());
                    e->setDestination(output->destination());
                    this->addItem(e);
                    e->show();
                    child->addOutputEdge(e, e->source());
                    e->destination()->node()->addInputEdge(e, e->destination());
                }
            }
        }        

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
    s_evaluate = true;

    emit evaluationStarted();

    foreach(dtkComposerNode *node, this->nodes())
        if(node->kind() == dtkComposerNode::Data)
            node->setDirty(false);
        else
            node->setDirty(true);

    if(this->selectedItems().count()) {
        foreach(QGraphicsItem *item, this->selectedItems()) {
            if(dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item)) {
                if(!node->parentItem()) {
                    node->setDirty(true);
                    node->update();
                }
            }
        }
    } else {
        foreach(dtkComposerNode *node, this->startNodes()) {
            node->setDirty(true);
            node->update();
        }
    }
}

void dtkComposerScene::stopEvaluation(void)
{
    s_evaluate = false;

    emit evaluationStopped();
}

void dtkComposerScene::copy(void)
{
    d->clipboard.nodes.clear();
    d->clipboard.edges.clear();

    foreach(QGraphicsItem *item, this->selectedItems())
        if(dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item))
            d->clipboard.nodes << node;

    foreach(dtkComposerEdge *edge, d->edges)
        if(d->clipboard.nodes.contains(edge->source()->node()) && d->clipboard.nodes.contains(edge->destination()->node()))
            d->clipboard.edges << edge;

    // -- Forbid copy/paste of composite nodes for the moment
    
    foreach(dtkComposerNode *node, d->clipboard.nodes) {
        if(node->kind() == dtkComposerNode::Composite) {
            d->clipboard.nodes.clear();
            d->clipboard.edges.clear();
        }
    }
}

void dtkComposerScene::paste(void)
{
    QMap<dtkComposerNode *, dtkComposerNode *> node_map;

    foreach(dtkComposerNode *node, d->clipboard.nodes)
        node_map.insert(node, this->createNode(node->type(), node->pos() + QPointF(200, 200)));

    foreach(dtkComposerEdge *edge, d->clipboard.edges) {

        dtkComposerEdge *e = new dtkComposerEdge;
        e->setSource(node_map.value(edge->source()->node())->outputProperty(edge->source()->name()));
        e->setDestination(node_map.value(edge->destination()->node())->inputProperty(edge->destination()->name()));

        node_map.value(edge->source()->node())->addOutputEdge(e, node_map.value(edge->source()->node())->outputProperty(edge->source()->name()));
        node_map.value(edge->destination()->node())->addInputEdge(e, node_map.value(edge->destination()->node())->inputProperty(edge->destination()->name()));

        this->addEdge(e);
    }
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
}

void dtkComposerScene::hideAllNodes(void)
{
    foreach(QGraphicsItem *item, this->items()) {
        if(dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item)) {
            if(node->isVisible()) {
                node->hide();
            }
        }
    }
}

void dtkComposerScene::showAllNodes(void)
{
    foreach(dtkComposerNode *node, d->nodes) {
        if(!node->parentNode()) {
            node->show();
        }
    }
}

void dtkComposerScene::showChildNodes(dtkComposerNode *node)
{
    node->show();

    foreach(dtkComposerNode *child, node->childNodes())
        child->show();
}

void dtkComposerScene::updateEdgesVisibility(void)
{
    foreach(dtkComposerEdge *edge, d->edges) {
        
        if (edge->source()->node()->isVisible() && edge->destination()->node()->isVisible() && !edge->isVisible())
            edge->show();

        if(!edge->source()->node()->isVisible() && edge->destination()->node()->isVisible() && edge->isVisible())
            edge->hide();

        if(edge->source()->node()->isVisible() && !edge->destination()->node()->isVisible() && edge->isVisible())
            edge->hide();

        if(!edge->source()->node()->isVisible() && !edge->destination()->node()->isVisible() && edge->isVisible())
            edge->hide();

        edge->adjust();
    }
}

QList<dtkComposerNodeControlBlock *> dtkComposerScene::hoveredControlBlocks(dtkComposerNode *node)
{
    QList<dtkComposerNodeControlBlock *> blocks;

    foreach(QGraphicsItem *item, this->items(node->mapToScene(node->boundingRect()))) {
        if(dtkComposerNodeControlBlock *block = dynamic_cast<dtkComposerNodeControlBlock *>(item)) {
            if((block->parentItem() != node)
            && (block->mapRectToScene(block->boundingRect()).contains(node->mapRectToScene(node->boundingRect())))
            && (this->hoveredControlBlocks(node, block->childItems()).isEmpty()))
                blocks << block;
        }
    }
    
    return blocks;
}

QList<dtkComposerNodeControlBlock *> dtkComposerScene::hoveredControlBlocks(dtkComposerNode *node, QList<QGraphicsItem *> parents)
{
    QList<dtkComposerNodeControlBlock *> blocks;

    foreach(QGraphicsItem *parent, parents) {
        foreach(QGraphicsItem *item, parent->childItems()) {
            if(dtkComposerNodeControlBlock *block = dynamic_cast<dtkComposerNodeControlBlock *>(item)) {
                if((block->parentItem() != node)
                && (block->mapRectToScene(block->boundingRect()).contains(node->mapRectToScene(node->boundingRect())))
                && (this->hoveredControlBlocks(node, block->childItems()).isEmpty()))
                    blocks << block;
            }
        }
    }
    
    return blocks;
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

    if (url.scheme() == "note") {
        this->createNote(url.path(), event->scenePos());
        event->acceptProposedAction();
        return;
    }

    if (url.scheme() != "type") {
        event->ignore();
        return;
    }

    this->createNode(url.path(), event->scenePos());

    event->acceptProposedAction();
}

void dtkComposerScene::keyPressEvent(QKeyEvent *event)
{
    // Item deletion - Delete | Backspace

    if((event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) && (event->modifiers() & Qt::ControlModifier))
        foreach(QGraphicsItem *item, this->selectedItems())
            if(dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item))
                this->removeNode(node);

    // Item Copy - Ctrl + C

    if(event->key() == Qt::Key_C && event->modifiers() & Qt::ControlModifier) {
        this->copy();
    }

    // Item Copy - Ctrl + V

    if(event->key() == Qt::Key_V && event->modifiers() & Qt::ControlModifier) {
        this->paste();
    }

    QGraphicsScene::keyPressEvent(event);
}

void dtkComposerScene::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

void dtkComposerScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);

    if (d->current_edge)
        d->current_edge->adjust(d->current_edge->start(), mouseEvent->scenePos());

    this->updateEdgesVisibility();

    // -- Control nodes handling

    d->grabber_node = NULL;
    
    if(this->mouseGrabberItem())
        d->grabber_node = dynamic_cast<dtkComposerNode *>(this->mouseGrabberItem());
    
    if(!d->grabber_node)
        return;

    QList<dtkComposerNodeControlBlock *> hovered_control_blocks = this->hoveredControlBlocks(d->grabber_node);

    foreach(dtkComposerNodeControlBlock *block, hovered_control_blocks)
        if(d->grabber_node->parentItem() != block)
            block->highlight(block);

    if(hovered_control_blocks.isEmpty())
        dtkComposerNodeControlBlock::highlight(0);
}

void dtkComposerScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);

    dtkComposerNodeProperty *property = propertyAt(mouseEvent->scenePos());

    if(!property)
        return;

    if (!property->node()->isGhost() && property->type() == dtkComposerNodeProperty::Output) {
        if(d->current_edge) {
            d->current_edge->hide();
            delete d->current_edge;
            d->current_edge = NULL;
        }
        d->current_edge = new dtkComposerEdge;
        this->addItem(d->current_edge);
        d->current_edge->setSource(property);
        d->current_edge->show();
        return;
    }

    if (!property->node()->isGhost() && property->type() == dtkComposerNodeProperty::Input) {
        d->current_edge = property->edge();
        if (d->current_edge) {
            d->current_edge->unlink();
            d->edges.removeAll(d->edge(d->current_edge));
        }
        return;
    }

    if (!property->node()->isGhost() && property->type() == dtkComposerNodeProperty::HybridOutput) {
        
        if (property->contains(mouseEvent->pos())) {
        
            property->setBehavior(dtkComposerNodeProperty::AsOutput);
            if(d->current_edge) {
                d->current_edge->hide();
                delete d->current_edge;
                d->current_edge = NULL;
            }
            d->current_edge = new dtkComposerEdge;
            this->addItem(d->current_edge);
            d->current_edge->setSource(property);
            d->current_edge->show();
            return;

        } else {
            
            property->setBehavior(dtkComposerNodeProperty::AsRelay);
            d->current_edge = property->edge();
            if (d->current_edge) {
                d->current_edge->unlink();
                d->edges.removeAll(d->edge(d->current_edge));
            }
            return;
        }
    }

    if (!property->node()->isGhost() && property->type() == dtkComposerNodeProperty::HybridInput) {
        
        if (property->contains(mouseEvent->pos())) {

            property->setBehavior(dtkComposerNodeProperty::AsRelay);
            if(d->current_edge) {
                d->current_edge->hide();
                delete d->current_edge;
                d->current_edge = NULL;
            }
            d->current_edge = new dtkComposerEdge;
            this->addItem(d->current_edge);
            d->current_edge->setSource(property);
            d->current_edge->show();
            return;

        } else {

            property->setBehavior(dtkComposerNodeProperty::AsInput);
            d->current_edge = property->edge();
            if (d->current_edge) {
                d->current_edge->unlink();
                d->edges.removeAll(d->edge(d->current_edge));
            }
            return;
        }
    }

    if (property->node()->isGhost() && property->type() == dtkComposerNodeProperty::Input) {
        if(d->current_edge) {
            d->current_edge->hide();
            delete d->current_edge;
            d->current_edge = NULL;
        }
        d->current_edge = new dtkComposerEdge;
        this->addItem(d->current_edge);
        d->current_edge->setSource(property);
        d->current_edge->show();
        return;
    }

    if (property->node()->isGhost() && property->type() == dtkComposerNodeProperty::Output) {
        d->current_edge = property->edge();
        if (d->current_edge) {
            d->current_edge->unlink();
            d->edges.removeAll(d->edge(d->current_edge));
        }
        return;
    }
}

void dtkComposerScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);

    // -- Current edge handling

    if (d->current_edge) {

        if(dtkComposerNodeProperty *property = propertyAt(mouseEvent->scenePos())) {
            
            d->current_edge->setDestination(property);
            
            if(!d->current_edge->link()) {
                
                delete d->current_edge;
                
                d->current_edge = 0;
                
                this->setModified(true);
                
            } else {
                
                // -- Handling control nodes
                
                if (property->node()->kind() == dtkComposerNode::Control)
                    property->node()->onInputEdgeConnected(d->current_edge, property);
                
                // --
                
                dtkComposerEdge *edge = d->current_edge;
                
                d->edges << edge;
                
                d->current_edge = 0;
            }
            
            this->setModified(true);

        } else {

            delete d->current_edge;

            d->current_edge = 0;
        }        
    }

    // -- Control nodes handling

    if(!d->grabber_node)
        return;

    QList<dtkComposerNodeControlBlock *> blocks = this->hoveredControlBlocks(d->grabber_node);

    if(blocks.count() > 1)
        return;

    if(blocks.count()) {

        if(d->grabber_node->parentItem() == blocks.first())
            return;

        QPointF c = d->grabber_node->scenePos();
        QPointF w = blocks.first()->scenePos();

        d->grabber_node->setParentItem(blocks.first());
        //d->grabber_node->setParentNode(blocks.first()->parentNode());
        d->grabber_node->setPos(c - w);

        if(dtkComposerNodeControl *control = dynamic_cast<dtkComposerNodeControl *>(d->grabber_node))
            control->setZValue(blocks.first()->zValue() + 1);

    } else {

        QPointF c = d->grabber_node->pos();
        QPointF w = QPointF(0, 0);

        if(d->grabber_node->parentItem())
            w = d->grabber_node->parentItem()->scenePos();

        d->grabber_node->setParentItem(0); 
        //d->grabber_node->setParentNode(0);
        d->grabber_node->setPos(c + w);
    }
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

        if(dtkComposerNode *parent = node->parentNode())
            parent->setGhost(false);                
        node->setGhost(true);

        this->hideAllNodes();
        this->showChildNodes(node);
        this->updateEdgesVisibility();
        this->setCurrentNode(node);

        emit centerOn(node->sceneBoundingRect().center());
        // emit fitInView(node->sceneBoundingRect());
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
            
            emit centerOn(parent->sceneBoundingRect().center());
            // emit fitInView(parent->sceneBoundingRect());
            emit pathChanged(d->current_node);
            
        } else {

            node->setGhost(false);
            
            this->hideAllNodes();
            this->showAllNodes();
            this->updateEdgesVisibility();
            this->setCurrentNode(NULL);
            
            emit centerOn(this->sceneRect().center());
            // emit fitInView(this->sceneRect());
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

bool dtkComposerScene::s_evaluate = false;

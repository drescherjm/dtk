/* dtkComposerScene.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:13:25
 * Version: $Id$
 * Last-Updated: Sat Feb 18 14:38:25 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 1487
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerMachine.h"
#include "dtkComposerMachineState.h"
#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerSceneNote.h"
#include "dtkComposerScenePort.h"
#include "dtkComposerStack.h"
#include "dtkComposerStackCommand.h"

dtkComposerScene::dtkComposerScene(QObject *parent) : QGraphicsScene(parent), d(new dtkComposerScenePrivate)
{
    d->factory = NULL;
    d->machine = NULL;
    d->stack = NULL;
    d->graph = NULL;

    d->root_node = new dtkComposerSceneNodeComposite;
    d->root_node->setRoot(true);

    d->current_node = d->root_node;
    d->current_edge = NULL;

    d->reparent_origin = NULL;
    d->reparent_target = NULL;

    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
}

dtkComposerScene::~dtkComposerScene(void)
{
    delete d;

    d = NULL;
}

void dtkComposerScene::setFactory(dtkComposerFactory *factory)
{
    d->factory = factory;
}

void dtkComposerScene::setMachine(dtkComposerMachine *machine)
{
    d->machine = machine;
}

void dtkComposerScene::setStack(dtkComposerStack *stack)
{
    d->stack = stack;
}

void dtkComposerScene::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
}

void dtkComposerScene::addNode(dtkComposerSceneNode *node)
{
    d->current_node->addNode(node);

    this->addItem(node);

    emit modified(true);
}

void dtkComposerScene::removeNode(dtkComposerSceneNode *node)
{
    d->current_node->removeNode(node);

    this->removeItem(node);

    emit modified(true);
}

void dtkComposerScene::addEdge(dtkComposerSceneEdge *edge)
{
    d->current_node->addEdge(edge);

    this->addItem(edge);

    edge->adjust();

    emit modified(true);
}

void dtkComposerScene::removeEdge(dtkComposerSceneEdge *edge)
{
    d->current_node->removeEdge(edge);

    this->removeItem(edge);

    emit modified(true);
}

void dtkComposerScene::addNote(dtkComposerSceneNote *note)
{
    d->current_node->addNote(note);

    this->addItem(note);

    emit modified(true);
}

void dtkComposerScene::removeNote(dtkComposerSceneNote *note)
{
    d->current_node->removeNote(note);

    this->removeItem(note);

    emit modified(true);
}

dtkComposerSceneNodeComposite *dtkComposerScene::root(void)
{
    return d->root_node;
}

dtkComposerSceneNodeComposite *dtkComposerScene::current(void)
{
    return d->current_node;
}

void dtkComposerScene::clear(void)
{
    foreach(dtkComposerSceneNote *note, d->root_node->notes())
        this->removeNote(note);

    foreach(dtkComposerSceneNode *node, d->root_node->nodes())
        this->removeNode(node);

    foreach(dtkComposerSceneEdge *edge, d->root_node->edges())
        this->removeEdge(edge);
}

void dtkComposerScene::setRoot(dtkComposerSceneNodeComposite *root)
{
    foreach(dtkComposerSceneNote *note, root->notes())
        this->addItem(note);

    foreach(dtkComposerSceneNode *node, root->nodes())
        this->addItem(node);

    foreach(dtkComposerSceneEdge *edge, root->edges())
        this->addItem(edge);

    emit reset();
}

void dtkComposerScene::setCurrent(dtkComposerSceneNode *node)
{
    if(!node)
        d->current_node = d->root_node;
    else if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node))
        d->current_node = composite;
    else
        qDebug() << __func__ << "Node should be a composite one";
}

void dtkComposerScene::setCurrent(dtkComposerSceneNodeComposite *current)
{
    d->current_node = current;
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
    QString name = event->mimeData()->text();
    QUrl url = event->mimeData()->urls().first();

    if (url.scheme() == "note") {

        dtkComposerStackCommandCreateNote *command = new dtkComposerStackCommandCreateNote;
        command->setScene(this);
        command->setPosition(event->scenePos());
        
        d->stack->push(command);

        event->acceptProposedAction();

        return;
    }

    if (url.scheme() == "node") {

        dtkComposerStackCommandCreateNode *command = new dtkComposerStackCommandCreateNode;
        command->setFactory(d->factory);
        command->setScene(this);
        command->setGraph(d->graph);
        command->setPosition(event->scenePos());
        command->setType(url.path());
        command->setName(name);
        
        d->stack->push(command);
        
        event->acceptProposedAction();

        return;
    }

    event->ignore();
}

void dtkComposerScene::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) && (event->modifiers() & Qt::ControlModifier)) {

        QList<dtkComposerSceneNode *> selected_nodes;
        QList<dtkComposerSceneNote *> selected_notes;

        // retrieve items to be deleted

        foreach(QGraphicsItem *item, this->selectedItems()) {
            if (dtkComposerSceneNode *snode = dynamic_cast<dtkComposerSceneNode *>(item))
                selected_nodes << snode;
            if (dtkComposerSceneNote *snote = dynamic_cast<dtkComposerSceneNote *>(item))
                selected_notes << snote;
        }

        // multiple node deletion
        
        if(selected_nodes.count() > 1) {

            dtkComposerStackCommand *group = new dtkComposerStackCommand;
            group->setText("Destroy a set of nodes");
            
            foreach(dtkComposerSceneNode *node, selected_nodes) {

                dtkComposerStackCommandDestroyNode *command = new dtkComposerStackCommandDestroyNode(group);
                command->setScene(this);
                command->setNode(node);
            }

            d->stack->push(group);

        // single node deletion

        } else if(selected_nodes.count() == 1) {

            dtkComposerStackCommandDestroyNode *command = new dtkComposerStackCommandDestroyNode;
            command->setScene(this);
            command->setNode(selected_nodes.first());

            d->stack->push(command);
        }

        // multiple note deletion

        if(selected_notes.count() > 1) {

            dtkComposerStackCommand *group = new dtkComposerStackCommand;
            group->setText("Destroy a set of notes");
            
            foreach(dtkComposerSceneNote *note, selected_notes) {

                dtkComposerStackCommandDestroyNote *command = new dtkComposerStackCommandDestroyNote(group);
                command->setScene(this);
                command->setNote(note);
            }

            d->stack->push(group);

        // single note deletion

        } else if(selected_notes.count() == 1) {

            dtkComposerStackCommandDestroyNote *command = new dtkComposerStackCommandDestroyNote;
            command->setScene(this);
            command->setNote(selected_notes.first());

            d->stack->push(command);
        }

    } else if ((event->key() == Qt::Key_G) && (event->modifiers() & Qt::ControlModifier)) {

        dtkComposerSceneNodeList selected_nodes;
        dtkComposerSceneNoteList selected_notes;

        foreach(QGraphicsItem *item, this->selectedItems()) {
            if (dtkComposerSceneNode *snode = dynamic_cast<dtkComposerSceneNode *>(item))
                selected_nodes << snode;
            if (dtkComposerSceneNote *snote = dynamic_cast<dtkComposerSceneNote *>(item))
                selected_notes << snote;
        }

        if(selected_nodes.count()) {

            dtkComposerStackCommandCreateGroup *command = new dtkComposerStackCommandCreateGroup;
            command->setScene(this);
            command->setNodes(selected_nodes);
            command->setNotes(selected_notes);
            
            d->stack->push(command);
        }

    } else if ((event->key() == Qt::Key_U) && (event->modifiers() & Qt::ControlModifier) && (this->selectedItems().count() == 1)) {

        if(dtkComposerSceneNodeComposite *group = dynamic_cast<dtkComposerSceneNodeComposite *>(this->selectedItems().first())) {

            if(!group->entered() || !group->flattened()) {

                dtkComposerStackCommandDestroyGroup *command = new dtkComposerStackCommandDestroyGroup;
                command->setScene(this);
                command->setNode(group);
                
                d->stack->push(command);
            }
        }

    } else {
        QGraphicsScene::keyPressEvent(event);
    }
}

void dtkComposerScene::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsScene::keyReleaseEvent(event);
}

void dtkComposerScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    if(!(event->buttons() & Qt::LeftButton))
        return;

//-- Managing reparenting

    if (d->reparent_origin_pos.isNull()) {

        d->reparent_origin = this->nodeAt(event->scenePos());
        
        if(!d->reparent_origin)
            goto adjust_edges;
        
        if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(d->reparent_origin->parent()))
            d->reparent_origin = control;

        if (d->reparent_origin->inputEdges().count()) {
            d->reparent_origin = NULL;
            goto adjust_edges;
        }

        if (d->reparent_origin->outputEdges().count()) {
            d->reparent_origin = NULL;
            goto adjust_edges;
        }

        d->reparent_origin_pos = d->reparent_origin->pos();

    } else {

        dtkComposerSceneNode *node = this->nodeAt(event->scenePos(), d->reparent_origin);

        if(!node) {
            d->reparent_target = NULL;
            this->views().at(0)->setCursor(Qt::ArrowCursor);
            goto adjust_edges;
        }

        if(dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {

            d->reparent_target = node;

            if (d->reparent_origin->parent() == d->reparent_target) {
                d->reparent_target = NULL;
                goto adjust_edges;
            }
            
            if (dynamic_cast<dtkComposerSceneNodeControl *>(d->reparent_target->parent())) {
                d->reparent_target = NULL;
                goto adjust_edges;
            }

            this->views().at(0)->setCursor(Qt::WaitCursor);
        }

        if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {

            d->reparent_target = node;

            if (d->reparent_origin->parent() == d->reparent_target) {
                d->reparent_target = NULL;
                goto adjust_edges;
            }

            // Look for a block within the control node

            dtkComposerSceneNodeComposite *block = control->blockAt(event->scenePos());

            if(!block) {
                this->views().at(0)->setCursor(Qt::ArrowCursor);
                d->reparent_target = NULL;
                goto adjust_edges;
            }

            this->views().at(0)->setCursor(Qt::WaitCursor);
        }

    }

// --
  
adjust_edges: // Adjusting edges of selected nodes

    foreach(QGraphicsItem *item, this->selectedItems()) {

        if(dtkComposerSceneNode *node = dynamic_cast<dtkComposerSceneNode *>(item)) {

            if (node->parent() != d->root_node) {
                node->parent()->layout();
                this->update();
            }
            
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

adjust_current: // Adjusting current edge

    if (d->current_edge)
        d->current_edge->adjust(d->current_edge->source()->mapToScene(d->current_edge->source()->boundingRect().center()), event->scenePos());

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

    // Managing of reparenting

    if (d->reparent_target) {
        d->reparent_target_pos = event->scenePos();

        this->views().at(0)->setCursor(Qt::ArrowCursor);

        dtkComposerStackCommandReparentNode *command = new dtkComposerStackCommandReparentNode;
        command->setOriginNode(d->reparent_origin);
        command->setTargetNode(d->reparent_target);
        command->setOriginPosition(d->reparent_origin_pos);
        command->setTargetPosition(d->reparent_target_pos);
        command->setScene(this);
        d->stack->push(command);

        d->reparent_origin = NULL;
        d->reparent_target = NULL;

        this->views().at(0)->setCursor(Qt::ArrowCursor);
    }

    d->reparent_origin_pos = QPointF();
    d->reparent_target_pos = QPointF();

    // Managing of current edge

    if(!d->current_edge)
        return;

    if(dtkComposerScenePort *destination = this->portAt(event->scenePos()))
        d->current_edge->setDestination(destination);

    if(d->current_edge->link()) {

        dtkComposerStackCommandCreateEdge *command = new dtkComposerStackCommandCreateEdge;
        command->setGraph(d->graph);
        command->setScene(this);
        command->setSource(d->current_edge->source());
        command->setDestination(d->current_edge->destination());

        d->stack->push(command);
    }

    d->current_edge->unlink();

    this->removeItem(d->current_edge);

    delete d->current_edge;
    
    d->current_edge = NULL;
}

void dtkComposerScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);

    dtkComposerSceneNode *node = this->nodeAt(event->scenePos());

    if(!node)
        return;

    dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node);

    if(!composite)
        return;

    if(event->modifiers() & Qt::ControlModifier) {

        if(!composite->flattened() && !composite->entered()) {
            dtkComposerStackCommandFlattenGroup *command = new dtkComposerStackCommandFlattenGroup;
            command->setScene(this);
            command->setNode(composite);
            d->stack->push(command);
        } else if(!composite->entered()) {
            dtkComposerStackCommandUnflattenGroup *command = new dtkComposerStackCommandUnflattenGroup;
            command->setScene(this);
            command->setNode(composite);
            d->stack->push(command);
        }

    } else {

        if(!composite->entered() && !composite->flattened()) {
            dtkComposerStackCommandEnterGroup *command = new dtkComposerStackCommandEnterGroup;
            command->setScene(this);
            command->setNode(composite);
            d->stack->push(command);
        } else if(!composite->flattened()) {
            dtkComposerStackCommandLeaveGroup *command = new dtkComposerStackCommandLeaveGroup;
            command->setScene(this);
            command->setNode(composite);
            d->stack->push(command);
        }
    }
}

dtkComposerSceneNode *dtkComposerScene::nodeAt(const QPointF& point) const
{
    QList<QGraphicsItem *> items = this->items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect);

    foreach(QGraphicsItem *item, items)
        if (dtkComposerSceneNode *node = dynamic_cast<dtkComposerSceneNode *>(item))
            return node;

    return NULL;
}

dtkComposerSceneNode *dtkComposerScene::nodeAt(const QPointF& point, dtkComposerSceneNode *exclude) const
{
    QList<QGraphicsItem *> items = this->items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect);

    foreach(QGraphicsItem *item, items) {
        if (dtkComposerSceneNode *n = dynamic_cast<dtkComposerSceneNode *>(item)) {
            
            dtkComposerSceneNode *node = n;

            if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node->parent()))
                node = control;
            
            if (node != exclude && !(node->parent() == exclude))
                return node;
        }
    }

    return NULL;
}

dtkComposerScenePort *dtkComposerScene::portAt(const QPointF& point) const
{
    QList<QGraphicsItem *> items = this->items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect);

    foreach(QGraphicsItem *item, items)
        if (dtkComposerScenePort *port = dynamic_cast<dtkComposerScenePort *>(item))
            return port;

    return NULL;
}

void dtkComposerScene::onSelectionChanged(void)
{
    QList<QGraphicsItem *> selection = this->selectedItems();

    // if(!selection.count())
    //     emit selectionCleared();
    // else if(selection.count() > 1)
    //     emit selectionCleared();
    // else
    //     emit selected(selection.first());

    if(selection.count() == 1) {

        dtkComposerSceneNode *node = dynamic_cast<dtkComposerSceneNode *>(selection.first());

        if(node)
            emit selectedNode(node);

    } else {

        emit selectionCleared();

    }
}

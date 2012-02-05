/* dtkComposerScene.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:13:25
 * Version: $Id$
 * Last-Updated: Sun Feb  5 15:20:24 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 1147
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

    d->root_node = new dtkComposerSceneNodeComposite;
    d->root_node->setRoot(true);

    d->current_node = d->root_node;
    d->current_edge = NULL;
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
        this->addNote(note);

    foreach(dtkComposerSceneNode *node, root->nodes())
        this->addNode(node);

    foreach(dtkComposerSceneEdge *edge, root->edges())
        this->addEdge(edge);
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

        foreach(QGraphicsItem *item, this->selectedItems()) {
            if (dtkComposerSceneNode *snode = dynamic_cast<dtkComposerSceneNode *>(item))
                selected_nodes << snode;
        }

        if(selected_nodes.count()) {

            dtkComposerStackCommandCreateGroup *command = new dtkComposerStackCommandCreateGroup;
            command->setScene(this);
            command->setNodes(selected_nodes);
            command->setEdges(d->current_node->edges());
            
            d->stack->push(command);
        }

    } else if ((event->key() == Qt::Key_U) && (event->modifiers() & Qt::ControlModifier) && (this->selectedItems().count() == 1)) {

        if(dtkComposerSceneNodeComposite *group = dynamic_cast<dtkComposerSceneNodeComposite *>(this->selectedItems().first())) {

            dtkComposerStackCommandDestroyGroup *command = new dtkComposerStackCommandDestroyGroup;
            command->setScene(this);
            command->setNode(group);
        
            d->stack->push(command);
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

    if(!d->current_edge)
        return;

    if(dtkComposerScenePort *destination = this->portAt(event->scenePos()))
        d->current_edge->setDestination(destination);

    if(d->current_edge->link()) {

        dtkComposerStackCommandCreateEdge *command = new dtkComposerStackCommandCreateEdge;
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

    if(!composite->entered()) {
        dtkComposerStackCommandEnterGroup *command = new dtkComposerStackCommandEnterGroup;
        command->setScene(this);
        command->setNode(composite);
        d->stack->push(command);
    } else {
        dtkComposerStackCommandLeaveGroup *command = new dtkComposerStackCommandLeaveGroup;
        command->setScene(this);
        command->setNode(composite);
        d->stack->push(command);
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

dtkComposerScenePort *dtkComposerScene::portAt(const QPointF& point) const
{
    QList<QGraphicsItem *> items = this->items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect);

    foreach(QGraphicsItem *item, items)
        if (dtkComposerScenePort *port = dynamic_cast<dtkComposerScenePort *>(item))
            return port;

    return NULL;
}

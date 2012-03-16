/* dtkComposerScene.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:13:25
 * Version: $Id$
 * Last-Updated: ven. mars 16 18:22:35 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 1950
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerEvaluator.h"
#include "dtkComposerGraph.h"
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
#include "dtkComposerStackUtils.h"

dtkComposerScene::dtkComposerScene(QObject *parent) : QGraphicsScene(parent), d(new dtkComposerScenePrivate)
{
    d->factory = NULL;
    d->machine = NULL;
    d->stack = NULL;
    d->graph = NULL;
    d->evaluator = new dtkComposerEvaluator;

    d->root_node = new dtkComposerSceneNodeComposite;
    d->root_node->setRoot(true);
    d->root_node->setTitle("Root");

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

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Setup
// /////////////////////////////////////////////////////////////////

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
    d->graph->addNode(d->root_node);
    d->graph->layout();
    d->evaluator->setGraph(graph);
}

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Composition depth management
// /////////////////////////////////////////////////////////////////

dtkComposerSceneNodeComposite *dtkComposerScene::root(void)
{
    return d->root_node;
}

dtkComposerSceneNodeComposite *dtkComposerScene::current(void)
{
    return d->current_node;
}

void dtkComposerScene::setRoot(dtkComposerSceneNodeComposite *root)
{
    foreach(dtkComposerSceneNote *note, root->notes())
        this->addItem(note);

    foreach(dtkComposerSceneNode *node, root->nodes())
        this->addItem(node);

    foreach(dtkComposerSceneEdge *edge, root->edges())
        this->addItem(edge);

    emit modified(true);
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

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Scene management
// /////////////////////////////////////////////////////////////////

void dtkComposerScene::addItem(QGraphicsItem *item)
{
    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(item)) {

        QGraphicsScene::addItem(item);

        foreach(dtkComposerSceneNodeComposite *block, control->blocks()) {

            block->setParentItem(control);

            foreach(dtkComposerSceneNote *note, block->notes())
                this->addItem(note);
            
            foreach(dtkComposerSceneNode *node, block->nodes())
                this->addItem(node);
            
            foreach(dtkComposerSceneEdge *edge, block->edges())
                this->addItem(edge);
        }

        control->layout();

        return;
    }

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(item)) {

        if(item != d->root_node)
            QGraphicsScene::addItem(item);

        if(!composite->flattened() && !composite->entered() && !composite->root())
            return;

        foreach(dtkComposerSceneNote *note, composite->notes())
            this->addItem(note);

        foreach(dtkComposerSceneNode *node, composite->nodes())
            this->addItem(node);

        foreach(dtkComposerSceneEdge *edge, composite->edges())
            this->addItem(edge);

        return;
    }

    QGraphicsScene::addItem(item);
}

void dtkComposerScene::removeItem(QGraphicsItem *item)
{
    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(item)) {

        QGraphicsScene::removeItem(item);

        foreach(dtkComposerSceneNodeComposite *block, control->blocks()) {

            foreach(dtkComposerSceneNote *note, block->notes())
                this->removeItem(note);
            
            foreach(dtkComposerSceneNode *node, block->nodes())
                this->removeItem(node);
            
            foreach(dtkComposerSceneEdge *edge, block->edges())
                this->removeItem(edge);
        }

        return;
    }

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(item)) {

        if(item != d->root_node)
            QGraphicsScene::removeItem(composite);

        if(!composite->flattened() && !composite->entered() && !composite->root())
            return;

        foreach(dtkComposerSceneNote *note, composite->notes())
            this->removeItem(note);

        foreach(dtkComposerSceneNode *node, composite->nodes())
            this->removeItem(node);

        foreach(dtkComposerSceneEdge *edge, composite->edges())
            this->removeItem(edge);

        return;
    }

    QGraphicsScene::removeItem(item);
}

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Sig Events
// /////////////////////////////////////////////////////////////////

void dtkComposerScene::modify(bool b)
{
    emit modified(b);
}

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Drag n Drop Events
// /////////////////////////////////////////////////////////////////

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
        command->setParent(this->parentAt(event->scenePos()));
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
        command->setParent(this->parentAt(event->scenePos()));
        command->setPosition(event->scenePos());
        command->setType(url.path());
        command->setName(name);

        d->stack->push(command);

        event->acceptProposedAction();

        return;
    }

    event->ignore();
}

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Keyboard Events
// /////////////////////////////////////////////////////////////////

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
                command->setGraph(d->graph);
                command->setNode(node);
            }

            d->stack->push(group);

        // single node deletion

        } else if(selected_nodes.count() == 1) {

            dtkComposerStackCommandDestroyNode *command = new dtkComposerStackCommandDestroyNode;
            command->setScene(this);
            command->setGraph(d->graph);
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
            command->setGraph(d->graph);
            command->setNodes(selected_nodes);
            command->setNotes(selected_notes);

            if(areBrothers(selected_nodes, selected_notes))
                d->stack->push(command);
            else
                delete command;
        }

    } else if ((event->key() == Qt::Key_U) && (event->modifiers() & Qt::ControlModifier) && (this->selectedItems().count() == 1)) {

        if(dtkComposerSceneNodeComposite *group = dynamic_cast<dtkComposerSceneNodeComposite *>(this->selectedItems().first())) {

            if(!group->entered() || !group->flattened()) {

                dtkComposerStackCommandDestroyGroup *command = new dtkComposerStackCommandDestroyGroup;
                command->setGraph(d->graph);
                command->setScene(this);
                command->setNode(group);

                d->stack->push(command);
            }
        }
    } else if ((event->key() == Qt::Key_R)  && (event->modifiers() & Qt::ControlModifier) && (event->modifiers() & Qt::ShiftModifier)) {
        QtConcurrent::run(d->evaluator, &dtkComposerEvaluator::run, true);
    } else if ((event->key() == Qt::Key_R)  && (event->modifiers() & Qt::ControlModifier)) {
        QtConcurrent::run(d->evaluator, &dtkComposerEvaluator::run, false);
    } else if ((event->key() == Qt::Key_N)  && (event->modifiers() & Qt::ControlModifier)) {
        QtConcurrent::run(d->evaluator, &dtkComposerEvaluator::step, false);
    } else if ((event->key() == Qt::Key_C)  && (event->modifiers() & Qt::ControlModifier)) {
        QtConcurrent::run(d->evaluator, &dtkComposerEvaluator::cont, false);
    } else {
        QGraphicsScene::keyPressEvent(event);
    }
}

void dtkComposerScene::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsScene::keyReleaseEvent(event);
}

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Mouse Events
// /////////////////////////////////////////////////////////////////

void dtkComposerScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    if(!(event->buttons() & Qt::LeftButton))
        return;

    if(d->current_edge)
        goto adjust_edges;

//-- Managing reparenting

    if (d->reparent_origin_pos.isNull()) {

        d->reparent_origin = this->nodeAt(event->scenePos());

        if(!d->reparent_origin) {
            this->views().at(0)->setCursor(Qt::ArrowCursor);
            goto adjust_edges;
        }

        if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(d->reparent_origin->parent()))
            d->reparent_origin = control;

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
                this->views().at(0)->setCursor(Qt::ArrowCursor);
                goto adjust_edges;
            }

            if (dynamic_cast<dtkComposerSceneNodeControl *>(d->reparent_target->parent())) {
                d->reparent_target = NULL;
                this->views().at(0)->setCursor(Qt::ArrowCursor);
                goto adjust_edges;
            }

            this->views().at(0)->setCursor(Qt::PointingHandCursor);
        }

        if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {
            // Look for a block within the control node

            dtkComposerSceneNodeComposite *block = control->blockAt(event->scenePos());

            if(!block) {
                this->views().at(0)->setCursor(Qt::ArrowCursor);
                d->reparent_target = NULL;
                goto adjust_edges;
            }

            if (d->reparent_origin->parent() == block) {
                d->reparent_target = NULL;
                this->views().at(0)->setCursor(Qt::ArrowCursor);
                goto adjust_edges;
            }

            d->reparent_target = block;

            this->views().at(0)->setCursor(Qt::PointingHandCursor);
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

        d->reparent_target_pos = event->scenePos() - event->pos();

        dtkComposerStackCommandReparentNode *command = new dtkComposerStackCommandReparentNode;
        command->setScene(this);
        command->setGraph(d->graph);
        command->setOriginNode(d->reparent_origin);
        command->setTargetNode(d->reparent_target);
        command->setOriginPosition(d->reparent_origin_pos);
        command->setTargetPosition(d->reparent_target_pos);
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

    if(composite) {

        dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node->parent());

        if(!control) {

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
            
        } else {
            
            if(event->modifiers() & Qt::ControlModifier) {
                
                ; // Do nothing so far
                
            } else {
                
                if(!composite->entered()) {
                    dtkComposerStackCommandEnterGroup *command = new dtkComposerStackCommandEnterGroup;
                    command->setScene(this);
                    command->setBlock(composite);
                    d->stack->push(command);
                } else {
                    dtkComposerStackCommandLeaveGroup *command = new dtkComposerStackCommandLeaveGroup;
                    command->setScene(this);
                    command->setBlock(composite);
                    d->stack->push(command);
                }
            }
            
        }        
    }
}

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Geometric queries
// /////////////////////////////////////////////////////////////////

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

dtkComposerSceneNodeComposite *dtkComposerScene::parentAt(const QPointF& point) const
{
    dtkComposerSceneNode *node = this->nodeAt(point);

    if(!node) {
        // qDebug() << __func__ << "current node";
        return d->current_node;
    }
    
    if(dtkComposerSceneNodeLeaf *leaf = dynamic_cast<dtkComposerSceneNodeLeaf *>(node)) {
        // qDebug() << __func__ << "leaf node's parent";
        return dynamic_cast<dtkComposerSceneNodeComposite *>(leaf->parent());
    }

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {

        if(composite->flattened()) {
            // qDebug() << __func__ << "flattened composite node";
            return composite;
        }

        if(composite->entered()) {
            // qDebug() << __func__ << "entered composite node";
            return composite;
        }

        if(!composite->flattened() && !composite->entered()) {
            // qDebug() << __func__ << "unrevealed composite node's parent";
            return composite;
        }
    }

    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {

        dtkComposerSceneNodeComposite *block = control->blockAt(control->mapFromScene(point));

        if(!block) {
            // qDebug() << __func__ << "control node's parent" << control->parent()->title();
            return dynamic_cast<dtkComposerSceneNodeComposite *>(control->parent());
        }

        // qDebug() << __func__ << "control node's block" << block->title();

        return block;
    }

    // qDebug() << __func__ << "NO PARENT FOUND - DRAMATIC";

    return NULL;
}

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Internal signal handling
// /////////////////////////////////////////////////////////////////

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

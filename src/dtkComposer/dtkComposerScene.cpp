// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkComposerGraph.h"
#include "dtkComposerGraphNode.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeLeaf.h"
#include "dtkComposerReader.h"
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

#include <QtWidgets>

dtkComposerScene::dtkComposerScene(QObject *parent) : QGraphicsScene(parent), d(new dtkComposerScenePrivate)
{
    d->factory = NULL;
    d->stack = NULL;
    d->graph = NULL;

    // BspTreeIndex causes some bugs with (at least) "enter group"
    setItemIndexMethod( QGraphicsScene::NoIndex);

    d->root_node = new dtkComposerSceneNodeComposite;
    d->root_node->wrap(new dtkComposerNodeComposite);
    d->root_node->setRoot(true);
    d->root_node->setTitle("Root");

    d->current_node = d->root_node;
    d->current_edge = NULL;

    d->reparent_origin = NULL;
    d->reparent_target = NULL;
    d->last_paused_node = NULL;

    d->masked_edges = false;

    d->mask_edges_action = new QAction("Mask Edges", this);
    d->mask_edges_action->setShortcut(QKeySequence(Qt::ControlModifier  + Qt::Key_M));

    d->unmask_edges_action = new QAction("Unmask Edges", this);
    d->unmask_edges_action->setShortcut(QKeySequence(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_M));

    d->flag_as_blue_action = new QAction("Flag as blue", this);
    d->flag_as_blue_action->setShortcut(QKeySequence(Qt::ControlModifier + Qt::AltModifier + Qt::ShiftModifier + Qt::Key_B));
    d->flag_as_blue_action->setIcon(QIcon(":dtkComposer/pixmaps/dtkComposerNodeFlag-blue.png"));

    d->flag_as_gray_action = new QAction("Flag as gray", this);
    d->flag_as_gray_action->setShortcut(QKeySequence(Qt::ControlModifier + Qt::AltModifier + Qt::ShiftModifier + Qt::Key_W));
    d->flag_as_gray_action->setIcon(QIcon(":dtkComposer/pixmaps/dtkComposerNodeFlag-gray.png"));

    d->flag_as_green_action = new QAction("Flag as green", this);
    d->flag_as_green_action->setShortcut(QKeySequence(Qt::ControlModifier + Qt::AltModifier + Qt::ShiftModifier + Qt::Key_G));
    d->flag_as_green_action->setIcon(QIcon(":dtkComposer/pixmaps/dtkComposerNodeFlag-green.png"));

    d->flag_as_orange_action = new QAction("Flag as orange", this);
    d->flag_as_orange_action->setShortcut(QKeySequence(Qt::ControlModifier + Qt::AltModifier + Qt::ShiftModifier + Qt::Key_O));
    d->flag_as_orange_action->setIcon(QIcon(":dtkComposer/pixmaps/dtkComposerNodeFlag-orange.png"));

    d->flag_as_pink_action = new QAction("Flag as pink", this);
    d->flag_as_pink_action->setShortcut(QKeySequence(Qt::ControlModifier + Qt::AltModifier + Qt::ShiftModifier + Qt::Key_P));
    d->flag_as_pink_action->setIcon(QIcon(":dtkComposer/pixmaps/dtkComposerNodeFlag-pink.png"));

    d->flag_as_red_action = new QAction("Flag as red", this);
    d->flag_as_red_action->setShortcut(QKeySequence(Qt::ControlModifier + Qt::AltModifier + Qt::ShiftModifier + Qt::Key_R));
    d->flag_as_red_action->setIcon(QIcon(":dtkComposer/pixmaps/dtkComposerNodeFlag-red.png"));

    d->flag_as_yellow_action = new QAction("Flag as yellow", this);
    d->flag_as_yellow_action->setShortcut(QKeySequence(Qt::ControlModifier + Qt::AltModifier + Qt::ShiftModifier + Qt::Key_Y));
    d->flag_as_yellow_action->setIcon(QIcon(":dtkComposer/pixmaps/dtkComposerNodeFlag-yellow.png"));

    d->set_breakpoint_action = new QAction("Set BreakPoint", this);
    d->set_breakpoint_action->setShortcut(QKeySequence(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_B));
    d->set_breakpoint_action->setIcon(QIcon(":dtkComposer/pixmaps/dtkComposerNode-breakpoint.png"));

    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));

    connect(d->mask_edges_action, SIGNAL(triggered()), this, SLOT(onMaskEdge()));
    connect(d->unmask_edges_action, SIGNAL(triggered()), this, SLOT(onUnMaskEdge()));

    connect(d->flag_as_blue_action, SIGNAL(triggered()), this, SLOT(onFlagAsBlue()));
    connect(d->flag_as_gray_action, SIGNAL(triggered()), this, SLOT(onFlagAsGray()));
    connect(d->flag_as_green_action, SIGNAL(triggered()), this, SLOT(onFlagAsGreen()));
    connect(d->flag_as_orange_action, SIGNAL(triggered()), this, SLOT(onFlagAsOrange()));
    connect(d->flag_as_pink_action, SIGNAL(triggered()), this, SLOT(onFlagAsPink()));
    connect(d->flag_as_red_action, SIGNAL(triggered()), this, SLOT(onFlagAsRed()));
    connect(d->flag_as_yellow_action, SIGNAL(triggered()), this, SLOT(onFlagAsYellow()));
    connect(d->set_breakpoint_action, SIGNAL(triggered()), this, SLOT(onBreakPointSet()));

    this->setItemIndexMethod(QGraphicsScene::NoIndex);
}

dtkComposerScene::~dtkComposerScene(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////

void dtkComposerScene::clear(void)
{
    foreach(dtkComposerSceneNode *node, d->root_node->nodes()) {

        dtkComposerStackCommandDestroyNode *command = new dtkComposerStackCommandDestroyNode;
        command->setGraph(d->graph);
        command->setScene(this);
        command->setFactory(d->factory);
        command->setNode(node);
        command->redo();

        delete command;
    }

    foreach(dtkComposerSceneNote *note, d->root_node->notes()) {

        dtkComposerStackCommandDestroyNote *command = new dtkComposerStackCommandDestroyNote;
        command->setGraph(d->graph);
        command->setScene(this);
        command->setFactory(d->factory);
        command->setNote(note);
        command->redo();

        delete command;
    }
}

bool dtkComposerScene::maskedEdges(void)
{
    return d->masked_edges;
}

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Setup
// /////////////////////////////////////////////////////////////////

void dtkComposerScene::setFactory(dtkComposerNodeFactory *factory)
{
    d->factory = factory;
}

void dtkComposerScene::setStack(dtkComposerStack *stack)
{
    d->stack = stack;
}

void dtkComposerScene::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
    d->graph->addNode(d->root_node->wrapee(),NULL);
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

    dtkComposerSceneNode *first = NULL;

    dtkComposerSceneNode *node;

    for(int i = 0; i < root->nodes().count(); ++i) {

        node = root->nodes()[i];

        if (i == 0)
            first = node;

        this->addItem(node);
    }

    foreach(dtkComposerSceneEdge *edge, root->edges()) {

        this->addItem(edge);

        if (first)
            edge->stackBefore(first);
    }

    emit modified(true);
}

void dtkComposerScene::setCurrent(dtkComposerSceneNode *node)
{
    if(!node)
        d->current_node = d->root_node;
    else if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node))
        d->current_node = composite;
    else
        qDebug() << Q_FUNC_INFO << "Node should be a composite one";
    emit changed();
}

void dtkComposerScene::setCurrent(dtkComposerSceneNodeComposite *current)
{
    d->current_node = current;
    emit changed();
}

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Scene management
// /////////////////////////////////////////////////////////////////

void dtkComposerScene::addItem(QGraphicsItem *item)
{
    if (dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(item)) {

        QGraphicsScene::addItem(item);

        foreach(dtkComposerSceneNodeComposite *block, control->blocks()) {

            block->setParentItem(control);

            foreach(dtkComposerSceneNote *note, block->notes()) {
                this->addItem(note);
                control->stackBefore(note);
            }

            dtkComposerSceneNode *first = NULL;
            dtkComposerSceneNode *node;
            for(int i = 0; i < block->nodes().count(); ++i) {
                node = block->nodes()[i];
                if (i == 0)
                    first = node;
                this->addItem(node);
                control->stackBefore(node);
            }

            foreach(dtkComposerSceneEdge *edge, block->edges()) {
                this->addItem(edge);
                if (first)
                    edge->stackBefore(first);
            }
        }

        control->layout();

        emit modified(true);

        return;
    }

    if (dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(item)) {

        if(item != d->root_node)
            QGraphicsScene::addItem(item);

        if(!composite->flattened() && !composite->entered() && !composite->root()) {
            emit modified(true);
            return;
        }

        foreach(dtkComposerSceneNote *note, composite->notes())
            this->addItem(note);

        dtkComposerSceneNode *first = NULL;
        dtkComposerSceneNode *node;
        for(int i = 0; i < composite->nodes().count(); ++i) {
            node = composite->nodes()[i];
            if (i == 0)
                first = node;
            this->addItem(node);
        }

        foreach(dtkComposerSceneEdge *edge, composite->edges()) {
            this->addItem(edge);
            if (first)
                edge->stackBefore(first);
        }

        composite->layout();

        emit modified(true);

        return;
    }

    if(dtkComposerSceneNodeLeaf *leaf = dynamic_cast<dtkComposerSceneNodeLeaf *>(item)) {

        if(leaf->flagged()) {

            Qt::GlobalColor color = leaf->flagColor();

            if(!d->flagged_nodes[color].contains(leaf))
                d->flagged_nodes[color] << leaf;
        }
    }

    QGraphicsScene::addItem(item);

    emit modified(true);
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

        emit modified(true);

        return;
    }

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(item)) {

        if(item != d->root_node)
            QGraphicsScene::removeItem(composite);

        if(!composite->flattened() && !composite->entered() && !composite->root()) {
            emit modified(true);
            return;
        }

        foreach(dtkComposerSceneNote *note, composite->notes())
            this->removeItem(note);

        foreach(dtkComposerSceneNode *node, composite->nodes())
            this->removeItem(node);

        foreach(dtkComposerSceneEdge *edge, composite->edges())
            this->removeItem(edge);

        emit modified(true);

        return;
    }

    QGraphicsScene::removeItem(item);

    emit modified(true);
}

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Actions
// /////////////////////////////////////////////////////////////////

QAction *dtkComposerScene::flagAsBlueAction(void)
{
    return d->flag_as_blue_action;
}

QAction *dtkComposerScene::flagAsGrayAction(void)
{
    return d->flag_as_gray_action;
}

QAction *dtkComposerScene::flagAsGreenAction(void)
{
    return d->flag_as_green_action;
}

QAction *dtkComposerScene::flagAsOrangeAction(void)
{
    return d->flag_as_orange_action;
}

QAction *dtkComposerScene::flagAsPinkAction(void)
{
    return d->flag_as_pink_action;
}

QAction *dtkComposerScene::flagAsRedAction(void)
{
    return d->flag_as_red_action;
}

QAction *dtkComposerScene::flagAsYellowAction(void)
{
    return d->flag_as_yellow_action;
}

QAction *dtkComposerScene::setBreakPointAction(void)
{
    return d->set_breakpoint_action;
}

QAction *dtkComposerScene::maskEdgesAction(void)
{
    return d->mask_edges_action;
}

QAction *dtkComposerScene::unmaskEdgesAction(void)
{
    return d->unmask_edges_action;
}

QList<dtkComposerSceneNodeLeaf *> dtkComposerScene::flagged(Qt::GlobalColor color)
{
    return d->flagged_nodes[color];
}

bool dtkComposerScene::checkImplementations(void)
{
    populateNodes();
    foreach (dtkComposerSceneNode * node, d->all_nodes) {
        if (dtkComposerNodeLeafObject *nobj = dynamic_cast<dtkComposerNodeLeafObject*>(node->wrapee())) {
            if (nobj->currentImplementation().isEmpty()) {
                QMessageBox msgBox;

                msgBox.setText("Node implementation is missing. Run anyway?");
                msgBox.setInformativeText("A node has no implementation set, an execution may give you random results or a crash !");
                QString msg = QString("The following node is missing an implementation: %1.\nAvailable implementations:\n%2").
                    arg(node->title()).
                    arg(nobj->implementations().join("\n"));
                msgBox.setDetailedText(msg);
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Cancel);

                if(msgBox.exec() == QMessageBox::Cancel)
                    return false;

            }
        }
    }
    return true;
}

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Sig Events
// /////////////////////////////////////////////////////////////////

void dtkComposerScene::modify(bool b)
{
    emit modified(b);
}

void dtkComposerScene::onMaskEdge(void)
{
    // if (d->masked_edges)
    //     return;

    d->masked_edges = true;
    populateEdges();
    foreach (dtkComposerSceneEdge * edge, d->all_edges) {
        edge->setOpacity(0.05);
    }
}

void dtkComposerScene::onUnMaskEdge(void)
{
    // if (!d->masked_edges)
    //     return;

    d->masked_edges = false;
    populateEdges();
    foreach (dtkComposerSceneEdge * edge, d->all_edges) {
        edge->setOpacity(1);
    }
}

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Flag Events
// /////////////////////////////////////////////////////////////////

void dtkComposerScene::onFlagAsBlue(void)
{
    this->onFlagAs(Qt::blue);
}

void dtkComposerScene::onFlagAsGray(void)
{
    this->onFlagAs(Qt::gray);
}

void dtkComposerScene::onFlagAsGreen(void)
{
    this->onFlagAs(Qt::green);
}

void dtkComposerScene::onFlagAsOrange(void)
{
    this->onFlagAs(Qt::darkYellow);
}

void dtkComposerScene::onFlagAsRed(void)
{
    this->onFlagAs(Qt::red);
}

void dtkComposerScene::onFlagAsPink(void)
{
    this->onFlagAs(Qt::magenta);
}

void dtkComposerScene::onFlagAsYellow(void)
{
    this->onFlagAs(Qt::yellow);
}

void dtkComposerScene::onFlagAs(Qt::GlobalColor color)
{
    foreach(QGraphicsItem *item, this->selectedItems()) {

        if (dtkComposerSceneNodeLeaf *node = dynamic_cast<dtkComposerSceneNodeLeaf *>(item)) {

            if(node->flagged(color))
                d->flagged_nodes[color].removeAll(node);

            node->flag(color, !node->flagged(color));

            if(node->flagged(color))
                d->flagged_nodes[color] << node;

            emit flagged(node);
        }
    }
}

void dtkComposerScene::onBreakPointSet(void)
{
    foreach(QGraphicsItem *item, this->selectedItems()) {

        if (dtkComposerSceneNodeLeaf *node = dynamic_cast<dtkComposerSceneNodeLeaf *>(item)) {

            dtkComposerNode *wrapee = node->wrapee();

            foreach(dtkComposerGraphNode *gnode, d->graph->nodes()) {
                if (gnode->wrapee() == wrapee) {
                    if (gnode->breakpoint()) {
                        gnode->setBreakPoint(false);
                        node->flag(Qt::white, false);

                    } else {
                        gnode->setBreakPoint(true);
                        node->flag(Qt::white, true);
                    }
                    return;
                }
            }
        }
    }
}

void dtkComposerScene::onEvaluationFinished(void)
{
    if (d->last_paused_node) {
        d->last_paused_node->setOpacity(1);
        d->last_paused_node = NULL;
    }
}

void dtkComposerScene::onEvaluationPaused(dtkComposerNode *node)
{
    this->populateNodes();
    foreach (dtkComposerSceneNode * snode, d->all_nodes) {
        if (snode->wrapee() == node) {
            if (d->last_paused_node != NULL)
                d->last_paused_node->setOpacity(1);
            snode->setOpacity(0.5);
            d->last_paused_node = snode;
        }
    }
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
        QGraphicsScene::dragEnterEvent(event);
}

void dtkComposerScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        QGraphicsScene::dragLeaveEvent(event);
}

void dtkComposerScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        QGraphicsScene::dragMoveEvent(event);
}

void dtkComposerScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasUrls()) {

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

        } else if (!url.scheme().isEmpty()) {

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
    }

    QGraphicsScene::dropEvent(event);
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
        QList<dtkComposerSceneEdge *> selected_edges;

        // retrieve items to be deleted

        foreach(QGraphicsItem *item, this->selectedItems()) {
            if (dtkComposerSceneNode *snode = dynamic_cast<dtkComposerSceneNode *>(item))
                selected_nodes << snode;
            if (dtkComposerSceneNote *snote = dynamic_cast<dtkComposerSceneNote *>(item))
                selected_notes << snote;
            if (dtkComposerSceneEdge *sedge = dynamic_cast<dtkComposerSceneEdge *>(item))
                selected_edges << sedge;
        }

        // multiple node deletion

        if(selected_nodes.count() + selected_edges.count() > 1 ) {

            dtkComposerStackCommand *group = new dtkComposerStackCommand;
            group->setText("Destroy a set of nodes/edges");

            foreach(dtkComposerSceneNode *node, selected_nodes) {

                dtkComposerStackCommandDestroyNode *command = new dtkComposerStackCommandDestroyNode(group);
                command->setScene(this);
                command->setGraph(d->graph);
                command->setNode(node);
            }

            foreach(dtkComposerSceneEdge *edge, selected_edges) {

                // ne need to destroy edge if the src or dest node will be destroyed
                bool skip = false;
                foreach(dtkComposerSceneNode *node, selected_nodes)
                    if (edge->source()->node() == node || edge->destination()->node() == node) {
                        skip = true;
                    }

                if (!skip) {
                    dtkComposerStackCommandDestroyEdge *command = new dtkComposerStackCommandDestroyEdge(group);
                    command->setScene(this);
                    command->setGraph(d->graph);
                    command->setEdge(edge);
                }
            }

            d->stack->push(group);

        // single node deletion

        } else if(selected_nodes.count() == 1) {

            dtkComposerStackCommandDestroyNode *command = new dtkComposerStackCommandDestroyNode;
            command->setScene(this);
            command->setGraph(d->graph);
            command->setNode(selected_nodes.first());

            d->stack->push(command);

        // single edge deletion

        } else if(selected_edges.count() == 1) {

            dtkComposerStackCommandDestroyEdge *command = new dtkComposerStackCommandDestroyEdge;
            command->setScene(this);
            command->setGraph(d->graph);
            command->setEdge(selected_edges.first());

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
            command->setFactory(d->factory);
            command->setGraph(d->graph);
            command->setNodes(selected_nodes);
            command->setNotes(selected_notes);

            if(areBrothers(selected_nodes, selected_notes))
                d->stack->push(command);
            else
                delete command;
        }


    } else if ((event->key() == Qt::Key_C) && (event->modifiers() & Qt::ControlModifier)) {
        //copy

        d->copy_nodes.clear();

        foreach(QGraphicsItem *item, this->selectedItems()) {
            if (dtkComposerSceneNode *snode = dynamic_cast<dtkComposerSceneNode *>(item))
                d->copy_nodes << snode;
        }

    } else if ((event->key() == Qt::Key_V) && (event->modifiers() & Qt::ControlModifier) ) {
        // paste
        if (d->copy_nodes.isEmpty() || !areBrothers(d->copy_nodes))
            return;

        dtkComposerStackCommandCopyNodes *command = new dtkComposerStackCommandCopyNodes;
        command->setScene(this);
        command->setGraph(d->graph);
        command->setFactory(d->factory);
        command->setNodes(d->copy_nodes);

        d->stack->push(command);

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

    foreach(QGraphicsItem *item, this->selectedItems())
        if(dtkComposerSceneNode *node = dynamic_cast<dtkComposerSceneNode *>(item))
            node->layout();

    this->update();

// adjust_current: // Adjusting current edge

    if (d->current_edge)
        d->current_edge->adjust(d->current_edge->source()->mapToScene(d->current_edge->source()->boundingRect().center()), event->scenePos());

    if (d->current_edge)
        this->update(d->current_edge->boundingRect());

    if (d->current_edge)
        event->accept();
}

void dtkComposerScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();

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

    foreach(dtkComposerSceneEdge *e, d->connected_edges)
        e->setConnected(false);
    d->connected_edges.clear();

    // Managing of reparenting

    if (d->reparent_target && d->reparent_target != d->reparent_origin) {

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

    if (d->reparent_target == d->reparent_origin)
        this->views().at(0)->setCursor(Qt::ArrowCursor);

    d->reparent_origin_pos = QPointF();
    d->reparent_target_pos = QPointF();

    // Managing of current edge

    if(!d->current_edge) {
        foreach(QGraphicsItem *item, this->selectedItems()) {
            if (dtkComposerSceneNode *snode = dynamic_cast<dtkComposerSceneNode *>(item)) {
                if (dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(snode)) {
                    foreach(dtkComposerSceneEdge *e, composite->edges())
                        d->connected_edges << e;
                    foreach(dtkComposerSceneEdge *e, composite->inputEdges())
                        d->connected_edges << e;
                    foreach(dtkComposerSceneEdge *e, composite->outputEdges())
                        d->connected_edges << e;
                } else if (dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(snode)) {
                    d->connected_edges << control->header()->inputEdges();
                    d->connected_edges << control->footer()->outputEdges();
                    foreach(dtkComposerSceneNodeComposite *b, control->blocks()) {
                        foreach(dtkComposerSceneEdge *e, b->edges())
                             d->connected_edges << e;
                        foreach(dtkComposerSceneEdge *e, b->inputEdges())
                             d->connected_edges << e;
                        foreach(dtkComposerSceneEdge *e, b->outputEdges())
                             d->connected_edges << e;
                    }
                }
                foreach(dtkComposerSceneEdge *e, snode->inputEdges())
                    d->connected_edges << e;
                foreach(dtkComposerSceneEdge *e, snode->outputEdges())
                    d->connected_edges << e;
                foreach(dtkComposerSceneEdge *e, d->connected_edges)
                    e->setConnected(true);
            }
        }

        return;
    }

    if(dtkComposerScenePort *destination = this->portAt(event->scenePos()))
        d->current_edge->setDestination(destination);

    if(d->current_edge->link()) {
        bool srcInput = d->current_edge->source()->type() == dtkComposerScenePort::Input;
        bool dstInput = d->current_edge->destination()->type() == dtkComposerScenePort::Input;
        bool srcComposite = dynamic_cast<dtkComposerSceneNodeComposite *>(d->current_edge->source()->node()) != NULL;
        bool dstComposite = dynamic_cast<dtkComposerSceneNodeComposite *>(d->current_edge->destination()->node()) != NULL;
        bool dstParent = d->current_edge->destination()->node() == d->current_edge->source()->owner()->parent() ;
        bool srcParent = d->current_edge->source()->node() == d->current_edge->destination()->owner()->parent() ;
        bool sameParent = d->current_edge->source()->owner()->parent() == d->current_edge->destination()->owner()->parent() ;

        if (!((srcInput  && !dstInput) ||
              (!srcInput &&  dstInput &&  srcParent) ||
              (!srcInput &&  dstInput &&  dstParent) ||
              (srcInput  &&  dstInput && !srcComposite) ||
              (!srcInput && !dstInput && !dstComposite) ||
              (!sameParent && !(dstParent || srcParent)) ||
              (!srcInput && !dstInput &&  srcComposite && dstComposite && srcParent) ||
              (srcInput  &&  dstInput &&  srcComposite && dstComposite && dstParent)))
            {
                dtkComposerStackCommandCreateEdge *command = new dtkComposerStackCommandCreateEdge;
                command->setGraph(d->graph);
                command->setScene(this);
                command->setSource(d->current_edge->source());
                command->setDestination(d->current_edge->destination());

                d->stack->push(command);
            }
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
                    command->setFormer(d->current_node);
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
                    command->setNode(composite);
                    command->setFormer(d->current_node);
                    d->stack->push(command);

                } else {

                    dtkComposerStackCommandLeaveGroup *command = new dtkComposerStackCommandLeaveGroup;
                    command->setScene(this);
                    command->setNode(composite);
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
    QList<QGraphicsItem *> items = this->items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect, Qt::DescendingOrder);

    foreach(QGraphicsItem *item, items)
        if (dtkComposerSceneNode *node = dynamic_cast<dtkComposerSceneNode *>(item))
            return node;

    return NULL;
}

dtkComposerSceneNode *dtkComposerScene::nodeAt(const QPointF& point, dtkComposerSceneNode *exclude) const
{
    QList<QGraphicsItem *> items = this->items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect, Qt::DescendingOrder);

    foreach(QGraphicsItem *item, items) {
        if (dtkComposerSceneNode *node = dynamic_cast<dtkComposerSceneNode *>(item)) {

            if (node != d->current_node) {

                if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node->parent()))
                    node = control;

                if (node != exclude && !(node->parent() == exclude))
                    return node;
            }
        }
    }

    return d->current_node;
}

dtkComposerScenePort *dtkComposerScene::portAt(const QPointF& point) const
{
    QList<QGraphicsItem *> items = this->items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect, Qt::DescendingOrder);

    foreach(QGraphicsItem *item, items)
        if (dtkComposerScenePort *port = dynamic_cast<dtkComposerScenePort *>(item))
            return port;

    return NULL;
}

dtkComposerSceneNodeComposite *dtkComposerScene::parentAt(const QPointF& point) const
{
    dtkComposerSceneNode *node = this->nodeAt(point);

    if(!node)
        return d->current_node;

    if(dtkComposerSceneNodeLeaf *leaf = dynamic_cast<dtkComposerSceneNodeLeaf *>(node))
        return dynamic_cast<dtkComposerSceneNodeComposite *>(leaf->parent());

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {

        if(composite->flattened())
            return composite;

        if(composite->entered())
            return composite;

        if(!composite->flattened() && !composite->entered())
            return composite;
    }

    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {

        dtkComposerSceneNodeComposite *block = control->blockAt(control->mapFromScene(point));

        if(!block)
            return dynamic_cast<dtkComposerSceneNodeComposite *>(control->parent());

        return block;
    }

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

// /////////////////////////////////////////////////////////////////
#pragma mark -
#pragma mark - Helper functions
// /////////////////////////////////////////////////////////////////

void dtkComposerScene::populateEdges(dtkComposerSceneNode *node)
{
    if (!node) {
        node = d->root_node;
        d->all_edges.clear();
    }

    d->all_edges << node->inputEdges();
    d->all_edges << node->outputEdges();

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node))
        foreach(dtkComposerSceneNode *child, composite->nodes())
            this->populateEdges(child);

    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {
        d->all_edges << control->header()->inputEdges();
        d->all_edges << control->footer()->outputEdges();
        foreach(dtkComposerSceneNodeComposite *block, control->blocks())
            this->populateEdges(block);
    }
}

void dtkComposerScene::populateNodes(dtkComposerSceneNode *node)
{
    if (!node) {
        node = d->root_node;
        d->all_nodes.clear();
    }

    d->all_nodes << node;

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node))
        foreach(dtkComposerSceneNode *child, composite->nodes())
            this->populateNodes(child);

    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {
        foreach(dtkComposerSceneNodeComposite *block, control->blocks())
            this->populateNodes(block);
    }
}


//
// dtkComposerScene.cpp ends here

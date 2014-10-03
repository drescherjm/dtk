/* dtkComposerStackCommand.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 18:17:43 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkConfig.h>

#include "dtkComposerNodeFactory.h"
#include "dtkComposerGraph.h"
#include "dtkComposerGraphNode.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeControlCase.h"
#include "dtkComposerNodeLeaf.h"
#if defined(DTK_BUILD_DISTRIBUTED)
#include "dtkComposerNodeRemote.h"
#endif
#include "dtkComposerReader.h"
#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerSceneNote.h"
#include "dtkComposerScenePort.h"
#include "dtkComposerStackCommand.h"
#include "dtkComposerStackUtils.h"
#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterProxy.h"
#include "dtkComposerTransmitterProxyLoop.h"
#include "dtkComposerWriter.h"

#include <dtkLog/dtkLogger.h>

// /////////////////////////////////////////////////////////////////
// dtkLog categories
// /////////////////////////////////////////////////////////////////

//DTK_LOG_CATEGORY(FR_INRIA_DTK_COMPOSER_STACK, "fr.inria.dtk.composer.stack")

// /////////////////////////////////////////////////////////////////
// Base Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandPrivate
{
public:
    dtkComposerNodeFactory *factory;
    dtkComposerScene *scene;
    dtkComposerGraph *graph;
};

dtkComposerStackCommand::dtkComposerStackCommand(dtkComposerStackCommand *parent) : QUndoCommand(parent), d(new dtkComposerStackCommandPrivate)
{
    d->factory = NULL;
    d->scene = NULL;
    d->graph = NULL;
}

dtkComposerStackCommand::~dtkComposerStackCommand(void)
{
    delete d;

    d = NULL;
}

void dtkComposerStackCommand::setFactory(dtkComposerNodeFactory *factory)
{
    d->factory = factory;
}

void dtkComposerStackCommand::setScene(dtkComposerScene *scene)
{
    d->scene = scene;
}

void dtkComposerStackCommand::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
}

// /////////////////////////////////////////////////////////////////
// Create Node Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateNodePrivate
{
public:
    QString name;
    QString type;
    QPointF position;

public:
    dtkComposerSceneNode *node;

public:
    dtkComposerSceneNodeComposite *parent;
};

dtkComposerStackCommandCreateNode::dtkComposerStackCommandCreateNode(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandCreateNodePrivate)
{
    e->node = NULL;
    e->parent = NULL;
}

dtkComposerStackCommandCreateNode::~dtkComposerStackCommandCreateNode(void)
{
    delete e->node;
    delete e;

    e = NULL;
}

dtkComposerSceneNode *dtkComposerStackCommandCreateNode::node(void)
{
    return e->node;
}

void dtkComposerStackCommandCreateNode::setParent(dtkComposerSceneNodeComposite *parent)
{
    e->parent = parent;
}

void dtkComposerStackCommandCreateNode::setPosition(const QPointF& position)
{
    e->position = position;
}

void dtkComposerStackCommandCreateNode::setName(const QString& name)
{
    e->name = name;

    this->setText(QString("Create node %1").arg(e->name));
}

void dtkComposerStackCommandCreateNode::setType(const QString& type)
{
    e->type = type;
}

void dtkComposerStackCommandCreateNode::redo(void)
{

    if(!d->factory)
        return;

    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->parent)
        return;

    if(e->type.isEmpty())
        return;

    if(!e->node) {

        dtkComposerNode *node = d->factory->create(e->type);

        if(dynamic_cast<dtkComposerNodeLeaf *>(node))
            e->node = new dtkComposerSceneNodeLeaf;
        else if(dynamic_cast<dtkComposerNodeComposite *>(node) )
            e->node = new dtkComposerSceneNodeComposite;
        else
            e->node = new dtkComposerSceneNodeControl;

        e->node->wrap(node);
        e->node->setParent(e->parent);
    }

    e->node->setPos(e->position);

    e->parent->addNode(e->node);
    e->parent->layout();

    d->graph->addNode(e->node);
    d->graph->layout();

// -- ??
    if (e->parent->visible()) {
        d->scene->addItem(e->node);
        e->node->layout();
    }

    d->scene->modify(true);
// --
}

void dtkComposerStackCommandCreateNode::undo(void)
{
    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->node)
        return;

    if(!e->parent)
        return;

    if(!e->node)
        return;

    e->position = e->node->scenePos();


    d->graph->removeNode(e->node);
    d->graph->layout();

    e->parent->removeNode(e->node);
    e->parent->layout();
// -- ??
    if (e->parent->visible())
        d->scene->removeItem(e->node);

    d->scene->modify(true);
// --
}

// /////////////////////////////////////////////////////////////////
// Destroy Node Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyNodePrivate
{
public:
    dtkComposerSceneNode *node;

public:
    bool dirty;
public:
    dtkComposerSceneNodeComposite *parent;

public:
    QList<dtkComposerSceneEdge *>       input_edges;
    QList<dtkComposerSceneEdge *>      output_edges;
    QList<dtkComposerStackCommand *>  destroy_nodes;
    QList<dtkComposerStackCommandDestroyEdge *>  destroy_edges;

};

dtkComposerStackCommandDestroyNode::dtkComposerStackCommandDestroyNode(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandDestroyNodePrivate)
{
    e->node = NULL;
    e->parent = NULL;
    e->dirty = true;
}

dtkComposerStackCommandDestroyNode::~dtkComposerStackCommandDestroyNode(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandDestroyNode::setNode(dtkComposerSceneNode *node)
{
    e->node = node;

    e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->node->parent());

    if (dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {

        foreach(dtkComposerSceneNode *subnode, composite->nodes()) {
            dtkComposerStackCommandDestroyNode *cmd = new dtkComposerStackCommandDestroyNode();
            cmd->setScene(d->scene);
            cmd->setGraph(d->graph);
            cmd->setNode(subnode);
            e->destroy_nodes << cmd;
        }
        foreach(dtkComposerSceneNote *subnote, composite->notes()) {
            dtkComposerStackCommandDestroyNote *cmd = new dtkComposerStackCommandDestroyNote();
            cmd->setScene(d->scene);
            cmd->setNote(subnote);
            e->destroy_nodes << cmd;
        }

    } else if (dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {

        foreach(dtkComposerSceneNodeComposite *block, control->blocks()) {
            foreach(dtkComposerSceneNode *subnode, block->nodes()) {
                dtkComposerStackCommandDestroyNode *cmd = new dtkComposerStackCommandDestroyNode();
                cmd->setScene(d->scene);
                cmd->setGraph(d->graph);
                cmd->setNode(subnode);
                e->destroy_nodes << cmd;
            }
            foreach(dtkComposerSceneNote *subnote, block->notes()) {
                dtkComposerStackCommandDestroyNote *cmd = new dtkComposerStackCommandDestroyNote();
                cmd->setScene(d->scene);
                cmd->setNote(subnote);
                e->destroy_nodes << cmd;
            }
        }

    }

    this->setText(QString("Destroy node %1").arg(e->node->title()));
}

void dtkComposerStackCommandDestroyNode::redo(void)
{
    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->parent)
        return;

    if(!e->node)
        return;

    if(e->dirty) {

        foreach(dtkComposerSceneEdge *edge, e->node->inputEdges()){
            e->destroy_edges << new dtkComposerStackCommandDestroyEdge;
            e->destroy_edges.last()->setFactory(d->factory);
            e->destroy_edges.last()->setScene(d->scene);
            e->destroy_edges.last()->setGraph(d->graph);
            e->destroy_edges.last()->setEdge(edge);
            e->destroy_edges.last()->redo();
            // if (d->scene->items().contains(edge))
            //     d->scene->removeItem(edge);
            // d->graph->removeEdge(edge);
            // e->parent->removeEdge(edge);
            // e->input_edges << edge;
            // edge->unlink();
        }

        foreach(dtkComposerSceneEdge *edge, e->node->outputEdges()){
            e->destroy_edges << new dtkComposerStackCommandDestroyEdge;
            e->destroy_edges.last()->setFactory(d->factory);
            e->destroy_edges.last()->setScene(d->scene);
            e->destroy_edges.last()->setGraph(d->graph);
            e->destroy_edges.last()->setEdge(edge);
            e->destroy_edges.last()->redo();
        }

        if (dtkComposerSceneNodeControl *control = dynamic_cast< dtkComposerSceneNodeControl * >(e->node)) {

            foreach(dtkComposerSceneNodeComposite *block, control->blocks()) {
                foreach(dtkComposerSceneEdge *edge, block->inputEdges()) {
                    e->destroy_edges << new dtkComposerStackCommandDestroyEdge;
                    e->destroy_edges.last()->setFactory(d->factory);
                    e->destroy_edges.last()->setScene(d->scene);
                    e->destroy_edges.last()->setGraph(d->graph);
                    e->destroy_edges.last()->setEdge(edge);
                    e->destroy_edges.last()->redo();
                }
                foreach(dtkComposerSceneEdge *edge, block->outputEdges()) {
                    e->destroy_edges << new dtkComposerStackCommandDestroyEdge;
                    e->destroy_edges.last()->setFactory(d->factory);
                    e->destroy_edges.last()->setScene(d->scene);
                    e->destroy_edges.last()->setGraph(d->graph);
                    e->destroy_edges.last()->setEdge(edge);
                    e->destroy_edges.last()->redo();
                }
            }
            foreach(dtkComposerSceneEdge *edge, control->header()->inputEdges()){
                e->destroy_edges << new dtkComposerStackCommandDestroyEdge;
                e->destroy_edges.last()->setFactory(d->factory);
                e->destroy_edges.last()->setScene(d->scene);
                e->destroy_edges.last()->setGraph(d->graph);
                e->destroy_edges.last()->setEdge(edge);
                e->destroy_edges.last()->redo();
            }
            foreach(dtkComposerSceneEdge *edge, control->footer()->outputEdges()){
                e->destroy_edges << new dtkComposerStackCommandDestroyEdge;
                e->destroy_edges.last()->setFactory(d->factory);
                e->destroy_edges.last()->setScene(d->scene);
                e->destroy_edges.last()->setGraph(d->graph);
                e->destroy_edges.last()->setEdge(edge);
                e->destroy_edges.last()->redo();
            }
        }
        e->dirty = false;
    } else {
        foreach(dtkComposerStackCommand *destroy_edge, e->destroy_edges)
            destroy_edge->redo();
    }

    const int listSize = e->destroy_nodes.size();
    for (int i = 0; i < listSize; ++i)
        e->destroy_nodes.at(i)->redo();

    d->graph->removeNode(e->node);
    d->graph->layout();

    e->parent->removeNode(e->node);
    e->parent->layout();

    if (e->parent->visible())
        d->scene->removeItem(e->node);

    d->scene->modify(true);
}

void dtkComposerStackCommandDestroyNode::undo(void)
{
    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->parent)
        return;

    if(!e->node)
        return;

    e->parent->addNode(e->node);
    d->graph->addNode(e->node);

    if (e->parent->visible())
        d->scene->addItem(e->node);

    const int listSize = e->destroy_nodes.size();
    for (int i = listSize-1; i >= 0; --i)
        e->destroy_nodes.at(i)->undo();

    e->parent->layout();

    foreach(dtkComposerStackCommand *cmd, e->destroy_edges)
        cmd->undo();

    d->graph->layout();


    d->scene->modify(true);
}

// /////////////////////////////////////////////////////////////////
// Create Edge Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateEdgePrivate
{
public:
    dtkComposerScenePort *source;
    dtkComposerScenePort *destination;

public:
    dtkComposerSceneEdge *edge;

public:
    dtkComposerSceneNodeComposite *parent;
};

dtkComposerStackCommandCreateEdge::dtkComposerStackCommandCreateEdge(void) : dtkComposerStackCommand(), e(new dtkComposerStackCommandCreateEdgePrivate)
{
    e->edge = NULL;
    e->source = NULL;
    e->destination = NULL;
    e->parent = NULL;

    this->setText("Create edge");
}

dtkComposerStackCommandCreateEdge::~dtkComposerStackCommandCreateEdge(void)
{
    delete e->edge;
    delete e;

    e = NULL;
}

void dtkComposerStackCommandCreateEdge::setSource(dtkComposerScenePort *source)
{
    e->source = source;
}

void dtkComposerStackCommandCreateEdge::setDestination(dtkComposerScenePort *destination)
{
    e->destination = destination;
}

void dtkComposerStackCommandCreateEdge::redo(void)
{
    if(!d->graph)
        return;

    if(!d->scene)
        return;

    if(!e->parent)
        this->setParent();

    if(!e->parent)
        return;

    if(!e->source)
        return;

    if(!e->destination)
        return;

    if(!e->edge) {
        e->edge = new dtkComposerSceneEdge;
        e->edge->setParent(e->parent);
        e->edge->setSource(e->source);
        e->edge->setDestination(e->destination);
    }

    e->edge->link();

    e->parent->addEdge(e->edge);

    if(e->parent->visible()) {

        d->scene->addItem(e->edge);

        if (d->scene->items().contains(e->source->node())) {
            if (e->source->node() != e->parent) {
                if (e->source->owner()->parent() == e->parent)
                    e->edge->stackBefore(e->source->owner());
                else
                    e->edge->stackBefore(e->source->node());
            }
        }

        if (d->scene->items().contains(e->destination->node())) {
            if (e->destination->node() != e->parent) {
                if (e->destination->owner()->parent() == e->parent)
                    e->edge->stackBefore(e->destination->owner());
                else
                    e->edge->stackBefore(e->destination->node());
            }
        }
    }

    d->scene->modify(true);

    // Setting up control flow

    d->graph->addEdge(e->edge);

    // Setting up data flow

    dtkComposerTransmitterConnection(d->scene->root(), e->parent, e->edge);
}

void dtkComposerStackCommandCreateEdge::undo(void)
{
    if(!d->scene)
        return;

    if(!e->parent)
        return;

    if(!e->edge)
        return;

    // Setting up data flow

    dtkComposerTransmitterDisconnection(d->scene->root(), e->parent, e->edge);

    // Setting up scene

    e->edge->unlink();

    e->parent->removeEdge(e->edge);

    // Setting up control flow

    d->graph->removeEdge(e->edge);

    if(e->parent->visible())
        d->scene->removeItem(e->edge);

    d->scene->modify(true);
}

void dtkComposerStackCommandCreateEdge::setParent(void)
{
    if(!e->source)
        return;

    if(!e->destination)
        return;

    if(e->parent)
        return;

    if(e->source->node()->parent() == e->destination->node()->parent())
        e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->source->node()->parent());
    else if(e->source->node() == e->destination->node()->parent())
        e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->source->node());
    else if(e->destination->node() == e->source->node()->parent())
        e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->destination->node());
    else if(e->source->node()->parent()->parent() == e->destination->node()->parent())
        e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->source->node()->parent()->parent());
    else if(e->destination->node()->parent()->parent() == e->source->node()->parent())
        e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->destination->node()->parent()->parent());
    else if(e->source->node()->parent()->parent() == e->destination->node())
        e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->destination->node());
    else if(e->destination->node()->parent()->parent() == e->source->node())
        e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->source->node());
    else if(e->source->node()->parent()->parent() == e->destination->node()->parent()->parent())
        e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->destination->node()->parent()->parent());
    else
        qDebug() << Q_FUNC_INFO << "Unhandled case" ;
}

void dtkComposerStackCommandCreateEdge::setParent(dtkComposerSceneNodeComposite *parent)
{
    e->parent = parent;
}

// /////////////////////////////////////////////////////////////////
// Destroy Edge Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyEdgePrivate
{
public:
    dtkComposerSceneEdge *edge;

public:
    dtkComposerSceneNodeComposite *parent;
};

dtkComposerStackCommandDestroyEdge::dtkComposerStackCommandDestroyEdge(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandDestroyEdgePrivate)
{
    e->edge = NULL;
    e->parent = NULL;

    this->setText("Destroy edge");
}

dtkComposerStackCommandDestroyEdge::~dtkComposerStackCommandDestroyEdge(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandDestroyEdge::setEdge(dtkComposerSceneEdge *edge)
{
    e->edge = edge;

    e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(edge->parent());
}

void dtkComposerStackCommandDestroyEdge::redo(void)
{
    if(!e->edge) {
        dtkError() << "no edge in destroy edge!" ;
        return;
    }

    if(!e->parent) {
        dtkError() << "no parent in destroy edge!" ;
        return;
    }

    if(!d->graph) {
        dtkError() << "no graph in destroy edge!" ;
        return;
    }

    // Setting up control flow

    d->graph->removeEdge(e->edge);

    // Setting up data flow

    dtkComposerTransmitterDisconnection(d->scene->root(), e->parent, e->edge);

    // Setting up scene

    e->edge->unlink();

    e->parent->removeEdge(e->edge);


    if(e->parent->visible())
        d->scene->removeItem(e->edge);

    d->scene->modify(true);
}

void dtkComposerStackCommandDestroyEdge::undo(void)
{
    if(!e->edge) {
        dtkError() << "no edge in destroy edge undo!" ;
        return;
    }

    if(!e->parent) {
        dtkError() << "no parent in destroy edge undo!" ;
        return;
    }

    if(!d->graph) {
        dtkError() << "no graph in destroy edge undo!" ;
        return;
    }

    e->edge->link();

    e->parent->addEdge(e->edge);

    if(e->parent->visible())
        d->scene->addItem(e->edge);

    e->edge->adjust();
    d->scene->modify(true);

    // Setting up control flow

    d->graph->addEdge(e->edge);

    // Setting up data flow

    dtkComposerTransmitterConnection(d->scene->root(), e->parent, e->edge);
}

// /////////////////////////////////////////////////////////////////
// Create Note Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateNotePrivate
{
public:
    QPointF position;

public:
    dtkComposerSceneNote *note;

public:
    dtkComposerSceneNodeComposite *parent;
};

dtkComposerStackCommandCreateNote::dtkComposerStackCommandCreateNote(dtkComposerStackCommand *parent) : dtkComposerStackCommand(), e(new dtkComposerStackCommandCreateNotePrivate)
{
    e->note = NULL;
    e->parent = NULL;

    this->setText("Create note");
}

dtkComposerStackCommandCreateNote::~dtkComposerStackCommandCreateNote(void)
{
    delete e->note;
    delete e;

    e = NULL;
}

void dtkComposerStackCommandCreateNote::setParent(dtkComposerSceneNodeComposite *parent)
{
    e->parent = parent;
}

void dtkComposerStackCommandCreateNote::setPosition(const QPointF& position)
{
    e->position = position;
}

void dtkComposerStackCommandCreateNote::redo(void)
{
    if(!d->scene)
        return;

    if(!e->parent)
        return;

    if(!e->note) {
        e->note = new dtkComposerSceneNote;
        e->note->setParent(e->parent);
    }

    e->note->setPos(e->position);

    e->parent->addNote(e->note);

    if (e->parent->visible())
        d->scene->addItem(e->note);
    d->scene->modify(true);
}

void dtkComposerStackCommandCreateNote::undo(void)
{
    if(!e->parent)
        return;

    if(!e->note)
        return;

    e->position = e->note->scenePos();

    e->parent->removeNote(e->note);

    if (e->parent->visible())
        d->scene->removeItem(e->note);

    d->scene->modify(true);
}

// /////////////////////////////////////////////////////////////////
// Destroy Note Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyNotePrivate
{
public:
    QPointF position;

public:
    dtkComposerSceneNote *note;

public:
    dtkComposerSceneNodeComposite *parent;
};

dtkComposerStackCommandDestroyNote::dtkComposerStackCommandDestroyNote(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandDestroyNotePrivate)
{
    e->parent = NULL;
    e->note = NULL;

    this->setText("Destroy note");
}

dtkComposerStackCommandDestroyNote::~dtkComposerStackCommandDestroyNote(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandDestroyNote::setNote(dtkComposerSceneNote *note)
{
    e->note = note;

    e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->note->parent());
}

void dtkComposerStackCommandDestroyNote::redo(void)
{
    if(!d->scene)
        return;

    if(!e->parent)
        return;

    if(!e->note)
        return;

    e->position = e->note->pos();

    e->parent->removeNote(e->note);

    if (e->parent->visible())
        d->scene->removeItem(e->note);

    d->scene->modify(true);
}

void dtkComposerStackCommandDestroyNote::undo(void)
{
    if(!d->scene)
        return;

    if(!e->parent)
        return;

    if(!e->note)
        return;

    e->parent->addNote(e->note);

    e->note->setPos(e->position);

    if (e->parent->visible())
        d->scene->addItem(e->note);

    d->scene->modify(true);
}

// /////////////////////////////////////////////////////////////////
// Create Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateGroupPrivate
{
public:
    dtkComposerSceneNodeComposite *node;

public:
    dtkComposerSceneNodeComposite *parent;

public:
    QList<dtkComposerSceneNote *> notes;

public:
    QList<dtkComposerStackCommandReparentNode *> reparent;

public:
    dtkComposerSceneNodeList nodes;

public:
    QPointF pos;

public:
    bool dirty;
};

dtkComposerStackCommandCreateGroup::dtkComposerStackCommandCreateGroup(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandCreateGroupPrivate)
{
    e->parent = NULL;
    e->node   = NULL;
    e->dirty = true;

    this->setText("Create group");
}

dtkComposerStackCommandCreateGroup::~dtkComposerStackCommandCreateGroup(void)
{
    qDeleteAll(e->reparent);

    e->reparent.clear();

    delete e;

    e = NULL;
}

void dtkComposerStackCommandCreateGroup::setNodes(dtkComposerSceneNodeList nodes)
{
    QRectF rect;

    e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(nodes.first()->parent());

    if(!e->node && e->parent) {
        e->node = new dtkComposerSceneNodeComposite;
        e->node->wrap(new dtkComposerNodeComposite);
        e->node->setParent(e->parent);
    }

    foreach(dtkComposerSceneNode *node, nodes) {
        if(node->parent() == e->parent) {
            rect |= node->sceneBoundingRect();
        }
    }

    e->pos = rect.center();

    e->nodes = nodes;
}

void dtkComposerStackCommandCreateGroup::setNotes(dtkComposerSceneNoteList notes)
{
    if(!e->parent)
        return;

    foreach(dtkComposerSceneNote *note, notes)
        if(note->parent() == e->parent)
            e->notes << note;
}

void dtkComposerStackCommandCreateGroup::redo(void)
{
    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->parent)
        return;

    if(!e->node)
        return;

    e->parent->addNode(e->node);

    d->graph->addNode(e->node);
    d->graph->layout();

    e->node->setPos(e->pos - e->node->boundingRect().center());

    if(e->dirty) {
        foreach(dtkComposerSceneNode *node, e->nodes) {
            if(node->parent() == e->parent) {
                e->reparent << new dtkComposerStackCommandReparentNode;
                e->reparent.last()->setFactory(d->factory);
                e->reparent.last()->setScene(d->scene);
                e->reparent.last()->setGraph(d->graph);
                e->reparent.last()->setOriginNode(node);
                e->reparent.last()->setOriginPosition(node->sceneBoundingRect().topLeft());
                e->reparent.last()->setTargetPosition(node->sceneBoundingRect().topLeft());
                e->reparent.last()->setTargetNode(e->node);
                e->reparent.last()->redo();
            }
        }

        e->dirty = false;

    } else {
        foreach(dtkComposerStackCommandReparentNode *command, e->reparent)
            command->redo();
    }

    foreach(dtkComposerSceneNote *note, e->notes) {
        e->parent->removeNote(note);
        d->scene->removeItem(note);
        e->node->addNote(note);
        note->setParent(e->node);
    }

    d->scene->addItem(e->node);
    d->scene->modify(true);
    d->scene->update();
}

void dtkComposerStackCommandCreateGroup::undo(void)
{
    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->parent)
        return;

    if(!e->node)
        return;

    foreach(dtkComposerSceneNote *note, e->notes) {
        e->parent->addNote(note);
        d->scene->addItem(note);
        e->node->removeNote(note);
        note->setParent(e->node->parent());
    }

    // roll back reparent commands

    QListIterator<dtkComposerStackCommandReparentNode *> i(e->reparent);
    i.toBack();
    while (i.hasPrevious())
        i.previous()->undo();
    
    // --

   d->graph->removeNode(e->node);
   d->graph->layout();

    e->parent->removeNode(e->node);

    if (e->parent->visible())
        d->scene->removeItem(e->node);

    d->scene->update();
    d->scene->modify(true);
}

// /////////////////////////////////////////////////////////////////
// Destroy Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyGroupPrivate
{
public:
    dtkComposerSceneNodeComposite *node;

public:
    dtkComposerSceneNodeComposite *parent;

public:
    QList<dtkComposerSceneNode *> nodes;

public:
    QList<dtkComposerSceneNote *> notes;

public:
    QList<dtkComposerStackCommandReparentNode *> reparent;

public:
    bool dirty;
};

dtkComposerStackCommandDestroyGroup::dtkComposerStackCommandDestroyGroup(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandDestroyGroupPrivate)
{
    e->parent = NULL;
    e->node = NULL;
    e->dirty = true;

    this->setText("Destroy group");
}

dtkComposerStackCommandDestroyGroup::~dtkComposerStackCommandDestroyGroup(void)
{
    qDeleteAll(e->reparent);

    e->reparent.clear();

    delete e;
    
    e = NULL;
}

void dtkComposerStackCommandDestroyGroup::setNode(dtkComposerSceneNodeComposite *node)
{
    e->node  = node;
    e->nodes = node->nodes();
    e->notes = node->notes();
    e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(node->parent());
}

void dtkComposerStackCommandDestroyGroup::redo(void)
{
    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->parent)
        return;

    if(!e->node)
        return;

    foreach(dtkComposerSceneNote *note, e->notes) {
        e->parent->addNote(note);
        d->scene->addItem(note);
        e->node->removeNote(note);
        note->setParent(e->node->parent());
    }
    
    if(e->dirty) {
        foreach(dtkComposerSceneNode *node, e->nodes) {
            e->reparent << new dtkComposerStackCommandReparentNode;
            e->reparent.last()->setFactory(d->factory);
            e->reparent.last()->setScene(d->scene);
            e->reparent.last()->setGraph(d->graph);
            e->reparent.last()->setOriginNode(node);
            e->reparent.last()->setOriginPosition(node->sceneBoundingRect().topLeft());
            e->reparent.last()->setTargetPosition(node->sceneBoundingRect().topLeft());
            e->reparent.last()->setTargetNode(e->parent);
            e->reparent.last()->redo();
        }

        e->dirty = false;

    } else {

        foreach(dtkComposerStackCommandReparentNode *command, e->reparent)
            command->redo();

    }

    d->graph->removeNode(e->node);
    d->graph->layout();

    e->parent->removeNode(e->node);

    d->scene->removeItem(e->node);
    d->scene->modify(true);
    d->scene->update();
}

void dtkComposerStackCommandDestroyGroup::undo(void)
{
    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->parent)
        return;

    if(!e->node)
        return;

    e->parent->addNode(e->node);

    d->graph->addNode(e->node);
    d->graph->layout();

    QRectF rect;
    foreach(dtkComposerSceneNode *node, e->nodes) {
        rect |= node->sceneBoundingRect();
    }

    e->node->setPos(rect.center() - e->node->boundingRect().center());
    
    // roll back reparent commands

    QListIterator<dtkComposerStackCommandReparentNode *> i(e->reparent);
    i.toBack();
    while (i.hasPrevious())
        i.previous()->undo();
    
    // --

    foreach(dtkComposerSceneNote *note, e->notes) {
        e->parent->removeNote(note);
        d->scene->removeItem(note);
        e->node->addNote(note);
        note->setParent(e->node);
    }

    if (e->parent->visible())
        d->scene->addItem(e->node);

    d->scene->update();
    d->scene->modify(true);
}

// /////////////////////////////////////////////////////////////////
// Enter Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandEnterGroupPrivate
{
public:
    dtkComposerSceneNodeComposite *node;

public:
    dtkComposerSceneNodeComposite *former;
};

dtkComposerStackCommandEnterGroup::dtkComposerStackCommandEnterGroup(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandEnterGroupPrivate)
{
    e->node = NULL;
    e->former = NULL;

    this->setText("Enter group");
}

dtkComposerStackCommandEnterGroup::~dtkComposerStackCommandEnterGroup(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandEnterGroup::setNode(dtkComposerSceneNodeComposite *node)
{
    e->node = node;
}

void dtkComposerStackCommandEnterGroup::setFormer(dtkComposerSceneNodeComposite *former)
{
    e->former = former;
}

void dtkComposerStackCommandEnterGroup::redo(void)
{
    if(!e->node)
        return;

    e->node->setFormer(e->former);

    e->node->setUnrevealRect(e->node->sceneBoundingRect());
    e->node->setUnrevealPos(e->node->scenePos());

    d->scene->removeItem(e->former);

    e->node->enter();

    d->scene->addItem(e->node);
    d->scene->setCurrent(e->node);
    d->scene->update();
}

void dtkComposerStackCommandEnterGroup::undo(void)
{
    if(!e->node)
        return;

    d->scene->removeItem(e->node);

    e->node->leave();
    e->node->setPos(e->node->unrevealPos());
    e->node->layout();

    d->scene->setCurrent(e->former);
    d->scene->addItem(e->former);
    d->scene->update();
}

// /////////////////////////////////////////////////////////////////
// Leave Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandLeaveGroupPrivate
{
public:
    dtkComposerSceneNodeComposite *node;
};

dtkComposerStackCommandLeaveGroup::dtkComposerStackCommandLeaveGroup(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandLeaveGroupPrivate)
{
    e->node = NULL;

    this->setText("Leave group");
}

dtkComposerStackCommandLeaveGroup::~dtkComposerStackCommandLeaveGroup(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandLeaveGroup::setNode(dtkComposerSceneNodeComposite *node)
{
    e->node = node;
}

void dtkComposerStackCommandLeaveGroup::redo(void)
{
    if(!e->node)
        return;

    d->scene->removeItem(e->node);

    e->node->leave();
    e->node->setPos(e->node->unrevealPos());
    e->node->layout();

    d->scene->addItem(e->node->former());
    d->scene->setCurrent(e->node->former());

    d->scene->update();
}

void dtkComposerStackCommandLeaveGroup::undo(void)
{
    if(!e->node)
        return;

    e->node->setUnrevealRect(e->node->sceneBoundingRect());
    e->node->setUnrevealPos(e->node->scenePos());

    d->scene->removeItem(e->node->former());

    e->node->enter();
    
    d->scene->addItem(e->node);
    d->scene->setCurrent(e->node);

    d->scene->update();
}

// /////////////////////////////////////////////////////////////////
// Flatten Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandFlattenGroupPrivate
{
public:
    dtkComposerSceneNodeComposite *node;
};

dtkComposerStackCommandFlattenGroup::dtkComposerStackCommandFlattenGroup(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandFlattenGroupPrivate)
{
    e->node = NULL;

    this->setText("Flatten group");
}

dtkComposerStackCommandFlattenGroup::~dtkComposerStackCommandFlattenGroup(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandFlattenGroup::setNode(dtkComposerSceneNodeComposite *node)
{
    e->node = node;
}

void dtkComposerStackCommandFlattenGroup::redo(void)
{
    if(!e->node)
        return;

    e->node->setUnrevealPos(e->node->scenePos());

    d->scene->removeItem(e->node);

    e->node->flatten();
    e->node->layout();

    d->scene->addItem(e->node);


    d->scene->update();
}

void dtkComposerStackCommandFlattenGroup::undo(void)
{
    if(!e->node)
        return;

    d->scene->removeItem(e->node);

    e->node->unflatten();
    e->node->setPos(e->node->unrevealPos());
    e->node->layout();

    d->scene->addItem(e->node);
    d->scene->update();
}

// /////////////////////////////////////////////////////////////////
// Unflatten Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandUnflattenGroupPrivate
{
public:
    dtkComposerSceneNodeComposite *node;
};

dtkComposerStackCommandUnflattenGroup::dtkComposerStackCommandUnflattenGroup(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandUnflattenGroupPrivate)
{
    e->node = NULL;

    this->setText("Unflatten group");
}

dtkComposerStackCommandUnflattenGroup::~dtkComposerStackCommandUnflattenGroup(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandUnflattenGroup::setNode(dtkComposerSceneNodeComposite *node)
{
    e->node = node;
}

void dtkComposerStackCommandUnflattenGroup::redo(void)
{
    if(!e->node)
        return;

    d->scene->removeItem(e->node);

    e->node->unflatten();
    e->node->setPos(e->node->unrevealPos());
    e->node->layout();

    d->scene->addItem(e->node);
    d->scene->update();
}

void dtkComposerStackCommandUnflattenGroup::undo(void)
{
    if(!e->node)
        return;

    e->node->setUnrevealPos(e->node->scenePos());

    d->scene->removeItem(e->node);

    e->node->flatten();
    e->node->layout();

    d->scene->addItem(e->node);
    d->scene->update();
}

// /////////////////////////////////////////////////////////////////
// Create Port Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreatePortPrivate
{
public:
    dtkComposerSceneNodeComposite *node;
    dtkComposerScenePort *port;

public:
    dtkComposerTransmitter *transmitter;

public:
    int type;

public:
    dtkComposerTransmitter::Kind kind;
};

dtkComposerStackCommandCreatePort::dtkComposerStackCommandCreatePort(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandCreatePortPrivate)
{
    e->node = NULL;
    e->port = NULL;
    e->transmitter = NULL;
    e->type = -1;
    e->kind = dtkComposerTransmitter::Proxy;

    this->setText("Create port");
}

dtkComposerStackCommandCreatePort::~dtkComposerStackCommandCreatePort(void)
{
    delete e;

    e = NULL;
}

dtkComposerScenePort *dtkComposerStackCommandCreatePort::port(void)
{
    return e->port;
}

void dtkComposerStackCommandCreatePort::setKind(dtkComposerTransmitter::Kind kind)
{
    e->kind = kind;
}

void dtkComposerStackCommandCreatePort::setNode(dtkComposerSceneNodeComposite *node)
{
    e->node = node;
}

void dtkComposerStackCommandCreatePort::setType(int type)
{
    e->type = type;
}

void dtkComposerStackCommandCreatePort::redo(void)
{
    if(!d->scene)
        return;

    if(!e->node)
        return;

    if(e->type < 0)
        return;

    switch(e->type) {
    case dtkComposerScenePort::Input:
        if(!e->port)
            e->port = new dtkComposerScenePort(dtkComposerScenePort::Input, e->node);
        if(!e->transmitter) {
            switch(e->kind) {
            case dtkComposerTransmitter::ProxyLoop:
                e->transmitter = new dtkComposerTransmitterProxyLoop(e->node->wrapee());
                break;
            default:
                e->transmitter = new dtkComposerTransmitterProxy(e->node->wrapee());
                break;
            }
        }
        e->node->addInputPort(e->port);
        e->node->layout();
        e->transmitter->setRequired(false);
        e->node->wrapee()->appendReceiver(e->transmitter);
        break;
    case dtkComposerScenePort::Output:
        if(!e->port)
            e->port = new dtkComposerScenePort(dtkComposerScenePort::Output, e->node);
        if(!e->transmitter) {
            switch(e->kind) {
            case dtkComposerTransmitter::ProxyLoop:
                e->transmitter = new dtkComposerTransmitterProxyLoop(e->node->wrapee());
                break;
            default:
                e->transmitter = new dtkComposerTransmitterProxy(e->node->wrapee());
                break;
            }
        }
        e->node->addOutputPort(e->port);
        e->node->layout();
        e->transmitter->setRequired(false);
        e->node->wrapee()->appendEmitter(e->transmitter);
        break;
    default:
        break;
    }

    e->port->setVisible(true);

    d->scene->update();
}

void dtkComposerStackCommandCreatePort::undo(void)
{
    if(!e->node)
        return;

    if(!e->port)
        return;

    if(!e->transmitter)
        return;

    if(!d->scene)
        return;

    if(e->type < 0)
        return;

    switch(e->type) {
    case dtkComposerScenePort::Input:
        e->node->wrapee()->removeReceiver(e->transmitter);
        e->node->removeInputPort(e->port);
        e->node->layout();
        break;
    case dtkComposerScenePort::Output:
        e->node->wrapee()->removeEmitter(e->transmitter);
        e->node->removeOutputPort(e->port);
        e->node->layout();
        break;
    default:
        break;
    }

    e->port->setVisible(false);

    d->scene->update();
}

// /////////////////////////////////////////////////////////////////
// Destroy Port Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyPortPrivate
{
public:
    dtkComposerSceneNodeComposite *node;
    dtkComposerScenePort *port;

public:
    dtkComposerTransmitter *transmitter;

public:
    QList<dtkComposerStackCommandDestroyEdge *> destroy_left_edges;
    QList<dtkComposerStackCommandDestroyEdge *> destroy_right_edges;
};

dtkComposerStackCommandDestroyPort::dtkComposerStackCommandDestroyPort(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandDestroyPortPrivate)
{
    e->node = NULL;
    e->port = NULL;
    e->transmitter = NULL;

    this->setText("Destroy port");
}

dtkComposerStackCommandDestroyPort::~dtkComposerStackCommandDestroyPort(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandDestroyPort::setNode(dtkComposerSceneNodeComposite *node)
{
    e->node = node;
}

void dtkComposerStackCommandDestroyPort::setPort(dtkComposerScenePort *port)
{
    if (!e->node)
        return;

    e->port = port;

    switch(e->port->type()) {
    case dtkComposerScenePort::Input:
        e->transmitter = e->node->wrapee()->receivers().at(e->node->inputPorts().indexOf(e->port));
        foreach(dtkComposerSceneEdge *l_edge, e->node->inputEdges()) {
            if (l_edge->destination() == e->port) {
                e->destroy_left_edges << new dtkComposerStackCommandDestroyEdge;
                e->destroy_left_edges.last()->setFactory(d->factory);
                e->destroy_left_edges.last()->setScene(d->scene);
                e->destroy_left_edges.last()->setGraph(d->graph);
                e->destroy_left_edges.last()->setEdge(l_edge);
            }
        }
        if (dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(e->node)) {
            foreach(dtkComposerSceneEdge *r_edge, composite->edges()) {
                if (r_edge->source() == e->port) {
                    e->destroy_right_edges << new dtkComposerStackCommandDestroyEdge;
                    e->destroy_right_edges.last()->setFactory(d->factory);
                    e->destroy_right_edges.last()->setScene(d->scene);
                    e->destroy_right_edges.last()->setGraph(d->graph);
                    e->destroy_right_edges.last()->setEdge(r_edge);
                }
            }
        }
        break;
    case dtkComposerScenePort::Output:
        e->transmitter = e->node->wrapee()->emitters().at(e->node->outputPorts().indexOf(e->port));
        foreach(dtkComposerSceneEdge *r_edge, e->node->outputEdges()) {
            if (r_edge->source() == e->port) {
                e->destroy_right_edges << new dtkComposerStackCommandDestroyEdge;
                e->destroy_right_edges.last()->setFactory(d->factory);
                e->destroy_right_edges.last()->setScene(d->scene);
                e->destroy_right_edges.last()->setGraph(d->graph);
                e->destroy_right_edges.last()->setEdge(r_edge);
            }
        }
        if (dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(e->node)) {
            foreach(dtkComposerSceneEdge *l_edge, composite->edges()) {
                if (l_edge->destination() == e->port) {
                    e->destroy_left_edges << new dtkComposerStackCommandDestroyEdge;
                    e->destroy_left_edges.last()->setFactory(d->factory);
                    e->destroy_left_edges.last()->setScene(d->scene);
                    e->destroy_left_edges.last()->setGraph(d->graph);
                    e->destroy_left_edges.last()->setEdge(l_edge);
                }
            }
        }
        break;
    }
}

void dtkComposerStackCommandDestroyPort::redo(void)
{
    if(!e->node)
        return;

    if(!e->port)
        return;

    if(!e->transmitter)
        return;

    if(!d->scene)
        return;

    foreach(dtkComposerStackCommandDestroyEdge *destroy_left_edge, e->destroy_left_edges)
        destroy_left_edge->redo();
        
    foreach(dtkComposerStackCommandDestroyEdge *destroy_right_edge, e->destroy_right_edges)
        destroy_right_edge->redo();

    switch(e->port->type()) {
    case dtkComposerScenePort::Input:
        e->node->wrapee()->removeReceiver(e->transmitter);
        e->node->removeInputPort(e->port);
        e->node->layout();
        break;
    case dtkComposerScenePort::Output:
        e->node->removeOutputPort(e->port);
        e->node->wrapee()->removeEmitter(e->transmitter);
        e->node->layout();
        break;
    default:
        break;
    };

    e->port->setVisible(false);

    d->scene->update();
}

void dtkComposerStackCommandDestroyPort::undo(void)
{
    if(!e->node)
        return;

    if(!e->port)
        return;

    if(!e->transmitter)
        return;

    switch(e->port->type()) {
    case dtkComposerScenePort::Input:
        e->node->addInputPort(e->port);
        e->node->wrapee()->appendReceiver(e->transmitter);
        e->node->layout();
        break;
    case dtkComposerScenePort::Output:
        e->node->addOutputPort(e->port);
        e->node->wrapee()->appendEmitter(e->transmitter);
        e->node->layout();
        break;
    default:
        break;
    }

    e->port->setVisible(true);

    foreach(dtkComposerStackCommandDestroyEdge *destroy_left_edge, e->destroy_left_edges)
        destroy_left_edge->undo();

    foreach(dtkComposerStackCommandDestroyEdge *destroy_right_edge, e->destroy_right_edges)
        destroy_right_edge->undo();

    d->scene->update();
}

// /////////////////////////////////////////////////////////////////
// Reparent Node Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandReparentNodePrivate
{
public:
    dtkComposerSceneNodeComposite *ancestor(dtkComposerSceneNodeComposite *from, dtkComposerSceneNodeComposite *to);

public:
    enum Direction {
        None,
        Decomposition,
        Down,
        Up
    };

public:
    QPointF origin_pos;
    QPointF target_pos;

public:
    dtkComposerSceneNode *origin;

public:
    dtkComposerSceneNodeComposite *source;
    dtkComposerSceneNodeComposite *target;

public:
    Direction direction;

public:
    QList<dtkComposerStackCommandReparentNode *> up;
    QList<dtkComposerStackCommandReparentNode *> down;

public:
    QList<dtkComposerStackCommandDestroyEdge *> des;
    QList<dtkComposerStackCommandCreatePort *> cps;
    QList<dtkComposerStackCommandCreateEdge *> ces;
    QList<dtkComposerStackCommandDestroyPort *> dps;

public:
    bool dirty;
    bool back;
};

dtkComposerSceneNodeComposite *dtkComposerStackCommandReparentNodePrivate::ancestor(dtkComposerSceneNodeComposite *from, dtkComposerSceneNodeComposite *to)
{
    dtkComposerSceneNodeComposite *parent = NULL;

    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(to->parent()))
        parent = dynamic_cast<dtkComposerSceneNodeComposite *>(control->parent());
    else
        parent = dynamic_cast<dtkComposerSceneNodeComposite *>(to->parent());

    if(from == parent)
        return to;
    else
        return this->ancestor(from, dynamic_cast<dtkComposerSceneNodeComposite *>(parent));
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkComposerStackCommandReparentNode::dtkComposerStackCommandReparentNode(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandReparentNodePrivate)
{
    e->origin = NULL;
    e->target = NULL;

    e->direction = dtkComposerStackCommandReparentNodePrivate::None;

    e->dirty = true;
    e->back = false;

    this->setText("Reparent node");
}

dtkComposerStackCommandReparentNode::~dtkComposerStackCommandReparentNode(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandReparentNode::setOriginNode(dtkComposerSceneNode *node)
{
    e->origin = node;
    e->source = dynamic_cast<dtkComposerSceneNodeComposite *>(node->parent());
}

void dtkComposerStackCommandReparentNode::setTargetNode(dtkComposerSceneNode *node)
{
    e->target = dynamic_cast<dtkComposerSceneNodeComposite *>(node);
}

void dtkComposerStackCommandReparentNode::setOriginPosition(QPointF position)
{
    e->origin_pos = position;
}

void dtkComposerStackCommandReparentNode::setTargetPosition(QPointF position)
{
    e->target_pos = position;
}

void dtkComposerStackCommandReparentNode::redo(void)
{
    if(!d->graph)
        return;

    if(!e->origin)
        return;

    if(!e->source)
        return;

    if(!e->target)
        return;

    // qDebug() << "source:" << e->source->title();
    // qDebug() << "target:" << e->target->title();
    // qDebug() << "origin:" << e->origin->title();

    dtkComposerSceneNodeComposite *source_parent = NULL;
    dtkComposerSceneNodeComposite *target_parent = NULL;

    if (e->source->embedded())
        source_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->source->parent()->parent());
    else
        source_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->source->parent());

    if (e->target->embedded())
        target_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->target->parent()->parent());
    else
        target_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->target->parent());

    // Choose the direction - Are we going down ?

    if (e->direction == dtkComposerStackCommandReparentNodePrivate::None && e->source == target_parent) {

        e->direction = dtkComposerStackCommandReparentNodePrivate::Down;

        // qDebug() << "Going down";

        // Choose the direction - Are we going up ?

    } else if(e->direction == dtkComposerStackCommandReparentNodePrivate::None && source_parent == e->target) {

        e->direction = dtkComposerStackCommandReparentNodePrivate::Up;

        // qDebug() << "Going up";

        // Choose the direction - How to decompose ?

    } else if(e->direction == dtkComposerStackCommandReparentNodePrivate::None) {

        e->direction = dtkComposerStackCommandReparentNodePrivate::Decomposition;

        // qDebug() << "Decomposing";

        dtkComposerSceneNode *origin = e->origin;
        dtkComposerSceneNodeComposite *root = d->scene->root();
        dtkComposerSceneNodeComposite *source = e->source;
        dtkComposerSceneNodeComposite *target = e->target;

        // Move origin up to root

        while(source != root) {

            if (source->embedded())
                source = dynamic_cast<dtkComposerSceneNodeComposite *>(source->parent()->parent());
            else
                source = dynamic_cast<dtkComposerSceneNodeComposite *>(source->parent());

            dtkComposerStackCommandReparentNode *command = new dtkComposerStackCommandReparentNode;
            command->e->direction = dtkComposerStackCommandReparentNodePrivate::Up;
            command->setScene(d->scene);
            command->setGraph(d->graph);
            command->setOriginNode(origin);
            command->setTargetNode(source);
            command->setOriginPosition(e->origin_pos );
            command->setTargetPosition(origin->sceneBoundingRect().topLeft());
            command->redo();

            e->up << command;

            // qDebug() << "1 UP more";
        }

        // Move origin down to target

        while(source != target) {

            source = e->ancestor(source, target);

            dtkComposerStackCommandReparentNode *command = new dtkComposerStackCommandReparentNode;
            command->e->direction = dtkComposerStackCommandReparentNodePrivate::Down;
            command->setScene(d->scene);
            command->setGraph(d->graph);
            command->setOriginNode(origin);
            command->setTargetNode(source);
            command->setOriginPosition(origin->sceneBoundingRect().topLeft());
            command->setTargetPosition(origin->sceneBoundingRect().topLeft());
            command->redo();

            e->down << command;

            // qDebug() << "1 DOWN more";
        }

        // Done if we are composite

        return;
    }

    // Handle redo

    if(e->direction == dtkComposerStackCommandReparentNodePrivate::Decomposition) {

        foreach(dtkComposerStackCommandReparentNode *command, e->up)
            command->redo();

        foreach(dtkComposerStackCommandReparentNode *command, e->down)
            command->redo();

    }

    // Stop if command is composite

    if(e->up.count() || e->down.count())
        return;

    if(e->dirty) { // /////////////////////////////////////////////////////////////////

        // Deal with edges

        dtkComposerScenePort *proxy = NULL;
        dtkComposerSceneNode *origin = e->origin;
        dtkComposerSceneNodeComposite *source = e->source;
        dtkComposerSceneNodeComposite *target = e->target;


        dtkComposerSceneEdgeList outputEdges = origin->outputEdges();
        dtkComposerSceneEdgeList inputEdges  = origin->inputEdges();

        if (dtkComposerSceneNodeControl *control= dynamic_cast<dtkComposerSceneNodeControl *>(origin)) {
            foreach(dtkComposerSceneNodeComposite  *n, control->blocks()) {
                outputEdges << n->outputEdges();
                inputEdges  << n->inputEdges();
            }
            inputEdges << control->header()->inputEdges();
            outputEdges << control->footer()->inputEdges();
        } else {
            outputEdges = origin->outputEdges();
            inputEdges  = origin->inputEdges();
        }

        dtkComposerSceneEdgeList targetEdges = target->edges();
        dtkComposerSceneEdgeList sourceEdges = source->edges();

        dtkComposerSceneNode *s_parent = NULL;
        dtkComposerSceneNode *t_parent = NULL;

        // Deal with input edges

        foreach(dtkComposerSceneEdge *edge, inputEdges) {

            if (edge->source()->node()->embedded())
                s_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(edge->source()->node()->parent()->parent());
            else
                s_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(edge->source()->node()->parent());

            if(edge->source()->node() == target) {

                proxy = edge->source();

                { // Destroy edge

                    dtkComposerStackCommandDestroyEdge *command = new dtkComposerStackCommandDestroyEdge;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setEdge(edge);
                    command->redo();

                    e->des << command;

                }

                foreach(dtkComposerSceneEdge *ed, targetEdges) {

                    if(ed->destination() == proxy) {

                        { // Destroy edge

                            dtkComposerStackCommandDestroyEdge *command = new dtkComposerStackCommandDestroyEdge;
                            command->setFactory(d->factory);
                            command->setScene(d->scene);
                            command->setGraph(d->graph);
                            command->setEdge(ed);
                            command->redo();

                            e->des << command;

                        }
                    }
                }


                // qDebug() << Q_FUNC_INFO << "input" << target->inputDegree(proxy) + target->outputDegree(proxy);

                if(target->inputDegree(proxy) + target->outputDegree(proxy) == 0) {

                    dtkComposerStackCommandDestroyPort *command = new dtkComposerStackCommandDestroyPort;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setNode(target);
                    command->setPort(proxy);
                    command->redo();

                    e->dps << command;
                }
            } else if(edge->source()->node() == source) {

                proxy = edge->source();

                { // Destroy edge

                    dtkComposerStackCommandDestroyEdge *command = new dtkComposerStackCommandDestroyEdge;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setEdge(edge);
                    command->redo();

                    e->des << command;

                }

                foreach(dtkComposerSceneEdge *ed, sourceEdges) {

                    if(ed->destination() == proxy) {

                        { // Destroy edge

                            dtkComposerStackCommandDestroyEdge *command = new dtkComposerStackCommandDestroyEdge;
                            command->setFactory(d->factory);
                            command->setScene(d->scene);
                            command->setGraph(d->graph);
                            command->setEdge(ed);
                            command->redo();

                            e->des << command;

                        }
                    }
                }


                // qDebug() << Q_FUNC_INFO << "input" << target->inputDegree(proxy) + target->outputDegree(proxy);

                if(source->inputDegree(proxy) + source->outputDegree(proxy) == 0) {

                    dtkComposerStackCommandDestroyPort *command = new dtkComposerStackCommandDestroyPort;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setNode(source);
                    command->setPort(proxy);
                    command->redo();

                    e->dps << command;
                }

            } else if(s_parent == source) {

                { // Destroy edge

                    dtkComposerStackCommandDestroyEdge *command = new dtkComposerStackCommandDestroyEdge;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setEdge(edge);
                    command->redo();

                    e->des << command;

                }

            } else {

                qDebug() << Q_FUNC_INFO << "Unhandled case (input)";
            }
        }

        // Deal with output edges

        foreach(dtkComposerSceneEdge *edge, outputEdges) {

            if (edge->destination()->node()->embedded())
                t_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(edge->destination()->node()->parent()->parent());
            else
                t_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(edge->destination()->node()->parent());

            if(edge->destination()->node() == target) {

                proxy = edge->destination();

                { // Destroy edge

                    dtkComposerStackCommandDestroyEdge *command = new dtkComposerStackCommandDestroyEdge;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setEdge(edge);
                    command->redo();

                    e->des << command;

                }

                foreach(dtkComposerSceneEdge *ed, targetEdges) {

                    if(ed->source() == proxy) {

                        { // Destroy edge

                            dtkComposerStackCommandDestroyEdge *command = new dtkComposerStackCommandDestroyEdge;
                            command->setFactory(d->factory);
                            command->setScene(d->scene);
                            command->setGraph(d->graph);
                            command->setEdge(ed);
                            command->redo();

                            e->des << command;

                        }
                    }
                }

                // qDebug() << Q_FUNC_INFO << "output" << target->inputDegree(proxy) + target->outputDegree(proxy);

                if(target->inputDegree(proxy) + target->outputDegree(proxy) == 0) {

                    dtkComposerStackCommandDestroyPort *command = new dtkComposerStackCommandDestroyPort;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setNode(target);
                    command->setPort(proxy);
                    command->redo();

                    e->dps << command;
                }

            } else if(edge->destination()->node() == source) {

                proxy = edge->destination();

                { // Destroy edge

                    dtkComposerStackCommandDestroyEdge *command = new dtkComposerStackCommandDestroyEdge;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setEdge(edge);
                    command->redo();

                    e->des << command;

                }

                foreach(dtkComposerSceneEdge *ed, targetEdges) {

                    if(ed->source() == proxy) {

                        { // Destroy edge

                            dtkComposerStackCommandDestroyEdge *command = new dtkComposerStackCommandDestroyEdge;
                            command->setFactory(d->factory);
                            command->setScene(d->scene);
                            command->setGraph(d->graph);
                            command->setEdge(ed);
                            command->redo();

                            e->des << command;

                        }
                    }
                }

                // qDebug() << Q_FUNC_INFO << "output" << target->inputDegree(proxy) + target->outputDegree(proxy);

                if(source->inputDegree(proxy) + source->outputDegree(proxy) == 0) {

                    dtkComposerStackCommandDestroyPort *command = new dtkComposerStackCommandDestroyPort;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setNode(source);
                    command->setPort(proxy);
                    command->redo();

                    e->dps << command;
                }

            } else if(t_parent == source) {

                { // Destroy edge

                    dtkComposerStackCommandDestroyEdge *command = new dtkComposerStackCommandDestroyEdge;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setEdge(edge);
                    command->redo();

                    e->des << command;

                }

            } else {

                qDebug() << Q_FUNC_INFO << "Unhandled case (output)";
            }
        }

        d->graph->reparentNode(e->origin, e->target);

        // Notify source about reparenting

        e->source->removeNode(e->origin);

        // Remove node from the scene if source is not flattened 

        if (e->source->flattened() || e->source == d->scene->current()) {
            d->scene->removeItem(e->origin);
        }

        // Notify target about reparenting

        e->target->addNode(e->origin);

        // Notify origin about reparenting

        e->origin->setParent(e->target);

        // Add node in the scene at its right z-value.

        if (e->target == d->scene->current()) {
            d->scene->addItem(e->origin);

        } else if (e->target->flattened()) {
            d->scene->addItem(e->origin);
            if (e->target->embedded() && !e->target->entered())
                e->target->parent()->stackBefore(e->origin);
            else
                e->target->stackBefore(e->origin);

        }

        // Set node position 

        e->origin->setPos(e->target_pos);

        // Deal with input edges

        foreach(dtkComposerSceneEdge *edge, inputEdges) {

            if (edge->source()->node()->embedded())
                s_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(edge->source()->node()->parent()->parent());
            else
                s_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(edge->source()->node()->parent());

            if(edge->source()->node() == target || (edge->source()->node() == source)) {

                proxy = edge->source();


                foreach(dtkComposerSceneEdge *ed, targetEdges) {

                    if(ed->destination() == proxy) {

                        { // Create edge

                            dtkComposerStackCommandCreateEdge *command = new dtkComposerStackCommandCreateEdge;
                            command->setFactory(d->factory);
                            command->setScene(d->scene);
                            command->setGraph(d->graph);
                            command->setSource(ed->source());
                            command->setDestination(edge->destination());
                            command->setParent(target);
                            command->redo();

                            e->ces << command;

                        }
                    }
                }

            } else if(s_parent == source) {

                { // Create port

                    dtkComposerStackCommandCreatePort *command = new dtkComposerStackCommandCreatePort;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setKind(dtkComposerTransmitter::Proxy);
                    if(e->direction == dtkComposerStackCommandReparentNodePrivate::Down) {
#if defined(DTK_BUILD_DISTRIBUTED)
                        if (dynamic_cast<dtkComposerNodeRemote *>(target->wrapee()))
                            command->setKind(dtkComposerTransmitter::ProxyLoop);
#endif
                        command->setNode(target);
                    }
                    if(e->direction == dtkComposerStackCommandReparentNodePrivate::Up) {
#if defined(DTK_BUILD_DISTRIBUTED)
                        if (dynamic_cast<dtkComposerNodeRemote *>(source->wrapee()))
                            command->setKind(dtkComposerTransmitter::ProxyLoop);
#endif
                        command->setNode(source);
                    }
                    if(e->direction == dtkComposerStackCommandReparentNodePrivate::Down)
                        command->setType(dtkComposerScenePort::Input);
                    if(e->direction == dtkComposerStackCommandReparentNodePrivate::Up)
                        command->setType(dtkComposerScenePort::Output);
                    command->redo();

                    proxy = command->port();

                    e->cps << command;

                }

                { // Create lhs edge

                    dtkComposerStackCommandCreateEdge *command = new dtkComposerStackCommandCreateEdge;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setSource(edge->source());
                    command->setDestination(proxy);
                    command->setParent(source);
                    command->redo();

                    e->ces << command;

                }

                { // Create rhs edge

                    dtkComposerStackCommandCreateEdge *command = new dtkComposerStackCommandCreateEdge;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setSource(proxy);
                    command->setDestination(edge->destination());
                    command->setParent(target);
                    command->redo();

                    e->ces << command;

                }

            } else {

                qDebug() << Q_FUNC_INFO << "Unhandled case (input create)";
            }
        }

        // Deal with output edges

        foreach(dtkComposerSceneEdge *edge, outputEdges) {

            if (edge->destination()->node()->embedded())
                t_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(edge->destination()->node()->parent()->parent());
            else
                t_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(edge->destination()->node()->parent());


            if(edge->destination()->node() == target || edge->destination()->node() == source) {

                proxy = edge->destination();

                foreach(dtkComposerSceneEdge *ed, targetEdges) {

                    if(ed->source() == proxy) {

                        { // Create edge

                            dtkComposerStackCommandCreateEdge *command = new dtkComposerStackCommandCreateEdge;
                            command->setFactory(d->factory);
                            command->setScene(d->scene);
                            command->setGraph(d->graph);
                            command->setSource(edge->source());
                            command->setDestination(ed->destination());
                            command->setParent(target);
                            command->redo();

                            e->ces << command;

                        }
                    }
                }

            } else if(t_parent == source) {

                { // Create port

                    dtkComposerStackCommandCreatePort *command = new dtkComposerStackCommandCreatePort;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setKind(dtkComposerTransmitter::Proxy);
                    if(e->direction == dtkComposerStackCommandReparentNodePrivate::Down) {
#if defined(DTK_BUILD_DISTRIBUTED)
                        if (dynamic_cast<dtkComposerNodeRemote *>(target->wrapee()))
                            command->setKind(dtkComposerTransmitter::ProxyLoop);
#endif
                        command->setNode(target);
                    }
                    if(e->direction == dtkComposerStackCommandReparentNodePrivate::Up) {
#if defined(DTK_BUILD_DISTRIBUTED)
                        if (dynamic_cast<dtkComposerNodeRemote *>(source->wrapee()))
                            command->setKind(dtkComposerTransmitter::ProxyLoop);
#endif
                        command->setNode(source);
                    }
                    if(e->direction == dtkComposerStackCommandReparentNodePrivate::Down)
                        command->setType(dtkComposerScenePort::Output);
                    if(e->direction == dtkComposerStackCommandReparentNodePrivate::Up)
                        command->setType(dtkComposerScenePort::Input);
                    command->redo();

                    proxy = command->port();

                    e->cps << command;

                }

                { // Create lhs edge

                    dtkComposerStackCommandCreateEdge *command = new dtkComposerStackCommandCreateEdge;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setSource(edge->source());
                    command->setDestination(proxy);
                    command->setParent(target);
                    command->redo();

                    e->ces << command;

                }

                { // Create rhs edge

                    dtkComposerStackCommandCreateEdge *command = new dtkComposerStackCommandCreateEdge;
                    command->setFactory(d->factory);
                    command->setScene(d->scene);
                    command->setGraph(d->graph);
                    command->setSource(proxy);
                    command->setDestination(edge->destination());
                    command->setParent(source);
                    command->redo();

                    e->ces << command;

                }

            } else {

                qDebug() << Q_FUNC_INFO << "Unhandled case (output create)";
            }
        }


        e->dirty = false;

    } else if(!e->back) { // redo

        foreach(dtkComposerStackCommand *command, e->des)
            command->redo();

        foreach(dtkComposerStackCommand *command, e->dps)
            command->redo();

        d->graph->reparentNode(e->origin, e->target);

        // Notify source about reparenting

        e->source->removeNode(e->origin);

        // Remove node from the scene if source is not flattened 

        if (e->source->flattened() || e->source == d->scene->current()) {
            d->scene->removeItem(e->origin);
        }

        // Notify target about reparenting

        e->target->addNode(e->origin);

        // Notify origin about reparenting

        e->origin->setParent(e->target);

        // Add node in the scene at its right z-value.

        if (e->target == d->scene->current()) {
            d->scene->addItem(e->origin);

        } else if (e->target->flattened()) {
            d->scene->addItem(e->origin);
            if (e->target->embedded() && !e->target->entered())
                e->target->parent()->stackBefore(e->origin);
            else
                e->target->stackBefore(e->origin);

        }

        // Set node position 

        e->origin->setPos(e->target_pos);

        // 

        foreach(dtkComposerStackCommand *command, e->cps)
            command->redo();

        foreach(dtkComposerStackCommand *command, e->ces)
            command->redo();


    } else { //undo

        d->graph->reparentNode(e->origin, e->target);

        // Notify source about reparenting

        e->source->removeNode(e->origin);

        if (e->source->flattened()) {
            e->source->layout();
            d->scene->removeItem(e->origin);
        } else if (e->source == d->scene->current()) {
            d->scene->removeItem(e->origin);
        }

        // Notify origin about reparenting

        e->target->addNode(e->origin);
        e->origin->setParent(e->target);
        e->origin->setPos(e->origin_pos);


        if (e->target->visible())
            d->scene->addItem(e->origin);

    }


    e->source->layout();
    e->target->layout();

    // // Notify the scene

    // if(e->source->flattened() || e->source == d->scene->current()) {

    //     // qDebug() << "Removing origin from scene";

    //     d->scene->removeItem(e->origin);
    // }

    // if(e->target->flattened() || e->target == d->scene->current()) {

    //     // qDebug() << "Adding origin to scene";

    //     d->scene->addItem(e->origin);
    // }
    d->graph->layout();
    d->scene->modify(true);
    d->scene->update();
}

void dtkComposerStackCommandReparentNode::undo(void)
{
    { // Undo down commands 

    QListIterator<dtkComposerStackCommandReparentNode *> command(e->down); command.toBack();

    while (command.hasPrevious())
        command.previous()->undo();

    }

    { // Undo up commands 

    QListIterator<dtkComposerStackCommandReparentNode *> command(e->up); command.toBack();

    while (command.hasPrevious())
        command.previous()->undo();

    }

    // Stop if command is composite

    if(e->up.count() || e->down.count())
        return;


    { // Undo create edges commands 

    QListIterator<dtkComposerStackCommandCreateEdge *> command(e->ces); command.toBack();

    while (command.hasPrevious())
        command.previous()->undo();

    }

    { // Undo create ports commands 

    QListIterator<dtkComposerStackCommandCreatePort *> command(e->cps); command.toBack();

    while (command.hasPrevious())
        command.previous()->undo();

    }

    // Switch target and source ...

    dtkComposerSceneNodeComposite *temp;

    temp = e->source;
    e->source = e->target;
    e->target = temp;

    // ... and go ...

    e->back = true;

    this->redo();

    e->back = false;

    // ... and switch back ...

    temp = e->source;
    e->source = e->target;
    e->target = temp;

    { // Undo destroy ports commands 

    QListIterator<dtkComposerStackCommandDestroyPort *> command(e->dps); command.toBack();

    while (command.hasPrevious())
        command.previous()->undo();

    }

    { // Undo destroy edges commands 

    QListIterator<dtkComposerStackCommandDestroyEdge *> command(e->des); command.toBack();

    while (command.hasPrevious())
        command.previous()->undo();

    }

}


// /////////////////////////////////////////////////////////////////
// Create Block Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateBlockPrivate
{
public:
    QPointF position;

public:
    dtkComposerSceneNodeControl *node;
    dtkComposerSceneNodeComposite *block;

public:
    int id;
};

dtkComposerStackCommandCreateBlock::dtkComposerStackCommandCreateBlock(dtkComposerStackCommand *parent) : dtkComposerStackCommand(), e(new dtkComposerStackCommandCreateBlockPrivate)
{
    e->node  = NULL;
    e->block = NULL;

    this->setText("Create block");
}

dtkComposerStackCommandCreateBlock::~dtkComposerStackCommandCreateBlock(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandCreateBlock::setNode(dtkComposerSceneNodeControl *node)
{
    e->node = node;
}

void dtkComposerStackCommandCreateBlock::redo(void)
{
    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->node)
        return;

    e->block = new dtkComposerSceneNodeComposite;
    dtkComposerNodeControlCase *control = dynamic_cast<dtkComposerNodeControlCase *>(e->node->wrapee());

    control->addBlock();
    e->id = control->blockCount()-1;

    e->block->wrap(control->block(e->id));
    e->node->addBlock(e->block);

    d->graph->addBlock(e->node);

    d->scene->modify(true);
}

void dtkComposerStackCommandCreateBlock::undo(void)
{
    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->node)
        return;

    dtkComposerNodeControlCase *control = dynamic_cast<dtkComposerNodeControlCase *>(e->node->wrapee());

    d->graph->removeBlock(e->block);
    control->removeBlock(e->id);
    e->node->removeBlock(e->block);

    d->scene->removeItem(e->block);

    d->scene->modify(true);
}

// /////////////////////////////////////////////////////////////////
// Destroy Block Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyBlockPrivate
{
public:
    QPointF position;

public:
    dtkComposerSceneNodeComposite *block;
    dtkComposerSceneNodeControl    *node;

public:
    int id;

};

dtkComposerStackCommandDestroyBlock::dtkComposerStackCommandDestroyBlock(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandDestroyBlockPrivate)
{
    e->block = NULL;
    e->node  = NULL;
    e->id   = -1;
    this->setText("Destroy block");
}

dtkComposerStackCommandDestroyBlock::~dtkComposerStackCommandDestroyBlock(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandDestroyBlock::setNode(dtkComposerSceneNodeComposite *block)
{
    e->block = block;
    e->node = dynamic_cast<dtkComposerSceneNodeControl *>(e->block->parent());
}

void dtkComposerStackCommandDestroyBlock::setId(int id)
{
    e->id = id;
}

void dtkComposerStackCommandDestroyBlock::redo(void)
{
    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->block)
        return;

    if(e->id < 1)
        return;

    dtkComposerNodeControlCase *control = dynamic_cast<dtkComposerNodeControlCase *>(e->block->parent()->wrapee());

    d->graph->removeBlock(e->block);
    e->node->removeBlock(e->block);
    control->removeBlock(e->id);

    d->scene->removeItem(e->block);

    d->scene->modify(true);
}

void dtkComposerStackCommandDestroyBlock::undo(void)
{
    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->block)
        return;

    if(e->id < 1)
        return;

    dtkComposerNodeControlCase *control = dynamic_cast<dtkComposerNodeControlCase *>(e->block->parent()->wrapee());

    control->addBlock(dynamic_cast<dtkComposerNodeComposite *>(e->block->wrapee()));
    e->node->addBlock(e->block);

    d->graph->addBlock(e->block);


    d->scene->modify(true);
}




/////////////////////////////////////////////////////////////////
// Copy Nodes Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCopyNodesPrivate
{
public:
    dtkComposerSceneNodeList nodes;
    dtkComposerSceneNodeList old_nodes;

public:
    QString data;
};

dtkComposerStackCommandCopyNodes::dtkComposerStackCommandCopyNodes(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandCopyNodesPrivate)
{
    this->setText("Copy nodes");
}

dtkComposerStackCommandCopyNodes::~dtkComposerStackCommandCopyNodes(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandCopyNodes::setNodes(dtkComposerSceneNodeList nodes)
{
    e->nodes = nodes;
    e->data.clear();
}

void dtkComposerStackCommandCopyNodes::redo(void)
{
    if(!d->scene)
        return;

    if(!d->factory)
        return;

    if(!d->graph)
        return;

    if(e->nodes.isEmpty())
        return;

    if (e->data.isEmpty()) {
        e->old_nodes = d->scene->root()->nodes();

        if ((dynamic_cast<dtkComposerSceneNodeComposite *>(e->nodes.at(0))) && e->nodes.count() == 1)  {

            dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(e->nodes.at(0));
            dtkComposerWriter writer;
            writer.setScene(d->scene);
            QString old = composite->title();
            composite->setTitle(old +" copy");
            e->data = writer.toXML(composite).toString();
            composite->setTitle(old);

        } else if (areBrothers(e->nodes)) {

            // first create a temporary composite
            dtkComposerStackCommandCreateGroup *group = new dtkComposerStackCommandCreateGroup;
            group->setScene(d->scene);
            group->setGraph(d->graph);
            group->setNodes(e->nodes);
            group->redo();

            dtkComposerSceneNodeList dummylist ;

            // get the composite pointer by calling parent on one of the nodes
            dtkComposerSceneNode *dummy_composite = e->nodes.at(0)->parent();
            dummy_composite->setTitle("dummy composite");
            dummylist << dummy_composite;

            // then copy this composite
            dtkComposerStackCommandCopyNodes *copy = new dtkComposerStackCommandCopyNodes;
            copy->setScene(d->scene);
            copy->setGraph(d->graph);
            copy->setFactory(d->factory);
            copy->setNodes(dummylist);
            copy->redo();
            delete copy;

            // then undo the temporary composite
            group->undo();
            delete group;

            // look for the duplicated composite
            foreach(dtkComposerSceneNode *node, d->scene->current()->nodes()) {
                if (node->title() == "dummy composite copy")
                    dummy_composite = node;
            }

            // then ungroup the duplicate composite
            dtkComposerSceneNodeList copies = (dynamic_cast<dtkComposerSceneNodeComposite *>(dummy_composite))->nodes();
            dtkComposerStackCommandDestroyGroup *ungroup = new dtkComposerStackCommandDestroyGroup;
            ungroup->setScene(d->scene);
            ungroup->setGraph(d->graph);
            ungroup->setNode( dynamic_cast<dtkComposerSceneNodeComposite *>(dummy_composite));
            ungroup->redo();
            delete ungroup;
            foreach (dtkComposerSceneNode *n,copies) {
                n->setPos(n->pos()+QPointF(100,100));
                n->layout();
            }
        }
    }

    if (!e->data.isEmpty()) {
        dtkComposerReader reader;
        reader.setFactory(d->factory);
        reader.setScene(d->scene);
        reader.setGraph(d->graph);
        reader.readString(e->data, true, true);
    }

    d->scene->modify(true);
}

void dtkComposerStackCommandCopyNodes::undo(void)
{
    if(!d->scene)
        return;

    if(!d->factory)
        return;

    if(!d->graph)
        return;

    foreach(dtkComposerSceneNode *node, d->scene->root()->nodes()) {
        if (!e->old_nodes.contains(node)) {

            dtkComposerStackCommandDestroyNode *command = new dtkComposerStackCommandDestroyNode;
            command->setGraph(d->graph);
            command->setScene(d->scene);
            command->setFactory(d->factory);
            command->setNode(node);
            command->redo();

            delete command;
        }
    }

    d->scene->modify(true);
}


/* dtkComposerStackCommand.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 18:17:43 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. févr. 24 15:56:02 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 2146
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerFactory.h"
#include "dtkComposerGraph.h"
#include "dtkComposerGraphNode.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeLeaf.h"
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

// /////////////////////////////////////////////////////////////////
// Base Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandPrivate
{
public:
    dtkComposerFactory *factory;
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

void dtkComposerStackCommand::setFactory(dtkComposerFactory *factory)
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
    if (e->parent->root() || e->parent->flattened() || e->parent->entered())
        d->scene->addItem(e->node);
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

    e->parent->removeNode(e->node);
    e->parent->layout();

    d->graph->removeNode(e->node);
    d->graph->layout();

// -- ??
    if (e->parent->root() || e->parent->flattened() || e->parent->entered())
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
    dtkComposerSceneNodeComposite *parent;

public:
    QList<dtkComposerSceneEdge *>  input_edges;
    QList<dtkComposerSceneEdge *> output_edges;
};

dtkComposerStackCommandDestroyNode::dtkComposerStackCommandDestroyNode(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandDestroyNodePrivate)
{
    e->node = NULL;
    e->parent = NULL;
}

dtkComposerStackCommandDestroyNode::~dtkComposerStackCommandDestroyNode(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandDestroyNode::setNode(dtkComposerSceneNode *node)
{
    e->node = node;

    foreach(dtkComposerSceneEdge *edge, e->node->inputEdges())
        e->input_edges << edge;

    foreach(dtkComposerSceneEdge *edge, e->node->outputEdges())
        e->output_edges << edge;

    e->parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->node->parent());

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

    foreach(dtkComposerSceneEdge *edge, e->input_edges) {
        if (d->scene->items().contains(edge))
            d->scene->removeItem(edge);
        e->parent->removeEdge(edge);
    }

    foreach(dtkComposerSceneEdge *edge, e->output_edges) {
        if (d->scene->items().contains(edge))
            d->scene->removeItem(edge);
        e->parent->removeEdge(edge);
    }

    e->parent->removeNode(e->node);
    e->parent->layout();

    d->graph->removeNode(e->node);
    d->graph->layout();

    if (e->parent->root() || e->parent->flattened() || e->parent->entered())
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
    e->parent->layout();

    d->graph->addNode(e->node);
    d->graph->layout();

    foreach(dtkComposerSceneEdge *edge, e->input_edges) {
        if(!d->scene->items().contains(edge))
            d->scene->addItem(edge);
        e->parent->addEdge(edge);
    }

    foreach(dtkComposerSceneEdge *edge, e->output_edges) {
        if(!d->scene->items().contains(edge))
            d->scene->addItem(edge);
        e->parent->addEdge(edge);
    }

    if (e->parent->root() || e->parent->flattened() || e->parent->entered())
        d->scene->addItem(e->node);

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

    this->setParent();
}

void dtkComposerStackCommandCreateEdge::setDestination(dtkComposerScenePort *destination)
{
    e->destination = destination;

    this->setParent();
}

void dtkComposerStackCommandCreateEdge::redo(void)
{
    if(!d->graph)
        return;

    if(!d->scene)
        return;

    if(!e->parent)
        return;

    if(!e->source)
        return;

    if(!e->destination)
        return;

    if(!e->edge) {
        e->edge = new dtkComposerSceneEdge;
        e->edge->setSource(e->source);
        e->edge->setDestination(e->destination);
        e->edge->setParent(e->parent);
    }

    e->edge->link();

    e->parent->addEdge(e->edge);

    if(e->parent->entered() || e->parent->flattened() || e->parent->root())
        d->scene->addItem(e->edge);
    
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

    // Setting up control flow

    d->graph->removeEdge(e->edge);

    // Setting up scene

    e->edge->unlink();

    e->parent->removeEdge(e->edge);

    if(e->parent->entered() || e->parent->flattened() || e->parent->root())
        d->scene->removeItem(e->edge);

    d->scene->modify(true);
}

void dtkComposerStackCommandCreateEdge::setParent(void)
{
    if(!e->source)
        return;

    if(!e->destination)
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
    else
        qDebug() << __func__ << "Unhandled case";
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
    if(!e->edge)
        return;

    if(!e->parent)
        return;

    // Setting up data flow

    dtkComposerTransmitterDisconnection(d->scene->root(), e->parent, e->edge);

    // Setting up control flow

    d->graph->removeEdge(e->edge);

    // Setting up scene

    e->edge->unlink();

    e->parent->removeEdge(e->edge);

    if(e->parent->entered() || e->parent->flattened() || e->parent->root())
        d->scene->removeItem(e->edge);

    d->scene->modify(true);
}

void dtkComposerStackCommandDestroyEdge::undo(void)
{
    if(!e->edge)
        return;

    if(!e->parent)
        return;

    e->edge->link();

    e->parent->addEdge(e->edge);

    d->scene->addItem(e->edge);
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

    if (e->parent->root() || e->parent->flattened() || e->parent->entered())
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

    if (e->parent->root() || e->parent->flattened() || e->parent->entered())
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

    if (e->parent->root() || e->parent->flattened() || e->parent->entered())
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

    if (e->parent->root() || e->parent->flattened() || e->parent->entered())
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
    QList<dtkComposerSceneNode *> nodes;

public:
    QList<dtkComposerSceneNote *> notes;

public:
    QList<dtkComposerSceneEdge *> intern_edges;
    QList<dtkComposerSceneEdge *>  input_edges;
    QList<dtkComposerSceneEdge *> output_edges;

public:
    QList<dtkComposerStackCommandDestroyEdge *> destroy_input_edges;
    QList<dtkComposerStackCommandCreatePort *>  create_input_ports;
    QList<dtkComposerStackCommandCreateEdge *>  create_input_lhs_edges;
    QList<dtkComposerStackCommandCreateEdge *>  create_input_rhs_edges;

public:
    QList<dtkComposerStackCommandDestroyEdge *> destroy_output_edges;
    QList<dtkComposerStackCommandCreatePort *>  create_output_ports;
    QList<dtkComposerStackCommandCreateEdge *>  create_output_lhs_edges;
    QList<dtkComposerStackCommandCreateEdge *>  create_output_rhs_edges;
};

dtkComposerStackCommandCreateGroup::dtkComposerStackCommandCreateGroup(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandCreateGroupPrivate)
{
    e->parent = NULL;
    e->node = NULL;

    this->setText("Create group");
}

dtkComposerStackCommandCreateGroup::~dtkComposerStackCommandCreateGroup(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandCreateGroup::setParent(dtkComposerSceneNodeComposite *parent)
{
    e->parent = parent;
}

void dtkComposerStackCommandCreateGroup::setNodes(dtkComposerSceneNodeList nodes)
{
    if(!e->parent)
        return;

    foreach(dtkComposerSceneNode *node, nodes)
        if(node->parent() == e->parent)
            e->nodes << node;

    foreach(dtkComposerSceneEdge *edge, e->parent->edges()) {

        if (e->nodes.contains(edge->source()->node()) && e->nodes.contains(edge->destination()->node())) {

            e->intern_edges << edge;

        } else if (!e->nodes.contains(edge->source()->node()) && e->nodes.contains(edge->destination()->node())) {

            e->input_edges << edge;

            e->destroy_input_edges    << new dtkComposerStackCommandDestroyEdge;
            e->destroy_input_edges.last()->setFactory(d->factory);
            e->destroy_input_edges.last()->setScene(d->scene);
            e->destroy_input_edges.last()->setGraph(d->graph);

            e->create_input_ports     << new dtkComposerStackCommandCreatePort;
            e->create_input_ports.last()->setFactory(d->factory);
            e->create_input_ports.last()->setScene(d->scene);
            e->create_input_ports.last()->setGraph(d->graph);

            e->create_input_lhs_edges << new dtkComposerStackCommandCreateEdge;
            e->create_input_lhs_edges.last()->setFactory(d->factory);
            e->create_input_lhs_edges.last()->setScene(d->scene);
            e->create_input_lhs_edges.last()->setGraph(d->graph);

            e->create_input_rhs_edges << new dtkComposerStackCommandCreateEdge;
            e->create_input_rhs_edges.last()->setFactory(d->factory);
            e->create_input_rhs_edges.last()->setScene(d->scene);
            e->create_input_rhs_edges.last()->setGraph(d->graph);

        } else if (!e->nodes.contains(edge->destination()->node()) && e->nodes.contains(edge->source()->node())) {

            e->output_edges << edge;
        
            e->destroy_output_edges    << new dtkComposerStackCommandDestroyEdge;
            e->destroy_output_edges.last()->setFactory(d->factory);
            e->destroy_output_edges.last()->setScene(d->scene);
            e->destroy_output_edges.last()->setGraph(d->graph);

            e->create_output_ports     << new dtkComposerStackCommandCreatePort;
            e->create_output_ports.last()->setFactory(d->factory);
            e->create_output_ports.last()->setScene(d->scene);
            e->create_output_ports.last()->setGraph(d->graph);

            e->create_output_lhs_edges << new dtkComposerStackCommandCreateEdge;
            e->create_output_lhs_edges.last()->setFactory(d->factory);
            e->create_output_lhs_edges.last()->setScene(d->scene);
            e->create_output_lhs_edges.last()->setGraph(d->graph);

            e->create_output_rhs_edges << new dtkComposerStackCommandCreateEdge;
            e->create_output_rhs_edges.last()->setFactory(d->factory);
            e->create_output_rhs_edges.last()->setScene(d->scene);
            e->create_output_rhs_edges.last()->setGraph(d->graph);

        }
    }
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

    if(e->nodes.isEmpty())
        return;

    if(!e->node) {
        e->node = new dtkComposerSceneNodeComposite;
        e->node->wrap(new dtkComposerNodeComposite);
        e->node->setParent(e->parent);
    }

    QRectF rect;

    foreach(dtkComposerSceneNode *node, e->nodes) {
        rect |= node->sceneBoundingRect();
        e->parent->removeNode(node);
        d->graph->removeNode(node);
        d->scene->removeItem(node);
        e->node->addNode(node);
        node->setParent(e->node);
        d->graph->addNode(node);
    }

    e->parent->addNode(e->node);

    e->node->setPos(rect.center() - e->node->boundingRect().center());

    foreach(dtkComposerSceneEdge *edge, e->intern_edges) {
        e->parent->removeEdge(edge);
        d->scene->removeItem(edge);
        e->node->addEdge(edge);
        edge->setParent(e->node);
    }

    for(int i = 0; i < e->input_edges.count(); i++) {

        e->destroy_input_edges.at(i)->setEdge(e->input_edges.at(i));
        e->destroy_input_edges.at(i)->redo();

        e->create_input_ports.at(i)->setNode(e->node);
        e->create_input_ports.at(i)->setType(dtkComposerScenePort::Input);
        e->create_input_ports.at(i)->redo();

        e->create_input_lhs_edges.at(i)->setSource(e->input_edges.at(i)->source());
        e->create_input_lhs_edges.at(i)->setDestination(e->node->inputPorts().last());
        e->create_input_lhs_edges.at(i)->redo();

        e->create_input_rhs_edges.at(i)->setSource(e->node->inputPorts().last());
        e->create_input_rhs_edges.at(i)->setDestination(e->input_edges.at(i)->destination());
        e->create_input_rhs_edges.at(i)->redo();

    }

    for(int i = 0; i < e->output_edges.count(); i++) {

        e->destroy_output_edges.at(i)->setEdge(e->output_edges.at(i));
        e->destroy_output_edges.at(i)->redo();

        e->create_output_ports.at(i)->setNode(e->node);
        e->create_output_ports.at(i)->setType(dtkComposerScenePort::Output);
        e->create_output_ports.at(i)->redo();

        e->create_output_lhs_edges.at(i)->setSource(e->output_edges.at(i)->source());
        e->create_output_lhs_edges.at(i)->setDestination(e->node->outputPorts().last());
        e->create_output_lhs_edges.at(i)->redo();

        e->create_output_rhs_edges.at(i)->setSource(e->node->outputPorts().last());
        e->create_output_rhs_edges.at(i)->setDestination(e->output_edges.at(i)->destination());
        e->create_output_rhs_edges.at(i)->redo();

    }

    foreach(dtkComposerSceneNote *note, e->notes) {
        e->parent->removeNote(note);
        d->scene->removeItem(note);
        e->node->addNote(note);
        note->setParent(e->node);
    }

    d->scene->addItem(e->node);

    d->graph->addNode(e->node);

    d->scene->update();
    d->scene->modify(true);
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

    foreach(dtkComposerSceneEdge *edge, e->intern_edges) {
        e->node->removeEdge(edge);
        e->parent->addEdge(edge);
        d->scene->addItem(edge);
        edge->setParent(e->parent);
    }

    for(int i = 0; i < e->input_edges.count(); i++) {
        e->create_input_rhs_edges.at(i)->undo();
        e->create_input_lhs_edges.at(i)->undo();
        e->destroy_input_edges.at(i)->undo();
    }

    for(int i = 0; i < e->input_edges.count(); i++)
        e->create_input_ports.at(i)->undo();

    for(int i = 0; i < e->output_edges.count(); i++) {
        e->create_output_rhs_edges.at(i)->undo();
        e->create_output_lhs_edges.at(i)->undo();
        e->destroy_output_edges.at(i)->undo();
    }

    for(int i = 0; i < e->output_edges.count(); i++)
        e->create_output_ports.at(i)->undo();

    foreach(dtkComposerSceneNote *note, e->notes) {
        e->parent->addNote(note);
        d->scene->addItem(note);
        e->node->removeNote(note);
        note->setParent(e->node->parent());
    }

    foreach(dtkComposerSceneNode *node, e->nodes) {
        e->parent->addNode(node);
        d->graph->addNode(node);
        d->scene->addItem(node);
        e->node->removeNode(node);
        node->setParent(e->node->parent());
        d->graph->removeNode(node);
    }

    e->parent->removeNode(e->node);

    d->scene->removeItem(e->node);
    d->graph->removeNode(e->node);

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
    dtkComposerSceneEdgeList edges;
    dtkComposerSceneNodeList nodes;
    dtkComposerSceneNoteList notes;

public:
    QList<dtkComposerSceneEdge *> lflles;
    QList<dtkComposerSceneEdge *> llhses;
    QList<dtkComposerSceneEdge *> lrhses;

public:
    QList<dtkComposerSceneEdge *> rflles;
    QList<dtkComposerSceneEdge *> rlhses;
    QList<dtkComposerSceneEdge *> rrhses;
};

dtkComposerStackCommandDestroyGroup::dtkComposerStackCommandDestroyGroup(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandDestroyGroupPrivate)
{
    e->parent = NULL;
    e->node = NULL;

    this->setText("Destroy group");
}

dtkComposerStackCommandDestroyGroup::~dtkComposerStackCommandDestroyGroup(void)
{
    delete e;
    
    e = NULL;
}

void dtkComposerStackCommandDestroyGroup::setParent(dtkComposerSceneNodeComposite *parent)
{
    e->parent = parent;
}

void dtkComposerStackCommandDestroyGroup::setNode(dtkComposerSceneNodeComposite *node)
{
    e->node  = node;
    e->nodes = node->nodes();
    e->notes = node->notes();
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

    e->edges = e->node->edges();

    foreach(dtkComposerSceneNode *node, e->nodes) {
        e->parent->addNode(node);
        d->scene->addItem(node);
        e->node->removeNode(node);
        node->setParent(e->node->parent());
    }

    foreach(dtkComposerSceneEdge *edge, e->edges) {

        if (e->nodes.contains(edge->source()->node()) && e->nodes.contains(edge->destination()->node())) {
            e->parent->addEdge(edge);
            d->scene->addItem(edge);
            e->node->removeEdge(edge);
            edge->setParent(e->node->parent());

// /////////////////////////////////////////////////////////////////
// -- Experimental: Handling external edges
// /////////////////////////////////////////////////////////////////

        } else if(!e->nodes.contains(edge->source()->node()) && e->nodes.contains(edge->destination()->node())) {

            dtkComposerSceneEdge *lhs = NULL;
            dtkComposerSceneEdge *rhs = edge;

            foreach(dtkComposerSceneEdge *ed, e->node->inputEdges())
                if(ed->destination() == edge->source())
                    lhs = ed;

            if(lhs && rhs) {

                dtkComposerSceneEdge *ed = new dtkComposerSceneEdge;
                ed->setSource(lhs->source());
                ed->setDestination(rhs->destination());
                ed->link();
                ed->setParent(e->node->parent());

                e->parent->addEdge(ed);
                d->scene->addItem(ed);

                e->lflles << ed;
            }

            lhs->unlink();
            rhs->unlink();
            
            e->parent->removeEdge(lhs);
            d->scene->removeItem(lhs);
            e->node->removeEdge(rhs);

            e->llhses << lhs;
            e->lrhses << rhs;

        } else if(!e->nodes.contains(edge->destination()->node()) && e->nodes.contains(edge->source()->node())) {

            dtkComposerSceneEdge *lhs = edge;
            dtkComposerSceneEdge *rhs = NULL;

            foreach(dtkComposerSceneEdge *ed, e->node->outputEdges())
                if(ed->source() == edge->destination())
                    rhs = ed;

            if(lhs && rhs) {

                dtkComposerSceneEdge *ed = new dtkComposerSceneEdge;
                ed->setSource(lhs->source());
                ed->setDestination(rhs->destination());
                ed->link();
                ed->setParent(e->node->parent());

                e->parent->addEdge(ed);
                d->scene->addItem(ed);

                e->rflles << ed;
            }

            lhs->unlink();
            rhs->unlink();
            
            e->node->removeEdge(lhs);
            e->parent->removeEdge(rhs);
            d->scene->removeItem(rhs);

            e->rlhses << lhs;
            e->rrhses << rhs;
        }

// /////////////////////////////////////////////////////////////////

    }

    foreach(dtkComposerSceneNote *note, e->notes) {
        e->parent->addNote(note);
        d->scene->addItem(note);
        e->node->removeNote(note);
        note->setParent(e->node->parent());
    }

    e->parent->removeNode(e->node);
    d->scene->removeItem(e->node);
    d->graph->removeNode(e->node);

    d->scene->update();
    d->scene->modify(true);
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

    foreach(dtkComposerSceneNode *node, e->nodes) {
        e->parent->removeNode(node);
        d->scene->removeItem(node);
        e->node->addNode(node);
        node->setParent(e->node);
    }

    foreach(dtkComposerSceneEdge *edge, e->edges) {

        if (e->nodes.contains(edge->source()->node()) && e->nodes.contains(edge->destination()->node())) {
            e->parent->removeEdge(edge);
            d->scene->removeItem(edge);
            e->node->addEdge(edge);
            edge->setParent(e->node);

// /////////////////////////////////////////////////////////////////
// -- Experimental: Handling external edges
// /////////////////////////////////////////////////////////////////

        } else if(!e->nodes.contains(edge->source()->node()) && e->nodes.contains(edge->destination()->node())) {

            

        } else if(!e->nodes.contains(edge->destination()->node()) && e->nodes.contains(edge->source()->node())) {


        }
    }

    foreach(dtkComposerSceneEdge *edge, e->lflles) {
        e->parent->removeEdge(edge);
        d->scene->removeItem(edge);
        edge->unlink();
    }

    foreach(dtkComposerSceneEdge *edge, e->rflles) {
        e->parent->removeEdge(edge);
        d->scene->removeItem(edge);
        edge->unlink();
    }

    foreach(dtkComposerSceneEdge *edge, e->llhses) {
        e->parent->addEdge(edge);
        d->scene->addItem(edge);
        edge->link();
    }

    foreach(dtkComposerSceneEdge *edge, e->lrhses) {
        e->node->addEdge(edge);
        edge->link();
    }

    foreach(dtkComposerSceneEdge *edge, e->rlhses) {
        e->node->addEdge(edge);
        edge->link();
    }

    foreach(dtkComposerSceneEdge *edge, e->rrhses) {
        e->parent->addEdge(edge);
        d->scene->addItem(edge);
        edge->link();
    }

    qDeleteAll(e->lflles);
    qDeleteAll(e->rflles);

    e->lflles.clear();
    e->rflles.clear();
    e->llhses.clear();
    e->lrhses.clear();
    e->rlhses.clear();
    e->rrhses.clear();

// /////////////////////////////////////////////////////////////////

    foreach(dtkComposerSceneNote *note, e->notes) {
        e->parent->removeNote(note);
        d->scene->removeItem(note);
        e->node->addNote(note);
        note->setParent(e->node);
    }

    e->parent->addNode(e->node);
    d->graph->addNode(e->node);
    d->scene->addItem(e->node);
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

void dtkComposerStackCommandEnterGroup::setBlock(dtkComposerSceneNodeComposite *block)
{
    e->node = block;

    e->former = dynamic_cast<dtkComposerSceneNodeComposite *>(e->node->parent()->parent());
}

void dtkComposerStackCommandEnterGroup::setNode(dtkComposerSceneNodeComposite *node)
{
    e->node = node;

    e->former = dynamic_cast<dtkComposerSceneNodeComposite *>(e->node->parent());
}

void dtkComposerStackCommandEnterGroup::redo(void)
{
    if(!e->node)
        return;

    if (e->former != d->scene->root())
        d->scene->removeItem(e->former);

    foreach(dtkComposerSceneNote *note, e->former->notes())
        d->scene->removeItem(note);

    foreach(dtkComposerSceneNode *node, e->former->nodes())
        d->scene->removeItem(node);

    foreach(dtkComposerSceneEdge *edge, e->former->edges())
        d->scene->removeItem(edge);

    e->node->enter();
    
    d->scene->addItem(e->node);

    d->scene->setCurrent(e->node);

    foreach(dtkComposerSceneNote *note, e->node->notes())
        d->scene->addItem(note);

    foreach(dtkComposerSceneNode *node, e->node->nodes())
        d->scene->addItem(node);

    foreach(dtkComposerSceneEdge *edge, e->node->edges()) {
        edge->adjust();
        d->scene->addItem(edge);
    }
}

void dtkComposerStackCommandEnterGroup::undo(void)
{
    if(!e->node)
        return;

    foreach(dtkComposerSceneNote *note, e->node->notes())
        d->scene->removeItem(note);

    foreach(dtkComposerSceneNode *node, e->node->nodes())
        d->scene->removeItem(node);

    foreach(dtkComposerSceneEdge *edge, e->node->edges())
        d->scene->removeItem(edge);

    d->scene->removeItem(e->node);

    e->node->leave();

    d->scene->setCurrent(e->former);
    
    if (e->former != d->scene->root())
        d->scene->addItem(e->former);

    foreach(dtkComposerSceneNote *note, e->former->notes())
        d->scene->addItem(note);

    foreach(dtkComposerSceneNode *node, e->former->nodes())
        d->scene->addItem(node);

    foreach(dtkComposerSceneEdge *edge, e->former->edges()) {
        edge->adjust();
        d->scene->addItem(edge);
    }

    e->node->layout();
}

// /////////////////////////////////////////////////////////////////
// Leave Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandLeaveGroupPrivate
{
public:
    dtkComposerSceneNodeComposite *node;

public:
    dtkComposerSceneNodeComposite *former;
};

dtkComposerStackCommandLeaveGroup::dtkComposerStackCommandLeaveGroup(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandLeaveGroupPrivate)
{
    e->node = NULL;
    e->former = NULL;

    this->setText("Leave group");
}

dtkComposerStackCommandLeaveGroup::~dtkComposerStackCommandLeaveGroup(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandLeaveGroup::setBlock(dtkComposerSceneNodeComposite *block)
{
    e->node = block;

    e->former = dynamic_cast<dtkComposerSceneNodeComposite *>(e->node->parent()->parent());
}

void dtkComposerStackCommandLeaveGroup::setNode(dtkComposerSceneNodeComposite *node)
{
    e->node = node;

    e->former = dynamic_cast<dtkComposerSceneNodeComposite *>(e->node->parent());
}

void dtkComposerStackCommandLeaveGroup::redo(void)
{
    if(!e->node)
        return;

    foreach(dtkComposerSceneNote *note, e->node->notes())
        d->scene->removeItem(note);

    foreach(dtkComposerSceneNode *node, e->node->nodes())
        d->scene->removeItem(node);

    foreach(dtkComposerSceneEdge *edge, e->node->edges())
        d->scene->removeItem(edge);

    d->scene->removeItem(e->node);

    e->node->leave();

    d->scene->setCurrent(e->former);
    
    if (e->former != d->scene->root())
        d->scene->addItem(e->former);

    foreach(dtkComposerSceneNote *note, e->former->notes())
        d->scene->addItem(note);

    foreach(dtkComposerSceneNode *node, e->former->nodes())
        d->scene->addItem(node);

    foreach(dtkComposerSceneEdge *edge, e->former->edges()) {
        edge->adjust();
        d->scene->addItem(edge);
    }

    e->node->layout();

    d->scene->update();
}

void dtkComposerStackCommandLeaveGroup::undo(void)
{
    if(!e->node)
        return;

    if (e->former != d->scene->root())
        d->scene->removeItem(e->former);

    foreach(dtkComposerSceneNote *note, e->former->notes())
        d->scene->removeItem(note);

    foreach(dtkComposerSceneNode *node, e->former->nodes())
        d->scene->removeItem(node);

    foreach(dtkComposerSceneEdge *edge, e->former->edges())
        d->scene->removeItem(edge);

    e->node->enter();
    
    d->scene->addItem(e->node);

    d->scene->setCurrent(e->node);

    foreach(dtkComposerSceneNote *note, e->node->notes())
        d->scene->addItem(note);

    foreach(dtkComposerSceneNode *node, e->node->nodes())
        d->scene->addItem(node);

    foreach(dtkComposerSceneEdge *edge, e->node->edges()) {
        edge->adjust();
        d->scene->addItem(edge);
    }

    e->node->layout();

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

    d->scene->removeItem(e->node);

    e->node->flatten();

    d->scene->addItem(e->node);
}

void dtkComposerStackCommandFlattenGroup::undo(void)
{
    if(!e->node)
        return;

    d->scene->removeItem(e->node);

    e->node->unflatten();

    d->scene->addItem(e->node);
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

    d->scene->addItem(e->node);
}

void dtkComposerStackCommandUnflattenGroup::undo(void)
{
    if(!e->node)
        return;

    d->scene->removeItem(e->node);

    e->node->flatten();

    d->scene->addItem(e->node);
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
};

dtkComposerStackCommandCreatePort::dtkComposerStackCommandCreatePort(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandCreatePortPrivate)
{
    e->node = NULL;
    e->port = NULL;
    e->transmitter = NULL;
    e->type = -1;

    this->setText("Create port");
}

dtkComposerStackCommandCreatePort::~dtkComposerStackCommandCreatePort(void)
{
    if (e->port)
        delete e->port;
    if (e->transmitter)
        delete e->transmitter;

    delete e;

    e = NULL;
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
            e->port = new dtkComposerScenePort(e->node->inputPorts().count(), dtkComposerScenePort::Input, e->node);
        if(!e->transmitter)
            e->transmitter = new dtkComposerTransmitterProxy(e->node->wrapee());
        e->node->addInputPort(e->port);
        e->node->layout();
        e->node->wrapee()->appendReceiver(e->transmitter);
        break;
    case dtkComposerScenePort::Output:
        if(!e->port)
            e->port = new dtkComposerScenePort(e->node->outputPorts().count(), dtkComposerScenePort::Output, e->node);
        if(!e->transmitter)
            e->transmitter = new dtkComposerTransmitterProxy(e->node->wrapee());
        e->node->addOutputPort(e->port);
        e->node->layout();
        e->node->wrapee()->appendEmitter(e->transmitter);
        break;
    default:
        break;
    };

    e->port->setVisible(true);

    d->scene->update();
}

void dtkComposerStackCommandCreatePort::undo(void)
{
    if(!e->node)
        return;

    if(!e->port)
        return;

    if(!d->scene)
        return;

    if(e->type < 0)
        return;

    switch(e->type) {
    case dtkComposerScenePort::Input:
        dynamic_cast<dtkComposerTransmitterProxy *>(e->transmitter)->clear();
        e->node->wrapee()->removeReceiver(e->transmitter);
        e->node->removeInputPort(e->port);
        e->node->layout();
        break;
    case dtkComposerScenePort::Output:
        dynamic_cast<dtkComposerTransmitterProxy *>(e->transmitter)->clear();
        e->node->wrapee()->removeEmitter(e->transmitter);
        e->node->removeOutputPort(e->port);
        e->node->layout();
        break;
    default:
        break;
    };

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
    e->port = port;
}

void dtkComposerStackCommandDestroyPort::redo(void)
{
    if(!e->node)
        return;

    if(!e->port)
        return;

    if(!d->scene)
        return;

    switch(e->port->type()) {
    case dtkComposerScenePort::Input:
        e->node->removeInputPort(e->port);
        if(!e->transmitter)
            e->transmitter = e->node->wrapee()->receivers().at(e->port->id());
        e->node->wrapee()->removeReceiver(e->transmitter);
        e->node->layout();
        break;
    case dtkComposerScenePort::Output:
        e->node->removeOutputPort(e->port);
        if(!e->transmitter)
            e->transmitter = e->node->wrapee()->emitters().at(e->port->id());
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

    switch(e->port->type()) {
    case dtkComposerScenePort::Input:
        e->node->addInputPort(e->port);
        e->node->wrapee()->appendReceiver(e->transmitter);
        e->node->layout();
        break;
    case dtkComposerScenePort::Output:
        e->node->addOutputPort(e->port);
        e->node->wrapee()->removeEmitter(e->transmitter);
        e->node->layout();
        break;
    default:
        break;
    };

    e->port->setVisible(true);

    d->scene->update();
}

// /////////////////////////////////////////////////////////////////
// Reparent Node Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandReparentNodePrivate
{
public:
    QPointF origin_pos;
    QPointF target_pos;

public:
    dtkComposerSceneNode *origin;
    dtkComposerSceneNode *target;

public:
    dtkComposerSceneNodeComposite *origin_parent;
};

dtkComposerStackCommandReparentNode::dtkComposerStackCommandReparentNode(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandReparentNodePrivate)
{
    e->origin_parent = NULL;
    e->origin = NULL;
    e->target = NULL;

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
    e->origin_parent = dynamic_cast<dtkComposerSceneNodeComposite *>(e->origin->parent());
}

void dtkComposerStackCommandReparentNode::setTargetNode(dtkComposerSceneNode *node)
{
    e->target = node;
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
    if(e->origin_pos.isNull())
        return;

    if(e->target_pos.isNull())
        return;

    if(!e->origin)
        return;

    if(!e->target)
        return;

    if (dtkComposerSceneNodeComposite *target = dynamic_cast<dtkComposerSceneNodeComposite *>(e->target)) {

        e->origin_parent->removeNode(e->origin);

        d->scene->removeItem(e->origin);
        
        target->addNode(e->origin);
        
        if (target->flattened()) {
            d->scene->addItem(e->origin);
            target->layout();
        }
        
        e->origin->setParent(target);
        e->origin->setPos(e->target_pos);

        target->layout();
    }

    d->scene->modify(true);
}

void dtkComposerStackCommandReparentNode::undo(void)
{
    if(e->origin_pos.isNull())
        return;

    if(e->target_pos.isNull())
        return;

    if(!e->origin)
        return;

    if(!e->target)
        return;

    if(dtkComposerSceneNodeComposite *target = dynamic_cast<dtkComposerSceneNodeComposite *>(e->target)) {

        target->removeNode(e->origin);
        
        if (target->flattened()) {
            target->layout();
            d->scene->removeItem(e->origin);
        }
        
        e->origin_parent->addNode(e->origin);
        e->origin->setParent(e->origin_parent);
        e->origin->setPos(e->origin_pos);

        if (e->origin_parent->flattened() || e->origin_parent->entered() || e->origin_parent->root())
            d->scene->addItem(e->origin);
    }

    if (dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(e->target)) {

        dtkComposerSceneNodeComposite *target = control->blockAt(e->target_pos);

        target->removeNode(e->origin);
        
        if (target->flattened()) {
            target->layout();
            d->scene->removeItem(e->origin);
        }
        
        e->origin_parent->addNode(e->origin);
        
        e->origin->setParent(e->origin_parent);
        e->origin->setPos(e->origin_pos);
        // e->origin->setParentItem(0);

        if (e->origin_parent->flattened() || e->origin_parent->entered() || e->origin_parent->root())
            d->scene->addItem(e->origin);

        control->layout();
    }

    d->scene->modify(true);
}

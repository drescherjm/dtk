/* dtkComposerStackCommand.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 18:17:43 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  2 13:47:05 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 103
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerFactory.h"
#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"
#include "dtkComposerStackCommand.h"

class dtkComposerStackCommandPrivate
{
public:
    dtkComposerFactory *factory;
    dtkComposerScene *scene;
};

dtkComposerStackCommand::dtkComposerStackCommand(dtkComposerStackCommand *parent) : QUndoCommand(parent), d(new dtkComposerStackCommandPrivate)
{
    d->factory = NULL;
    d->scene = NULL;
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

// /////////////////////////////////////////////////////////////////
// dtkComposerStackCommandCreateNode
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateNodePrivate
{
public:
    QString name;
    QString type;
    QPointF position;

public:
    dtkComposerSceneNode *node;
};

dtkComposerStackCommandCreateNode::dtkComposerStackCommandCreateNode(void) : dtkComposerStackCommand(), e(new dtkComposerStackCommandCreateNodePrivate)
{
    e->node = NULL;
}

dtkComposerStackCommandCreateNode::~dtkComposerStackCommandCreateNode(void)
{
    delete e->node;
    delete e;

    e = NULL;
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

    if(e->type.isEmpty())
        return;

    if(!e->node) {
        e->node = d->factory->create("");
        e->node->setPos(e->position);
    }

    d->scene->addNode(e->node);
}

void dtkComposerStackCommandCreateNode::undo(void)
{
    if(!e->node)
        return;

    e->position = e->node->scenePos();

    d->scene->removeNode(e->node);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerStackCommandDestroyNode
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyNodePrivate
{
public:
    dtkComposerSceneNode *node;

public:
    QList<dtkComposerSceneEdge *>  input_edges;
    QList<dtkComposerSceneEdge *> output_edges;
};

dtkComposerStackCommandDestroyNode::dtkComposerStackCommandDestroyNode(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandDestroyNodePrivate)
{
    e->node = NULL;

    this->setText("Destroy node");
}

dtkComposerStackCommandDestroyNode::~dtkComposerStackCommandDestroyNode(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandDestroyNode::setNode(dtkComposerSceneNode *node)
{
    e->node = node;
}

void dtkComposerStackCommandDestroyNode::redo(void)
{
    if(!d->scene)
        return;

    if(!e->node)
        return;

    foreach(dtkComposerSceneEdge *edge, e->node->inputEdges()) {
        if(d->scene->contains(edge)) {
            d->scene->removeEdge(edge);
            e->input_edges << edge;
        }
    }

    foreach(dtkComposerSceneEdge *edge, e->node->outputEdges()) {
        if(d->scene->contains(edge)) {
            d->scene->removeEdge(edge);
            e->output_edges << edge;
        }
    }

    d->scene->removeNode(e->node);
}

void dtkComposerStackCommandDestroyNode::undo(void)
{
    if(!e->node)
        return;

    d->scene->addNode(e->node);

    foreach(dtkComposerSceneEdge *edge, e->input_edges) {

        dtkComposerSceneNode *s_node = dynamic_cast<dtkComposerSceneNode *>(edge->source()->parentItem());
        dtkComposerSceneNode *d_node = dynamic_cast<dtkComposerSceneNode *>(edge->destination()->parentItem());

        if(s_node && d_node && d->scene->contains(s_node) && d->scene->contains(d_node)) {
            d->scene->addEdge(edge);
            e->input_edges.removeAll(edge);
        }
    }

    foreach(dtkComposerSceneEdge *edge, e->output_edges) {

        dtkComposerSceneNode *s_node = dynamic_cast<dtkComposerSceneNode *>(edge->source()->parentItem());
        dtkComposerSceneNode *d_node = dynamic_cast<dtkComposerSceneNode *>(edge->destination()->parentItem());

        if(s_node && d_node && d->scene->contains(s_node) && d->scene->contains(d_node)) {
            d->scene->addEdge(edge);
            e->output_edges.removeAll(edge);
        }
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerStackCommandCreateEdge
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateEdgePrivate
{
public:
    dtkComposerScenePort *source;
    dtkComposerScenePort *destination;

public:
    dtkComposerSceneEdge *edge;
};

dtkComposerStackCommandCreateEdge::dtkComposerStackCommandCreateEdge(void) : dtkComposerStackCommand(), e(new dtkComposerStackCommandCreateEdgePrivate)
{
    e->source = NULL;
    e->destination = NULL;
    e->edge = NULL;

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
    if(!d->scene)
        return;

    if(!e->source)
        return;

    if(!e->destination)
        return;

    e->edge = new dtkComposerSceneEdge;
    e->edge->setSource(e->source);
    e->edge->setDestination(e->destination);
    e->edge->link();
    e->edge->adjust();

    d->scene->addEdge(e->edge);
}

void dtkComposerStackCommandCreateEdge::undo(void)
{
    if(!e->edge)
        return;
    
    e->edge->unlink();

    d->scene->removeEdge(e->edge);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerStackCommandCreateNote
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateNotePrivate
{
public:
    QPointF position;

public:
    dtkComposerSceneNote *note;
};

dtkComposerStackCommandCreateNote::dtkComposerStackCommandCreateNote(void) : dtkComposerStackCommand(), e(new dtkComposerStackCommandCreateNotePrivate)
{
    e->note = NULL;

    this->setText("Create note");
}

dtkComposerStackCommandCreateNote::~dtkComposerStackCommandCreateNote(void)
{
    delete e->note;
    delete e;

    e = NULL;
}

void dtkComposerStackCommandCreateNote::setPosition(const QPointF& position)
{
    e->position = position;
}

void dtkComposerStackCommandCreateNote::redo(void)
{
    if(!d->scene)
        return;

    if(!e->note) {
        e->note = new dtkComposerSceneNote;
        e->note->setPos(e->position);
    }

    d->scene->addNote(e->note);
}

void dtkComposerStackCommandCreateNote::undo(void)
{
    if(!e->note)
        return;

    e->position = e->note->scenePos();

    d->scene->removeNote(e->note);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerStackCommandDestroyNote
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyNotePrivate
{
public:
    dtkComposerSceneNote *note;
};

dtkComposerStackCommandDestroyNote::dtkComposerStackCommandDestroyNote(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandDestroyNotePrivate)
{
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
}

void dtkComposerStackCommandDestroyNote::redo(void)
{
    if(!d->scene)
        return;

    if(!e->note)
        return;

    d->scene->removeNote(e->note);
}

void dtkComposerStackCommandDestroyNote::undo(void)
{
    if(!d->scene)
        return;

    if(!e->note)
        return;

    d->scene->addNote(e->note);
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateGroupPrivate
{
public:
    dtkComposerSceneNode *node;

public:
    QList<dtkComposerSceneNode *> children;
};

dtkComposerStackCommandCreateGroup::dtkComposerStackCommandCreateGroup(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandCreateGroupPrivate)
{
    e->node = NULL;

    this->setText("Create group");
}

dtkComposerStackCommandCreateGroup::~dtkComposerStackCommandCreateGroup(void)
{
    delete e;

    e = NULL;
}

void dtkComposerStackCommandCreateGroup::setNodes(QList<dtkComposerSceneNode *> nodes)
{
    e->children = nodes;
}

void dtkComposerStackCommandCreateGroup::redo(void)
{
    if(!d->scene)
        return;

    if(e->node)
        return;

    qDebug() << __func__;
}

void dtkComposerStackCommandCreateGroup::undo(void)
{
    if(!d->scene)
        return;

    qDebug() << __func__;
}

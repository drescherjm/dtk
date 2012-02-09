/* dtkComposerStackCommand.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 18:17:43 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  9 16:18:22 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 1279
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
#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerSceneNote.h"
#include "dtkComposerScenePort.h"
#include "dtkComposerStackCommand.h"

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
};

dtkComposerStackCommandCreateNode::dtkComposerStackCommandCreateNode(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandCreateNodePrivate)
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

    if(!d->graph)
        return;

    if(e->type.isEmpty())
        return;

    if(!e->node) {
        e->node = d->factory->create(e->type);
        e->node->setParent(d->scene->current());
    }
    
    e->node->setPos(e->position);

    d->scene->addNode(e->node);
    d->graph->addNode(e->node);

// --

    if (d->scene->current() != d->scene->root())
        d->scene->current()->layout();
}

void dtkComposerStackCommandCreateNode::undo(void)
{
    if(!d->scene)
        return;

    if(!d->graph)
        return;

    if(!e->node)
        return;

    e->position = e->node->scenePos();

    d->scene->removeNode(e->node);
    d->graph->removeNode(e->node);
}

// /////////////////////////////////////////////////////////////////
// Destroy Node Command
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

    foreach(dtkComposerSceneEdge *edge, e->node->inputEdges())
        e->input_edges << edge;

    foreach(dtkComposerSceneEdge *edge, e->node->outputEdges())
        e->output_edges << edge;
}

void dtkComposerStackCommandDestroyNode::redo(void)
{
    if(!d->scene)
        return;

    if(!e->node)
        return;

    foreach(dtkComposerSceneEdge *edge, e->input_edges)
        if (d->scene->items().contains(edge))
            d->scene->removeEdge(edge);

    foreach(dtkComposerSceneEdge *edge, e->output_edges)
        if (d->scene->items().contains(edge))
            d->scene->removeEdge(edge);

    d->scene->removeNode(e->node);
}

void dtkComposerStackCommandDestroyNode::undo(void)
{
    if(!e->node)
        return;

    d->scene->addNode(e->node);

    foreach(dtkComposerSceneEdge *edge, e->input_edges)
        if(!d->scene->items().contains(edge))
            d->scene->addEdge(edge);

    foreach(dtkComposerSceneEdge *edge, e->output_edges)
        if(!d->scene->items().contains(edge))
            d->scene->addEdge(edge);
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
};

dtkComposerStackCommandCreateEdge::dtkComposerStackCommandCreateEdge(void) : dtkComposerStackCommand(), e(new dtkComposerStackCommandCreateEdgePrivate)
{
    e->edge = NULL;
    e->source = NULL;
    e->destination = NULL;

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

    if(!e->edge) {
        e->edge = new dtkComposerSceneEdge;
        e->edge->setSource(e->source);
        e->edge->setDestination(e->destination);
        e->edge->setParent(d->scene->current());
    }

    e->edge->link();

    d->scene->addEdge(e->edge);
}

void dtkComposerStackCommandCreateEdge::undo(void)
{
    if(!d->scene)
        return;

    if(!e->edge)
        return;

    e->edge->unlink();

    d->scene->removeEdge(e->edge);
}

// /////////////////////////////////////////////////////////////////
// Destroy Edge Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyEdgePrivate
{
public:
    dtkComposerSceneEdge *edge;
};

dtkComposerStackCommandDestroyEdge::dtkComposerStackCommandDestroyEdge(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandDestroyEdgePrivate)
{
    e->edge = NULL;

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
}

void dtkComposerStackCommandDestroyEdge::redo(void)
{

}

void dtkComposerStackCommandDestroyEdge::undo(void)
{

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
};

dtkComposerStackCommandCreateNote::dtkComposerStackCommandCreateNote(dtkComposerStackCommand *parent) : dtkComposerStackCommand(), e(new dtkComposerStackCommandCreateNotePrivate)
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
        e->note->setParent(d->scene->current());
    }

    e->note->setPos(e->position);

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
// Destroy Note Command
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
// Create Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateGroupPrivate
{
public:
    dtkComposerSceneNodeComposite *node;

public:
    dtkComposerSceneEdgeList edges;
    dtkComposerSceneNodeList nodes;
    dtkComposerSceneNoteList notes;

public:
    QList<dtkComposerScenePort *> iports;
    QList<dtkComposerSceneEdge *> ilhses;
    QList<dtkComposerSceneEdge *> irhses;

public:
    QList<dtkComposerScenePort *> oports;
    QList<dtkComposerSceneEdge *> olhses;
    QList<dtkComposerSceneEdge *> orhses;

public:
    bool dirty;
};

dtkComposerStackCommandCreateGroup::dtkComposerStackCommandCreateGroup(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandCreateGroupPrivate)
{
    e->node = NULL;

    e->dirty = true;

    this->setText("Create group");
}

dtkComposerStackCommandCreateGroup::~dtkComposerStackCommandCreateGroup(void)
{
    qDeleteAll(e->iports);
    qDeleteAll(e->ilhses);
    qDeleteAll(e->irhses);
    
    qDeleteAll(e->oports);
    qDeleteAll(e->olhses);
    qDeleteAll(e->orhses);

    delete e;

    e = NULL;
}

void dtkComposerStackCommandCreateGroup::setNodes(dtkComposerSceneNodeList nodes)
{
    e->nodes = nodes;
}

void dtkComposerStackCommandCreateGroup::setNotes(dtkComposerSceneNoteList notes)
{
    e->notes = notes;
}

void dtkComposerStackCommandCreateGroup::redo(void)
{
    if(!d->scene)
        return;

    e->edges = d->scene->current()->edges();

    if(e->nodes.isEmpty())
        return;

    if(!e->node) {
        e->node = new dtkComposerSceneNodeComposite;
        e->node->setParent(d->scene->current());
    }
    
    QRectF rect;

    foreach(dtkComposerSceneNode *node, e->nodes) {
        rect |= node->sceneBoundingRect();
        d->scene->removeNode(node);
        e->node->addNode(node);
        node->setParent(e->node);
    }

    e->node->setPos(rect.center() - e->node->boundingRect().center());

    foreach(dtkComposerSceneEdge *edge, e->edges) {

        if (e->nodes.contains(edge->source()->node()) && e->nodes.contains(edge->destination()->node())) {

            d->scene->removeEdge(edge);
            e->node->addEdge(edge);
            edge->setParent(e->node);

// /////////////////////////////////////////////////////////////////
// -- Experimental: Handling external edges
// /////////////////////////////////////////////////////////////////

        } else if (!e->nodes.contains(edge->source()->node()) && e->nodes.contains(edge->destination()->node())) {

            edge->unlink();
            
            d->scene->removeEdge(edge);

            if(e->dirty) {

                dtkComposerScenePort *port = new dtkComposerScenePort(e->node->inputPorts().count()+e->node->outputPorts().count(), dtkComposerScenePort::Input, e->node);
                
                e->node->addInputPort(port);
                e->node->layout();
                
                dtkComposerSceneEdge *lhs = new dtkComposerSceneEdge;
                lhs->setSource(edge->source());
                lhs->setDestination(port);
                lhs->link();
                lhs->setParent(d->scene->current());
                
                dtkComposerSceneEdge *rhs = new dtkComposerSceneEdge;
                rhs->setSource(port);
                rhs->setDestination(edge->destination());
                rhs->link();
                rhs->setParent(e->node);
                
                d->scene->addEdge(lhs);
                e->node->addEdge(rhs);
                
                e->iports << port;
                e->ilhses << lhs;
                e->irhses << rhs;

            }

        } else if (!e->nodes.contains(edge->destination()->node()) && e->nodes.contains(edge->source()->node())) {

            edge->unlink();

            d->scene->removeEdge(edge);

            if(e->dirty) {

                dtkComposerScenePort *port = new dtkComposerScenePort(e->node->inputPorts().count()+e->node->outputPorts().count(), dtkComposerScenePort::Output, e->node);
                
                e->node->addOutputPort(port);
                e->node->layout();
                
                dtkComposerSceneEdge *lhs = new dtkComposerSceneEdge;
                lhs->setSource(edge->source());
                lhs->setDestination(port);
                lhs->link();
                lhs->setParent(e->node);
                
                dtkComposerSceneEdge *rhs = new dtkComposerSceneEdge;
                rhs->setSource(port);
                rhs->setDestination(edge->destination());
                rhs->link();
                rhs->setParent(d->scene->current());
                
                e->node->addEdge(lhs);            
                d->scene->addEdge(rhs);
                
                e->oports << port;
                e->olhses << lhs;
                e->orhses << rhs;

            }
        }
    }

    if(!e->dirty) {

        foreach(dtkComposerScenePort *port, e->iports) {
            e->node->addInputPort(port);
        }
        
        foreach(dtkComposerSceneEdge *edge, e->ilhses) {
            edge->link();
            d->scene->addEdge(edge);
        }
        
        foreach(dtkComposerSceneEdge *edge, e->irhses) {
            edge->link();
            e->node->addEdge(edge);
        }
        
        foreach(dtkComposerScenePort *port, e->oports) {
            e->node->addOutputPort(port);
        }
        
        foreach(dtkComposerSceneEdge *edge, e->olhses) {
            edge->link();
            e->node->addEdge(edge);
        }
        
        foreach(dtkComposerSceneEdge *edge, e->orhses) {
            edge->link();
            d->scene->addEdge(edge);
        }
    }

    e->dirty = false;
    
// /////////////////////////////////////////////////////////////////

    foreach(dtkComposerSceneNote *note, e->notes) {
        d->scene->removeNote(note);
        e->node->addNote(note);
        note->setParent(e->node);
    }

    d->scene->addNode(e->node);
}

void dtkComposerStackCommandCreateGroup::undo(void)
{
    if(!d->scene)
        return;

    if(!e->node)
        return;

    foreach(dtkComposerSceneNode *node, e->nodes) {
        d->scene->addNode(node);
        e->node->removeNode(node);
        node->setParent(e->node->parent());
    }

    foreach(dtkComposerSceneEdge *edge, e->edges) {

        if (e->nodes.contains(edge->source()->node()) && e->nodes.contains(edge->destination()->node())) {
            d->scene->addEdge(edge);
            e->node->removeEdge(edge);
            edge->setParent(e->node->parent());

// /////////////////////////////////////////////////////////////////
// -- Experimental: Handling external edges
// /////////////////////////////////////////////////////////////////

        } else if (!e->nodes.contains(edge->source()->node()) && e->nodes.contains(edge->destination()->node())) {

            edge->link();

            d->scene->addEdge(edge);

        } else if (!e->nodes.contains(edge->destination()->node()) && e->nodes.contains(edge->source()->node())) {
            
            edge->link();

            d->scene->addEdge(edge);
        }
    }

    foreach(dtkComposerScenePort *port, e->iports) {
        e->node->removeInputPort(port);
    }
    
    foreach(dtkComposerSceneEdge *edge, e->ilhses) {
        edge->unlink();
        d->scene->removeEdge(edge);
    }
    
    foreach(dtkComposerSceneEdge *edge, e->irhses) {
        edge->unlink();
        e->node->removeEdge(edge);
    }
    
    // qDeleteAll(e->iports);
    // qDeleteAll(e->ilhses);
    // qDeleteAll(e->irhses);
    
    // e->iports.clear();
    // e->ilhses.clear();
    // e->irhses.clear();
    
    foreach(dtkComposerScenePort *port, e->oports) {
        e->node->removeOutputPort(port);
    }
    
    foreach(dtkComposerSceneEdge *edge, e->olhses) {
        edge->unlink();
        e->node->removeEdge(edge);
    }
    
    foreach(dtkComposerSceneEdge *edge, e->orhses) {
        edge->unlink();
        d->scene->removeEdge(edge);
    }
    
    // qDeleteAll(e->oports);
    // qDeleteAll(e->olhses);
    // qDeleteAll(e->orhses);
    
    // e->oports.clear();
    // e->olhses.clear();
    // e->orhses.clear();
    
// /////////////////////////////////////////////////////////////////

    foreach(dtkComposerSceneNote *note, e->notes) {
        d->scene->addNote(note);
        e->node->removeNote(note);
        note->setParent(e->node->parent());
    }

    d->scene->removeNode(e->node);

    d->scene->update();
}

// /////////////////////////////////////////////////////////////////
// Destroy Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyGroupPrivate
{
public:
    dtkComposerSceneNodeComposite *node;

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
    e->node = NULL;

    this->setText("Destroy group");
}

dtkComposerStackCommandDestroyGroup::~dtkComposerStackCommandDestroyGroup(void)
{
    delete e;
    
    e = NULL;
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

    if(!e->node)
        return;

    e->edges = e->node->edges();

    foreach(dtkComposerSceneNode *node, e->nodes) {
        d->scene->addNode(node);
        e->node->removeNode(node);
        node->setParent(e->node->parent());
    }

    foreach(dtkComposerSceneEdge *edge, e->edges) {

        if (e->nodes.contains(edge->source()->node()) && e->nodes.contains(edge->destination()->node())) {
            d->scene->addEdge(edge);
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

                d->scene->addEdge(ed);

                e->lflles << ed;
            }

            lhs->unlink();
            rhs->unlink();
            
            d->scene->removeEdge(lhs);
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

                d->scene->addEdge(ed);

                e->rflles << ed;
            }

            lhs->unlink();
            rhs->unlink();
            
            e->node->removeEdge(lhs);
            d->scene->removeEdge(rhs);

            e->rlhses << lhs;
            e->rrhses << rhs;
        }

// /////////////////////////////////////////////////////////////////

    }

    foreach(dtkComposerSceneNote *note, e->notes) {
        d->scene->addNote(note);
        e->node->removeNote(note);
        note->setParent(e->node->parent());
    }

    d->scene->removeNode(e->node);
}

void dtkComposerStackCommandDestroyGroup::undo(void)
{
    if(!d->scene)
        return;

    if(!e->node)
        return;

    foreach(dtkComposerSceneNode *node, e->nodes) {
        d->scene->removeNode(node);
        e->node->addNode(node);
        node->setParent(e->node);
    }

    foreach(dtkComposerSceneEdge *edge, e->edges) {

        if (e->nodes.contains(edge->source()->node()) && e->nodes.contains(edge->destination()->node())) {
            d->scene->removeEdge(edge);
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
        d->scene->removeEdge(edge);
        edge->unlink();
    }

    foreach(dtkComposerSceneEdge *edge, e->rflles) {
        d->scene->removeEdge(edge);
        edge->unlink();
    }

    foreach(dtkComposerSceneEdge *edge, e->llhses) {
        d->scene->addEdge(edge);
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
        d->scene->addEdge(edge);
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
        d->scene->removeNote(note);
        e->node->addNote(note);
        note->setParent(e->node);
    }

    d->scene->addNode(e->node);
}

// /////////////////////////////////////////////////////////////////
// Enter Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandEnterGroupPrivate
{
public:
    dtkComposerSceneNodeComposite *node;
};

dtkComposerStackCommandEnterGroup::dtkComposerStackCommandEnterGroup(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandEnterGroupPrivate)
{
    e->node = NULL;

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

void dtkComposerStackCommandEnterGroup::redo(void)
{
    if(!e->node)
        return;

    if (d->scene->current() != d->scene->root())
        d->scene->removeItem(d->scene->current());

    foreach(dtkComposerSceneNote *note, d->scene->current()->notes())
        d->scene->removeItem(note);

    foreach(dtkComposerSceneNode *node, d->scene->current()->nodes())
        d->scene->removeItem(node);

    foreach(dtkComposerSceneEdge *edge, d->scene->current()->edges())
        d->scene->removeItem(edge);

    e->node->enter();
    
    d->scene->addItem(e->node);

    d->scene->setCurrent(e->node);

    foreach(dtkComposerSceneNote *note, d->scene->current()->notes())
        d->scene->addItem(note);

    foreach(dtkComposerSceneNode *node, d->scene->current()->nodes())
        d->scene->addItem(node);

    foreach(dtkComposerSceneEdge *edge, d->scene->current()->edges()) {
        edge->adjust();
        d->scene->addItem(edge);
    }
}

void dtkComposerStackCommandEnterGroup::undo(void)
{
    if(!e->node)
        return;

    foreach(dtkComposerSceneNote *note, d->scene->current()->notes())
        d->scene->removeItem(note);

    foreach(dtkComposerSceneNode *node, d->scene->current()->nodes())
        d->scene->removeItem(node);

    foreach(dtkComposerSceneEdge *edge, d->scene->current()->edges())
        d->scene->removeItem(edge);

    d->scene->removeItem(d->scene->current());

    e->node->leave();

    d->scene->setCurrent(e->node->parent());
    
    if (d->scene->current() != d->scene->root())
        d->scene->addItem(d->scene->current());

    foreach(dtkComposerSceneNote *note, d->scene->current()->notes())
        d->scene->addItem(note);

    foreach(dtkComposerSceneNode *node, d->scene->current()->nodes())
        d->scene->addItem(node);

    foreach(dtkComposerSceneEdge *edge, d->scene->current()->edges()) {
        edge->adjust();
        d->scene->addItem(edge);
    }
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

    foreach(dtkComposerSceneNote *note, d->scene->current()->notes())
        d->scene->removeItem(note);

    foreach(dtkComposerSceneNode *node, d->scene->current()->nodes())
        d->scene->removeItem(node);

    foreach(dtkComposerSceneEdge *edge, d->scene->current()->edges())
        d->scene->removeItem(edge);

    d->scene->removeItem(d->scene->current());

    e->node->leave();

    d->scene->setCurrent(e->node->parent());
    
    if (d->scene->current() != d->scene->root())
        d->scene->addItem(d->scene->current());

    foreach(dtkComposerSceneNote *note, d->scene->current()->notes())
        d->scene->addItem(note);

    foreach(dtkComposerSceneNode *node, d->scene->current()->nodes())
        d->scene->addItem(node);

    foreach(dtkComposerSceneEdge *edge, d->scene->current()->edges()) {
        edge->adjust();
        d->scene->addItem(edge);
    }

    d->scene->update();
}

void dtkComposerStackCommandLeaveGroup::undo(void)
{
    if(!e->node)
        return;

    if (d->scene->current() != d->scene->root())
        d->scene->removeItem(d->scene->current());

    foreach(dtkComposerSceneNote *note, d->scene->current()->notes())
        d->scene->removeItem(note);

    foreach(dtkComposerSceneNode *node, d->scene->current()->nodes())
        d->scene->removeItem(node);

    foreach(dtkComposerSceneEdge *edge, d->scene->current()->edges())
        d->scene->removeItem(edge);

    e->node->enter();
    
    d->scene->addItem(e->node);

    d->scene->setCurrent(e->node);

    foreach(dtkComposerSceneNote *note, d->scene->current()->notes())
        d->scene->addItem(note);

    foreach(dtkComposerSceneNode *node, d->scene->current()->nodes())
        d->scene->addItem(node);

    foreach(dtkComposerSceneEdge *edge, d->scene->current()->edges()) {
        edge->adjust();
        d->scene->addItem(edge);
    }

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
    
    foreach(dtkComposerSceneNote *note, e->node->notes())
        d->scene->addItem(note);

    foreach(dtkComposerSceneNode *node, e->node->nodes())
        d->scene->addItem(node);

    foreach(dtkComposerSceneEdge *edge, e->node->edges()) {
        edge->adjust();
        d->scene->addItem(edge);
    }
}

void dtkComposerStackCommandFlattenGroup::undo(void)
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

    foreach(dtkComposerSceneNote *note, e->node->notes())
        d->scene->removeItem(note);

    foreach(dtkComposerSceneNode *node, e->node->nodes())
        d->scene->removeItem(node);

    foreach(dtkComposerSceneEdge *edge, e->node->edges())
        d->scene->removeItem(edge);

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
    
    foreach(dtkComposerSceneNote *note, e->node->notes())
        d->scene->addItem(note);

    foreach(dtkComposerSceneNode *node, e->node->nodes())
        d->scene->addItem(node);

    foreach(dtkComposerSceneEdge *edge, e->node->edges()) {
        edge->adjust();
        d->scene->addItem(edge);
    }
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
    int type;
};

dtkComposerStackCommandCreatePort::dtkComposerStackCommandCreatePort(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandCreatePortPrivate)
{
    e->node = NULL;
    e->port = NULL;
    e->type = -1;

    this->setText("Create port");
}

dtkComposerStackCommandCreatePort::~dtkComposerStackCommandCreatePort(void)
{
    if(e->port)
        delete e->port;

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
    if(!e->node)
        return;

    if(e->type < 0)
        return;

    switch(e->type) {
    case dtkComposerScenePort::Input:
        if(!e->port)
            e->port = new dtkComposerScenePort(e->node->inputPorts().count()+e->node->outputPorts().count(), dtkComposerScenePort::Input, e->node);
        e->node->addInputPort(e->port);
        e->node->layout();
        break;
    case dtkComposerScenePort::Output:
        if(!e->port)
            e->port = new dtkComposerScenePort(e->node->inputPorts().count()+e->node->outputPorts().count(), dtkComposerScenePort::Output, e->node);
        e->node->addOutputPort(e->port);
        e->node->layout();
        break;
    default:
        break;
    };

    e->port->setVisible(true);
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
        e->node->removeInputPort(e->port);
        e->node->layout();
        break;
    case dtkComposerScenePort::Output:
        e->node->removeOutputPort(e->port);
        e->node->layout();
        break;
    default:
        break;
    };

    d->scene->update();

    e->port->setVisible(false);
}

// /////////////////////////////////////////////////////////////////
// Unflatten Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyPortPrivate
{
public:
    dtkComposerSceneNodeComposite *node;
    dtkComposerScenePort *port;
};

dtkComposerStackCommandDestroyPort::dtkComposerStackCommandDestroyPort(dtkComposerStackCommand *parent) : dtkComposerStackCommand(parent), e(new dtkComposerStackCommandDestroyPortPrivate)
{
    e->node = NULL;
    e->port = NULL;

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
        e->node->layout();
        break;
    case dtkComposerScenePort::Output:
        e->node->removeOutputPort(e->port);
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
        e->node->layout();
        break;
    case dtkComposerScenePort::Output:
        e->node->addOutputPort(e->port);
        e->node->layout();
        break;
    default:
        break;
    };

    e->port->setVisible(true);
}

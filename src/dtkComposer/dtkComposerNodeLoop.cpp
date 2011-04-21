/* dtkComposerNodeLoop.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar  7 09:26:54 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 21 12:16:36 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 77
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeLoop.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoopPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLoopPrivate
{
public:
    dtkComposerNodeControlBlock *current_block;

public:
    bool pre_running;
    bool post_running;

public:
    bool loop_condition;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoop implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLoop::dtkComposerNodeLoop(dtkComposerNode *parent) : dtkComposerNodeControl(parent), d(new dtkComposerNodeLoopPrivate)
{
    this->setColor(QColor("#004b07"));
    this->setTitle("Loop");
    this->setType("dtkComposerLoop");

    d->current_block = NULL;

    d->pre_running = false;
    d->post_running = false;

    d->loop_condition = false;
}

dtkComposerNodeLoop::~dtkComposerNodeLoop(void)
{
    delete d;
    
    d = NULL;
}

bool dtkComposerNodeLoop::isPreRunning(void)
{
    return d->pre_running;
}

bool dtkComposerNodeLoop::isPostRunning(void)
{
    return d->post_running;
}

bool dtkComposerNodeLoop::loopConditon(void)
{
    return d->loop_condition;
}

dtkComposerNodeControlBlock *dtkComposerNodeLoop::currentBlock(void)
{
    return d->current_block;
}

void dtkComposerNodeLoop::setPreRunning(bool pre_running)
{
    d->pre_running = pre_running;
}

void dtkComposerNodeLoop::setPostRunning(bool post_running)
{
    d->post_running = post_running;
}

void dtkComposerNodeLoop::setLoopCondition(bool loop_condition)
{
    d->loop_condition = loop_condition;
}

void dtkComposerNodeLoop::setCurrentBlock(dtkComposerNodeControlBlock *block)
{
    d->current_block = block;
}

void dtkComposerNodeLoop::pull(dtkComposerEdge *i_route, dtkComposerNodeProperty *property)
{
    if (property == this->inputProperty()) {
        
        foreach(dtkComposerEdge *relay_route, this->inputRelayRoutes()) {
            if (relay_route->source()->name() == "variable") {

                dtkComposerEdge *route = new dtkComposerEdge;
                route->setSource(this->inputProperty());
                route->setDestination(relay_route->destination());
                
                relay_route->destination()->node()->addInputRoute(route);
                this->addInputActiveRoute(route);
            }
        }

    } else {

        foreach(dtkComposerEdge *relay_route, this->inputRelayRoutes()) {
            if (relay_route->source() == property) {
                
                dtkComposerEdge *route = new dtkComposerEdge;
                route->setSource(i_route->source());
                route->setDestination(relay_route->destination());
                
                relay_route->destination()->node()->addInputRoute(route);
                this->addInputActiveRoute(route);
            }
        }
    }
}

void dtkComposerNodeLoop::run(void)
{
    foreach(dtkComposerNode *child, d->current_block->nodes()) 
        child->setDirty(true);

    foreach(dtkComposerNode *child, d->current_block->startNodes())
        child->update();
}

void dtkComposerNodeLoop::push(dtkComposerEdge *o_route, dtkComposerNodeProperty *property)
{
    if (property->name() == "variable" && property->type() == dtkComposerNodeProperty::Output) {
        
        dtkComposerEdge *route = new dtkComposerEdge;
        route->setSource(this->inputProperty());
        route->setDestination(o_route->destination());
        
        o_route->destination()->node()->addInputRoute(route);
        this->addOutputActiveRoute(route);

    } else {

        foreach(dtkComposerEdge *relay_route, this->outputRelayRoutes()) {
            if (relay_route->destination() == o_route->source()) {
                
                dtkComposerEdge *route = new dtkComposerEdge;
                route->setSource(relay_route->source());
                route->setDestination(o_route->destination());
                
                o_route->destination()->node()->addInputRoute(route);
                this->addOutputActiveRoute(route);
            }
        }
    }
}

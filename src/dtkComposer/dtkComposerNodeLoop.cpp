/* dtkComposerNodeLoop.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar  7 09:26:54 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Oct 13 17:41:41 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 197
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

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoopPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLoopPrivate
{
public:
    bool pre_running;
    bool post_running;

public:
    bool loop_condition;

public:
    QHash<dtkComposerNodeProperty *, QVariant> pass_through_variables;
    QHash<dtkComposerNodeProperty *, dtkComposerNodeProperty *> twin_properties;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoop implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLoop::dtkComposerNodeLoop(dtkComposerNode *parent) : dtkComposerNodeControl(parent), d(new dtkComposerNodeLoopPrivate)
{
    this->setColor(QColor("#004b07"));
    this->setTitle("Loop");
    this->setType("dtkComposerLoop");

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
    
QVariant dtkComposerNodeLoop::value(dtkComposerNodeProperty *property)
{
    return d->pass_through_variables.value(property, QVariant());
}

QList<QVariant> dtkComposerNodeLoop::passThroughVariables(void)
{
    return d->pass_through_variables.values();
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

void dtkComposerNodeLoop::setPassThroughVariable(dtkComposerNodeProperty *property, QVariant loop_variable)
{
    d->pass_through_variables.insert(property, loop_variable);
}

bool dtkComposerNodeLoop::dirtyBlockEndNodes(void)
{        
    foreach(dtkComposerEdge *o_route, this->outputRelayRoutes()) {
        if (o_route->destination()->blockedFrom() == this->currentBlock()->title()) {
            if(dtkComposerNodeLoop *loop = dynamic_cast<dtkComposerNodeLoop *>(o_route->source()->node())) {
                if(this->isChildOf(loop)) {
                    if(loop->isPreRunning() || loop->isRunning() || loop->isPostRunning()) {
                        continue;
                    } else {
                        return true;
                    }
                } else {
                    if (o_route->source()->node()->dirty())
                        return true;
                }
            } else {                
                if (o_route->source()->node()->dirty())
                    return true;
            }
        }
    }
    
    foreach(dtkComposerNode *node, this->currentBlock()->nodes())
        if(!node->outputEdges().count() && node->inputEdges().count() && node->dirty())
            return true;
    
    return false;
}

void dtkComposerNodeLoop::pull(dtkComposerEdge *i_route, dtkComposerNodeProperty *property)
{
    if (property->type() == dtkComposerNodeProperty::PassThroughInput) {

        dtkComposerNodeProperty *i_source;
        if (i_route->source()->node()->value(i_route->source()).convert(QVariant::Double)) {

            i_source = property;        
            d->pass_through_variables.insert(property, i_route->source()->node()->value(i_route->source()));

        } else {

            i_source = i_route->source();

        }

        foreach(dtkComposerNodeProperty *twin, this->outputProperties())
            if (twin->type() == dtkComposerNodeProperty::PassThroughOutput && twin->name() == property->name())
                d->twin_properties.insert(twin, i_source);
        
        foreach(dtkComposerEdge *relay_route, this->inputRelayRoutes()) {
            if (relay_route->source()->name() == property->name()) {
                
                dtkComposerEdge *route = new dtkComposerEdge;
                route->setSource(i_source);
                route->setDestination(relay_route->destination());
                
                relay_route->destination()->node()->addInputRoute(route);
                this->addInputActiveRoute(route);
            }
        }

    } else {

        dtkComposerNodeControl::pull(i_route, property);

    }
}

void dtkComposerNodeLoop::push(dtkComposerEdge *o_route, dtkComposerNodeProperty *property)
{
    if (this->inputProperty() && property->name() == this->inputProperty()->name() && property->type() == dtkComposerNodeProperty::Output) {
        
        dtkComposerEdge *route = new dtkComposerEdge;
        route->setSource(this->inputProperty());
        route->setDestination(o_route->destination());
        this->addOutputActiveRoute(route);
                
        if (o_route->destination()->type() == dtkComposerNodeProperty::HybridOutput || 
            o_route->destination()->type() == dtkComposerNodeProperty::PassThroughOutput || 
            (o_route->destination()->type() == dtkComposerNodeProperty::Input && o_route->destination()->node()->kind() == dtkComposerNode::Control && this->isChildOfControlNode(o_route->destination()->node()))) {

            dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(o_route->destination()->node());
            output_control_node->addOutputRelayRoute(route);
            
        } else {

            o_route->destination()->node()->addInputRoute(route);

        }

    } else if (property->type() == dtkComposerNodeProperty::PassThroughOutput && this->value(property).isValid()) {

        dtkComposerEdge *route = new dtkComposerEdge;
        route->setSource(d->twin_properties.value(property));
        route->setDestination(o_route->destination());
                
        o_route->destination()->node()->addInputRoute(route);
        this->addOutputActiveRoute(route);
                
        if (o_route->destination()->type() == dtkComposerNodeProperty::HybridOutput || 
            o_route->destination()->type() == dtkComposerNodeProperty::PassThroughOutput || 
            (o_route->destination()->type() == dtkComposerNodeProperty::Input && o_route->destination()->node()->kind() == dtkComposerNode::Control && this->isChildOfControlNode(o_route->destination()->node()))) {

            dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(o_route->destination()->node());
            output_control_node->addOutputRelayRoute(route);
            
        } else {

            o_route->destination()->node()->addInputRoute(route);

        }
        
    } else {

        dtkComposerNodeControl::push(o_route, property);

    }
}

void dtkComposerNodeLoop::updatePassThroughVariables(void)
{
    if (this->currentBlock()->title() == "loop")
        foreach(dtkComposerEdge *o_route, this->outputRelayRoutes())
            if (o_route->destination()->type() == dtkComposerNodeProperty::PassThroughOutput) {
                this->setPassThroughVariable(d->twin_properties.value(o_route->destination()), o_route->source()->node()->value(o_route->source()));
            }
}

/* dtkComposerNodeLoop.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar  7 09:26:54 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  7 16:03:19 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 220
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
#include "dtkComposerRoute.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoopPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLoopPrivate
{
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

    d->loop_condition = false;
}

dtkComposerNodeLoop::~dtkComposerNodeLoop(void)
{
    delete d;
    
    d = NULL;
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

void dtkComposerNodeLoop::setLoopCondition(bool loop_condition)
{
    d->loop_condition = loop_condition;
}

void dtkComposerNodeLoop::setPassThroughVariable(dtkComposerNodeProperty *property, QVariant loop_variable)
{
    d->pass_through_variables.insert(property, loop_variable);
}

void dtkComposerNodeLoop::pull(dtkComposerRoute *i_route, dtkComposerNodeProperty *property)
{
    if (property->type() == dtkComposerNodeProperty::PassThroughInput || (property->type() == dtkComposerNodeProperty::Generic && property->behavior() == dtkComposerNodeProperty::AsLoop)) {

        dtkComposerNodeProperty *i_source;
        if (i_route->source()->node()->value(i_route->source()).convert(QVariant::Double)) {

            i_source = property;        
            d->pass_through_variables.insert(property, i_route->source()->node()->value(i_route->source()));

        } else {

            i_source = i_route->source();

        }

        foreach(dtkComposerNodeProperty *twin, this->g->rightProperties()) {
            if ((twin->type() == dtkComposerNodeProperty::PassThroughOutput || (twin->type() == dtkComposerNodeProperty::Generic && property->behavior() == dtkComposerNodeProperty::AsLoop)) && twin->name() == property->name())
                d->twin_properties.insert(twin, i_source);
            
            foreach(dtkComposerRoute *relay_route, this->inputRelayRoutes()) {
                if (relay_route->source()->name() == property->name()) {
                    
                    dtkComposerRoute *route = new dtkComposerRoute;
                    route->setSource(i_source);
                    route->setDestination(relay_route->destination());
                    
                    relay_route->destination()->node()->l->appendLeftRoute(route);
                    this->addInputActiveRoute(route);
                }
            }
        }

    } else {

        dtkComposerNodeControl::pull(i_route, property);

    }
}

void dtkComposerNodeLoop::push(dtkComposerRoute *o_route, dtkComposerNodeProperty *property)
{
    if (this->inputProperty() && property->name() == this->inputProperty()->name() && (property->type() == dtkComposerNodeProperty::Output || (property->type() == dtkComposerNodeProperty::Generic && property->behavior() == dtkComposerNodeProperty::AsOutput))) {
        
        dtkComposerRoute *route = new dtkComposerRoute;
        route->setSource(this->inputProperty());
        route->setDestination(o_route->destination());
        this->addOutputActiveRoute(route);

        if (o_route->destination()->type() == dtkComposerNodeProperty::Generic) {
                                  
            if (o_route->destination()->position() == dtkComposerNodeProperty::Right) {   

                dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(o_route->destination()->node());
                output_control_node->addOutputRelayRoute(route);
            } else {
                o_route->destination()->node()->l->appendLeftRoute(route);
            }
      
        } else if (o_route->destination()->type() == dtkComposerNodeProperty::HybridOutput || 
            o_route->destination()->type() == dtkComposerNodeProperty::PassThroughOutput || 
            (o_route->destination()->type() == dtkComposerNodeProperty::Input && o_route->destination()->node()->kind() == dtkComposerNode::Control && this->isChildOfControlNode(o_route->destination()->node()))) {

            dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(o_route->destination()->node());
            output_control_node->addOutputRelayRoute(route);
            
        } else {

            o_route->destination()->node()->l->appendLeftRoute(route);

        }

    } else if ((property->type() == dtkComposerNodeProperty::PassThroughOutput || (property->type() == dtkComposerNodeProperty::Generic && property->behavior() == dtkComposerNodeProperty::AsLoop)) && this->value(property).isValid()) {

        dtkComposerRoute *route = new dtkComposerRoute;
        route->setSource(d->twin_properties.value(property));
        route->setDestination(o_route->destination());
                
        o_route->destination()->node()->l->appendLeftRoute(route);
        this->addOutputActiveRoute(route);
            
        if (o_route->destination()->type() == dtkComposerNodeProperty::Generic) {
                        
            if (o_route->destination()->position() == dtkComposerNodeProperty::Right) {
                dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(o_route->destination()->node());
                output_control_node->addOutputRelayRoute(route);
                
            } else {
                o_route->destination()->node()->l->appendLeftRoute(route);                            
            }
            
        } else if (o_route->destination()->type() == dtkComposerNodeProperty::HybridOutput || 
            o_route->destination()->type() == dtkComposerNodeProperty::PassThroughOutput || 
            (o_route->destination()->type() == dtkComposerNodeProperty::Input && o_route->destination()->node()->kind() == dtkComposerNode::Control && this->isChildOfControlNode(o_route->destination()->node()))) {

            dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(o_route->destination()->node());
            output_control_node->addOutputRelayRoute(route);
            
        } else {

            o_route->destination()->node()->l->appendLeftRoute(route);

        }
        
    } else {

        dtkComposerNodeControl::push(o_route, property);

    }
}

void dtkComposerNodeLoop::updatePassThroughVariables(void)
{
    if (this->currentBlock()->title() == "loop")
        foreach(dtkComposerRoute *o_route, this->outputRelayRoutes())
            if (o_route->destination()->type() == dtkComposerNodeProperty::PassThroughOutput || (o_route->destination()->type() == dtkComposerNodeProperty::Generic && o_route->destination()->behavior() == dtkComposerNodeProperty::AsLoop)) {
                this->setPassThroughVariable(d->twin_properties.value(o_route->destination()), o_route->source()->node()->value(o_route->source()));
            }
}

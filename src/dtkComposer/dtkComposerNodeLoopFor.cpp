/* dtkComposerNodeLoopFor.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:03:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov  9 16:25:13 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 300
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerEvaluator_p.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeLoopFor.h"
#include "dtkComposerNodeLoopFor_p.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoop implementation
// /////////////////////////////////////////////////////////////////

//! Creates a block defined by its \a title inside the for loop node
//! \a parent.
/*! 
 *  
 */
dtkComposerNodeControlBlock *dtkComposerNodeLoopForPrivate::createBlock(const QString& title, dtkComposerNodeLoopFor *parent)
{
    dtkComposerNodeControlBlock *block = new dtkComposerNodeControlBlock(title, parent);
    parent->appendBlock(block);
    block->setInteractive(false);

    if (title == "condition") {

        block->setHeightRatio(0.95);
        parent->appendBlockLeftProperty("variable", dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, block);
        parent->appendBlockRightProperty("condition", dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Single, block);

    } else if (title == "loop") {
        
        block->setHeightRatio(1.1);
        parent->appendBlockLeftProperty("variable", dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, block);
        parent->appendBlockRightProperty("variable", dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Single, block);
        
    } else if (title == "post") {

        block->setHeightRatio(0.95);
        parent->appendBlockLeftProperty("variable", dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, block);
        parent->appendBlockRightProperty("variable", dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Single, block);
        
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoop implementation
// /////////////////////////////////////////////////////////////////

//! Constructs a for loop control node.
/*! 
 *  
 */
dtkComposerNodeLoopFor::dtkComposerNodeLoopFor(dtkComposerNode *parent) : dtkComposerNodeLoop(parent), d(new dtkComposerNodeLoopForPrivate)
{
    d->createBlock("condition", this);
    d->createBlock("loop", this);
    d->createBlock("post", this);

    this->setColor(QColor("#005b07"));
    this->setInputPropertyName("variable");
    this->setTitle("For Loop");
    this->setType("dtkComposerLoopFor");

    d->node_cond = NULL;
    d->node_post = NULL;

    d->prop_cond = NULL;
    d->prop_post = NULL;

    d->loop_variable = QVariant();
    d->loop_variable_old = QVariant();
}

//! Destroys for loop control node.
/*! 
 *  
 */
dtkComposerNodeLoopFor::~dtkComposerNodeLoopFor(void)
{
    delete d;

    d = NULL;
}

//! Defines the layout of the for loop node.
/*! 
 *  Reimplemented from dtkComposerNodeControl.
 */
void dtkComposerNodeLoopFor::layout(void)
{
    dtkComposerNodeControl::layout();

    QRectF  node_rect = this->boundingRect();
    qreal node_radius = this->nodeRadius();

    int j;
    qreal offset = 23;
    
    foreach(dtkComposerNodeControlBlock *block, this->blocks()) { 

        block->setRect(QRectF(node_rect.x(),
                              node_rect.y() + offset,
                              node_rect.width(),
                              block->height()));

        offset += block->rect().height();

        j = 0;
        foreach(dtkComposerNodeProperty *property, block->leftProperties()) {

            property->setRect(QRectF(block->mapRectToParent(block->rect()).left() + node_radius,
                                     block->mapRectToParent(block->rect()).top()  + node_radius * (4*j + 1),
                                     2 * node_radius,
                                     2 * node_radius ));

            if (property->type() == dtkComposerNodeProperty::Output)
                property->mirror();

            if (property->name() == "variable")
                j++;

            j++;
        }
        j = 0;
        foreach(dtkComposerNodeProperty *property, block->rightProperties()) {

            property->setRect(QRectF(block->mapRectToParent(block->rect()).right() - node_radius * 3,
                                     block->mapRectToParent(block->rect()).top()   + node_radius * (4*j + 1),
                                     2 * node_radius,
                                     2 * node_radius ));

            if (property->type() == dtkComposerNodeProperty::Input)
                property->mirror();    

            if (property->name() == "variable" || property->name() == "condition") 
                j++;

            j++;
        }
    }     
}

//! Node delegates its own evaluation to the evaluator according to
//! Visitor Design Pattern.
/*! 
 * 
 */
bool dtkComposerNodeLoopFor::evaluate(dtkComposerEvaluatorPrivate *evaluator)
{
    return evaluator->evaluate(this);
}
   
//! 
/*! 
 * 
 */ 
QVariant dtkComposerNodeLoopFor::value(dtkComposerNodeProperty *property)
{
    QVariant value;
    if (property == this->inputProperty())
        value = d->loop_variable;
    else
        value = dtkComposerNodeLoop::value(property);

    return value;
}
   
//! 
/*! 
 * 
 */ 
void dtkComposerNodeLoopFor::pull(dtkComposerEdge *i_route, dtkComposerNodeProperty *property)
{
    if (this->inputProperty() && property == this->inputProperty()) {
        
        foreach(dtkComposerEdge *relay_route, this->inputRelayRoutes()) {
            if (relay_route->source()->name() == this->inputProperty()->name()) {

                dtkComposerEdge *route = new dtkComposerEdge;
                route->setSource(this->inputProperty());
                route->setDestination(relay_route->destination());
                
                relay_route->destination()->node()->l->appendLeftRoute(route);
                this->addInputActiveRoute(route);
            }
        }

    }

    dtkComposerNodeLoop::pull(i_route, property);
}
    

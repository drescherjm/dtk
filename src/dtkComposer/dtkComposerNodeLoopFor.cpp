/* dtkComposerNodeLoopFor.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:03:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Nov  4 10:21:28 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 279
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

// #define DTK_DEBUG_COMPOSER_INTERACTION 1
// #define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoop implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLoopFor::dtkComposerNodeLoopFor(dtkComposerNode *parent) : dtkComposerNodeLoop(parent), d(new dtkComposerNodeLoopForPrivate)
{
    d->block_cond = this->addBlock("condition");
    d->block_cond->setInteractive(false);
    d->block_cond->setHeightRatio(0.95);
    this->g->appendLeftProperty(d->block_cond->appendLeftProperty("variable", this));
    this->g->appendRightProperty(d->block_cond->appendRightProperty("condition", this));

    d->block_loop = this->addBlock("loop");
    d->block_loop->setInteractive(false);
    d->block_loop->setHeightRatio(1.1);
    this->g->appendLeftProperty(d->block_loop->appendLeftProperty("variable", this));
    this->g->appendRightProperty(d->block_loop->appendRightProperty("variable", this));

    d->block_post = this->addBlock("post");
    d->block_post->setInteractive(false);
    d->block_post->setHeightRatio(0.95);
    this->g->appendLeftProperty(d->block_post->appendLeftProperty("variable", this));
    this->g->appendRightProperty(d->block_post->appendRightProperty("variable", this));

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

dtkComposerNodeLoopFor::~dtkComposerNodeLoopFor(void)
{
    delete d;

    d = NULL;
}

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

// void dtkComposerNodeLoopFor::update(void)
// {
// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//     qDebug() << DTK_PRETTY_FUNCTION << this;
// #endif
    
//     // -- If update is invoked while node is running, update is not necessary.
    
//     if (this->isRunning()) {
        
//         return;
        
//     } else {
        
//         // -- Check that node is ready (ie dirty)

//         if (!this->dirty())
//             return;

//         // -- Check dirty input value

//         if (this->dirtyInputValue())
//             return;

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Dirty input value OK" << DTK_NO_COLOR;
// #endif

//         // -- Retrieve input value

//         d->loop_variable = dtkComposerNodeControl::value();

//         if (!d->loop_variable.isValid())
//             return;

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Input value valid" << DTK_NO_COLOR;
// #endif

//         // -- Check dirty inputs

//         if (this->dtkComposerNode::dirtyUpstreamNodes())
//             return;

//         // -- Mark dirty outputs

//         this->dtkComposerNode::markDirtyDownstreamNodes();

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "All output nodes are set to dirty" << DTK_NO_COLOR;
// #endif

//         // -- Clean active input routes

//         this->cleanInputActiveRoutes();

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Input active routes cleaned" << DTK_NO_COLOR;
// #endif

//         // -- Pull

//         foreach(dtkComposerEdge *i_route, this->l->leftRoutes())
//             this->pull(i_route, i_route->destination());

//         foreach(dtkComposerEdge *o_route, this->outputRelayRoutes()) {
//             if (o_route->destination()->blockedFrom() == d->block_cond->title()) {
//                 if (o_route->destination()->name() == "condition") {
//                     d->node_cond = o_route->source()->node();
//                     d->prop_cond = o_route->source();
//                 }
//             } else if (o_route->destination()->blockedFrom() == d->block_post->title()) {
//                 if (o_route->destination()->name() == "variable") {
//                     d->node_post = o_route->source()->node();
//                     d->prop_post = o_route->source();
//                 }
//             }
//         }

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Pull done" << DTK_NO_COLOR;
// #endif

//         // -- Node is now ready to run

//         this->setRunning(true);

//         // -- First of all, condition of loop evaluation is evaluated from conditional block.

//         this->setCurrentBlock(d->block_cond);
//         this->run();

//         // -- Loop evaluation is performed while condition is fullfilled

//         while(d->node_cond->value(d->prop_cond).toBool()) {

//             // -- Workflow of loop block is evaluated

//             this->setCurrentBlock(d->block_loop);
//             this->run();

//             // -- Loop variables, if present, are updated.
                
//             d->loop_variable_old = d->loop_variable;
//             this->updatePassThroughVariables();

//             // -- Loop variable is updated from post block.

//             this->setCurrentBlock(d->block_post);
//             this->run();            
//             d->loop_variable = d->node_post->value(d->prop_post);

//             // -- Loop condition is re-calculated from condition block.
            
//             this->setCurrentBlock(d->block_cond);
//             this->run();
            
//         }
            
//         // -- Clean active output routes

//         this->cleanOutputActiveRoutes();

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Output active routes cleaned" << DTK_NO_COLOR;
// #endif
        
//         // -- Push
        
//         foreach(dtkComposerEdge *o_route, this->l->rightRoutes())
//             this->push(o_route, o_route->source());

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Push done" << DTK_NO_COLOR;
// #endif

//         // -- Node is now clean and is no more running

//         this->setDirty(false);
//         this->setRunning(false);

//         // -- Forward to downstream nodes
            
// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_BLUE << DTK_PRETTY_FUNCTION << "Forward done" << DTK_NO_COLOR;
// #endif

//         foreach(dtkComposerEdge *o_route, this->l->rightRoutes())
//             o_route->destination()->node()->update();
            
//     }
// }
    
QVariant dtkComposerNodeLoopFor::value(dtkComposerNodeProperty *property)
{
    QVariant value;
    if (property == this->inputProperty())
        value = d->loop_variable;
    else
        value = dtkComposerNodeLoop::value(property);

    return value;
}

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
    

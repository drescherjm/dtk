/* dtkComposerEvaluator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Oct 24 12:57:38 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Oct 26 17:10:26 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 392
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerEvaluator.h"
#include "dtkComposerEvaluator_p.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeCase.h"
#include "dtkComposerNodeCase_p.h"
#include "dtkComposerNodeConditional.h"
#include "dtkComposerNodeConditional_p.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeLoopDataComposite.h"
#include "dtkComposerNodeLoopDataComposite_p.h"
#include "dtkComposerNodeLoopFor.h"
#include "dtkComposerNodeLoopFor_p.h"
#include "dtkComposerNodeLoopWhile.h"
#include "dtkComposerNodeLoopWhile_p.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerScene.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataComposite.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkGlobal.h>

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// Helper definitions
// /////////////////////////////////////////////////////////////////

// #define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate - evaluation
// /////////////////////////////////////////////////////////////////

void dtkComposerEvaluatorPrivate::run(void)
{
    emit evaluationStarted();

    while(!this->stack.isEmpty()) {
        dtkComposerNode *node = this->stack.pop();
        if(!node->evaluate(this))
            this->stack.push(node);
    }

    emit evaluationStopped();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate - evaluating generic node
// /////////////////////////////////////////////////////////////////

bool dtkComposerEvaluatorPrivate::evaluate(dtkComposerNode *node)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << node;
#endif

    if (!node->dirty())
        return true;

    if (node->kind() == dtkComposerNode::Composite) {

        foreach(dtkComposerNode *child, node->childNodes())
            this->stack.push(child);

        return true;
    }

    // -- Check dirty inputs

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_COLOR_BG_GREEN << "-- Check dirty inputs" << node->title() << DTK_NO_COLOR;
#endif

    if (node->dirtyUpstreamNodes())
        return true;

    // -- Mark dirty outputs

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_COLOR_BG_GREEN << "-- Mark dirty outputs" << node->title() << DTK_NO_COLOR;
#endif

    node->markDirtyDownstreamNodes();

    // -- Pull

    foreach(dtkComposerEdge *i_route, node->inputRoutes()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << "Pulling" << node->title() << i_route << DTK_NO_COLOR;
#endif
        node->pull(i_route, i_route->destination());
    }

    // -- Run node's logics

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_COLOR_BG_RED  << "Running node" << node->title() << "'s logics" << DTK_NO_COLOR;
#endif

    // int status = node->run();

    node->run(); int status = true;

    // -- Push

    foreach(dtkComposerEdge *o_route, node->outputRoutes()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << "Pushing" << node->title() << o_route << DTK_NO_COLOR;
#endif
        node->push(o_route, o_route->source());
    }

    // --

    node->setDirty(false);

    // -- Forward

    foreach(dtkComposerEdge *o_route, node->outputRoutes()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_BLUE << "Forwarding" << node->title() << "->" << o_route->destination()->node()->title() << DTK_NO_COLOR;
#endif
        if(!this->stack.contains(o_route->destination()->node()))
            this->stack.push(o_route->destination()->node());
    }

    // --

    return status;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate - evaluating case node
// /////////////////////////////////////////////////////////////////

bool dtkComposerEvaluatorPrivate::evaluate(dtkComposerNodeCase *node)
{
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_PRETTY_FUNCTION << node;
#endif
    
    // -- If update is invoked while node is running, update is not necessary.
    
    if (node->isRunning()) {
        
        return true;
        
    } else {
        
        // -- Check that node is ready (ie dirty)

        if (!node->dirty())
            return true;

        // -- Check dirty input value

        if (node->dirtyInputValue())
            return true;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Dirty input value OK" << DTK_NO_COLOR;
#endif

        // -- Retrieve input value

        QVariant value = node->dtkComposerNodeControl::value();

        if (!value.isValid())
            return true;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Input value valid" << DTK_NO_COLOR;
#endif

        // -- Block selection
        
        dtkComposerNodeProperty *property = NULL;

        QVariant constant;

        node->setCurrentBlock(NULL);

        foreach(dtkComposerNodeControlBlock *block, node->d->block_cases) {

            property = node->inputProperty(block->title(), "constant");

            if(!property)
                continue;

            property->setBehavior(dtkComposerNodeProperty::AsInput);

            if(!property->edge())
                continue;
            
            if (property->edge()->source()->node()->dirty()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_MAGENTA << DTK_PRETTY_FUNCTION << "Constant is dirty" << DTK_NO_COLOR;
#endif
                return true;
            }

            constant = property->edge()->source()->node()->value(property->edge()->source());

            if (constant == value) {
                node->setCurrentBlock(block);
                break;
            }
        }

        if(!node->currentBlock())
            node->setCurrentBlock(node->d->block_default);

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Selected block is" << node->currentBlock()->title() << DTK_NO_COLOR;
#endif

        // -- Check dirty inputs

        if (node->dirtyUpstreamNodes()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_MAGENTA << DTK_PRETTY_FUNCTION << "Some upstream nodes are dirty" << DTK_NO_COLOR;
#endif
            return true;
        }

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "All input nodes are clean" << DTK_NO_COLOR;
#endif

        // -- Mark dirty outputs

        node->markDirtyDownstreamNodes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "All output nodes are set to dirty" << DTK_NO_COLOR;
#endif

        // -- Clean active input routes

        node->cleanInputActiveRoutes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Input active routes cleaned" << DTK_NO_COLOR;
#endif

        // -- Pull

        foreach(dtkComposerEdge *i_route, node->inputRoutes())
            if (i_route->destination()->blockedFrom() == node->currentBlock()->title() || i_route->destination() == node->inputProperty())
                node->pull(i_route, i_route->destination());

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Pull done" << DTK_NO_COLOR;
#endif
        
        // -- Node is now ready to run
        
        node->setRunning(true);
        
        // -- Running logics

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_RED  << "Running node" << node->title() << "'s logics" << DTK_NO_COLOR;
#endif

        { // node->run();

        dtkComposerEvaluatorPrivate evaluator;

        foreach(dtkComposerNode *child, node->currentBlock()->nodes())
            child->setDirty(true);
        
        foreach(dtkComposerNode *child, node->currentBlock()->startNodes())
            evaluator.stack.push(child);

        evaluator.run();

        }

        // -- Clean active output routes

        node->cleanOutputActiveRoutes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Output active routes cleaned" << DTK_NO_COLOR;
#endif

        // -- Push

        foreach(dtkComposerEdge *o_route, node->outputRoutes())
            if (o_route->source()->blockedFrom() == node->currentBlock()->title())
                node->push(o_route, o_route->source());

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Push done" << DTK_NO_COLOR;
#endif

        // -- Node is now clean and is no more running

        node->setDirty(false);
        node->setRunning(false);

        // -- Forward to downstream nodes

        foreach(dtkComposerEdge *o_route, node->outputRoutes()) {
            if (o_route->source()->blockedFrom() == node->currentBlock()->title()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                qDebug() << DTK_COLOR_BG_BLUE << "Forwarding" << node->title() << "->" << o_route->destination()->node()->title() << DTK_NO_COLOR;
#endif      
                if(!this->stack.contains(o_route->destination()->node()))
                    this->stack.push(o_route->destination()->node());
            }
        }
    }
    
    return true;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate - evaluating if node
// /////////////////////////////////////////////////////////////////

bool dtkComposerEvaluatorPrivate::evaluate(dtkComposerNodeConditional *node)
{
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_PRETTY_FUNCTION << node;
#endif
    
    // -- If update is invoked while node is running, update is not necessary.
    
    if (node->isRunning()) {

        return true;
    
    } else {

         // -- Check that node is ready (ie dirty)

        if (!node->dirty())
            return true;

        // -- Check dirty input value

        if (node->dirtyInputValue())
            return true;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Dirty input value OK" << DTK_NO_COLOR;
#endif

        // -- Block selection

        if(node->condition())
            node->setCurrentBlock(node->d->block_then);
        else
            node->setCurrentBlock(node->d->block_else);

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Selected block is" << node->currentBlock()->title() << DTK_NO_COLOR;
#endif

        // -- Check dirty inputs

        if (node->dirtyUpstreamNodes())
            return true;

        // -- Mark dirty outputs

        node->markDirtyDownstreamNodes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "All output nodes are set to dirty" << DTK_NO_COLOR;
#endif

        // -- Clean active input routes

        node->cleanInputActiveRoutes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Input active routes cleaned" << DTK_NO_COLOR;
#endif

        // -- Pull

        foreach(dtkComposerEdge *i_route, node->inputRoutes())
            if (i_route->destination()->blockedFrom() == node->currentBlock()->title())
                node->pull(i_route, i_route->destination());

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Pull done" << DTK_NO_COLOR;
#endif

        // -- Node is now ready to run

        node->setRunning(true);
        
        // -- Running logics

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_COLOR_BG_RED  << "Running node" << node->title() << "'s logics" << DTK_NO_COLOR;
#endif

        node->run();

        // -- Clean active output routes

        node->cleanOutputActiveRoutes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Output active routes cleaned" << DTK_NO_COLOR;
#endif

        // -- Push

        foreach(dtkComposerEdge *o_route, node->outputRoutes())
            if (o_route->source()->blockedFrom() == node->currentBlock()->title())
                node->push(o_route, o_route->source());

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Push done" << DTK_NO_COLOR;
#endif

        // -- Node is now clean and is no more running

        node->setDirty(false);
        node->setRunning(false);

        // -- Forward to downstream nodes

        foreach(dtkComposerEdge *o_route, node->outputRoutes()) {
            if (o_route->source()->blockedFrom() == node->currentBlock()->title()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                qDebug() << DTK_COLOR_BG_BLUE << "Forwarding" << node->title() << "->" << o_route->destination()->node()->title() << DTK_NO_COLOR;
#endif      
                if(!this->stack.contains(o_route->destination()->node()))
                    this->stack.push(o_route->destination()->node());
            }
        }
    }

    return true;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate - evaluating loop on composite node
// /////////////////////////////////////////////////////////////////

bool dtkComposerEvaluatorPrivate::evaluate(dtkComposerNodeLoopDataComposite *node)
{
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_PRETTY_FUNCTION << node;
#endif
    
    // -- If update is invoked while node is running, update is not necessary.
    
    if (node->isRunning()) {

        return true;
    
    } else {

         // -- Check that node is ready (ie dirty)

        if (!node->dirty())
            return true;

        // -- Check dirty input value

        if (node->dirtyInputValue())
            return true;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Dirty input value OK" << DTK_NO_COLOR;
#endif

        // -- Check dirty inputs

        if (node->dtkComposerNode::dirtyUpstreamNodes())
            return true;

        // -- Mark dirty outputs

        node->dtkComposerNode::markDirtyDownstreamNodes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "All output nodes are set to dirty" << DTK_NO_COLOR;
#endif

        // -- Clean active input routes

        node->cleanInputActiveRoutes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Input active routes cleaned" << DTK_NO_COLOR;
#endif

        // -- Pull

        foreach(dtkComposerEdge *i_route, node->inputRoutes())
            node->pull(i_route, i_route->destination());

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Pull done" << DTK_NO_COLOR;
#endif

        // -- Set input relay routes connected to item and index properties

        foreach(dtkComposerEdge *relay_route, node->inputRelayRoutes()) {

            if (relay_route->source()->name() == "item" || relay_route->source()->name() == "index") {

                dtkComposerEdge *route = new dtkComposerEdge;
                route->setSource(relay_route->source());
                route->setDestination(relay_route->destination());
                
                relay_route->destination()->node()->addInputRoute(route);
                node->addInputActiveRoute(route);
            
            }
        }

        // -- Set input composite and loop options

        foreach(dtkComposerEdge *i_route, node->inputRoutes()) {
            if (i_route->destination() == node->inputProperty()) {
        
                dtkAbstractData *data = NULL;

                if(dtkAbstractData *dt = qobject_cast<dtkAbstractData *>(i_route->source()->node()->object())) {
                    
                    data = dt;                    

                } else if(dtkAbstractProcess *process = qobject_cast<dtkAbstractProcess *>(i_route->source()->node()->object())) {
                                        
                    if(i_route->source()->node()->outputProperties().count() >= 1)
                        data = process->output(i_route->source()->node()->number(i_route->source()));
                    else
                        data = process->output();

                }
                
                if (data) {

                    node->d->composite = qobject_cast<dtkAbstractDataComposite *>(data);
                    if (!node->d->composite) {
                        dtkDebug() << DTK_PRETTY_FUNCTION << "input data is not of dtkAbstractDataComposite* type.";
                        return true;
                    }
                    node->d->to_default = node->d->composite->count()-1;
                    node->d->valid_input_composite = true;

                } else {

                    dtkDebug() << DTK_PRETTY_FUNCTION << "input data is not defined";
                    return true;

                }

            } else if (i_route->destination()->name() == "from") {

                node->d->from = (dtkxarch_int)(i_route->source()->node()->value(i_route->source()).toLongLong());   

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "from value =" << node->d->from << DTK_NO_COLOR;
#endif

            } else if (i_route->destination()->name() == "to") {

                node->d->to = (dtkxarch_int)(i_route->source()->node()->value(i_route->source()).toLongLong()); 

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "to value =" << node->d->to << DTK_NO_COLOR;
#endif

            } else if (i_route->destination()->name() == "step") {

                node->d->step = (dtkxarch_int)(i_route->source()->node()->value(i_route->source()).toLongLong());

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "step value =" << node->d->step << DTK_NO_COLOR;
#endif

            }
        }
 
        if (!node->d->valid_input_composite) {
            dtkDebug() << DTK_PRETTY_FUNCTION << " input composite property is not connected.";
            return true;   
        }

        // -- Set ranges and step of the loop

        if (node->d->from > node->d->to) {

            if (node->d->from > node->d->to_default)
                node->d->from = node->d->to_default;
            if (node->d->to < 0)
                node->d->to = node->d->from_default;
            if (node->d->step > 0)
                node->d->step *= -1;

        } else {

            if (node->d->from < 0)
                node->d->from = node->d->from_default;
            if (node->d->to > node->d->to_default || node->d->to < 0)
                node->d->to = node->d->to_default;
            if (node->d->step < 0)
                node->d->step *= -1;

        }
        node->d->index = node->d->from;
        
         // -- Node is now ready to run

         node->setRunning(true);

         // -- Loop evaluation is performed while condition is fullfilled

        while(node->d->index <= node->d->to) {

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
            qDebug() << DTK_COLOR_BG_RED  << "Loop is running, index = " << node->d->index << DTK_NO_COLOR;
#endif

            // -- Set current available item of the composite

            node->d->item = node->d->composite->at(node->d->index);
            node->setObject(node->d->item, false);

             // -- Workflow of loop block is evaluated

            { // node->run()

                dtkComposerEvaluatorPrivate evaluator;
                
                foreach(dtkComposerNode *child, node->currentBlock()->nodes())
                    child->setDirty(true);
                
                foreach(dtkComposerNode *child, node->currentBlock()->startNodes())
                    evaluator.stack.push(child);
                
                evaluator.run();
                
            }

            // -- Loop variables, if present, are updated.

            node->updatePassThroughVariables();

            // -- Increment loop index

            node->d->index += node->d->step;
            
        }
        node->d->index -= node->d->step;
            
        // -- Clean active output routes

        node->cleanOutputActiveRoutes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Output active routes cleaned" << DTK_NO_COLOR;
#endif
            
        // -- Push
            
        foreach(dtkComposerEdge *o_route, node->outputRoutes())
            node->push(o_route, o_route->source());

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Push done" << DTK_NO_COLOR;
#endif

         // -- Node is now clean and is no more running

        node->setDirty(false);
        node->setRunning(false);
            
        // -- Forward

        foreach(dtkComposerEdge *o_route, node->outputRoutes()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
            qDebug() << DTK_COLOR_BG_BLUE << "Forwarding" << node->title() << "->" << o_route->destination()->node()->title() << DTK_NO_COLOR;
#endif
            if(!this->stack.contains(o_route->destination()->node()))
                this->stack.push(o_route->destination()->node());
        }
    }

    return true;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate - evaluating for node
// /////////////////////////////////////////////////////////////////

bool dtkComposerEvaluatorPrivate::evaluate(dtkComposerNodeLoopFor *node)
{
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_PRETTY_FUNCTION << node;
#endif
    
    // -- If update is invoked while node is running, update is not necessary.
    
    if (node->isRunning()) {
        
        return true;
        
    } else {
        
        // -- Check that node is ready (ie dirty)

        if (!node->dirty())
            return true;

        // -- Check dirty input value

        if (node->dirtyInputValue())
            return true;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Dirty input value OK" << DTK_NO_COLOR;
#endif

        // -- Retrieve input value

        node->d->loop_variable = node->dtkComposerNodeControl::value();

        if (!node->d->loop_variable.isValid())
            return true;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Input value valid" << DTK_NO_COLOR;
#endif

        // -- Check dirty inputs

        if (node->dtkComposerNode::dirtyUpstreamNodes())
            return true;

        // -- Mark dirty outputs

        node->dtkComposerNode::markDirtyDownstreamNodes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "All output nodes are set to dirty" << DTK_NO_COLOR;
#endif

        // -- Clean active input routes

        node->cleanInputActiveRoutes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Input active routes cleaned" << DTK_NO_COLOR;
#endif

        // -- Pull

        foreach(dtkComposerEdge *i_route, node->inputRoutes())
            node->pull(i_route, i_route->destination());

        foreach(dtkComposerEdge *o_route, node->outputRelayRoutes()) {
            if (o_route->destination()->blockedFrom() == node->d->block_cond->title()) {
                if (o_route->destination()->name() == "condition") {
                    node->d->node_cond = o_route->source()->node();
                    node->d->prop_cond = o_route->source();
                }
            } else if (o_route->destination()->blockedFrom() == node->d->block_post->title()) {
                if (o_route->destination()->name() == "variable") {
                    node->d->node_post = o_route->source()->node();
                    node->d->prop_post = o_route->source();
                }
            }
        }

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Pull done" << DTK_NO_COLOR;
#endif

        // -- Node is now ready to run

        node->setRunning(true);

        // -- First of all, condition of loop evaluation is evaluated from conditional block.

        node->setCurrentBlock(node->d->block_cond);
        node->run();

        // -- Loop evaluation is performed while condition is fullfilled

        while(node->d->node_cond->value(node->d->prop_cond).toBool()) {

            // -- Workflow of loop block is evaluated

            node->setCurrentBlock(node->d->block_loop);
            node->run();

            // -- Loop variables, if present, are updated.
                
            node->d->loop_variable_old = node->d->loop_variable;
            node->updatePassThroughVariables();

            // -- Loop variable is updated from post block.

            node->setCurrentBlock(node->d->block_post);
            node->run();            
            node->d->loop_variable = node->d->node_post->value(node->d->prop_post);

            // -- Loop condition is re-calculated from condition block.
            
            node->setCurrentBlock(node->d->block_cond);
            node->run();
            
        }
            
        // -- Clean active output routes

        node->cleanOutputActiveRoutes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Output active routes cleaned" << DTK_NO_COLOR;
#endif
        
        // -- Push
        
        foreach(dtkComposerEdge *o_route, node->outputRoutes())
            node->push(o_route, o_route->source());

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Push done" << DTK_NO_COLOR;
#endif

        // -- Node is now clean and is no more running

        node->setDirty(false);
        node->setRunning(false);

        // -- Forward to downstream nodes
                
        foreach(dtkComposerEdge *o_route, node->outputRoutes()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
            qDebug() << DTK_COLOR_BG_BLUE << "Forwarding" << node->title() << "->" << o_route->destination()->node()->title() << DTK_NO_COLOR;
#endif
            if(!this->stack.contains(o_route->destination()->node()))
                this->stack.push(o_route->destination()->node());
        }            
    }

    return true;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate - evaluating while node
// /////////////////////////////////////////////////////////////////

bool dtkComposerEvaluatorPrivate::evaluate(dtkComposerNodeLoopWhile *node)
{
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_PRETTY_FUNCTION << node;
#endif
    
    // -- If update is invoked while node is running, update is not necessary.
    
    if (node->isRunning()) {
        
        return true;
        
    } else {
        
        // -- Check that node is ready (ie dirty)
        
        if (!node->dirty())
            return true;
        
        // -- Check dirty inputs
        
        if (node->dtkComposerNode::dirtyUpstreamNodes())
            return true;
        
        // -- Mark dirty outputs
        
        node->dtkComposerNode::markDirtyDownstreamNodes();
        
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "All output nodes are set to dirty" << DTK_NO_COLOR;
#endif
        
        // -- Clean active input routes
        
        node->cleanInputActiveRoutes();
        
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Input active routes cleaned" << DTK_NO_COLOR;
#endif
        
        // -- Pull
        
        foreach(dtkComposerEdge *i_route, node->inputRoutes())
            node->pull(i_route, i_route->destination());
        
        foreach(dtkComposerEdge *o_route, node->outputRelayRoutes()) {
            if (o_route->destination()->blockedFrom() == node->d->block_cond->title()) {
                if (o_route->destination()->name() == "condition") {
                    node->d->node_cond = o_route->source()->node();
                    node->d->prop_cond = o_route->source();
                }
            }
        }

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Pull done" << DTK_NO_COLOR;
#endif

        // -- Node is now ready to run

        node->setRunning(true);

        // -- First of all, condition of loop evaluation is evaluated from conditional block.

        node->setCurrentBlock(node->d->block_cond);

        { // node->run()

            dtkComposerEvaluatorPrivate evaluator;
            
            foreach(dtkComposerNode *child, node->currentBlock()->nodes())
                child->setDirty(true);
            
            foreach(dtkComposerNode *child, node->currentBlock()->startNodes())
                evaluator.stack.push(child);
            
            evaluator.run();
        }

        // -- Loop evaluation is performed while condition is fullfilled

        while(node->d->node_cond->value(node->d->prop_cond).toBool()) {

            // -- Workflow of loop block is evaluated

            node->setCurrentBlock(node->d->block_loop);

            { // node->run()

                dtkComposerEvaluatorPrivate evaluator;
                
                foreach(dtkComposerNode *child, node->currentBlock()->nodes())
                    child->setDirty(true);
                
                foreach(dtkComposerNode *child, node->currentBlock()->startNodes())
                    evaluator.stack.push(child);
                
                evaluator.run();
                
            }

            // -- Loop variables, if present, are updated.

            node->updatePassThroughVariables();

            // -- Loop condition is re-calculated from condition block.

            node->setCurrentBlock(node->d->block_cond);

            { // node->run()

                dtkComposerEvaluatorPrivate evaluator;
                
                foreach(dtkComposerNode *child, node->currentBlock()->nodes())
                    child->setDirty(true);
                
                foreach(dtkComposerNode *child, node->currentBlock()->startNodes())
                    evaluator.stack.push(child);
                
                evaluator.run();
                
            }
        }

        // -- Clean active output routes

        node->cleanOutputActiveRoutes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Output active routes cleaned" << DTK_NO_COLOR;
#endif

        // -- Push

        foreach(dtkComposerEdge *o_route, node->outputRoutes())
            node->push(o_route, o_route->source());

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Push done" << DTK_NO_COLOR;
#endif

        // -- Node is now clean and is no more running

        node->setDirty(false);
        node->setRunning(false);

        // -- Forward to downstream nodes
                
        foreach(dtkComposerEdge *o_route, node->outputRoutes()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
            qDebug() << DTK_COLOR_BG_BLUE << "Forwarding" << node->title() << "->" << o_route->destination()->node()->title() << DTK_NO_COLOR;
#endif
            if(!this->stack.contains(o_route->destination()->node()))
                this->stack.push(o_route->destination()->node());
        }
    }

    return true;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluator
// /////////////////////////////////////////////////////////////////

dtkComposerEvaluator::dtkComposerEvaluator(QObject *parent) : QObject(parent), d(new dtkComposerEvaluatorPrivate)
{
    d->scene = NULL;

    connect(d, SIGNAL(evaluationStarted()), this, SIGNAL(evaluationStarted()));
    connect(d, SIGNAL(evaluationStarted()), this, SIGNAL(evaluationStopped()));
}

dtkComposerEvaluator::~dtkComposerEvaluator(void)
{
    d->terminate();
    d->wait();

    delete d;
}

void dtkComposerEvaluator::setScene(dtkComposerScene *scene)
{
    d->scene = scene;
}

void dtkComposerEvaluator::start(void)
{
    if(!d->scene) {
        qDebug() << DTK_PRETTY_FUNCTION << "No scene set";
        return;
    }

    if(!d->stack.isEmpty()) {
        qDebug() << DTK_PRETTY_FUNCTION << "Stack is not empty";
        return;
    }

    if (d->scene->selectedItems().count()) {
        foreach(QGraphicsItem *item, d->scene->selectedItems()) {
            if (dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item)) { 
                node->setDirty(true);
                d->stack.push(node);
            }
        }
    } else {
        foreach(dtkComposerNode *node, d->scene->startNodes()) {
            node->setDirty(true);
            d->stack.push(node);
        }
    }

    qDebug() << DTK_PRETTY_FUNCTION << d->stack;

    d->start();
}

void dtkComposerEvaluator::stop(void)
{

}

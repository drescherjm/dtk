/* dtkComposerEvaluator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Oct 24 12:57:38 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 16:53:12 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 327
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
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeLoopDataComposite.h"
#include "dtkComposerNodeLoopFor.h"
#include "dtkComposerNodeLoopWhile.h"
#include "dtkComposerNodeLoopWhile_p.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerScene.h"

#include <dtkCore/dtkGlobal.h>

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// Helper definitions
// /////////////////////////////////////////////////////////////////

#define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate - evaluation
// /////////////////////////////////////////////////////////////////

void dtkComposerEvaluatorPrivate::run(void)
{
    emit evaluationStarted();

    while(!this->stack.isEmpty()) {

        dtkComposerNode *node = this->stack.pop();

        if(dtkComposerNodeCase *n = qobject_cast<dtkComposerNodeCase *>(node)) {
            if(!this->evaluate(n))
                this->stack.push(n);
        } else if(dtkComposerNodeConditional *n = qobject_cast<dtkComposerNodeConditional *>(node)) {
            if(!this->evaluate(n))
                this->stack.push(n);
        } else if(dtkComposerNodeLoopDataComposite *n = qobject_cast<dtkComposerNodeLoopDataComposite *>(node)) {
            if(!this->evaluate(n))
                this->stack.push(n);
        } else if(dtkComposerNodeLoopFor *n = qobject_cast<dtkComposerNodeLoopFor *>(node)) {
            if(!this->evaluate(n))
                this->stack.push(n);
        } else if(dtkComposerNodeLoopWhile *n = qobject_cast<dtkComposerNodeLoopWhile *>(node)) {
            if(!this->evaluate(n))
                this->stack.push(n);
        } else {
            if(!this->evaluate(node))
                this->stack.push(node);
        }
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
            
            if (property->edge()->source()->node()->dirty())
                return true;

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

        if (node->dirtyUpstreamNodes())
            return true;

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
        
        // -- Running logics
        
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_RED  << "Running node" << node->title() << "'s logics" << DTK_NO_COLOR;
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

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_BLUE << DTK_PRETTY_FUNCTION << "Forward done" << DTK_NO_COLOR;
#endif

        foreach(dtkComposerEdge *o_route, node->outputRoutes())
            if (o_route->source()->blockedFrom() == node->currentBlock()->title())
                o_route->destination()->node()->update();
    }

    return true;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate - evaluating if node
// /////////////////////////////////////////////////////////////////

bool dtkComposerEvaluatorPrivate::evaluate(dtkComposerNodeConditional *node)
{
    qDebug() << DTK_PRETTY_FUNCTION << node;

    return true;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate - evaluating loop on composite node
// /////////////////////////////////////////////////////////////////

bool dtkComposerEvaluatorPrivate::evaluate(dtkComposerNodeLoopDataComposite *node)
{
    qDebug() << DTK_PRETTY_FUNCTION << node;

    return true;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate - evaluating for node
// /////////////////////////////////////////////////////////////////

bool dtkComposerEvaluatorPrivate::evaluate(dtkComposerNodeLoopFor *node)
{
    qDebug() << DTK_PRETTY_FUNCTION << node;

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
        
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_BLUE << DTK_PRETTY_FUNCTION << "Forward is about to be done" << DTK_NO_COLOR;
#endif
        
        foreach(dtkComposerEdge *o_route, node->outputRoutes())
            o_route->destination()->node()->update();
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

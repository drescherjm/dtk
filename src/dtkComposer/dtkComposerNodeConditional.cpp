/* dtkComposerNodeConditional.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:03:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Oct 26 16:36:13 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 84
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerEvaluator_p.h"
#include "dtkComposerNodeConditional.h"
#include "dtkComposerNodeConditional_p.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeLoop.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// #define DTK_DEBUG_COMPOSER_INTERACTION 1
// #define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeConditional implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeConditional::dtkComposerNodeConditional(dtkComposerNode *parent) : dtkComposerNodeControl(parent), d(new dtkComposerNodeConditionalPrivate)
{
    d->block_then = this->addBlock("then");
    d->block_then->setInteractive(false);

    d->block_else = this->addBlock("else");
    d->block_else->setInteractive(false);

    this->setColor(QColor("#aa7845"));
    this->setTitle("Conditional");
    this->setType("dtkComposerConditional");
}

dtkComposerNodeConditional::~dtkComposerNodeConditional(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeConditional::layout(void)
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
        foreach(dtkComposerNodeProperty *property, block->inputProperties()) {

            property->setRect(QRectF(block->mapRectToParent(block->rect()).left() + node_radius,
                                     block->mapRectToParent(block->rect()).top()  + node_radius * (4*j + 1),
                                     2 * node_radius,
                                     2 * node_radius ));

            j++;
        }
        j = 0;
        foreach(dtkComposerNodeProperty *property, block->outputProperties()) {

            property->setRect(QRectF(block->mapRectToParent(block->rect()).right() - node_radius * 3,
                                     block->mapRectToParent(block->rect()).top()   + node_radius * (4*j + 1),
                                     2 * node_radius,
                                     2 * node_radius ));

            j++;
        }
    }     
}

//! Node delegates its own evaluation to the evaluator according to
//! Visitor Design Pattern.
/*! 
 * 
 */
bool dtkComposerNodeConditional::evaluate(dtkComposerEvaluatorPrivate *evaluator)
{
    return evaluator->evaluate(this);
}

// void dtkComposerNodeConditional::update(void)
// {
// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_PRETTY_FUNCTION << this;
// #endif
    
//     // -- If update is invoked while node is running, update is not necessary.
    
//     if (this->isRunning()) {

//         return;
    
//     } else {

//          // -- Check that node is ready (ie dirty)

//         if (!this->dirty())
//             return;

//         // -- Check dirty input value

//         if (this->dirtyInputValue())
//             return;

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Dirty input value OK" << DTK_NO_COLOR;
// #endif

//         // -- Block selection

//         if(this->condition())
//             this->setCurrentBlock(d->block_then);
//         else
//             this->setCurrentBlock(d->block_else);

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Selected block is" << this->currentBlock()->title() << DTK_NO_COLOR;
// #endif

//         // -- Check dirty inputs

//         if (this->dirtyUpstreamNodes())
//             return;

//         // -- Mark dirty outputs

//         this->markDirtyDownstreamNodes();

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "All output nodes are set to dirty" << DTK_NO_COLOR;
// #endif

//         // -- Clean active input routes

//         this->cleanInputActiveRoutes();

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Input active routes cleaned" << DTK_NO_COLOR;
// #endif

//         // -- Pull

//         foreach(dtkComposerEdge *i_route, this->inputRoutes())
//             if (i_route->destination()->blockedFrom() == this->currentBlock()->title())
//                 this->pull(i_route, i_route->destination());

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Pull done" << DTK_NO_COLOR;
// #endif

//         // -- Node is now ready to run

//         this->setRunning(true);
        
//         // -- Running logics

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//     qDebug() << DTK_COLOR_BG_RED  << "Running node" << this->title() << "'s logics" << DTK_NO_COLOR;
// #endif

//         this->run();

//         // -- Clean active output routes

//         this->cleanOutputActiveRoutes();

// #if defined(DTK_DEBUG_COMPOSER_EVALUATION)
//         qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Output active routes cleaned" << DTK_NO_COLOR;
// #endif

//         // -- Push

//         foreach(dtkComposerEdge *o_route, this->outputRoutes())
//             if (o_route->source()->blockedFrom() == this->currentBlock()->title())
//                 this->push(o_route, o_route->source());

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

//         foreach(dtkComposerEdge *o_route, this->outputRoutes())
//             if (o_route->source()->blockedFrom() == this->currentBlock()->title())
//                 o_route->destination()->node()->update();

//     }
// }

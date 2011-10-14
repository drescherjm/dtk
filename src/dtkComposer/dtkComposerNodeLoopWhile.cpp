/* dtkComposerNodeLoopWhile.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed May  4 08:51:21 2011 (+0200)
 * Version: $Id$
 * Last-Updated: ven. oct. 14 23:30:02 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 45
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeLoopWhile.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// #define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoopPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLoopWhilePrivate
{
public:
    dtkComposerNodeControlBlock *block_cond;
    dtkComposerNodeControlBlock *block_loop;

    dtkComposerNode *node_cond;
    dtkComposerNodeProperty *prop_cond;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoop implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLoopWhile::dtkComposerNodeLoopWhile(dtkComposerNode *parent) : dtkComposerNodeLoop(parent), d(new dtkComposerNodeLoopWhilePrivate)
{
    d->block_cond = this->addBlock("condition");
    d->block_cond->setInteractive(false);
    d->block_cond->setHeightRatio(0.95);
    this->addOutputProperty(d->block_cond->addOutputProperty("condition", this));

    d->block_loop = this->addBlock("loop");
    d->block_loop->setInteractive(false);
    d->block_loop->setHeightRatio(1.05);

    this->disableInputProperty();
    this->setColor(QColor("#30DC7B"));
    this->setTitle("While Loop");
    this->setType("dtkComposerLoopWhile");

    d->node_cond = NULL;
    d->prop_cond = NULL;
}

dtkComposerNodeLoopWhile::~dtkComposerNodeLoopWhile(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeLoopWhile::layout(void)
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

        j = 1;
        foreach(dtkComposerNodeProperty *property, block->inputProperties()) {

            property->setRect(QRectF(block->mapRectToParent(block->rect()).left() + node_radius,
                                     block->mapRectToParent(block->rect()).top()  + node_radius * (4*j + 1),
                                     2 * node_radius,
                                     2 * node_radius ));
            
            if (property->type() == dtkComposerNodeProperty::Output)
                property->mirror();
            
            j++;

        }
        
        if (block == d->block_cond)
            j = 0;
        else
            j = 1;
        foreach(dtkComposerNodeProperty *property, block->outputProperties()) {
            
            property->setRect(QRectF(block->mapRectToParent(block->rect()).right() - node_radius * 3,
                                     block->mapRectToParent(block->rect()).top()   + node_radius * (4*j + 1),
                                     2 * node_radius,
                                     2 * node_radius ));
            
            if (property->name() == "condition") {
                property->mirror();
                j++;
            }
            
            j++;

        }
    }     
}

void dtkComposerNodeLoopWhile::update(void)
{
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    
    // -- If update is invoked while node is running, update is not necessary.
    
    if (this->isRunning()) {
        
        return;
        
    } else {
        
        // -- Check that node is ready (ie not dirty)
        
        if (!this->dirty())
            return;
        
        // -- Check dirty inputs
        
        if (this->dtkComposerNode::dirtyUpstreamNodes())
            return;
        
        // -- Mark dirty outputs
        
        this->dtkComposerNode::markDirtyDownstreamNodes();
        
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "All output nodes are set to dirty" << DTK_NO_COLOR;
#endif
        
        // -- Clean active input routes
        
        this->cleanInputActiveRoutes();
        
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Input active routes cleaned" << DTK_NO_COLOR;
#endif
        
        // -- Pull
        
        foreach(dtkComposerEdge *i_route, this->inputRoutes())
            this->pull(i_route, i_route->destination());
        
        foreach(dtkComposerEdge *o_route, this->outputRelayRoutes()) {
            if (o_route->destination()->blockedFrom() == d->block_cond->title()) {
                if (o_route->destination()->name() == "condition") {
                    d->node_cond = o_route->source()->node();
                    d->prop_cond = o_route->source();
                }
            }
        }

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Pull done" << DTK_NO_COLOR;
#endif

        // -- Node is now ready to run

        this->setRunning(true);

        // -- First of all, condition of loop evaluation is evaluated from conditional block.

        this->setCurrentBlock(d->block_cond);
        this->run();

        // -- Loop evaluation is performed while condition is fullfilled

        while(d->node_cond->value(d->prop_cond).toBool()) {

            // -- Workflow of loop block is evaluated

            this->setCurrentBlock(d->block_loop);
            this->run();

            // -- Loop variables, if present, are updated.

            this->updatePassThroughVariables();

            // -- Loop condition is re-calculated from condition block.

            this->setCurrentBlock(d->block_cond);
            this->run();

        }

        // -- Clean active output routes

        this->cleanOutputActiveRoutes();

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Output active routes cleaned" << DTK_NO_COLOR;
#endif

        // -- Push

        foreach(dtkComposerEdge *o_route, this->outputRoutes())
            this->push(o_route, o_route->source());

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Push done" << DTK_NO_COLOR;
#endif

        // -- Node is now clean and is no more running

        this->setDirty(false);
        this->setRunning(false);

        // -- Forward to downstream nodes
        
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_BLUE << DTK_PRETTY_FUNCTION << "Forward is about to be done" << DTK_NO_COLOR;
#endif
        
        foreach(dtkComposerEdge *o_route, this->outputRoutes())
            o_route->destination()->node()->update();
            
    }
}

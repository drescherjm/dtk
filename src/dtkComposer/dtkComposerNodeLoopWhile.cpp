/* dtkComposerNodeLoopWhile.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed May  4 08:51:21 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Nov  9 16:14:56 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 68
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
#include "dtkComposerNodeLoopWhile.h"
#include "dtkComposerNodeLoopWhile_p.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoopPrivate implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlBlock *dtkComposerNodeLoopWhilePrivate::createBlock(const QString& title, dtkComposerNodeLoopWhile *parent)
{
    dtkComposerNodeControlBlock *block = new dtkComposerNodeControlBlock(title, parent);
    parent->appendBlock(block);
    block->setInteractive(false);

    if (title == "condition") {

        block->setHeightRatio(0.95);
        parent->appendBlockRightProperty("condition", dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Single, block);

    } else if (title == "loop") {

        block->setHeightRatio(1.05);

    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoop implementation
// /////////////////////////////////////////////////////////////////

//! Constructs a while loop control node.
/*! 
 *  
 */
dtkComposerNodeLoopWhile::dtkComposerNodeLoopWhile(dtkComposerNode *parent) : dtkComposerNodeLoop(parent), d(new dtkComposerNodeLoopWhilePrivate)
{
    d->createBlock("condition", this);
    d->createBlock("loop", this);

    this->disableInputProperty();
    this->setColor(QColor("#30DC7B"));
    this->setTitle("While Loop");
    this->setType("dtkComposerLoopWhile");

    d->node_cond = NULL;
    d->prop_cond = NULL;
}

//! Destroys while loop control node.
/*! 
 *  
 */
dtkComposerNodeLoopWhile::~dtkComposerNodeLoopWhile(void)
{
    delete d;

    d = NULL;
}

//! Defines the layout of the while loop node.
/*! 
 *  Reimplemented from dtkComposerNodeControl.
 */
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
        foreach(dtkComposerNodeProperty *property, block->leftProperties()) {

            property->setRect(QRectF(block->mapRectToParent(block->rect()).left() + node_radius,
                                     block->mapRectToParent(block->rect()).top()  + node_radius * (4*j + 1),
                                     2 * node_radius,
                                     2 * node_radius ));
            
            if (property->type() == dtkComposerNodeProperty::Output)
                property->mirror();
            
            j++;

        }
        
        if (block == this->blocks().at(0))
            j = 0;
        else
            j = 1;
        foreach(dtkComposerNodeProperty *property, block->rightProperties()) {
            
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

//! Node delegates its own evaluation to the evaluator according to
//! Visitor Design Pattern.
/*! 
 * 
 */
bool dtkComposerNodeLoopWhile::evaluate(dtkComposerEvaluatorPrivate *evaluator)
{
    return evaluator->evaluate(this);
}

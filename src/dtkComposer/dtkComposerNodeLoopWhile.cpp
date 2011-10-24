/* dtkComposerNodeLoopWhile.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed May  4 08:51:21 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 16:29:09 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 53
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
#include "dtkComposerNodeLoopWhile_p.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

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

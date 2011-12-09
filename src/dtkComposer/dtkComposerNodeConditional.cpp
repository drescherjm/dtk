/* dtkComposerNodeConditional.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:03:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  7 15:53:01 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 127
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
#include "dtkComposerNodeTransmitter.h"
#include "dtkComposerRoute.h"

#include <dtkCore/dtkGlobal>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeConditionalPrivate implementation
// /////////////////////////////////////////////////////////////////

//! Creates a block defined by its \a title inside the conditional
//! node \a parent.
/*! 
 *  
 */
dtkComposerNodeControlBlock *dtkComposerNodeConditionalPrivate::createBlock(const QString& title, dtkComposerNodeConditional *parent)
{
    dtkComposerNodeControlBlock *block = new dtkComposerNodeControlBlock(title, parent);
    block->setInteractive(false);
    parent->appendBlock(block);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeConditional implementation
// /////////////////////////////////////////////////////////////////

//! Constructs a control conditional node.
/*! 
 *  
 */
dtkComposerNodeConditional::dtkComposerNodeConditional(dtkComposerNode *parent) : dtkComposerNodeControl(parent), d(new dtkComposerNodeConditionalPrivate)
{
    d->createBlock("then", this);
    d->createBlock("else", this);

    this->setColor(QColor("#aa7845"));
    this->setTitle("Conditional");
    this->setType("dtkComposerConditional");
}

//! Destroys control conditional node.
/*! 
 *  
 */
dtkComposerNodeConditional::~dtkComposerNodeConditional(void)
{
    delete d;

    d = NULL;
}

//! Defines the layout of the control conditional node.
/*! 
 *  Reimplemented from dtkComposerNodeControl
 */
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

        j = 2;
        foreach(dtkComposerNodeProperty *property, block->leftProperties()) {

            property->setRect(QRectF(block->mapRectToParent(block->rect()).left() + node_radius,
                                     block->mapRectToParent(block->rect()).top()  + node_radius * (4*j + 1),
                                     2 * node_radius,
                                     2 * node_radius ));

            j++;
        }
        j = 2;
        foreach(dtkComposerNodeProperty *property, block->rightProperties()) {

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



bool dtkComposerNodeConditional::onLeftRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *destination)
{
    if (destination == this->inputProperty()) {

        if(!(dynamic_cast<dtkComposerNodeTransmitter<bool> *>(route->source()->node()->emitter(route->source()))))
            return false;
    
        d->receivers.insert(route, static_cast<dtkComposerNodeTransmitter<bool> *>(route->source()->node()->emitter(route->source())));

        return true;

    }

    if (this->g->leftProperties().contains(destination)) {

        

    } else if (this->g->rightProperties().contains(destination)) {



    }

    return false;
}

bool dtkComposerNodeConditional::onRightRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    if (this->g->leftProperties().contains(property)) {

        this->l->appendRightRelayRoute(route);

    }

    return true;
}

void dtkComposerNodeConditional::appendSourceRoutes(dtkComposerRoute *route)
{
    if (route->destination() == this->inputProperty())
        this->l->appendLeftRoute(route);
}

void dtkComposerNodeConditional::appendDestinationRoutes(dtkComposerRoute *route)
{
    this->l->appendRightRoute(route);
}

void dtkComposerNodeConditional::appendSourceNodes(dtkComposerEdge *route)
{
    if (route->destination() == this->inputProperty())
        this->l->appendLeftNode(route->source()->node());
}

void dtkComposerNodeConditional::appendDestinationNodes(dtkComposerEdge *route)
{
    this->l->appendRightNode(route->destination()->node());
}

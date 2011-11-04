/* dtkComposerNodeLoopDataComposite.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Oct 12 16:02:18 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Nov  4 15:48:24 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 199
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeLoopDataComposite.h"
#include "dtkComposerNodeLoopDataComposite_p.h"

#include <dtkComposer/dtkComposerEdge>
#include <dtkComposer/dtkComposerEvaluator_p.h>
#include <dtkComposer/dtkComposerNode>
#include <dtkComposer/dtkComposerNodeControlBlock>
#include <dtkComposer/dtkComposerNodeNumber>
#include <dtkComposer/dtkComposerNodeProperty>

#include <dtkCore/dtkAbstractData>
#include <dtkCore/dtkAbstractDataComposite>
#include <dtkCore/dtkAbstractProcess>
#include <dtkCore/dtkGlobal>
#include <dtkCore/dtkLog>

// #define DTK_DEBUG_COMPOSER_INTERACTION 1
// #define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoopDataCompositePrivate declaration
// /////////////////////////////////////////////////////////////////


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoopDataComposite implementation
// /////////////////////////////////////////////////////////////////

//! 
/*! 
 * 
 */
dtkComposerNodeLoopDataComposite::dtkComposerNodeLoopDataComposite(dtkComposerNode *parent) : dtkComposerNodeLoop(parent), d(new dtkComposerNodeLoopDataCompositePrivate)
{
    d->block_loop = this->addBlock("loop");
    d->block_loop->setInteractive(false);
    d->block_loop->setHeightRatio(1);

    this->g->appendLeftProperty(d->block_loop->appendLeftProperty("from", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, dtkComposerNodeProperty::None, this));
    this->g->appendLeftProperty(d->block_loop->appendLeftProperty("to", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, dtkComposerNodeProperty::None, this));
    this->g->appendLeftProperty(d->block_loop->appendLeftProperty("step", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, dtkComposerNodeProperty::None, this));
    this->g->appendLeftProperty(d->block_loop->appendLeftProperty("item", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, dtkComposerNodeProperty::AsLoopInput, this));
    this->g->appendLeftProperty(d->block_loop->appendLeftProperty("index", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, dtkComposerNodeProperty::AsLoopInput, this));

    this->setCurrentBlock(d->block_loop);

    this->setColor(QColor("#2ABFFF"));
    this->setInputPropertyName("composite");
    this->setTitle("Composite Data Loop");
    this->setType("dtkComposerLoopDataComposite");

    d->from_default = 0;
    d->to_default = 0;

    d->from = -2;
    d->to = -1;
    d->step = -1;

    d->index = 0;

    d->item = NULL;
    d->composite = NULL;

    d->valid_input_composite = false;
}

//! 
/*! 
 * 
 */
dtkComposerNodeLoopDataComposite::~dtkComposerNodeLoopDataComposite(void)
{
    delete d;

    d = NULL;
}

//! 
/*! 
 * 
 */
void dtkComposerNodeLoopDataComposite::layout(void)
{
    dtkComposerNodeControl::layout();

    QRectF  node_rect = this->boundingRect();
    qreal node_radius = this->nodeRadius();

    int j;
    qreal offset = 23;

    dtkComposerNodeControlBlock *block = this->blocks().at(0);

    block->setRect(QRectF(node_rect.x(),
                          node_rect.y() + offset,
                          node_rect.width(),
                          block->height()));

    j = 0;
    foreach(dtkComposerNodeProperty *property, block->leftProperties()) {

        property->setRect(QRectF(block->mapRectToParent(block->rect()).left() + node_radius,
                                 block->mapRectToParent(block->rect()).top()  + node_radius * (4*j + 1),
                                 2 * node_radius,
                                 2 * node_radius ));

        if (property->name() == "step") {
            j++;
        } else if (property->name() == "item") {
            property->mirror();
        } else if (property->name() == "index") {
            property->mirror();
            j++;
        }

        j++;
    }
    j = 5;
    foreach(dtkComposerNodeProperty *property, block->rightProperties()) {

        property->setRect(QRectF(block->mapRectToParent(block->rect()).right() - node_radius * 3,
                                 block->mapRectToParent(block->rect()).top()   + node_radius * (4*j + 1),
                                 2 * node_radius,
                                 2 * node_radius ));
        
        j++;
    }
}

//! Node delegates its own evaluation to the evaluator according to
//! Visitor Design Pattern.
/*! 
 * 
 */
bool dtkComposerNodeLoopDataComposite::evaluate(dtkComposerEvaluatorPrivate *evaluator)
{
    return evaluator->evaluate(this);
}
 
//! 
/*! 
 * 
 */   
QVariant dtkComposerNodeLoopDataComposite::value(dtkComposerNodeProperty *property)
{
    QVariant value;
    if (property->name() == "index")
        value = QVariant(d->index);

    return value;
}

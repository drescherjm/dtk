/* dtkComposerNodeLoopDataComposite.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Oct 12 16:02:18 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 10:40:28 2012 (+0100)
 *           By: tkloczko
 *     Update #: 212
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeLoopDataComposite.h"
#include "dtkComposerNodeLoopDataComposite_p.h"

#include <dtkComposerOld/dtkComposerEdge>
#include <dtkComposerOld/dtkComposerEvaluator_p.h>
#include <dtkComposerOld/dtkComposerNode>
#include <dtkComposerOld/dtkComposerNodeControlBlock>
#include <dtkComposerOld/dtkComposerNodeNumber>
#include <dtkComposerOld/dtkComposerNodeProperty>

#include <dtkCore/dtkAbstractData>
#include <dtkCore/dtkAbstractDataComposite>
#include <dtkCore/dtkAbstractProcess>
#include <dtkCore/dtkGlobal>
#include <dtkCore/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoopDataCompositePrivate implementation
// /////////////////////////////////////////////////////////////////

//! Creates a block defined by its \a title inside the data composite
//! loop node \a parent.
/*! 
 *  
 */
dtkComposerNodeControlBlock *dtkComposerNodeLoopDataCompositePrivate::createBlock(const QString& title, dtkComposerNodeLoopDataComposite *parent)
{
    dtkComposerNodeControlBlock *block = new dtkComposerNodeControlBlock(title, parent);
    parent->appendBlock(block);

    block->setInteractive(false);
    block->setHeightRatio(1);

    parent->appendBlockLeftProperty("from", dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Single, block);
    parent->appendBlockLeftProperty("to", dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Single, block);
    parent->appendBlockLeftProperty("step", dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Single, block);
    parent->appendBlockLeftProperty("item", dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, block);
    parent->appendBlockLeftProperty("index", dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, block);

}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoopDataComposite implementation
// /////////////////////////////////////////////////////////////////

//! Constructs a dtkComposerNodeLoopDataComposite.
/*! 
 * 
 */
dtkComposerNodeLoopDataComposite::dtkComposerNodeLoopDataComposite(dtkComposerNode *parent) : dtkComposerNodeLoop(parent), d(new dtkComposerNodeLoopDataCompositePrivate)
{
    d->createBlock("loop", this);

    this->setCurrentBlock(this->blocks().at(0));

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

//! Destroys dtkComposerNodeLoopDataComposite.
/*! 
 * 
 */
dtkComposerNodeLoopDataComposite::~dtkComposerNodeLoopDataComposite(void)
{
    delete d;

    d = NULL;
}

//! Defines the layout of the control DataComposite loop node.
/*! 
 *  Reimplemented from dtkComposerNodeControl.
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

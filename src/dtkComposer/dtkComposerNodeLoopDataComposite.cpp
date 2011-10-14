/* dtkComposerNodeLoopDataComposite.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Oct 12 16:02:18 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Oct 14 12:11:33 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 131
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeLoopDataComposite.h"

#include <dtkComposer/dtkComposerEdge>
#include <dtkComposer/dtkComposerNode>
#include <dtkComposer/dtkComposerNodeControlBlock>
#include <dtkComposer/dtkComposerNodeNumber>
#include <dtkComposer/dtkComposerNodeProperty>

#include <dtkCore/dtkAbstractData>
#include <dtkCore/dtkAbstractDataComposite>
#include <dtkCore/dtkAbstractProcess>
#include <dtkCore/dtkGlobal>
#include <dtkCore/dtkLog>

#define DTK_DEBUG_COMPOSER_INTERACTION 1
#define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoopDataCompositePrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLoopDataCompositePrivate
{
public:
    dtkComposerNodeControlBlock *block_loop;

public:
    dtkxarch_int from_default;
    dtkxarch_int to_default;
    dtkxarch_int step_default;

    dtkxarch_int from;
    dtkxarch_int to;
    dtkxarch_int step;
    dtkxarch_int index;

    dtkAbstractData *item;

    dtkAbstractDataComposite *composite;

    bool valid_input_composite;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoopDataComposite implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLoopDataComposite::dtkComposerNodeLoopDataComposite(dtkComposerNode *parent) : dtkComposerNodeLoop(parent), d(new dtkComposerNodeLoopDataCompositePrivate)
{
    d->block_loop = this->addBlock("loop");
    d->block_loop->setInteractive(false);
    d->block_loop->setHeightRatio(1);
    this->addInputProperty(d->block_loop->addInputProperty("from", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, dtkComposerNodeProperty::None, this));
    this->addInputProperty(d->block_loop->addInputProperty("to", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, dtkComposerNodeProperty::None, this));
    this->addInputProperty(d->block_loop->addInputProperty("step", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, dtkComposerNodeProperty::None, this));
    this->addInputProperty(d->block_loop->addInputProperty("item", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, dtkComposerNodeProperty::AsLoopInput, this));

    this->setColor(QColor("#2ABFFF"));
    this->setInputPropertyName("composite");
    this->setTitle("Composite Data Loop");
    this->setType("dtkComposerLoopDataComposite");

    d->from_default = 0;
    d->to_default = 0;
    d->step_default = 1;

    d->from = -1;
    d->to = -1;
    d->step = -1;

    d->index = 0;

    d->item = NULL;
    d->composite = NULL;

    d->valid_input_composite = false;
}

dtkComposerNodeLoopDataComposite::~dtkComposerNodeLoopDataComposite(void)
{
    delete d;

    d = NULL;
}

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
    foreach(dtkComposerNodeProperty *property, block->inputProperties()) {

        property->setRect(QRectF(block->mapRectToParent(block->rect()).left() + node_radius,
                                 block->mapRectToParent(block->rect()).top()  + node_radius * (4*j + 1),
                                 2 * node_radius,
                                 2 * node_radius ));

        if (property->name() == "item") {
            property->mirror();
            j++;
        }

        j++;
    }
    j = 5;
    foreach(dtkComposerNodeProperty *property, block->outputProperties()) {

        property->setRect(QRectF(block->mapRectToParent(block->rect()).right() - node_radius * 3,
                                 block->mapRectToParent(block->rect()).top()   + node_radius * (4*j + 1),
                                 2 * node_radius,
                                 2 * node_radius ));
        
        j++;
    }
}

void dtkComposerNodeLoopDataComposite::update(void)
{
    
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if (this->isRunning()) {

        return;
    
    } else {

        if (!this->dirty())
            return;

        // -- Check dirty input value

        if (this->dirtyInputValue())
            return;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Dirty input value OK" << DTK_NO_COLOR;
#endif

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

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Pull done" << DTK_NO_COLOR;
#endif

        // -- Set input composite and loop options

        foreach(dtkComposerEdge *i_route, this->inputActiveRoutes()) {
            if (i_route->destination() == this->inputProperty()) {
        
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

                    d->composite = qobject_cast<dtkAbstractDataComposite *>(data);
                    if (!d->composite) {
                        dtkDebug() << DTK_PRETTY_FUNCTION << "input data is not of dtkAbstractDataComposite* type.";
                        return;
                    }
                    if (d->composite->count())
                        this->setObject((*d->composite)[0]);

                    d->to_default = d->composite->count()-1;
                    
                    d->valid_input_composite = true;

                } else {

                    dtkDebug() << DTK_PRETTY_FUNCTION << "input data is not defined";
                    return;

                }

            } else if (i_route->destination()->name() == "from") {

                d->from = (dtkxarch_int)(i_route->source()->node()->value(i_route->source()).toLongLong());   

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "from value =" << d->from << DTK_NO_COLOR;
#endif

            } else if (i_route->destination()->name() == "to") {

                d->to = (dtkxarch_int)(i_route->source()->node()->value(i_route->source()).toLongLong()); 

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "to value =" << d->to << DTK_NO_COLOR;
#endif

            } else if (i_route->destination()->name() == "step") {

                d->step = (dtkxarch_int)(i_route->source()->node()->value(i_route->source()).toLongLong());
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "step value =" << d->step << DTK_NO_COLOR;
#endif

            }

            qDebug() << i_route;

        }
 
        if (!d->valid_input_composite) {
            dtkDebug() << DTK_PRETTY_FUNCTION << " input composite property is not connected.";
            return;   
        }

        if ((d->from > d->to) && (d->from > d->to_default))
            d->from = d->to_default;
        else if (d->from < 0)
            d->from = d->from_default;
        else if (d->to < d->from && d->to < 0)
            d->to = d->from_default;
        else if (d->to > d->to_default)
            d->to = d->to_default;

        if (d->step < 0 && (d->from < d->to))
            d->step = d->step_default;

        d->index = d->from;
        
        // -- Running logics of conditional block
        
        this->setRunning(true);

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_RED  << "Loop initialization done" << DTK_NO_COLOR;
#endif

        while(d->index <= d->to) {

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
            qDebug() << DTK_COLOR_BG_RED  << "Loop is running, index = " << d->index << DTK_NO_COLOR;
#endif
            
            d->item = (*d->composite)[d->index];            
            this->run();
            this->updatePassThroughVariables();
            d->index += d->step;
            
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

        // -- Forward
            
        this->setDirty(false);
        this->setRunning(false);
            
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_BLUE << DTK_PRETTY_FUNCTION << "Forward done" << DTK_NO_COLOR;
#endif

        foreach(dtkComposerEdge *o_route, this->outputRoutes())
            o_route->destination()->node()->update();
            
    }
}

void dtkComposerNodeLoopDataComposite::pull(dtkComposerEdge *i_route, dtkComposerNodeProperty *property)
{
    if (property->name() == "from" || property->name() == "to" || property->name() == "step")
        this->addInputActiveRoute(i_route);

    dtkComposerNodeLoop::pull(i_route, property);
}
    
QVariant dtkComposerNodeLoopDataComposite::value(dtkComposerNodeProperty *property)
{
    QVariant value;
    // if (property == this->inputProperty())
    //     value = d->loop_variable;
    // else
    //     value = dtkComposerNodeLoop::value(property);

    return value;
}

/* dtkComposerNodeConditional.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:03:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 21 12:22:10 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 51
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeConditional.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeLoop.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// #define DTK_DEBUG_COMPOSER_INTERACTION 1
#define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeConditionalPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeConditionalPrivate
{
public:
    dtkComposerNodeControlBlock *block_then;
    dtkComposerNodeControlBlock *block_else;
    dtkComposerNodeControlBlock *selected_block;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeConditional implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeConditional::dtkComposerNodeConditional(dtkComposerNode *parent) : dtkComposerNodeControl(parent), d(new dtkComposerNodeConditionalPrivate)
{
    d->block_then = this->addBlock("then");
    d->block_then->setInteractive(true);

    d->block_else = this->addBlock("else");
    d->block_else->setInteractive(true);

    this->setColor(QColor("#aa7845"));
    this->setTitle("Conditional");
    this->setType("dtkComposerConditional");

    d->selected_block = NULL;
}

dtkComposerNodeConditional::~dtkComposerNodeConditional(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeConditional::layout(void)
{
    dtkComposerNodeControl::layout();

    int i = 0;
    int j;
    
    foreach(dtkComposerNodeControlBlock *block, this->blocks()) {

        block->setRect(QRectF(this->boundingRect().x(),
                              this->boundingRect().y() + 23 + i * ((this->boundingRect().height() - 46) / this->blocks().count()),
                              this->boundingRect().width(),
                              (this->boundingRect().height() - 46) / this->blocks().count()));

        j = 0;
        foreach(dtkComposerNodeProperty *property, block->inputProperties()) {

            property->setRect(QRectF(block->rect().left() + this->nodeRadius(),
                                     block->rect().top()  + this->nodeRadius() * (4*j + 1),
                                     2 * this->nodeRadius(),
                                     2 * this->nodeRadius() ));

            j++;
        }
        j = 0;
        foreach(dtkComposerNodeProperty *property, block->outputProperties()) {

            property->setRect(QRectF(block->rect().right() - this->nodeRadius() * 3,
                                     block->rect().top()   + this->nodeRadius() * (4*j + 1),
                                     2 * this->nodeRadius(),
                                     2 * this->nodeRadius() ));

            j++;
        }

        i++;
    }     
}

void dtkComposerNodeConditional::update(void)
{
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_PRETTY_FUNCTION << this;
#endif

    if (!this->isRunning()) {

        if (!this->dirty())
            return;

        // -- Check dirty input value
        
        if (this->inputProperty()->edge()->source()->node()->dirty())
            return;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Dirty input value OK" << DTK_NO_COLOR;
#endif

        // -- Block selection

        if(this->condition())
            d->selected_block = d->block_then;
        else
            d->selected_block = d->block_else;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Selected block is" << d->selected_block->title() << DTK_NO_COLOR;
#endif

        // -- Check dirty inputs
 
        foreach(dtkComposerEdge *i_route, this->inputRoutes()) {
            if (i_route->destination()->blockedFrom() == d->selected_block->title()) {

// /////////////////////////////////////////////////////////////////
// TMP: Treating special case of loop control nodes
// /////////////////////////////////////////////////////////////////

                if(dtkComposerNodeLoop *loop = dynamic_cast<dtkComposerNodeLoop *>(i_route->source()->node())) {
                    if(this->isChildOf(loop)) {
                        if(loop->isPreRunning() || loop->isRunning() || loop->isPostRunning()) {
                            continue;
                        } else {
                            return;
                        }
                    } else {
                        if (i_route->source()->node()->dirty())
                            return;
                    }
                } else {
                
// /////////////////////////////////////////////////////////////////

                    if (i_route->source()->node()->dirty())
                        return;
                
// /////////////////////////////////////////////////////////////////
                }
            }
        }

        // -- Mark dirty outputs

        foreach(dtkComposerEdge *o_route, this->outputRoutes())
            if (o_route->source()->blockedFrom() == d->selected_block->title())
                o_route->destination()->node()->setDirty(true);

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "All output nodes are set to dirty" << DTK_NO_COLOR;
#endif

        // -- Clean active input routes

        foreach(dtkComposerEdge *active_route, this->inputActiveRoutes()) {
            foreach(dtkComposerEdge *i_route, active_route->destination()->node()->inputRoutes()) {
                if (i_route == active_route) {
                    active_route->destination()->node()->removeInputRoute(i_route);
                    break;
                }
            }
            this->removeInputActiveRoute(active_route);
            delete active_route;
            active_route = NULL;
        }

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Input active routes cleaned" << DTK_NO_COLOR;
#endif

        // -- Pull

        foreach(dtkComposerEdge *i_route, this->inputRoutes())
            if (i_route->destination()->blockedFrom() == d->selected_block->title())
                this->pull(i_route, i_route->destination());

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Pull done" << DTK_NO_COLOR;
#endif
        
        // -- Running logics

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_COLOR_BG_RED  << "Running node" << this->title() << "'s logics" << DTK_NO_COLOR;
#endif

        this->setRunning(true);
        this->run();

    } else {

        // -- Check Dirty end nodes
        
        foreach(dtkComposerEdge *o_route, this->outputRelayRoutes())
            if (o_route->destination()->blockedFrom() == d->selected_block->title())
                if (o_route->source()->node()->dirty())
                    return;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "All end block nodes have finished their work" << DTK_NO_COLOR;
#endif

        // -- Clean active output routes

        foreach(dtkComposerEdge *active_route, this->outputActiveRoutes()) {
            foreach(dtkComposerEdge *i_route, active_route->destination()->node()->inputRoutes()) {
                if (i_route == active_route) {
                    active_route->destination()->node()->removeInputRoute(i_route);
                    break;
                }
            }
            this->removeOutputActiveRoute(active_route);
            delete active_route;
            active_route = NULL;
        }

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Output active routes cleaned" << DTK_NO_COLOR;
#endif

        // -- Push

        foreach(dtkComposerEdge *o_route, this->outputRoutes())
            if (o_route->source()->blockedFrom() == d->selected_block->title())
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
            if (o_route->source()->blockedFrom() == d->selected_block->title())
                o_route->destination()->node()->update();

    }
}

void dtkComposerNodeConditional::pull(dtkComposerEdge *i_route, dtkComposerNodeProperty *property)
{
    foreach(dtkComposerEdge *relay_route, this->inputRelayRoutes()) {
        if (relay_route->source() == property) {
                
            dtkComposerEdge *route = new dtkComposerEdge;
            route->setSource(i_route->source());
            route->setDestination(relay_route->destination());
                
            relay_route->destination()->node()->addInputRoute(route);
            this->addInputActiveRoute(route);
        }
    }
}

void dtkComposerNodeConditional::run(void)
{
    foreach(dtkComposerNode *child, d->selected_block->nodes())
        child->setDirty(true);

    foreach(dtkComposerNode *child, d->selected_block->startNodes())
        child->update();
}

void dtkComposerNodeConditional::push(dtkComposerEdge *o_route, dtkComposerNodeProperty *property)
{
    foreach(dtkComposerEdge *relay_route, this->outputRelayRoutes()) {
        if (relay_route->destination() == o_route->source()) {
                
            dtkComposerEdge *route = new dtkComposerEdge;
            route->setSource(relay_route->source());
            route->setDestination(o_route->destination());
                
            o_route->destination()->node()->addInputRoute(route);
            this->addOutputActiveRoute(route);
        }
    }
}

/* dtkComposerNodeLoopFor.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:03:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 21 14:01:46 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 158
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeLoopFor.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// #define DTK_DEBUG_COMPOSER_INTERACTION 1
// #define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoopPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLoopForPrivate
{
public:
    dtkComposerNodeControlBlock *block_cond;
    dtkComposerNodeControlBlock *block_loop;
    dtkComposerNodeControlBlock *block_post;

    dtkComposerNode *node_cond;
    dtkComposerNode *node_post;

    dtkComposerNodeProperty *prop_cond;
    dtkComposerNodeProperty *prop_post;

public:
    QVariant loop_variable;
    QVariant loop_variable_old;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLoop implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLoopFor::dtkComposerNodeLoopFor(dtkComposerNode *parent) : dtkComposerNodeLoop(parent), d(new dtkComposerNodeLoopForPrivate)
{
    d->block_cond = this->addBlock("condition");
    d->block_cond->setInteractive(true);
    this->addInputProperty(d->block_cond->addInputProperty("variable", this));
    this->addOutputProperty(d->block_cond->addOutputProperty("condition", this));

    d->block_loop = this->addBlock("loop");
    d->block_loop->setInteractive(true);
    this->addInputProperty(d->block_loop->addInputProperty("variable", this));
    this->addOutputProperty(d->block_loop->addOutputProperty("variable", this));

    d->block_post = this->addBlock("post");
    d->block_post->setInteractive(true);
    this->addInputProperty(d->block_post->addInputProperty("variable", this));
    this->addOutputProperty(d->block_post->addOutputProperty("variable", this));

    this->setColor(QColor("#005b07"));
    this->setInputPropertyName("variable");
    this->setTitle("For Loop");
    this->setType("dtkComposerLoopFor");

    d->node_cond = NULL;
    d->node_post = NULL;

    d->prop_cond = NULL;
    d->prop_post = NULL;

    d->loop_variable = QVariant();
    d->loop_variable_old = QVariant();
}

dtkComposerNodeLoopFor::~dtkComposerNodeLoopFor(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeLoopFor::layout(void)
{
    dtkComposerNodeControl::layout();

    int i = 0;
    int j;

    qreal height;
    qreal total_height = 0.;
    
    foreach(dtkComposerNodeControlBlock *block, this->blocks()) {

        if (block == d->block_cond || block == d->block_post)
            height = 0.25 * (this->boundingRect().height() - 46);
        else
            height = 0.5 * (this->boundingRect().height() - 46);

        block->setRect(QRectF(this->boundingRect().x(),
                              this->boundingRect().y() + 23 + total_height,
                              this->boundingRect().width(),
                              height));
        
        total_height += height;

        j = 0;
        foreach(dtkComposerNodeProperty *property, block->inputProperties()) {

            property->setRect(QRectF(block->rect().left() + this->nodeRadius(),
                                     block->rect().top()  + this->nodeRadius() * (4*j + 1),
                                     2 * this->nodeRadius(),
                                     2 * this->nodeRadius() ));

            if (property->name() == "variable") {
                property->mirror();
                j++;
            }

            j++;
        }
        j = 0;
        foreach(dtkComposerNodeProperty *property, block->outputProperties()) {

            property->setRect(QRectF(block->rect().right() - this->nodeRadius() * 3,
                                     block->rect().top()   + this->nodeRadius() * (4*j + 1),
                                     2 * this->nodeRadius(),
                                     2 * this->nodeRadius() ));

            if (property->name() == "variable") {
                if (block->title() == "post")
                    property->mirror();
                j++;
            }

            if (property->name() == "condition") {
                if (block->title() == "condition")
                    property->mirror();
                j++;
            }

            j++;
        }

        i++;
    }     
}

void dtkComposerNodeLoopFor::update(void)
{
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_PRETTY_FUNCTION << this;
#endif
    
    if (!this->isPreRunning() && !this->isRunning() && !this->isPostRunning()) {

        if (!this->dirty())
            return;

        // -- Check dirty input value

        foreach(dtkComposerEdge *i_route, this->inputRoutes())
            if (i_route->destination() == this->inputProperty() && i_route->source()->node()->dirty())
                return;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Dirty input value OK" << DTK_NO_COLOR;
#endif

        // -- Retrieve input value

        d->loop_variable = dtkComposerNodeControl::value();

        if (!d->loop_variable.isValid())
            return;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_GREEN << DTK_PRETTY_FUNCTION << "Input value valid" << DTK_NO_COLOR;
#endif

        // -- Check dirty inputs

        foreach(dtkComposerEdge *i_route, this->inputRoutes()) {

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

        // -- Mark dirty outputs

        foreach(dtkComposerEdge *o_route, this->outputRoutes())
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
            this->pull(i_route, i_route->destination());

        foreach(dtkComposerEdge *o_route, this->outputRelayRoutes()) {
            if (o_route->destination()->blockedFrom() == d->block_cond->title()) {
                if (o_route->destination()->name() == "condition") {
                    d->node_cond = o_route->source()->node();
                    d->prop_cond = o_route->source();
                }
            } else if (o_route->destination()->blockedFrom() == d->block_post->title()) {
                if (o_route->destination()->name() == "variable") {
                    d->node_post = o_route->source()->node();
                    d->prop_post = o_route->source();
                }
            }
        }        

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Pull done" << DTK_NO_COLOR;
#endif
        
        // -- Running logics of conditional block
        
        this->setPreRunning(true);
        this->setCurrentBlock(d->block_cond);

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_RED  << "Running Condition block" << DTK_NO_COLOR;
#endif

        this->run();
        this->update();

    } else {
            
        if (!this->isRunning()) {

            // -- Check Dirty end nodes for conditional block
        
            foreach(dtkComposerEdge *o_route, this->outputRelayRoutes())
                if (o_route->destination()->blockedFrom() == this->currentBlock()->title())
                    if (o_route->source()->node()->dirty())
                        return;

            foreach(dtkComposerNode *node, this->currentBlock()->nodes())
                if(!node->outputEdges().count() && node->inputEdges().count() && node->dirty())
                    return;
        
            this->setLoopCondition(d->node_cond->value(d->prop_cond).toBool());
        
            if (this->loopConditon()) {

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                qDebug() << DTK_COLOR_BG_RED  << "Running Loop block" << DTK_NO_COLOR;
#endif

                this->setCurrentBlock(d->block_loop);
                this->setRunning(true);
                this->setPostRunning(false);
                this->run();
                this->update();

            } else {

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                qDebug() << DTK_COLOR_BG_RED  << "Condition is no more fulfilled" << DTK_NO_COLOR;
#endif

                d->loop_variable = d->loop_variable_old;

                this->setPreRunning(true);
                this->setRunning(true);
                this->setPostRunning(true);
                this->update();

            }

        } else if (!this->isPostRunning()) {
        
                foreach(dtkComposerEdge *o_route, this->outputRelayRoutes())
                    if (o_route->destination()->blockedFrom() == this->currentBlock()->title())
                        if (o_route->source()->node()->dirty())
                            return;

                foreach(dtkComposerNode *node, this->currentBlock()->nodes())
                    if(!node->outputEdges().count() && node->inputEdges().count() && node->dirty())
                        return;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                qDebug() << DTK_COLOR_BG_RED  << "Running Post block" << DTK_NO_COLOR;
#endif

                d->loop_variable_old = d->loop_variable;

                this->setCurrentBlock(d->block_post);
                this->setPostRunning(true);
                this->setPreRunning(false);
                this->run();
                this->update();

        } else if (!this->isPreRunning()) {
        
                foreach(dtkComposerEdge *o_route, this->outputRelayRoutes())
                    if (o_route->destination()->blockedFrom() == this->currentBlock()->title())
                        if (o_route->source()->node()->dirty())
                            return;

                foreach(dtkComposerNode *node, this->currentBlock()->nodes())
                    if(!node->outputEdges().count() && node->inputEdges().count() && node->dirty())
                        return;

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
                qDebug() << DTK_COLOR_BG_RED  << "Running Condition block" << DTK_NO_COLOR;
#endif

                d->loop_variable = d->node_post->value(d->prop_post);

                this->setCurrentBlock(d->block_cond);
                this->setPreRunning(true);
                this->setRunning(false);
                this->run();
                this->update();

        } else {

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
                this->push(o_route, o_route->source());

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
            qDebug() << DTK_COLOR_BG_YELLOW << DTK_PRETTY_FUNCTION << "Push done" << DTK_NO_COLOR;
#endif

            // -- Forward
            
            this->setDirty(false);
            this->setPreRunning(false);
            this->setRunning(false);
            this->setPostRunning(false);
            
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
            qDebug() << DTK_COLOR_BG_BLUE << DTK_PRETTY_FUNCTION << "Forward done" << DTK_NO_COLOR;
#endif

            foreach(dtkComposerEdge *o_route, this->outputRoutes())
                o_route->destination()->node()->update();
            
        }
    }
}

//! Overloads output value to feed the destination back with the corresponding input value.
/*! 
 * 
 * \param property Output constant property of a case block.
 */

QVariant dtkComposerNodeLoopFor::value(dtkComposerNodeProperty *property)
{
    if (property == this->inputProperty())
        return d->loop_variable;

    return QVariant();
}

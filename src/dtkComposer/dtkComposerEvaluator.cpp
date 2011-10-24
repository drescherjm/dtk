/* dtkComposerEvaluator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Oct 24 12:57:38 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 14:43:11 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 154
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEvaluator.h"
#include "dtkComposerEvaluator_p.h"

#include <dtkCore/dtkGlobal.h>

#include <dtkComposer/dtkComposerEdge.h>
#include <dtkComposer/dtkComposerNode.h>
#include <dtkComposer/dtkComposerNodeProperty.h>
#include <dtkComposer/dtkComposerScene.h>

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// Helper definitions
// /////////////////////////////////////////////////////////////////

// #define DTK_DEBUG_COMPOSER_EVALUATION 1

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate
// /////////////////////////////////////////////////////////////////

void dtkComposerEvaluatorPrivate::run(void)
{
    emit evaluationStarted();

    while(!this->stack.isEmpty())
        if(this->evaluate(this->stack.top()))
           this->stack.pop();

    emit evaluationStopped();
}

bool dtkComposerEvaluatorPrivate::evaluate(dtkComposerNode *node)
{
#if defined(DTK_DEBUG_COMPOSER_INTERACTION)
    qDebug() << DTK_PRETTY_FUNCTION << node;
#endif

    if (!node->dirty())
        return true;

    if (node->kind() == dtkComposerNode::Composite) {

        foreach(dtkComposerNode *child, node->childNodes())
            this->stack.push(child);

        return true;
    }

    // -- Check dirty inputs

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_COLOR_BG_GREEN << "-- Check dirty inputs" << node->title() << DTK_NO_COLOR;
#endif

    if (node->dirtyUpstreamNodes())
        return true;

    // -- Mark dirty outputs

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_COLOR_BG_GREEN << "-- Mark dirty outputs" << node->title() << DTK_NO_COLOR;
#endif

    node->markDirtyDownstreamNodes();

    // -- Pull

    foreach(dtkComposerEdge *i_route, node->inputRoutes()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << "Pulling" << node->title() << i_route << DTK_NO_COLOR;
#endif
        node->pull(i_route, i_route->destination());
    }

    // -- Run node's logics

#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
    qDebug() << DTK_COLOR_BG_RED  << "Running node" << node->title() << "'s logics" << DTK_NO_COLOR;
#endif

    // int status = node->run();

    node->run(); int status = true;

    // -- Push

    foreach(dtkComposerEdge *o_route, node->outputRoutes()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_YELLOW << "Pushing" << node->title() << o_route << DTK_NO_COLOR;
#endif
        node->push(o_route, o_route->source());
    }

    // --

    node->setDirty(false);

    // -- Forward

    foreach(dtkComposerEdge *o_route, node->outputRoutes()) {
#if defined(DTK_DEBUG_COMPOSER_EVALUATION)
        qDebug() << DTK_COLOR_BG_BLUE << "Forwarding" << node->title() << "->" << o_route->destination()->node()->title() << DTK_NO_COLOR;
#endif
        if(!this->stack.contains(o_route->destination()->node()))
            this->stack.push(o_route->destination()->node());
    }

    // --

    return status;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluator
// /////////////////////////////////////////////////////////////////

dtkComposerEvaluator::dtkComposerEvaluator(QObject *parent) : QObject(parent), d(new dtkComposerEvaluatorPrivate)
{
    d->scene = NULL;

    connect(d, SIGNAL(evaluationStarted()), this, SIGNAL(evaluationStarted()));
    connect(d, SIGNAL(evaluationStarted()), this, SIGNAL(evaluationStopped()));
}

dtkComposerEvaluator::~dtkComposerEvaluator(void)
{
    d->terminate();
    d->wait();

    delete d;
}

void dtkComposerEvaluator::setScene(dtkComposerScene *scene)
{
    d->scene = scene;
}

void dtkComposerEvaluator::start(void)
{
    if(!d->scene) {
        qDebug() << DTK_PRETTY_FUNCTION << "No scene set";
        return;
    }

    if(!d->stack.isEmpty()) {
        qDebug() << DTK_PRETTY_FUNCTION << "Stack is not empty";
        return;
    }

    if (d->scene->selectedItems().count()) {
        foreach(QGraphicsItem *item, d->scene->selectedItems()) {
            if (dtkComposerNode *node = dynamic_cast<dtkComposerNode *>(item)) { 
                node->setDirty(true);
                d->stack.push(node);
            }
        }
    } else {
        foreach(dtkComposerNode *node, d->scene->startNodes()) {
            node->setDirty(true);
            d->stack.push(node);
        }
    }

    qDebug() << DTK_PRETTY_FUNCTION << d->stack;

    emit evaluationStarted();
}

void dtkComposerEvaluator::stop(void)
{
    if(!d->scene)
        return;

    qDebug() << DTK_PRETTY_FUNCTION;

    emit evaluationStopped();
}

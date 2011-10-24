/* dtkComposerEvaluator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Oct 24 12:57:38 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 13:08:56 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 41
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

#include <dtkComposer/dtkComposerNode.h>
#include <dtkComposer/dtkComposerScene.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate
// /////////////////////////////////////////////////////////////////

void dtkComposerEvaluatorPrivate::run(void)
{
    qDebug() << DTK_PRETTY_FUNCTION;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluator
// /////////////////////////////////////////////////////////////////

dtkComposerEvaluator::dtkComposerEvaluator(void) : QObject(), d(new dtkComposerEvaluatorPrivate)
{
    d->scene = NULL;
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
    if(!d->scene)
        return;

    qDebug() << DTK_PRETTY_FUNCTION;
}

void dtkComposerEvaluator::stop(void)
{
    if(!d->scene)
        return;

    qDebug() << DTK_PRETTY_FUNCTION;
}

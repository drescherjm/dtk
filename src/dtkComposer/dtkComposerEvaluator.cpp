/* dtkComposerEvaluator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Sep 11 22:54:53 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Feb  8 11:06:18 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 77
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerEvaluator.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerScene.h"

#include <dtkCore/dtkAbstractObject.h>

#include <dtkScript/dtkScriptInterpreter.h>
#include <dtkScript/dtkScriptInterpreterPool.h>

class dtkComposerEvaluatorPrivate // : public QThread
{
public:
    dtkComposerScene *scene;
};

dtkComposerEvaluator::dtkComposerEvaluator(void) : QObject(), d(new dtkComposerEvaluatorPrivate)
{

}

dtkComposerEvaluator::~dtkComposerEvaluator(void)
{
    delete d;

    d = NULL;
}

void dtkComposerEvaluator::run(void)
{
    QList<dtkComposerNode *> datas;
    QList<dtkComposerNode *> processes;
    QList<dtkComposerNode *> views;

    foreach(dtkComposerNode *node, d->scene->nodes()) if(node->type() == dtkComposerNode::Data) datas << node;
    foreach(dtkComposerNode *node, d->scene->nodes()) if(node->type() == dtkComposerNode::Process) processes << node;
    foreach(dtkComposerNode *node, d->scene->nodes()) if(node->type() == dtkComposerNode::View) views << node;

    Q_UNUSED(datas);
    Q_UNUSED(processes);
    Q_UNUSED(views);
}

void dtkComposerEvaluator::evaluate(dtkComposerNode *node)
{
    Q_UNUSED(node);
}

void dtkComposerEvaluator::stop(void)
{

}

void dtkComposerEvaluator::setScene(dtkComposerScene *scene)
{
    d->scene = scene;
}

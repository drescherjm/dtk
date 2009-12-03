/* dtkComposerEvaluator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Sep 11 22:54:53 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Sep 13 18:23:36 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 72
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

    QString script;

    foreach(dtkComposerNode *node, views)
        script += this->evaluate(node);

    int stat; qDebug() << script;

    dtkScriptInterpreterPool::instance()->python()->interpret(script, &stat);
}

QString dtkComposerEvaluator::evaluate(dtkComposerNode *node)
{
    QString node_script;

    if(!node->inputEdges().count())
        return node_script;

    foreach(dtkComposerEdge *input, node->inputEdges())
        node_script += this->evaluate(input->source()->node()) + "\n";

    QString script = node->script(); script.replace("#0", node->object()->name());

    foreach(dtkComposerEdge *input, node->inputEdges()) {
        qDebug() << "replacing" << input->destination()->port() << "by" << input->source()->node()->object()->name();
        script.replace(input->destination()->port(), input->source()->node()->object()->name());
    }

    node_script += script;
    node_script += "\n";

    return node_script;
}

void dtkComposerEvaluator::stop(void)
{

}

void dtkComposerEvaluator::setScene(dtkComposerScene *scene)
{
    d->scene = scene;
}

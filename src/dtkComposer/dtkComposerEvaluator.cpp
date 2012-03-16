/* dtkComposerEvaluator.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:34:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. mars 16 18:22:01 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 268
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEvaluator.h"
#include "dtkComposerEvaluator_p.h"
#include "dtkComposerGraph.h"
#include "dtkComposerGraphNode.h"
#include "dtkComposerGraphEdge.h"

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// Helper definitions
// /////////////////////////////////////////////////////////////////

#define DTK_DEBUG_COMPOSER_EVALUATION 0

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate 
// /////////////////////////////////////////////////////////////////


// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluator
// /////////////////////////////////////////////////////////////////

dtkComposerEvaluator::dtkComposerEvaluator(QObject *parent) : QObject(parent), d(new dtkComposerEvaluatorPrivate)
{

}

dtkComposerEvaluator::~dtkComposerEvaluator(void)
{
    delete d;

    d = NULL;
}


void dtkComposerEvaluator::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
}

void dtkComposerEvaluator::run(bool run_concurrent)
{
    QTime time;
    time.start();

    d->stack << d->graph->root();

    emit started();
    while (this->step(run_concurrent));
    qDebug() << "elapsed time:"<< time.elapsed() << "ms";
    emit stopped();
}

void dtkComposerEvaluator::cont(bool run_concurrent)
{
    while (this->step(run_concurrent));
}

bool dtkComposerEvaluator::step(bool run_concurrent)
{
    if (d->stack.isEmpty())
        return false;

    d->current = d->stack.takeFirst();
    qDebug() << "current node to evaluate is" << d->current->title();
    bool runnable = true;
    foreach (dtkComposerGraphNode *pred, d->current->predecessors()) {
        if (pred->status() != dtkComposerGraphNode::Done) {
            qDebug() << "predecessor not ready" << pred->title();
            runnable = false;
            break;
        }
    }
    if (runnable) {
        if (d->current->status() == dtkComposerGraphNode::BreakPoint) {
            qDebug() << "break point reached";
            d->current->setStatus(dtkComposerGraphNode::Ready);
            d->stack << d->current;
            return false;
        }
        if (run_concurrent && d->current->kind() != dtkComposerGraphNode::SelectBranch)
            QtConcurrent::run(d->current, &dtkComposerGraphNode::eval);
        else
            d->current->eval();
        foreach ( dtkComposerGraphNode *s, d->current->successors())
            if (!d->stack.contains(s)) {
                if (s->status() == dtkComposerGraphNode::Done) //must reset status
                    s->setStatus(dtkComposerGraphNode::Ready);
                d->stack << s;
            }
    } else {
        qDebug() << " node not runnable, put it at the end of the list ";
        d->stack << d->current; // current is not ready, put it at the end
    }
    d->graph->layout();
    return !d->stack.isEmpty();
}

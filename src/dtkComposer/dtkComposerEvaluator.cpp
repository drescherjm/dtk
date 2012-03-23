/* dtkComposerEvaluator.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:34:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. mars 23 21:55:57 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 414
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
#include "dtkComposerGraphEdge.h"
#include "dtkComposerGraphNode.h"
#include "dtkComposerGraphNodeBegin.h"
#include "dtkComposerGraphNodeEnd.h"

#include <dtkLog/dtkLog.h>

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

    emit evaluationStarted();
    while (this->step(run_concurrent));
    dtkInfo() << "elapsed time:"<< time.elapsed() << "ms";
    emit evaluationStopped();
}

void dtkComposerEvaluator::cont(bool run_concurrent)
{
    while (this->step(run_concurrent));
}

void dtkComposerEvaluator::next(bool run_concurrent)
{
    if (d->stack.isEmpty())
        return;

    dtkComposerGraphNode *first = d->stack.first();
    if (dynamic_cast<dtkComposerGraphNodeBegin *>(first)) {
        // Begin node, look for the corresponding End node
        dtkComposerGraphNode *end;
        foreach(dtkComposerGraphNode *n,  d->graph->nodes())
            if ((dynamic_cast<dtkComposerGraphNodeEnd *>(n)) && n->wrapee() == first->wrapee()) {
                end = n;
                end->setBreakPoint();
                break;
            }
        while (d->current != end) // we must continue if a node inside the begin/end contains a breakpoint
            this->cont(run_concurrent);
        this->step(run_concurrent); // eval End
    } else {
        this->step(run_concurrent);
    }
}

bool dtkComposerEvaluator::step(bool run_concurrent)
{
    if (d->stack.isEmpty())
        return false;

    d->current = d->stack.takeFirst();
//    dtkTrace() << "current node to evaluate is" << d->current->title();
    bool runnable = true;

    dtkComposerGraphNodeList preds = d->current->predecessors();
    int   i = 0;
    int max = preds.count();
    while (i < max && runnable) {
        if (preds.at(i)->status() != dtkComposerGraphNode::Done && (!preds.at(i)->endloop())) {
            dtkTrace() << "predecessor not ready" << preds.at(i)->title();
            runnable = false;
        }
        i++;
    }

    if (runnable) {
        if (d->current->breakpoint() && d->current->status() == dtkComposerGraphNode::Ready ) {
            dtkTrace() << "break point reached";
            d->current->setStatus(dtkComposerGraphNode::Break);
            d->stack << d->current;
            return false;
        }
        if (run_concurrent && (d->current->kind() != dtkComposerGraphNode::SelectBranch))
            QtConcurrent::run(d->current, &dtkComposerGraphNode::eval);
        else
            d->current->eval();
        dtkComposerGraphNodeList s = d->current->successors();
        max = s.count();
        for (int i = 0; i < max; i++)
            if (!d->stack.contains(s.at(i))) {
                s.at(i)->setStatus(dtkComposerGraphNode::Ready);
                d->stack << s.at(i);
            }
    } else {
        dtkTrace() << " node not runnable, put it at the end of the list ";
        d->stack << d->current; // current is not ready, put it at the end
    }
    return !d->stack.isEmpty();
}

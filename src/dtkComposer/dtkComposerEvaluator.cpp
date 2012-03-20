/* dtkComposerEvaluator.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:34:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. mars 20 14:35:02 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 369
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

    emit started();
    while (this->step(run_concurrent));
    dtkInfo() << "elapsed time:"<< time.elapsed() << "ms";
    emit stopped();
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
    dtkTrace() << "current node to evaluate is" << d->current->title();
    bool runnable = true;
    foreach (dtkComposerGraphNode *pred, d->current->predecessors()) {
        if (pred->status() != dtkComposerGraphNode::Done && (!pred->endloop())) {
            dtkTrace() << "predecessor not ready" << pred->title();
            runnable = false;
            break;
        }
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
        foreach ( dtkComposerGraphNode *s, d->current->successors())
            if (!d->stack.contains(s)) {
                if (s->status() == dtkComposerGraphNode::Done) //must reset status
                    s->setStatus(dtkComposerGraphNode::Ready);
                d->stack << s;
            }
    } else {
        dtkTrace() << " node not runnable, put it at the end of the list ";
        d->stack << d->current; // current is not ready, put it at the end
    }
    d->graph->layout();
    return !d->stack.isEmpty();
}

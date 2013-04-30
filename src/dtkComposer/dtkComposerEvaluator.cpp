/* dtkComposerEvaluator.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:34:40 2012 (+0100)
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
#include <dtkNotification/dtkNotification.h>

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
    d->should_stop = false;
    d->stack.setCapacity(1024);
    d->max_stack_size = 0;
    d->notify = true;

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

void dtkComposerEvaluator::setNotify(bool notify)
{
    d->notify = notify;
}

void dtkComposerEvaluator::run(bool run_concurrent)
{
    QTime time; time.start();

    d->stack.clear();
    d->stack.append(d->graph->root());

    emit evaluationStarted();

    while (this->step(run_concurrent) && !d->should_stop);
    if (!d->should_stop) {
        QString msg = QString("Evaluation finished in %1 ms").arg(time.elapsed());
        dtkInfo() << msg;
        if (d->notify)
            dtkNotify(msg,30000);
        d->max_stack_size = 0;
    } else {
        QString msg = QString("Evaluation stopped after %1 ms").arg(time.elapsed());
        dtkInfo() << msg;
        if (d->notify)
            dtkNotify(msg,30000);
    }

    d->should_stop = false;

    emit evaluationStopped();
}


void dtkComposerEvaluator::stop(void)
{
    d->should_stop = true;
}

void dtkComposerEvaluator::reset(void)
{
    d->stack.clear();
    d->should_stop   = false;
}

void dtkComposerEvaluator::cont(bool run_concurrent)
{

    if (d->stack.isEmpty()) {
        this->run(run_concurrent);
        return;
    }


    while (this->step(run_concurrent) && !d->should_stop);
    if (!d->should_stop) {
        QString msg = QString("Evaluation resumed and finished");
        dtkInfo() << msg;
        if (d->notify)
            dtkNotify(msg,30000);
    } else {
        QString msg = QString("Evaluation stopped ");
        dtkInfo() << msg;
        if (d->notify)
            dtkNotify(msg,30000);
        dtkInfo() << "stack size: " << d->stack.size();
    }

    d->should_stop = false;

    emit evaluationStopped();
}

void dtkComposerEvaluator::logStack(void)
{
    dtkDebug() << "stack content:";

    int j = d->stack.firstIndex();
    while(j <= d->stack.lastIndex())
        dtkDebug() << d->stack.at(j++)->title();

    dtkDebug() << "stack end";
}

void dtkComposerEvaluator::next(bool run_concurrent)
{
    if (d->stack.isEmpty())
        return;

    dtkComposerGraphNode *first = d->stack.first();
    if (dynamic_cast<dtkComposerGraphNodeBegin *>(first)) {
        // Begin node, look for the corresponding End node
        dtkComposerGraphNode *end = NULL;
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
    // dtkTrace() << "handle " << d->current->title();
    bool runnable = true;

    dtkComposerGraphNodeList::const_iterator it;
    dtkComposerGraphNodeList::const_iterator ite;
    dtkComposerGraphNode *node ;

    dtkComposerGraphNodeList preds = d->current->predecessors();
    it = preds.constBegin();
    ite = preds.constEnd();
    while(it != ite) {
        node = *it++;
        if (node->status() != dtkComposerGraphNode::Done) {
            if (!node->endloop()) {
                runnable = false;
                break;
            } else {
                // predecessor is an end loop, we can continue, but we must unset the endloop flag.
                // dtkTrace() << "predecessor of "<< d->current->title() << " is an end loop, continue" << node->title();
                node->setEndLoop(false);
            }
        }
    }

    if (runnable) {
        if (d->current->breakpoint() && d->current->status() == dtkComposerGraphNode::Ready ) {
            dtkTrace() << "break point reached";
            d->current->setStatus(dtkComposerGraphNode::Break);
            d->stack.append( d->current);
            return false;
        }
        if (run_concurrent && (d->current->kind() == dtkComposerGraphNode::Process)){
            // dtkDebug() << "running process node in another thread"<< d->current->title();
            QtConcurrent::run(d->current, &dtkComposerGraphNode::eval);
        } else if ((d->current->kind() == dtkComposerGraphNode::View)) {
            connect(this, SIGNAL(runMainThread()), d->current, SLOT(eval()),Qt::BlockingQueuedConnection);
            // dtkTrace() << "emit signal and wait for GUI thread to run the node";
            emit runMainThread();
            disconnect(this, SIGNAL(runMainThread()), d->current, SLOT(eval()));
        } else {
            // dtkTrace() << "evaluating leaf node"<< d->current->title();
            d->current->eval();
        }

        dtkComposerGraphNodeList s = d->current->successors();
        it = s.constBegin();
        ite = s.constEnd();
        if (!d->stack.isEmpty()) {
            while(it != ite) {
                node = *it++;
                bool stacked = false;
                int j = d->stack.firstIndex();
                while(j <= d->stack.lastIndex() && !stacked)
                    stacked = (d->stack.at(j++) == node);
                // dtkTrace() << "add successor to stack " << node->title();
                if (!stacked)
                    d->stack.append(node);
            }
        } else {
            while(it != ite)
                d->stack.append(*it++);
        }


        // while(it != ite) {
        //     node = *it++;
        //     bool stacked = false;
        //     if (!d->stack.isEmpty()) {
        //         int j = d->stack.firstIndex();
        //         while(j <= d->stack.lastIndex() && !stacked)
        //             stacked = (d->stack.at(j++) == node);
        //     }
        //     // dtkTrace() << "add successor to stack " << node->title();
        //     if (!stacked)
        //         d->stack.append(node);
        // }
    } else if (run_concurrent) {
        dtkTrace() << "add back current node to stack: "<< d->current->title();
        d->stack.append(d->current);
    }
    // if (d->stack.size() > d->max_stack_size) {
    //     d->max_stack_size = d->stack.size();
    //     dtkDebug() << "Max stack size raised: "<< d->max_stack_size;
    // }
    d->stack.normalizeIndexes();
    return !d->stack.isEmpty();
}

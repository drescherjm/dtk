/* dtkComposerEvaluator.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:34:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 14:42:20 2014 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 841
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

#include <dtkLog/dtkLogger.h>
#include <dtkMathSupport/dtkGraph.h>
#include <dtkWidgets/dtkNotification.h>

#include <QtCore>
#include <QtConcurrent>

// ///////////////////////////////////////////////////////////////////
// Log categories
// ///////////////////////////////////////////////////////////////////

// //DTK_LOG_CATEGORY(FR_INRIA_DTK_COMPOSER_EVALUATOR, "fr.inria.dtk.composer.evaluator")

// /////////////////////////////////////////////////////////////////
// Helper definitions
// /////////////////////////////////////////////////////////////////

#define DTK_DEBUG_COMPOSER_EVALUATION 0

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluatorPrivate
// /////////////////////////////////////////////////////////////////

// bool dtkComposerEvaluatorPrivate::should_stop = false;

// /////////////////////////////////////////////////////////////////
// dtkComposerEvaluator
// /////////////////////////////////////////////////////////////////

dtkComposerEvaluator::dtkComposerEvaluator(QObject *parent) : QObject(parent), d(new dtkComposerEvaluatorPrivate)
{
    d->should_stop = false;
    d->stack.setCapacity(1024);
    d->max_stack_size = 0;
    d->notify         = true;
    d->profiling      = false;
    d->start_node     = NULL;
    d->use_gui        = (qApp && qobject_cast<QGuiApplication *>(qApp));
}

dtkComposerEvaluator::~dtkComposerEvaluator(void)
{
    delete d;

    d = NULL;
}

void dtkComposerEvaluator::setNotify(bool notify)
{
    d->notify = notify;
}

void dtkComposerEvaluator::setProfiling(bool profiling)
{
    d->profiling = profiling;
}

void dtkComposerEvaluator::run_static_rec(bool run_concurrent)
{
    if (!d->start_node) {
        d->start_node = d->graph->root();
        d->start_node->setGraph(d->graph);
    }

    dtkComposerGraphNodeBegin *begin = static_cast<dtkComposerGraphNodeBegin *>(d->start_node);
    bool is_if  = (begin->kind() ==  dtkComposerGraphNode::BeginIf );

    dtkComposerGraphNodeList L= begin->evaluableChilds();

    qlonglong end_loop_next = -1 ;
    qlonglong nodeCount = L.count();
    qlonglong current = 0;

    QElapsedTimer *timer = NULL;

    dtkComposerGraphNode::Kind kind;
    while (current < nodeCount &&  !d->should_stop) {
        if (d->profiling) {
            timer = new QElapsedTimer;
            timer->restart();
        }
        dtkComposerGraphNode *node = L.at(current);
        if (!d->eval_count.contains(node)) {
            d->eval_count[node]    = 0;
            d->eval_duration[node] = 0.0;
        }
        kind = node->kind();
        if (kind == dtkComposerGraphNode::BeginLoop || kind == dtkComposerGraphNode::BeginIf) {

            node->eval();
            // dtkComposerEvaluator ev;
            // ev.setGraph(d->graph);
            setStartNode(node);
            run_static_rec(false);
            if (d->profiling) {
                d->eval_count[node] ++;
                d->eval_duration[node] +=  timer->nsecsElapsed() / 1000000.0;
            }

            current ++;
        } else if (kind == dtkComposerGraphNode::SelectBranch ) {
            // dtkTrace() << "Select Branch";
            node->eval();
            dtkComposerGraphNode *next = node->firstSuccessor();

            if (is_if) {
                setStartNode(next);
                run_static_rec(false);
                current = nodeCount;
                if (d->profiling) {
                    d->eval_count[node] ++;
                    d->eval_duration[node] +=  timer->nsecsElapsed() / 1000000.0;
                }
            } else {
                qlonglong i = 0;
                while (i < nodeCount && (L[i]) != next) {
                    i++;
                }

                current = i;
            }

        } else if (node->endloop() ) {
            // dtkTrace() << "End Loop";
            node->eval();
            if (end_loop_next < 0) {
                dtkComposerGraphNode *next = node->firstSuccessor();
                qlonglong i = nodeCount -1;
                while (L[i] != next) { i--; };
                current = i;
                end_loop_next = i;
            } else {
                current = end_loop_next;
            }
        } else if (kind == dtkComposerGraphNode::View || kind == dtkComposerGraphNode::Actor ) {
            // dtkTrace() << "View|Actor";
            if (d->use_gui) {
                connect(this, SIGNAL(runMainThread()), node, SLOT(eval()),Qt::BlockingQueuedConnection);
                // dtkTrace() << "emit signal and wait for GUI thread to run the node";
                emit runMainThread();
                disconnect(this, SIGNAL(runMainThread()), node, SLOT(eval()));
            } else {
                node->setStatus(dtkComposerGraphNode::Done);
            }
            current ++;
        } else {
            // dtkTrace() << "eval" << node->title();
            node->eval();
            if (d->profiling) {
                d->eval_count[node] ++;
                d->eval_duration[node] +=  timer->nsecsElapsed() / 1000000.0;
            }
            current ++;
        }
    }
    if (d->profiling && timer) {
        delete timer;
    }

    d->should_stop = false;
}

void dtkComposerEvaluator::run_static(bool run_concurrent)
{
    QTime time; time.start();
    emit evaluationStarted();
    run_static_rec(run_concurrent);
    QString msg = QString("Evaluation finished in %1 ms").arg(time.elapsed());
    dtkInfo() << msg;
    if (d->notify)
        dtkNotify(msg,30000);
    emit evaluationStopped();
    d->start_node = d->graph->root();

    if (d->profiling) {
        printProfiling();
        // foreach(dtkComposerGraphNode * node, d->eval_count.keys()) {
        //     qlonglong count = d->eval_count[node];
        //     double mean = d->eval_duration[node] / count;
        //     qDebug() << node->title() << ";" << count << ";" <<  mean << ";" << d->eval_duration[node];
        // }
    }

}

void  dtkComposerEvaluator::printProfiling(qlonglong level)
{
    dtkComposerGraphNodeBegin *begin = static_cast<dtkComposerGraphNodeBegin *>(d->start_node);

    dtkComposerGraphNodeList L= begin->evaluableChilds();
    qlonglong nodeCount = L.count();
    qlonglong current = 0;

    dtkComposerGraphNode::Kind kind;

    while (current < nodeCount) {
        dtkComposerGraphNode *node = L.at(current);

        qlonglong count = d->eval_count[node];
        double mean = d->eval_duration[node] / count;
        qDebug() << QString(level, QChar(' ')) + node->title() << ";" << count << ";" <<  mean << ";" << d->eval_duration[node];
        kind = node->kind();
        if (kind == dtkComposerGraphNode::BeginLoop || kind == dtkComposerGraphNode::BeginIf) {
            setStartNode(node);
            qlonglong sublevel = level +1;
            printProfiling(sublevel);
        }
        current++;
    }
}

void dtkComposerEvaluator::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;

    connect(graph, SIGNAL(cleared()), this, SLOT(reset()));
}

void dtkComposerEvaluator::setStartNode(dtkComposerGraphNode *node)
{
    d->start_node = node;
}

void dtkComposerEvaluator::run(bool run_concurrent)
{
    QTime time; time.start();

    if (d->stack.isEmpty())
        d->stack.setCapacity(1024);

    d->stack.clear();

    if (!d->start_node)
        d->start_node = d->graph->root();

    d->stack.append(d->start_node);

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
    d->start_node    = NULL;
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
    dtkTrace() << "stack content:" ;
    d->stack.normalizeIndexes();
    for (int i = d->stack.firstIndex()  ; i <= d->stack.lastIndex() ; i++ ) {
            dtkTrace() << "  " << d->stack.at(i)->title() << d->stack.at(i)->status() << d->stack.at(i)->predecessors().count() ;
    }
    dtkTrace() << "stack end";
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
    // dtkTrace() << "handle " << d->current->title() << d->start_node->title() ;
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
            if (node->status() == dtkComposerGraphNode::Running) {
                dtkDebug() << d->current->title() <<  " is waiting for " << node->title();
                this->logStack();
                if (d->waitfor.contains(d->current,node)) { // d->current is already waiting for node
                    dtkDebug()<< "Force the evaluator to wait for " << node->title();
                    d->futures.take(node).waitForFinished();
                    d->waitfor.remove(d->current,node);
                    continue;
                } else {
                    dtkDebug()<< "store the waiting of " << node->title();
                    d->waitfor.insert(d->current,node);
                    // FIXME: we should clear the hash when wait is not necessary (it won't be removed in this case)
                }
            }
            if (!node->endloop()) {
                runnable = false;
//                dtkTrace() << d->current->title() <<  " depends on " << node->title();
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
            d->current->setStatus(dtkComposerGraphNode::Running);
            d->futures.insert(d->current,QtConcurrent::run(d->current, &dtkComposerGraphNode::eval));
            // FIXME: we should clear the hash when futures are finished
        } else if ((d->current->kind() == dtkComposerGraphNode::View) || (d->current->kind() == dtkComposerGraphNode::Actor)) {
            if (d->use_gui) {
                connect(this, SIGNAL(runMainThread()), d->current, SLOT(eval()),Qt::BlockingQueuedConnection);
//                dtkTrace() << "emit signal and wait for GUI thread to run the node";
                emit runMainThread();
                disconnect(this, SIGNAL(runMainThread()), d->current, SLOT(eval()));
//                this->logStack();
            } else {
                d->current->setStatus(dtkComposerGraphNode::Done);
            }
        } else {
//            dtkTrace() << "evaluating leaf node"<< d->current->title();
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

    } else if (run_concurrent) {
//        dtkTrace() << "add back current node to stack: "<< d->current->title();
        d->stack.append(d->current);
    }
    // if (d->stack.size() > d->max_stack_size) {
    //     d->max_stack_size = d->stack.size();
    //     dtkDebug() << "Max stack size raised: "<< d->max_stack_size;
    // }
    d->stack.normalizeIndexes();
    return !d->stack.isEmpty();
}

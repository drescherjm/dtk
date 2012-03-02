/* dtkComposerEvaluator.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:34:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. mars  2 18:55:02 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 169
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

void dtkComposerEvaluator::run(void)
{
    dtkComposerGraphEdgeList edges = d->graph->edges();
    dtkComposerGraphNodeList nodes = d->graph->nodes();

    dtkComposerGraphNode *current;
    dtkComposerGraphNodeList stack ;

    stack << d->graph->root();

    emit started();

    while (!stack.isEmpty()) {
        current = stack.takeFirst();
        qDebug() << "current node to evaluate is " << current->title();
        if (current->status() == dtkComposerGraphNode::Done) {
            qDebug() << "Warning, node is already done !" ;
            continue;
        }
        bool runnable = true;
        foreach (dtkComposerGraphNode *pred, current->predecessors()) {
            if (pred->status() != dtkComposerGraphNode::Done && (pred->kind() != dtkComposerGraphNode::SelectBranch)) {
                qDebug() << " predecessor not ready " << pred->title();
                runnable = false;
                break;
            }
        }
        if (runnable) {
            current->eval();
            foreach ( dtkComposerGraphNode *s, current->successors())
                if (!stack.contains(s)) {
                    s->setStatus( dtkComposerGraphNode::Ready);
                    stack << s;
                }
        } else {
            qDebug() << " node not runnable, put it at the end of the list ";
            stack << current; // current is not ready, put it at the end
        }
        d->graph->layout();
        QApplication::processEvents();
    }
    emit stopped();
}

/* dtkComposerEvaluator_p.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:39:36 2012 (+0100)
 * Version: $Id$
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSEREVALUATOR_P_H
#define DTKCOMPOSEREVALUATOR_P_H


#include "dtkComposerSupportExport.h"

#include "dtkComposerGraph.h"
#include "dtkComposerGraphNode.h"
#include <QtCore>

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerEvaluatorPrivate : public QThread
{
public:
    dtkComposerGraph *graph;
    QContiguousCache<dtkComposerGraphNode *> stack;
    dtkComposerGraphNode *current;
    dtkComposerGraphNode *start_node;
    dtkComposerGraphNode *end_node;

public:
    QHash<dtkComposerGraphNode *, qlonglong >  eval_count;
    QHash<dtkComposerGraphNode *, double >  eval_duration;

public:
    QHash<dtkComposerGraphNode *, QFuture<void> > futures;
    QMultiHash<dtkComposerGraphNode *, dtkComposerGraphNode * > waitfor;

public:
    bool should_stop;
    bool notify;
    bool use_gui;
    bool profiling;

public:
    int max_stack_size;

};

#endif

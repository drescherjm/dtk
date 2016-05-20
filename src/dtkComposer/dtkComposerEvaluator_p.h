/* dtkComposerEvaluator_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:39:36 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:30:28 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 39
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerGraph.h"
#include "dtkComposerGraphNode.h"
#include <QtCore>

class DTKCOMPOSER_EXPORT dtkComposerEvaluatorPrivate : public QThread
{
public:
    dtkComposerGraph *graph;
    dtkComposerGraphNode *current;
    dtkComposerGraphNode *start_node;
    dtkComposerGraphNode *end_node;

public:
    QContiguousCache<dtkComposerGraphNode *> stack;

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
    bool catch_exceptions;

public:
    int max_stack_size;
};


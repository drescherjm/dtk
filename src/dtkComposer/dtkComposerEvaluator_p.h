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

#include "dtkComposerGraph.h"
#include "dtkComposerGraphNode.h"
#include <QtCore>

class dtkComposerEvaluatorPrivate : public QThread
{
public:
    dtkComposerGraph *graph;
    dtkComposerGraphNode *current;

public:
    QContiguousCache<dtkComposerGraphNode *> stack;

public:
    QHash<dtkComposerGraphNode *, int> connected_views;

public:
    bool should_stop;

public:
    int max_stack_size;
};


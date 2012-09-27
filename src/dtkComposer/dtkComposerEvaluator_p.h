/* dtkComposerEvaluator_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:39:36 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mer. sept. 26 10:44:00 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSEREVALUATOR_P_H
#define DTKCOMPOSEREVALUATOR_P_H

#include "dtkComposerGraph.h"
#include "dtkComposerGraphNode.h"
#include <QtCore>

class dtkComposerEvaluatorPrivate : public QThread
{
public:
    dtkComposerGraph *graph;
    QContiguousCache<dtkComposerGraphNode *> stack;
    dtkComposerGraphNode *current;

public:
    QHash<dtkComposerGraphNode *, int > connected_views;
public:
    bool should_stop;

public:
    int max_stack_size;

};

#endif

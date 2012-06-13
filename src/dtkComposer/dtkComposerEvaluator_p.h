/* dtkComposerEvaluator_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:39:36 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. mai 15 14:20:46 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 19
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
    dtkComposerGraphNodeList stack;
    dtkComposerGraphNode *current;

public:
    bool should_stop;
};

#endif

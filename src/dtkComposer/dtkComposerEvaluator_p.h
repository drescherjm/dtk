/* dtkComposerEvaluator_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 11:39:36 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. mars  2 08:59:00 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 6
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
#include <QtCore>

class dtkComposerEvaluatorPrivate : public QThread
{
public:
    dtkComposerGraph *graph;
};

#endif

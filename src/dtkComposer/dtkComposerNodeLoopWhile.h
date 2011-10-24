/* dtkComposerNodeLoopWhile.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed May  4 08:44:22 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 16:28:59 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELOOPWHILE_H
#define DTKCOMPOSERNODELOOPWHILE_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLoop.h"

class dtkComposerNodeLoopWhilePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeLoopWhile : public dtkComposerNodeLoop
{
    Q_OBJECT

public:
     dtkComposerNodeLoopWhile(dtkComposerNode *parent = 0);
    ~dtkComposerNodeLoopWhile(void);

public:
    void layout(void);

private:
    dtkComposerNodeLoopWhilePrivate *d;

private:
    friend class dtkComposerEvaluatorPrivate;
};

#endif

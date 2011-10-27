/* dtkComposerNodeConditional.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:59:35 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Oct 26 16:36:21 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONDITIONAL_H
#define DTKCOMPOSERNODECONDITIONAL_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeControl.h"

class dtkComposerEdge;
class dtkComposerNodeProperty;

class dtkComposerNodeConditionalPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeConditional : public dtkComposerNodeControl
{
    Q_OBJECT

public:
     dtkComposerNodeConditional(dtkComposerNode *parent = 0);
    ~dtkComposerNodeConditional(void);

public:
    void layout(void);

public slots:
    bool evaluate(dtkComposerEvaluatorPrivate *evaluator);
    /* void update(void); */

private:
    dtkComposerNodeConditionalPrivate *d;

private:
    friend class dtkComposerEvaluatorPrivate;
};

#endif

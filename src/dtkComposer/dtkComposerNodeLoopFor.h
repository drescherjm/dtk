/* dtkComposerNodeLoopFor.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:01:16 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Oct 26 16:36:55 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELOOPFOR_H
#define DTKCOMPOSERNODELOOPFOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLoop.h"

class dtkComposerEvaluatorPrivate;
class dtkComposerNodeLoopForPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeLoopFor : public dtkComposerNodeLoop
{
    Q_OBJECT

public:
     dtkComposerNodeLoopFor(dtkComposerNode *parent = 0);
    ~dtkComposerNodeLoopFor(void);

public:
    void layout(void);

public slots:
    bool evaluate(dtkComposerEvaluatorPrivate *evaluator);
    /* void update(void); */

public:
    QVariant value(dtkComposerNodeProperty *property);

protected:
    void pull(dtkComposerEdge *i_route, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeLoopForPrivate *d;

private:
    friend class dtkComposerEvaluatorPrivate;
};

#endif

/* dtkComposerNodeLoop.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar  7 09:21:10 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Oct 26 17:53:35 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 55
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELOOP_H
#define DTKCOMPOSERNODELOOP_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeControl.h"

class dtkComposerNodeControlBlock;
class dtkComposerNodeProperty;

class dtkComposerNodeLoopPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeLoop : public dtkComposerNodeControl
{
    Q_OBJECT

public:
     dtkComposerNodeLoop(dtkComposerNode *parent = 0);
    ~dtkComposerNodeLoop(void);

    bool loopConditon(void);

    QVariant value(dtkComposerNodeProperty *property);

    QList<QVariant> passThroughVariables(void);

protected:
    void setLoopCondition(bool loop_condition);

    void setPassThroughVariable(dtkComposerNodeProperty *property, QVariant pass_through_variable);

protected:
    bool dirtyBlockEndNodes(void);

protected:
    virtual void pull(dtkComposerEdge *i_route, dtkComposerNodeProperty *property);
    virtual void push(dtkComposerEdge *o_route, dtkComposerNodeProperty *property);

protected:
    void updatePassThroughVariables(void);

private:
    dtkComposerNodeLoopPrivate *d;

private:
    friend class dtkComposerEvaluatorPrivate;
};

#endif

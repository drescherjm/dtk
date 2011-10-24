/* dtkComposerEvaluator_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Oct 24 12:54:41 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 16:38:07 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 47
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSEREVALUATOR_P_H
#define DTKCOMPOSEREVALUATOR_P_H

#include <QtCore/QThread>
#include <QtCore/QStack>

class dtkComposerNode;
class dtkComposerNodeCase;
class dtkComposerNodeConditional;
class dtkComposerNodeLoopDataComposite;
class dtkComposerNodeLoopFor;
class dtkComposerNodeLoopWhile;
class dtkComposerScene;

class dtkComposerEvaluatorPrivate : public QThread
{
    Q_OBJECT
    
public:
    void run(void);

private:
    bool evaluate(dtkComposerNode *node);
    bool evaluate(dtkComposerNodeCase *node);
    bool evaluate(dtkComposerNodeConditional *node);
    bool evaluate(dtkComposerNodeLoopDataComposite *node);
    bool evaluate(dtkComposerNodeLoopFor *node);
    bool evaluate(dtkComposerNodeLoopWhile *node);

public:
    dtkComposerScene *scene;

signals:
    void evaluationStarted(void);
    void evaluationStopped(void);

public:
    QStack<dtkComposerNode *> stack;
};

#endif

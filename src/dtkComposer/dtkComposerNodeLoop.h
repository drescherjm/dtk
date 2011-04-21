/* dtkComposerNodeLoop.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar  7 09:21:10 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 21 12:11:44 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 31
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

class dtkComposerNodeLoopPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeLoop : public dtkComposerNodeControl
{
    Q_OBJECT

public:
     dtkComposerNodeLoop(dtkComposerNode *parent = 0);
    ~dtkComposerNodeLoop(void);

    bool  isPreRunning(void);
    bool isPostRunning(void);

    bool loopConditon(void);

    dtkComposerNodeControlBlock *currentBlock(void);

protected:
    void  setPreRunning(bool pre_running);
    void setPostRunning(bool post_running);

    void setLoopCondition(bool loop_condition);

    void setCurrentBlock(dtkComposerNodeControlBlock *block);

protected:
    void pull(dtkComposerEdge *i_route, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *o_route, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeLoopPrivate *d;
};

#endif

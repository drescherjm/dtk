/* dtkComposerNodeLoopWhile_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Oct 24 16:25:16 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 24 16:26:06 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELOOPWHILE_P_H
#define DTKCOMPOSERNODELOOPWHILE_P_H

class dtkComposerNode;
class dtkComposerNodeControlBlock;
class dtkComposerNodeProperty;

class dtkComposerNodeLoopWhilePrivate
{
public:
    dtkComposerNodeControlBlock *block_cond;
    dtkComposerNodeControlBlock *block_loop;

    dtkComposerNode *node_cond;
    dtkComposerNodeProperty *prop_cond;
};

#endif

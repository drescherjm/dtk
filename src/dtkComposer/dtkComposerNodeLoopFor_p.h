/* dtkComposerNodeLoopFor_p.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Oct 26 16:37:12 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Oct 26 16:39:07 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */
#ifndef DTKCOMPOSERNODELOOPFOR_P
#define DTKCOMPOSERNODELOOPFOR_P

class QVariant;

class dtkComposerNode;
class dtkComposerNodeControlBlock;
class dtkComposerNodeProperty;

class dtkComposerNodeLoopForPrivate
{
public:
    dtkComposerNodeControlBlock *block_cond;
    dtkComposerNodeControlBlock *block_loop;
    dtkComposerNodeControlBlock *block_post;

    dtkComposerNode *node_cond;
    dtkComposerNode *node_post;

    dtkComposerNodeProperty *prop_cond;
    dtkComposerNodeProperty *prop_post;

public:
    QVariant loop_variable;
    QVariant loop_variable_old;
};

#endif

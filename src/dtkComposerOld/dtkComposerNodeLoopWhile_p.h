/* dtkComposerNodeLoopWhile_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Oct 24 16:25:16 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Nov  9 16:08:08 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 10
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
class dtkComposerNodeLoopWhile;
class dtkComposerNodeControlBlock;
class dtkComposerNodeProperty;

class dtkComposerNodeLoopWhilePrivate
{
public:
    dtkComposerNodeControlBlock *createBlock(const QString& title, dtkComposerNodeLoopWhile *parent);

public:
    dtkComposerNode *node_cond;
    dtkComposerNodeProperty *prop_cond;
};

#endif

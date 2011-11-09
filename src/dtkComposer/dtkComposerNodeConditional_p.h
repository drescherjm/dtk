/* dtkComposerNodeConditional_p.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Oct 26 16:33:37 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Nov  9 12:01:26 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */
 
#ifndef DTKCOMPOSERNODECONDITIONAL_P
#define DTKCOMPOSERNODECONDITIONAL_P

class dtkComposerNodeConditional;
class dtkComposerNodeControlBlock;

class dtkComposerNodeConditionalPrivate
{
public:
    dtkComposerNodeControlBlock *createBlock(const QString& title, dtkComposerNodeConditional *parent);
};

#endif

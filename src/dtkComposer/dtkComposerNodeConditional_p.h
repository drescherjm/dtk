/* dtkComposerNodeConditional_p.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Oct 26 16:33:37 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Oct 26 16:38:25 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */
 
#ifndef DTKCOMPOSERNODECONDITIONAL_P
#define DTKCOMPOSERNODECONDITIONAL_P

class dtkComposerNodeControlBlock;

class dtkComposerNodeConditionalPrivate
{
public:
    dtkComposerNodeControlBlock *block_then;
    dtkComposerNodeControlBlock *block_else;
};

#endif

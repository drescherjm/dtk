/* dtkComposerNodeConditional_p.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Oct 26 16:33:37 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Nov 28 17:07:22 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */
 
#ifndef DTKCOMPOSERNODECONDITIONAL_P
#define DTKCOMPOSERNODECONDITIONAL_P

class dtkComposerEdge;
class dtkComposerNodeConditional;
class dtkComposerNodeControlBlock;
template <class T> class dtkComposerNodeTransmitter;

class dtkComposerNodeConditionalPrivate
{
public:
    dtkComposerNodeControlBlock *createBlock(const QString& title, dtkComposerNodeConditional *parent);

public:
    QHash<dtkComposerRoute *, dtkComposerNodeTransmitter<bool> *> receivers;
};

#endif

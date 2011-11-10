/* dtkComposerNodeLoopDataComposite_p.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Oct 25 10:15:48 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Nov  9 15:23:27 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELOOPDATACOMPOSITE_P
#define DTKCOMPOSERNODELOOPDATACOMPOSITE_P

#include <dtkCore/dtkGlobal>

class dtkAbstractData;
class dtkAbstractDataComposite;

class dtkComposerNodeLoopDataCompositePrivate
{
public:
    dtkComposerNodeControlBlock *createBlock(const QString& title, dtkComposerNodeLoopDataComposite *parent);

public:
    dtkxarch_int from_default;
    dtkxarch_int to_default;

    dtkxarch_int from;
    dtkxarch_int to;
    dtkxarch_int step;
    dtkxarch_int index;

    dtkAbstractData *item;

    dtkAbstractDataComposite *composite;

    bool valid_input_composite;
};

#endif

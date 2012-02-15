/* dtkComposerNodeBooleanOperator.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:51:36 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 10:08:18 2012 (+0100)
 *           By: tkloczko
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEBOOLEANOPERATOR_H
#define DTKCOMPOSERNODEBOOLEANOPERATOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeBooleanOperatorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeBooleanOperator : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeBooleanOperator(void);
    ~dtkComposerNodeBooleanOperator(void);

public:
    void run(void);

private:
    dtkComposerNodeBooleanOperatorPrivate *d;
};

#endif

/* dtkComposerNodeBooleanOperator.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:51:36 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 18:06:00 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 15
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

public:
    inline QString type(void) {
        return "boolean operator";
    }

    inline QString titleHint(void) {
        return "Boolean Operator";
    }

    inline QString labelHint(int port) {
        if (port == 0)
            return "lhs";
        else if (port == 1)
            return "rhs";
        else
            return "value";
    }

private:
    dtkComposerNodeBooleanOperatorPrivate *d;
};

#endif

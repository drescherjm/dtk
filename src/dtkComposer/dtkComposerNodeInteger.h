/* dtkComposerNodeInteger.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 27 12:38:37 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEINTEGER_H
#define DTKCOMPOSERNODEINTEGER_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeIntegerPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeInteger : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeInteger(void);
    ~dtkComposerNodeInteger(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "integer";
    }

    inline QString titleHint(void) {
        return "Integer";
    }

    inline QString labelHint(int port) {
        return "value";
    }

private:
    dtkComposerNodeIntegerPrivate *d;
};

#endif

/* dtkComposerNodeInteger.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jun 26 16:17:16 2012 (+0200)
 *           By: tkloczko
 *     Update #: 15
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

#include <dtkCore/dtkGlobal.h>

class dtkComposerNodeIntegerPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeInteger interface
// /////////////////////////////////////////////////////////////////

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

    inline QString inputLabelHint(int) {
        return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

public:
    dtkxarch_int value(void);

public:
    void setValue(dtkxarch_int value);

private:
    dtkComposerNodeIntegerPrivate *d;
};

#endif

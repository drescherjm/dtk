/* dtkComposerNodeInteger.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Aug  4 00:06:38 2012 (+0200)
 *           By: tkloczko
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEINTEGER_H
#define DTKCOMPOSERNODEINTEGER_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

#include <dtkCore/dtkGlobal.h>

class dtkComposerNodeIntegerPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeInteger interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeInteger : public dtkComposerNodeLeaf
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
    qlonglong value(void);

public:
    void setValue(qlonglong value);

private:
    dtkComposerNodeIntegerPrivate *d;
};

#endif

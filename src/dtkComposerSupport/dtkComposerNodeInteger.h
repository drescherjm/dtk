/* dtkComposerNodeInteger.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:06:26 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 19
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

#include <dtkCoreSupport/dtkGlobal.h>

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

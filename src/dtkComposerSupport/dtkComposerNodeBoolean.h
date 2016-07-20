/* dtkComposerNodeBoolean.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 16:46:54 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Aug  4 00:08:42 2012 (+0200)
 *           By: tkloczko
 *     Update #: 19
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEBOOLEAN_H
#define DTKCOMPOSERNODEBOOLEAN_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeBooleanPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeBoolean : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeBoolean(void);
    ~dtkComposerNodeBoolean(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "boolean";
    }

    inline QString titleHint(void) {
        return "Boolean";
    }

    inline QString inputLabelHint(int) {
        return "value";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

public:
    bool value(void);

public:
    void setValue(bool value);

private:
    dtkComposerNodeBooleanPrivate *d;
};

#endif

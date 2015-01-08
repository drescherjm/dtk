/* dtkComposerNodeInteger.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:21 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerNodeLeaf.h"

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
    /* inline QString type(void) { */
    /*     return "integer"; */
    /* } */

    /* inline QString titleHint(void) { */
    /*     return "Integer"; */
    /* } */

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


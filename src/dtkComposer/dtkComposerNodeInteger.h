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
    qlonglong value(void);

public:
    void setValue(qlonglong value);

private:
    dtkComposerNodeIntegerPrivate *d;
};


/* dtkComposerNodeLeaf.h --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:03 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 08:50:04 2012 (+0100)
 *           By: tkloczko
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELEAF_H
#define DTKCOMPOSERNODELEAF_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLeafPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeLeaf : public dtkComposerNode
{
public:
             dtkComposerNodeLeaf(void);
    virtual ~dtkComposerNodeLeaf(void);

public:
    virtual void setInputs(void);
    virtual void run(void);

private:
    dtkComposerNodeLeafPrivate *d;
};

#endif

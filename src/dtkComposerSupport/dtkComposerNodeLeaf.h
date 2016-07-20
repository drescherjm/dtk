/* dtkComposerNodeLeaf.h ---
 *
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:03 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue May 22 16:52:37 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 26
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODELEAF_H
#define DTKCOMPOSERNODELEAF_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLeafPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeLeaf : public dtkComposerNode
{
public:
    dtkComposerNodeLeaf(void);
    virtual ~dtkComposerNodeLeaf(void);

public:
    virtual void setInputs(void);
    virtual void run(void);

public:
    void setAsHeader(bool header);
    void setAsFooter(bool footer);

public:
    bool isHeader(void);
    bool isFooter(void);

private:
    dtkComposerNodeLeafPrivate *d;
};

#endif

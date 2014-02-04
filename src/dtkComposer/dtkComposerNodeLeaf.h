/* dtkComposerNodeLeaf.h --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:03 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  5 09:38:38 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLeafPrivate;

class  dtkComposerNodeLeaf : public dtkComposerNode
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


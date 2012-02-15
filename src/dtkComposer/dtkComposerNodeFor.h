/* dtkComposerNodeFor.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:12:58 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 09:50:30 2012 (+0100)
 *           By: tkloczko
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEFOR_H
#define DTKCOMPOSERNODEFOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeControl.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFor declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeForPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeFor : public dtkComposerNodeControl
{
public:
             dtkComposerNodeFor(void);
    virtual ~dtkComposerNodeFor(void);

public:
    void setInputs(void);
    void setConditions(void);
    void setOutputs(void);
    void setVariables(void);
    void selectBranch(void);
    void begin(void);
    void end(void);

private:
    dtkComposerNodeForPrivate *d;
};

#endif

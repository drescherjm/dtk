/* dtkComposerNodeControl.h --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:03 2012 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. févr. 16 10:22:41 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROL_H
#define DTKCOMPOSERNODECONTROL_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControl declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControl : public dtkComposerNode
{
public:
             dtkComposerNodeControl(void);
    virtual ~dtkComposerNodeControl(void);

public:
    virtual void setInputs(void);
    virtual void setConditions(void);
    virtual void setOutputs(void);
    virtual void setVariables(void);
    virtual  int selectBranch(void);
    virtual void begin(void);
    virtual void end(void);

private:
    dtkComposerNodeControlPrivate *d;
};

#endif

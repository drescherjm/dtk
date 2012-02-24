/* dtkComposerNodeFor.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:12:58 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 24 16:21:43 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 16
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
    int blockCount(void);
    dtkComposerNodeLeaf *header(void);
    dtkComposerNodeLeaf *footer(void);
    dtkComposerNodeComposite *block(int id);

public:
    void setInputs(void);
    void setConditions(void);
    void setOutputs(void);
    void setVariables(void);
     int selectBranch(void);
    void begin(void);
    void end(void);

public:
    QString type(void);

public:
    QString titleHint(void);

private:
    dtkComposerNodeForPrivate *d;
};

#endif

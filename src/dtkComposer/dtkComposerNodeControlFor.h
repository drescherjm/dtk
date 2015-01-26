/* dtkComposerNodeControlFor.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:12:58 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerNodeControl.h"

class dtkComposerNodeControlForPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControlFor : public dtkComposerNodeControl
{
public:
     dtkComposerNodeControlFor(void);
    ~dtkComposerNodeControlFor(void);

public:
    int blockCount(void);
    dtkComposerNodeLeaf *header(void);
    dtkComposerNodeLeaf *footer(void);
    dtkComposerNodeComposite *block(int id);

public:
    void setInputs(void);
    void setOutputs(void);
    void setVariables(void);
     int selectBranch(void);
    void begin(void);
    void end(void);

private:
    dtkComposerNodeControlForPrivate *d;
};


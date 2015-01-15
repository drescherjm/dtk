// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerNodeControl.h"

class dtkComposerNodeControlForEachPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlForEach interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeControlForEach : public dtkComposerNodeControl
{
public:
             dtkComposerNodeControlForEach(void);
    virtual ~dtkComposerNodeControlForEach(void);

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
    dtkComposerNodeControlForEachPrivate *d;
};

// 
// dtkComposerNodeControlForEach.h ends here

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
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodePrintPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodePrint : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodePrint(void);
    ~dtkComposerNodePrint(void);

public:
    void run(void);

private:
    dtkComposerNodePrintPrivate *d;
};

// 
// dtkComposerNodePrint.h ends here

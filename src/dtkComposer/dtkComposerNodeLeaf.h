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

public:
    void setAsHeader(bool header);
    void setAsFooter(bool footer);

public:
    bool isHeader(void);
    bool isFooter(void);

private:
    dtkComposerNodeLeafPrivate *d;
};

//
// dtkComposerNodeLeaf.h ends here

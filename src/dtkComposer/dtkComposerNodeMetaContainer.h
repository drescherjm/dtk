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

class dtkComposerNodeMetaContainerPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainer interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMetaContainer : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMetaContainer(void);
    ~dtkComposerNodeMetaContainer(void);

public:
    void run(void);

private:
    dtkComposerNodeMetaContainerPrivate *d;
};

// 
// dtkComposerNodeMetaContainer.h ends here

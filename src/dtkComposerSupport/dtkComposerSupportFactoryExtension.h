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

#include "dtkComposerSupportExport.h"

#include <dtkComposer/dtkComposerNodeFactory.h>

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerSupportFactoryExtension : public dtkComposerNodeFactoryExtension
{
public:
    dtkComposerSupportFactoryExtension(void);
    ~dtkComposerSupportFactoryExtension(void);

public:
    void extend(dtkComposerNodeFactory *factory);
};

//
// dtkComposerSupportFactoryExtension.h ends here

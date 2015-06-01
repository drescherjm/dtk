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

#include "dtkComposerSupportFactoryExtension.h"

#include "dtkComposerNodeProcess.h"

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

dtkComposerSupportFactoryExtension::dtkComposerSupportFactoryExtension(void) : dtkComposerNodeFactoryExtension()
{

}

dtkComposerSupportFactoryExtension::~dtkComposerSupportFactoryExtension(void)
{

}

void dtkComposerSupportFactoryExtension::extend(dtkComposerNodeFactory *factory)
{
    factory->record(":dtkComposerSupport/dtkComposerNodeProcess.json", dtkComposerNodeCreator< dtkComposerNodeProcess >);
}

// 
// dtkComposerSupportFactoryExtension.cpp ends here

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

#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLeafPrivate
{
public:
    bool header;
    bool footer;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLeaf::dtkComposerNodeLeaf(void) : dtkComposerNode(), d(new dtkComposerNodeLeafPrivate)
{
    d->header = false;
    d->footer = false;
}

dtkComposerNodeLeaf::~dtkComposerNodeLeaf(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeLeaf::setInputs(void)
{
    // DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeLeaf::run(void)
{
    // DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeLeaf::setAsHeader(bool header)
{
    d->header = header;
}

void dtkComposerNodeLeaf::setAsFooter(bool footer)
{
    d->footer = footer;
}

bool dtkComposerNodeLeaf::isHeader(void)
{
    return d->header;
}

bool dtkComposerNodeLeaf::isFooter(void)
{
    return d->footer;
}

//
// dtkComposerNodeLeaf.cpp ends here

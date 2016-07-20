/* dtkComposerNodeLeaf.cpp ---
 *
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 21 11:03:51 2012 (+0100)
 *           By: tkloczko
 *     Update #: 27
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeLeaf.h"

#include <dtkCoreSupport/dtkGlobal.h>

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
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeLeaf::run(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
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

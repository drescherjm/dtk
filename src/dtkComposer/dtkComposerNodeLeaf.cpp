/* dtkComposerNodeLeaf.cpp --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 08:50:17 2012 (+0100)
 *           By: tkloczko
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeLeaf.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLeafPrivate
{
public:    

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLeaf::dtkComposerNodeLeaf(void) : dtkComposerNode(), d(new dtkComposerNodeLeafPrivate)
{

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

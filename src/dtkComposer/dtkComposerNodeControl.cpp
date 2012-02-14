/* dtkComposerNodeControl.cpp --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 14 16:32:51 2012 (+0100)
 *           By: David Rey
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControl.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlPrivate
{
public:    

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControl implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControl::dtkComposerNodeControl(void) : dtkComposerNode(), d(new dtkComposerNodeControlPrivate)
{

}

dtkComposerNodeControl::~dtkComposerNodeControl(void)
{
    delete d;
    d = NULL;
}

void dtkComposerNodeControl::setInputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControl::setConditions(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControl::setOutputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControl::setVariables(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControl::selectBranch(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControl::begin(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControl::end(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

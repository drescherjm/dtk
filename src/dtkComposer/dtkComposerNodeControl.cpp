/* dtkComposerNodeControl.cpp --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. févr. 16 10:23:43 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 22
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

int dtkComposerNodeControl::selectBranch(void)
{
    return -1;
}

void dtkComposerNodeControl::begin(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControl::end(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

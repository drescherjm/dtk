/* dtkComposerNodeFor.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:14:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 16 14:26:30 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeFor.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeForPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeForPrivate
{
public:    
    
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFor implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFor::dtkComposerNodeFor(void) : dtkComposerNodeControl(), d(new dtkComposerNodeForPrivate)
{

}

dtkComposerNodeFor::~dtkComposerNodeFor(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeFor::setInputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeFor::setConditions(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeFor::setOutputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeFor::setVariables(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

int dtkComposerNodeFor::selectBranch(void)
{
    return -1;
}

void dtkComposerNodeFor::begin(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeFor::end(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

QString dtkComposerNodeFor::type(void)
{
    return "for";
}

QString dtkComposerNodeFor::titleHint(void)
{
    return "For";
}

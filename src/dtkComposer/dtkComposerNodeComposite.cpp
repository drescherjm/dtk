/* dtkComposerNodeComposite.cpp ---
 *
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 20 14:11:28 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 32
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeComposite.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeCompositePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCompositePrivate
{
public:

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeComposite implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeComposite::dtkComposerNodeComposite(void) : dtkComposerNode(), d(new dtkComposerNodeCompositePrivate)
{

}

dtkComposerNodeComposite::~dtkComposerNodeComposite(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeComposite::type(void)
{
    return "composite";
}

void dtkComposerNodeComposite::begin(void)
{

}

void dtkComposerNodeComposite::end(void)
{

}

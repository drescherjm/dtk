/* dtkComposerNodeComposite.cpp ---
 *
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. févr. 20 16:09:51 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 28
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeComposite.h"

#include <dtkCore/dtkGlobal.h>

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

/* dtkComposerFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:37:32
 * Version: $Id$
 * Last-Updated: lun. janv. 30 11:42:15 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 6
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerFactory.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerFactoryPrivate
// /////////////////////////////////////////////////////////////////
class dtkComposerFactoryPrivate
{

};

dtkComposerFactory::dtkComposerFactory(void) : d(new dtkComposerFactoryPrivate)
{

}

dtkComposerFactory::~dtkComposerFactory(void)
{
    delete d;

    d = NULL;
}


/* @(#)dtkComposerNodeRemote.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:19:20
 * Version: $Id$
 * Last-Updated: mar. avril 10 18:06:51 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 21
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeRemote.h"



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemotePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemotePrivate
{
public:
    QDomDocument composition;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemote implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeRemote::dtkComposerNodeRemote(void) : dtkComposerNodeComposite(), d(new dtkComposerNodeRemotePrivate)
{
}

dtkComposerNodeRemote::~dtkComposerNodeRemote(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNodeRemote::type(void)
{
    return "remote";
}

QString dtkComposerNodeRemote::titleHint(void)
{
    return "Remote";
}

void dtkComposerNodeRemote::setComposition(QDomDocument document)
{
    d->composition = document;
}

void dtkComposerNodeRemote::begin(void)
{

}

void dtkComposerNodeRemote::end(void)
{

}

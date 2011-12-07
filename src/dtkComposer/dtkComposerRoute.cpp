/* dtkComposerRoute.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Dec  7 14:25:56 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  7 15:04:51 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeProperty.h"
#include "dtkComposerRoute.h"

#include <QtCore>

class dtkComposerRoutePrivate
{
public:
    dtkComposerNodeProperty *source;
    dtkComposerNodeProperty *destination;
};

dtkComposerRoute::dtkComposerRoute(void) : d(new dtkComposerRoutePrivate)
{
    d->source = NULL;
    d->destination = NULL;
}

dtkComposerRoute::~dtkComposerRoute(void)
{
    delete d;

    d = NULL;
}

bool dtkComposerRoute::active(void)
{
    return true;
}

dtkComposerNodeProperty *dtkComposerRoute::source(void)
{
    return d->source;
}

dtkComposerNodeProperty *dtkComposerRoute::destination(void)
{
    return d->destination;
}

void dtkComposerRoute::setSource(dtkComposerNodeProperty *property)
{
    d->source = property;
}

void dtkComposerRoute::setDestination(dtkComposerNodeProperty *property)
{
    d->destination = property;
}

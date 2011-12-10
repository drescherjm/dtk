/* dtkComposerRoute.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Dec  7 14:25:56 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Dec 10 17:29:08 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 35
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

// /////////////////////////////////////////////////////////////////
// dtkComposerRoutePrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerRoutePrivate
{
public:
    dtkComposerNodeProperty *source;
    dtkComposerNodeProperty *destination;

    bool active;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerRoute implementation
// /////////////////////////////////////////////////////////////////

//! Constructs a dtkComposerRoute.
/*! 
 *  Source and destination properties need to be defined.
 */
dtkComposerRoute::dtkComposerRoute(void) : d(new dtkComposerRoutePrivate)
{
    d->source = NULL;
    d->destination = NULL;

    d->active = false;
}

//! Destroys dtkComposerRoute.
/*! 
 *  
 */
dtkComposerRoute::~dtkComposerRoute(void)
{
    delete d;

    d = NULL;
}

// //! Returns true when route is active.
// /*! 
//  *  
//  */
// bool dtkComposerRoute::active(void)
// {
//     return d->active;
// }

// //! Sets route as active.
// /*! 
//  *  
//  */
// void dtkComposerRoute::activate(void)
// {
//     d->active = true;
// }

// //! Sets route as inactive.
// /*! 
//  *  
//  */
// void dtkComposerRoute::inactivate(void)
// {
//     d->active = false;
// }

//! Returns source property of the route.
/*! 
 *  
 */
dtkComposerNodeProperty *dtkComposerRoute::source(void)
{
    return d->source;
}

//! Returns destination property of the route.
/*! 
 *  
 */
dtkComposerNodeProperty *dtkComposerRoute::destination(void)
{
    return d->destination;
}

//! Sets source property.
/*! 
 *  
 */
void dtkComposerRoute::setSource(dtkComposerNodeProperty *property)
{
    d->source = property;
}

//! Sets destination property.
/*! 
 *  
 */
void dtkComposerRoute::setDestination(dtkComposerNodeProperty *property)
{
    d->destination = property;
}

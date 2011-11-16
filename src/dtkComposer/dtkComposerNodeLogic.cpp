/* dtkComposerNodeLogic.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Nov  4 14:16:40 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 14 09:22:37 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeLogic.h"

#include "dtkComposerEdge.h"
#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLogicPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLogicPrivate
{
public:
    QList<dtkComposerEdge *>  left_routes;
    QList<dtkComposerEdge *> right_routes;

public:
    dtkComposerNode *node;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLogic implementation
// /////////////////////////////////////////////////////////////////

//! Constructs dtkComposerNodeLogic.
/*! 
 *  
 */
dtkComposerNodeLogic::dtkComposerNodeLogic(dtkComposerNode *node) : QObject(node), d(new dtkComposerNodeLogicPrivate)
{
    d->node = node;
}

//! Destroys dtkComposerNodeLogic.
/*! 
 *  
 */
dtkComposerNodeLogic::~dtkComposerNodeLogic(void)
{
    delete d;
    d = NULL;
}

//! Return pointer to the owner node.
/*! 
 *  
 */
dtkComposerNode *dtkComposerNodeLogic::node(void)
{
    return d->node;
}

//! Appends \a route to the list of left routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::appendLeftRoute(dtkComposerEdge *route)
{
    if (d->left_routes.contains(route))
        return;

    d->left_routes << route;
}

//! Appends \a route to the list of right routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::appendRightRoute(dtkComposerEdge *route)
{
    if (d->right_routes.contains(route))
        return;

    d->right_routes << route;
}

//! Removes \a route from the list of left routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeLeftRoute(dtkComposerEdge *route)
{
    d->left_routes.removeAll(route);
}

//! Removes \a route from the list of right routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeRightRoute(dtkComposerEdge *route)
{
    d->right_routes.removeAll(route);
}

//! Clears left and right lists of routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeAllRoutes(void)
{
    d->left_routes.clear();
    d->right_routes.clear();
}

//! Returns list of left routes.
/*! 
 *  
 */
const QList<dtkComposerEdge *>& dtkComposerNodeLogic::leftRoutes(void) const
{
    return d->left_routes;
}

//! Returns list of right routes.
/*! 
 *  
 */
const QList<dtkComposerEdge *>& dtkComposerNodeLogic::rightRoutes(void) const
{
    return d->right_routes;
}


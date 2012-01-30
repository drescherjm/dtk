/* dtkComposerNodeLogic.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Nov  4 14:16:40 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Dec 12 14:12:26 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 168
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
#include "dtkComposerNodeProperty.h"
#include "dtkComposerRoute.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLogicPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLogicPrivate
{
public:
    QList<dtkComposerRoute *>  left_routes;
    QList<dtkComposerRoute *> right_routes;

    QList<dtkComposerRoute *>  left_relay_routes;
    QList<dtkComposerRoute *> right_relay_routes;

    QList<dtkComposerNode *>  left_nodes;
    QList<dtkComposerNode *> right_nodes;

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
void dtkComposerNodeLogic::appendLeftRoute(dtkComposerRoute *route)
{
    if (d->left_routes.contains(route))
        return;

    d->left_routes << route;
}

//! Appends \a route to the list of right routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::appendRightRoute(dtkComposerRoute *route)
{
    if (d->right_routes.contains(route))
        return;

    d->right_routes << route;
}

//! Removes \a route from the list of left routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeLeftRoute(dtkComposerRoute *route)
{
    d->left_routes.removeAll(route);
}

//! Removes \a route from the list of right routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeRightRoute(dtkComposerRoute *route)
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

//! Appends \a route to the list of left relay routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::appendLeftRelayRoute(dtkComposerRoute *route)
{
    if (d->left_relay_routes.contains(route))
        return;

    d->left_relay_routes << route;
}

//! Appends \a route to the list of right relay routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::appendRightRelayRoute(dtkComposerRoute *route)
{
    if (d->right_relay_routes.contains(route))
        return;

    d->right_relay_routes << route;
}

//! Removes \a route from the list of left relay routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeLeftRelayRoute(dtkComposerRoute *route)
{
    d->left_relay_routes.removeAll(route);
}

//! Removes \a route from the list of right relay routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeRightRelayRoute(dtkComposerRoute *route)
{
    d->right_relay_routes.removeAll(route);
}

//! Clears left and right lists of relay routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeAllRelayRoutes(void)
{
    d->left_relay_routes.clear();
    d->right_relay_routes.clear();
}

//! Appends \a node to the list of left nodes.
/*! 
 *  
 */
void dtkComposerNodeLogic::appendLeftNode(dtkComposerNode *node)
{
    if (d->left_nodes.contains(node))
        return;

    d->left_nodes << node;
}

//! Appends \a node to the list of right nodes.
/*! 
 *  
 */
void dtkComposerNodeLogic::appendRightNode(dtkComposerNode *node)
{
    if (d->right_nodes.contains(node))
        return;

    d->right_nodes << node;
}

//! Removes \a node from the list of left nodes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeLeftNode(dtkComposerNode *node)
{
    d->left_nodes.removeAll(node);
}

//! Removes \a node from the list of right nodes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeRightNode(dtkComposerNode *node)
{
    d->right_nodes.removeAll(node);
}

//! Clears left and right lists of nodes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeAllNodes(void)
{
    d->left_nodes.clear();
    d->right_nodes.clear();
}

//! Returns list of left routes.
/*! 
 *  
 */
const QList<dtkComposerRoute *>& dtkComposerNodeLogic::leftRoutes(void) const
{
    return d->left_routes;
}

//! Returns list of right routes.
/*! 
 *  
 */
const QList<dtkComposerRoute *>& dtkComposerNodeLogic::rightRoutes(void) const
{
    return d->right_routes;
}

//! Returns list of left relay routes.
/*! 
 *  
 */
const QList<dtkComposerRoute *>& dtkComposerNodeLogic::leftRelayRoutes(void) const
{
    return d->left_relay_routes;
}

//! Returns list of right relay routes.
/*! 
 *  
 */
const QList<dtkComposerRoute *>& dtkComposerNodeLogic::rightRelayRoutes(void) const
{
    return d->right_relay_routes;
}

//! Returns list of left nodes.
/*! 
 *  
 */
const QList<dtkComposerNode *>& dtkComposerNodeLogic::leftNodes(void) const
{
    return d->left_nodes;
}

//! Returns list of right nodes.
/*! 
 *  
 */
const QList<dtkComposerNode *>& dtkComposerNodeLogic::rightNodes(void) const
{
    return d->right_nodes;
}

//! 
/*! 
 *  
 */
bool dtkComposerNodeLogic::isRoute(dtkComposerNodeProperty *source, dtkComposerNodeProperty *destination)
{
    dtkComposerNode *destin_node = destination->node();

    foreach(dtkComposerRoute *left, destin_node->l->leftRoutes()) {
        if (left->source() == source && left->destination() == destination)
            return true;
    }

    foreach(dtkComposerRoute *left, destin_node->l->rightRelayRoutes()) {
        if (left->source() == source && left->destination() == destination)
            return true;
    }

    foreach(dtkComposerRoute *right, this->rightRoutes()) {
        if (right->source() == source && right->destination() == destination)
            return true;
    }

    foreach(dtkComposerRoute *right, this->leftRelayRoutes()) {
        if (right->source() == source && right->destination() == destination)
            return true;
    }

    return false;
}

//! 
/*! 
 *  
 */
bool dtkComposerNodeLogic::connectRoute(dtkComposerNodeProperty *source, dtkComposerNodeProperty *destination, dtkComposerNode *destin_node)
{
    bool  left_connection_ok = true;
    bool right_connection_ok = true;

    foreach(dtkComposerRoute *left, destin_node->l->leftRoutes()) {
        if (left->source() == source && left->destination() == destination)
            return true;
    }

    foreach(dtkComposerRoute *right, this->rightRoutes()) {
        if (right->source() == source && right->destination() == destination)
            return true;
    }
  
    dtkComposerRoute *route = new dtkComposerRoute;
    route->setSource(source);
    route->setDestination(destination);

     left_connection_ok = destin_node->onLeftRouteConnected(route, destination);
    right_connection_ok = d->node->onRightRouteConnected(route, source);

    if (left_connection_ok && right_connection_ok) {

        destin_node->appendSourceRoutes(route);
        d->node->appendDestinationRoutes(route);

        destin_node->appendSourceNodes(route);
        d->node->appendDestinationNodes(route);

        return true;

    } else {

       delete route; 
       route = NULL;

       return false;

    }

    // if (left_connection_ok) {
    //     destin_node->appendSourceRoutes(route);
    //     d->node->appendDestinationRoutes(route);
    // }
    
    // if (right_connection_ok) {
    //     destin_node->appendSourceNodes(route);
    //     d->node->appendDestinationNodes(route);
    // }

    // if (!left_connection_ok && !right_connection_ok) {
    //     delete route;
    //     route = NULL;
    // }

    // if (!left_connection_ok || !right_connection_ok)
    //     return false;

    return true;
}

            // if (source->type() == dtkComposerNodeProperty::Generic) {
                
            //     if (source->position() == dtkComposerNodeProperty::Right) {
                    
            //         if (source->node()->kind() == dtkComposerNode::Control) {
                        
            //             dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());                    
            //             control_node->l->appendRightRoute(route);
                    
            //             // dtkComposerRoute *active_route = new dtkComposerRoute;
            //             // active_route->setSource(route->source());
            //             // active_route->setDestination(route->destination());
                        
            //             // control_node->addOutputActiveRoute(active_route);
                        
            //             if (destin->position() == dtkComposerNodeProperty::Right) {
            //                 dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
            //                 output_control_node->addOutputRelayRoute(route);

            //             } else {                            
            //                 destin->node()->l->appendLeftRoute(route);                            
            //             }
                        
            //         } else {
                        
            //             source->node()->l->appendRightRoute(route);
                        
            //             if (destin->position() == dtkComposerNodeProperty::Right && 
            //                 source->node()->isChildOfControlNode(destin->node())) { 
                            
            //                 dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
            //                 control_node->addOutputRelayRoute(route);
                            
            //             } else {
                            
            //                 destin->node()->l->appendLeftRoute(route);
                            
            //             }
            //         }
                    
            //     } else {

            //         dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());
            //         control_node->addInputRelayRoute(route);
                    
            //     }

            // } else if (source->type() == dtkComposerNodeProperty::HybridOutput || 
            //            source->type() == dtkComposerNodeProperty::PassThroughOutput || 
            //            (source->type() == dtkComposerNodeProperty::Output && source->node()->kind() == dtkComposerNode::Control && !destin->node()->isChildOfControlNode(source->node()))) {

            //     dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());                    
            //     control_node->l->appendRightRoute(route);

            //     dtkComposerRoute *active_route = new dtkComposerRoute;
            //     active_route->setSource(route->source());
            //     active_route->setDestination(route->destination());

            //     control_node->addOutputActiveRoute(active_route);

            //     if (destin->type() == dtkComposerNodeProperty::HybridOutput || 
            //         destin->type() == dtkComposerNodeProperty::PassThroughOutput || 
            //         (destin->type() == dtkComposerNodeProperty::Input && destin->node()->kind() == dtkComposerNode::Control && source->node()->isChildOfControlNode(destin->node()))) {
            //         dtkComposerNodeControl *output_control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
            //         output_control_node->addOutputRelayRoute(active_route);
            //     } else {
            //         destin->node()->l->appendLeftRoute(active_route);
            //     }

            // } else if (source->type() == dtkComposerNodeProperty::HybridInput || 
            //            source->type() == dtkComposerNodeProperty::PassThroughInput || 
            //            (source->type() == dtkComposerNodeProperty::Output && source->node()->kind() == dtkComposerNode::Control && destin->node()->isChildOfControlNode(source->node()))) {

            //     dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());
            //     control_node->addInputRelayRoute(route);

            // } else if (destin->type() == dtkComposerNodeProperty::HybridOutput || 
            //            destin->type() == dtkComposerNodeProperty::PassThroughOutput || 
            //            (destin->type() == dtkComposerNodeProperty::Input && destin->node()->kind() == dtkComposerNode::Control && source->node()->isChildOfControlNode(destin->node()))) {

            //     dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(destin->node());
            //     control_node->addOutputRelayRoute(route);
            //     source->node()->l->appendRightRoute(route);

            // } else {
                
            //     destin->node()->l->appendLeftRoute(route);
            //     source->node()->l->appendRightRoute(route);
            // }

//! 
/*! 
 *  
 */
bool dtkComposerNodeLogic::disconnectRoute(dtkComposerNodeProperty *source, dtkComposerNodeProperty *destination, dtkComposerNode *destin_node)
{
    dtkComposerRoute  *left_route = NULL;
    dtkComposerRoute *right_route = NULL;

    foreach(dtkComposerRoute *l_route, destin_node->l->leftRoutes()) {
        if (l_route->source() == source && l_route->destination() == destination) {
            left_route = l_route;
            break;
        }
    }
    
    foreach(dtkComposerRoute *r_route, this->rightRoutes()) {
        if (r_route->source() == source && r_route->destination() == destination) {
            right_route = r_route;
            break;
        }
    }

    Q_UNUSED(destin_node->onLeftRouteDisconnected(left_route, destination));
    Q_UNUSED(this->node()->onRightRouteDisconnected(right_route, source));    
    
    if (left_route) {
        destin_node->removeSourceRoutes(left_route);
        destin_node->removeSourceNodes(left_route);
    }

    if (right_route) {
        d->node->removeDestinationRoutes(right_route);
        d->node->removeDestinationNodes(right_route);
    }
    
    if (left_route == right_route)
        right_route = NULL;
    
    if (left_route)
        delete left_route;
    
    if (right_route)
        delete right_route;
    
     left_route = NULL;
    right_route = NULL;

    return true;
}

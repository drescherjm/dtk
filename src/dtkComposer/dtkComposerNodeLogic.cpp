/* dtkComposerNodeLogic.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Nov  4 14:16:40 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Dec  1 15:21:30 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 83
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

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLogicPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLogicPrivate
{
public:
    QList<dtkComposerEdge *>  left_routes;
    QList<dtkComposerEdge *> right_routes;

    QList<dtkComposerEdge *>  left_relay_routes;
    QList<dtkComposerEdge *> right_relay_routes;

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

//! Appends \a route to the list of left relay routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::appendLeftRelayRoute(dtkComposerEdge *route)
{
    if (d->left_relay_routes.contains(route))
        return;

    d->left_relay_routes << route;
}

//! Appends \a route to the list of right relay routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::appendRightRelayRoute(dtkComposerEdge *route)
{
    if (d->right_relay_routes.contains(route))
        return;

    d->right_relay_routes << route;
}

//! Removes \a route from the list of left relay routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeLeftRelayRoute(dtkComposerEdge *route)
{
    d->left_relay_routes.removeAll(route);
}

//! Removes \a route from the list of right relay routes.
/*! 
 *  
 */
void dtkComposerNodeLogic::removeRightRelayRoute(dtkComposerEdge *route)
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

//! Returns list of left relay routes.
/*! 
 *  
 */
const QList<dtkComposerEdge *>& dtkComposerNodeLogic::leftRelayRoutes(void) const
{
    return d->left_relay_routes;
}

//! Returns list of right relay routes.
/*! 
 *  
 */
const QList<dtkComposerEdge *>& dtkComposerNodeLogic::rightRelayRoutes(void) const
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
bool dtkComposerNodeLogic::canConnectRoute(dtkComposerNodeProperty *source, dtkComposerNodeProperty *destination, dtkComposerNode *destin_node)
{
    // qDebug() << DTK_PRETTY_FUNCTION << this->node();

    bool  left_connection_ok = true;
    bool right_connection_ok = true;

    foreach(dtkComposerEdge *left, destin_node->l->leftRoutes()) {
        if (left->source() == source && left->destination() == destination)
            return true;
    }

    foreach(dtkComposerEdge *right, this->rightRoutes()) {
        if (right->source() == source && right->destination() == destination)
            return true;
    }
  
    dtkComposerEdge *route = new dtkComposerEdge;
    route->setSource(source);
    route->setDestination(destination);

    left_connection_ok  = destin_node->onLeftRouteConnected(route, destination);
    right_connection_ok = d->node->onRightRouteConnected(route, source);

    if (left_connection_ok) {
        destin_node->updateSourceRoutes(route);
        d->node->updateDestinationRoutes(route);
    }
    
    if (right_connection_ok) {
        destin_node->updateSourceNodes(route);
        d->node->updateDestinationNodes(route);
    }

    if (!left_connection_ok && !right_connection_ok) {
        delete route;
        route = NULL;
    }

    if (!left_connection_ok || !right_connection_ok)
        return false;

    return true;
}

            // if (source->type() == dtkComposerNodeProperty::Generic) {
                
            //     if (source->position() == dtkComposerNodeProperty::Right) {
                    
            //         if (source->node()->kind() == dtkComposerNode::Control) {
                        
            //             dtkComposerNodeControl *control_node = dynamic_cast<dtkComposerNodeControl *>(source->node());                    
            //             control_node->l->appendRightRoute(route);
                    
            //             // dtkComposerEdge *active_route = new dtkComposerEdge;
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

            //     dtkComposerEdge *active_route = new dtkComposerEdge;
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

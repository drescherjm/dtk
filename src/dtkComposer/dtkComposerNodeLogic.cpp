/* dtkComposerNodeLogic.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Nov  4 14:16:40 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Nov 25 15:04:53 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 66
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

//! Returns list of right routes.
/*! 
 *  
 */
bool dtkComposerNodeLogic::canConnectRoute(dtkComposerNodeProperty *source, dtkComposerNodeProperty *destination, dtkComposerNode *destin_node)
{
    // qDebug() << DTK_PRETTY_FUNCTION << this->node();

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

    if (!destin_node->onLeftRouteConnected(route, destination)) {
        delete route;
        return false;
    }

    if (!d->node->onRightRouteConnected(route, source)) {
        delete route;
        return false;
    }
    
    destin_node->l->appendLeftRoute(route);
    this->appendRightRoute(route);

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
